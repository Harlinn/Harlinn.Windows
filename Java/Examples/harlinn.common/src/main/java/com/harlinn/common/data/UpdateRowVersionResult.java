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
