package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ItemParentChildLinkObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _parent;
    private Guid _child;
    private DateTime _timestamp;

    @Override
    public int getObjectType( ) {
        return Kind.ItemParentChildLink;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ItemParentChildLinkObject( );
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

    public Guid getParent( ) {
        return _parent;
    }
    public void setParent( Guid value ) {
        if( !Comparer.equalsGuid( _parent, value ) ) {
            _parent = value;
            onPropertyChanged( );
        }
    }

    public Guid getChild( ) {
        return _child;
    }
    public void setChild( Guid value ) {
        if( !Comparer.equalsGuid( _child, value ) ) {
            _child = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ItemParentChildLinkObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._parent = this._parent;
        targetObject._child = this._child;
        targetObject._timestamp = this._timestamp;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ItemParentChildLinkObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._parent, other._parent ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._child, other._child ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _parent );
        destination.writeGuid( _child );
        destination.writeDateTime( _timestamp );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _parent = source.readGuid( );
        _child = source.readGuid( );
        _timestamp = source.readDateTime( );
    }

}
