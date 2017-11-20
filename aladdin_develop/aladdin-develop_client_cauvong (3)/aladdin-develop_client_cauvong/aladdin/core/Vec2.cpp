/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Vec2 )

Vec2::Vec2( const float x, const float y ): _x( x ),
                                            _y( y ) {}

Vec2::~Vec2() {}

float Vec2::getX() const {
  return _x;
}

void Vec2::setX( const float x ) {
  _x = x;
}

float Vec2::getY() const {
  return _y;
}

void Vec2::setY( const float y ) {
  _y = y;
}

bool Vec2::isZero() const {
  return _x == 0.0f && _y == 0.0f;
}

bool Vec2::isOne() const {
  return _x == 1.0f && _y == 1.0f;
}

float Vec2::angle( const Vec2& v1, const Vec2& v2 ) {
  float dz = v1._x * v2._y - v1._y * v2._x;
  return atan2f( fabsf( dz ) + 1.0e-37f, dot( v1, v2 ) );

}

void Vec2::add( const Vec2& v ) {
  _x += v._x;
  _y += v._y;
}

void Vec2::add( const Vec2& v1, const Vec2& v2, Vec2* dst ) {
  dst->_x = v1._x + v2._x;
  dst->_y = v1._y + v2._y;
}

void Vec2::clamp( const Vec2& min, const Vec2& max ) {
  // Clamp the x value.
  if ( _x < min._x )
    _x = min._x;
  if ( _x > max._x )
    _x = max._x;

  // Clamp the y value.
  if ( _y < min._y )
    _y = min._y;
  if ( _y > max._y )
    _y = max._y;
}

void Vec2::clamp( const Vec2& v, const Vec2& min, const Vec2& max, Vec2* dst ) {
  // Clamp the x value.
  dst->_x = v._x;
  if ( dst->_x < min._x )
    dst->_x = min._x;
  if ( dst->_x > max._x )
    dst->_x = max._x;

  // Clamp the y value.
  dst->_y = v._y;
  if ( dst->_y < min._y )
    dst->_y = min._y;
  if ( dst->_y > max._y )
    dst->_y = max._y;
}

float Vec2::distance( const Vec2& v ) const {
  float dx = v._x - _x;
  float dy = v._y - _y;

  return std::sqrt( dx * dx + dy * dy );
}

float Vec2::distanceSquared( const Vec2& v ) const {
  float dx = v._x - _x;
  float dy = v._y - _y;
  return (dx * dx + dy * dy);
}

float Vec2::dot( const Vec2& v ) const {
  return (_x * v._x + _y * v._y);
}

float Vec2::dot( const Vec2& v1, const Vec2& v2 ) {
  return (v1._x * v2._x + v1._y * v2._y);
}

float Vec2::length() const {
  return std::sqrt( _x * _x + _y * _y );
}

float Vec2::lengthSquared() const {
  return (_x * _x + _y * _y);
}

void Vec2::negate() {
  _x = -_x;
  _y = -_y;
}

void Vec2::normalize() {
  float n = _x * _x + _y * _y;
  // Already normalized.
  if ( n == 1.0f )
    return;

  n = std::sqrt( n );

  if ( n == 0 ) {
    return;
  }

  n = 1.0f / n;
  _x *= n;
  _y *= n;
}

Vec2 Vec2::getNormalized() const {
  Vec2 v( *this );
  v.normalize();
  return v;
}

void Vec2::scale( float scalar ) {
  _x *= scalar;
  _y *= scalar;
}

void Vec2::scale( const Vec2& scale ) {
  _x *= scale._x;
  _y *= scale._y;
}

void Vec2::rotate( const Vec2& point, float angle ) {
  float sinAngle = std::sin( angle );
  float cosAngle = std::cos( angle );

  if ( point.isZero() ) {
    float tempX = _x * cosAngle - _y * sinAngle;
    _y = _y * cosAngle + _x * sinAngle;
    _x = tempX;
  }
  else {
    float tempX = _x - point._x;
    float tempY = _y - point._y;

    _x = tempX * cosAngle - tempY * sinAngle + point._x;
    _y = tempY * cosAngle + tempX * sinAngle + point._y;
  }
}

void Vec2::setZero() {
  _x = _y = 0.0f;
}

void Vec2::subtract( const Vec2& v ) {
  _x -= v._x;
  _y -= v._y;
}

void Vec2::subtract( const Vec2& v1, const Vec2& v2, Vec2* dst ) {
  dst->_x = v1._x - v2._x;
  dst->_y = v1._y - v2._y;
}

void Vec2::smooth( const Vec2& target, float elapsedTime, float responseTime ) {
  if ( elapsedTime > 0 ) {
    *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
  }
}

