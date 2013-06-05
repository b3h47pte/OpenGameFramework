#include "ASApi.h"


/*
 *
 */
AudioSystem* InitializeAudioSubsystem() {
	static AudioSystem* sys = [] () {
		AudioSystem* newSys = new AudioSystem();
		if (!newSys) return (AudioSystem*)(NULL);
		return newSys;
	}();
	return sys;
}