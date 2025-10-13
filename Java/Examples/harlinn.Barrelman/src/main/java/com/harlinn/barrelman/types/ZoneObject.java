package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class ZoneObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private String _name = "";
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private int _alarmType = ZoneAlarmType.None;
    private TimeSpan _alarmTime;
    private TimeSpan _radarTrackMinimumLifetime;
    private double _speed = 0.0;
    private int _strokeColor = 0;
    private int _fillColor = 0;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
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

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public int getAlarmType( ) {
        return _alarmType;
    }
    public void setAlarmType( int value ) {
        if( _alarmType != value ) {
            this._alarmType = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getAlarmTime( ) {
        return _alarmTime;
    }
    public void setAlarmTime( TimeSpan value ) {
        if( _alarmTime != value ) {
            this._alarmTime = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getRadarTrackMinimumLifetime( ) {
        return _radarTrackMinimumLifetime;
    }
    public void setRadarTrackMinimumLifetime( TimeSpan value ) {
        if( _radarTrackMinimumLifetime != value ) {
            this._radarTrackMinimumLifetime = value;
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

    public int getStrokeColor( ) {
        return _strokeColor;
    }
    public void setStrokeColor( int value ) {
        if( _strokeColor != value ) {
            this._strokeColor = value;
            onPropertyChanged( );
        }
    }

    public int getFillColor( ) {
        return _fillColor;
    }
    public void setFillColor( int value ) {
        if( _fillColor != value ) {
            this._fillColor = value;
            onPropertyChanged( );
        }
    }


}
