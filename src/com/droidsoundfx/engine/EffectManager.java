package com.droidsoundfx.engine;

import java.util.ArrayList;

import com.droidsoundfx.effect.AudioProcessor;
import com.droidsoundfx.effect.NativeAudioProcessor;
import com.droidsoundfx.effect.natives.Chorus;
import com.droidsoundfx.effect.natives.Distortion;
import com.droidsoundfx.effect.natives.NativeEffectID;
import com.droidsoundfx.effect.natives.SimpleDelay;
import com.droidsoundfx.effect.natives.SimpleReverb;


public final class EffectManager {
	
	private static EffectManager instance;
	
	private SoundManager soundManager = SoundManager.getInstance();
	
	private ArrayList<AudioProcessor> audioProcessors;

	static {
		System.loadLibrary("DroidSoundFX");
	}
	
	private EffectManager() {
		audioProcessors = new ArrayList<AudioProcessor>();
	}
	
	public static EffectManager getInstance() {
		if ( instance == null) {
			instance = new EffectManager();
		}
		
		return instance;
	}
	
	public AudioProcessor registerEffect( NativeEffectID nativeEffectID ) {
		int nativeId = 0;
		
		NativeAudioProcessor nativeEffect;
		
		switch ( nativeEffectID ) {
			case SimpleDelay:
				nativeId = 0;
				nativeEffect = new SimpleDelay();
				break;
			case SimpleReverb:
				nativeId = 1;
				nativeEffect = new SimpleReverb();
				break;
			case Chorus:
				nativeId = 2;
				nativeEffect = new Chorus();
				break;
			case Distortion:
			default:
				nativeId = 3;
				nativeEffect = new Distortion();
		}
		
		int instanceId = soundManager.registerNativeEffect( nativeId );
		
		nativeEffect.setId( instanceId );
		
		this.audioProcessors.add( nativeEffect );
		
		return nativeEffect;
	}
	
	public void registerEffect( AudioProcessor effect ) {
		int instanceId = soundManager.registerJavaEffect( effect );
		effect.setId( instanceId );
		
		this.audioProcessors.add( effect );
	}
	
	// TODO registerEffect - para efeitos nativos do desenvolvedor
	
}
