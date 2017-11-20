#ifndef __ALADDIN_CORE_GAME_MANAGER_H__
#define __ALADDIN_CORE_GAME_MANAGER_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"
#include "Scene.h"
#include "GameResource.h"
#include "Prefab.h"
#include "Logger.h"
#include "Messenger.h"
#include "Color.h"

NAMESPACE_ALA
{
class Sprite;

ALA_CLASS_HEADER_1(GameManager, ala::Releasable)
  // ==============================================
  // Basic
  // ==============================================
  friend class Application;

private:
  static GameManager* __instance;
  Logger _logger;

public:
  GameManager();

  virtual ~GameManager();

  static GameManager* get();

  void update( const float delta );

  void release() override;

  void onBackgroundToForeground();

  // ===============================================
  // Game Information
  // ===============================================
private:
  float _visibleWidth;
  float _visibleHeight;

public:
  float getVisibleWidth() const;
  float getVisibleHeight() const;

  // ===============================================
  // Id Generator
  // ===============================================
private:
  long _idCounter;

public:
  long newId();

  // ===============================================
  // Object Management
  // ===============================================
private:
  std::unordered_map<long, GameObject*> _attachedObjects;

public:
  void attach( GameObject* gameObject );

  void detach( GameObject* gameObject );

  std::vector<GameObject*> getAllObjects() const;

  GameObject* getObjectById( const long id ) const;

  template <class T>
  T* getObjectTById( const long id ) const;

  std::vector<GameObject*> getAllObjectsByName( const std::string& name ) const;

  GameObject* getObjectByName( const std::string& name ) const;

  template <class T>
  T* getObjectTByName( const std::string& name ) const;

  // ===============================================
  // Scene Management
  // ===============================================
private:
  Scene* _runningScene;
  Scene* _sceneToReplaceInNextFrame;

public:
  Scene* getRunningScene() const;

  GameObject* getMainCamera() const;

  void replaceScene( Scene* scene );

  void replaceSceneInNextFrame( Scene* scene );

private:
  void updateRunningScene();
  void doReplaceScene( Scene* scene );

  // ===============================================
  // Resource Management
  // ===============================================
private:
  std::unordered_map<std::string, GameResource*> _attachedResources;

public:
  void attach( GameResource* resource );

  void detach( GameResource* resource );

  GameResource* getResource( const std::string& name );

  Sprite* getEmptySprite( const ala::Color& color );

  std::vector<GameResource*> getResourcesWith( Scene* scope );

  std::vector<GameResource*> getAllResources();

  // ===============================================
  // Prefab Management
  // ===============================================
private:
  std::unordered_map<std::string, Prefab*> _registeredPrefabs;

public:
  void registerPrefab( Prefab* prefab );

  void removePrefab( Prefab* prefab );

  Prefab* getPrefab( const std::string& name );

  std::vector<Prefab*> getAllPrefabs();

  // ===============================================
  // Global Messenger
  // ===============================================
private:
  Messenger* _globalMessenger;

public:
  Messenger* getGlobalMessenger() const;

  // ===============================================
  // Layer Management
  // ===============================================
private:
  std::unordered_map<std::string, int> _layers;

public:
  void addLayer( const std::string& layer );

  int getLayerIndex( const std::string& layer );
};

// TEMPLATE DEFINITIONS

// ===============================================
// Object Management
// ===============================================

template <class T>
T* GameManager::getObjectTById( const long id ) const {
  const auto objectIt = _attachedObjects.find( id );
  if ( objectIt == _attachedObjects.end() ) return NULL;

  const auto object = objectIt->second;
  if ( ALA_IS_INSTANCE_OF( object, T) ) {
    return static_cast<T *>(object);
  }
  return NULL;
}

template <class T>
T* GameManager::getObjectTByName( const std::string& name ) const {
  for ( auto& pair : _attachedObjects ) {
    auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      if ( ALA_IS_INSTANCE_OF(object, T) ) {
        return static_cast<T *>(object);
      }
    }
  }
  return NULL;
}
}

#endif //__ALADDIN_CORE_GAME_MANAGER_H__
