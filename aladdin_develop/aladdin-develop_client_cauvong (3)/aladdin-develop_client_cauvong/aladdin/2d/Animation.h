#ifndef __ALADDIN_2D_ANIMATION_H__
#define __ALADDIN_2D_ANIMATION_H__

#include "2dInclude.h"
#include "AnimationAction.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( Animation, ala::GameResource )
private:
  std::string _sourceFile;
  std::map<std::string, AnimationAction> _frames;
protected:
  void onLoad() override;

  void onRelease() override;

public:
  Animation(const std::string& name, const std::string& sourceFile, Scene* scope = NULL);

  AnimationAction* getAction(const std::string& actionName);

  virtual ~Animation();
};
}
#endif //!__ALADDIN_2D_ANIMATION_H__