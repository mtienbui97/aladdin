/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Logger.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::Logger )

int Logger::__logLevel( ALA_LOG_DEBUG );

void Logger::setLogLevel( int level ) {
  ALA_ASSERT(level >= ALA_LOG_DEBUG && level <= ALA_LOG_ERROR);
  __logLevel = level;
}

Logger::Logger( const std::string& className ) : _className( className ) {
  _buffer = new char[LOGGER_BUFFER];
  TOTAL_LOGGERS_CREATED++;
}

Logger::~Logger() {
  delete[]_buffer;
  TOTAL_LOGGERS_DELETED++;
}

void Logger::debug( char const* const format, ... ) const {
  if ( __logLevel > ALA_LOG_DEBUG ) return;

  std::fill(_buffer, _buffer + LOGGER_BUFFER, '\0');

  va_list args;
  va_start(args, format);
  vsprintf(_buffer, format, args );

  std::string logString = "[D] [" + _className + "] : " + _buffer;
  if ( logString.back() != '\n' )logString += "\n";

  printf( logString.c_str() );
  va_end(args);
}

void Logger::info( char const* const format, ... ) const {
  if ( __logLevel > ALA_LOG_INFO ) return;

  std::fill(_buffer, _buffer + LOGGER_BUFFER, '\0');

  va_list args;
  va_start(args, format);
  vsprintf(_buffer, format, args );

  std::string logString = "[I] [" + _className + "] : " + _buffer;
  if ( logString.back() != '\n' )logString += "\n";

  printf( logString.c_str() );
  va_end(args);
}

void Logger::error( char const* const format, ... ) const {
  if ( __logLevel > ALA_LOG_ERROR ) return;

  std::fill(_buffer, _buffer + LOGGER_BUFFER, '\0');

  va_list args;
  va_start(args, format);
  vsprintf(_buffer, format, args );

  std::string logString = "[E] [" + _className + "]: " + _buffer;
  if ( logString.back() != '\n' )logString += "\n";

  printf( logString.c_str() );
  va_end(args);
}

// =============================================
// Debug memory allocation
// =============================================
long Logger::TOTAL_LOGGERS_CREATED( 0 );
long Logger::TOTAL_LOGGERS_DELETED( 0 );
}
