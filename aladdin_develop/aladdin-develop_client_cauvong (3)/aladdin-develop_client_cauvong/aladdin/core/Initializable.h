#ifndef __ALADDIN_CORE_INITIALIZABLE_H__
#define __ALADDIN_CORE_INITIALIZABLE_H__

/*
 * Created by phuctm97 on Oct 1st 2017
 */

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Initializable)
private:
  int _initializing;

public:
  Initializable();

  virtual ~Initializable();

  bool isInitializing() const;

  bool isInitialized() const;

  virtual void initialize() = 0;

protected:
  void setToInitializing();

  void setToInitialized();
};
}


#endif //!__ALADDIN_CORE_INITIALIZABLE_H__
