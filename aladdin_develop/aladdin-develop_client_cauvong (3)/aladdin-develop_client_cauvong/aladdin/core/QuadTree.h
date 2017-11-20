#ifndef __ALADDIN_CORE_QUAD_TREE_H__
#define __ALADDIN_CORE_QUAD_TREE_H__

#include "QuadNode.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(QuadTree)
private:
  float _spaceMinX;
  float _spaceMinY;
  float _spaceMaxX;
  float _spaceMaxY;
  int _level;
  float _minNodeWidth;
  float _minNodeHeight;
  std::map<std::string, QuadNode*> _tree;
  std::vector<QuadNode*> _visibleNodes;

public:
  QuadTree( const float spaceMinX, const float spaceMinY,
            const float spaceMaxX, const float spaceMaxY,
            const int level = 3 );

  virtual ~QuadTree();

  int getLevel() const;

  float getMinQuadNodeWidth() const;

  float getMinQuadNodeHeight() const;

  void updateVisibility( const float minVisibleX, const float minVisibleY,
                         const float maxVisibleX, const float maxVisibleY );

  const std::vector<QuadNode*>& getVisibleNodes() const;

  QuadNode* getNode( const std::string& index ) const;

private:
  std::string toTreeIndex( const float x,
                           const float y ) const;
};
}

#endif //!__ALADDIN_CORE_QUAD_TREE_H__
