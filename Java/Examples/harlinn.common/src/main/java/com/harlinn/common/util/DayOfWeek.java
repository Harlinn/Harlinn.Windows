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


