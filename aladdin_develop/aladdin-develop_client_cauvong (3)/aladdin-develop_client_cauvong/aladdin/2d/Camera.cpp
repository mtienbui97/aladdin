#include "Camera.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( ala::Camera, ala::GameObjectComponent )

Camera::Camera( GameObject* gameObject, const std::string& name ) :
  GameObjectComponent( gameObject, name ),
  _width( 0 ),
  _height( 0 ),
  _scaleFactor( Vec2( 1.0f, 1.0f ) ) {
  _orthographicMatrix = Mat4::getOrthoLHMatrix( _width, _height, ALA_CAMERA_MIN_Z, ALA_CAMERA_MAX_Z);
}

Camera::Camera( GameObject* gameObject, const std::string& name,
                const float width,
                const float height,
                const Vec2& scaleFactor ) :
  GameObjectComponent( gameObject, name ),
  _width( width ),
  _height( height ),
  _scaleFactor( scaleFactor ) {
  _orthographicMatrix = Mat4::getOrthoLHMatrix( _width, _height, ALA_CAMERA_MIN_Z, ALA_CAMERA_MAX_Z);
}

Camera::~Camera() {}

void Camera::onUpdate( float dt ) {
  const auto radianAngle = DEGREE_TO_RADIAN(getGameObject()->getTransform()->getRotation());
  _viewMatrix = Mat4::getIdentityMat();
  _viewMatrix.set11( _scaleFactor.getX() * cosf(radianAngle) );
  _viewMatrix.set12( _scaleFactor.getX() * sinf(radianAngle) );

  _viewMatrix.set21( -_scaleFactor.getY() * sinf(radianAngle) );
  _viewMatrix.set22( _scaleFactor.getY() * cosf(radianAngle) );

  auto cameraPosition = getGameObject()->getTransform()->getPosition();

  _viewMatrix.set41( -cameraPosition.getX() * _scaleFactor.getX() * cosf(radianAngle) + cameraPosition.getY() * _scaleFactor.getY() * sinf(radianAngle) );

  _viewMatrix.set42( -cameraPosition.getX() * _scaleFactor.getX() * sinf(radianAngle) - cameraPosition.getY() * _scaleFactor.getY() * cosf(radianAngle) );

  auto graphics = Graphics::get();

  graphics->setProjectionMatrix( _orthographicMatrix );
  graphics->setWorldMatrix( Mat4::getIdentityMat() );
  graphics->setViewMatrix( _viewMatrix );
}
}
