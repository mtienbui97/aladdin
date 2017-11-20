#include "AudioClip.h"
#include "Audio.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::AudioClip, ala::GameResource )

AudioClip::AudioClip( const std::string& name, const std::string& sourceFile, Scene* sceneScope )
  : GameResource( name, sceneScope ),
    _sourceFile( sourceFile ) {}

AudioClip::~AudioClip() {}

const std::string& AudioClip::getSourceFile() const {
  return _sourceFile;
}

void AudioClip::onLoad() {
}

void AudioClip::onRelease() {}
}
