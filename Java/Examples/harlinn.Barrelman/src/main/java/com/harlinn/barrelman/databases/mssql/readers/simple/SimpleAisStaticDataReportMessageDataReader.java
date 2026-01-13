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
package com.harlinn.barrelman.databases.mssql.readers.simple;

import java.sql.*;

import com.harlinn.barrelman.types.*;
import com.harlinn.common.data.*;
import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class SimpleAisStaticDataReportMessageDataReader extends SimpleAisMessageDataReader {
    public final static String BaseQuery = "SELECT \r\n" +
            "  asdrm.[Id], \r\n" +
            "  asdrm.[EntityType], \r\n" +
            "  asdrm.[RowVersion], \r\n" +
            "  asdrm.[AisDevice], \r\n" +
            "  asdrm.[ReceivedTimestamp], \r\n" +
            "  asdrm.[MessageSequenceNumber], \r\n" +
            "  asdrm.[Repeat], \r\n" +
            "  asdrm.[Mmsi], \r\n" +
            "  asdrm.[PartNumber] \r\n" +
            "FROM [AisStaticDataReportMessageView] asdrm \r\n";

    public final static String BaseViewName = "AisStaticDataReportMessageView";
    public final static String ViewAliasName = "asdrm";

    public final static int PARTNUMBER_FIELD_ID = 9;

    public SimpleAisStaticDataReportMessageDataReader( ResultSet resultSet ) {
        super( resultSet );
    }

    public final int getPartNumber() throws SQLException {
        return getInt32( PARTNUMBER_FIELD_ID );
    }

    @Override
    public void writeTo(BinaryWriter destination) throws SQLException {
        super.writeTo( destination );
        destination.writeInt32( getPartNumber( ) );
    }

    @Override
    public AisStaticDataReportMessageObject getDataObject( ) throws SQLException {
        return new AisStaticDataReportMessageObject( ObjectState.Stored, getId( ), getRowVersion( ), getAisDevice( ), getReceivedTimestamp( ), getMessageSequenceNumber( ), getRepeat( ), getMmsi( ), getPartNumber( ) );
    }

}
