#include "StateTransition.h"
#include "State.h"
#include "StateManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::StateTransition )

StateTransition::StateTransition( const std::string& targetState, const std::function<bool()>& checker )
  : _targetState( targetState ), checker( checker ) {}

StateTransition::StateTransition( StateManager* stateManager, const std::string& fromState, const std::string& targetState, const std::function<bool()>& checker )
  : _targetState( targetState ), checker( checker ) {
  auto state = stateManager->getState( fromState );
  state->addTransition( this );
}

StateTransition::~StateTransition() {}

const std::string& StateTransition::getTargetState() {
  return _targetState;
}
}
