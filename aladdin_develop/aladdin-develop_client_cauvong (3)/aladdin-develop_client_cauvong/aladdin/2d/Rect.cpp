/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Rect )

Rect::Rect( const Vec2& topLeft, const Size& size ): _topLeft( topLeft ),
                                                     _size( size ) {}

Rect::Rect ( const Vec2& center, float width, float height )
  : _size(width, height)
{
  _topLeft = center + Vec2(-width/2, height/2);
}

Rect::~Rect() {}

const Vec2& Rect::getTopLeft() const {
  return _topLeft;
}

void Rect::setTopLeft( const Vec2& topLeft ) {
  _topLeft = topLeft;
}

const Size& Rect::getSize() const {
  return _size;
}

void Rect::setSize( const Size& size ) {
  _size = size;
}

float Rect::getMinX ( ) const
{
  return _topLeft.getX (  );
}

float Rect::getMidX ( ) const
{
  return _topLeft.getX() + _size.getWidth() / 2;
}

float Rect::getMaxX ( ) const
{
  return _topLeft.getX() + _size.getWidth();
}

float Rect::getMinY ( ) const
{
  return _topLeft.getY();
}

float Rect::getMidY ( ) const
{
  return _topLeft.getY() + _size.getHeight() / 2;
}

float Rect::getMaxY ( ) const
{
  return _topLeft.getY() + _size.getHeight();
}

bool Rect::equals ( const Rect& rect ) const
{
  return _topLeft == rect.getTopLeft() && _size.getWidth() == rect._size.getWidth() && _size.getHeight() == rect._size.getHeight();
}

bool Rect::containsPoint ( const Vec2& point ) const
{
  bool bRet = false;

  if (point.getX (  ) >= getMinX() && point.getX (  ) <= getMaxX()
    && point.getY (  ) >= getMinY() && point.getY (  ) <= getMaxY())
  {
    bRet = true;
  }

  return bRet;
}

bool Rect::intersectsRect ( const Rect& rect ) const
{
  return !(getMaxX() < rect.getMinX() ||
    rect.getMaxX() <      getMinX() ||
    getMaxY() < rect.getMinY() ||
    rect.getMaxY() <      getMinY());
}

  bool Rect::operator== ( const Rect& rect ) const
  {
    return equals(rect);
  }
}
