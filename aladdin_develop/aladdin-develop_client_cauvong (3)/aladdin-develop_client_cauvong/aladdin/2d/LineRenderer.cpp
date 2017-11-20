#include "LineRenderer.h"
#include "../2d/Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::LineRenderer, ala::GameObjectComponent )

LineRenderer::LineRenderer( GameObject* gameObject,
                            const std::vector<ala::Vec2>& vertices,
                            const ala::Color& color,
                            const std::string& name )
  : GameObjectComponent( gameObject, name ), _vertices( vertices ), _color( color ), _zOrder( 0 ) {}

const std::vector<Vec2>& LineRenderer::getVertices() const {
  return _vertices;
}

void LineRenderer::addVertex( const ala::Vec2& vec ) {
  _vertices.push_back( vec );
}

void LineRenderer::addVertices( const std::vector<ala::Vec2>& vertices ) {
  for ( const auto& vec : vertices ) _vertices.push_back( vec );
}

void LineRenderer::setVertices( const std::vector<ala::Vec2>& vertices ) {
  _vertices = vertices;
}

void LineRenderer::setColor( const ala::Color& color ) {
  _color = color;
}

const ala::Color& LineRenderer::getColor() const {
  return _color;
}

void LineRenderer::setZOrder( const int zOrder ) {
  if ( zOrder < 0 ) _zOrder = 0;
  else if ( zOrder > ALA_MAX_Z_ORDER ) _zOrder = ALA_MAX_Z_ORDER;
  else _zOrder = zOrder;
}

int LineRenderer::getZOrder() const {
  return _zOrder;
}

void LineRenderer::onRender() {
  auto transform = getGameObject()->getTransform();
  auto worldZOrder = calculateWorldZOrder();

  // TODO: draw with transform
  Graphics::get()->drawLine( _vertices, getGameObject()->getTransform()->getLocalToWorldMatrix()* GameManager::get()->getRunningScene()->getMainCamera()->getTransform()->getLocalToWorldMatrix(), _color, worldZOrder );
}

int LineRenderer::calculateWorldZOrder() const {
  int layerIndex = GameManager::get()->getLayerIndex( getGameObject()->getLayer() );
  int worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
}
