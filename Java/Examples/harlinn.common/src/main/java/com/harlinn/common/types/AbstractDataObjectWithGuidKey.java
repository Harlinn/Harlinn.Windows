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
import com.harlinn.common.util.Guid;

public abstract class AbstractDataObjectWithGuidKey extends AbstractDataObjectWithObjectKey<Guid> {

	protected AbstractDataObjectWithGuidKey( ) {
		super(ObjectState.Unknown, new Guid());
	}
	
	protected AbstractDataObjectWithGuidKey(byte objectState, Guid id) {
		super(objectState, id);
	}

	@Override
	protected void readKeyFrom(BinaryReader source) {
		var key = source.readGuid();
		setId(key, true);
	}

	@Override
	protected void writeKeyTo(BinaryWriter destination) {
		var key = getId();
		destination.writeGuid(key);
	}
	
	@Override
	public boolean equals(Object obj) {
		if ( this == obj ) {
			return true;
		}
		if(obj == null ) {
			return false;
		}
		if ((obj instanceof AbstractDataObjectWithGuidKey) == false ) {
            return false;
        }
		var other = (AbstractDataObjectWithGuidKey)obj;
		return other.getId().equals(getId()); 
	}


}
