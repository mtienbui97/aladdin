#include "QuadTree.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::QuadTree )

QuadTree::QuadTree( const float spaceMinX, const float spaceMinY,
                    const float spaceMaxX, const float spaceMaxY,
                    const int level )
  : _spaceMinX( spaceMinX ), _spaceMinY( spaceMinY ), _spaceMaxX( spaceMaxX ), _spaceMaxY( spaceMaxY ),
    _level( level ) {
  ALA_ASSERT(level >= 1 && level <= 5);
  _minNodeWidth = (_spaceMaxX - _spaceMinX + 1) / powf( 2, static_cast<float>(level) );
  _minNodeHeight = (_spaceMaxY - _spaceMinY + 1) / powf( 2, static_cast<float>(level) );

  // build tree
  std::queue<std::string> treeQueue;
  treeQueue.push( "0" );
  treeQueue.push( "1" );
  treeQueue.push( "2" );
  treeQueue.push( "3" );
  while ( !treeQueue.empty() ) {
    const auto nodeId = treeQueue.front();
    treeQueue.pop();

    _tree.emplace( nodeId, new QuadNode() );

    const auto nodeLevel = static_cast<int>(nodeId.length());
    if ( nodeLevel < level ) {
      treeQueue.push( nodeId + "0" );
      treeQueue.push( nodeId + "1" );
      treeQueue.push( nodeId + "2" );
      treeQueue.push( nodeId + "3" );
    }
  }
}

QuadTree::~QuadTree() {
  for ( const auto it : _tree ) {
    delete it.second;
  }
}

int QuadTree::getLevel() const {
  return _level;
}

float QuadTree::getMinQuadNodeWidth() const {
  return _minNodeWidth;
}

float QuadTree::getMinQuadNodeHeight() const {
  return _minNodeHeight;
}

void QuadTree::updateVisibility( const float minVisibleX, const float minVisibleY,
                                 const float maxVisibleX, const float maxVisibleY ) {
  _visibleNodes.clear();

  std::unordered_set<std::string> visibleNodeIds;

  auto x = minVisibleX;
  auto y = minVisibleY;
  while ( true ) {
    const auto& treeIndex = toTreeIndex( x, y );
    for ( size_t l = 1; l <= treeIndex.length(); l++ ) {
      visibleNodeIds.emplace( treeIndex.substr( 0, l ) );
    }

    x += _minNodeWidth;
    y += _minNodeHeight;
    if ( x > maxVisibleX && y > maxVisibleY ) break;
    if ( x > maxVisibleX ) x -= _minNodeWidth;
    if ( y > maxVisibleY ) x -= _minNodeHeight;
  }

  for ( const auto& id : visibleNodeIds ) _visibleNodes.push_back( _tree[id] );
}

const std::vector<QuadNode*>& QuadTree::getVisibleNodes() const {
  return _visibleNodes;
}

QuadNode* QuadTree::getNode( const std::string& index ) const {
  return _tree.at( index );
}

std::string QuadTree::toTreeIndex( const float x, const float y ) const {
  auto levelWidth = (_spaceMaxX - _spaceMinX + 1) / 2;
  auto levelHeight = (_spaceMaxY - _spaceMinY + 1) / 2;

  std::string treeIndex = "";
  while ( static_cast<int>(treeIndex.length()) < _level ) {
    const auto levelXIndex = x / levelWidth;
    const auto levelYIndex = y / levelHeight;

    if ( levelXIndex < 1 && levelYIndex < 1 ) treeIndex += "0";
    else if ( levelXIndex >= 1 && levelYIndex < 1 ) treeIndex += "1";
    else if ( levelXIndex >= 1 && levelYIndex >= 1 ) treeIndex += "2";
    else if ( levelXIndex < 1 && levelYIndex >= 1 ) treeIndex += "3";

    levelWidth /= 2;
    levelHeight /= 2;
  }
  return treeIndex;
}
}
