/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Color.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Color )

Color::Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a ): _r( r ),
                                                                                    _g( g ),
                                                                                    _b( b ),
                                                                                    _a( a ) {}

Color::~Color() {}

unsigned char Color::getR() const {
  return _r;
}

void Color::setR( unsigned char r ) {
  _r = r;
}

unsigned char Color::getG() const {
  return _g;
}

void Color::setG( unsigned char g ) {
  _g = g;
}

unsigned char Color::getB() const {
  return _b;
}

void Color::setB( unsigned char b ) {
  _b = b;
}

unsigned char Color::getA() const {
  return _a;
}

void Color::setA( unsigned char a ) {
  _a = a;
}
}
