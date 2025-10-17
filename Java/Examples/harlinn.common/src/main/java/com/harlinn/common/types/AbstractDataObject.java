package com.harlinn.common.types;


import java.io.Serializable;

import com.harlinn.common.io.BinaryReader;
import com.harlinn.common.io.BinaryWriter;

public abstract class AbstractDataObject implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 8454292752307508627L;
	byte objectState = ObjectState.Unknown;
	
	protected AbstractDataObject()	{
	}

	protected AbstractDataObject(byte objectState)	{
		this.objectState = objectState;
	}

	protected final void onPropertyChanged() {
	    if (objectState == ObjectState.Stored || objectState == ObjectState.ConcurrencyConflict)
	    {
	    	objectState = ObjectState.Changed;
	    }
	}
	
	public abstract int getObjectType();
	
	public byte getObjectState() {
		return objectState;
	}
	public void setObjectState(byte objectState) {
		this.objectState = objectState;
	}
	
	public void readFrom(BinaryReader source) {
		objectState = source.readUInt8();
	}
	
	public void writeTo(BinaryWriter destination) {
		var objectType = getObjectType();
		destination.writeInt32(objectType);
		destination.writeUInt8(objectState);
	}
	
	protected abstract AbstractDataObject create();

	public void assignTo(AbstractDataObject target)
	{
	    target.objectState = this.objectState;
	}
	
	public AbstractDataObject clone() {
	    var result = create();
	    assignTo(result);
	    return result;
	}
	
	

}
