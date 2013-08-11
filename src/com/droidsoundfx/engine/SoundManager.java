package com.droidsoundfx.engine;

import android.util.Log;

import com.droidsoundfx.effect.AudioProcessor;

final class SoundManager {
	
	private static SoundManager instance;
	
	private SoundManager() {
		
	}
	
	public static SoundManager getInstance() {
		if ( instance == null ) {
			instance = new SoundManager();
		}
		
		return instance;
	}
	
	public native boolean startNativeProcessing();
	public native void stopNativeProcessing();
	public native void createNativeEngine( SoundSettings inputSettings, SoundSettings outputSettings );
	public native void destroyNativeEngine();
	
	// TODO metodos nativos add e remove effects:
	// TODO corrigir esses metodos de add e criação:
	public native int registerNativeEffect( int nativeEffectID );
	public native int registerJavaEffect( AudioProcessor effect );
	
	public boolean addEffect( AudioProcessor effect ) {
		Log.d("teste", "SoundManager.java, addEffect");
		return this.addEffect( effect.getId() );
	}
	
	public void removeEffect(AudioProcessor effect ) {
		this.removeEffect( effect.getId() );
	}
	
	// TODO addEffect ao SoundCore:
	private native boolean addEffect( int effectId );
	private native void removeEffect(  int effectId );

}
