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
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticDataReportMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisStaticDataReportMessage;

    private int _partNumber = 0;

    public AisStaticDataReportMessageObject( ) {
    }
    public AisStaticDataReportMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int partNumber ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._partNumber = partNumber;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisStaticDataReportMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStaticDataReportMessageObject( );
    }

    public int getPartNumber( ) {
        return _partNumber;
    }
    public void setPartNumber( int value ) {
        if( !Comparer.equalsInt32( _partNumber, value ) ) {
            _partNumber = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisStaticDataReportMessageObject )target;
        targetObject._partNumber = this._partNumber;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisStaticDataReportMessageObject)obj;
        if( !Comparer.equalsInt32( this._partNumber, other._partNumber ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _partNumber );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _partNumber = source.readInt32( );
    }

}
