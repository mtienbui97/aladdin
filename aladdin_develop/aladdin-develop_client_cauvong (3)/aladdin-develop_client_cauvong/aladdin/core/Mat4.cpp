#include "Mat4.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Mat4)


Mat4::Mat4()
  : _11( 0 ), _12( 0 ), _13( 0 ), _14( 0 ),
    _21( 0 ), _22( 0 ), _23( 0 ), _24( 0 ),
    _31( 0 ), _32( 0 ), _33( 0 ), _34( 0 ),
    _41( 0 ), _42( 0 ), _43( 0 ), _44( 0 ) { }

Mat4::~Mat4() { }

void Mat4::operator+=( const Mat4& mat ) {
  _11 += mat._11;
  _12 += mat._12;
  _13 += mat._13;
  _14 += mat._14;

  _21 += mat._21;
  _22 += mat._22;
  _23 += mat._23;
  _24 += mat._24;

  _31 += mat._31;
  _32 += mat._32;
  _33 += mat._33;
  _34 += mat._34;

  _41 += mat._41;
  _42 += mat._42;
  _43 += mat._43;
  _44 += mat._44;

}

void Mat4::operator-=( const Mat4& mat ) {
  _11 -= mat._11;
  _12 -= mat._12;
  _13 -= mat._13;
  _14 -= mat._14;

  _21 -= mat._21;
  _22 -= mat._22;
  _23 -= mat._23;
  _24 -= mat._24;

  _31 -= mat._31;
  _32 -= mat._32;
  _33 -= mat._33;
  _34 -= mat._34;

  _41 -= mat._41;
  _42 -= mat._42;
  _43 -= mat._43;
  _44 -= mat._44;

}

void Mat4::operator*=( const float v ) {
  _11 *= v;
  _12 *= v;
  _13 *= v;
  _14 *= v;

  _21 *= v;
  _22 *= v;
  _23 *= v;
  _24 *= v;

  _31 *= v;
  _32 *= v;
  _33 *= v;
  _34 *= v;

  _41 *= v;
  _42 *= v;
  _43 *= v;
  _44 *= v;

}

void Mat4::operator/=( const float v ) {
  _11 /= v;
  _12 /= v;
  _13 /= v;
  _14 /= v;

  _21 /= v;
  _22 /= v;
  _23 /= v;
  _24 /= v;

  _31 /= v;
  _32 /= v;
  _33 /= v;
  _34 /= v;

  _41 /= v;
  _42 /= v;
  _43 /= v;
  _44 /= v;

}

Mat4 Mat4::operator-() const {
  Mat4 result;

  result._11 = -_11;
  result._12 = -_12;
  result._13 = -_13;
  result._14 = -_14;

  result._21 = -_21;
  result._22 = -_22;
  result._23 = -_23;
  result._24 = -_24;

  result._31 = -_31;
  result._32 = -_32;
  result._33 = -_33;
  result._34 = -_34;

  result._41 = -_41;
  result._42 = -_42;
  result._43 = -_43;
  result._44 = -_44;

  return result;

}

Mat4 Mat4::operator+( const Mat4& mat ) const {
  Mat4 result;

  result._11 = _11 + mat._11;
  result._12 = _12 + mat._12;
  result._13 = _13 + mat._13;
  result._14 = _14 + mat._14;

  result._21 = _21 + mat._21;
  result._22 = _22 + mat._22;
  result._23 = _23 + mat._23;
  result._24 = _24 + mat._24;

  result._31 = _31 + mat._31;
  result._32 = _32 + mat._32;
  result._33 = _33 + mat._33;
  result._34 = _34 + mat._34;

  result._41 = _41 + mat._41;
  result._42 = _42 + mat._42;
  result._43 = _43 + mat._43;
  result._44 = _44 + mat._44;

  return result;

}

