/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Sprite.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Sprite, ala::GameResource)

Sprite::Sprite( const std::string& name, const std::string& sourceFile, const ala::Color& transColor, Scene* scope )
  : GameResource( name, scope ),
    _sourceFile( sourceFile ),
    _contentSize( 0, 0 ),
    _transColor( transColor ),
    _directXTexture( 0 ) {}

Sprite::~Sprite() {}

const std::string& Sprite::getSourceFile() const {
  return _sourceFile;
}

const ala::Color& Sprite::getTransColor() const {
  return _transColor;
}

const ala::Size& Sprite::getContentSize() const {
  return _contentSize;
}

void Sprite::setContentSize( const Size& size ) {
  _contentSize = size;
}

void Sprite::onLoad() {
  Graphics::get()->loadSprite( this );
  ALA_ASSERT( _directXTexture != 0);
}

void Sprite::onRelease() {
  if ( _directXTexture ) {
    _directXTexture->Release();
  }
}

void Sprite::setDirectXTexture( LPDIRECT3DTEXTURE9 directXTexture ) {
  _directXTexture = directXTexture;
}

LPDIRECT3DTEXTURE9 Sprite::getDirectXTexture() {
  return _directXTexture;
}
}