Vec2 Vec2::operator+( const Vec2& v ) const {
  Vec2 result( *this );
  result.add( v );
  return result;
}

Vec2& Vec2::operator+=( const Vec2& v ) {
  add( v );
  return *this;
}

Vec2 Vec2::operator-( const Vec2& v ) const {
  Vec2 result( *this );
  result.subtract( v );
  return result;
}

Vec2& Vec2::operator-=( const Vec2& v ) {
  subtract( v );
  return *this;
}

Vec2 Vec2::operator-() const {
  Vec2 result( *this );
  result.negate();
  return result;
}

Vec2 Vec2::operator*( float s ) const {
  Vec2 result( *this );
  result.scale( s );
  return result;
}

Vec2& Vec2::operator*=( float s ) {
  scale( s );
  return *this;
}

Vec2 Vec2::operator/( float s ) const {
  return Vec2( this->_x / s, this->_y / s );
}

bool Vec2::operator<( const Vec2& v ) const {
  if ( _x == v._x ) {
    return _y < v._y;
  }
  return _x < v._x;
}

bool Vec2::operator>( const Vec2& v ) const {
  if ( _x == v._x ) {
    return _y > v._y;
  }
  return _x > v._x;
}

bool Vec2::operator==( const Vec2& v ) const {
  return _x == v._x && _y == v._y;

}

bool Vec2::operator!=( const Vec2& v ) const {
  return _x != v._x || _y != v._y;
}

void Vec2::setPoint( const float x, const float y ) {
  this->_x = x;
  this->_y = y;
}

float Vec2::getLength() const {
  return sqrtf( _x * _x + _y * _y );
}

float Vec2::getLengthSq() const {
  return dot( *this ); //x*x + y*y;
}

float Vec2::getDistanceSq( const Vec2& other ) const {
  return (*this - other).getLengthSq();
}

float Vec2::getDistance( const Vec2& other ) const {
  return (*this - other).getLength();
}

float Vec2::getAngle() const {
  return atan2f( _y, _x );
}

float Vec2::getAngle( const Vec2& other ) const {
  Vec2 a2 = getNormalized();
  Vec2 b2 = other.getNormalized();
  float angle = atan2f( a2.cross( b2 ), a2.dot( b2 ) );
  if ( std::abs( angle ) < FLT_EPSILON ) return 0.f;
  return angle;
}

float Vec2::cross( const Vec2& other ) const {
  return _x * other._y - _y * other._x;
}

Vec2 Vec2::getMidpoint( const Vec2& other ) const {
  return Vec2( (_x + other._x) / 2.0f, (_y + other._y) / 2.0f );
}

Vec2 Vec2::rotate( const Vec2& other ) const {
  return Vec2( _x * other._x - _y * other._y, _x * other._y + _y * other._x );
}

Vec2 Vec2::unrotate( const Vec2& other ) const {
  return Vec2( _x * other._x + _y * other._y, _y * other._x - _x * other._y );
}

Vec2 Vec2::lerp( const Vec2& other, float alpha ) const {
  return *this * (1.f - alpha) + other * alpha;
}

Vec2 Vec2::rotateByAngle( const Vec2& pivot, float angle ) const {
  return pivot + (*this - pivot).rotate( Vec2::forAngle( angle ) );
}

Vec2 Vec2::forAngle( const float a ) {
  return Vec2( cosf( a ), sinf( a ) );
}

Vec2 Vec2::getZeroVector() {
  return Vec2( 0, 0 );
}

Vec2 Vec2::getIdentityVector() {
  return Vec2( 1, 1 );
}

Vec2 Vec2::getUnitXVector() {
  return Vec2( 1, 0 );
}

Vec2 Vec2::getUnitYVector() {
  return Vec2( 0, 1 );
}

Vec2 Vec2::getAnchorMiddle() {
  return Vec2( 0.5f, 0.5f );
}

Vec2 Vec2::getAnchorBottomLeft() {
  return Vec2( 0, 0 );
}

Vec2 Vec2::getAnchorTopLeft() {
  return Vec2( 0, 1 );
}

Vec2 Vec2::getAnchorBottomRight() {
  return Vec2( 1, 0 );
}

Vec2 Vec2::getAnchorTopRight() {
  return Vec2( 1, 1 );
}

Vec2 Vec2::getAnchorMiddleRight() {
  return Vec2( 1, 0.5f );
}

Vec2 Vec2::getAnchorMiddleLeft() {
  return Vec2( 0, 0.5f );
}

Vec2 Vec2::getAnchorMiddleTop() {
  return Vec2( 0.5f, 1 );
}

Vec2 Vec2::getAnchorMiddleBottom() {
  return Vec2( 0.5f, 0 );
}
}
