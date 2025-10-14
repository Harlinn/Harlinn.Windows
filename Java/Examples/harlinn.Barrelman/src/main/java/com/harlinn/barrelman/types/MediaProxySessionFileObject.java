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

    public String getStreamName( ) {
        return _streamName;
    }
    public void setStreamName( String value ) {
        if( !Comparer.equalsString( _streamName, value ) ) {
            _streamName = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _proxySession );
        destination.writeDateTime( _timestamp );
        destination.writeStringUtf8( _streamName );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _proxySession = source.readGuid( );
        _timestamp = source.readDateTime( );
        _streamName = source.readString( );
    }

}
