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

public class AisAddressedSafetyRelatedMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisAddressedSafetyRelatedMessage;

    private int _sequenceNumber = 0;
    private Guid _destinationMmsi;
    private boolean _retransmitFlag = false;
    private int _spare = 0;
    private String _text = "";

    public AisAddressedSafetyRelatedMessageObject( ) {
    }
    public AisAddressedSafetyRelatedMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int sequenceNumber, Guid destinationMmsi, boolean retransmitFlag, int spare, String text ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._sequenceNumber = sequenceNumber;
        this._destinationMmsi = destinationMmsi;
        this._retransmitFlag = retransmitFlag;
        this._spare = spare;
        this._text = text;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisAddressedSafetyRelatedMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAddressedSafetyRelatedMessageObject( );
    }

    public int getSequenceNumber( ) {
        return _sequenceNumber;
    }
    public void setSequenceNumber( int value ) {
        if( !Comparer.equalsInt32( _sequenceNumber, value ) ) {
            _sequenceNumber = value;
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

    public boolean getRetransmitFlag( ) {
        return _retransmitFlag;
    }
    public void setRetransmitFlag( boolean value ) {
        if( !Comparer.equalsBoolean( _retransmitFlag, value ) ) {
            _retransmitFlag = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( !Comparer.equalsInt32( _spare, value ) ) {
            _spare = value;
            onPropertyChanged( );
        }
    }

    public String getText( ) {
        return _text;
    }
    public void setText( String value ) {
        if( !Comparer.equalsString( _text, value ) ) {
            _text = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisAddressedSafetyRelatedMessageObject )target;
        targetObject._sequenceNumber = this._sequenceNumber;
        targetObject._destinationMmsi = this._destinationMmsi;
        targetObject._retransmitFlag = this._retransmitFlag;
        targetObject._spare = this._spare;
        targetObject._text = this._text;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisAddressedSafetyRelatedMessageObject)obj;
        if( !Comparer.equalsInt32( this._sequenceNumber, other._sequenceNumber ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._destinationMmsi, other._destinationMmsi ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._retransmitFlag, other._retransmitFlag ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._text, other._text ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _sequenceNumber );
        destination.writeNullableGuid( _destinationMmsi );
        destination.writeBoolean( _retransmitFlag );
        destination.writeInt32( _spare );
        destination.writeStringUtf8( _text );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _sequenceNumber = source.readInt32( );
        _destinationMmsi = source.readNullableGuid( );
        _retransmitFlag = source.readBoolean( );
        _spare = source.readInt32( );
        _text = source.readString( );
    }

}
