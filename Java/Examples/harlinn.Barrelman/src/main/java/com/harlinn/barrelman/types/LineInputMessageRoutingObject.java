package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputMessageRoutingObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _lineInputDevice;
    private String _type = "";

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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getLineInputDevice( ) {
        return _lineInputDevice;
    }
    public void setLineInputDevice( Guid value ) {
        if( _lineInputDevice != value ) {
            this._lineInputDevice = value;
            onPropertyChanged( );
        }
    }

    public String getType( ) {
        return _type;
    }
    public void setType( String value ) {
        if( _type != value ) {
            this._type = value;
            onPropertyChanged( );
        }
    }


}
