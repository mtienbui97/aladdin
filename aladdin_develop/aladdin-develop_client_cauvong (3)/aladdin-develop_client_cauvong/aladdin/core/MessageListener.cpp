#include "MessageListener.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::MessageListener )

MessageListener::MessageListener() {}

MessageListener::~MessageListener() {
  unsubcribeAllMessages();
}

void MessageListener::subscribeGlobalMessage( const std::string& messageId, const std::function<void( MessageArgs* )>& callback ) {
  if ( callback == NULL ) return;

  const auto token = GameManager::get()->getGlobalMessenger()->subscribe( messageId, callback );

  const auto vecIt = _subcribedGlobalTokens.find( messageId );
  if ( vecIt == _subcribedGlobalTokens.end() ) {
    std::vector<long> vec;
    vec.push_back( token );
    _subcribedGlobalTokens.emplace( messageId, vec);
  }
  else {
    auto& vec = vecIt->second;
    vec.push_back( token );
  }
}

void MessageListener::subscribeObjectMessage( GameObject* object, const std::string& messageId, const std::function<void( MessageArgs* )>& callback ) {
  if ( callback == NULL ) return;
  if ( object == NULL ) return;

  const auto token = object->getMessenger()->subscribe( messageId, callback );

  auto mapIt = _subcribedObjectTokens.find( object->getId() );
  if ( mapIt == _subcribedObjectTokens.end() ) {
    std::unordered_map<std::string, std::vector<long>> map;
    std::vector<long> vec;
    vec.push_back( token );
    map.emplace( messageId, vec );
    _subcribedObjectTokens.emplace( object->getId(), map );
  }
  else {
    auto& map = mapIt->second;
    const auto vecIt = map.find( messageId );
    if ( vecIt == map.end() ) {
      std::vector<long> vec;
      vec.push_back( token );
      map.emplace( messageId, vec);
    }
    else {
      auto& vec = vecIt->second;
      vec.push_back( token );
    }
  }
}

void MessageListener::unsubcribeGlobalMessage( const std::string& messageId ) {
  for ( const auto token : _subcribedGlobalTokens[messageId] ) {
    GameManager::get()->getGlobalMessenger()->unsubscribe( messageId, token );
  }
  _subcribedGlobalTokens.erase( messageId );
}

void MessageListener::unsubcribeObjectMessage( GameObject* object, const std::string& messageId ) {
  if ( object == NULL ) return;

  for ( const auto token : _subcribedObjectTokens[object->getId()][messageId] ) {
    object->getMessenger()->unsubscribe( messageId, token );
  }
  _subcribedObjectTokens.erase( object->getId() );
}

void MessageListener::unsubcribeAllMessages() {
  unsubcribeAllGlobalMessages();
  unsubcribeAllObjectMessages();
}

void MessageListener::unsubcribeAllGlobalMessages() {
  for ( const auto vecIt : _subcribedGlobalTokens ) {
    for ( const auto token : vecIt.second ) {
      GameManager::get()->getGlobalMessenger()->unsubscribe( vecIt.first, token );
    }
  }
  _subcribedGlobalTokens.clear();
}

void MessageListener::unsubcribeAllObjectMessages() {
  for ( const auto mapIt : _subcribedObjectTokens ) {
    const auto object = GameManager::get()->getObjectById( mapIt.first );
    if ( object == NULL ) continue;

    for ( const auto vecIt : mapIt.second ) {
      for ( const auto token : vecIt.second ) {
        object->getMessenger()->unsubscribe( vecIt.first, token );
      }
    }
  }
  _subcribedObjectTokens.clear();
}

void MessageListener::unsubcribeAllObjectMessages( GameObject* object ) {
  if ( object == NULL ) return;

  for ( const auto vecIt : _subcribedObjectTokens[object->getId()] ) {
    for ( const auto token : vecIt.second ) {
      object->getMessenger()->unsubscribe( vecIt.first, token );
    }
  }
  _subcribedObjectTokens.erase( object->getId() );
}
}
