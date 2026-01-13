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

import com.harlinn.common.io.BinaryReader;
import com.harlinn.common.io.BinaryWriter;

public abstract class AbstractDataObjectWithObjectKey<KeyT> extends AbstractDataObject {
	private KeyT id;
	
	protected AbstractDataObjectWithObjectKey(KeyT id)	{
		assert id != null : "id cannot be null";
		this.id = id;
	}

	protected AbstractDataObjectWithObjectKey(byte objectState, KeyT id) {
		super(objectState);
		assert id != null : "id cannot be null";
		this.id = id;
	}
	
	public KeyT getId() {
		return id;
	}
	
	public void setId(KeyT id) {
		assert id != null : "id cannot be null";
		if(getId().equals(id) == false) {
			this.id = id;
		}
	}
	
	protected void setId(KeyT id, boolean noPropertyChanged) {
		assert id != null : "id cannot be null";
		if(getId().equals(id) == false) {
			this.id = id;
			if(noPropertyChanged == false) {
				onPropertyChanged();
			}
		}
	}
	
	protected abstract void readKeyFrom(BinaryReader source);
	protected abstract void writeKeyTo(BinaryWriter destination);
	
	@Override
	public void readFrom(BinaryReader source) {
		super.readFrom(source);
		readKeyFrom(source);
	}
	
	@Override
	public void writeTo(BinaryWriter destination) {
		super.writeTo(destination);
		writeKeyTo(destination);
	}
	
	@Override
	public void assignTo(AbstractDataObject target)
	{
		super.assignTo(target);
		var targetObject = (AbstractDataObjectWithObjectKey<KeyT>)target;
		targetObject.id = this.id;
	}
	
}
