package com.droidsoundfx.effect.natives;

import com.droidsoundfx.effect.NativeAudioProcessor;

public class Distortion extends NativeAudioProcessor {
	
	public static final NativeEffectID NativeID = NativeEffectID.Distortion;
	
	public static final int INT_DRY = 1;
	public static final int INT_DISTORTED = 2;
	public static final int INT_THRESHOLD = 3;
	public static final int INT_CLAMP = 4;
	public static final int BOOL_GATE = 5;
	
	public static final int MAX_DRY_DISTORTED = 100;
	public static final int MIN_DRY_DISTORTED = 1;
	
	public static final int MAX_CLAMP_THRESHOLD = Short.MAX_VALUE / 10;
	public static final int MIN_CLAMP_THRESHOLD = 0;
	
	public boolean isGateEnabled() {
		return this.getBooleanParameter( BOOL_GATE );
	}
	
	public void setGateEnabled( boolean enabled ) {
		this.setParameter( BOOL_GATE, enabled );
	}
	
	public int getDry() {
		return this.getIntParameter( INT_DRY );
	}
	
	public void setDry( int dry ) {
		this.setParameter( INT_DRY, dry );
	}
	
	public int getDistortion() {
		return this.getIntParameter( INT_DISTORTED );
	}
	
	public void setDistortion( int distortion ) {
		this.setParameter( INT_DISTORTED, distortion );
	}
	
	public int getThresholdLevel() {
		return this.getIntParameter( INT_THRESHOLD );
	}

	public void setThresholdLevel( int threshold ) {
		this.setParameter( INT_THRESHOLD, threshold );
	}
	
	public int getClampLevel() {
		return this.getIntParameter( INT_CLAMP );
	}
	
	public void setClampLevel( int clamp ) {
		this.setParameter( INT_CLAMP, clamp );
	}
	
}
