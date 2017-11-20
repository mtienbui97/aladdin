#include "RectMessageArgs.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::RectMessageArgs, ala::MessageArgs)

RectMessageArgs::RectMessageArgs( const Rect& rect )
  :_rect(rect)
{
}

const Rect& RectMessageArgs::getRect ( ) const
{
  return _rect;
}
}
