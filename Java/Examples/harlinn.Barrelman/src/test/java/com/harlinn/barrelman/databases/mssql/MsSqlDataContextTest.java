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

class MsSqlDataContextTest {

	static ConnectionWrapper connection;
	static MsSqlDataContext dataContext; 
	
	@BeforeAll
	static void setUpBeforeClass() throws Exception {
		var connectionUrl = "jdbc:sqlserver://localhost;encrypt=true;databaseName=barrelman;integratedSecurity=true;trustServerCertificate=true;";
		var jdbcConnection = DriverManager.getConnection(connectionUrl);
		connection = new ConnectionWrapper(jdbcConnection);
		dataContext = new MsSqlDataContext(connection, Guid.newGuid());
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
	
	/**
	 * Test CRUD for AircraftType
	 * 
	 * @throws Exception
	 */
	@Test
	void testAircraftTypeCRUD() throws Exception {
		var id = Guid.fromString("{1504638D-0153-4572-8BBB-5B999FD2A9AE}");
		var name1 = "AircraftTypeName1"; 
		var name2 = "AircraftTypeName2";
		var aircraftType = new AircraftTypeObject(ObjectState.New,id,0,name1);
		var existingAircraftType = dataContext.getAircraftTypeById(id);
		if(existingAircraftType != null) {
			var deleted = dataContext.deleteObject(existingAircraftType);
			assertTrue(deleted);
			var notFoundAircraftType = dataContext.getAircraftTypeById(id);
			assertNull(notFoundAircraftType);
		}
		var inserted = dataContext.insertObject(aircraftType);
		assertTrue(inserted);
		var insertedAircraftType = dataContext.getAircraftTypeById(id);
		var areEqual = insertedAircraftType.equals(aircraftType);
		assertTrue(areEqual);
		
		aircraftType.setName(name2);
		var updated = dataContext.updateObject(aircraftType);
		assertTrue(updated);
		var updatedAircraftType = dataContext.getAircraftTypeById(id);
		areEqual = updatedAircraftType.equals(aircraftType);
		assertTrue(areEqual);
		
	}
	
	

}
