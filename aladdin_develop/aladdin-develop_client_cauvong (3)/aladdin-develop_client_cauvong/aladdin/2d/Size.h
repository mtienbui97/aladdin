#ifndef __ALADDIN_2D_SIZE2_H__
#define __ALADDIN_2D_SIZE2_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Size)
private:
  float _width;
  float _height;

public:
  Size( const float x, const float y );

  virtual ~Size();

  float getWidth() const;

  void setWidth( const float width );

  float getHeight() const;

  void setHeight( const float height );

	float getArea() const;

  bool operator==(const Size& s) const;

  bool operator!=(const Size& s) const;
};
}

#endif //!__ALADDIN_2D_SIZE2_H__
