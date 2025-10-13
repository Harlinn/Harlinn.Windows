package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomeConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radome;
    private DateTime _timestamp;
    private TimeSpan _interval;
    private double _lowPressureLimit = 0.0;
    private double _highPressureLimit = 0.0;
    private double _lowTemperatureLimit = 0.0;
    private double _highTemperatureLimit = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.RadomeConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadomeConfigurationObject( );
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

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( _radome != value ) {
            this._radome = value;
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

    public TimeSpan getInterval( ) {
        return _interval;
    }
    public void setInterval( TimeSpan value ) {
        if( _interval != value ) {
            this._interval = value;
            onPropertyChanged( );
        }
    }

    public double getLowPressureLimit( ) {
        return _lowPressureLimit;
    }
    public void setLowPressureLimit( double value ) {
        if( _lowPressureLimit != value ) {
            this._lowPressureLimit = value;
            onPropertyChanged( );
        }
    }

    public double getHighPressureLimit( ) {
        return _highPressureLimit;
    }
    public void setHighPressureLimit( double value ) {
        if( _highPressureLimit != value ) {
            this._highPressureLimit = value;
            onPropertyChanged( );
        }
    }

    public double getLowTemperatureLimit( ) {
        return _lowTemperatureLimit;
    }
    public void setLowTemperatureLimit( double value ) {
        if( _lowTemperatureLimit != value ) {
            this._lowTemperatureLimit = value;
            onPropertyChanged( );
        }
    }

    public double getHighTemperatureLimit( ) {
        return _highTemperatureLimit;
    }
    public void setHighTemperatureLimit( double value ) {
        if( _highTemperatureLimit != value ) {
            this._highTemperatureLimit = value;
            onPropertyChanged( );
        }
    }


}
