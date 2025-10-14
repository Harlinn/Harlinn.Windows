package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _track;
    private DateTime _timestamp;
    private int _flags = TrackFlags.None;
    private int _status = TrackStatus.Unknown;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _speed = 0.0;
    private double _course = 0.0;
    private double _heading = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.TrackValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackValueObject( );
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

    public Guid getTrack( ) {
        return _track;
    }
    public void setTrack( Guid value ) {
        if( !Comparer.equalsGuid( _track, value ) ) {
            _track = value;
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

    public int getFlags( ) {
        return _flags;
    }
    public void setFlags( int value ) {
        if( !Comparer.equalsInt32( _flags, value ) ) {
            _flags = value;
            onPropertyChanged( );
        }
    }

    public int getStatus( ) {
        return _status;
    }
    public void setStatus( int value ) {
        if( !Comparer.equalsInt32( _status, value ) ) {
            _status = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getSpeed( ) {
        return _speed;
    }
    public void setSpeed( double value ) {
        if( !Comparer.equalsDouble( _speed, value ) ) {
            _speed = value;
            onPropertyChanged( );
        }
    }

    public double getCourse( ) {
        return _course;
    }
    public void setCourse( double value ) {
        if( !Comparer.equalsDouble( _course, value ) ) {
            _course = value;
            onPropertyChanged( );
        }
    }

    public double getHeading( ) {
        return _heading;
    }
    public void setHeading( double value ) {
        if( !Comparer.equalsDouble( _heading, value ) ) {
            _heading = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _track );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _flags );
        destination.writeInt32( _status );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _speed );
        destination.writeDouble( _course );
        destination.writeDouble( _heading );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _track = source.readGuid( );
        _timestamp = source.readDateTime( );
        _flags = source.readInt32( );
        _status = source.readInt32( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _speed = source.readDouble( );
        _course = source.readDouble( );
        _heading = source.readDouble( );
    }

}
