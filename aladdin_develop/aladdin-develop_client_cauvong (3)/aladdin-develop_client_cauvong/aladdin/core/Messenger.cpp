#include "Messenger.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Messenger, ala::Releasable)

Messenger::Messenger()
  : _tokenCounter( 0 ) {
  ALA_ASSERT(!isReleased() && !isReleasing());
  TOTAL_MESSENGERS_CREATED++;
}

Messenger::~Messenger() {
  ALA_ASSERT(isReleased());
  TOTAL_MESSENGERS_DELETED++;
}

void Messenger::broadcast( const std::string& messageId, MessageArgs* args ) {
  for ( const auto callback : _callbacks[messageId] ) {
    callback.second( args );
  }

  // release args
  if ( args ) {
    args->release();
  }
}

long Messenger::subscribe( const std::string& messageId, const std::function<void( MessageArgs* )>& callback ) {
  if ( isReleased() || isReleasing() ) return -1;
  if ( callback == NULL ) return -1;

  ++_tokenCounter;
  _callbacks[messageId].emplace( _tokenCounter, callback );
  return _tokenCounter;
}

void Messenger::unsubscribe( const std::string& messageId, const long token ) {
  if ( isReleased() || isReleasing() ) return;

  int rc = _callbacks[messageId].erase( token );
}

void Messenger::release() {
  ALA_ASSERT(!isReleased() && !isReleasing());
  setToReleasing();

  // releasing goes here

  setToReleased();

  // destroy
  delete this;
}

long Messenger::TOTAL_MESSENGERS_CREATED( 0 );
long Messenger::TOTAL_MESSENGERS_DELETED( 0 );
}
