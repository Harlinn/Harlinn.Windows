package com.harlinn.common.serialization;

public class DataType {

    public final static byte Unknown = 0;
    public final static byte Eos = 1;
    public final static byte Null = 2;
    public final static byte BooleanTrue = 3;
    public final static byte BooleanFalse = 4;

    public final static byte ZeroChar = 5;
    public final static byte OneChar = 6;
    public final static byte MaxChar = 7;
    public final static byte Char = 8;

    public final static byte ZeroByte = 9;
    public final static byte OneByte = 10;
    public final static byte MaxByte = 11;
    public final static byte Byte = 12;

    public final static byte MinSByte = 13;
    public final static byte MinusOneSByte = 14;
    public final static byte ZeroSByte = 15;
    public final static byte OneSByte = 16;
    public final static byte MaxSByte = 17;
    public final static byte SByte = 18;

    public final static byte MinInt16 = 19;
    public final static byte MinusOneInt16 = 20;
    public final static byte ZeroInt16 = 21;
    public final static byte OneInt16 = 22;
    public final static byte MaxInt16 = 23;
    public final static byte Int16 = 24;

    public final static byte ZeroUInt16 = 25;
    public final static byte OneUInt16 = 26;
    public final static byte MaxUInt16 = 27;
    public final static byte UInt16 = 28;

    public final static byte MinInt32 = 29;
    public final static byte MinusOneInt32 = 30;
    public final static byte ZeroInt32 = 31;
    public final static byte OneInt32 = 32;
    public final static byte MaxInt32 = 33;
    public final static byte Int32 = 34;

    public final static byte ZeroUInt32 = 35;
    public final static byte OneUInt32 = 36;
    public final static byte MaxUInt32 = 37;
    public final static byte UInt32 = 38;

    public final static byte MinInt64 = 39;
    public final static byte MinusOneInt64 = 40;
    public final static byte ZeroInt64 = 41;
    public final static byte OneInt64 = 42;
    public final static byte MaxInt64 = 43;
    public final static byte Int64 = 44;

    public final static byte ZeroUInt64 = 45;
    public final static byte OneUInt64 = 46;
    public final static byte MaxUInt64 = 47;
    public final static byte UInt64 = 48;

    public final static byte SingleNegativeInfinity = 49;
    public final static byte MinSingle = 50;
    public final static byte MinusOneSingle = 51;
    public final static byte ZeroSingle = 52;
    public final static byte OneSingle = 53;
    public final static byte MaxSingle = 54;
    public final static byte SinglePositiveInfinity = 55;
    public final static byte SingleNaN = 56;
    public final static byte Single = 57;

    public final static byte DoubleNegativeInfinity = 58;
    public final static byte MinDouble = 59;
    public final static byte MinusOneDouble = 60;
    public final static byte ZeroDouble = 61;
    public final static byte OneDouble = 62; 
    public final static byte MaxDouble = 63;
    public final static byte DoublePositiveInfinity = 64;
    public final static byte DoubleNaN = 65;
    public final static byte Double = 66;

    public final static byte DateTime = 67;
    public final static byte ZeroDateTime = 68;

    public final static byte TimeSpan = 69;
    public final static byte ZeroTimeSpan = 70;

    public final static byte Guid = 71;
    public final static byte EmptyGuid = 72;

    public final static byte String = 73;
    public final static byte EmptyString = 74;
    
    public final static byte MinCurrency = 75;
    public final static byte MinusOneCurrency = 76;
    public final static byte ZeroCurrency = 77;
    public final static byte OneCurrency = 78;
    public final static byte MaxCurrency = 79;
    public final static byte Currency = 80;

    public final static byte SmallBooleanArray = (byte) 0x80;
    public final static byte BooleanArray = (byte) 0x81;
    public final static byte LargeBooleanArray = (byte) 0x82;
    public final static byte EmptyBooleanArray = (byte) 0x83;

    public final static byte SmallCharArray = (byte) 0x84;
    public final static byte CharArray = (byte) 0x85;
    public final static byte LargeCharArray = (byte) 0x86;
    public final static byte EmptyCharArray = (byte) 0x87;

    public final static byte SmallSByteArray = (byte) 0x88;
    public final static byte SByteArray = (byte) 0x89;
    public final static byte LargeSByteArray = (byte) 0x8A;
    public final static byte EmptySByteArray = (byte) 0x8B;

