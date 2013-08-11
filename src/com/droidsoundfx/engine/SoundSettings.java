package com.droidsoundfx.engine;

import com.droidsoundfx.engine.settings.BitsPerSample;
import com.droidsoundfx.engine.settings.ChannelType;
import com.droidsoundfx.engine.settings.SamplingRate;


class SoundSettings {
	private int nativeChannels;
	private int nativeSamplingRate;
	private int nativeBitsPerSample;
	
	private SamplingRate samplingRate = null;
	private BitsPerSample bitsPerSample = null;
	private ChannelType channelType = null;
	
	public void setChannelType(ChannelType channel) {
		this.channelType = channel;
		
		switch( channel ) {
		case Mono:
			this.nativeChannels = 1;
			break;
		case Stereo:
			this.nativeChannels = 2;
		}
	}
	
	public void setSamplingRate(SamplingRate samplingRate) {
		this.samplingRate = samplingRate;
		
		switch (samplingRate) {
		case _8000Hz:
			this.nativeSamplingRate = 8000;
			break;
		case _11025Hz:
			this.nativeSamplingRate = 11025;
			break;
		case _12000Hz:
			this.nativeSamplingRate = 12000;
			break;
		case _16000Hz:
			this.nativeSamplingRate = 16000;
			break;
		case _22050Hz:
			this.nativeSamplingRate = 22050;
			break;
		case _24000Hz:
			this.nativeSamplingRate = 24000;
			break;
		case _32000Hz:
			this.nativeSamplingRate = 32000;
			break;
		case _44100Hz:
			this.nativeSamplingRate = 44100;
			break;
		case _48000Hz:
			this.nativeSamplingRate = 48000;
			break;
		}
	}
	
	public void setBitsPerSample(BitsPerSample bitsPerSample) {
		this.bitsPerSample = bitsPerSample;
		
		 switch (bitsPerSample) {
		case _8:
			this.nativeBitsPerSample = 8;
			break;
		case _16:
			this.nativeBitsPerSample = 16;
			break;
		}
	}

	public int getNativeChannels() {
		return nativeChannels;
	}

	public int getNativeSamplingRate() {
		return nativeSamplingRate;
	}

	public int getNativeBitsPerSample() {
		return nativeBitsPerSample;
	}

	public SamplingRate getSamplingRate() {
		return samplingRate;
	}

	public BitsPerSample getBitsPerSample() {
		return bitsPerSample;
	}

	public ChannelType getChannelType() {
		return channelType;
	}
	
}