package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackValue3DObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _track;
    private DateTime _timestamp;
    private int _flags = TrackFlags3D.None;
    private int _status = 0;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _altitude = 0.0;
    private double _speed = 0.0;
    private double _course = 0.0;
    private double _rateOfClimb = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.TrackValue3D;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackValue3DObject( );
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

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public int getFlags( ) {
        return _flags;
    }
    public void setFlags( int value ) {
        if( _flags != value ) {
            this._flags = value;
            onPropertyChanged( );
        }
    }

    public int getStatus( ) {
        return _status;
    }
    public void setStatus( int value ) {
        if( _status != value ) {
            this._status = value;
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

    public double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( double value ) {
        if( _altitude != value ) {
            this._altitude = value;
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

    public double getCourse( ) {
        return _course;
    }
    public void setCourse( double value ) {
        if( _course != value ) {
            this._course = value;
            onPropertyChanged( );
        }
    }

    public double getRateOfClimb( ) {
        return _rateOfClimb;
    }
    public void setRateOfClimb( double value ) {
        if( _rateOfClimb != value ) {
            this._rateOfClimb = value;
            onPropertyChanged( );
        }
    }


}
