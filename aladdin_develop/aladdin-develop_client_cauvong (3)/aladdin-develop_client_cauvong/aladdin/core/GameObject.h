#ifndef __ALADDIN_CORE_GAME_OBJECT_H__
#define __ALADDIN_CORE_GAME_OBJECT_H__

/*
* Created on Sep 27th 2017
*/

#include "GameObjectComponent.h"
#include "Transform.h"
#include "Messenger.h"

NAMESPACE_ALA
{
class CollisionInfo;
class Scene;

ALA_CLASS_HEADER_2(GameObject, ala::Initializable, ala::Releasable)
  // =========================================================================
  // Basic
  // =========================================================================
private:
  long _id;
  std::string _name;
  Scene* _parentScene;
  std::string _layer;
  bool _active;
  bool _selfInitialize;
  bool _toReleaseInNextFrame;

public:
  /**
   * \brief Create a game object, attach to game manager and attach to parent scene
   */
  GameObject( Scene* parentScene, const std::string& name = "", const std::string& quadIndex = "" );

  /**
   * \brief Create a game object, attach to game manager and attach its transform to "parentObject"'s transform 
   */
  GameObject( GameObject* parentObject, const std::string& name = "" );

  virtual ~GameObject();

  long getId() const;

  const std::string& getName() const;

  Scene* getParentScene() const;

  bool isActive() const;

  GameObject* setActive( const bool val );

  bool isSelfInitialize() const;

  GameObject* setSelfInitialize( const bool val );

  const std::string& getLayer() const;

  GameObject* setLayer( const std::string& layer );

  // =========================================================
  // Events
  // =========================================================
public:
  void initialize() override;

  void updatePhysics( const float delta );

  void update( const float delta );

  void onCollisionEnter( const CollisionInfo& collisionInfo );
  void onCollisionStay( const CollisionInfo& collisionInfo );
  void onCollisionExit( const CollisionInfo& collisionInfo );

  void onTriggerEnter( const CollisionInfo& collisionInfo );
  void onTriggerStay( const CollisionInfo& collisionInfo );
  void onTriggerExit( const CollisionInfo& collisionInfo );

  void render();

  /**
   * \brief Release and destroy game object, automatically removed from parent scene or "parent object" and detached from game manager
   */
  void release() override;

  void releaseInNextFrame();

public:
  void resolveLockedTasks();

  virtual void onResolveLockedTasks();

  // ========================================================
  // Components
  // ========================================================
private:
  bool _componentsInLock;
  std::vector<GameObjectComponent*> _components;
  std::vector<GameObjectComponent*> _componentsToAddInNextFrame;
  std::vector<GameObjectComponent*> _componentsToRemoveInNextFrame;

public:
  /**
   * \brief Attach a component to game object, this will not change component's game object, you should not call this method directly
   * \param component Component to attach
   */
  void addComponent( GameObjectComponent* component );

  void addComponentInNextFrame( GameObjectComponent* component );

  /**
   * \brief Detach a component from game object, this will not release component, you will have to delete in your own when it's necessary
   * \param component Component to detach
   */
  void removeComponent( GameObjectComponent* component );

  void removeComponentInNextFrame( GameObjectComponent* component );

  GameObjectComponent* getComponent( const std::string& name ) const;

  std::vector<GameObjectComponent*> getAllComponents() const;

  std::vector<GameObjectComponent*> getAllComponents( const std::string& name ) const;

  template <class T>
  T* getComponentT() const;

  template <class T>
  std::vector<T*> getAllComponentTs() const;

private:
  void lockComponents();

  void unlockComponents();

  void updateAddAndRemoveComponentInNextFrame();

  void doAddComponent( GameObjectComponent* component );

  void doRemoveComponent( GameObjectComponent* component );

  // ========================================================
  // Default components
  // ========================================================
private:
  Transform* _transform;

  bool isDefaultComponents( GameObjectComponent* component );

public:
  Transform* getTransform() const;

  // ===========================================================
  // Messenger
  // ===========================================================

private:
  Messenger* _messenger;

public:
  Messenger* getMessenger() const;

  // ===========================================================
  // Debug memory allocation
  // ===========================================================
public:
  static long TOTAL_OBJECTS_CREATED;
  static long TOTAL_OBJECTS_DELETED;
};

// TEMPLATE DEFINITIONS

// ========================================================
// Components
// ========================================================

template <class T>
T* GameObject::getComponentT() const {
  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && ALA_IS_INSTANCE_OF(component, T) ) {
      return static_cast<T*>(component);
    }
  }
  return NULL;
}

template <class T>
std::vector<T*> GameObject::getAllComponentTs() const {
  std::vector<T*> ret;

  for ( GameObjectComponent* component : _components ) {
    if ( component != NULL && ALA_IS_INSTANCE_OF( component, T) ) {
      ret.emplace_back( static_cast<T*>(component) );
    }
  }
  return ret;
}
}


#endif //!__ALADDIN_CORE_GAME_OBJECT_H__
