package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CountryObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.Country;

    private long _rowVersion = 0;
    private String _name = "";
    private int _code = 0;
    private String _alpha2 = "";
    private String _alpha3 = "";

    public CountryObject( ) {
    }
    public CountryObject( byte objectState, Guid id, long rowVersion, String name, int code, String alpha2, String alpha3 ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._name = name;
        this._code = code;
        this._alpha2 = alpha2;
        this._alpha3 = alpha3;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CountryObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._name = this._name;
        targetObject._code = this._code;
        targetObject._alpha2 = this._alpha2;
        targetObject._alpha3 = this._alpha3;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CountryObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._code, other._code ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._alpha2, other._alpha2 ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._alpha3, other._alpha3 ) ) {
            return false;
        }
        return true;
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
