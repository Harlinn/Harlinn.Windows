package com.harlinn.common.data;

import java.io.InputStream;
import java.io.Reader;
import java.math.BigDecimal;
import java.net.URL;
import java.sql.Array;
import java.sql.Blob;
import java.sql.Clob;
import java.sql.Date;
import java.sql.NClob;
import java.sql.ParameterMetaData;
import java.sql.PreparedStatement;
import java.sql.Ref;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.RowId;
import java.sql.SQLException;
import java.sql.SQLXML;
import java.sql.Time;
import java.sql.Timestamp;
import java.sql.Types;
import java.util.Calendar;
import java.util.Optional;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory; 

import com.harlinn.common.util.Currency;
import com.harlinn.common.util.Guid;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeSpan;


public class PreparedStatementWrapper extends StatementWrapper implements PreparedStatement {
	static Logger logger = LoggerFactory.getLogger(PreparedStatementWrapper.class);
	
	PreparedStatementWrapper(PreparedStatement preparedStatement) throws SQLException {
		super(preparedStatement);
	}
	
	PreparedStatementWrapper(ConnectionWrapper connectionWrapper,PreparedStatement preparedStatement) throws SQLException {
		super(connectionWrapper, preparedStatement);
	}
	
	
	PreparedStatement getPreparedStatement() {
		return (PreparedStatement)getStatement( );
	}

