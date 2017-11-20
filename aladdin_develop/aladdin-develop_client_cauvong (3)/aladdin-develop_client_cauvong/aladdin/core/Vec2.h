/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_VEC2_H__
#define __ALADDIN_CORE_VEC2_H__

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Vec2)
private:
  float _x;
  float _y;

public:
  Vec2( const float x = 0, const float y = 0 );

  virtual ~Vec2();

  float getX() const;

  void setX( const float x );

  float getY() const;

  void setY( const float y );


  bool isZero() const;

  bool isOne() const;

  static float angle(const Vec2& v1, const Vec2& v2);

  void add(const Vec2& v);

  static void add(const Vec2& v1, const Vec2& v2, Vec2* dst);

  void clamp(const Vec2& min, const Vec2& max);

  static void clamp(const Vec2& v, const Vec2& min, const Vec2& max, Vec2* dst);

  float distance(const Vec2& v) const;

  float distanceSquared(const Vec2& v) const;

  float dot(const Vec2& v) const;

  static float dot(const Vec2& v1, const Vec2& v2);

  float length() const;

  float lengthSquared() const;

  void negate();

  void normalize();

  Vec2 getNormalized() const;

  void scale(float scalar);

  void scale(const Vec2& scale);

  void rotate(const Vec2& point, float angle);

  void setZero();

  void subtract(const Vec2& v);

  void subtract(const Vec2& v1, const Vec2& v2, Vec2* dst);

  void smooth(const Vec2& target, float elapsedTime, float responseTime);

  Vec2 operator+(const Vec2& v) const;

  Vec2& operator+=(const Vec2& v);

  Vec2 operator-(const Vec2& v) const;

  Vec2& operator-=(const Vec2& v);

  Vec2 operator-() const;

  Vec2 operator*(float s) const;

  Vec2& operator*=(float s);

  Vec2 operator/(float s) const;

  bool operator<(const Vec2& v) const;

  bool operator>(const Vec2& v) const;

  bool operator==(const Vec2& v) const;

  bool operator!=(const Vec2& v) const;

  void setPoint(const float x, const float y);

  float getLength() const;

  float getLengthSq() const;

  float getDistanceSq(const Vec2& other) const;

  float getDistance(const Vec2& other) const;

  float getAngle() const;

  float getAngle(const Vec2& other) const;

  float cross(const Vec2& other) const;

  Vec2 getMidpoint(const Vec2& other) const;

  Vec2 rotate(const Vec2& other) const;

  Vec2 unrotate(const Vec2& other) const;

  Vec2 lerp(const Vec2& other, float alpha) const;

  Vec2 rotateByAngle(const Vec2& pivot, float angle) const;

  static Vec2 forAngle(const float a);

  // TODO: Why don't you use static constants instead?

  /** equals to Vec2(0,0) */
  static Vec2 getZeroVector();
  /** equals to Vec2(1,1) */
  static Vec2 getIdentityVector();
  /** equals to Vec2(1,0) */
  static Vec2 getUnitXVector();
  /** equals to Vec2(0,1) */
  static Vec2 getUnitYVector();
  /** equals to Vec2(0.5, 0.5) */
  static Vec2 getAnchorMiddle();
  /** equals to Vec2(0, 0) */
  static Vec2 getAnchorBottomLeft();
  /** equals to Vec2(0, 1) */
  static Vec2 getAnchorTopLeft();
  /** equals to Vec2(1, 0) */
  static Vec2 getAnchorBottomRight();
  /** equals to Vec2(1, 1) */
  static Vec2 getAnchorTopRight();
  /** equals to Vec2(1, 0.5) */
  static Vec2 getAnchorMiddleRight();
  /** equals to Vec2(0, 0.5) */
  static Vec2 getAnchorMiddleLeft();
  /** equals to Vec2(0.5, 1) */
  static Vec2 getAnchorMiddleTop();
  /** equals to Vec2(0.5, 0) */
  static Vec2 getAnchorMiddleBottom();
};

typedef Vec2 Point;
}

#endif //!__ALADDIN_CORE_VEC2_H__
