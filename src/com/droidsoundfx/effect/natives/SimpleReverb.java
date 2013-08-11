package com.droidsoundfx.effect.natives;

import com.droidsoundfx.effect.NativeAudioProcessor;

public final class SimpleReverb extends NativeAudioProcessor {
	
	private static final int INT_ECHODELAY = 0;
	private static final int INT_ECHORATIO = 1;
	private static final int INT_SAMPLINGRATE = 2;
	
	public static final int MAX_ECHODELAY = 300;
	public static final int MIN_ECHODELAY = 50;
	
	public static final int MAX_ECHORATIO = 100;
	public static final int MIN_ECHORATIO = 1;
	
	public static final NativeEffectID NativeID = NativeEffectID.SimpleReverb;
	
	public int getEchoDelay() {
		return this.getIntParameter( INT_ECHODELAY );
	}
	
	public void setEchoDelay( int echoDelay ) {
		this.setParameter( INT_ECHODELAY, echoDelay );
	}
	
	public int getEchoRatio() {
		return this.getIntParameter( INT_ECHORATIO );
	}
	
	public void setEchoRatio( int echoRatio ) {
		this.setParameter( INT_ECHORATIO, echoRatio );
	}
	
	public int getSamplingRate() {
		return this.getIntParameter( INT_SAMPLINGRATE );
	}
	
	public void setSamplingRate( int samplingRate ) {
		this.setParameter( INT_SAMPLINGRATE, samplingRate );
	}
}
