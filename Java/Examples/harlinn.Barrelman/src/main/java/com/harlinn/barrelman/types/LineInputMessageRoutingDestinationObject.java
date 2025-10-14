package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputMessageRoutingDestinationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _routing;
    private Guid _listener;

    @Override
    public int getObjectType( ) {
        return Kind.LineInputMessageRoutingDestination;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputMessageRoutingDestinationObject( );
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

    public Guid getRouting( ) {
        return _routing;
    }
    public void setRouting( Guid value ) {
        if( !Comparer.equalsGuid( _routing, value ) ) {
            _routing = value;
            onPropertyChanged( );
        }
    }

    public Guid getListener( ) {
        return _listener;
    }
    public void setListener( Guid value ) {
        if( !Comparer.equalsNullableGuid( _listener, value ) ) {
            _listener = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _routing );
        destination.writeNullableGuid( _listener );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _routing = source.readGuid( );
        _listener = source.readNullableGuid( );
    }

}
