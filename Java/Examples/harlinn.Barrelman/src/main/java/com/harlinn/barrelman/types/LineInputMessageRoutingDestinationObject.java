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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRouting( ) {
        return _routing;
    }
    public void setRouting( Guid value ) {
        if( _routing != value ) {
            this._routing = value;
            onPropertyChanged( );
        }
    }

    public Guid getListener( ) {
        return _listener;
    }
    public void setListener( Guid value ) {
        if( _listener != value ) {
            this._listener = value;
            onPropertyChanged( );
        }
    }


}
