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
package com.harlinn.barrelman.databases.mssql;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import com.harlinn.common.data.ConnectionWrapper;
import com.harlinn.common.serialization.DataReader;
import com.harlinn.common.serialization.DataWriter;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

import com.harlinn.barrelman.databases.mssql.readers.simple.*;
import com.harlinn.barrelman.types.*;
import com.harlinn.barrelman.types.DataObjectFactory;

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
	
	@Test
	void testCreateAndDelete() throws Exception {
		var testDataObjectFactory = new TestDataObjectFactory();
		var dataObjectFactory = new DataObjectFactory();
		
		var dataObjects = testDataObjectFactory.getDataObjects();
		var count = dataObjects.length;
		
		var reversedDataObjects = new AbstractDataObjectWithGuidKey[count];
	    for (int i = 0; i < count; i++) {
	    	reversedDataObjects[i] = dataObjects[count - 1 - i];
	    }
	    
	    for (int i = 0; i < count; i++) {
	    	var dataObject = reversedDataObjects[i];
	    	dataContext.deleteObject(dataObject);
	    }
	    
	    for (int i = 0; i < count; i++) {
	    	var dataObject = dataObjects[i];
	    	var className = dataObject.getClass().getName();
	    	if(className == "com.harlinn.barrelman.types.AisAddressedSafetyRelatedMessageObject") {
	    		var foundDataObject = dataContext.findObject(dataObject.getId(), dataObject.getObjectType());
	    		if( foundDataObject != null) {
	    			System.out.append("Found: " + className);
	    		}
	    		System.out.append("Inserting: " + className);
	    	}
	    	var inserted = dataContext.insertObject(dataObject);
	    	if(inserted == false) {
	    		System.out.append("Not inserted: " + className + " i:"+i);
	    		
	    	}
	    	assertTrue(inserted,"Not inserted: " + dataObject.getClass().getName());
	    }
	    
	    for (int i = 0; i < count; i++) {
	    	var dataObject = dataObjects[i];
	    	var foundDataObject = dataContext.findObject(dataObject.getId(), dataObject.getObjectType());
	    	assertNotNull(foundDataObject);
	    }
	    
	    for (int i = 0; i < count; i++) {
	    	var dataObject = reversedDataObjects[i];
	    	var deleted = dataContext.deleteObject(dataObject);
	    	assertTrue(deleted);
	    }
		
	}
	
	

}
