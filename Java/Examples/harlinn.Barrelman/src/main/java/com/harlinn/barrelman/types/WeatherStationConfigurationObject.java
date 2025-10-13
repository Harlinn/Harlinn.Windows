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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getWeatherStation( ) {
        return _weatherStation;
    }
    public void setWeatherStation( Guid value ) {
        if( _weatherStation != value ) {
            this._weatherStation = value;
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

    public TimeSpan getNoDataTimeOut( ) {
        return _noDataTimeOut;
    }
    public void setNoDataTimeOut( TimeSpan value ) {
        if( _noDataTimeOut != value ) {
            this._noDataTimeOut = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getSendInterval( ) {
        return _sendInterval;
    }
    public void setSendInterval( TimeSpan value ) {
        if( _sendInterval != value ) {
            this._sendInterval = value;
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

    public double getGyroOffset( ) {
        return _gyroOffset;
    }
    public void setGyroOffset( double value ) {
        if( _gyroOffset != value ) {
            this._gyroOffset = value;
            onPropertyChanged( );
        }
    }

    public boolean getEnableAveraging( ) {
        return _enableAveraging;
    }
    public void setEnableAveraging( boolean value ) {
        if( _enableAveraging != value ) {
            this._enableAveraging = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getAveragingInterval( ) {
        return _averagingInterval;
    }
    public void setAveragingInterval( TimeSpan value ) {
        if( _averagingInterval != value ) {
            this._averagingInterval = value;
            onPropertyChanged( );
        }
    }


}
