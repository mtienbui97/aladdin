/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_PREFAB_H__
#define __ALADDIN_CORE_PREFAB_H__

#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Prefab, ala::Releasable)
private:
  std::string _name;

public:
  Prefab( const std::string& name );

  virtual ~Prefab();

  const std::string& getName() const;

  GameObject* instantiate( const std::string& name = "", const std::string& quadIndex = "" ) const;

  GameObject* instantiate( const Vec2& position,
                           const std::string& name = "",
                           const std::string& quadIndex = "" ) const;

  GameObject* instantiate( const Vec2& position, const Vec2& scale,
                           const std::string& name = "",
                           const std::string& quadIndex = "" ) const;

  GameObject* instantiate( const Vec2& position, const Vec2& scale, const float rotation,
                           const std::string& name = "",
                           const std::string& quadIndex = "" ) const;

  GameObject* instantiate( Scene* scene, const std::string& name = "", const std::string& quadIndex = "" ) const;

  GameObject* instantiate( Scene* scene, const Vec2& position, const std::string& name = "",
                           const std::string& quadIndex = "" ) const;

  GameObject* instantiate( Scene* scene, const Vec2& position, const Vec2& scale, const std::string& name = "",
                           const std::string& quadIndex = "" ) const;

  GameObject* instantiate( Scene* scene, const Vec2& position, const Vec2& scale, const float rotation,
                           const std::string& name = "",
                           const std::string& quadIndex = "" ) const;

  GameObject* instantiate( GameObject* parentObject, const std::string& name = "" ) const;

  GameObject* instantiate( GameObject* parentObject, const Vec2& position, const std::string& name = "" ) const;

  GameObject* instantiate( GameObject* parentObject, const Vec2& position, const Vec2& scale,
                           const std::string& name = "" ) const;

  GameObject* instantiate( GameObject* parentObject, const Vec2& position, const Vec2& scale, const float rotation,
                           const std::string& name = "" ) const;

protected:
  virtual void doInstantiate( GameObject* object ) const = 0;

public:
  void release() override;

protected:
  virtual void onRelease();

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_PREFABS_CREATED;
  static long TOTAL_PREFABS_DELETED;
};
}

#endif //!__ALADDIN_CORE_PREFAB_H__
