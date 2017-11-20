#ifndef __ALADDIN_CORE_LOADABLE__
#define __ALADDIN_CORE_LOADABLE__

/*
 * Created by phuctm97 on Oct 1st 2017
 */

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Loadable)
private:
  int _loading;

public:
  Loadable();

  virtual ~Loadable();

  bool isLoading() const;

  bool isLoaded() const;

  virtual void load() = 0;

protected:
  void setToLoading();

  void setToLoaded();
};
}

#endif //!__ALADDIN_CORE_LOADABLE__
