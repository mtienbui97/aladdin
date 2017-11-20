/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "SpriteRenderer.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::SpriteRenderer, ala::GameObjectComponent )

SpriteRenderer::SpriteRenderer( GameObject* gameObject, Sprite* sprite, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _sprite( sprite ),
    _backColor( 255, 255, 255 ),
    _zOrder( 0 ),
    _offset(0, 0),
    _visible( true ) {
  _srcRect.setTopLeft(Vec2(0.f, 0.f));
  _srcRect.setSize(_sprite->getContentSize());
}

SpriteRenderer::SpriteRenderer( GameObject* gameObject, const std::string& spriteResourceName, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _sprite( NULL ),
    _backColor( 255, 255, 255 ),
    _zOrder( 0 ),
    _offset(0, 0),
    _visible(true) {
  _sprite = static_cast<Sprite*>(GameManager::get()->getResource( spriteResourceName ));

  _srcRect.setTopLeft(Vec2(0.f, 0.f));
  _srcRect.setSize(_sprite->getContentSize());
}

SpriteRenderer::~SpriteRenderer() {}

Sprite* SpriteRenderer::getSprite() const {
  return _sprite;
}

void SpriteRenderer::setSprite( Sprite* sprite ) {
  _sprite = sprite;

  _srcRect.setTopLeft(Vec2(0.f, 0.f));
  _srcRect.setSize(_sprite->getContentSize());
}

const Color& SpriteRenderer::getBackColor() const {
  return _backColor;
}

void SpriteRenderer::setBackColor( const Color& color ) {
  _backColor = color;
}

Size SpriteRenderer::getFrameSize() const {
  const auto transform = getGameObject()->getTransform();

  return Size(_srcRect.getSize().getWidth() * transform->getScale().getX(), 
    _srcRect.getSize().getHeight() * transform->getScale().getY());
}

void SpriteRenderer::setZOrder( const int zOrder ) {
  if (zOrder < 0) _zOrder = 0;
  else if (zOrder > ALA_MAX_Z_ORDER) _zOrder = ALA_MAX_Z_ORDER;
  else _zOrder = zOrder;
}

int SpriteRenderer::getZOrder() const {
  return _zOrder;
}

const Rect& SpriteRenderer::getSourceRect ( ) const
{
  return _srcRect;
}

void SpriteRenderer::setSourceRect ( const Rect& rect )
{
  _srcRect = rect;
}

const Vec2& SpriteRenderer::getOffset() const { return _offset; }

void SpriteRenderer::setOffset( const Vec2& offset ) { _offset = offset; }
bool SpriteRenderer::isVisible() const { return _visible; }
void SpriteRenderer::setVisible( const bool visible ) { _visible = visible; }

void SpriteRenderer::onInitialize ( )
{
}

void SpriteRenderer::onRender() {
  if (!_visible) return;

  const auto transform = getGameObject()->getTransform();
  const auto worldZOrder = calculateWorldZOrder();

  const auto oldPosition = transform->getPosition();
  transform->setPositionX(transform->getPositionX() + _offset.getX()*transform->getScale().getX());
  transform->setPositionY(transform->getPositionY() + _offset.getY()*transform->getScale().getY());
  Graphics::get()->drawSprite( _sprite, Vec2(0.5f, 0.5f), transform->getLocalToWorldMatrix(), _backColor, _srcRect, worldZOrder);
  transform->setPosition( oldPosition );
}

void SpriteRenderer::onRelease ( )
{
}

int SpriteRenderer::calculateWorldZOrder() const {
  const auto layerIndex = GameManager::get()->getLayerIndex(getGameObject()->getLayer());
  const auto worldZOrder = layerIndex * 1000 + _zOrder;
  return worldZOrder;
}
}
