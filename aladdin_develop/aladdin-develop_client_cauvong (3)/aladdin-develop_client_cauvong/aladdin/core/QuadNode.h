#ifndef __ALADDIN_CORE_QUAD_NODE_H__
#define __ALADDIN_CORE_QUAD_NODE_H__

#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(QuadNode)
private:
  std::vector<GameObject*> _gameObjects;

public:
  QuadNode();

  virtual ~QuadNode();

  const std::vector<GameObject*>& getGameObjects() const;

  void addGameObject( GameObject* gameObject );

  void removeGameObject( GameObject* gameObject );
};
}


#endif //!__ALADDIN_CORE_QUAD_NODE_H__
