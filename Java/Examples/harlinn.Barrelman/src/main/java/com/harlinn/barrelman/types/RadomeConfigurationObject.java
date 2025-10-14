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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadome( ) {
        return _radome;
    }
    public void setRadome( Guid value ) {
        if( !Comparer.equalsGuid( _radome, value ) ) {
            _radome = value;
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

    public TimeSpan getInterval( ) {
        return _interval;
    }
    public void setInterval( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _interval, value ) ) {
            _interval = value;
            onPropertyChanged( );
        }
    }

    public double getLowPressureLimit( ) {
        return _lowPressureLimit;
    }
    public void setLowPressureLimit( double value ) {
        if( !Comparer.equalsDouble( _lowPressureLimit, value ) ) {
            _lowPressureLimit = value;
            onPropertyChanged( );
        }
    }

    public double getHighPressureLimit( ) {
        return _highPressureLimit;
    }
    public void setHighPressureLimit( double value ) {
        if( !Comparer.equalsDouble( _highPressureLimit, value ) ) {
            _highPressureLimit = value;
            onPropertyChanged( );
        }
    }

    public double getLowTemperatureLimit( ) {
        return _lowTemperatureLimit;
    }
    public void setLowTemperatureLimit( double value ) {
        if( !Comparer.equalsDouble( _lowTemperatureLimit, value ) ) {
            _lowTemperatureLimit = value;
            onPropertyChanged( );
        }
    }

    public double getHighTemperatureLimit( ) {
        return _highTemperatureLimit;
    }
    public void setHighTemperatureLimit( double value ) {
        if( !Comparer.equalsDouble( _highTemperatureLimit, value ) ) {
            _highTemperatureLimit = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radome );
        destination.writeDateTime( _timestamp );
        destination.writeTimeSpan( _interval );
        destination.writeDouble( _lowPressureLimit );
        destination.writeDouble( _highPressureLimit );
        destination.writeDouble( _lowTemperatureLimit );
        destination.writeDouble( _highTemperatureLimit );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radome = source.readGuid( );
        _timestamp = source.readDateTime( );
        _interval = source.readTimeSpan( );
        _lowPressureLimit = source.readDouble( );
        _highPressureLimit = source.readDouble( );
        _lowTemperatureLimit = source.readDouble( );
        _highTemperatureLimit = source.readDouble( );
    }

}
