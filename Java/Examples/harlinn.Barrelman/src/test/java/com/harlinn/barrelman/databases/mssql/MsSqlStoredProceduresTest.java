package com.harlinn.barrelman.databases.mssql;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import com.harlinn.common.data.ConnectionWrapper;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

import com.harlinn.barrelman.databases.mssql.readers.simple.*;
import com.harlinn.barrelman.types.*;

class MsSqlStoredProceduresTest {

	static ConnectionWrapper connection;
	static MsSqlStoredProcedures procedures; 
	
	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		var connectionUrl = "jdbc:sqlserver://localhost;encrypt=true;databaseName=barrelman;integratedSecurity=true;trustServerCertificate=true;";
		var jdbcConnection = DriverManager.getConnection(connectionUrl);
		connection = new ConnectionWrapper(jdbcConnection);
		procedures = new MsSqlStoredProcedures(connection);
	}

	@AfterAll
	static void tearDownAfterClass() throws Exception {
		if (connection != null && !connection.isClosed()) {
            connection.close();
        }
	}

	@Test
	void testGetConnection() throws Exception {
		assertFalse(connection.isClosed());
	}
	
	@Test
	void testInsertAircraftType() throws Exception {
		var id = Guid.fromString("{1504638D-0153-4572-8BBB-5B999FD2A9AE}");
		var name = "AircraftTypeName"; 
		var aircraftType = new AircraftTypeObject(ObjectState.New,id,0,name);
		var inserted = procedures.insertAircraftType(aircraftType);
		assertTrue(inserted);
		
	}
	
	

}
