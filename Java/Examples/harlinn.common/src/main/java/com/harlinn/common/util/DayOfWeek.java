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
package com.harlinn.common.util;

/**
 * Specifies the day of the week.
 */
public enum DayOfWeek {
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday;
	
	public static DayOfWeek fromValue(int value) {
		switch(value) {
			case 0:
				return Sunday;
			case 1:
				return Monday;
			case 2:
				return Tuesday;
			case 3:
				return Wednesday;
			case 4:
				return Thursday;
			case 5:
				return Friday;
			case 6:
				return Saturday;
			default:
				throw new IllegalArgumentException("value");
		}
	}
}


