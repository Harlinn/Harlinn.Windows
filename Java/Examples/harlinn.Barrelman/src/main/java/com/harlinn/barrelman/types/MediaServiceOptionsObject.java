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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getMediaService( ) {
        return _mediaService;
    }
    public void setMediaService( Guid value ) {
        if( !Comparer.equalsGuid( _mediaService, value ) ) {
            _mediaService = value;
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

    public int getRtspPortNumber( ) {
        return _rtspPortNumber;
    }
    public void setRtspPortNumber( int value ) {
        if( !Comparer.equalsInt32( _rtspPortNumber, value ) ) {
            _rtspPortNumber = value;
            onPropertyChanged( );
        }
    }

    public int getHttpPortNumber( ) {
        return _httpPortNumber;
    }
    public void setHttpPortNumber( int value ) {
        if( !Comparer.equalsInt32( _httpPortNumber, value ) ) {
            _httpPortNumber = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _mediaService );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _rtspPortNumber );
        destination.writeInt32( _httpPortNumber );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _mediaService = source.readGuid( );
        _timestamp = source.readDateTime( );
        _rtspPortNumber = source.readInt32( );
        _httpPortNumber = source.readInt32( );
    }

}
