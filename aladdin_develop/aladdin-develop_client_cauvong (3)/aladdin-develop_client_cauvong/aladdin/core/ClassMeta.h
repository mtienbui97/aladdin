#ifndef __ALADDIN_CORE_META_CLASS_H__
#define __ALADDIN_CORE_META_CLASS_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "CoreInclude.h"

NAMESPACE_ALA
{
class ClassMeta {
  // TODO: Do not allow to have Ptr<ClassMeta> instance

private:
  std::string _className;
  std::vector<ClassMeta *> _baseClasses;

public:
  ClassMeta( const std::string& className );

  ClassMeta( const std::string& className,
             ClassMeta* baseClass );

  ClassMeta( const std::string& className,
             ClassMeta* baseClass1,
             ClassMeta* baseClass2 );

  ClassMeta( const std::string& className,
             ClassMeta* baseClass1,
             ClassMeta* baseClass2,
             ClassMeta* baseClass3 );

  ClassMeta( const std::string& className,
             ClassMeta* baseClass1,
             ClassMeta* baseClass2,
             ClassMeta* baseClass3,
             ClassMeta* baseClass4 );

  ClassMeta( const std::string& className,
             ClassMeta* baseClass1,
             ClassMeta* baseClass2,
             ClassMeta* baseClass3,
             ClassMeta* baseClass4,
             ClassMeta* baseClass5 );

  const std::string& getClassName() const;

  const std::vector<ClassMeta *>& getBaseClasses() const;

  const bool isExactly( const ClassMeta& classMeta ) const;

  const bool isDerived( const ClassMeta& classMeta ) const;
};
}

#endif //!__ALADDIN_CORE_META_CLASS_H__
