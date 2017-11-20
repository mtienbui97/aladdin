#ifndef __ALADDIN_CORE_CORE_MARCOS_H__
#define __ALADDIN_CORE_CORE_MARCOS_H__

/*
 * Created by phuctm97 on Sep 27th 2017
 */

// Common Methods
#ifndef M_PI
#define M_PI      3.1415927f
#endif

#ifndef MIN
#define MIN( x, y ) (((x) > (y)) ? (y) : (x))
#endif

#ifndef MAX
#define MAX( x, y ) (((x) < (y)) ? (y) : (x))
#endif

#ifndef ABS
#define ABS( x ) (x >= 0 ? x : -(x))
#endif

#ifndef DEGREE_TO_RADIAN
#define DEGREE_TO_RADIAN(degree) ((degree) * (M_PI/180.f))
#endif

#ifndef RADIAN_TO_DEGREE
#define RADIAN_TO_DEGREE(radian) ((radian) * (180.f/M_PI))
#endif

#undef min
#undef max

#ifdef NULL
#undef NULL
#endif
#define NULL nullptr

#ifdef ALA_ASSERT
#undef ALA_ASSERT
#endif
#define ALA_ASSERT( _expr_ ) assert( _expr_ )

#define SAFE_DELETE(_ptr_) \
  if(_ptr_ != NULL) { \
    delete _ptr_; \
    _ptr_ = NULL; \
  }

// Aladdin Defines
#define NAMESPACE_ALA         namespace ala
#define USING_NAMESPACE_ALA   using namespace ala

// ClassMeta
#define ALA_IS_INSTANCE_OF(_obj_, _class_) (_obj_->getClassMeta().isExactly( _class_::CLASS_META ) || _obj_->getClassMeta().isDerived( _class_::CLASS_META ))

#define ALA_DECLARE_CLASS_META \
public: \
  static ala::ClassMeta CLASS_META; \
  virtual const ala::ClassMeta &getClassMeta() const { return CLASS_META; }

#define ALA_DEFINE_CLASS_META_0( _class_ ) ala::ClassMeta _class_::CLASS_META( #_class_ );

#define ALA_DEFINE_CLASS_META_1( _class_, _baseclass1_ ) \
ala::ClassMeta _class_::CLASS_META( \
  #_class_, \
  &_baseclass1_::CLASS_META );

#define ALA_DEFINE_CLASS_META_2( _class_, _baseclass1_, _baseclass2_ ) \
ala::ClassMeta _class_::CLASS_META( \
  #_class_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META );

#define ALA_DEFINE_CLASS_META_3( _class_, _baseclass1_, _baseclass2_, _baseclass3_ ) \
ala::ClassMeta _class_::CLASS_META( \
  #_class_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META, \
  &_baseclass3_::CLASS_META );

#define ALA_DEFINE_CLASS_META_4( _class_, _baseclass1_, _baseclass2_, _baseclass3_, _baseclass4_ ) \
ala::ClassMeta _class_::CLASS_META( \
  #_class_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META, \
  &_baseclass3_::CLASS_META, \
  &_baseclass4_::CLASS_META );

#define ALA_DEFINE_CLASS_META_5( _class_, _baseclass1_, _baseclass2_, _baseclass3_, _baseclass4_, _baseclass5_ ) \
ala::ClassMeta _class_::CLASS_META( \
  #_class_, \
  &_baseclass1_::CLASS_META, \
  &_baseclass2_::CLASS_META, \
  &_baseclass3_::CLASS_META, \
  &_baseclass4_::CLASS_META, \
  &_baseclass5_::CLASS_META );

#define ALA_CLASS_HEADER_0( _class_ ) \
  class _class_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_1( _class_, _base1_ ) \
  class _class_ : public _base1_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_2( _class_, _base1_, _base2_ ) \
  class _class_ : public _base1_, public _base2_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_3( _class_, _base1_, _base2_, _base3_ ) \
  class _class_ : public _base1_, public _base2_, public _base3_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_4( _class_, _base1_, _base2_, _base3_, _base4_ ) \
  class _class_ : public _base1_, public _base2_, public _base3_, public _base4_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_HEADER_5( _class_, _base1_, _base2_, _base3_, _base4_, _base5_ ) \
  class _class_ : public _base1_, public _base2_, public _base3_, public _base4_, public _base5_ { \
  public: \
    ALA_DECLARE_CLASS_META \
  private:

#define ALA_CLASS_SOURCE_0( _class_ ) \
ALA_DEFINE_CLASS_META_0(_class_)

#define ALA_CLASS_SOURCE_1( _class_, _base1_ ) \
ALA_DEFINE_CLASS_META_1(_class_, _base1_)

#define ALA_CLASS_SOURCE_2( _class_, _base1_, _base2_ ) \
ALA_DEFINE_CLASS_META_2(_class_, _base1_, _base2_)

#define ALA_CLASS_SOURCE_3( _class_, _base1_, _base2_, _base3_ ) \
ALA_DEFINE_CLASS_META_3(_class_, _base1_, _base2_, _base3_ )

#define ALA_CLASS_SOURCE_4( _class_, _base1_, _base2_, _base3_, _base4_ ) \
ALA_DEFINE_CLASS_META_4(_class_, _base1_, _base2_, _base3_, _base4_ )

#define ALA_CLASS_SOURCE_5( _class_, _base1_, _base2_, _base3_, _base4_, _base5_ ) \
ALA_DEFINE_CLASS_META_5(_class_, _base1_, _base2_, _base3_, _base4_, _base5_ )

enum
{
  ALA_FALSE,
  ALA_INITIALIZING,
  ALA_INITIALIZED,
  ALA_RELEASING,
  ALA_RELEASED
};

//MESSAGE DEFINITIONS

#define SOURCE_RECT_CHANGE_MESSAGE "Source rect changed"

#endif //!__ALADDIN_CORE_CORE_MARCOS_H__
