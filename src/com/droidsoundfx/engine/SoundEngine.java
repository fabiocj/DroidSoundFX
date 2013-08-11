package com.droidsoundfx.engine;

import java.util.ArrayList;

import com.droidsoundfx.effect.AudioProcessor;
import com.droidsoundfx.engine.settings.BitsPerSample;
import com.droidsoundfx.engine.settings.ChannelType;
import com.droidsoundfx.engine.settings.SamplingRate;

public final class SoundEngine {
	
	public enum Type {
		DEFAULT,
		CUSTOM
	}
	
	private SoundSettings outputSettings;
	private SoundSettings inputSettings;
	
	private boolean processing;
	
	private ArrayList<AudioProcessor> effectsList;
	
	private SoundManager soundManager;
	
	private SoundEngine( SoundSettings inputSettings, SoundSettings outputSettings) {
		this.outputSettings = outputSettings;
		this.inputSettings = inputSettings;
		this.effectsList = new ArrayList<AudioProcessor>();
		this.processing = false;
		
		this.soundManager = SoundManager.getInstance();
		
	}
	
	public boolean isProcessing() {
		return processing;
	}

//	public void setProcessing(boolean processing) {
//		this.processing = processing;
//	}

	private void throwIfProcessing() {
		if ( this.processing ) {
			throw new IllegalStateException( "Can't add/remove effects while audio is been processed" );
		}
	}
	
	public boolean startProcessing() {
		if ( ! this.processing ) {
			this.processing = true;
			return this.soundManager.startNativeProcessing();
		}
		
		return false;
	}
	
	public void stopProcessing() {
		if ( this.processing ) {
			this.processing = false;
			this.soundManager.stopNativeProcessing();
		}
	}
	
	public void startEngine() {
		this.soundManager.createNativeEngine( inputSettings, outputSettings );
	}
	
	public void stopEngine() {
		this.soundManager.destroyNativeEngine();
	}
	
	public boolean addEffect( AudioProcessor effect ) {
		this.throwIfProcessing();

		boolean added = this.soundManager.addEffect( effect );
		
		if ( added ) {
			if ( this.effectsList == null ) {
				this.effectsList = new ArrayList<AudioProcessor>();
			}
			
			this.effectsList.add( effect );
			return true;
		}
		
		return false;
	}
	
	public void removeEffect( AudioProcessor effect ) {
		this.throwIfProcessing();
		
		this.soundManager.removeEffect( effect );
		
		if ( this.effectsList != null ) {
			this.effectsList.remove( effect );
		}
		
	}

	public SamplingRate getPlayerSamplingRate() {
		return outputSettings.getSamplingRate();
	}

	public BitsPerSample getPlayerBitsPerSample() {
		return outputSettings.getBitsPerSample();
	}

	public ChannelType getPlayerChannelType() {
		return outputSettings.getChannelType();
	}
	
	public SamplingRate getRecorderSamplingRate() {
		return inputSettings.getSamplingRate();
	}

	public BitsPerSample getRecorderBitsPerSample() {
		return inputSettings.getBitsPerSample();
	}

	public ChannelType getRecorderChannelType() {
		return inputSettings.getChannelType();
	}
	
	public interface onStream {
		// TODO callback para stream do audio resultante
	}
	
	public static class Builder  {
		private SoundEngine.Type type;
		
		private SoundSettings inputSettings;
		private SoundSettings outputSettings;
		
		private boolean definingInputSettings = false;

		private boolean inputCalled = false;
		private boolean outputCalled = false;
		
		public Builder( SoundEngine.Type type ) {
			this.type = type;
		}
		
		void setCurrentStreamSettings( SoundSettings streamSettings ) {
			if ( definingInputSettings ) {
				this.inputSettings = streamSettings;
			} else {
				this.outputSettings = streamSettings;
			}
		}
		
		public SoundEngine create() {
			return new SoundEngine( inputSettings, outputSettings );
		}
		
		private void throwIfIsDefaultEngine() {
			if ( type == SoundEngine.Type.DEFAULT ) {
				throw new UnsupportedOperationException( "Can't redefine Default SoundEngine's settings." );
			}
		}
		
		public StreamBuilder input() {
			if ( inputCalled ) {
				throw new IllegalStateException( "Can't redefine Input settings." );
			}
			
			throwIfIsDefaultEngine();
			
			inputCalled = true;
			definingInputSettings = true;
			
			return new StreamBuilder( this );
		}
		
		public StreamBuilder output() {
			if ( outputCalled ) {
				throw new IllegalStateException( "Can't redefine Output settings." );
			}
			
			throwIfIsDefaultEngine();
			
			outputCalled = true;
			definingInputSettings = false;
			
			return new StreamBuilder( this );
		}
		
		public static class StreamBuilder {
			
			private SoundSettings streamSettings = new SoundSettings();
			
			private boolean samplingRateCalled = false;
			private boolean bitPerSampleCalled = false;
			private boolean channelCalled = false;
			
			private Builder builder;
			
			StreamBuilder(Builder builder) {
				this.builder = builder;
			}
			
			public StreamBuilder samplingRate( SamplingRate samplingRate ) {
				if ( samplingRateCalled ) {
					throw new IllegalStateException( "Can't redefine Sampling Rate." );
				}
				
				samplingRateCalled = true;
				
				streamSettings.setSamplingRate(samplingRate);
				return this;
			}
			
			public StreamBuilder bitsPerSample( BitsPerSample bitsPerSample ) {
				if ( bitPerSampleCalled ) {
					throw new IllegalStateException( "Can't redefine the number of Bits per Sample." );
				}
				
				bitPerSampleCalled = true;
				
				streamSettings.setBitsPerSample( bitsPerSample );
				return this;
			}
			
			public Builder channel( ChannelType channelType ) {
				if ( channelCalled ) {
					throw new IllegalStateException( "Can't redefine the number of Channels." );
				}
				
				channelCalled = true;
				
				streamSettings.setChannelType( channelType );
				
				builder.setCurrentStreamSettings( streamSettings );
				return builder;
				
//				return this;
			}
			
//			public Builder create() {
//				builder.setCurrentStreamSettings( streamSettings );
//				return builder;
//			}
			
		}
		
	}
	
	
}
