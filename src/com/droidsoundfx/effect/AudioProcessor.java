package com.droidsoundfx.effect;

public abstract class AudioProcessor {

	protected int id = -1;
	private boolean enabled = true;
	
	public final int getId() {
		return id;
	}
	
	public final void setId(int id) {
		this.id = id;
	}
	
	public final boolean isEnabled() {
		return enabled;
	}

	public final void setEnabled( boolean enabled ) {
		this.enabled = enabled;
		this.setNativeEnabled( id, enabled );
	}
	
	public abstract void process( float buffer[] );
	
	public native void setNativeEnabled( int effectId, boolean enabled );
	
	public void onChangeParameter() {}
	
	// SETTERS Parameters:
	public void setParameter( int parameterId, Object value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, byte value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, char value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, double value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, float value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, int value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, long value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, short value  ) {
		this.onChangeParameter();
	}
	public void setParameter( int parameterId, boolean value  ) {
		this.onChangeParameter();
	}
	
	// GETTERS Parameters:
	public Object getObjectParameter( int parameterId ) {
		return this;
	}
	public byte getByteParameter( int parameterId ) {
		return 0;
	}
	public char getCharParameter( int parameterId ) {
		return '0';
	}
	public double getDoubleParameter( int parameterId ) {
		return 0;
	}
	public float getFloatParameter( int parameterId ) {
		return 0;
	}
	public int getIntParameter( int parameterId ) {
		return 0;
	}
	public long getLongParameter( int parameterId ) {
		return 0;
	}
	public short getShortParameter( int parameterId ) {
		return 0;
	}
	public boolean getBooleanParameter( int parameterId ) {
		return false;
	}
	
}
