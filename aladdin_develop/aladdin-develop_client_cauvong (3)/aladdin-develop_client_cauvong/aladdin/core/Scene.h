/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_SCENE_H__
#define __ALADDIN_CORE_SCENE_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "QuadTree.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Scene, ala::Initializable, ala::Releasable)

  // ================================================
  // Basic
  // ================================================
private:
  bool _toReleaseInNextFrame;

public:
  /**
   * \brief Create a scene, this will not be managed unless you attach to GameManager by call replaceScene
   */
  Scene();

  virtual ~Scene();

  // ==================================================
  // Events
  // ==================================================
public:
  void initialize() override;

protected:

  /**
   * \brief Add Default Objects and Scene Resources here, they will be init right after this function return
   */
  virtual void onPreInitialize();

  /**
  * \brief Add special Logic happen after initlization, every object and component in scene has been initialized
  * Object and Component added to scene there will be not automatically init, so you have to init them manually
  */
  virtual void onPostInitialize();

public:
  void updatePhysics( const float delta );

protected:
  /**
  * \brief Happen before scene, its objects and components were physically updated
  * \param delta
  */
  virtual void onPrePhysicsUpdate( const float delta );


  /**
  * \brief Happen after scene, its objects and components were physically updated
  */
  virtual void onPostPhysicsUpdate( const float delta );

public:
  void update( const float delta );

protected:

  /**
   * \brief Happen before scene, its objects and components were updated
   * \param delta 
   */
  virtual void onPreUpdate( const float delta );


  /**
   * \brief Happen after scene, its objects and components were updated
   */
  virtual void onPostUpdate( const float delta );

public:
  void render();

protected:
  /**
   * \brief Happen before scene, its objects and components were rendered
   */
  virtual void onPreRender();


  /**
   * \brief Happen after scene, its objects and components were rendered
   */
  virtual void onPostRender();

public:
  /**
   * \brief Release and destroy scene, this will not change running scene, you should not call this method directly
   */
  void release() override;

  void releaseInNextFrame();

protected:

  /**
   * \brief Happen before scene, its objects and components were released
   */
  virtual void onPreRelease();


  /**
   * \brief Happen after scene, its objects and components were released and destroyed
   */
  virtual void onPostRelease();

public:
  void resolveLockedTasks();

  virtual void onResolveLockedTasks();

  // ==================================================
  // Objects Management
  // ==================================================
private:
  std::unordered_map<long, GameObject*> _gameObjects;
  bool _gameObjectInLock;
  std::vector<std::pair<GameObject*, std::string>> _gameObjectsToAddInNextFrame;
  std::vector<long> _gameObjectsToRemoveInNextFrame;

  QuadTree* _quadTree;
  std::unordered_map<long, GameObject*> _dynamicGameObjects;
  std::unordered_map<long, std::string> _gameObjectToQuadNode;

public:
  GameObject* getGameObject( const long id ) const;

  GameObject* getMainCamera() const;

  /**
   * \brief Attach game object to scene, this will not change game object's parent, you should not call this method directly
   * \param gameObject Game object to attach
   */
  void addGameObject( GameObject* gameObject, const std::string& quadIndex = "" );

  void addGameObjectInNextFrame( GameObject* gameObject, const std::string& quadIndex = "" );

  /**
   * \brief Detach game object from scene, this will not change game object's parent or release it, you should not call this method directly
   * \param gameObject Game object to detach
   */
  void removeGameObject( GameObject* gameObject );

  void removeGameObjectInNextFrame( GameObject* gameObject );

  void enableQuadTree( const float spaceMinX, const float spaceMinY,
                       const float spaceMaxX, const float spaceMaxY,
                       const int level = 3 );

  QuadTree* getQuadTree() const;

  bool isQuadTreeEnabled() const;

private:
  void updateQuadTreeVisibility() const;

  void lockGameObjects();

  void unlockGameObjects();

  void updateAddAndRemoveGameObjects();

  void doAddGameObject( GameObject* gameObject, const std::string& quadIndex = "" );

  void doRemoveGameObject( const long id );

  // ================================================
  // Physics
  // ================================================
private:
  bool _physicsEnabled;
  Vec2 _gravityAcceleration;

public:
  const Vec2& getGravityAcceleration() const;

  void enablePhysics( const Vec2& gravity );

  bool isPhysicsEnabled() const;

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_SCENES_CREATED;
  static long TOTAL_SCENES_DELETED;
};
}

#endif //!__ALADDIN_CORE_SCENE_H__
