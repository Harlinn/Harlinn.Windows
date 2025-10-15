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
