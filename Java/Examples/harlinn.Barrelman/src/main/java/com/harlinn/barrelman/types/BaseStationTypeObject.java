package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class BaseStationTypeObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.BaseStationType;

    private long _rowVersion = 0;
    private String _name = "";

    public BaseStationTypeObject( ) {
    }
    public BaseStationTypeObject( byte objectState, Guid id, long rowVersion, String name ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._name = name;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BaseStationType;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BaseStationTypeObject( );
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BaseStationTypeObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._name = this._name;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BaseStationTypeObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _name );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _name = source.readString( );
    }

}
