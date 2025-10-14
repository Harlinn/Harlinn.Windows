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
