package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CollectionInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private long _count = 0;

    @Override
    public int getObjectType( ) {
        return Kind.CollectionInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CollectionInfoObject( );
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

    public long getCount( ) {
        return _count;
    }
    public void setCount( long value ) {
        if( !Comparer.equalsInt64( _count, value ) ) {
            _count = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( CollectionInfoObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._count = this._count;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (CollectionInfoObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._count, other._count ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeInt64( _count );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _count = source.readInt64( );
    }

}
