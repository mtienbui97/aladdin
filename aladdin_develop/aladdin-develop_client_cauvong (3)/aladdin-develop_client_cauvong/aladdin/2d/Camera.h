#ifndef __ALADDIN_2D_CAMERA_H__
#define __ALADDIN_2D_CAMERA_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( Camera, ala::GameObjectComponent )

private:
  float _width;
  float _height;
  Vec2 _scaleFactor;

  Mat4 _orthographicMatrix;
  Mat4 _viewMatrix;

public:
  Camera( GameObject* gameObject, const std::string& name );
  Camera( GameObject* gameObject, const std::string& name,
          const float width,
          const float height,
          const Vec2& scaleFactor );

  virtual ~Camera();


protected:
  void onUpdate( float dt ) override;
};
}

#endif //!__ALADDIN_2D_CAMERA_H__