Mat4 Mat4::operator-( const Mat4& mat ) const {
  Mat4 result;

  result._11 = _11 - mat._11;
  result._12 = _12 - mat._12;
  result._13 = _13 - mat._13;
  result._14 = _14 - mat._14;

  result._21 = _21 - mat._21;
  result._22 = _22 - mat._22;
  result._23 = _23 - mat._23;
  result._24 = _24 - mat._24;

  result._31 = _31 - mat._31;
  result._32 = _32 - mat._32;
  result._33 = _33 - mat._33;
  result._34 = _34 - mat._34;

  result._41 = _41 - mat._41;
  result._42 = _42 - mat._42;
  result._43 = _43 - mat._43;
  result._44 = _44 - mat._44;

  return result;

}

Mat4 Mat4::operator*( const Mat4& mat ) const {
  Mat4 result;
  result._11 = this->_11 * mat._11 + this->_12 * mat._21 + this->_13 * mat._31 + this->_14 * mat._41;
  result._12 = this->_11 * mat._12 + this->_12 * mat._22 + this->_13 * mat._32 + this->_14 * mat._42;
  result._13 = this->_11 * mat._13 + this->_12 * mat._23 + this->_13 * mat._33 + this->_14 * mat._43;
  result._14 = this->_11 * mat._14 + this->_12 * mat._24 + this->_13 * mat._34 + this->_14 * mat._44;
  result._21 = this->_21 * mat._11 + this->_22 * mat._21 + this->_23 * mat._31 + this->_24 * mat._41;
  result._22 = this->_21 * mat._12 + this->_22 * mat._22 + this->_23 * mat._32 + this->_24 * mat._42;
  result._23 = this->_21 * mat._13 + this->_22 * mat._23 + this->_23 * mat._33 + this->_24 * mat._43;
  result._24 = this->_21 * mat._14 + this->_22 * mat._24 + this->_23 * mat._34 + this->_24 * mat._44;
  result._31 = this->_31 * mat._11 + this->_32 * mat._21 + this->_33 * mat._31 + this->_34 * mat._41;
  result._32 = this->_31 * mat._12 + this->_32 * mat._22 + this->_33 * mat._32 + this->_34 * mat._42;
  result._33 = this->_31 * mat._13 + this->_32 * mat._23 + this->_33 * mat._33 + this->_34 * mat._43;
  result._34 = this->_31 * mat._14 + this->_32 * mat._24 + this->_33 * mat._34 + this->_34 * mat._44;
  result._41 = this->_41 * mat._11 + this->_42 * mat._21 + this->_43 * mat._31 + this->_44 * mat._41;
  result._42 = this->_41 * mat._12 + this->_42 * mat._22 + this->_43 * mat._32 + this->_44 * mat._42;
  result._43 = this->_41 * mat._13 + this->_42 * mat._23 + this->_43 * mat._33 + this->_44 * mat._43;
  result._44 = this->_41 * mat._14 + this->_42 * mat._24 + this->_43 * mat._34 + this->_44 * mat._44;

  return result;
}

Mat4 Mat4::operator*( const float v ) const {
  Mat4 result;

  result._11 = _11 * v;
  result._12 = _12 * v;
  result._13 = _13 * v;
  result._14 = _14 * v;

  result._21 = _21 * v;
  result._22 = _22 * v;
  result._23 = _23 * v;
  result._24 = _24 * v;

  result._31 = _31 * v;
  result._32 = _32 * v;
  result._33 = _33 * v;
  result._34 = _34 * v;

  result._41 = _41 * v;
  result._42 = _42 * v;
  result._43 = _43 * v;
  result._44 = _44 * v;

  return result;
}

Mat4 Mat4::operator/( const float v ) const {
  Mat4 result;

  result._11 = _11 / v;
  result._12 = _12 / v;
  result._13 = _13 / v;
  result._14 = _14 / v;

  result._21 = _21 / v;
  result._22 = _22 / v;
  result._23 = _23 / v;
  result._24 = _24 / v;

  result._31 = _31 / v;
  result._32 = _32 / v;
  result._33 = _33 / v;
  result._34 = _34 / v;

  result._41 = _41 / v;
  result._42 = _42 / v;
  result._43 = _43 / v;
  result._44 = _44 / v;

  return result;

}

