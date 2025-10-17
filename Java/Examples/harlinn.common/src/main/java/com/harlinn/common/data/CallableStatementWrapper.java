package com.harlinn.common.data;

import java.io.InputStream;
import java.io.Reader;
import java.math.BigDecimal;
import java.net.URL;
import java.sql.Array;
import java.sql.Blob;
import java.sql.CallableStatement;
import java.sql.Clob;
import java.sql.Date;
import java.sql.NClob;
import java.sql.Ref;
import java.sql.RowId;
import java.sql.SQLException;
import java.sql.SQLXML;
import java.sql.Time;
import java.sql.Timestamp;
import java.sql.Types;
import java.util.Calendar;
import java.util.Map;
import java.util.UUID;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;


import com.harlinn.common.util.Currency;
import com.harlinn.common.util.Guid;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeSpan;



public class CallableStatementWrapper extends PreparedStatementWrapper implements CallableStatement {
	static Logger logger = LoggerFactory.getLogger(CallableStatementWrapper.class);
	
	
	public CallableStatementWrapper(CallableStatement callableStatement) throws SQLException {
		super(callableStatement);
	}
	
	public CallableStatementWrapper(ConnectionWrapper connectionWrapper,CallableStatement callableStatement) throws SQLException {
		super(connectionWrapper,callableStatement);
	}
	
	CallableStatement getCallableStatement() {
		return (CallableStatement)getStatement();
	}

