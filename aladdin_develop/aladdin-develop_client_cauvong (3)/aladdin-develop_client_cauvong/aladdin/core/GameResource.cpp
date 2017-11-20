/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "GameResource.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::GameResource, ala::Loadable, ala::Releasable)

GameResource::GameResource( const std::string& name, Scene* sceneScope )
  : _name( name ),
    _sceneScope( sceneScope ) {
  // check initial state
  ALA_ASSERT((!isLoaded()) && (!isLoading()) && (!isReleased()) && (!isReleasing()));

  // attach to game manager
  GameManager::get()->attach( this );

  TOTAL_RESOURCES_CREATED++;
}

GameResource::~GameResource() {
  if ( isLoaded() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }
  TOTAL_RESOURCES_DELETED++;
}

const std::string& GameResource::getName() const {
  return _name;
}

void GameResource::load() {
  // make sure that object is not loaded
  ALA_ASSERT((!isLoaded()) && (!isLoading()));

  setToLoading();

  // TODO: lock mutual exclusive when run in multithreading mode

  onLoad();

  setToLoaded();
}

void GameResource::release() {
  // make sure object is initialized and not released
  ALA_ASSERT((isLoaded()) && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode

  onRelease();

  // detach from game manager
  GameManager::get()->detach( this );

  setToReleased();

  // destroy
  delete this;
}

void GameResource::setGameScope() {
  _sceneScope = NULL;
}

void GameResource::setSceneScope( Scene* sceneScope ) {
  _sceneScope = sceneScope;
}

Scene* GameResource::getSceneScope() const {
  return _sceneScope;
}

bool GameResource::isGameScope() const {
  return _sceneScope == NULL;
}

bool GameResource::isShared() const {
  return true;
}

GameResource* GameResource::clone() {
  return this;
}

// =============================================
// Debug memory allocation
// =============================================
long GameResource::TOTAL_RESOURCES_CREATED( 0 );
long GameResource::TOTAL_RESOURCES_DELETED( 0 );
}
