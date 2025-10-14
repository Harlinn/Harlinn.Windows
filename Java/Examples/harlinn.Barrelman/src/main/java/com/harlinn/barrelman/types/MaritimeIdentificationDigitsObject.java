package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MaritimeIdentificationDigitsObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private int _code = 0;
    private Guid _country;

    @Override
    public int getObjectType( ) {
        return Kind.MaritimeIdentificationDigits;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MaritimeIdentificationDigitsObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public int getCode( ) {
        return _code;
    }
    public void setCode( int value ) {
        if( !Comparer.equalsInt32( _code, value ) ) {
            _code = value;
            onPropertyChanged( );
        }
    }

    public Guid getCountry( ) {
        return _country;
    }
    public void setCountry( Guid value ) {
        if( !Comparer.equalsGuid( _country, value ) ) {
            _country = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeInt32( _code );
        destination.writeGuid( _country );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _code = source.readInt32( );
        _country = source.readGuid( );
    }

}
