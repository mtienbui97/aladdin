/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Size.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Size )

Size::Size( const float x, const float y ) : _width( x ),
                                             _height( y ) {}

Size::~Size() {}

float Size::getWidth() const {
  return _width;
}

void Size::setWidth( const float width ) {
  _width = width;
}

float Size::getHeight() const {
  return _height;
}

void Size::setHeight( const float height ) {
  _height = height;
}

float Size::getArea() const
{
	return _height*_width;
}

bool Size::operator==( const Size& s ) const {
  return _width == s._width && s._height == _height;
}

bool Size::operator!=( const Size& s ) const {
  return !operator==( s );
}
}
