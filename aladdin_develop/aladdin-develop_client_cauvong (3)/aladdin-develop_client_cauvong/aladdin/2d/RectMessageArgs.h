#ifndef __ALADDIN_CORE_RECT_MESSAGE_ARGS_H__
#define __ALADDIN_CORE_RECT_MESSAGE_ARGS_H__

#include "../core/MessageArgs.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( RectMessageArgs, MessageArgs )
private:
  Rect _rect;
public:
  RectMessageArgs(const Rect &rect);

  const Rect& getRect() const;
};
}

#endif //!__ALADDIN_CORE_RECT_MESSAGE_ARGS_H__