Mat4 Mat4::getEmptyMat() {
  Mat4 result;

  result._11 = 0.0f;
  result._12 = 0.0f;
  result._13 = 0.0f;
  result._14 = 0.0f;
  result._21 = 0.0f;
  result._22 = 0.0f;
  result._23 = 0.0f;
  result._24 = 0.0f;
  result._31 = 0.0f;
  result._32 = 0.0f;
  result._33 = 0.0f;
  result._34 = 0.0f;
  result._41 = 0.0f;
  result._42 = 0.0f;
  result._43 = 0.0f;
  result._44 = 0.0f;

  return result;
}

Mat4 Mat4::getIdentityMat() {
  Mat4 result;

  result._11 = 1.0f;
  result._12 = 0.0f;
  result._13 = 0.0f;
  result._14 = 0.0f;

  result._21 = 0.0f;
  result._22 = 1.0f;
  result._23 = 0.0f;
  result._24 = 0.0f;

  result._31 = 0.0f;
  result._32 = 0.0f;
  result._33 = 1.0f;
  result._34 = 0.0f;

  result._41 = 0.0f;
  result._42 = 0.0f;
  result._43 = 0.0f;
  result._44 = 1.0f;

  return result;

}

float Mat4::getDet() const {
  return _11 * _22 * _33 * _44 +
    _11 * _23 * _34 * _42 +
    _11 * _24 * _32 * _43 +
    _12 * _21 * _34 * _43 +
    _12 * _23 * _31 * _44 +
    _12 * _24 * _33 * _41 +
    _13 * _21 * _32 * _44 +
    _13 * _22 * _34 * _41 +
    _13 * _24 * _31 * _42 +
    _14 * _21 * _33 * _42 +
    _14 * _22 * _31 * _43 +
    _14 * _23 * _32 * _41 - (
      _11 * _22 * _34 * _44 +
      _11 * _23 * _32 * _44 +
      _11 * _24 * _33 * _42 +
      _12 * _21 * _33 * _44 +
      _12 * _23 * _34 * _41 +
      _12 * _24 * _32 * _41 +
      _13 * _21 * _34 * _42 +
      _13 * _22 * _31 * _44 +
      _13 * _24 * _32 * _41 +
      _14 * _21 * _32 * _43 +
      _14 * _22 * _33 * _41 +
      _14 * _23 * _31 * _42);
}

float Mat4::getTrace() const {
  return this->_11 + this->_22 + this->_33 + this->_44;
}

Mat4 Mat4::getTranspose() const {
  Mat4 result;
  result._11 = this->_11;
  result._12 = this->_21;
  result._13 = this->_31;
  result._14 = this->_41;

  result._21 = this->_12;
  result._22 = this->_22;
  result._23 = this->_32;
  result._24 = this->_42;

  result._31 = this->_13;
  result._32 = this->_23;
  result._33 = this->_33;
  result._34 = this->_43;

  result._41 = this->_14;
  result._42 = this->_24;
  result._43 = this->_34;
  result._44 = this->_44;

  return result;
}

Mat4 Mat4::getInverse() const {
  Mat4 I = getIdentityMat();

  Mat4 mat2 = (*this) * (*this);
  Mat4 mat3 = (*this) * (mat2);

  float trace1 = this->getTrace();
  float trace2 = mat2.getTrace();
  float trace3 = mat3.getTrace();

  float tmp1 = (trace1 * trace1 * trace1 - 3.0f * trace1 * trace2 + 2.0f * trace3) / 6.0f;
  float tmp2 = -(trace1 * trace1 - trace2) / 2.0f;

  Mat4 result = (I * tmp1 + (*this) * tmp2 + mat2 * trace1 - mat3) / getDet();

  return result;

}

float Mat4::get11() const {
  return _11;
}

float Mat4::get12() const {
  return _12;
}

float Mat4::get13() const {
  return _13;
}

float Mat4::get14() const {
  return _14;
}

float Mat4::get21() const {
  return _21;
}

float Mat4::get22() const {
  return _22;
}

float Mat4::get23() const {
  return _23;
}

float Mat4::get24() const {
  return _24;
}

