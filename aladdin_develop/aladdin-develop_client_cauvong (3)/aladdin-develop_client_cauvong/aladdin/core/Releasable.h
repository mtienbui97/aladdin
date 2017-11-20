#ifndef __ALADDIN_CORE_RELEASABLE__
#define __ALADDIN_CORE_RELEASABLE__

/*
 * Created by phuctm97 on Oct 1st 2017
 */

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Releasable)
private:
  int _releasing;

public:
  Releasable();

  virtual ~Releasable();

  bool isReleasing() const;

  bool isReleased() const;

  virtual void release() = 0;

protected:
  void setToReleasing();

  void setToReleased();
};
}

#endif //!__ALADDIN_CORE_RELEASABLE__
