package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ZoneTrackAlarmObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _track;
    private Guid _zone;
    private Guid _radarTrack;
    private DateTime _timestamp;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _speed = 0.0;
    private Double _course;
    private Double _heading;
    private double _enterLatitude = 0.0;
    private double _enterLongitude = 0.0;
    private Double _leaveLatitude;
    private Double _leaveLongitude;

    @Override
    public int getObjectType( ) {
        return Kind.ZoneTrackAlarm;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ZoneTrackAlarmObject( );
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

    public Guid getZone( ) {
        return _zone;
    }
    public void setZone( Guid value ) {
        if( !Comparer.equalsGuid( _zone, value ) ) {
            _zone = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadarTrack( ) {
        return _radarTrack;
    }
    public void setRadarTrack( Guid value ) {
        if( !Comparer.equalsNullableGuid( _radarTrack, value ) ) {
            _radarTrack = value;
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

    public Double getCourse( ) {
        return _course;
    }
    public void setCourse( Double value ) {
        if( !Comparer.equalsNullableDouble( _course, value ) ) {
            _course = value;
            onPropertyChanged( );
        }
    }

    public Double getHeading( ) {
        return _heading;
    }
    public void setHeading( Double value ) {
        if( !Comparer.equalsNullableDouble( _heading, value ) ) {
            _heading = value;
            onPropertyChanged( );
        }
    }

    public double getEnterLatitude( ) {
        return _enterLatitude;
    }
    public void setEnterLatitude( double value ) {
        if( !Comparer.equalsDouble( _enterLatitude, value ) ) {
            _enterLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getEnterLongitude( ) {
        return _enterLongitude;
    }
    public void setEnterLongitude( double value ) {
        if( !Comparer.equalsDouble( _enterLongitude, value ) ) {
            _enterLongitude = value;
            onPropertyChanged( );
        }
    }

    public Double getLeaveLatitude( ) {
        return _leaveLatitude;
    }
    public void setLeaveLatitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _leaveLatitude, value ) ) {
            _leaveLatitude = value;
            onPropertyChanged( );
        }
    }

    public Double getLeaveLongitude( ) {
        return _leaveLongitude;
    }
    public void setLeaveLongitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _leaveLongitude, value ) ) {
            _leaveLongitude = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _track );
        destination.writeGuid( _zone );
        destination.writeNullableGuid( _radarTrack );
        destination.writeDateTime( _timestamp );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _speed );
        destination.writeNullableDouble( _course );
        destination.writeNullableDouble( _heading );
        destination.writeDouble( _enterLatitude );
        destination.writeDouble( _enterLongitude );
        destination.writeNullableDouble( _leaveLatitude );
        destination.writeNullableDouble( _leaveLongitude );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _track = source.readGuid( );
        _zone = source.readGuid( );
        _radarTrack = source.readNullableGuid( );
        _timestamp = source.readDateTime( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _speed = source.readDouble( );
        _course = source.readNullableDouble( );
        _heading = source.readNullableDouble( );
        _enterLatitude = source.readDouble( );
        _enterLongitude = source.readDouble( );
        _leaveLatitude = source.readNullableDouble( );
        _leaveLongitude = source.readNullableDouble( );
    }

}
