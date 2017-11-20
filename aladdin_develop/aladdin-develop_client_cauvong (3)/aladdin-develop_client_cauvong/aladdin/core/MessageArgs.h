#ifndef __ALADDIN_CORE_MESSAGE_ARGS_H__
#define __ALADDIN_CORE_MESSAGE_ARGS_H__

#include "Releasable.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(MessageArgs, ala::Releasable)
public:
  MessageArgs();

  virtual ~MessageArgs();

public:
  void release() override;

protected:
  virtual void onRelease();
};
}
#endif //!__ALADDIN_CORE_MESSAGE_ARGS_H__
