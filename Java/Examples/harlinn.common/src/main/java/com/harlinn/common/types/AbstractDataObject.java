/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
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
