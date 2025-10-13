package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaServiceOptionsObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _mediaService;
    private DateTime _timestamp;
    private int _rtspPortNumber = 0;
    private int _httpPortNumber = 0;

    @Override
    public int getObjectType( ) {
        return Kind.MediaServiceOptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaServiceOptionsObject( );
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

    public Guid getMediaService( ) {
        return _mediaService;
    }
    public void setMediaService( Guid value ) {
        if( _mediaService != value ) {
            this._mediaService = value;
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

    public int getRtspPortNumber( ) {
        return _rtspPortNumber;
    }
    public void setRtspPortNumber( int value ) {
        if( _rtspPortNumber != value ) {
            this._rtspPortNumber = value;
            onPropertyChanged( );
        }
    }

    public int getHttpPortNumber( ) {
        return _httpPortNumber;
    }
    public void setHttpPortNumber( int value ) {
        if( _httpPortNumber != value ) {
            this._httpPortNumber = value;
            onPropertyChanged( );
        }
    }


}
