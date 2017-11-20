/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "ClassMeta.h"

NAMESPACE_ALA
{
ClassMeta::ClassMeta( const std::string& className ) :
  _className( className ),
  _baseClasses( {} ) {}

ClassMeta::ClassMeta( const std::string& className, ClassMeta* baseClass ) :
  _className( className ),
  _baseClasses( { baseClass } ) {}

ClassMeta::ClassMeta( const std::string& className, ClassMeta* baseClass1, ClassMeta* baseClass2 ) :
  _className( className ),
  _baseClasses( { baseClass1, baseClass2 } ) {}

ClassMeta::ClassMeta( const std::string& className, ClassMeta* baseClass1, ClassMeta* baseClass2,
                      ClassMeta* baseClass3 ) :
  _className( className ),
  _baseClasses( { baseClass1, baseClass2, baseClass3 } ) {}

ClassMeta::ClassMeta( const std::string& className, ClassMeta* baseClass1, ClassMeta* baseClass2, ClassMeta* baseClass3,
                      ClassMeta* baseClass4 ) :
  _className( className ),
  _baseClasses( { baseClass1, baseClass2, baseClass3, baseClass4 } ) {}

ClassMeta::ClassMeta( const std::string& className, ClassMeta* baseClass1, ClassMeta* baseClass2, ClassMeta* baseClass3,
                      ClassMeta* baseClass4, ClassMeta* baseClass5 ) :
  _className( className ),
  _baseClasses( { baseClass1, baseClass2, baseClass3, baseClass4, baseClass5 } ) {}

const std::string& ClassMeta::getClassName() const {
  return _className;
}

const std::vector<ClassMeta *>& ClassMeta::getBaseClasses() const {
  return _baseClasses;
}

const bool ClassMeta::isExactly( const ClassMeta& classMeta ) const {
  return this == &classMeta;
}

const bool ClassMeta::isDerived( const ClassMeta& classMeta ) const {
  std::stack<ClassMeta *> stack = {};

  // init stack base
  for ( ClassMeta* baseClass : _baseClasses ) {
    stack.push( baseClass );
  }

  while ( !stack.empty() ) {
    ClassMeta* p = stack.top();
    stack.pop();

    if ( p == &classMeta ) return true;
    for ( ClassMeta* baseClass : p->_baseClasses ) {
      stack.push( baseClass );
    }
  }

  return false;
}
}
