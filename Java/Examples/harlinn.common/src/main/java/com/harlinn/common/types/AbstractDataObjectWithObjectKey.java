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
