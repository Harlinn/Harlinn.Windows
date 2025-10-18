package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class ZoneObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.Zone;

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

    public ZoneObject( ) {
    }
    public ZoneObject( byte objectState, Guid id, long rowVersion, String name, double longitude, double latitude, int alarmType, TimeSpan alarmTime, TimeSpan radarTrackMinimumLifetime, double speed, int strokeColor, int fillColor ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._name = name;
        this._longitude = longitude;
        this._latitude = latitude;
        this._alarmType = alarmType;
        this._alarmTime = alarmTime;
        this._radarTrackMinimumLifetime = radarTrackMinimumLifetime;
        this._speed = speed;
        this._strokeColor = strokeColor;
        this._fillColor = fillColor;
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

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
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

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public int getAlarmType( ) {
        return _alarmType;
    }
    public void setAlarmType( int value ) {
        if( !Comparer.equalsInt32( _alarmType, value ) ) {
            _alarmType = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getAlarmTime( ) {
        return _alarmTime;
    }
    public void setAlarmTime( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _alarmTime, value ) ) {
            _alarmTime = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getRadarTrackMinimumLifetime( ) {
        return _radarTrackMinimumLifetime;
    }
    public void setRadarTrackMinimumLifetime( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _radarTrackMinimumLifetime, value ) ) {
            _radarTrackMinimumLifetime = value;
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

    public int getStrokeColor( ) {
        return _strokeColor;
    }
    public void setStrokeColor( int value ) {
        if( !Comparer.equalsUInt32( _strokeColor, value ) ) {
            _strokeColor = value;
            onPropertyChanged( );
        }
    }

    public int getFillColor( ) {
        return _fillColor;
    }
    public void setFillColor( int value ) {
        if( !Comparer.equalsUInt32( _fillColor, value ) ) {
            _fillColor = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ZoneObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._name = this._name;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._alarmType = this._alarmType;
        targetObject._alarmTime = this._alarmTime;
        targetObject._radarTrackMinimumLifetime = this._radarTrackMinimumLifetime;
        targetObject._speed = this._speed;
        targetObject._strokeColor = this._strokeColor;
        targetObject._fillColor = this._fillColor;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ZoneObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._alarmType, other._alarmType ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._alarmTime, other._alarmTime ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._radarTrackMinimumLifetime, other._radarTrackMinimumLifetime ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._speed, other._speed ) ) {
            return false;
        }
        if( !Comparer.equalsUInt32( this._strokeColor, other._strokeColor ) ) {
            return false;
        }
        if( !Comparer.equalsUInt32( this._fillColor, other._fillColor ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeStringUtf8( _name );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeInt32( _alarmType );
        destination.writeTimeSpan( _alarmTime );
        destination.writeTimeSpan( _radarTrackMinimumLifetime );
        destination.writeDouble( _speed );
        destination.writeUInt32( _strokeColor );
        destination.writeUInt32( _fillColor );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _name = source.readString( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _alarmType = source.readInt32( );
        _alarmTime = source.readTimeSpan( );
        _radarTrackMinimumLifetime = source.readTimeSpan( );
        _speed = source.readDouble( );
        _strokeColor = source.readUInt32( );
        _fillColor = source.readUInt32( );
    }

}
