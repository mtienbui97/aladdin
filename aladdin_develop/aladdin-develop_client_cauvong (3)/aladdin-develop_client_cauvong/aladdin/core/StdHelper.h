#ifndef __ALADDIN_CORE_STD_HELPER_H__
#define __ALADDIN_CORE_STD_HELPER_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "CoreInclude.h"

NAMESPACE_ALA
{
class StdHelper {

public:
  template <class T>
  static bool vectorContain( const std::vector<T>& vec, const T& value );

  template <class T>
  static bool vectorErase( std::vector<T>& vec, const T& value );
};

template <class T>
bool StdHelper::vectorContain( const std::vector<T>& vec, const T& value ) {
  const auto it = std::find( vec.begin(), vec.end(), value );
  return it != vec.end();
}

template <class T>
bool StdHelper::vectorErase( std::vector<T>& vec, const T& value ) {
  const auto it = std::find( vec.begin(), vec.end(), value );
  if ( it == vec.end() ) return false;
  
  vec.erase( it );
  return true;
}
}

#endif //!__ALADDIN_CORE_STD_HELPER_H__
