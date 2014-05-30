#pragma once
#ifndef _ASYSTEM_H
#define _ASYSTEM_H

#include "ASCommon.h"
#include "fmod.h"
#include "fmod.hpp"

#define CHECK_FMOD_ERROR_VOID(result)  if (CheckFMODError(result)) return;

/*
 * 
 */ 
class AudioSystem
{
public:
  AudioSystem(void);
  virtual ~AudioSystem(void);

  bool CheckInitialized() const { return mInitialized; }

  void InitializeAudioAPI(int);
private:
  void DestroyAudioAPI();

  bool mInitialized;

  /*
   * FMOD Wrapper
   */
  bool CheckFMODError(FMOD_RESULT);

  /*
   * FMOD Variables
   */
  FMOD::System* mFMODSystem;
};

#endif // _ASYSTEM_H
