package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisBinaryAddressedMessageObject extends AisMessageObject {

    private int _sequenceNumber = 0;
    private Guid _destinationMmsi;
    private boolean _retransmitFlag = false;
    private int _spare = 0;
    private int _designatedAreaCode = 0;
    private int _functionalId = 0;
    private String _data = "";

    @Override
    public int getObjectType( ) {
        return Kind.AisBinaryAddressedMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisBinaryAddressedMessageObject( );
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

    public int getDesignatedAreaCode( ) {
        return _designatedAreaCode;
    }
    public void setDesignatedAreaCode( int value ) {
        if( _designatedAreaCode != value ) {
            this._designatedAreaCode = value;
            onPropertyChanged( );
        }
    }

    public int getFunctionalId( ) {
        return _functionalId;
    }
    public void setFunctionalId( int value ) {
        if( _functionalId != value ) {
            this._functionalId = value;
            onPropertyChanged( );
        }
    }

    public String getData( ) {
        return _data;
    }
    public void setData( String value ) {
        if( _data != value ) {
            this._data = value;
            onPropertyChanged( );
        }
    }


}
