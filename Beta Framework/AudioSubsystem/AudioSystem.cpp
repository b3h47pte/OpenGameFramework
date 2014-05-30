#include "AudioSystem.h"
#include "fmod_errors.h"

using namespace std;

AudioSystem::AudioSystem(void): mInitialized(false) {
}


AudioSystem::~AudioSystem(void) {
  DestroyAudioAPI();
}

/*
 * Sets up FMOD for utilization.
 */
void AudioSystem::InitializeAudioAPI(int inMaxChannels) {
  FMOD_RESULT result;
  result = FMOD::System_Create(&mFMODSystem);
  CHECK_FMOD_ERROR_VOID(result);

  result = mFMODSystem->init(inMaxChannels, FMOD_INIT_NORMAL, NULL);
}

/*
 * Closes FMOD.
 */
void AudioSystem::DestroyAudioAPI() {
  FMOD_RESULT result;
  result = mFMODSystem->close();
  CHECK_FMOD_ERROR_VOID(result);
  result = mFMODSystem->release();
  CHECK_FMOD_ERROR_VOID(result);
}

/*
 * Determine if an error occurred.
 */
bool AudioSystem::CheckFMODError(FMOD_RESULT result) {
  if (result != FMOD_OK) {
    cout << "FMOD Error " << result << " - " << FMOD_ErrorString(result) << endl;
    return true;
  }
  return false;
}
