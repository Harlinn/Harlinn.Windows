package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MediaProxySessionOptionsObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _proxySession;
    private DateTime _timestamp;
    private String _sourceStreamUrl = "";
    private String _streamName = "";
    private int _mode = MediaProxySessionMode.Unknown;
    private int _tunnelOverHTTPPortNumber = 0;
    private String _username = "";
    private String _password = "";
    private int _recorderPortNumber = 0;
    private int _sessionType = MediaProxySessionType.Unknown;
    private TimeSpan _maxFileTime;
    private TimeSpan _maxFileRetention;
    private String _videoDirectory = "";

    @Override
    public int getObjectType( ) {
        return Kind.MediaProxySessionOptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MediaProxySessionOptionsObject( );
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

    public String getSourceStreamUrl( ) {
        return _sourceStreamUrl;
    }
    public void setSourceStreamUrl( String value ) {
        if( _sourceStreamUrl != value ) {
            this._sourceStreamUrl = value;
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

    public int getMode( ) {
        return _mode;
    }
    public void setMode( int value ) {
        if( _mode != value ) {
            this._mode = value;
            onPropertyChanged( );
        }
    }

    public int getTunnelOverHTTPPortNumber( ) {
        return _tunnelOverHTTPPortNumber;
    }
    public void setTunnelOverHTTPPortNumber( int value ) {
        if( _tunnelOverHTTPPortNumber != value ) {
            this._tunnelOverHTTPPortNumber = value;
            onPropertyChanged( );
        }
    }

    public String getUsername( ) {
        return _username;
    }
    public void setUsername( String value ) {
        if( _username != value ) {
            this._username = value;
            onPropertyChanged( );
        }
    }

    public String getPassword( ) {
        return _password;
    }
    public void setPassword( String value ) {
        if( _password != value ) {
            this._password = value;
            onPropertyChanged( );
        }
    }

    public int getRecorderPortNumber( ) {
        return _recorderPortNumber;
    }
    public void setRecorderPortNumber( int value ) {
        if( _recorderPortNumber != value ) {
            this._recorderPortNumber = value;
            onPropertyChanged( );
        }
    }

    public int getSessionType( ) {
        return _sessionType;
    }
    public void setSessionType( int value ) {
        if( _sessionType != value ) {
            this._sessionType = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxFileTime( ) {
        return _maxFileTime;
    }
    public void setMaxFileTime( TimeSpan value ) {
        if( _maxFileTime != value ) {
            this._maxFileTime = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxFileRetention( ) {
        return _maxFileRetention;
    }
    public void setMaxFileRetention( TimeSpan value ) {
        if( _maxFileRetention != value ) {
            this._maxFileRetention = value;
            onPropertyChanged( );
        }
    }

    public String getVideoDirectory( ) {
        return _videoDirectory;
    }
    public void setVideoDirectory( String value ) {
        if( _videoDirectory != value ) {
            this._videoDirectory = value;
            onPropertyChanged( );
        }
    }


}