float Mat4::get31() const {
  return _31;
}

float Mat4::get32() const {
  return _32;
}

float Mat4::get33() const {
  return _33;
}

float Mat4::get34() const {
  return _34;
}

float Mat4::get41() const {
  return _41;
}

float Mat4::get42() const {
  return _42;
}

float Mat4::get43() const {
  return _43;
}

float Mat4::get44() const {
  return _44;
}

void Mat4::set11( const float x ) {
  _11 = x;
}

void Mat4::set12( const float x ) {
  _12 = x;
}

void Mat4::set13( const float x ) {
  _13 = x;
}

void Mat4::set14( const float x ) {
  _14 = x;
}

void Mat4::set21( const float x ) {
  _21 = x;
}

void Mat4::set22( const float x ) {
  _22 = x;
}

void Mat4::set23( const float x ) {
  _23 = x;
}

void Mat4::set24( const float x ) {
  _24 = x;
}

void Mat4::set31( const float x ) {
  _31 = x;
}

void Mat4::set32( const float x ) {
  _32 = x;
}

void Mat4::set33( const float x ) {
  _33 = x;
}

void Mat4::set34( const float x ) {
  _34 = x;
}

void Mat4::set41( const float x ) {
  _41 = x;
}

void Mat4::set42( const float x ) {
  _42 = x;
}

void Mat4::set43( const float x ) {
  _43 = x;
}

void Mat4::set44( const float x ) {
  _44 = x;
}

Mat4 Mat4::getRotationXMatrix( const float angle ) {
  Mat4 result = getIdentityMat();
  float cosAng = cosf( angle );
  float sinAng = sinf( angle );

  result._22 = cosAng;
  result._33 = cosAng;
  result._23 = sinAng;
  result._32 = -sinAng;

  return result;

}

Mat4 Mat4::getRotationYMatrix( const float angle ) {
  Mat4 result = getIdentityMat();
  float cosAng = cosf( angle );
  float sinAng = sinf( angle );

  result._11 = cosAng;
  result._33 = cosAng;
  result._13 = -sinAng;
  result._31 = sinAng;

  return result;

}

Mat4 Mat4::getRotationZMatrix( const float angle ) {
  auto radianAngle = D3DXToRadian(angle);
  Mat4 result = getIdentityMat();
  float cosAng = cosf(radianAngle);
  float sinAng = sinf(radianAngle);

  result._11 = cosAng;
  result._22 = cosAng;
  result._12 = sinAng;
  result._21 = -sinAng;

  return result;

}

Mat4 Mat4::getTranslationMatrix( const Vec2& translation ) {
  Mat4 result = getIdentityMat();
  result._41 = translation.getX();
  result._42 = translation.getY();

  return result;

}

Mat4 Mat4::getTranslationMatrix( const float x, const float y, const float z ) {
  Mat4 result = getIdentityMat();
  result._41 = x;
  result._42 = y;
  result._43 = z;

  return result;
}

Mat4 Mat4::getScalingMatrix( const Vec2& scale ) {
  Mat4 result = getIdentityMat();

  result._11 = scale.getX();
  result._22 = scale.getY();

  return result;
}

Mat4 Mat4::getScalingMatrix( const float x, const float y, const float z ) {
  Mat4 result = getIdentityMat();

  result._11 = x;
  result._22 = y;
  result._33 = z;

  return result;
}

Mat4 Mat4::getOrthoLHMatrix ( float width, float height, float zn, float zf )
{
  Mat4 result = getIdentityMat (  );

  float d = zf - zn;

  result._11 = 2.0f / float(width);
  result._22 = 2.0f / float(height);
  result._33 = 1.0f / d;
  result._43 = -zn / d;

  return result;
}

Mat4 Mat4::getOrthoRHMatrix ( float width, float height, float zn, float zf )
{
  Mat4 result = getIdentityMat();

  float d = zn - zf;

  result._11 = 2.0f / float(width);
  result._22 = 2.0f / float(height);
  result._33 = 1.0f / d;
  result._43 = zn / d;

  return result;

}
}
