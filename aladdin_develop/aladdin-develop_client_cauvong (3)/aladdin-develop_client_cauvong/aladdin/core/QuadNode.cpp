#include "QuadNode.h"
#include "StdHelper.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::QuadNode)

QuadNode::QuadNode() {}

QuadNode::~QuadNode() {}

const std::vector<GameObject*>& QuadNode::getGameObjects() const {
  return _gameObjects;
}

void QuadNode::addGameObject( GameObject* gameObject ) {
  _gameObjects.push_back( gameObject );
}

void QuadNode::removeGameObject( GameObject* gameObject ) {
  const auto it = std::find( _gameObjects.cbegin(), _gameObjects.cend(), gameObject );
  _gameObjects.erase( it );
}
}
