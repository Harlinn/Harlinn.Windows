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
        if( _sequenceNumber != value ) {
            this._sequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public Guid getDestinationMmsi( ) {
        return _destinationMmsi;
    }
    public void setDestinationMmsi( Guid value ) {
        if( _destinationMmsi != value ) {
            this._destinationMmsi = value;
            onPropertyChanged( );
        }
    }

    public boolean getRetransmitFlag( ) {
        return _retransmitFlag;
    }
    public void setRetransmitFlag( boolean value ) {
        if( _retransmitFlag != value ) {
            this._retransmitFlag = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( _spare != value ) {
            this._spare = value;
            onPropertyChanged( );
        }
    }

    public String getText( ) {
        return _text;
    }
    public void setText( String value ) {
        if( _text != value ) {
            this._text = value;
            onPropertyChanged( );
        }
    }


}