    public final static byte SmallByteArray = (byte) 0x8C;
    public final static byte ByteArray = (byte) 0x8D;
    public final static byte LargeByteArray = (byte) 0x8E;
    public final static byte EmptyByteArray = (byte) 0x8F;

    public final static byte SmallInt16Array = (byte) 0x90;
    public final static byte Int16Array = (byte) 0x91;
    public final static byte LargeInt16Array = (byte) 0x92;
    public final static byte EmptyInt16Array = (byte) 0x93;

    public final static byte SmallUInt16Array = (byte) 0x94;
    public final static byte UInt16Array = (byte) 0x95;
    public final static byte LargeUInt16Array = (byte) 0x96;
    public final static byte EmptyUInt16Array = (byte) 0x97;

    public final static byte SmallInt32Array = (byte) 0x98;
    public final static byte Int32Array = (byte) 0x99;
    public final static byte LargeInt32Array = (byte) 0x9A;
    public final static byte EmptyInt32Array = (byte) 0x9B;

    public final static byte SmallUInt32Array = (byte) 0x9C;
    public final static byte UInt32Array = (byte) 0x9D;
    public final static byte LargeUInt32Array = (byte) 0x9E;
    public final static byte EmptyUInt32Array = (byte) 0x9F;

    public final static byte SmallInt64Array = (byte) 0xA0;
    public final static byte Int64Array = (byte) 0xA1;
    public final static byte LargeInt64Array = (byte) 0xA2;
    public final static byte EmptyInt64Array = (byte) 0xA3;

    public final static byte SmallUInt64Array = (byte) 0xA4;
    public final static byte UInt64Array = (byte) 0xA5;
    public final static byte LargeUInt64Array = (byte) 0xA6;
    public final static byte EmptyUInt64Array = (byte) 0xA7;

    public final static byte SmallSingleArray = (byte) 0xA8;
    public final static byte SingleArray = (byte) 0xA9;
    public final static byte LargeSingleArray = (byte) 0xAA;
    public final static byte EmptySingleArray = (byte) 0xAB;

    public final static byte SmallDoubleArray = (byte) 0xAC;
    public final static byte DoubleArray = (byte) 0xAD;
    public final static byte LargeDoubleArray = (byte) 0xAE;
    public final static byte EmptyDoubleArray = (byte) 0xAF;

    public final static byte SmallDateTimeArray = (byte) 0xB0;
    public final static byte DateTimeArray = (byte) 0xB1;
    public final static byte LargeDateTimeArray = (byte) 0xB2;
    public final static byte EmptyDateTimeArray = (byte) 0xB3;

    public final static byte SmallTimeSpanArray = (byte) 0xB4;
    public final static byte TimeSpanArray = (byte) 0xB5;
    public final static byte LargeTimeSpanArray = (byte) 0xB6;
    public final static byte EmptyTimeSpanArray = (byte) 0xB7;

    public final static byte SmallGuidArray = (byte) 0xB8;
    public final static byte GuidArray = (byte) 0xB9;
    public final static byte LargeGuidArray = (byte) 0xBA;
    public final static byte EmptyGuidArray = (byte) 0xBB;

    public final static byte SmallStringArray = (byte) 0xBC;
    public final static byte StringArray = (byte) 0xBD;
    public final static byte LargeStringArray = (byte) 0xBE;
    public final static byte EmptyStringArray = (byte) 0xBF;

