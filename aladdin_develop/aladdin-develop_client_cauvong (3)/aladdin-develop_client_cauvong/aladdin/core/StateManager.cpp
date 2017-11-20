#include "StateManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::StateManager, ala::GameObjectComponent)


StateManager::StateManager( GameObject* gameObject, const std::string& startState, const std::string& name ) :
  GameObjectComponent( gameObject, name ), _startStateName( startState ), _previousState( NULL ), _currentState( NULL ) {}

StateManager::~StateManager() {}

void StateManager::onInitialize() {
  _currentState = getState( _startStateName );
  if ( _currentState->onStateEnter != NULL ) {
    _currentState->onStateEnter();
  }
}

void StateManager::onUpdate( const float delta ) {
  const auto nextState = _currentState->checkTransition();
  if ( nextState != NULL ) {
    changeState( nextState );
  }
  else {
    if ( _currentState->onUpdate != NULL ) {
      _currentState->onUpdate( delta );
    }
  }
}

void StateManager::onRelease() {
  std::vector<State*> states;
  for ( const auto it : _states ) states.push_back( it.second );
  for ( auto state : states ) delete state;
}

void StateManager::changeState( State* state ) {
  if ( state ) {
    if ( _currentState->onStateExit != NULL ) {
      _currentState->onStateExit();
    }
    _previousState = _currentState;
    _currentState = state;
    if ( _currentState->onStateEnter != NULL ) {
      _currentState->onStateEnter();
    }
  }
}

void StateManager::attachState( State* state ) {
  if ( isReleasing() || isReleased() ) return;
  _states.emplace( state->getName(), state );
}

void StateManager::detachState( State* state ) {
  if ( isReleasing() || isReleased() ) return;
  _states.erase( state->getName() );
}

State* StateManager::getState( const std::string& name ) {
  const auto it = _states.find( name );
  if ( it == _states.end() ) return NULL;
  return it->second;
}

State* StateManager::getPreviousState() const {
  return _previousState;
}

std::string StateManager::getPreviousStateName() const {
  return _previousState == NULL ? "" : _previousState->getName();
}
}
