#include "Animation.h"

#include "../pugixml/pugixml.hpp"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animation, ala::GameResource)


void Animation::onLoad ( )
{
  pugi::xml_document _animationFile;
  pugi::xml_parse_result result = _animationFile.load_file(_sourceFile.c_str (  ));

  ALA_ASSERT(result);

  auto atlasNode = _animationFile.child("Animations");

  auto actionNodes = atlasNode.children();

  for(auto action: actionNodes)
  {
    const std::string actionName = action.attribute("name").as_string();

    auto frameNodes = action.children("sprite");

    std::vector<std::pair<Rect, Vec2>> frames;

    for(auto frame: frameNodes)
    {
      Rect rect;
      rect.setTopLeft(Vec2(static_cast<float>(frame.attribute( "x" ).as_int()), static_cast<float>(frame.attribute( "y" ).as_int())));
      rect.setSize(Size(static_cast<float>(frame.attribute( "w" ).as_int()), static_cast<float>(frame.attribute( "h" ).as_int())));
      rect.setTopLeft(Vec2(rect.getTopLeft().getX(), rect.getTopLeft().getY()));

      Vec2 offset;
      offset.setX(frame.attribute("offsetX").as_float(0));
      offset.setY(frame.attribute("offsetY").as_float(0));

      frames.push_back(std::make_pair( rect, offset ));
    }

    const auto animationAction = AnimationAction(frames, actionName, action.attribute("imagePath").as_string(), action.attribute("interval").as_float(), action.attribute("isLoop").as_bool());

    _frames[actionName] = animationAction;
  }
}

void Animation::onRelease ( )
{
}

Animation::Animation ( const std::string& name, const std::string& sourceFile, Scene* scope )
  : GameResource ( name, scope )
{
  _sourceFile = sourceFile;
}

AnimationAction* Animation::getAction ( const std::string& actionName )
{
  return &_frames[actionName];
}

Animation::~Animation ( )
{
}
}