    public final static byte SmallByteArrayList = (byte) 0xC0;
    public final static byte ByteArrayList = (byte) 0xC1;
    public final static byte LargeByteArrayList = (byte) 0xC2;
    public final static byte EmptyByteArrayList = (byte) 0xC3; // 195U
    
    
    public final static String toString(byte value) {
    	switch(value) {
    		case Unknown:
    			return "Unknown";
    		case Eos:
    			return "Eos";
    		case Null:
    			return "Null";
    		case BooleanTrue:
    			return "BooleanTrue";
    		case BooleanFalse:
    			return "BooleanFalse";
	
    		case ZeroChar:
    			return "ZeroChar";
    		case OneChar:
    			return "OneChar";
    		case MaxChar:
    			return "MaxChar";
    		case Char:
    			return "Char";
	
    		case ZeroByte:
    			return "ZeroByte";
    		case OneByte:
    			return "OneByte";
    		case MaxByte:
    			return "MaxByte";
    		case Byte:
    			return "Byte";
	
    		case MinSByte:
    			return "MinSByte";
    		case MinusOneSByte:
    			return "MinusOneSByte";
    		case ZeroSByte:
    			return "ZeroSByte";
    		case OneSByte:
    			return "OneSByte";
    		case MaxSByte:
    			return "MaxSByte";
    		case SByte:
    			return "SByte";
	
    		case MinInt16:
    			return "MinInt16";
    		case MinusOneInt16:
    			return "MinusOneInt16";
    		case ZeroInt16:
    			return "ZeroInt16";
    		case OneInt16:
    			return "OneInt16";
    		
    		case MaxInt16:
    			return "MaxInt16";
    		case Int16:
    			return "Int16";
	
    		case ZeroUInt16:
    			return "ZeroUInt16";
    		case OneUInt16:
    			return "OneUInt16";
    		case MaxUInt16:
    			return "MaxUInt16";
    		case UInt16:
    			return "UInt16";
	
    		case MinInt32:
    			return "MinInt32";
    		case MinusOneInt32:
    			return "MinusOneInt32";
    		case ZeroInt32:
    			return "ZeroInt32";
    		case OneInt32:
    			return "OneInt32";
    		case MaxInt32:
    			return "MaxInt32";
    		case Int32:
    			return "Int32";
	
    		case ZeroUInt32:
    			return "ZeroUInt32";
    		
    		case OneUInt32:
    			return "OneUInt32";
    		case MaxUInt32:
    			return "MaxUInt32";
    		case UInt32:
    			return "UInt32";
	
    		case MinInt64:
    			return "MinInt64";
    		case MinusOneInt64:
    			return "MinusOneInt64";
    		case ZeroInt64:
    			return "ZeroInt64";
    		case OneInt64:
    			return "OneInt64";
    		case MaxInt64:
    			return "MaxInt64";
    		case Int64:
    			return "Int64";
	
    		case ZeroUInt64:
    			return "ZeroUInt64";
    		case OneUInt64:
    			return "OneUInt64";
    		case MaxUInt64:
    			return "MaxUInt64";
    		case UInt64:
    			return "UInt64";
	
    		case SingleNegativeInfinity:
    			return "SingleNegativeInfinity";
    		case MinSingle:
    			return "MinSingle";
    		case MinusOneSingle:
    			return "MinusOneSingle";
    		case ZeroSingle:
    			return "ZeroSingle";
    		case OneSingle:
    			return "OneSingle";
    		case MaxSingle:
    			return "MaxSingle";
    		case SinglePositiveInfinity:
    			return "SinglePositiveInfinity";
    		case SingleNaN:
    			return "SingleNaN";
    		case Single:
    			return "Single";
	
    		case DoubleNegativeInfinity:
    			return "DoubleNegativeInfinity";
    		case MinDouble:
    			return "MinDouble";
    		case MinusOneDouble:
    			return "MinusOneDouble";
    		case ZeroDouble:
    			return "ZeroDouble";
    		case OneDouble:
    			return "OneDouble";
    		case MaxDouble:
    			return "MaxDouble";
    		case DoublePositiveInfinity:
    			return "DoublePositiveInfinity";
    		case DoubleNaN:
    			return "DoubleNaN";
    		case Double:
    			return "Double";
	
    		case DateTime:
    			return "DateTime";
    		case ZeroDateTime:
    			return "ZeroDateTime";
	
    		case TimeSpan:
    			return "TimeSpan";
    		case ZeroTimeSpan:
    			return "ZeroTimeSpan";
	
    		case Guid:
    			return "Guid";
    		case EmptyGuid:
    			return "EmptyGuid";
	
    		case String:
    			return "String";
    		case EmptyString:
    			return "EmptyString";
	
    		case SmallBooleanArray:
    			return "SmallBooleanArray";
    		case BooleanArray:
    			return "BooleanArray";
    		case LargeBooleanArray:
    			return "LargeBooleanArray";
    		case EmptyBooleanArray:
    			return "EmptyBooleanArray";
	
    		case SmallCharArray:
    			return "SmallCharArray";
    		case CharArray:
    			return "CharArray";
    		case LargeCharArray:
    			return "LargeCharArray";
    		case EmptyCharArray:
    			return "EmptyCharArray";
	
    		case SmallSByteArray:
    			return "SmallSByteArray";
    		case SByteArray:
    			return "SByteArray";
    		case LargeSByteArray:
    			return "LargeSByteArray";
    		case EmptySByteArray:
    			return "EmptySByteArray";
	
    		case SmallByteArray:
    			return "SmallByteArray";
    		case ByteArray:
    			return "ByteArray";
    		case LargeByteArray:
    			return "LargeByteArray";
    		case EmptyByteArray:
    			return "EmptyByteArray";
	
    		case SmallInt16Array:
    			return "SmallInt16Array";
    		case Int16Array:
    			return "Int16Array";
    		case LargeInt16Array:
    			return "LargeInt16Array";
    		case EmptyInt16Array:
    			return "EmptyInt16Array";
	
    		case SmallUInt16Array:
    			return "SmallUInt16Array";
    		case UInt16Array:
    			return "UInt16Array";
    		case LargeUInt16Array:
    			return "LargeUInt16Array";
    		case EmptyUInt16Array:
    			return "EmptyUInt16Array";
	
    		case SmallInt32Array:
    			return "SmallInt32Array";
    		case Int32Array:
    			return "SmallInt32Array";
    		case LargeInt32Array:
    			return "LargeInt32Array";
    		case EmptyInt32Array:
    			return "EmptyInt32Array";
	
    		case SmallUInt32Array:
    			return "SmallUInt32Array";
    		case UInt32Array:
    			return "UInt32Array";
    		case LargeUInt32Array:
    			return "LargeUInt32Array";
    		case EmptyUInt32Array:
    			return "EmptyUInt32Array";
	
    		case SmallInt64Array:
    			return "SmallInt64Array";
    		case Int64Array:
    			return "Int64Array";
    		case LargeInt64Array:
    			return "LargeInt64Array";
    		case EmptyInt64Array:
    			return "EmptyInt64Array";
	
    		case SmallUInt64Array:
    			return "SmallUInt64Array";
    		case UInt64Array:
    			return "UInt64Array";
    		case LargeUInt64Array:
    			return "LargeUInt64Array";
    		case EmptyUInt64Array:
    			return "EmptyUInt64Array";
	
    		case SmallSingleArray:
    			return "SmallSingleArray";
    		case SingleArray:
    			return "SingleArray";
    		case LargeSingleArray:
    			return "LargeSingleArray";
    		case EmptySingleArray:
    			return "EmptySingleArray";
	
    		case SmallDoubleArray:
    			return "SmallDoubleArray";
    		case DoubleArray:
    			return "DoubleArray";
    		case LargeDoubleArray:
    			return "LargeDoubleArray";
    		case EmptyDoubleArray:
    			return "EmptyDoubleArray";
	
    		case SmallDateTimeArray:
    			return "SmallDateTimeArray";
    		case DateTimeArray:
    			return "DateTimeArray";
    		case LargeDateTimeArray:
    			return "LargeDateTimeArray";
    		case EmptyDateTimeArray:
    			return "EmptyDateTimeArray";
	
    		case SmallTimeSpanArray:
    			return "SmallTimeSpanArray";
    		case TimeSpanArray:
    			return "TimeSpanArray";
    		case LargeTimeSpanArray:
    			return "LargeTimeSpanArray";
    		case EmptyTimeSpanArray:
    			return "EmptyTimeSpanArray";
	
    		case SmallGuidArray:
    			return "SmallGuidArray";
    		case GuidArray:
    			return "GuidArray";
    		case LargeGuidArray:
    			return "LargeGuidArray";
    		case EmptyGuidArray:
    			return "EmptyGuidArray";
	
    		case SmallStringArray:
    			return "SmallStringArray";
    		case StringArray:
    			return "StringArray";
    		case LargeStringArray:
    			return "LargeStringArray";
    		case EmptyStringArray:
    			return "EmptyStringArray";
	
    		case SmallByteArrayList:
    			return "SmallByteArrayList";
    		case ByteArrayList:
    			return "ByteArrayList";
    		case LargeByteArrayList:
    			return "LargeByteArrayList";
    		case EmptyByteArrayList:
    			return "EmptyByteArrayList";
			default:
				return "Unknown(" + Integer.toUnsignedString(value, 10) + ")";
    	}
    }
    	
