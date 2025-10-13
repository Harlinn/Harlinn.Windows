package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class LineInputWhiteListEntryObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _lineInputDevice;
    private String _hostName = "";
    private int _port = 0;

    @Override
    public int getObjectType( ) {
        return Kind.LineInputWhiteListEntry;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new LineInputWhiteListEntryObject( );
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

    public String getHostName( ) {
        return _hostName;
    }
    public void setHostName( String value ) {
        if( _hostName != value ) {
            this._hostName = value;
            onPropertyChanged( );
        }
    }

    public int getPort( ) {
        return _port;
    }
    public void setPort( int value ) {
        if( _port != value ) {
            this._port = value;
            onPropertyChanged( );
        }
    }


}
