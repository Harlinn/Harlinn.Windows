package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _weatherStation;
    private DateTime _timestamp;
    private TimeSpan _noDataTimeOut;
    private TimeSpan _sendInterval;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _gyroOffset = 0.0;
    private boolean _enableAveraging = false;
    private TimeSpan _averagingInterval;

    @Override
    public int getObjectType( ) {
        return Kind.WeatherStationConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new WeatherStationConfigurationObject( );
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

    public Guid getWeatherStation( ) {
        return _weatherStation;
    }
    public void setWeatherStation( Guid value ) {
        if( !Comparer.equalsGuid( _weatherStation, value ) ) {
            _weatherStation = value;
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

    public TimeSpan getNoDataTimeOut( ) {
        return _noDataTimeOut;
    }
    public void setNoDataTimeOut( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _noDataTimeOut, value ) ) {
            _noDataTimeOut = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getSendInterval( ) {
        return _sendInterval;
    }
    public void setSendInterval( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _sendInterval, value ) ) {
            _sendInterval = value;
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

    public double getGyroOffset( ) {
        return _gyroOffset;
    }
    public void setGyroOffset( double value ) {
        if( !Comparer.equalsDouble( _gyroOffset, value ) ) {
            _gyroOffset = value;
            onPropertyChanged( );
        }
    }

    public boolean getEnableAveraging( ) {
        return _enableAveraging;
    }
    public void setEnableAveraging( boolean value ) {
        if( !Comparer.equalsBoolean( _enableAveraging, value ) ) {
            _enableAveraging = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getAveragingInterval( ) {
        return _averagingInterval;
    }
    public void setAveragingInterval( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _averagingInterval, value ) ) {
            _averagingInterval = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _weatherStation );
        destination.writeDateTime( _timestamp );
        destination.writeTimeSpan( _noDataTimeOut );
        destination.writeTimeSpan( _sendInterval );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _gyroOffset );
        destination.writeBoolean( _enableAveraging );
        destination.writeTimeSpan( _averagingInterval );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _weatherStation = source.readGuid( );
        _timestamp = source.readDateTime( );
        _noDataTimeOut = source.readTimeSpan( );
        _sendInterval = source.readTimeSpan( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _gyroOffset = source.readDouble( );
        _enableAveraging = source.readBoolean( );
        _averagingInterval = source.readTimeSpan( );
    }

}
