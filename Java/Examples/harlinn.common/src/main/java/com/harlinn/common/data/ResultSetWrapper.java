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
import java.sql.Ref;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.RowId;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.SQLXML;
import java.sql.Statement;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.harlinn.common.util.Guid;
import com.harlinn.common.util.DateTime;
import com.harlinn.common.util.TimeSpan;


public class ResultSetWrapper implements ResultSet {
	static Logger logger = LoggerFactory.getLogger(ResultSetWrapper.class);
	ResultSet resultSet;

	
	public ResultSetWrapper(ResultSet resultSet) {
		this.resultSet = resultSet;
	}
	
	com.microsoft.sqlserver.jdbc.SQLServerResultSet getSQLServerResultSet() {
		if (resultSet instanceof com.microsoft.sqlserver.jdbc.SQLServerResultSet ) {
			return (com.microsoft.sqlserver.jdbc.SQLServerResultSet)resultSet;
		}
		return null;
	}
	
	
	@Override
	public <T> T unwrap(Class<T> iface) throws SQLException {
		try {
			return resultSet.unwrap(iface);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isWrapperFor(Class<?> iface) throws SQLException {
		try {
			return resultSet.isWrapperFor(iface);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean next() throws SQLException {
		try {
			return resultSet.next();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void close() throws SQLException {
		try {
			resultSet.close();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public boolean wasNull() throws SQLException {
		try {
			return resultSet.wasNull();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getString(int columnIndex) throws SQLException {
		try {
			return resultSet.getString(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean getBoolean(int columnIndex) throws SQLException {
		try {
			return resultSet.getBoolean(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public byte getByte(int columnIndex) throws SQLException {
		try {
			return resultSet.getByte(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public short getShort(int columnIndex) throws SQLException {
		try {
			return resultSet.getShort(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getInt(int columnIndex) throws SQLException {
		try {
			return resultSet.getInt(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public long getLong(int columnIndex) throws SQLException {
		try {
			return resultSet.getLong(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public float getFloat(int columnIndex) throws SQLException {
		try {
			return resultSet.getFloat(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public double getDouble(int columnIndex) throws SQLException {
		try {
			return resultSet.getDouble(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	@Deprecated(since="1.2")
	public BigDecimal getBigDecimal(int columnIndex, int scale) throws SQLException {
		try {
			return resultSet.getBigDecimal(columnIndex, scale);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public byte[] getBytes(int columnIndex) throws SQLException {
		try {
			return resultSet.getBytes(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Date getDate(int columnIndex) throws SQLException {
		try {
			return resultSet.getDate(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Time getTime(int columnIndex) throws SQLException {
		try {
			return resultSet.getTime(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Timestamp getTimestamp(int columnIndex) throws SQLException {
		try {
			return resultSet.getTimestamp(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public InputStream getAsciiStream(int columnIndex) throws SQLException {
		try {
			return resultSet.getAsciiStream(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	@Deprecated(since="1.2")
	public InputStream getUnicodeStream(int columnIndex) throws SQLException {
		try {
			return resultSet.getUnicodeStream(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public InputStream getBinaryStream(int columnIndex) throws SQLException {
		try {
			return resultSet.getBinaryStream(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getString(String columnLabel) throws SQLException {
		try {
			return resultSet.getString(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean getBoolean(String columnLabel) throws SQLException {
		try {
			return resultSet.getBoolean(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public byte getByte(String columnLabel) throws SQLException {
		try {
			return resultSet.getByte(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public short getShort(String columnLabel) throws SQLException {
		try {
			return resultSet.getShort(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getInt(String columnLabel) throws SQLException {
		try {
			return resultSet.getInt(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public long getLong(String columnLabel) throws SQLException {
		try {
			return resultSet.getLong(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public float getFloat(String columnLabel) throws SQLException {
		try {
			return resultSet.getFloat(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public double getDouble(String columnLabel) throws SQLException {
		try {
			return resultSet.getDouble(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	@Deprecated(since="1.2")
	public BigDecimal getBigDecimal(String columnLabel, int scale) throws SQLException {
		try {
			return resultSet.getBigDecimal(columnLabel, scale);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public byte[] getBytes(String columnLabel) throws SQLException {
		try {
			return resultSet.getBytes(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Date getDate(String columnLabel) throws SQLException {
		try {
			return resultSet.getDate(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Time getTime(String columnLabel) throws SQLException {
		try {
			return resultSet.getTime(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Timestamp getTimestamp(String columnLabel) throws SQLException {
		try {
			return resultSet.getTimestamp(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public InputStream getAsciiStream(String columnLabel) throws SQLException {
		try {
			return resultSet.getAsciiStream(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	@Deprecated(since="1.2")
	public InputStream getUnicodeStream(String columnLabel) throws SQLException {
		try {
			return resultSet.getUnicodeStream(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public InputStream getBinaryStream(String columnLabel) throws SQLException {
		try {
			return resultSet.getBinaryStream(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public SQLWarning getWarnings() throws SQLException {
		try {
			return resultSet.getWarnings( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void clearWarnings() throws SQLException {
		try {
			resultSet.clearWarnings( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public String getCursorName() throws SQLException {
		try {
			return resultSet.getCursorName( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public ResultSetMetaData getMetaData() throws SQLException {
		try {
			return resultSet.getMetaData( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Object getObject(int columnIndex) throws SQLException {
		try {
			return resultSet.getObject( columnIndex );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Object getObject(String columnLabel) throws SQLException {
		try {
			return resultSet.getObject( columnLabel );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int findColumn(String columnLabel) throws SQLException {
		try {
			return resultSet.findColumn( columnLabel );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Reader getCharacterStream(int columnIndex) throws SQLException {
		try {
			return resultSet.getCharacterStream( columnIndex );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Reader getCharacterStream(String columnLabel) throws SQLException {
		try {
			return resultSet.getCharacterStream( columnLabel );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public BigDecimal getBigDecimal(int columnIndex) throws SQLException {
		try {
			return resultSet.getBigDecimal( columnIndex );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public BigDecimal getBigDecimal(String columnLabel) throws SQLException {
		try {
			return resultSet.getBigDecimal( columnLabel );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isBeforeFirst() throws SQLException {
		try {
			return resultSet.isBeforeFirst( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isAfterLast() throws SQLException {
		try {
			return resultSet.isAfterLast( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isFirst() throws SQLException {
		try {
			return resultSet.isFirst( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isLast() throws SQLException {
		try {
			return resultSet.isLast( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void beforeFirst() throws SQLException {
		try {
			resultSet.beforeFirst( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public void afterLast() throws SQLException {
		try {
			resultSet.afterLast( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public boolean first() throws SQLException {
		try {
			return resultSet.first( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean last() throws SQLException {
		try {
			return resultSet.last( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getRow() throws SQLException {
		try {
			return resultSet.getRow( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean absolute(int row) throws SQLException {
		try {
			return resultSet.absolute(row);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean relative(int rows) throws SQLException {
		try {
			return resultSet.relative(rows);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean previous() throws SQLException {
		try {
			return resultSet.previous( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setFetchDirection(int direction) throws SQLException {
		try {
			resultSet.setFetchDirection(direction);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getFetchDirection() throws SQLException {
		try {
			return resultSet.getFetchDirection();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setFetchSize(int rows) throws SQLException {
		try {
			resultSet.setFetchSize(rows);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getFetchSize() throws SQLException {
		try {
			return resultSet.getFetchSize();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getType() throws SQLException {
		try {
			return resultSet.getType();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getConcurrency() throws SQLException {
		try {
			return resultSet.getConcurrency();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean rowUpdated() throws SQLException {
		try {
			return resultSet.rowUpdated();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean rowInserted() throws SQLException {
		try {
			return resultSet.rowInserted();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean rowDeleted() throws SQLException {
		try {
			return resultSet.rowDeleted();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNull(int columnIndex) throws SQLException {
		try {
			resultSet.updateNull(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBoolean(int columnIndex, boolean x) throws SQLException {
		try {
			resultSet.updateBoolean(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateByte(int columnIndex, byte x) throws SQLException {
		try {
			resultSet.updateByte(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateShort(int columnIndex, short x) throws SQLException {
		try {
			resultSet.updateShort(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateInt(int columnIndex, int x) throws SQLException {
		try {
			resultSet.updateInt(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateLong(int columnIndex, long x) throws SQLException {
		try {
			resultSet.updateLong(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateFloat(int columnIndex, float x) throws SQLException {
		try {
			resultSet.updateFloat(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateDouble(int columnIndex, double x) throws SQLException {
		try {
			resultSet.updateDouble(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBigDecimal(int columnIndex, BigDecimal x) throws SQLException {
		try {
			resultSet.updateBigDecimal(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateString(int columnIndex, String x) throws SQLException {
		try {
			resultSet.updateString(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBytes(int columnIndex, byte[] x) throws SQLException {
		try {
			resultSet.updateBytes(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateDate(int columnIndex, Date x) throws SQLException {
		try {
			resultSet.updateDate(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateTime(int columnIndex, Time x) throws SQLException {
		try {
			resultSet.updateTime(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateTimestamp(int columnIndex, Timestamp x) throws SQLException {
		try {
			resultSet.updateTimestamp(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateAsciiStream(int columnIndex, InputStream x, int length) throws SQLException {
		try {
			resultSet.updateAsciiStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBinaryStream(int columnIndex, InputStream x, int length) throws SQLException {
		try {
			resultSet.updateBinaryStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateCharacterStream(int columnIndex, Reader x, int length) throws SQLException {
		try {
			resultSet.updateCharacterStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateObject(int columnIndex, Object x, int scaleOrLength) throws SQLException {
		try {
			resultSet.updateObject(columnIndex, x, scaleOrLength);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateObject(int columnIndex, Object x) throws SQLException {
		try {
			resultSet.updateObject(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNull(String columnLabel) throws SQLException {
		try {
			resultSet.updateNull(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBoolean(String columnLabel, boolean x) throws SQLException {
		try {
			resultSet.updateBoolean(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateByte(String columnLabel, byte x) throws SQLException {
		try {
			resultSet.updateByte(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateShort(String columnLabel, short x) throws SQLException {
		try {
			resultSet.updateShort(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateInt(String columnLabel, int x) throws SQLException {
		try {
			resultSet.updateInt(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateLong(String columnLabel, long x) throws SQLException {
		try {
			resultSet.updateLong(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateFloat(String columnLabel, float x) throws SQLException {
		try {
			resultSet.updateFloat(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateDouble(String columnLabel, double x) throws SQLException {
		try {
			resultSet.updateDouble(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBigDecimal(String columnLabel, BigDecimal x) throws SQLException {
		try {
			resultSet.updateBigDecimal(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateString(String columnLabel, String x) throws SQLException {
		try {
			resultSet.updateString(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBytes(String columnLabel, byte[] x) throws SQLException {
		try {
			resultSet.updateBytes(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateDate(String columnLabel, Date x) throws SQLException {
		try {
			resultSet.updateDate(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateTime(String columnLabel, Time x) throws SQLException {
		try {
			resultSet.updateTime(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateTimestamp(String columnLabel, Timestamp x) throws SQLException {
		try {
			resultSet.updateTimestamp(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateAsciiStream(String columnLabel, InputStream x, int length) throws SQLException {
		try {
			resultSet.updateAsciiStream(columnLabel, x, length );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBinaryStream(String columnLabel, InputStream x, int length) throws SQLException {
		try {
			resultSet.updateBinaryStream(columnLabel, x, length );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateCharacterStream(String columnLabel, Reader reader, int length) throws SQLException {
		try {
			resultSet.updateCharacterStream(columnLabel, reader, length );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateObject(String columnLabel, Object x, int scaleOrLength) throws SQLException {
		try {
			resultSet.updateObject(columnLabel, x, scaleOrLength );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateObject(String columnLabel, Object x) throws SQLException {
		try {
			resultSet.updateObject(columnLabel, x );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void insertRow() throws SQLException {
		try {
			resultSet.insertRow();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateRow() throws SQLException {
		try {
			resultSet.updateRow();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void deleteRow() throws SQLException {
		try {
			resultSet.updateRow();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void refreshRow() throws SQLException {
		try {
			resultSet.refreshRow();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void cancelRowUpdates() throws SQLException {
		try {
			resultSet.cancelRowUpdates();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void moveToInsertRow() throws SQLException {
		try {
			resultSet.moveToInsertRow();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void moveToCurrentRow() throws SQLException {
		try {
			resultSet.moveToCurrentRow();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Statement getStatement() throws SQLException {
		try {
			return resultSet.getStatement();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Object getObject(int columnIndex, Map<String, Class<?>> map) throws SQLException {
		try {
			return resultSet.getObject(columnIndex, map);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Ref getRef(int columnIndex) throws SQLException {
		try {
			return resultSet.getRef(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Blob getBlob(int columnIndex) throws SQLException {
		try {
			return resultSet.getBlob(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Clob getClob(int columnIndex) throws SQLException {
		try {
			return resultSet.getClob(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Array getArray(int columnIndex) throws SQLException {
		try {
			return resultSet.getArray(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Object getObject(String columnLabel, Map<String, Class<?>> map) throws SQLException {
		try {
			return resultSet.getObject(columnLabel, map);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Ref getRef(String columnLabel) throws SQLException {
		try {
			return resultSet.getRef(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Blob getBlob(String columnLabel) throws SQLException {
		try {
			return resultSet.getBlob(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Clob getClob(String columnLabel) throws SQLException {
		try {
			return resultSet.getClob(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Array getArray(String columnLabel) throws SQLException {
		try {
			return resultSet.getArray(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Date getDate(int columnIndex, Calendar cal) throws SQLException {
		try {
			return resultSet.getDate(columnIndex, cal);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Date getDate(String columnLabel, Calendar cal) throws SQLException {
		try {
			return resultSet.getDate(columnLabel, cal);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Time getTime(int columnIndex, Calendar cal) throws SQLException {
		try {
			return resultSet.getTime(columnIndex, cal);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Time getTime(String columnLabel, Calendar cal) throws SQLException {
		try {
			return resultSet.getTime(columnLabel, cal);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Timestamp getTimestamp(int columnIndex, Calendar cal) throws SQLException {
		try {
			return resultSet.getTimestamp(columnIndex, cal);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Timestamp getTimestamp(String columnLabel, Calendar cal) throws SQLException {
		try {
			return resultSet.getTimestamp(columnLabel, cal);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public URL getURL(int columnIndex) throws SQLException {
		try {
			return resultSet.getURL(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public URL getURL(String columnLabel) throws SQLException {
		try {
			return resultSet.getURL(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateRef(int columnIndex, Ref x) throws SQLException {
		try {
			resultSet.updateRef(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateRef(String columnLabel, Ref x) throws SQLException {
		try {
			resultSet.updateRef(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBlob(int columnIndex, Blob x) throws SQLException {
		try {
			resultSet.updateBlob(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBlob(String columnLabel, Blob x) throws SQLException {
		try {
			resultSet.updateBlob(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateClob(int columnIndex, Clob x) throws SQLException {
		try {
			resultSet.updateClob(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateClob(String columnLabel, Clob x) throws SQLException {
		try {
			resultSet.updateClob(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateArray(int columnIndex, Array x) throws SQLException {
		try {
			resultSet.updateArray(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateArray(String columnLabel, Array x) throws SQLException {
		try {
			resultSet.updateArray(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public RowId getRowId(int columnIndex) throws SQLException {
		try {
			return resultSet.getRowId(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public RowId getRowId(String columnLabel) throws SQLException {
		try {
			return resultSet.getRowId(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateRowId(int columnIndex, RowId x) throws SQLException {
		try {
			resultSet.updateRowId(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateRowId(String columnLabel, RowId x) throws SQLException {
		try {
			resultSet.updateRowId(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getHoldability() throws SQLException {
		try {
			return resultSet.getHoldability();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isClosed() throws SQLException {
		try {
			return resultSet.isClosed();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNString(int columnIndex, String nString) throws SQLException {
		try {
			resultSet.updateNString(columnIndex, nString);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNString(String columnLabel, String nString) throws SQLException {
		try {
			resultSet.updateNString(columnLabel, nString);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNClob(int columnIndex, NClob nClob) throws SQLException {
		try {
			resultSet.updateNClob(columnIndex, nClob);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNClob(String columnLabel, NClob nClob) throws SQLException {
		try {
			resultSet.updateNClob(columnLabel, nClob);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public NClob getNClob(int columnIndex) throws SQLException {
		try {
			return resultSet.getNClob(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public NClob getNClob(String columnLabel) throws SQLException {
		try {
			return resultSet.getNClob(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public SQLXML getSQLXML(int columnIndex) throws SQLException {
		try {
			return resultSet.getSQLXML(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public SQLXML getSQLXML(String columnLabel) throws SQLException {
		try {
			return resultSet.getSQLXML(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateSQLXML(int columnIndex, SQLXML xmlObject) throws SQLException {
		try {
			resultSet.updateSQLXML(columnIndex, xmlObject);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateSQLXML(String columnLabel, SQLXML xmlObject) throws SQLException {
		try {
			resultSet.updateSQLXML(columnLabel, xmlObject);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getNString(int columnIndex) throws SQLException {
		try {
			return resultSet.getNString(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getNString(String columnLabel) throws SQLException {
		try {
			return resultSet.getNString(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Reader getNCharacterStream(int columnIndex) throws SQLException {
		try {
			return resultSet.getNCharacterStream(columnIndex);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Reader getNCharacterStream(String columnLabel) throws SQLException {
		try {
			return resultSet.getNCharacterStream(columnLabel);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNCharacterStream(int columnIndex, Reader x, long length) throws SQLException {
		try {
			resultSet.updateNCharacterStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNCharacterStream(String columnLabel, Reader reader, long length) throws SQLException {
		try {
			resultSet.updateNCharacterStream(columnLabel, reader, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateAsciiStream(int columnIndex, InputStream x, long length) throws SQLException {
		try {
			resultSet.updateAsciiStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBinaryStream(int columnIndex, InputStream x, long length) throws SQLException {
		try {
			resultSet.updateBinaryStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateCharacterStream(int columnIndex, Reader x, long length) throws SQLException {
		try {
			resultSet.updateCharacterStream(columnIndex, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateAsciiStream(String columnLabel, InputStream x, long length) throws SQLException {
		try {
			resultSet.updateAsciiStream(columnLabel, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBinaryStream(String columnLabel, InputStream x, long length) throws SQLException {
		try {
			resultSet.updateBinaryStream(columnLabel, x, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateCharacterStream(String columnLabel, Reader reader, long length) throws SQLException {
		try {
			resultSet.updateCharacterStream(columnLabel, reader, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBlob(int columnIndex, InputStream inputStream, long length) throws SQLException {
		try {
			resultSet.updateBlob(columnIndex, inputStream, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBlob(String columnLabel, InputStream inputStream, long length) throws SQLException {
		try {
			resultSet.updateBlob(columnLabel, inputStream, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateClob(int columnIndex, Reader reader, long length) throws SQLException {
		try {
			resultSet.updateClob(columnIndex, reader, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateClob(String columnLabel, Reader reader, long length) throws SQLException {
		try {
			resultSet.updateClob(columnLabel, reader, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNClob(int columnIndex, Reader reader, long length) throws SQLException {
		try {
			resultSet.updateNClob(columnIndex, reader, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public void updateNClob(String columnLabel, Reader reader, long length) throws SQLException {
		try {
			resultSet.updateNClob(columnLabel, reader, length);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public void updateNCharacterStream(int columnIndex, Reader x) throws SQLException {
		try {
			resultSet.updateNCharacterStream(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
		
	}

	@Override
	public void updateNCharacterStream(String columnLabel, Reader reader) throws SQLException {
		try {
			resultSet.updateNCharacterStream(columnLabel, reader);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateAsciiStream(int columnIndex, InputStream x) throws SQLException {
		try {
			resultSet.updateAsciiStream(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBinaryStream(int columnIndex, InputStream x) throws SQLException {
		try {
			resultSet.updateBinaryStream(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateCharacterStream(int columnIndex, Reader x) throws SQLException {
		try {
			resultSet.updateCharacterStream(columnIndex, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateAsciiStream(String columnLabel, InputStream x) throws SQLException {
		try {
			resultSet.updateAsciiStream(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBinaryStream(String columnLabel, InputStream x) throws SQLException {
		try {
			resultSet.updateBinaryStream(columnLabel, x);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateCharacterStream(String columnLabel, Reader reader) throws SQLException {
		try {
			resultSet.updateCharacterStream(columnLabel, reader);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBlob(int columnIndex, InputStream inputStream) throws SQLException {
		try {
			resultSet.updateBlob(columnIndex, inputStream);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateBlob(String columnLabel, InputStream inputStream) throws SQLException {
		try {
			resultSet.updateBlob(columnLabel, inputStream);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateClob(int columnIndex, Reader reader) throws SQLException {
		try {
			resultSet.updateClob(columnIndex, reader);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateClob(String columnLabel, Reader reader) throws SQLException {
		try {
			resultSet.updateClob(columnLabel, reader);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNClob(int columnIndex, Reader reader) throws SQLException {
		try {
			resultSet.updateNClob(columnIndex, reader);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void updateNClob(String columnLabel, Reader reader) throws SQLException {
		try {
			resultSet.updateNClob(columnLabel, reader);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public <T> T getObject(int columnIndex, Class<T> type) throws SQLException {
		try {
			return resultSet.getObject(columnIndex, type);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public <T> T getObject(String columnLabel, Class<T> type) throws SQLException {
		try {
			return resultSet.getObject(columnLabel, type);
		}
		catch(Exception exc) {
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
