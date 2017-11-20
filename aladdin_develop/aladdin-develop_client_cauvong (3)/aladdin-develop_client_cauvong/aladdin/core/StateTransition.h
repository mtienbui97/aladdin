#ifndef __ALADDIN_CORE_STATE_TRANSITION_H__
#define __ALADDIN_CORE_STATE_TRANSITION_H__

#include "ClassMeta.h"

NAMESPACE_ALA
{
class StateManager;

ALA_CLASS_HEADER_0(StateTransition)
private:
  std::string _targetState;

public:
  StateTransition( const std::string& targetState, const std::function<bool()>& checker );

  StateTransition( StateManager* stateManager, const std::string& fromState, const std::string& targetState, const std::function<bool()>& checker );


  virtual ~StateTransition();

  std::function<bool()> checker;

  const std::string& getTargetState();
};
}


#endif //!__ALADDIN_CORE_STATE_TRANSITION_H__
