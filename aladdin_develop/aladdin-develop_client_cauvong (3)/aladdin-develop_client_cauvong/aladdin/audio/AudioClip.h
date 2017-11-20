#ifndef __ALADDIN_AUDIO_AUDIO_CLIP_H__
#define __ALADDIN_AUDIO_AUDIO_CLIP_H__

#include "AudioInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(AudioClip, ala::GameResource)
  // ====================================================
  // Basics
  // ====================================================
private:
  std::string _sourceFile;

public:
  AudioClip( const std::string& name, const std::string& sourceFile, Scene* sceneScope = NULL );

  virtual ~AudioClip();

  const std::string& getSourceFile() const;

protected:
  void onLoad() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_AUDIO_AUDIO_CLIP_H__
