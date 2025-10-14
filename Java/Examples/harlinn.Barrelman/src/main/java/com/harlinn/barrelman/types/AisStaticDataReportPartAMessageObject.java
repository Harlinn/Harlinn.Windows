package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticDataReportPartAMessageObject extends AisStaticDataReportMessageObject {

    private Guid _shipName;
    private int _spare = 0;

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
