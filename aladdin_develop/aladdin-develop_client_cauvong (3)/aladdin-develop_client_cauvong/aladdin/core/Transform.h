/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_TRANSFORM2_H__
#define __ALADDIN_CORE_TRANSFORM2_H__

#include "GameObjectComponent.h"
#include "Vec2.h"
#include "Mat4.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Transform, ala::GameObjectComponent)

  // ===================================================
  // Basic
  // ===================================================
private:
  Vec2 _position;
  Vec2 _scale;
  float _rotation;
  Vec2 _origin;
public:
  Transform( GameObject* gameObject, Transform* parentTransform = NULL, const std::string& name = "" );

  virtual ~Transform();

  const Vec2& getPosition() const;

  float getPositionX() const;

  float getPositionY() const;

  Transform* setPosition( const Vec2& position );

  Transform* setPosition( const float x, const float y );

  Transform* setPositionX( const float x );

  Transform* setPositionY( const float y );

  const Vec2& getScale() const;

  Transform* setScale( const Vec2& scale );

  Transform* setScaleX( const float x );

  Transform* setScaleY( const float y );

  Transform* setScale( const float scale );

  float getRotation() const;

  Transform* setRotation( const float rotation );

  Vec2 getWorldPosition();

  // =======================================================
  // Children management
  // =======================================================

private:
  bool _childrenInLock;
  std::vector<Transform*> _children;
  Transform* _parent;
  std::vector<Transform*> _childrenToAddInNextFrame;
  std::vector<Transform*> _childrenToRemoveInNextFrame;

public:
  std::vector<Transform*> getChildren() const;

  Transform* getChild( const int index ) const;

  Transform* getParent() const;

  /**
   * \brief Attach a transform as child of this transform, this will not remove child from old parent and change its parent, you should not call this method directly
   * \param child Child transform to attach
   */
  void addChild( Transform* child );

  void addChildInNextFrame( Transform* child );

  /**
   * \brief Detach a transform from this children, this will not reset child parent or object, you should not call this method directly
   * \param child Child transform to detach
   */
  void removeChild( Transform* child );

  void removeChildInNextFrame( Transform* child );

private:
  void lockChildren();

  void unlockChildren();

  void updateAddAndRemoveChildInNextFrame();

  void doAddChild( Transform* child );

  void doRemoveChild( Transform* child );

protected:
  bool onPreRelease() override;

  void onRelease() override;

  void onResolvedLockedTasks() override;

  void onUpdate( const float delta ) override;

  void onRender() override;

  // =====================================================
  // Transformation
  // =====================================================
public:
  Mat4 calculateLocalToParentMatrix() const;

  Mat4 getLocalToWorldMatrix();

  Mat4 getWorldToLocalMatrix();
private:
  // specifies if the localToWorldTransform
  // needs to be recalulated
  bool _dirty;
  // the transform that converts local coordinates
  // to world coordinates
  Mat4 _localToWorldMatrix;
  // specifies if the worldToLocalMatrix
  // needs to be recalculated
  bool _inverseDirty;
  // the transform that converts world cooridnates
  // to local coordinates
  Mat4 _worldToLocalMatrix;

  void setDirty();
};
}

#endif //!__ALADDIN_CORE_TRANSFORM2_H__
