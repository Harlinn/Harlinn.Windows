package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisAddressedSafetyRelatedMessageObject extends AisMessageObject {

    private int _sequenceNumber = 0;
    private Guid _destinationMmsi;
    private boolean _retransmitFlag = false;
    private int _spare = 0;
    private String _text = "";

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
