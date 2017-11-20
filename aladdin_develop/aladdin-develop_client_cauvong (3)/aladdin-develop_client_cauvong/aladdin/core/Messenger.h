#ifndef __ALADDIN_CORE_MESSENGER__
#define __ALADDIN_CORE_MESSENGER__

#include "MessageArgs.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Messenger, ala::Releasable)
public:
  Messenger();

  virtual ~Messenger();

  void broadcast( const std::string& messageId, MessageArgs* args );

  long subscribe( const std::string& messageId, const std::function<void( MessageArgs* )>& callback );

  void unsubscribe( const std::string& messageId, const long token );

  void release() override;

private:
  std::unordered_map<std::string, std::unordered_map<long, std::function<void( MessageArgs* )>>> _callbacks;

  long _tokenCounter;

  // =============================================
  // Debug memory usage
  // =============================================
public:
  static long TOTAL_MESSENGERS_CREATED;
  static long TOTAL_MESSENGERS_DELETED;
};
}
#endif //!__ALADDIN_CORE_MESSENGER__
