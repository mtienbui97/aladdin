/*
 * Created by phuctm97 on Oct 1st 2017
 */

#include "Loadable.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::Loadable)

Loadable::Loadable()
  : _loading( 0 ) {}

Loadable::~Loadable() {}

bool Loadable::isLoading() const {
  return _loading == 1;
}

bool Loadable::isLoaded() const {
  return _loading == 2;
}

void Loadable::setToLoading() {
  _loading = 1;
}

void Loadable::setToLoaded() {
  _loading = 2;
}
}
