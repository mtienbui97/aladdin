#ifndef __ALADDIN_CORE_STRING_MESSAGE_ARGS_H__
#define __ALADDIN_CORE_STRING_MESSAGE_ARGS_H__

#include "MessageArgs.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(StringMessageArgs, MessageArgs)
public:
  StringMessageArgs( const std::string& payload );

  const std::string& getPayload() const;

private:
  std::string _payload;
};
}
#endif //!__ALADDIN_CORE_STRING_MESSAGE_ARGS_H__
