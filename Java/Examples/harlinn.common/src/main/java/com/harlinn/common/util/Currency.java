package com.harlinn.common.util;

import java.math.BigDecimal;

/**
 * A Currency number stored as a long, scaled by 10,000 to give a fixed-point 
 * number with 15 digits to the left of the decimal point and 4 digits to the right.
 */
public class Currency implements Cloneable, Comparable<Currency> {
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

	@Override 
	public Currency clone() throws CloneNotSupportedException {
		return fromValue(value);
	}
	
	@Override
	public int compareTo(Currency o) {
		return Long.compare(value, o.value);
	}
	public static int compare(Currency first, Currency second) {
		return first.compareTo(second);
	}
	
	@Override
	public boolean equals(Object obj) {
		if ( this == obj ) {
			return true;
		}
		if(obj == null ) {
			return false;
		}
		if ((obj instanceof Currency) == false ) {
            return false;
        }
		var other = (Currency)obj;
		return other.value == this.value; 
	}
	
}
