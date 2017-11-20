#ifndef __ALADDIN_AUDIO_SOUND_H__
#define __ALADDIN_AUDIO_SOUND_H__

#include "AudioInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Sound, ala::Initializable, ala::Releasable)
private:
  std::string _sourceFile;

public:
  Sound( const std::string& sourceFile );

  virtual ~Sound();

public:
  void initialize() override;

  void release() override;

  const std::string& getSourceFile() const;

  // ===================================================
  // Platform specific
  // ===================================================
private:
  CSound* _cSound;

public:
  CSound* getCSound() const;

  void setCSound( CSound* cSound );

private:
  void initCSound();

  void releaseCSound();
};
}


#endif //!__ALADDIN_AUDIO_SOUND_H__
