package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputMessageRoutingObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.LineInputMessageRouting;

    private long _rowVersion = 0;
    private Guid _lineInputDevice;
    private String _type = "";

    public LineInputMessageRoutingObject( ) {
    }
    public LineInputMessageRoutingObject( byte objectState, Guid id, long rowVersion, Guid lineInputDevice, String type ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._lineInputDevice = lineInputDevice;
        this._type = type;
    }

    @Override
    public int getObjectType( ) {
        return Kind.LineInputMessageRouting;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputMessageRoutingObject( );
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

    public Guid getLineInputDevice( ) {
        return _lineInputDevice;
    }
    public void setLineInputDevice( Guid value ) {
        if( !Comparer.equalsGuid( _lineInputDevice, value ) ) {
            _lineInputDevice = value;
            onPropertyChanged( );
        }
    }

    public String getType( ) {
        return _type;
    }
    public void setType( String value ) {
        if( !Comparer.equalsString( _type, value ) ) {
            _type = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( LineInputMessageRoutingObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._lineInputDevice = this._lineInputDevice;
        targetObject._type = this._type;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (LineInputMessageRoutingObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._lineInputDevice, other._lineInputDevice ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._type, other._type ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _lineInputDevice );
        destination.writeStringUtf8( _type );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _lineInputDevice = source.readGuid( );
        _type = source.readString( );
    }

}
