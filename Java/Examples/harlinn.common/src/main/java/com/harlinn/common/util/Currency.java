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

import java.math.BigDecimal;

/**
 * A Currency number stored as a long, scaled by 10,000 to give a fixed-point 
 * number with 15 digits to the left of the decimal point and 4 digits to the right.
 */
public class Currency implements Cloneable, Comparable<Currency> {
	public static final int BYTES = 8;
	
	public static final long Scale = 10000;
	static final float ScaleFloat = 10000.0f;
	static final double ScaleDouble = 10000.0;
	static final BigDecimal ScaleDecimal = new BigDecimal(10000.0);
	
	public static final Currency MIN_VALUE = Currency.fromValue( Long.MIN_VALUE );
	public static final Currency MAX_VALUE = Currency.fromValue( Long.MAX_VALUE );
	
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
