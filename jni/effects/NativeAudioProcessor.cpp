/*
 * BaseEffect.cpp
 *
 *  Created on: 25/04/2013
 *      Author: Leonardo
 */

#include "NativeAudioProcessor.h"

namespace DroidSoundFX {

NativeAudioProcessor::NativeAudioProcessor() {
	enabled = true;
}

NativeAudioProcessor::~NativeAudioProcessor() {
}

bool NativeAudioProcessor::isEnabled() {
	return enabled;
}

void NativeAudioProcessor::setEnabled( bool enabled ) {
	this->enabled = enabled;
}

int NativeAudioProcessor::getId() {
	return this->id;
}

void NativeAudioProcessor::setId( int id ) {
	this->id = id;
}

void NativeAudioProcessor::changeParameter( int parameterId, jvalue value ) {
	this->setParameter( parameterId, value );
	this->onParameterChange();
}

} /* namespace DroidSoundFX */
