/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadomeConfigurationObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.RadomeConfiguration;

    private long _rowVersion = 0;
    private Guid _radome;
    private DateTime _timestamp;
    private TimeSpan _interval;
    private double _lowPressureLimit = 0.0;
    private double _highPressureLimit = 0.0;
    private double _lowTemperatureLimit = 0.0;
    private double _highTemperatureLimit = 0.0;

    public RadomeConfigurationObject( ) {
    }
    public RadomeConfigurationObject( byte objectState, Guid id, long rowVersion, Guid radome, DateTime timestamp, TimeSpan interval, double lowPressureLimit, double highPressureLimit, double lowTemperatureLimit, double highTemperatureLimit ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._radome = radome;
        this._timestamp = timestamp;
        this._interval = interval;
        this._lowPressureLimit = lowPressureLimit;
        this._highPressureLimit = highPressureLimit;
        this._lowTemperatureLimit = lowTemperatureLimit;
        this._highTemperatureLimit = highTemperatureLimit;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadomeConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radome = this._radome;
        targetObject._timestamp = this._timestamp;
        targetObject._interval = this._interval;
        targetObject._lowPressureLimit = this._lowPressureLimit;
        targetObject._highPressureLimit = this._highPressureLimit;
        targetObject._lowTemperatureLimit = this._lowTemperatureLimit;
        targetObject._highTemperatureLimit = this._highTemperatureLimit;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadomeConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radome, other._radome ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._interval, other._interval ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._lowPressureLimit, other._lowPressureLimit ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._highPressureLimit, other._highPressureLimit ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._lowTemperatureLimit, other._lowTemperatureLimit ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._highTemperatureLimit, other._highTemperatureLimit ) ) {
            return false;
        }
        return true;
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
