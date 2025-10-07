package com.harlinn.common.util;

public enum DatePart {
	Year,
	DayOfYear,
	Month,
	Day;
	
	public static DatePart fromValue(int value) {
		switch(value) {
			case 0:
				return Year;
			case 1:
				return DayOfYear;
			case 2:
				return Month;
			case 3:
				return Day;
			default:
				throw new IllegalArgumentException("value");
		}
	}
	
}