	public static final byte toByte(String value) {
		switch(value) {
    		case "Unknown":
    			return Unknown;
    		case "Eos":
    			return Eos;
    		case "Null":
    			return Null;
    		case "BooleanTrue":
    			return BooleanTrue;
    		case "BooleanFalse":
    			return BooleanFalse;
	
    		case "ZeroChar":
    			return ZeroChar;
    		case "OneChar":
    			return OneChar;
    		case "MaxChar":
    			return MaxChar;
    		case "Char":
    			return Char;
	
    		case "ZeroByte":
    			return ZeroByte;
    		case "OneByte":
    			return OneByte;
    		case "MaxByte":
    			return MaxByte;
    		case "Byte":
    			return Byte;
	
    		case "MinSByte":
    			return MinSByte;
    		case "MinusOneSByte":
    			return MinusOneSByte;
    		case "ZeroSByte":
    			return ZeroSByte;
    		case "OneSByte":
    			return OneSByte;
    		case "MaxSByte":
    			return MaxSByte;
    		case "SByte":
    			return SByte;
	
    		case "MinInt16":
    			return MinInt16;
    		case "MinusOneInt16":
    			return MinusOneInt16;
    		case "ZeroInt16":
    			return ZeroInt16;
    		case "OneInt16":
    			return OneInt16;
    		
    		case "MaxInt16":
    			return MaxInt16;
    		case "Int16":
    			return Int16;
	
    		case "ZeroUInt16":
    			return ZeroUInt16;
    		case "OneUInt16":
    			return OneUInt16;
    		case "MaxUInt16":
    			return MaxUInt16;
    		case "UInt16":
    			return UInt16;
	
    		case "MinInt32":
    			return MinInt32;
    		case "MinusOneInt32":
    			return MinusOneInt32;
    		case "ZeroInt32":
    			return ZeroInt32;
    		case "OneInt32":
    			return OneInt32;
    		case "MaxInt32":
    			return MaxInt32;
    		case "Int32":
    			return Int32;
	
    		case "ZeroUInt32":
    			return ZeroUInt32;
    		
    		case "OneUInt32":
    			return OneUInt32;
    		case "MaxUInt32":
    			return MaxUInt32;
    		case "UInt32":
    			return UInt32;
	
    		case "MinInt64":
    			return MinInt64;
    		case "MinusOneInt64":
    			return MinusOneInt64;
    		case "ZeroInt64":
    			return ZeroInt64;
    		case "OneInt64":
    			return OneInt64;
    		case "MaxInt64":
    			return MaxInt64;
    		case "Int64":
    			return Int64;
	
    		case "ZeroUInt64":
    			return ZeroUInt64;
    		case "OneUInt64":
    			return OneUInt64;
    		case "MaxUInt64":
    			return MaxUInt64;
    		case "UInt64":
    			return UInt64;
	
    		case "SingleNegativeInfinity":
    			return SingleNegativeInfinity;
    		case "MinSingle":
    			return MinSingle;
    		case "MinusOneSingle":
    			return MinusOneSingle;
    		case "ZeroSingle":
    			return ZeroSingle;
    		case "OneSingle":
    			return OneSingle;
    		case "MaxSingle":
    			return MaxSingle;
    		case "SinglePositiveInfinity":
    			return SinglePositiveInfinity;
    		case "SingleNaN":
    			return SingleNaN;
    		case "Single":
    			return Single;
	
    		case "DoubleNegativeInfinity":
    			return DoubleNegativeInfinity;
    		case "MinDouble":
    			return MinDouble;
    		case "MinusOneDouble":
    			return MinusOneDouble;
    		case "ZeroDouble":
    			return ZeroDouble;
    		case "OneDouble":
    			return OneDouble;
    		case "MaxDouble":
    			return MaxDouble;
    		case "DoublePositiveInfinity":
    			return DoublePositiveInfinity;
    		case "DoubleNaN":
    			return DoubleNaN;
    		case "Double":
    			return Double;
	
    		case "DateTime":
    			return DateTime;
    		case "ZeroDateTime":
    			return ZeroDateTime;
	
    		case "TimeSpan":
    			return TimeSpan;
    		case "ZeroTimeSpan":
    			return ZeroTimeSpan;
	
    		case "Guid":
    			return Guid;
    		case "EmptyGuid":
    			return EmptyGuid;
	
    		case "String":
    			return String;
    		case "EmptyString":
    			return EmptyString;
	
    		case "SmallBooleanArray":
    			return SmallBooleanArray;
    		case "BooleanArray":
    			return BooleanArray;
    		case "LargeBooleanArray":
    			return LargeBooleanArray;
    		case "EmptyBooleanArray":
    			return EmptyBooleanArray;
	
    		case "SmallCharArray":
    			return SmallCharArray;
    		case "CharArray":
    			return CharArray;
    		case "LargeCharArray":
    			return LargeCharArray;
    		case "EmptyCharArray":
    			return EmptyCharArray;
	
    		case "SmallSByteArray":
    			return SmallSByteArray;
    		case "SByteArray":
    			return SByteArray;
    		case "LargeSByteArray":
    			return LargeSByteArray;
    		case "EmptySByteArray":
    			return EmptySByteArray;
	
    		case "SmallByteArray":
    			return SmallByteArray;
    		case "ByteArray":
    			return ByteArray;
    		case "LargeByteArray":
    			return LargeByteArray;
    		case "EmptyByteArray":
    			return EmptyByteArray;
	
    		case "SmallInt16Array":
    			return SmallInt16Array;
    		case "Int16Array":
    			return Int16Array;
    		case "LargeInt16Array":
    			return LargeInt16Array;
    		case "EmptyInt16Array":
    			return EmptyInt16Array;
	
    		case "SmallUInt16Array":
    			return SmallUInt16Array;
    		case "UInt16Array":
    			return UInt16Array;
    		case "LargeUInt16Array":
    			return LargeUInt16Array;
    		case "EmptyUInt16Array":
    			return EmptyUInt16Array;
	
    		case "SmallInt32Array":
    			return SmallInt32Array;
    		case "Int32Array":
    			return SmallInt32Array;
    		case "LargeInt32Array":
    			return LargeInt32Array;
    		case "EmptyInt32Array":
    			return EmptyInt32Array;
	
    		case "SmallUInt32Array":
    			return SmallUInt32Array;
    		case "UInt32Array":
    			return UInt32Array;
    		case "LargeUInt32Array":
    			return LargeUInt32Array;
    		case "EmptyUInt32Array":
    			return EmptyUInt32Array;
	
    		case "SmallInt64Array":
    			return SmallInt64Array;
    		case "Int64Array":
    			return Int64Array;
    		case "LargeInt64Array":
    			return LargeInt64Array;
    		case "EmptyInt64Array":
    			return EmptyInt64Array;
	
    		case "SmallUInt64Array":
    			return SmallUInt64Array;
    		case "UInt64Array":
    			return UInt64Array;
    		case "LargeUInt64Array":
    			return LargeUInt64Array;
    		case "EmptyUInt64Array":
    			return EmptyUInt64Array;
	
    		case "SmallSingleArray":
    			return SmallSingleArray;
    		case "SingleArray":
    			return SingleArray;
    		case "LargeSingleArray":
    			return LargeSingleArray;
    		case "EmptySingleArray":
    			return EmptySingleArray;
	
    		case "SmallDoubleArray":
    			return SmallDoubleArray;
    		case "DoubleArray":
    			return DoubleArray;
    		case "LargeDoubleArray":
    			return LargeDoubleArray;
    		case "EmptyDoubleArray":
    			return EmptyDoubleArray;
	
    		case "SmallDateTimeArray":
    			return SmallDateTimeArray;
    		case "DateTimeArray":
    			return DateTimeArray;
    		case "LargeDateTimeArray":
    			return LargeDateTimeArray;
    		case "EmptyDateTimeArray":
    			return EmptyDateTimeArray;
	
    		case "SmallTimeSpanArray":
    			return SmallTimeSpanArray;
    		case "TimeSpanArray":
    			return TimeSpanArray;
    		case "LargeTimeSpanArray":
    			return LargeTimeSpanArray;
    		case "EmptyTimeSpanArray":
    			return EmptyTimeSpanArray;
	
    		case "SmallGuidArray":
    			return SmallGuidArray;
    		case "GuidArray":
    			return GuidArray;
    		case "LargeGuidArray":
    			return LargeGuidArray;
    		case "EmptyGuidArray":
    			return EmptyGuidArray;
	
    		case "SmallStringArray":
    			return SmallStringArray;
    		case "StringArray":
    			return StringArray;
    		case "LargeStringArray":
    			return LargeStringArray;
    		case "EmptyStringArray":
    			return EmptyStringArray;
	
    		case "SmallByteArrayList":
    			return SmallByteArrayList;
    		case "ByteArrayList":
    			return ByteArrayList;
    		case "LargeByteArrayList":
    			return LargeByteArrayList;
    		case "EmptyByteArrayList":
    			return EmptyByteArrayList;
			default:
				return Unknown;
		}
    	
    	
    	
    }
    

}