	@Override
	public void registerOutParameter(int parameterIndex, int sqlType) throws SQLException {
		try {
			getCallableStatement().registerOutParameter(parameterIndex, sqlType);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void registerOutParameter(int parameterIndex, int sqlType, int scale) throws SQLException {
		try {
			getCallableStatement().registerOutParameter(parameterIndex, sqlType, scale);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean wasNull() throws SQLException {
		try {
			return getCallableStatement().wasNull();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public String getString(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getString(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean getBoolean(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getBoolean(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public byte getByte(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getByte(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public short getShort(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getShort(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getInt(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getInt(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public long getLong(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getLong(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public float getFloat(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getFloat(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public double getDouble(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getDouble(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public BigDecimal getBigDecimal(int parameterIndex, int scale) throws SQLException {
		try {
			return getCallableStatement().getBigDecimal(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public byte[] getBytes(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getBytes(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Date getDate(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getDate(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Time getTime(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getTime(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Timestamp getTimestamp(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getTimestamp(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Object getObject(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getTimestamp(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public BigDecimal getBigDecimal(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getBigDecimal(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Object getObject(int parameterIndex, Map<String, Class<?>> map) throws SQLException {
		try {
			return getCallableStatement().getObject(parameterIndex, map);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Ref getRef(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getRef(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Blob getBlob(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getBlob(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Clob getClob(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getClob(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Array getArray(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getArray(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Date getDate(int parameterIndex, Calendar cal) throws SQLException {
		try {
			return getCallableStatement().getDate(parameterIndex, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Time getTime(int parameterIndex, Calendar cal) throws SQLException {
		try {
			return getCallableStatement().getTime(parameterIndex, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Timestamp getTimestamp(int parameterIndex, Calendar cal) throws SQLException {
		try {
			return getCallableStatement().getTimestamp(parameterIndex, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void registerOutParameter(int parameterIndex, int sqlType, String typeName) throws SQLException {
		try {
			getCallableStatement().registerOutParameter(parameterIndex, sqlType, typeName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void registerOutParameter(String parameterName, int sqlType) throws SQLException {
		try {
			getCallableStatement().registerOutParameter(parameterName, sqlType);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void registerOutParameter(String parameterName, int sqlType, int scale) throws SQLException {
		try {
			getCallableStatement().registerOutParameter(parameterName, sqlType, scale);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void registerOutParameter(String parameterName, int sqlType, String typeName) throws SQLException {
		try {
			getCallableStatement().registerOutParameter(parameterName, sqlType, typeName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
		
	}

	@Override
	public URL getURL(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getURL(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setURL(String parameterName, URL val) throws SQLException {
		try {
			getCallableStatement().setURL(parameterName, val);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNull(String parameterName, int sqlType) throws SQLException {
		try {
			getCallableStatement().setNull(parameterName, sqlType);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBoolean(String parameterName, boolean x) throws SQLException {
		try {
			getCallableStatement().setBoolean(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setByte(String parameterName, byte x) throws SQLException {
		try {
			getCallableStatement().setByte(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setShort(String parameterName, short x) throws SQLException {
		try {
			getCallableStatement().setShort(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setInt(String parameterName, int x) throws SQLException {
		try {
			getCallableStatement().setInt(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setLong(String parameterName, long x) throws SQLException {
		try {
			getCallableStatement().setLong(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setFloat(String parameterName, float x) throws SQLException {
		try {
			getCallableStatement().setFloat(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setDouble(String parameterName, double x) throws SQLException {
		try {
			getCallableStatement().setDouble(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBigDecimal(String parameterName, BigDecimal x) throws SQLException {
		try {
			getCallableStatement().setBigDecimal(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setString(String parameterName, String x) throws SQLException {
		try {
			getCallableStatement().setString(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBytes(String parameterName, byte[] x) throws SQLException {
		try {
			getCallableStatement().setBytes(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setDate(String parameterName, Date x) throws SQLException {
		try {
			getCallableStatement().setDate(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setTime(String parameterName, Time x) throws SQLException {
		try {
			getCallableStatement().setTime(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setTimestamp(String parameterName, Timestamp x) throws SQLException {
		try {
			getCallableStatement().setTimestamp(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setAsciiStream(String parameterName, InputStream x, int length) throws SQLException {
		try {
			getCallableStatement().setAsciiStream(parameterName, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBinaryStream(String parameterName, InputStream x, int length) throws SQLException {
		try {
			getCallableStatement().setBinaryStream(parameterName, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setObject(String parameterName, Object x, int targetSqlType, int scale) throws SQLException {
		try {
			getCallableStatement().setObject(parameterName, x, targetSqlType, scale);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setObject(String parameterName, Object x, int targetSqlType) throws SQLException {
		try {
			getCallableStatement().setObject(parameterName, x, targetSqlType);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setObject(String parameterName, Object x) throws SQLException {
		try {
			getCallableStatement().setObject(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCharacterStream(String parameterName, Reader reader, int length) throws SQLException {
		try {
			getCallableStatement().setCharacterStream(parameterName, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setDate(String parameterName, Date x, Calendar cal) throws SQLException {
		try {
			getCallableStatement().setDate(parameterName, x, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setTime(String parameterName, Time x, Calendar cal) throws SQLException {
		try {
			getCallableStatement().setTime(parameterName, x, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setTimestamp(String parameterName, Timestamp x, Calendar cal) throws SQLException {
		try {
			getCallableStatement().setTimestamp(parameterName, x, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNull(String parameterName, int sqlType, String typeName) throws SQLException {
		try {
			getCallableStatement().setNull(parameterName, sqlType, typeName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public String getString(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getString(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean getBoolean(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getBoolean(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public byte getByte(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getByte(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public short getShort(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getShort(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getInt(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getInt(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public long getLong(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getLong(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public float getFloat(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getFloat(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public double getDouble(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getDouble(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public byte[] getBytes(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getBytes(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Date getDate(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getDate(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Time getTime(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getTime(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Timestamp getTimestamp(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getTimestamp(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Object getObject(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getObject(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public BigDecimal getBigDecimal(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getBigDecimal(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Object getObject(String parameterName, Map<String, Class<?>> map) throws SQLException {
		try {
			return getCallableStatement().getObject(parameterName, map);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Ref getRef(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getRef(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Blob getBlob(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getBlob(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Clob getClob(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getClob(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Array getArray(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getArray(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Date getDate(String parameterName, Calendar cal) throws SQLException {
		try {
			return getCallableStatement().getDate(parameterName, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Time getTime(String parameterName, Calendar cal) throws SQLException {
		try {
			return getCallableStatement().getTime(parameterName, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Timestamp getTimestamp(String parameterName, Calendar cal) throws SQLException {
		try {
			return getCallableStatement().getTimestamp(parameterName, cal);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public URL getURL(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getURL(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public RowId getRowId(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getRowId(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public RowId getRowId(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getRowId(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setRowId(String parameterName, RowId x) throws SQLException {
		try {
			getCallableStatement().setRowId(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNString(String parameterName, String value) throws SQLException {
		try {
			getCallableStatement().setNString(parameterName, value);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNCharacterStream(String parameterName, Reader value, long length) throws SQLException {
		try {
			getCallableStatement().setNCharacterStream(parameterName, value, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNClob(String parameterName, NClob value) throws SQLException {
		try {
			getCallableStatement().setNClob(parameterName, value);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setClob(String parameterName, Reader reader, long length) throws SQLException {
		try {
			getCallableStatement().setClob(parameterName, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBlob(String parameterName, InputStream inputStream, long length) throws SQLException {
		try {
			getCallableStatement().setBlob(parameterName, inputStream, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNClob(String parameterName, Reader reader, long length) throws SQLException {
		try {
			getCallableStatement().setNClob(parameterName, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public NClob getNClob(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getNClob(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public NClob getNClob(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getNClob(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setSQLXML(String parameterName, SQLXML xmlObject) throws SQLException {
		try {
			getCallableStatement().setSQLXML(parameterName, xmlObject);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public SQLXML getSQLXML(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getSQLXML(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public SQLXML getSQLXML(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getSQLXML(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public String getNString(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getNString(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public String getNString(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getNString(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Reader getNCharacterStream(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getNCharacterStream(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Reader getNCharacterStream(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getNCharacterStream(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Reader getCharacterStream(int parameterIndex) throws SQLException {
		try {
			return getCallableStatement().getCharacterStream(parameterIndex);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Reader getCharacterStream(String parameterName) throws SQLException {
		try {
			return getCallableStatement().getCharacterStream(parameterName);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBlob(String parameterName, Blob x) throws SQLException {
		try {
			getCallableStatement().setBlob(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setClob(String parameterName, Clob x) throws SQLException {
		try {
			getCallableStatement().setClob(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setAsciiStream(String parameterName, InputStream x, long length) throws SQLException {
		try {
			getCallableStatement().setAsciiStream(parameterName, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBinaryStream(String parameterName, InputStream x, long length) throws SQLException {
		try {
			getCallableStatement().setBinaryStream(parameterName, x, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCharacterStream(String parameterName, Reader reader, long length) throws SQLException {
		try {
			getCallableStatement().setCharacterStream(parameterName, reader, length);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setAsciiStream(String parameterName, InputStream x) throws SQLException {
		try {
			getCallableStatement().setAsciiStream(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBinaryStream(String parameterName, InputStream x) throws SQLException {
		try {
			getCallableStatement().setBinaryStream(parameterName, x);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCharacterStream(String parameterName, Reader reader) throws SQLException {
		try {
			getCallableStatement().setCharacterStream(parameterName, reader);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNCharacterStream(String parameterName, Reader value) throws SQLException {
		try {
			getCallableStatement().setNCharacterStream(parameterName, value);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setClob(String parameterName, Reader reader) throws SQLException {
		try {
			getCallableStatement().setClob(parameterName, reader);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setBlob(String parameterName, InputStream inputStream) throws SQLException {
		try {
			getCallableStatement().setBlob(parameterName, inputStream);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setNClob(String parameterName, Reader reader) throws SQLException {
		try {
			getCallableStatement().setNClob(parameterName, reader);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
		
	}

	@Override
	public <T> T getObject(int parameterIndex, Class<T> type) throws SQLException {
		try {
			return getCallableStatement().getObject(parameterIndex, type);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public <T> T getObject(String parameterName, Class<T> type) throws SQLException {
		try {
			return getCallableStatement().getObject(parameterName, type);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	
	
	public Boolean getNullableBoolean(int parameterIndex) throws SQLException {
		var value = getBoolean(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public char getChar(int parameterIndex) throws SQLException {
		var value = getString(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value.charAt(0);
	}
	
	public Character getNullableChar(int parameterIndex) throws SQLException {
		var value = getString(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value.charAt(0);
	}
	
	public byte getUInt8(int parameterIndex) throws SQLException {
		var value = getByte(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Byte getNullableUInt8(int parameterIndex) throws SQLException {
		var value = getByte(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public byte getInt8(int parameterIndex) throws SQLException {
		var value = getByte(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Byte getNullableInt8(int parameterIndex) throws SQLException {
		var value = getByte(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public short getUInt16(int parameterIndex) throws SQLException {
		var value = getShort(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Short getNullableUInt16(int parameterIndex) throws SQLException {
		var value = getShort(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public short getInt16(int parameterIndex) throws SQLException {
		var value = getShort(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Short getNullableInt16(int parameterIndex) throws SQLException {
		var value = getShort(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public int getUInt32(int parameterIndex) throws SQLException {
		var value = getInt(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Integer getNullableUInt32(int parameterIndex) throws SQLException {
		var value = getInt(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public int getInt32(int parameterIndex) throws SQLException {
		var value = getInt(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Integer getNullableInt32(int parameterIndex) throws SQLException {
		var value = getInt(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	
	public long getUInt64(int parameterIndex) throws SQLException {
		var value = getLong(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Long getNullableUInt64(int parameterIndex) throws SQLException {
		var value = getLong(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public long getInt64(int parameterIndex) throws SQLException {
		var value = getLong(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Long getNullableInt64(int parameterIndex) throws SQLException {
		var value = getLong(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public float getSingle(int parameterIndex) throws SQLException {
		var value = getFloat(parameterIndex);
		if(wasNull()) {
			throw new SQLException("The parameter at index "+ parameterIndex +" was NULL.");
		}
		return value;
	}
	
	public Float getNullableSingle(int parameterIndex) throws SQLException {
		var value = getFloat(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public Double getNullableDouble(int parameterIndex) throws SQLException {
		var value = getDouble(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	
	public DateTime getDateTime(int parameterIndex) throws SQLException {
		var timestamp = getTimestamp(parameterIndex);
		if(timestamp != null) {
			return new DateTime(timestamp);
		}
		return new DateTime();
	}
	
	public DateTime getNullableDateTime(int parameterIndex) throws SQLException {
		var timestamp = getTimestamp(parameterIndex);
		if(timestamp != null) {
			return new DateTime(timestamp);
		}
		return null;
	}
	
	public DateTime getDateTimeFromLong(int parameterIndex) throws SQLException {
		var ticks = getLong(parameterIndex);
		if(wasNull()) {
			return new DateTime();
		}
		return new DateTime(ticks);
	}
	
	public DateTime getNullableDateTimeFromLong(int parameterIndex) throws SQLException {
		var ticks = getLong(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return new DateTime(ticks);
	}
	
	public TimeSpan getTimeSpan(int parameterIndex) throws SQLException {
		var ticks = getLong(parameterIndex);
		if(wasNull()) {
			return new TimeSpan();
		}
		return new TimeSpan(ticks);
	}
	
	public TimeSpan getNullableTimeSpan(int parameterIndex) throws SQLException {
		var ticks = getLong(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return new TimeSpan(ticks);
	}
	
	public Currency getCurrency(int parameterIndex) throws SQLException {
		var value = getLong(parameterIndex);
		if(wasNull()) {
			return new Currency();
		}
		return Currency.fromValue(value);
	}
	
	public Currency getNullableCurrency(int parameterIndex) throws SQLException {
		var value = getLong(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return Currency.fromValue(value);
	}
	
	
	public Guid getGuid(int parameterIndex) throws SQLException {
		var guidAsString = getString(parameterIndex);
		if(guidAsString != null) {
			return Guid.fromString(guidAsString);
		}
		return new Guid();
	}
	
	public Guid getNullableGuid(int parameterIndex) throws SQLException {
		var guidAsString = getString(parameterIndex);
		if(guidAsString != null) {
			return Guid.fromString(guidAsString);
		}
		return null;
	}
	
	public String getNullableString(int parameterIndex) throws SQLException {
		var value = getString(parameterIndex);
		if(wasNull()) {
			return null;
		}
		return value;
	}
	
	public byte[] getBinary(int parameterIndex) throws SQLException {
		var value = getBytes(parameterIndex);
		if(wasNull() || value == null ) {
			return new byte[0];
		}
		return value;
	}
	
	public byte[] getNullableBinary(int parameterIndex) throws SQLException {
		var value = getBytes(parameterIndex);
		if(wasNull() || value == null ) {
			return null;
		}
		return value;
	}
	
	
	
	
	
}
