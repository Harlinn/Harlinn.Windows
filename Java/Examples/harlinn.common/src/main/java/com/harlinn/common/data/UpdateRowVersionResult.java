package com.harlinn.common.data;

import com.harlinn.common.util.Guid;

public class UpdateRowVersionResult {
	boolean success; 
	long rowVersion;
	
	public UpdateRowVersionResult() {
		
	}
	
	public UpdateRowVersionResult(boolean success,long rowVersion) {
		this.success = success;
		this.rowVersion = rowVersion;
	}
	
	public void reset() {
		this.success = false;
		this.rowVersion = 0;
	}
	
	public void assign(long rowVersion) {
		this.success = true;
		this.rowVersion = rowVersion;
	}
	
	public void assign(boolean success, long rowVersion) {
		this.success = success;
		this.rowVersion = rowVersion;
	}
	
	public boolean isSuccess() {
		return success;
	}

	public void setSuccess(boolean success) {
		this.success = success;
	}

	public long getRowVersion() {
		return rowVersion;
	}

	public void setRowVersion(long rowVersion) {
		this.rowVersion = rowVersion;
	}
	
}
