#ifndef __ALADDIN_CORE_ANIMATION_ACTION_H__
#define __ALADDIN_CORE_ANIMATION_ACTION_H__

#include "2dInclude.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0 (AnimationAction)
private:
  bool _loop;
  
  float _interval;

  std::string _actionName;

  std::string _textureName;

  std::vector<std::pair<Rect, Vec2>> _frames;
public:
  AnimationAction();

  AnimationAction( const std::vector<std::pair<Rect, Vec2>>& frames, const std::string& actionName, const std::string& textureName, const float interval = 0, const bool loop = true );

  virtual ~AnimationAction();

  const std::vector<std::pair<Rect, Vec2>>& getFrames() const;

  std::vector<std::pair<Rect, Vec2>>& getFrames();
  
  float getInterval() const;

  bool isLoop() const;

  const std::string& getActionName() const;

  const std::string& getTextureName() const;
};
}

#endif //!__ALADDIN_CORE_ANIMATION_ACTION_H__
