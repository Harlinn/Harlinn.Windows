package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticDataReportPartAMessageObject extends AisStaticDataReportMessageObject {

    public final int KIND = Kind.AisStaticDataReportPartAMessage;

    private Guid _shipName;
    private int _spare = 0;

    public AisStaticDataReportPartAMessageObject( ) {
    }
    public AisStaticDataReportPartAMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int partNumber, Guid shipName, int spare ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, partNumber );
        this._shipName = shipName;
        this._spare = spare;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisStaticDataReportPartAMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStaticDataReportPartAMessageObject( );
    }

    public Guid getShipName( ) {
        return _shipName;
    }
    public void setShipName( Guid value ) {
        if( !Comparer.equalsNullableGuid( _shipName, value ) ) {
            _shipName = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisStaticDataReportPartAMessageObject )target;
        targetObject._shipName = this._shipName;
        targetObject._spare = this._spare;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisStaticDataReportPartAMessageObject)obj;
        if( !Comparer.equalsNullableGuid( this._shipName, other._shipName ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _shipName );
        destination.writeInt32( _spare );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _shipName = source.readNullableGuid( );
        _spare = source.readInt32( );
    }

}
