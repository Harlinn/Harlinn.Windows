package com.harlinn.common.util;

import java.math.BigDecimal;

/**
 * A Currency number stored as a long, scaled by 10,000 to give a fixed-point 
 * number with 15 digits to the left of the decimal point and 4 digits to the right.
 */
public class Currency {
	public static final long Scale = 10000;
	static final float ScaleFloat = 10000.0f;
	static final double ScaleDouble = 10000.0;
	static final BigDecimal ScaleDecimal = new BigDecimal(10000.0);
	long value;
	
	public Currency() {
	}
	
	public Currency(long value) {
		this.value = value * Scale;
	}
	
	public Currency(float value) {
		this.value = (long)(value * ScaleFloat);
	}
	
	public Currency(double value) {
		this.value = (long)(value * ScaleDouble);
	}
	
	public static Currency fromValue(long value) {
		var result = new Currency();
		result.value = value;
		return result;
	}
	
	public long getValue() {
		return value;
	}
	
}
