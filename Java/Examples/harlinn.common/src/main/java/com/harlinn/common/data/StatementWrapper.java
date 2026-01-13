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
package com.harlinn.common.data;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.Statement;
import java.util.Objects;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class StatementWrapper implements Statement, AutoCloseable {
	static Logger logger = LoggerFactory.getLogger(StatementWrapper.class);
	
	Statement statement;
	ConnectionWrapper connection; 
	
	public StatementWrapper(Statement statement) throws SQLException {
		Objects.requireNonNull(statement);
		this.statement = statement;
		this.connection = new ConnectionWrapper(statement.getConnection());
	}
	
	public StatementWrapper(ConnectionWrapper connectionWrapper,Statement statement) throws SQLException {
		Objects.requireNonNull(statement);
		this.statement = statement;
		this.connection = connectionWrapper;
	}
	

	Statement getStatement() {
		return statement;
	}
	
	
	@Override
	public <T> T unwrap(Class<T> iface) throws SQLException {
		try {
			return getStatement().unwrap(iface);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean isWrapperFor(Class<?> iface) throws SQLException {
		try {
			return getStatement().isWrapperFor(iface);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public ResultSet executeQuery(String sql) throws SQLException {
		try {
			var resultSet = getStatement().executeQuery(sql);
			return new ResultSetWrapper( resultSet );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int executeUpdate(String sql) throws SQLException {
		try {
			return getStatement().executeUpdate(sql);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void close() throws SQLException {
		try {
			getStatement().close( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getMaxFieldSize() throws SQLException {
		try {
			return getStatement().getMaxFieldSize( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setMaxFieldSize(int max) throws SQLException {
		try {
			getStatement().setMaxFieldSize(max);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getMaxRows() throws SQLException {
		try {
			return getStatement().getMaxRows( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setMaxRows(int max) throws SQLException {
		try {
			getStatement().setMaxRows(max);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setEscapeProcessing(boolean enable) throws SQLException {
		try {
			getStatement().setEscapeProcessing(enable);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getQueryTimeout() throws SQLException {
		try {
			return getStatement().getQueryTimeout();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setQueryTimeout(int seconds) throws SQLException {
		try {
			getStatement().setMaxRows(seconds);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void cancel() throws SQLException {
		try {
			getStatement().cancel( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public SQLWarning getWarnings() throws SQLException {
		try {
			return getStatement().getWarnings( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void clearWarnings() throws SQLException {
		try {
			getStatement().clearWarnings( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setCursorName(String name) throws SQLException {
		try {
			getStatement().setCursorName(name);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean execute(String sql) throws SQLException {
		try {
			return getStatement().execute(sql);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public ResultSet getResultSet() throws SQLException {
		try {
			var resultSet = getStatement().getResultSet( );
			return new ResultSetWrapper(resultSet);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getUpdateCount() throws SQLException {
		try {
			return getStatement().getUpdateCount( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean getMoreResults() throws SQLException {
		try {
			return getStatement().getMoreResults( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setFetchDirection(int direction) throws SQLException {
		try {
			getStatement().setFetchDirection(direction);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getFetchDirection() throws SQLException {
		try {
			return getStatement().getFetchDirection( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setFetchSize(int rows) throws SQLException {
		try {
			getStatement().setFetchSize(rows);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getFetchSize() throws SQLException {
		try {
			return getStatement().getFetchSize();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getResultSetConcurrency() throws SQLException {
		try {
			return getStatement().getResultSetConcurrency();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getResultSetType() throws SQLException {
		try {
			return getStatement().getResultSetType();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void addBatch(String sql) throws SQLException {
		try {
			getStatement().addBatch(sql);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void clearBatch() throws SQLException {
		try {
			getStatement().clearBatch( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int[] executeBatch() throws SQLException {
		try {
			return getStatement().executeBatch( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public Connection getConnection() throws SQLException {
		return connection;
	}

	@Override
	public boolean getMoreResults(int current) throws SQLException {
		try {
			return getStatement().getMoreResults( current );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public ResultSet getGeneratedKeys() throws SQLException {
		try {
			var resultSet = getStatement().getGeneratedKeys();
			return new ResultSetWrapper(resultSet);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int executeUpdate(String sql, int autoGeneratedKeys) throws SQLException {
		try {
			return getStatement().executeUpdate( sql, autoGeneratedKeys );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int executeUpdate(String sql, int[] columnIndexes) throws SQLException {
		try {
			return getStatement().executeUpdate( sql, columnIndexes );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int executeUpdate(String sql, String[] columnNames) throws SQLException {
		try {
			return getStatement().executeUpdate( sql, columnNames );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean execute(String sql, int autoGeneratedKeys) throws SQLException {
		try {
			return getStatement().execute( sql, autoGeneratedKeys );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean execute(String sql, int[] columnIndexes) throws SQLException {
		try {
			return getStatement().execute( sql, columnIndexes );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean execute(String sql, String[] columnNames) throws SQLException {
		try {
			return getStatement().execute( sql, columnNames );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public int getResultSetHoldability() throws SQLException {
		try {
			return getStatement().getResultSetHoldability( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean isClosed() throws SQLException {
		try {
			return getStatement().isClosed( );
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void setPoolable(boolean poolable) throws SQLException {
		try {
			getStatement().setPoolable(poolable);
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean isPoolable() throws SQLException {
		try {
			return getStatement().isPoolable();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public void closeOnCompletion() throws SQLException {
		try {
			getStatement().closeOnCompletion();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}

	@Override
	public boolean isCloseOnCompletion() throws SQLException {
		try {
			return getStatement().isCloseOnCompletion();
		}
		catch (Exception exc) {
			logger.error("Exception", exc);
			throw exc;
		}
	}
	
	

}
