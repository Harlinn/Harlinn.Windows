package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class IdentityObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( IdentityObject )target;
        targetObject._rowVersion = this._rowVersion;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (IdentityObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
    }

}
