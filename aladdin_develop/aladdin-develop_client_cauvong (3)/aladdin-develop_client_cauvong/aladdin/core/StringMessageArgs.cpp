#include "StringMessageArgs.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( ala::StringMessageArgs, ala::MessageArgs )

StringMessageArgs::StringMessageArgs( const std::string& payload ) {
  _payload = payload;
}

const std::string& StringMessageArgs::getPayload() const {
  return _payload;
}
}
