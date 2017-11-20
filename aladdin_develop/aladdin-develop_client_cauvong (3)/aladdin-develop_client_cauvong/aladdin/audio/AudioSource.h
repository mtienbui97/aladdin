#ifndef __ALADDIN_AUDIO_AUDIO_SOURCE_H__
#define __ALADDIN_AUDIO_AUDIO_SOURCE_H__

#include "AudioInclude.h"
#include "AudioClip.h"
#include "Sound.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(AudioSource, ala::GameObjectComponent)
private:
  AudioClip* _audioClip;
  Sound* _sound;
  bool _loop;

public:
  AudioSource( GameObject* gameObject, AudioClip* audioClip, const std::string& name = "" );

  AudioSource( GameObject* gameObject, const std::string& audioClipName, const std::string& name = "" );

  virtual ~AudioSource();

  void pause();

  void stop();

  void play();

  void playOneShot();

  void unPause();

  void setAudioClip( AudioClip* clip );

  AudioClip* getAudioClip() const;

  Sound* getSound() const;

  void setLoop( const bool val );

  bool isLoop() const;

protected:
  void onInitialize() override;

  void onRelease() override;
};
}

#endif //!__ALADDIN_AUDIO_AUDIO_SOURCE_H__
