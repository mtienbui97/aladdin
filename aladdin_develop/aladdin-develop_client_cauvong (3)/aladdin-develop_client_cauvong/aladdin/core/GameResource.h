#ifndef __ALADDIN_CORE_GAME_RESOURCE_H__
#define __ALADDIN_CORE_GAME_RESOURCE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Scene.h"
#include "Loadable.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(GameResource, ala::Loadable, ala::Releasable)
private:
  std::string _name;
  Scene* _sceneScope;

public:
  GameResource( const std::string& name, Scene* sceneScope = NULL );

  virtual ~GameResource();

  const std::string& getName() const;

  void load() override;

  void release() override;

  void setGameScope();

  void setSceneScope( Scene* sceneScope );

  Scene* getSceneScope() const;

  bool isGameScope() const;

  virtual bool isShared() const;

  virtual GameResource* clone();

protected:
  virtual void onLoad() = 0;

  virtual void onRelease() = 0;

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_RESOURCES_CREATED;
  static long TOTAL_RESOURCES_DELETED;
};
}

#endif //!__ALADDIN_CORE_GAME_RESOURCE_H__
