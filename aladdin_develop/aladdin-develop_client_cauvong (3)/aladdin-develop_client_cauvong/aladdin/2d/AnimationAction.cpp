#include "AnimationAction.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(ala::AnimationAction)

AnimationAction::AnimationAction ( ): _loop( false ), _interval( 0 ) {}

AnimationAction::AnimationAction(const std::vector<std::pair<Rect, Vec2>>& frames, const std::string& actionName, const std::string& textureName, const float interval, const bool loop)
{
  _frames = frames;
  _interval = interval;
  _loop = loop;
  _actionName = actionName;
  _textureName = textureName;
}

AnimationAction::~AnimationAction() {}

const std::vector<std::pair<Rect, Vec2>>& AnimationAction::getFrames() const
{
  return _frames;
}

std::vector<std::pair<Rect, Vec2>>& AnimationAction::getFrames() {
  return _frames;
}

float AnimationAction::getInterval() const
{
  return _interval;
}

bool AnimationAction::isLoop() const
{
  return _loop;
}

const std::string& AnimationAction::getActionName ( ) const
{
  return _actionName;
}

const std::string& AnimationAction::getTextureName ( ) const
{
  return _textureName;
}
}
