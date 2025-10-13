package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaProxySessionFileObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _proxySession;
    private DateTime _timestamp;
    private String _streamName = "";

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySessionFile;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionFileObject( );
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

    public Guid getProxySession( ) {
        return _proxySession;
    }
    public void setProxySession( Guid value ) {
        if( _proxySession != value ) {
            this._proxySession = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public String getStreamName( ) {
        return _streamName;
    }
    public void setStreamName( String value ) {
        if( _streamName != value ) {
            this._streamName = value;
            onPropertyChanged( );
        }
    }


}
