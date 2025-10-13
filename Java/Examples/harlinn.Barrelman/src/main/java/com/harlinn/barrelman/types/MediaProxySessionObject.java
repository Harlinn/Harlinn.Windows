package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaProxySessionObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _service;
    private String _name = "";
    private Guid _enabledTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySession;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionObject( );
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

    public Guid getService( ) {
        return _service;
    }
    public void setService( Guid value ) {
        if( _service != value ) {
            this._service = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
            onPropertyChanged( );
        }
    }

    public Guid getEnabledTimeseries( ) {
        return _enabledTimeseries;
    }
    public void setEnabledTimeseries( Guid value ) {
        if( _enabledTimeseries != value ) {
            this._enabledTimeseries = value;
            onPropertyChanged( );
        }
    }


}
