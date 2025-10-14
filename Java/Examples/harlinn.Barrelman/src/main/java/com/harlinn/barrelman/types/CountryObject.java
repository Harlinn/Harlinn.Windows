package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CountryObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _name = "";
    private int _code = 0;
    private String _alpha2 = "";
    private String _alpha3 = "";

    @Override
    public int getObjectType( ) {
        return Kind.Country;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CountryObject( );
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

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
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

    public String getAlpha2( ) {
        return _alpha2;
    }
    public void setAlpha2( String value ) {
        if( !Comparer.equalsString( _alpha2, value ) ) {
            _alpha2 = value;
            onPropertyChanged( );
        }
    }

    public String getAlpha3( ) {
        return _alpha3;
    }
    public void setAlpha3( String value ) {
        if( !Comparer.equalsString( _alpha3, value ) ) {
            _alpha3 = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _name );
        destination.writeInt32( _code );
        destination.writeStringUtf8( _alpha2 );
        destination.writeStringUtf8( _alpha3 );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _name = source.readString( );
        _code = source.readInt32( );
        _alpha2 = source.readString( );
        _alpha3 = source.readString( );
    }

}
