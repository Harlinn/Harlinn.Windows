package com.harlinn.common.io;

import java.sql.Time;
import java.time.Instant;
import java.time.Duration;
import java.util.Date;
import java.util.UUID;

import com.harlinn.common.util.Currency;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeSpan;
import com.harlinn.common.util.Guid;

public interface BinaryReader {

	boolean readBoolean( );
	Boolean readNullableBoolean( );
	
	char readChar( );
	Character readNullableChar( );
	
	byte readUInt8( );
	Byte readNullableUInt8( );
	
	byte readInt8( );
	Byte readNullableInt8( );
	
	short readUInt16( );
	Short readNullableUInt16( );
	
	short readInt16( );
	Short readNullableInt16( );
	
	int readUInt32( );
	Integer readNullableUInt32( );
	
	int readInt32( );
	Integer readNullableInt32( );
	
	long readUInt64( );
	Long readNullableUInt64( );
	
	long readInt64( );
	Long readNullableInt64( );
	
	float readSingle( );
	Float readNullableSingle( );
	
	double readDouble( );
	Double readNullableDouble( );
	
	Currency readCurrency( );
	Currency readNullableCurrency( );
	
	DateTime readDateTime( );
	DateTime readNullableDateTime( );
	
	Instant readInstant( );
	Instant readNullableInstant( );
	
	Date readDate( );
	Date readNullableDate( );
	
	TimeSpan readTimeSpan( );
	TimeSpan readNullableTimeSpan( );
	
	Duration readDuration( );
	Duration readNullableDuration( );
	
	Time readTime( );
	Time readNullableTime( );
	
	Guid readGuid( );
	Guid readNullableGuid( );
	
	UUID readUUID( );
	UUID readNullableUUID( );
	
	String readString( );
	String readNullableString( );
	
	boolean[] readBooleanArray();
	boolean[] readNullableBooleanArray();
	
	char[] readCharArray();
	char[] readNullableCharArray();
	
	byte[] readUInt8Array();
	byte[] readNullableUInt8Array();
	
	byte[] readInt8Array();
	byte[] readNullableInt8Array();
	
	short[] readUInt16Array();
	short[] readNullableUInt16Array();
	
	short[] readInt16Array();
	short[] readNullableInt16Array();
	
	int[] readUInt32Array();
	int[] readNullableUInt32Array();
	
	int[] readInt32Array();
	int[] readNullableInt32Array();
	
	long[] readUInt64Array();
	long[] readNullableUInt64Array();
	
	long[] readInt64Array();
	long[] readNullableInt64Array();
	
	float[] readSingleArray();
	float[] readNullableSingleArray();
	
	double[] readDoubleArray();
	double[] readNullableDoubleArray();
	
	DateTime[] readDateTimeArray();
	DateTime[] readNullableDateTimeArray();
	
	TimeSpan[] readTimeSpanArray();
	TimeSpan[] readNullableTimeSpanArray();
	
	Guid[] readGuidArray();
	Guid[] readNullableGuidArray();
	
	String[] readStringArray();
	String[] readNullableStringArray();
	
	byte[][] readInt8ListArray();
	byte[][] readNullableInt8ListArray();
	
	
}
