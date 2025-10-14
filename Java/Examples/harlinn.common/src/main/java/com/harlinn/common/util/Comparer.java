package com.harlinn.common.util;

public class Comparer {
	
	public static int compareBoolean(boolean first, boolean second) {
		return Boolean.compare(first, second);
	}
	
	public static int compareNullableBoolean(Boolean first, Boolean second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsBoolean(boolean first, boolean second) {
		return first == second;
	}
	public static boolean equalsNullableBoolean(Boolean first, Boolean second) {
		return compareNullableBoolean(first, second) == 0;
	}
	
	public static int compareChar(char first, char second) {
		return Character.compare(first, second);
	}
	
	public static int compareNullableChar(Character first, Character second) {
		if(first != null) {
			if(second != null) {
				return Character.compare(first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsChar(char first, char second) {
		return first == second;
	}
	public static boolean equalsNullableChar(Character first, Character second) {
		return compareNullableChar(first, second) == 0;
	}
	
	
	public static int compareUInt8(byte first, byte second) {
		return Byte.compareUnsigned(first, second);
	}
	
	public static int compareNullableUInt8(Byte first, Byte second) {
		if(first != null) {
			if(second != null) {
				return Byte.compareUnsigned(first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsUInt8(byte first, byte second) {
		return first == second;
	}
	public static boolean equalsNullableUInt8(Byte first, Byte second) {
		return compareNullableUInt8(first, second) == 0;
	}
	
	public static int compareInt8(byte first, byte second) {
		return Byte.compare(first, second);
	}
	
	public static int compareNullableInt8(Byte first, Byte second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsInt8(byte first, byte second) {
		return first == second;
	}
	public static boolean equalsNullableInt8(Byte first, Byte second) {
		return compareNullableInt8(first, second) == 0;
	}
	
	public static int compareUInt16(short first, short second) {
		return Short.compareUnsigned(first, second);
	}
	
	public static int compareNullableUInt16(Short first, Short second) {
		if(first != null) {
			if(second != null) {
				return Short.compareUnsigned(first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsUInt16(short first, short second) {
		return first == second;
	}
	public static boolean equalsNullableUInt16(Short first, Short second) {
		return compareNullableUInt16(first, second) == 0;
	}
	
	public static int compareInt16(short first, short second) {
		return Short.compare(first, second);
	}
	
	public static int compareNullableInt16(Short first, Short second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsInt16(short first, short second) {
		return first == second;
	}
	public static boolean equalsNullableInt16(Short first, Short second) {
		return compareNullableInt16(first, second) == 0;
	}
	
	public static int compareUInt32(int first, int second) {
		return Integer.compareUnsigned(first, second);
	}
	
	public static int compareNullableUInt32(Integer first, Integer second) {
		if(first != null) {
			if(second != null) {
				return Integer.compareUnsigned(first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsUInt32(int first, int second) {
		return first == second;
	}
	public static boolean equalsNullableUInt32(Integer first, Integer second) {
		return compareNullableUInt32(first, second) == 0;
	}
	
	public static int compareInt32(int first, int second) {
		return Integer.compare(first, second);
	}
	
	public static int compareNullableInt32(Integer first, Integer second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsInt32(int first, int second) {
		return first == second;
	}
	public static boolean equalsNullableInt32(Integer first, Integer second) {
		return compareNullableInt32(first, second) == 0;
	}
	
	public static int compareUInt64(long first, long second) {
		return Long.compareUnsigned(first, second);
	}
	
	public static int compareNullableUInt64(Long first, Long second) {
		if(first != null) {
			if(second != null) {
				return Long.compareUnsigned(first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsUInt64(long first, long second) {
		return first == second;
	}
	public static boolean equalsNullableUInt64(Long first, Long second) {
		return compareNullableUInt64(first, second) == 0;
	}
	
	public static int compareInt64(long first, long second) {
		return Long.compare(first, second);
	}
	
	public static int compareNullableInt64(Long first, Long second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsInt64(long first, long second) {
		return first == second;
	}
	public static boolean equalsNullableInt64(Long first, Long second) {
		return compareNullableInt64(first, second) == 0;
	}
	
	public static int compareSingle(float first, float second) {
		if(Float.isNaN(first) == false) {
			if(Float.isNaN(second) == false) {
				return Float.compare(first, second); 
			}
			return 1;
		}
		else if(Float.isNaN(second) == false) {
			return -1;
		}
		return 0;
	}
	
	public static int compareNullableSingle(Float first, Float second) {
		if(first != null) {
			if(second != null) {
				return compareSingle( first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}

	
	public static boolean equalsSingle(float first, float second) {
		return compareSingle(first, second) == 0;
	}
	public static boolean equalsNullableSingle(Float first, Float second) {
		return compareNullableSingle(first, second) == 0;
	}

	
	public static int compareDouble(double first, double second) {
		if(Double.isNaN(first) == false) {
			if(Double.isNaN(second) == false) {
				return Double.compare(first, second); 
			}
			return 1;
		}
		else if(Double.isNaN(second) == false) {
			return -1;
		}
		return 0;
		
	}
	
	public static int compareNullableDouble(Double first, Double second) {
		if(first != null) {
			if(second != null) {
				return compareDouble( first, second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsDouble(double first, double second) {
		return compareDouble(first, second) == 0;
	}
	public static boolean equalsNullableDouble(Double first, Double second) {
		return compareNullableDouble(first, second) == 0;
	}
	
	public static int compareDateTime(DateTime first, DateTime second) {
		return DateTime.compare(first, second);
	}
	
	public static int compareNullableDateTime(DateTime first, DateTime second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsDateTime(DateTime first, DateTime second) {
		return compareDateTime(first, second) == 0;
	}
	public static boolean equalsNullableDateTime(DateTime first, DateTime second) {
		return compareNullableDateTime(first, second) == 0;
	}
	
	public static int compareTimeSpan(TimeSpan first, TimeSpan second) {
		return TimeSpan.compare(first, second);
	}
	
	public static int compareNullableTimeSpan(TimeSpan first, TimeSpan second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsTimeSpan(TimeSpan first, TimeSpan second) {
		return compareTimeSpan(first, second) == 0;
	}
	public static boolean equalsNullableTimeSpan(TimeSpan first, TimeSpan second) {
		return compareNullableTimeSpan(first, second) == 0;
	}
	
	public static int compareCurrency(Currency first, Currency second) {
		return Currency.compare(first, second);
	}
	
	public static int compareNullableCurrency(Currency first, Currency second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsCurrency(Currency first, Currency second) {
		return compareCurrency(first, second) == 0;
	}
	public static boolean equalsNullableCurrency(Currency first, Currency second) {
		return compareNullableCurrency(first, second) == 0;
	}
	
	
	public static int compareGuid(Guid first, Guid second) {
		return Guid.compare(first, second);
	}
	
	public static int compareNullableGuid(Guid first, Guid second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsGuid(Guid first, Guid second) {
		return compareGuid(first, second) == 0;
	}
	public static boolean equalsNullableGuid(Guid first, Guid second) {
		return compareNullableGuid(first, second) == 0;
	}
	
	public static int compareString(String first, String second) {
		return first.compareTo(second);
	}
	
	public static int compareNullableString(String first, String second) {
		if(first != null) {
			if(second != null) {
				return first.compareTo(second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsString(String first, String second) {
		return compareString(first, second) == 0;
	}
	public static boolean equalsNullableString(String first, String second) {
		return compareNullableString(first, second) == 0;
	}
	
	public static int compareUInt8Array(byte[] first, byte[] second) {
		return java.util.Arrays.compare(first, second);
	}
	
	public static int compareNullableUInt8Array(byte[] first, byte[] second) {
		if(first != null) {
			if(second != null) {
				return compareUInt8Array(first,second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	public static boolean equalsUInt8Array(byte[] first, byte[] second) {
		return compareUInt8Array(first, second) == 0;
	}
	public static boolean equalsNullableUInt8Array(byte[] first, byte[] second) {
		return compareNullableUInt8Array(first, second) == 0;
	}
	
	
	public static int compareUInt8ListArray(byte[][] first, byte[][] second) {
		var cmopareCount = Math.min(first.length, second.length);
		for(int i = 0; i < cmopareCount; i++) {
			var f = first[i];
			var s = second[i];
			var r = compareNullableUInt8Array(f,s);
			if(r != 0) {
				return r;
			}
		}
		if(first.length > second.length) {
			return 1;
		}
		else if(first.length < second.length) {
			return -1;
		}
		else {
			return 0;
		}
	}
	
	public static int compareNullableUInt8ListArray(byte[][] first, byte[][] second) {
		if(first != null) {
			if(second != null) {
				return compareUInt8ListArray(first,second); 
			}
			return 1;
		}
		else if(second != null) {
			return -1;
		}
		return 0;
	}
	
	
}
