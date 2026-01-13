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

public class AisUtcAndDateInquiryMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisUtcAndDateInquiryMessage;

    private int _spare1 = 0;
    private Guid _destinationMmsi;
    private int _spare2 = 0;

    public AisUtcAndDateInquiryMessageObject( ) {
    }
    public AisUtcAndDateInquiryMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int spare1, Guid destinationMmsi, int spare2 ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._spare1 = spare1;
        this._destinationMmsi = destinationMmsi;
        this._spare2 = spare2;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisUtcAndDateInquiryMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisUtcAndDateInquiryMessageObject( );
    }

    public int getSpare1( ) {
        return _spare1;
    }
    public void setSpare1( int value ) {
        if( !Comparer.equalsInt32( _spare1, value ) ) {
            _spare1 = value;
            onPropertyChanged( );
        }
    }

    public Guid getDestinationMmsi( ) {
        return _destinationMmsi;
    }
    public void setDestinationMmsi( Guid value ) {
        if( !Comparer.equalsNullableGuid( _destinationMmsi, value ) ) {
            _destinationMmsi = value;
            onPropertyChanged( );
        }
    }

    public int getSpare2( ) {
        return _spare2;
    }
    public void setSpare2( int value ) {
        if( !Comparer.equalsInt32( _spare2, value ) ) {
            _spare2 = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisUtcAndDateInquiryMessageObject )target;
        targetObject._spare1 = this._spare1;
        targetObject._destinationMmsi = this._destinationMmsi;
        targetObject._spare2 = this._spare2;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisUtcAndDateInquiryMessageObject)obj;
        if( !Comparer.equalsInt32( this._spare1, other._spare1 ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._destinationMmsi, other._destinationMmsi ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare2, other._spare2 ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _spare1 );
        destination.writeNullableGuid( _destinationMmsi );
        destination.writeInt32( _spare2 );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _spare1 = source.readInt32( );
        _destinationMmsi = source.readNullableGuid( );
        _spare2 = source.readInt32( );
    }

}
