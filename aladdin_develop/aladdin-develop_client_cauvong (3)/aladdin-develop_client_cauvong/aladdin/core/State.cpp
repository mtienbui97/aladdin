#include "State.h"
#include "StateManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0 ( ala::State )

State::State( StateManager* stateManager,
              const std::string& name,
              const std::function<void()>& onStateEnter,
              const std::function<void( float dt )>& onUpdate,
              const std::function<void()>& onStateExit )
  : _stateManager( stateManager ),
    _name( name ),
    onStateEnter( onStateEnter ),
    onUpdate( onUpdate ),
    onStateExit( onStateExit ) {
  _stateManager->attachState( this );
}

State::~State() {
  for ( auto transition : _transitions ) {
    delete transition;
  }
  _stateManager->detachState( this );
}

const std::string& State::getName() const {
  return _name;
}

GameObject* State::getGameObject() const {
  return _stateManager->getGameObject();
}

StateManager* State::getStateManager() const {
  return _stateManager;
}

const std::vector<StateTransition*>& State::getTransitions() const {
  return _transitions;
}

void State::addTransition( StateTransition* transition ) {
  _transitions.push_back( transition );
}

State* State::checkTransition() {
  for ( auto transition : _transitions ) {
    if ( transition->checker == NULL ) continue;
    if ( transition->checker() ) return _stateManager->getState( transition->getTargetState() );
  }
  return NULL;
}
}
