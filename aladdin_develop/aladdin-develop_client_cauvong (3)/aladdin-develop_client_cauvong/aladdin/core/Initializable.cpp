/*
 * Created by phuctm97 on Oct 1st 2017
 */

#include "Initializable.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Initializable)

Initializable::Initializable()
  : _initializing( 0 ) {}

Initializable::~Initializable() {}

bool Initializable::isInitializing() const {
  return _initializing == 1;
}

bool Initializable::isInitialized() const {
  return _initializing == 2;
}

void Initializable::setToInitializing() {
  _initializing = 1;
}

void Initializable::setToInitialized() {
  _initializing = 2;
}
}
