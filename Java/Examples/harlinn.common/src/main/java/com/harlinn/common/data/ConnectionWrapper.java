package com.harlinn.common.data;

import java.sql.Array;
import java.sql.Blob;
import java.sql.CallableStatement;
import java.sql.Clob;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.NClob;
import java.sql.PreparedStatement;
import java.sql.SQLClientInfoException;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.SQLXML;
import java.sql.Savepoint;
import java.sql.Statement;
import java.sql.Struct;
import java.util.Map;
import java.util.Properties;
import java.util.concurrent.Executor;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ConnectionWrapper implements Connection, AutoCloseable {
	static Logger logger = LoggerFactory.getLogger(ConnectionWrapper.class);
	
	public Connection connection;
	
	public ConnectionWrapper(Connection connection) {
		this.connection = connection;
	}
	

	@Override
	public <T> T unwrap(Class<T> iface) throws SQLException {
		try {
			return connection.unwrap(iface);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isWrapperFor(Class<?> iface) throws SQLException {
		try {
			return connection.isWrapperFor(iface);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Statement createStatement() throws SQLException {
		try {
			var statement = connection.createStatement();
			return new StatementWrapper(this, statement);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public PreparedStatement prepareStatement(String sql) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql);
			return new PreparedStatementWrapper(this, preparedStatement);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public CallableStatement prepareCall(String sql) throws SQLException {
		try {
			var callableStatement = connection.prepareCall(sql);
			return new CallableStatementWrapper(this, callableStatement);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}
	
	public CallableStatementWrapper prepareCallEx(String sql) throws SQLException {
		try {
			var callableStatement = connection.prepareCall(sql);
			return new CallableStatementWrapper(this, callableStatement);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String nativeSQL(String sql) throws SQLException {
		try {
			return connection.nativeSQL(sql);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setAutoCommit(boolean autoCommit) throws SQLException {
		try {
			connection.setAutoCommit(autoCommit);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean getAutoCommit() throws SQLException {
		try {
			return connection.getAutoCommit( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void commit() throws SQLException {
		try {
			connection.commit();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void rollback() throws SQLException {
		try {
			connection.rollback();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void close() throws SQLException {
		try {
			connection.close();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isClosed() throws SQLException {
		try {
			return connection.isClosed();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public DatabaseMetaData getMetaData() throws SQLException {
		try {
			return connection.getMetaData();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setReadOnly(boolean readOnly) throws SQLException {
		try {
			connection.setReadOnly(readOnly);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isReadOnly() throws SQLException {
		try {
			return connection.isReadOnly( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setCatalog(String catalog) throws SQLException {
		try {
			connection.setCatalog(catalog);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getCatalog() throws SQLException {
		try {
			return connection.getCatalog();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setTransactionIsolation(int level) throws SQLException {
		try {
			connection.setTransactionIsolation(level);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getTransactionIsolation() throws SQLException {
		try {
			return connection.getTransactionIsolation();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public SQLWarning getWarnings() throws SQLException {
		try {
			return connection.getWarnings();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void clearWarnings() throws SQLException {
		try {
			connection.clearWarnings();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Statement createStatement(int resultSetType, int resultSetConcurrency) throws SQLException {
		try {
			var statement = connection.createStatement(resultSetType, resultSetConcurrency);
			return new StatementWrapper(this, statement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public PreparedStatement prepareStatement(String sql, int resultSetType, int resultSetConcurrency) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql, resultSetType, resultSetConcurrency);
			return new PreparedStatementWrapper(this, preparedStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}
	public PreparedStatementWrapper prepareStatementEx(String sql, int resultSetType, int resultSetConcurrency) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql, resultSetType, resultSetConcurrency);
			return new PreparedStatementWrapper(this, preparedStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public CallableStatement prepareCall(String sql, int resultSetType, int resultSetConcurrency) throws SQLException {
		try {
			var callableStatement = connection.prepareCall(sql, resultSetType, resultSetConcurrency);
			return new CallableStatementWrapper(this, callableStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Map<String, Class<?>> getTypeMap() throws SQLException {
		try {
			return connection.getTypeMap();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setTypeMap(Map<String, Class<?>> map) throws SQLException {
		try {
			connection.setTypeMap(map);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setHoldability(int holdability) throws SQLException {
		try {
			connection.setHoldability(holdability);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getHoldability() throws SQLException {
		try {
			return connection.getHoldability( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Savepoint setSavepoint() throws SQLException {
		try {
			return connection.setSavepoint( );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Savepoint setSavepoint(String name) throws SQLException {
		try {
			return connection.setSavepoint( name );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void rollback(Savepoint savepoint) throws SQLException {
		try {
			connection.rollback( savepoint );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void releaseSavepoint(Savepoint savepoint) throws SQLException {
		try {
			connection.releaseSavepoint( savepoint );
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Statement createStatement(int resultSetType, int resultSetConcurrency, int resultSetHoldability) throws SQLException {
		try {
			var statement = connection.createStatement(resultSetType, resultSetConcurrency, resultSetHoldability);
			return new StatementWrapper(this, statement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public PreparedStatement prepareStatement(String sql, int resultSetType, int resultSetConcurrency, int resultSetHoldability) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql, resultSetType, resultSetConcurrency, resultSetHoldability);
			return new PreparedStatementWrapper(this, preparedStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public CallableStatement prepareCall(String sql, int resultSetType, int resultSetConcurrency, int resultSetHoldability) throws SQLException {
		try {
			var callableStatement = connection.prepareCall(sql, resultSetType, resultSetConcurrency, resultSetHoldability);
			return new CallableStatementWrapper(this, callableStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public PreparedStatement prepareStatement(String sql, int autoGeneratedKeys) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql, autoGeneratedKeys);
			return new PreparedStatementWrapper(this, preparedStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public PreparedStatement prepareStatement(String sql, int[] columnIndexes) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql, columnIndexes);
			return new PreparedStatementWrapper(this, preparedStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public PreparedStatement prepareStatement(String sql, String[] columnNames) throws SQLException {
		try {
			var preparedStatement = connection.prepareStatement(sql, columnNames);
			return new PreparedStatementWrapper(this, preparedStatement); 
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Clob createClob() throws SQLException {
		try {
			return connection.createClob();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Blob createBlob() throws SQLException {
		try {
			return connection.createBlob();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public NClob createNClob() throws SQLException {
		try {
			return connection.createNClob();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public SQLXML createSQLXML() throws SQLException {
		try {
			return connection.createSQLXML();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public boolean isValid(int timeout) throws SQLException {
		try {
			return connection.isValid(timeout);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setClientInfo(String name, String value) throws SQLClientInfoException {
		try {
			connection.setClientInfo(name, value);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setClientInfo(Properties properties) throws SQLClientInfoException {
		try {
			connection.setClientInfo(properties);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getClientInfo(String name) throws SQLException {
		try {
			return connection.getClientInfo(name);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Properties getClientInfo() throws SQLException {
		try {
			return connection.getClientInfo();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Array createArrayOf(String typeName, Object[] elements) throws SQLException {
		try {
			return connection.createArrayOf(typeName, elements);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public Struct createStruct(String typeName, Object[] attributes) throws SQLException {
		try {
			return connection.createStruct(typeName, attributes);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setSchema(String schema) throws SQLException {
		try {
			connection.setSchema(schema);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public String getSchema() throws SQLException {
		try {
			return connection.getSchema();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void abort(Executor executor) throws SQLException {
		try {
			connection.abort(executor);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public void setNetworkTimeout(Executor executor, int milliseconds) throws SQLException {
		try {
			connection.setNetworkTimeout(executor, milliseconds);
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}

	@Override
	public int getNetworkTimeout() throws SQLException {
		try {
			return connection.getNetworkTimeout();
		}
		catch(Exception exc) {
			logger.error("Exception", exc);
			throw exc; 
		}
	}
	
	

}
