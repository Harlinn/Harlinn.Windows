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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getProxySession( ) {
        return _proxySession;
    }
    public void setProxySession( Guid value ) {
        if( !Comparer.equalsGuid( _proxySession, value ) ) {
            _proxySession = value;
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

    public String getSourceStreamUrl( ) {
        return _sourceStreamUrl;
    }
    public void setSourceStreamUrl( String value ) {
        if( !Comparer.equalsString( _sourceStreamUrl, value ) ) {
            _sourceStreamUrl = value;
            onPropertyChanged( );
        }
    }

    public String getStreamName( ) {
        return _streamName;
    }
    public void setStreamName( String value ) {
        if( !Comparer.equalsString( _streamName, value ) ) {
            _streamName = value;
            onPropertyChanged( );
        }
    }

    public int getMode( ) {
        return _mode;
    }
    public void setMode( int value ) {
        if( !Comparer.equalsInt32( _mode, value ) ) {
            _mode = value;
            onPropertyChanged( );
        }
    }

    public int getTunnelOverHTTPPortNumber( ) {
        return _tunnelOverHTTPPortNumber;
    }
    public void setTunnelOverHTTPPortNumber( int value ) {
        if( !Comparer.equalsInt32( _tunnelOverHTTPPortNumber, value ) ) {
            _tunnelOverHTTPPortNumber = value;
            onPropertyChanged( );
        }
    }

    public String getUsername( ) {
        return _username;
    }
    public void setUsername( String value ) {
        if( !Comparer.equalsString( _username, value ) ) {
            _username = value;
            onPropertyChanged( );
        }
    }

    public String getPassword( ) {
        return _password;
    }
    public void setPassword( String value ) {
        if( !Comparer.equalsString( _password, value ) ) {
            _password = value;
            onPropertyChanged( );
        }
    }

    public int getRecorderPortNumber( ) {
        return _recorderPortNumber;
    }
    public void setRecorderPortNumber( int value ) {
        if( !Comparer.equalsInt32( _recorderPortNumber, value ) ) {
            _recorderPortNumber = value;
            onPropertyChanged( );
        }
    }

    public int getSessionType( ) {
        return _sessionType;
    }
    public void setSessionType( int value ) {
        if( !Comparer.equalsInt32( _sessionType, value ) ) {
            _sessionType = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxFileTime( ) {
        return _maxFileTime;
    }
    public void setMaxFileTime( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxFileTime, value ) ) {
            _maxFileTime = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxFileRetention( ) {
        return _maxFileRetention;
    }
    public void setMaxFileRetention( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxFileRetention, value ) ) {
            _maxFileRetention = value;
            onPropertyChanged( );
        }
    }

    public String getVideoDirectory( ) {
        return _videoDirectory;
    }
    public void setVideoDirectory( String value ) {
        if( !Comparer.equalsString( _videoDirectory, value ) ) {
            _videoDirectory = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _proxySession );
        destination.writeDateTime( _timestamp );
        destination.writeStringUtf8( _sourceStreamUrl );
        destination.writeStringUtf8( _streamName );
        destination.writeInt32( _mode );
        destination.writeInt32( _tunnelOverHTTPPortNumber );
        destination.writeStringUtf8( _username );
        destination.writeStringUtf8( _password );
        destination.writeInt32( _recorderPortNumber );
        destination.writeInt32( _sessionType );
        destination.writeTimeSpan( _maxFileTime );
        destination.writeTimeSpan( _maxFileRetention );
        destination.writeStringUtf8( _videoDirectory );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _proxySession = source.readGuid( );
        _timestamp = source.readDateTime( );
        _sourceStreamUrl = source.readString( );
        _streamName = source.readString( );
        _mode = source.readInt32( );
        _tunnelOverHTTPPortNumber = source.readInt32( );
        _username = source.readString( );
        _password = source.readString( );
        _recorderPortNumber = source.readInt32( );
        _sessionType = source.readInt32( );
        _maxFileTime = source.readTimeSpan( );
        _maxFileRetention = source.readTimeSpan( );
        _videoDirectory = source.readString( );
    }

}
