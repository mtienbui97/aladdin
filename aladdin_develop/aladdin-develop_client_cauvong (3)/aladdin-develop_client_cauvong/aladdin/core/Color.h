#ifndef __ALADDIN_CORE_COLOR_H__
#define __ALADDIN_CORE_COLOR_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Color)
private:
  unsigned char _r;
  unsigned char _g;
  unsigned char _b;
  unsigned char _a;
public:
  Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );
  virtual ~Color();

  unsigned char getR() const;
  void setR( unsigned char r );
  unsigned char getG() const;
  void setG( unsigned char g );
  unsigned char getB() const;
  void setB( unsigned char b );
  unsigned char getA() const;
  void setA( unsigned char a );
};
}

#endif //!__ALADDIN_CORE_COLOR_H__
