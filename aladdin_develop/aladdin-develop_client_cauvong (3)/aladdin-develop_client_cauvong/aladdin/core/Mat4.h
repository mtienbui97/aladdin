#ifndef __ALADDIN_CORE_MAT4_H__
#define __ALADDIN_CORE_MAT4_H__

#include "ClassMeta.h"
#include "Vec2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Mat4)
private:
  float _11, _12, _13, _14;
  float _21, _22, _23, _24;
  float _31, _32, _33, _34;
  float _41, _42, _43, _44;
public:
  Mat4();

  virtual ~Mat4();

  void operator +=( const Mat4& mat );
  void operator -=( const Mat4& mat );
  void operator *=( const float v );
  void operator /=( const float v );
  Mat4 operator -() const;
  Mat4 operator +( const Mat4& mat ) const;
  Mat4 operator -( const Mat4& mat ) const;
  Mat4 operator *( const Mat4& mat ) const;
  Mat4 operator *( const float v ) const;
  Mat4 operator /( const float v ) const;

  static Mat4 getEmptyMat();
  static Mat4 getIdentityMat();

  float getDet() const;
  float getTrace() const;
  Mat4 getTranspose() const;
  Mat4 getInverse() const;

  float get11() const;
  float get12() const;
  float get13() const;
  float get14() const;
  float get21() const;
  float get22() const;
  float get23() const;
  float get24() const;
  float get31() const;
  float get32() const;
  float get33() const;
  float get34() const;
  float get41() const;
  float get42() const;
  float get43() const;
  float get44() const;
  void set11( const float x );
  void set12( const float x );
  void set13( const float x );
  void set14( const float x );
  void set21( const float x );
  void set22( const float x );
  void set23( const float x );
  void set24( const float x );
  void set31( const float x );
  void set32( const float x );
  void set33( const float x );
  void set34( const float x );
  void set41( const float x );
  void set42( const float x );
  void set43( const float x );
  void set44( const float x );

  static Mat4 getRotationXMatrix( const float angle );
  static Mat4 getRotationYMatrix( const float angle );
  static Mat4 getRotationZMatrix( const float angle );

  static Mat4 getTranslationMatrix( const Vec2& translation );
  static Mat4 getTranslationMatrix( const float x, const float y, const float z );

  static Mat4 getScalingMatrix( const Vec2& scale );
  static Mat4 getScalingMatrix( const float x, const float y, const float z );

  static Mat4 getOrthoLHMatrix(float width, float height, float zn, float zf);
  static Mat4 getOrthoRHMatrix(float width, float height, float zn, float zf);
};
}

#endif //!__ALADDIN_CORE_MAT4_H__
