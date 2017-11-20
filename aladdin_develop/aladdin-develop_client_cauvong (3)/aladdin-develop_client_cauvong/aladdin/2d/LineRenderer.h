#ifndef __ALADDIN_LINE_RENDERER_H__
#define __ALADDIN_LINE_RENDERER_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(LineRenderer, ala::GameObjectComponent)
private:
  std::vector<Vec2> _vertices;
  ala::Color _color;
  int _zOrder;

public:
  LineRenderer( GameObject* gameObject,
                const std::vector<ala::Vec2>& vertices,
                const ala::Color& color = ala::Color( 255, 255, 255 ),
                const std::string& name = "" );

  const std::vector<Vec2>& getVertices() const;

  void addVertex( const ala::Vec2& vec );

  void addVertices( const std::vector<ala::Vec2>& vertices );

  void setVertices( const std::vector<ala::Vec2>& vertices );

  void setColor( const ala::Color& color );

  const ala::Color& getColor() const;

  void setZOrder(const int order);

  int getZOrder() const;

protected:
  void onRender() override;

private:
  int calculateWorldZOrder() const;
};
}

#endif //!__ALADDIN_LINE_RENDERER_H__
