/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Scene.h"
#include "StdHelper.h"
#include "GameResource.h"
#include "GameManager.h"
#include "../2d/2dMacros.h"
#include "../2d/Camera.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::Scene, ala::Initializable, ala::Releasable)

// ================================================
// Basic
// ================================================

Scene::Scene(): _toReleaseInNextFrame( false ),
                _gameObjectInLock( false ),
                _quadTree( NULL ),
                _physicsEnabled( false ),
                _gravityAcceleration( 0, -100.0f ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  TOTAL_SCENES_CREATED++;
}

Scene::~Scene() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  TOTAL_SCENES_DELETED++;
}

// =================================================
// Events
// =================================================

void Scene::initialize() {
  // make sure scene is not initialized;
  ALA_ASSERT((!isInitializing()) && (!isInitialized()));

  // required framework objects
  ala::GameManager::get()->getPrefab( ALA_MAIN_CAMERA )->instantiate( ALA_MAIN_CAMERA );

  onPreInitialize();

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // load resources scope with this
  for ( auto resource : GameManager::get()->getResourcesWith( this ) ) {
    if ( !resource->isLoaded() ) {
      resource->load();
    }
  }

  // init game objects
  for ( const auto it : _gameObjects ) {
    auto object = it.second;

    if ( !object->isInitialized() ) {
      object->initialize();
    }
  }

  setToInitialized();

  onPostInitialize();
}

void Scene::onPreInitialize() { }

void Scene::onPostInitialize() {}

void Scene::updatePhysics( const float delta ) {
  if ( isReleasing() || isReleased() || !isInitialized() || !isPhysicsEnabled() ) return;

  lockGameObjects();

  onPrePhysicsUpdate( delta );

  // update game objects

  if ( !isQuadTreeEnabled() ) {
    for ( const auto it : _gameObjects ) {
      auto object = it.second;
      object->updatePhysics( delta );
    }
  }
  else {
    for ( const auto visibleNode : _quadTree->getVisibleNodes() ) {
      for ( const auto object : visibleNode->getGameObjects() ) {
        object->updatePhysics( delta );
      }
    }

    for ( const auto it : _dynamicGameObjects ) {
      auto object = it.second;
      object->updatePhysics( delta );
    }
  }

  onPostPhysicsUpdate( delta );

  unlockGameObjects();
}

void Scene::onPrePhysicsUpdate( const float delta ) {}

void Scene::onPostPhysicsUpdate( const float delta ) {}

void Scene::update( const float delta ) {
  if ( isReleasing() || isReleased() || !isInitialized() ) return;

  lockGameObjects();

  onPreUpdate( delta );

  // update game objects

  if ( !isQuadTreeEnabled() ) {
    for ( const auto it : _gameObjects ) {
      auto object = it.second;
      object->update( delta );
    }
  }
  else {
    for ( const auto visibleNode : _quadTree->getVisibleNodes() ) {
      for ( const auto object : visibleNode->getGameObjects() ) {
        object->update( delta );
      }
    }

    for ( const auto it : _dynamicGameObjects ) {
      auto object = it.second;
      object->update( delta );
    }
  }

  onPostUpdate( delta );

  unlockGameObjects();
}

void Scene::onPreUpdate( const float delta ) {}

void Scene::onPostUpdate( const float delta ) {}

void Scene::render() {
  // make sure scene is initialized and not being released
  if ( (!isInitialized()) || isReleasing() || isReleased() ) return;

  lockGameObjects();

  onPreRender();

  // render game objects
  if ( !isQuadTreeEnabled() ) {
    for ( const auto it : _gameObjects ) {
      auto object = it.second;
      object->render();
    }
  }
  else {
    for ( const auto visibleNode : _quadTree->getVisibleNodes() ) {
      for ( const auto object : visibleNode->getGameObjects() ) {
        object->render();
      }
    }

    for ( const auto it : _dynamicGameObjects ) {
      auto object = it.second;
      object->render();
    }
  }


  onPostRender();

  unlockGameObjects();
}

void Scene::onPreRender() {}

void Scene::onPostRender() {}

void Scene::release() {
  // check lock
  if ( _gameObjectInLock ) {
    releaseInNextFrame();
    return;
  }

  // make sure scene is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));

  onPreRelease();

  setToReleasing();

  // release quad tree
  if ( _quadTree != NULL ) delete _quadTree;

  // release game objects
  std::vector<GameObject*> gameObjectsToRelease;
  for ( const auto it : _gameObjects ) {
    auto object = it.second;
    object->release();
  }

  // release resources scope with this
  for ( auto resouce : GameManager::get()->getResourcesWith( this ) ) {
    resouce->release();
  }

  setToReleased();

  onPostRelease();

  // destroy
  delete this;
}

void Scene::releaseInNextFrame() {
  // make sure scene is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));
  _toReleaseInNextFrame = true;
}

void Scene::onPreRelease() {}

void Scene::onPostRelease() {}

