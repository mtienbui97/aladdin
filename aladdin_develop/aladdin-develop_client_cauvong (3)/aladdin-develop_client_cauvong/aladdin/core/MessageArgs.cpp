#include "MessageArgs.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::MessageArgs, ala::Releasable)

MessageArgs::MessageArgs() {
  ALA_ASSERT(!isReleased() && !isReleasing());
}

MessageArgs::~MessageArgs() {
  ALA_ASSERT(isReleased());
}

void MessageArgs::release() {
  ALA_ASSERT(!isReleased() && !isReleasing());
  setToReleasing();

  // releasing goes here
  onRelease();

  setToReleased();

  // destroy
  delete this;
}

void MessageArgs::onRelease() {}
}
