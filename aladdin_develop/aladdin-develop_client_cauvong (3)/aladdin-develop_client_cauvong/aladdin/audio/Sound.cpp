#include "Sound.h"
#include "Audio.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2( ala::Sound, ala::Initializable, ala::Releasable)

Sound::Sound( const std::string& sourceFile ) : _sourceFile( sourceFile ), _cSound( NULL ) {}

Sound::~Sound() {
  if ( isInitialized() ) {
    ALA_ASSERT(isReleased());
  }
}

void Sound::initialize() {
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  initCSound();

  setToInitialized();
}

void Sound::release() {
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  releaseCSound();

  setToReleased();

  // destroy
  delete this;
}

const std::string& Sound::getSourceFile() const {
  return _sourceFile;
}

// ===================================================
// Platform specific
// ===================================================

CSound* Sound::getCSound() const {
  return _cSound;
}

void Sound::setCSound( CSound* cSound ) {
  _cSound = cSound;
}

void Sound::initCSound() {
  ala::Audio::get()->load( this );
}

void Sound::releaseCSound() {
  if ( _cSound != NULL ) {
    delete _cSound;
    _cSound = NULL;
  }
}
}
