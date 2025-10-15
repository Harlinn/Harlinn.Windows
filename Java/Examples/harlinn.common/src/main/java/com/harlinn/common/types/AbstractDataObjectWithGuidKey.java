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
