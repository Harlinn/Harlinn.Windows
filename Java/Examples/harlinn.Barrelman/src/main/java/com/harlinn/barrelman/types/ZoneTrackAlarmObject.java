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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getTrack( ) {
        return _track;
    }
    public void setTrack( Guid value ) {
        if( _track != value ) {
            this._track = value;
            onPropertyChanged( );
        }
    }

    public Guid getZone( ) {
        return _zone;
    }
    public void setZone( Guid value ) {
        if( _zone != value ) {
            this._zone = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadarTrack( ) {
        return _radarTrack;
    }
    public void setRadarTrack( Guid value ) {
        if( _radarTrack != value ) {
            this._radarTrack = value;
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

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getSpeed( ) {
        return _speed;
    }
    public void setSpeed( double value ) {
        if( _speed != value ) {
            this._speed = value;
            onPropertyChanged( );
        }
    }

    public Double getCourse( ) {
        return _course;
    }
    public void setCourse( Double value ) {
        if( _course != value ) {
            this._course = value;
            onPropertyChanged( );
        }
    }

    public Double getHeading( ) {
        return _heading;
    }
    public void setHeading( Double value ) {
        if( _heading != value ) {
            this._heading = value;
            onPropertyChanged( );
        }
    }

    public double getEnterLatitude( ) {
        return _enterLatitude;
    }
    public void setEnterLatitude( double value ) {
        if( _enterLatitude != value ) {
            this._enterLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getEnterLongitude( ) {
        return _enterLongitude;
    }
    public void setEnterLongitude( double value ) {
        if( _enterLongitude != value ) {
            this._enterLongitude = value;
            onPropertyChanged( );
        }
    }

    public Double getLeaveLatitude( ) {
        return _leaveLatitude;
    }
    public void setLeaveLatitude( Double value ) {
        if( _leaveLatitude != value ) {
            this._leaveLatitude = value;
            onPropertyChanged( );
        }
    }

    public Double getLeaveLongitude( ) {
        return _leaveLongitude;
    }
    public void setLeaveLongitude( Double value ) {
        if( _leaveLongitude != value ) {
            this._leaveLongitude = value;
            onPropertyChanged( );
        }
    }


}
