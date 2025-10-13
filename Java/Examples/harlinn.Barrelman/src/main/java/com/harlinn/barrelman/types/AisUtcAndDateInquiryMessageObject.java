package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisUtcAndDateInquiryMessageObject extends AisMessageObject {

    private int _spare1 = 0;
    private Guid _destinationMmsi;
    private int _spare2 = 0;

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
        if( _spare1 != value ) {
            this._spare1 = value;
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

    public int getSpare2( ) {
        return _spare2;
    }
    public void setSpare2( int value ) {
        if( _spare2 != value ) {
            this._spare2 = value;
            onPropertyChanged( );
        }
    }


}
