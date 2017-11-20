#ifndef __ALADDIN_CORE_STATE_MANAGER_H__
#define __ALADDIN_CORE_STATE_MANAGER_H__

#include "State.h"
#include "GameObjectComponent.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( StateManager, GameObjectComponent )
private:
  std::string _startStateName;

  State* _currentState;
  State* _previousState;

  std::map<std::string, State*> _states;

protected:
  void onInitialize() override;

  void onUpdate( const float delta ) override;

  void onRelease() override;
public:
  StateManager( GameObject* gameObject, const std::string& startState, const std::string& name = "" );

  virtual ~StateManager();

  void changeState( State* state );

  void attachState( State* state );

  void detachState( State* state );

  State* getState( const std::string& name );

  State* getPreviousState() const;

  std::string getPreviousStateName() const;
};
}

#endif //__ALADDIN_CORE_STATE_MANAGER_H__
