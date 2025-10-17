package com.harlinn.common.data;

import com.harlinn.common.util.Guid;

public class InsertGuidKeyResult {
	
	boolean success;
	Guid id;
	
	InsertGuidKeyResult() {
		
	}
	
	public InsertGuidKeyResult(boolean success, Guid id) {
		this.success = success;
		this.id = id;
	}
	
	public boolean isSuccess() {
		return success;
	}
	public void setSuccess(boolean success) {
		this.success = success;
	}
	public Guid getId() {
		return id;
	}
	public void setId(Guid id) {
		this.id = id;
	}
	
	public void reset() {
		this.success = false;
		this.id = null;
	}
	
	public void assign(Guid id) {
		this.success = true;
		this.id = id;
	}
	
	public void assign(boolean success, Guid id) {
		this.success = success;
		this.id = id;
	}
	

}
