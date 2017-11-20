#include "Animator.h"
#include "RectMessageArgs.h"
#include "SpriteRenderer.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animator, ala::GameObjectComponent)

Animator::~Animator ( )
{
}

void Animator::onUpdate ( const float delta )
{
  if(!_isPlaying)
  {
    return;
  }

  _elapsedTime += delta;

  if (_elapsedTime >= _currentAction->getInterval (  ))
  {
    ++_frameIterator;
    if (_frameIterator == _currentAction->getFrames().end() )
    {
      if(!_currentAction->isLoop (  ))
      {
        _isPlaying = false;
        return;
      }
      else
      {
        playFromStart();
        _elapsedTime = 0;
      }
    }
    else
    {
      auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
      if(spriteRenderer!= NULL)
      {
        spriteRenderer->setSourceRect(_frameIterator->first);
        spriteRenderer->setOffset(_frameIterator->second);
      }
      _elapsedTime = 0;
    }


  }

}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, Animation* animation,const std::string& name )
  :GameObjectComponent ( gameObject, name )
{
  _isPlaying = true;

  _animation = animation;
  _currentAction = _animation->getAction(entryAction);

  _frameIterator = _currentAction->getFrames (  ).begin();

  auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if (spriteRenderer != NULL)
  {
    spriteRenderer->setSprite(static_cast < Sprite* > (GameManager::get()->getResource(_currentAction->getTextureName())));
    spriteRenderer->setSourceRect(_frameIterator->first);
    spriteRenderer->setOffset(_frameIterator->second);
  }
}

Animator::Animator ( GameObject* gameObject, const std::string &entryAction, const std::string& animationResourceName, const std::string& name )
  :GameObjectComponent(gameObject, name)
{
  _isPlaying = true;

  _animation = static_cast<Animation*>(GameManager::get()->getResource(animationResourceName));
  _currentAction = _animation->getAction(entryAction);

  _frameIterator = _currentAction->getFrames().begin();

  auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if (spriteRenderer != NULL)
  {
    spriteRenderer->setSprite(static_cast < Sprite* > (GameManager::get()->getResource(_currentAction->getTextureName())));
    spriteRenderer->setSourceRect(_frameIterator->first);
    spriteRenderer->setOffset(_frameIterator->second);
  }

}

Animation* Animator::getAnimation() const {
  return _animation;
}

void Animator::setAction ( const std::string& actionName )
{
  _currentAction = _animation->getAction(actionName);
  _frameIterator = _currentAction->getFrames().begin();
  _isPlaying = true;
  auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if (spriteRenderer != NULL)
  {
    spriteRenderer->setSprite(static_cast < Sprite* > (GameManager::get()->getResource(_currentAction->getTextureName())));
    spriteRenderer->setSourceRect(_frameIterator->first);
    spriteRenderer->setOffset(_frameIterator->second);
  }
}

const std::string& Animator::getActionName ( ) const
{
  return _currentAction->getActionName();
}

const Rect& Animator::getCurrentFrameRect ( ) const
{
  return _frameIterator->first;
}

const Vec2& Animator::getCurrentFrameOffset() const {
  return _frameIterator->second;
}

AnimationAction* Animator::getAction() const {
  return _currentAction;
}

int Animator::getCurrentFrameIndex() const {
  return std::distance(_currentAction->getFrames().begin(), _frameIterator);
}

void Animator::pause ( )
{
  _isPlaying = false;
}

void Animator::playNext ( )
{
  ++_frameIterator;

  if(_frameIterator == _currentAction->getFrames (  ).end (  ))
  {
    playFromStart();
  }
  else
  {
    auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
    if (spriteRenderer != NULL)
    {
      spriteRenderer->setSourceRect(_frameIterator->first);
      spriteRenderer->setOffset(_frameIterator->second);
    }
  }
}

void Animator::play ( )
{
  _isPlaying = true;
}

void Animator::playFromStart ( )
{
  _isPlaying = true;

  _frameIterator = _currentAction->getFrames().begin();

  auto spriteRenderer = getGameObject()->getComponentT<SpriteRenderer>();
  if (spriteRenderer != NULL)
  {
    spriteRenderer->setSourceRect(_frameIterator->first);
    spriteRenderer->setOffset(_frameIterator->second);
  }
}

bool Animator::isPlaying ( ) const
{
  return _isPlaying;
}
}
