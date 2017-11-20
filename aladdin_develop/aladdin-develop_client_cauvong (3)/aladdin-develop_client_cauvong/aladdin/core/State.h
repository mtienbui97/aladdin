#ifndef __ALADDIN_CORE_I_STATE_H__
#define __ALADDIN_CORE_I_STATE_H__

#include "GameObject.h"
#include "StateTransition.h"

NAMESPACE_ALA
{
class StateManager;

ALA_CLASS_HEADER_0(State)
private:
  StateManager* _stateManager;
  
  std::string _name;

  std::vector<StateTransition*> _transitions;

public:
  State( StateManager* stateManager,
         const std::string& name,
         const std::function<void()>& onStateEnter,
         const std::function<void( float dt )>& onUpdate,
         const std::function<void()>& onStateExit );

  virtual ~State();

  const std::string& getName() const;

  std::function<void()> onStateEnter;

  std::function<void( float dt )> onUpdate;

  std::function<void()> onStateExit;

  GameObject* getGameObject() const;

  StateManager* getStateManager() const;

  const std::vector<StateTransition*>& getTransitions() const;

  void addTransition( StateTransition* transition );

  State* checkTransition();

};
}
#endif //__ALADDIN_CORE_I_STATE_H__
