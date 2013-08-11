package com.droidsoundfx.effect;

public class NativeAudioProcessor extends AudioProcessor {
	
	@Override
	public void setParameter( int parameterId, Object value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, byte value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, char value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, double value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, float value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, int value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, long value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter( int parameterId, short value  ) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	@Override
	public void setParameter(int parameterId, boolean value) {
		this.setEffectParameter( id, parameterId, value );
	}
	
	private native void setEffectParameter(int effectId, int parameterId, Object value);
	private native void setEffectParameter(int effectId, int parameterId, byte value);
	private native void setEffectParameter(int effectId, int parameterId, char value);
	private native void setEffectParameter(int effectId, int parameterId, double value);
	private native void setEffectParameter(int effectId, int parameterId, float value);
	private native void setEffectParameter(int effectId, int parameterId, int value);
	private native void setEffectParameter(int effectId, int parameterId, long value);
	private native void setEffectParameter(int effectId, int parameterId, short value);
	private native void setEffectParameter(int effectId, int parameterId, boolean value);
	
	@Override
	public Object getObjectParameter( int parameterId ) {
		return this.getObjectParameter( id, parameterId );
	}
	
	@Override
	public byte getByteParameter( int parameterId ) {
		return this.getByteParameter( id, parameterId );
	}
	
	@Override
	public char getCharParameter( int parameterId ) {
		return this.getCharParameter( id, parameterId );
	}
	
	@Override
	public double getDoubleParameter( int parameterId ) {
		return this.getDoubleParameter( id, parameterId );
	}
	
	@Override
	public float getFloatParameter( int parameterId ) {
		return this.getFloatParameter( id, parameterId );
	}
	
	@Override
	public int getIntParameter( int parameterId ) {
		return this.getIntParameter( id, parameterId );
	}
	
	@Override
	public long getLongParameter( int parameterId ) {
		return this.getLongParameter( id, parameterId );
	}
	
	@Override
	public short getShortParameter( int parameterId ) {
		return this.getShortParameter( id, parameterId );
	}
	
	@Override
	public boolean getBooleanParameter( int parameterId ) {
		return this.getBooleanParameter( id, parameterId );
	}
	
	private native Object getObjectParameter( int effectId, int parameterId );
	private native byte getByteParameter( int effectId, int parameterId );
	private native char getCharParameter( int effectId, int parameterId );
	private native double getDoubleParameter( int effectId, int parameterId );
	private native float getFloatParameter( int effectId, int parameterId );
	private native int getIntParameter( int effectId, int parameterId );
	private native long getLongParameter( int effectId, int parameterId );
	private native short getShortParameter( int effectId, int parameterId );
	private native boolean getBooleanParameter( int effectId, int parameterId );
	
	@Override
	public void process(float[] buffer) {
		// TODO melhorar mensagem:
		throw new UnsupportedOperationException( "This implementation can't process audio here." );
	}
	
}
