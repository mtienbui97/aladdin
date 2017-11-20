/*
 * Created by phuctm97 on Oct 1st 2017
 */

#include "Releasable.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Releasable)

Releasable::Releasable()
  : _releasing( 0 ) {}

Releasable::~Releasable() {}

bool Releasable::isReleasing() const {
  return _releasing == 1;
}

bool Releasable::isReleased() const {
  return _releasing == 2;
}

void Releasable::setToReleasing() {
  _releasing = 1;
}

void Releasable::setToReleased() {
  _releasing = 2;
}
}
