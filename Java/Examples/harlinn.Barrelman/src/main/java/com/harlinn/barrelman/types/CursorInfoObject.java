package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CursorInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private int _typeCode = 0;

    @Override
    public int getObjectType( ) {
        return Kind.CursorInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CursorInfoObject( );
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

    public int getTypeCode( ) {
        return _typeCode;
    }
    public void setTypeCode( int value ) {
        if( !Comparer.equalsInt32( _typeCode, value ) ) {
            _typeCode = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CursorInfoObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._typeCode = this._typeCode;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CursorInfoObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._typeCode, other._typeCode ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeInt32( _typeCode );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _typeCode = source.readInt32( );
    }

}
