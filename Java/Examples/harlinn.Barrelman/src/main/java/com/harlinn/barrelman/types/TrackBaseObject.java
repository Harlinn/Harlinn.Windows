package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TrackBaseObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _tracker;
    private long _trackNumber = 0;
    private DateTime _timestamp;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getTracker( ) {
        return _tracker;
    }
    public void setTracker( Guid value ) {
        if( !Comparer.equalsGuid( _tracker, value ) ) {
            _tracker = value;
            onPropertyChanged( );
        }
    }

    public long getTrackNumber( ) {
        return _trackNumber;
    }
    public void setTrackNumber( long value ) {
        if( !Comparer.equalsInt64( _trackNumber, value ) ) {
            _trackNumber = value;
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



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _tracker );
        destination.writeInt64( _trackNumber );
        destination.writeDateTime( _timestamp );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _tracker = source.readGuid( );
        _trackNumber = source.readInt64( );
        _timestamp = source.readDateTime( );
    }

}