	@Override
	public ResultSet executeQuery() throws SQLException {
		try {
			var resultSet = getPreparedStatement().executeQuery();
			return new ResultSetWrapper(resultSet);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int executeUpdate() throws SQLException {
		try {
			return getPreparedStatement().executeUpdate();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNull(int parameterIndex, int sqlType) throws SQLException {
		try {
			getPreparedStatement().setNull(parameterIndex, sqlType);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBoolean(int parameterIndex, boolean x) throws SQLException {
		try {
			getPreparedStatement().setBoolean(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	public void setBoolean(int parameterIndex, Optional<Boolean> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setBoolean(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.BOOLEAN);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	

	@Override
	public void setByte(int parameterIndex, byte x) throws SQLException {
		try {
			getPreparedStatement().setByte(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setByte(int parameterIndex, Optional<Byte> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setByte(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.TINYINT);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	@Override
	public void setShort(int parameterIndex, short x) throws SQLException {
		try {
			getPreparedStatement().setShort(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setShort(int parameterIndex, Optional<Short> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setShort(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.SMALLINT);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	
	@Override
	public void setInt(int parameterIndex, int x) throws SQLException {
		try {
			getPreparedStatement().setInt(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setInt(int parameterIndex, Optional<Integer> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setInt(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.INTEGER);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	@Override
	public void setLong(int parameterIndex, long x) throws SQLException {
		try {
			getPreparedStatement().setLong(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	public void setLong(int parameterIndex, Optional<Long> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setLong(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.BIGINT);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setFloat(int parameterIndex, float x) throws SQLException {
		try {
			getPreparedStatement().setFloat(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	public void setFloat(int parameterIndex, Optional<Float> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setFloat(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.REAL);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setDouble(int parameterIndex, double x) throws SQLException {
		try {
			getPreparedStatement().setDouble(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setDouble(int parameterIndex, Optional<Double> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setDouble(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.DOUBLE);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	@Override
	public void setBigDecimal(int parameterIndex, BigDecimal x) throws SQLException {
		try {
			getPreparedStatement().setBigDecimal(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	public void setBigDecimal(int parameterIndex, Optional<BigDecimal> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setBigDecimal(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.DECIMAL);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setString(int parameterIndex, String x) throws SQLException {
		try {
			getPreparedStatement().setString(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setString(int parameterIndex, Optional<String> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setString(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.NVARCHAR);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	
	@Override
	public void setBytes(int parameterIndex, byte[] x) throws SQLException {
		try {
			getPreparedStatement().setBytes(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setBytes(int parameterIndex, Optional<byte[]> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setBytes(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.VARBINARY);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	@Override
	public void setDate(int parameterIndex, Date x) throws SQLException {
		try {
			getPreparedStatement().setDate(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setDate(int parameterIndex, Optional<Date> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setDate(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.DATE);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	public void setDate(int parameterIndex, java.util.Date x) throws SQLException {
		try {
			getPreparedStatement().setDate(parameterIndex, new Date( x.getTime( ) ));
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	
	
	
	@Override
	public void setTime(int parameterIndex, Time x) throws SQLException {
		try {
			getPreparedStatement().setTime(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	
	public void setTime(int parameterIndex, Optional<Time> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setTime(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.TIME);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	@Override
	public void setTimestamp(int parameterIndex, Timestamp x) throws SQLException {
		try {
			getPreparedStatement().setTimestamp(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	public void setTimestamp(int parameterIndex, Optional<Timestamp> x) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setTimestamp(parameterIndex, x.get());
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.TIMESTAMP);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	

	@Override
	public void setAsciiStream(int parameterIndex, InputStream x, int length) throws SQLException {
		try {
			getPreparedStatement().setAsciiStream(parameterIndex, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setAsciiStream(int parameterIndex, Optional<InputStream> x, int length) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setAsciiStream(parameterIndex, x.get(), length);
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.NVARCHAR);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	@Deprecated(since="1.2")
	@Override
	public void setUnicodeStream(int parameterIndex, InputStream x, int length) throws SQLException {
		try {
			getPreparedStatement().setUnicodeStream(parameterIndex, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	

	@Override
	public void setBinaryStream(int parameterIndex, InputStream x, int length) throws SQLException {
		try {
			getPreparedStatement().setBinaryStream(parameterIndex, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setBinaryStream(int parameterIndex, Optional<InputStream> x, int length) throws SQLException {
		try {
			if(x.isPresent()) {
				getPreparedStatement().setBinaryStream(parameterIndex, x.get(), length);
			}
			else {
				getPreparedStatement().setNull(parameterIndex, Types.NVARCHAR);
			}
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	
	@Override
	public void clearParameters() throws SQLException {
		try {
			getPreparedStatement().clearParameters( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setObject(int parameterIndex, Object x, int targetSqlType) throws SQLException {
		try {
			getPreparedStatement().setObject(parameterIndex, x, targetSqlType);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setObject(int parameterIndex, Object x) throws SQLException {
		try {
			getPreparedStatement().setObject(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean execute() throws SQLException {
		try {
			return getPreparedStatement().execute( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void addBatch() throws SQLException {
		try {
			getPreparedStatement().addBatch( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCharacterStream(int parameterIndex, Reader reader, int length) throws SQLException {
		try {
			getPreparedStatement().setCharacterStream(parameterIndex, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setRef(int parameterIndex, Ref x) throws SQLException {
		try {
			getPreparedStatement().setRef(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBlob(int parameterIndex, Blob x) throws SQLException {
		try {
			getPreparedStatement().setBlob(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setClob(int parameterIndex, Clob x) throws SQLException {
		try {
			getPreparedStatement().setClob(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setArray(int parameterIndex, Array x) throws SQLException {
		try {
			getPreparedStatement().setArray(parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public ResultSetMetaData getMetaData() throws SQLException {
		try {
			return getPreparedStatement().getMetaData( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setDate(int parameterIndex, Date x, Calendar cal) throws SQLException {
		try {
			getPreparedStatement().setDate( parameterIndex, x, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setTime(int parameterIndex, Time x, Calendar cal) throws SQLException {
		try {
			getPreparedStatement().setTime( parameterIndex, x, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setTimestamp(int parameterIndex, Timestamp x, Calendar cal) throws SQLException {
		try {
			getPreparedStatement().setTimestamp( parameterIndex, x, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNull(int parameterIndex, int sqlType, String typeName) throws SQLException {
		try {
			getPreparedStatement().setNull( parameterIndex, sqlType, typeName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setURL(int parameterIndex, URL x) throws SQLException {
		try {
			getPreparedStatement().setURL( parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public ParameterMetaData getParameterMetaData() throws SQLException {
		try {
			return getPreparedStatement().getParameterMetaData( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setRowId(int parameterIndex, RowId x) throws SQLException {
		try {
			getPreparedStatement().setRowId( parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNString(int parameterIndex, String value) throws SQLException {
		try {
			getPreparedStatement().setNString( parameterIndex, value);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
		
	}

	@Override
	public void setNCharacterStream(int parameterIndex, Reader value, long length) throws SQLException {
		try {
			getPreparedStatement().setNCharacterStream( parameterIndex, value, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
		
	}

	@Override
	public void setNClob(int parameterIndex, NClob value) throws SQLException {
		try {
			getPreparedStatement().setNClob( parameterIndex, value);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setClob(int parameterIndex, Reader reader, long length) throws SQLException {
		try {
			getPreparedStatement().setClob( parameterIndex, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBlob(int parameterIndex, InputStream inputStream, long length) throws SQLException {
		try {
			getPreparedStatement().setBlob( parameterIndex, inputStream, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNClob(int parameterIndex, Reader reader, long length) throws SQLException {
		try {
			getPreparedStatement().setNClob( parameterIndex, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setSQLXML(int parameterIndex, SQLXML xmlObject) throws SQLException {
		try {
			getPreparedStatement().setSQLXML( parameterIndex, xmlObject);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setObject(int parameterIndex, Object x, int targetSqlType, int scaleOrLength) throws SQLException {
		try {
			getPreparedStatement().setObject( parameterIndex, x, targetSqlType, scaleOrLength);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setAsciiStream(int parameterIndex, InputStream x, long length) throws SQLException {
		try {
			getPreparedStatement().setAsciiStream( parameterIndex, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBinaryStream(int parameterIndex, InputStream x, long length) throws SQLException {
		try {
			getPreparedStatement().setBinaryStream( parameterIndex, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCharacterStream(int parameterIndex, Reader reader, long length) throws SQLException {
		try {
			getPreparedStatement().setCharacterStream( parameterIndex, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setAsciiStream(int parameterIndex, InputStream x) throws SQLException {
		try {
			getPreparedStatement().setAsciiStream( parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBinaryStream(int parameterIndex, InputStream x) throws SQLException {
		try {
			getPreparedStatement().setBinaryStream( parameterIndex, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCharacterStream(int parameterIndex, Reader reader) throws SQLException {
		try {
			getPreparedStatement().setCharacterStream( parameterIndex, reader);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNCharacterStream(int parameterIndex, Reader value) throws SQLException {
		try {
			getPreparedStatement().setNCharacterStream( parameterIndex, value);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setClob(int parameterIndex, Reader reader) throws SQLException {
		try {
			getPreparedStatement().setClob( parameterIndex, reader);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBlob(int parameterIndex, InputStream inputStream) throws SQLException {
		try {
			getPreparedStatement().setBlob( parameterIndex, inputStream);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNClob(int parameterIndex, Reader reader) throws SQLException {
		try {
			getPreparedStatement().setNClob( parameterIndex, reader);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	public void setNullableBoolean(int parameterIndex, Boolean x) throws SQLException {
		if(x != null) {
			setBoolean(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.BOOLEAN);
		}
	}
	
	public void setUInt8(int parameterIndex, byte x) throws SQLException {
		setShort(parameterIndex, x);
	}
	
	public void setNullableUInt8(int parameterIndex, Byte x) throws SQLException {
		if(x != null) {
			setShort(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.TINYINT);
		}
	}
	
	public void setInt8(int parameterIndex, byte x) throws SQLException {
		setShort(parameterIndex, x);
	}
	
	public void setNullableInt8(int parameterIndex, Byte x) throws SQLException {
		if(x != null) {
			setShort(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.TINYINT);
		}
	}
	
	public void setUInt16(int parameterIndex, short x) throws SQLException {
		setShort(parameterIndex, x);
	}
	
	public void setNullableUInt16(int parameterIndex, Short x) throws SQLException {
		if(x != null) {
			setShort(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.SMALLINT);
		}
	}
	
	public void setInt16(int parameterIndex, short x) throws SQLException {
		setShort(parameterIndex, x);
	}
	
	public void setNullableInt16(int parameterIndex, Short x) throws SQLException {
		if(x != null) {
			setShort(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.SMALLINT);
		}
	}
	
	public void setUInt32(int parameterIndex, int x) throws SQLException {
		setInt(parameterIndex, x);
	}
	
	public void setNullableUInt32(int parameterIndex, Integer x) throws SQLException {
		if(x != null) {
			setInt(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.INTEGER);
		}
	}
	
	public void setInt32(int parameterIndex, int x) throws SQLException {
		setInt(parameterIndex, x);
	}
	
	public void setNullableInt32(int parameterIndex, Integer x) throws SQLException {
		if(x != null) {
			setInt(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.INTEGER);
		}
	}
	
	public void setUInt64(int parameterIndex, long x) throws SQLException {
		setLong(parameterIndex, x);
	}
	
	public void setNullableUInt64(int parameterIndex, Long x) throws SQLException {
		if(x != null) {
			setLong(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.BIGINT);
		}
	}
	
	public void setInt64(int parameterIndex, long x) throws SQLException {
		setLong(parameterIndex, x);
	}
	
	public void setNullableInt64(int parameterIndex, Long x) throws SQLException {
		if(x != null) {
			setLong(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.BIGINT);
		}
	}
	
	public void setSingle(int parameterIndex, float x) throws SQLException {
		setFloat(parameterIndex, x);
	}
	
	public void setNullableSingle(int parameterIndex, Float x) throws SQLException {
		if(x != null) {
			setFloat(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.REAL);
		}
	}
	
	public void setNullableDouble(int parameterIndex, Double x) throws SQLException {
		if(x != null) {
			setDouble(parameterIndex, x);
		}
		else {
			setNull(parameterIndex,Types.DOUBLE);
		}
	}
	
	public void setDateTime(int parameterIndex, DateTime dateTime) throws SQLException {
		if(dateTime != null) {
			var timestamp = dateTime.toSqlTimestamp();
			setTimestamp(parameterIndex, timestamp);
		}
		else {
			var message = "dateTime cannot be null.";
			logger.error(message);
			throw new IllegalArgumentException(message);
		}
	}
	
	public void setNullableDateTime(int parameterIndex, DateTime dateTime) throws SQLException {
		if(dateTime != null) {
			var timestamp = dateTime.toSqlTimestamp();
			setTimestamp(parameterIndex, timestamp);
		}
		else {
			setNull(parameterIndex,Types.TIMESTAMP);
		}
	}
	
	public void setLongFromDateTime(int parameterIndex, DateTime dateTime) throws SQLException {
		if(dateTime != null) {
			var ticks = dateTime.toTicks();
			setLong(parameterIndex, ticks);
		}
		else {
			var message = "dateTime cannot be null.";
			logger.error(message);
			throw new IllegalArgumentException(message);
		}
	}
	
	public void setLongFromNullableDateTime(int parameterIndex, DateTime dateTime) throws SQLException {
		if(dateTime != null) {
			var ticks = dateTime.toTicks();
			setLong(parameterIndex, ticks);
		}
		else {
			setNull(parameterIndex,Types.BIGINT);
		}
	}
	
	public void setTimeSpan(int parameterIndex, TimeSpan timeSpan) throws SQLException {
		if(timeSpan != null) {
			var ticks = timeSpan.getTicks();
			setLong(parameterIndex, ticks);
		}
		else {
			var message = "timeSpan cannot be null.";
			logger.error(message);
			throw new IllegalArgumentException(message);
		}
	}
	
	public void setNullableTimeSpan(int parameterIndex, TimeSpan timeSpan) throws SQLException {
		if(timeSpan != null) {
			var ticks = timeSpan.getTicks();
			setLong(parameterIndex, ticks);
		}
		else {
			setNull(parameterIndex,Types.BIGINT);
		}
	}
	
	public void setCurrency(int parameterIndex, Currency currency) throws SQLException {
		if(currency != null) {
			var value = currency.getValue();
			setLong(parameterIndex, value);
		}
		else {
			var message = "currency cannot be null.";
			logger.error(message);
			throw new IllegalArgumentException(message);
		}
	}
	
	public void setNullableCurrency(int parameterIndex, Currency currency) throws SQLException {
		if(currency != null) {
			var value = currency.getValue();
			setLong(parameterIndex, value);
		}
		else {
			setNull(parameterIndex,Types.BIGINT);
		}
	}
	
	
	public void setGuid(int parameterIndex, Guid guid) throws SQLException {
		if(guid != null) {
			var guidAsString = guid.toString();
			setString(parameterIndex,guidAsString);
		}
		else {
			var message = "guid cannot be null.";
			logger.error(message);
			throw new IllegalArgumentException(message);
		}
	}
	
	public void setNullableGuid(int parameterIndex, Guid guid) throws SQLException {
		if(guid != null) {
			var guidAsString = guid.toString();
			setString(parameterIndex,guidAsString);
		}
		else {
			setNull(parameterIndex,Types.VARCHAR);
		}
	}
	
	public void setNullableString(int parameterIndex, String str) throws SQLException {
		if(str != null) {
			setString(parameterIndex,str);
		}
		else {
			setNull(parameterIndex,Types.VARCHAR);
		}
	}
	
	public void setBinary(int parameterIndex, byte[] bytes) throws SQLException {
		if(bytes != null) {
			setBytes(parameterIndex,bytes);
		}
		else {
			var message = "bytes cannot be null.";
			logger.error(message);
			throw new IllegalArgumentException(message);
		}
	}
	
	public void setNullableBinary(int parameterIndex, byte[] bytes) throws SQLException {
		if(bytes != null) {
			setBytes(parameterIndex,bytes);
		}
		else {
			setNull(parameterIndex,Types.VARBINARY);
		}
	}
	
	
	
	
	
}