void Scene::resolveLockedTasks() {
  if ( isReleasing() || isReleased() ) return;

  // lazy initialization
  if ( !isInitialized() ) {
    initialize();
  }

  // update to release in next frame
  if ( _toReleaseInNextFrame ) {
    release();
    _toReleaseInNextFrame = false;
    return;
  }

  // update locked actions
  updateAddAndRemoveGameObjects();

  // update quad tree
  if ( isQuadTreeEnabled() ) {
    updateQuadTreeVisibility();
  }

  // client
  onResolveLockedTasks();

  // update game object locked tasks
  lockGameObjects();

  if ( !isQuadTreeEnabled() ) {
    for ( const auto it : _gameObjects ) {
      auto object = it.second;
      object->resolveLockedTasks();
    }
  }
  else {
    for ( const auto visibleNode : _quadTree->getVisibleNodes() ) {
      for ( const auto object : visibleNode->getGameObjects() ) {
        object->resolveLockedTasks();
      }
    }

    for ( const auto it : _dynamicGameObjects ) {
      auto object = it.second;
      object->resolveLockedTasks();
    }
  }

  unlockGameObjects();
}

void Scene::onResolveLockedTasks() { }

// ==================================================
// Objects Management
// ==================================================

GameObject* Scene::getGameObject( const long id ) const {
  const auto it = _gameObjects.find( id );
  if ( it == _gameObjects.end() ) return NULL;
  return it->second;
}

GameObject* Scene::getMainCamera() const {
  for ( const auto it : _gameObjects ) {
    const auto object = it.second;
    if ( object->getName() == ALA_MAIN_CAMERA ) return object;
  }
  return NULL;
}

void Scene::addGameObject( GameObject* gameObject, const std::string& quadIndex ) {
  // check lock
  if ( _gameObjectInLock ) {
    addGameObjectInNextFrame( gameObject );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  doAddGameObject( gameObject, quadIndex );
}

void Scene::addGameObjectInNextFrame( GameObject* gameObject, const std::string& quadIndex ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _gameObjectsToAddInNextFrame.push_back( std::make_pair( gameObject, quadIndex ) );
}

void Scene::removeGameObject( GameObject* gameObject ) {
  // check lock
  if ( _gameObjectInLock ) {
    removeGameObjectInNextFrame( gameObject );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  doRemoveGameObject( gameObject->getId() );
}

void Scene::removeGameObjectInNextFrame( GameObject* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _gameObjectsToRemoveInNextFrame.push_back( gameObject->getId() );
}

QuadTree* Scene::getQuadTree() const {
  return _quadTree;
}

void Scene::enableQuadTree( const float spaceMinX, const float spaceMinY,
                            const float spaceMaxX, const float spaceMaxY,
                            const int level ) {
  _quadTree = new QuadTree( spaceMinX, spaceMinY, spaceMaxX, spaceMaxY, level );
}

bool Scene::isQuadTreeEnabled() const {
  return _quadTree != NULL;
}

void Scene::updateQuadTreeVisibility() const {
  const auto camera = getMainCamera();
  const auto cameraPosition = camera->getTransform()->getPosition();
  const auto halfVisibleWidth = GameManager::get()->getVisibleWidth() / 2;
  const auto halfVisibleHeight = GameManager::get()->getVisibleHeight() / 2;

  // TODO: calculate with camera scale

  const auto cameraMinX = cameraPosition.getX() - halfVisibleWidth;
  const auto cameraMinY = cameraPosition.getY() - halfVisibleHeight;
  const auto cameraMaxX = cameraPosition.getX() + halfVisibleWidth;
  const auto cameraMaxY = cameraPosition.getY() + halfVisibleHeight;

  _quadTree->updateVisibility( cameraMinX, cameraMinY, cameraMaxX, cameraMaxY );
}

void Scene::lockGameObjects() {
  _gameObjectInLock = true;
}

void Scene::unlockGameObjects() {
  _gameObjectInLock = false;
}

void Scene::updateAddAndRemoveGameObjects() {
  for ( const auto it : _gameObjectsToAddInNextFrame ) {
    doAddGameObject( it.first, it.second );
  }
  _gameObjectsToAddInNextFrame.clear();

  for ( auto objectId : _gameObjectsToRemoveInNextFrame ) {
    doRemoveGameObject( objectId );
  }
  _gameObjectsToRemoveInNextFrame.clear();
}

void Scene::doAddGameObject( GameObject* gameObject, const std::string& quadIndex ) {
  _gameObjects.emplace( gameObject->getId(), gameObject );

  if ( quadIndex.empty() ) {
    _dynamicGameObjects.emplace( gameObject->getId(), gameObject );
  }
  else {
    _quadTree->getNode( quadIndex )->addGameObject( gameObject );
    _gameObjectToQuadNode.emplace( gameObject->getId(), quadIndex );
  }
}

void Scene::doRemoveGameObject( const long id ) {
  const auto gameObjectIt = _gameObjects.find( id );
  if ( gameObjectIt == _gameObjects.cend() ) return;

  const auto gameObjectToQuadNodeIt = _gameObjectToQuadNode.find( id );
  if ( gameObjectToQuadNodeIt != _gameObjectToQuadNode.cend() ) {
    _quadTree->getNode( gameObjectToQuadNodeIt->second )->removeGameObject( gameObjectIt->second );
    _gameObjectToQuadNode.erase( gameObjectToQuadNodeIt );
  }

  _gameObjects.erase( id );
  _dynamicGameObjects.erase( id );
}

const Vec2& Scene::getGravityAcceleration() const {
  return _gravityAcceleration;
}

void Scene::enablePhysics( const Vec2& gravity ) {
  _physicsEnabled = true;
  _gravityAcceleration = gravity;
}

bool Scene::isPhysicsEnabled() const {
  return _physicsEnabled;
}

// =============================================
// Debug memory allocation
// =============================================
long Scene::TOTAL_SCENES_CREATED( 0 );
long Scene::TOTAL_SCENES_DELETED( 0 );
}
