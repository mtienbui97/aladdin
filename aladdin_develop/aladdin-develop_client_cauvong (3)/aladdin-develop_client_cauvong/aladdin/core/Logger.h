/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_LOGGER_H__
#define __ALADDIN_CORE_LOGGER_H__

#include "ClassMeta.h"
#define LOGGER_BUFFER 4096

enum {
  ALA_LOG_DEBUG = 0,
  ALA_LOG_INFO = 1,
  ALA_LOG_ERROR = 2
};

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Logger)
private:
  static int __logLevel;
  std::string _className;
  char* _buffer;

public:
  static void setLogLevel( int level );

  Logger( const std::string& className );

  virtual ~Logger();

  void debug( char const* const format, ... ) const;

  void info(char const* const format, ...) const;

  void error(char const* const format, ...) const;


  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_LOGGERS_CREATED;
  static long TOTAL_LOGGERS_DELETED;

};
}

#endif //!__ALADDIN_CORE_LOGGER_H__
