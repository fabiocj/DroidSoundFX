/*
 * Configuration.h
 *
 *  Created on: 11/04/2013
 *      Author: Leonardo
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <SLES/OpenSLES.h>

namespace DroidSoundFX {

class NativeSoundSettings {
	private:
		// TODO validar possiveis valores
		SLuint32 samplingRate;
		SLuint32 channels;
		SLuint16 bitsPerSample;

	public:
		NativeSoundSettings();
		virtual ~NativeSoundSettings();

		SLuint32 getChannels() const {
			return channels;
		}

		void setChannels(SLuint32 channels) {
			this->channels = channels;
		}

		SLuint32 getSamplingRate() const {
			return samplingRate;
		}

		void setSamplingRate(SLuint32 samplingRate) {
			this->samplingRate = samplingRate;
		}

		SLuint16 getBitsPerSample() const {
			return bitsPerSample;
		}

		void setBitsPerSample(SLuint16 bitsPerSample) {
			this->bitsPerSample = bitsPerSample;
		}
};

} /* namespace DroidSoundFX */
#endif /* CONFIGURATION_H_ */
