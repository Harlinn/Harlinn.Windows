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

public class TrackingServiceOptionsObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.TrackingServiceOptions;

    private long _rowVersion = 0;
    private DateTime _timestamp;
    private TimeSpan _timerInterval;
    private TimeSpan _maxAgeOfCurrentTrackValue;
    private double _falseThreshold = 0.0;
    private double _distanceThreshold = 0.0;
    private double _distanceUnmergeThreshold = 0.0;
    private long _unmergeLatency = 0;
    private boolean _kalmanFiltering = false;
    private double _maxCourseDeviation = 0.0;
    private double _maxSpeedDeviation = 0.0;
    private double _minimumSpeedThreshold = 0.0;

    public TrackingServiceOptionsObject( ) {
    }
    public TrackingServiceOptionsObject( byte objectState, Guid id, long rowVersion, DateTime timestamp, TimeSpan timerInterval, TimeSpan maxAgeOfCurrentTrackValue, double falseThreshold, double distanceThreshold, double distanceUnmergeThreshold, long unmergeLatency, boolean kalmanFiltering, double maxCourseDeviation, double maxSpeedDeviation, double minimumSpeedThreshold ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._timestamp = timestamp;
        this._timerInterval = timerInterval;
        this._maxAgeOfCurrentTrackValue = maxAgeOfCurrentTrackValue;
        this._falseThreshold = falseThreshold;
        this._distanceThreshold = distanceThreshold;
        this._distanceUnmergeThreshold = distanceUnmergeThreshold;
        this._unmergeLatency = unmergeLatency;
        this._kalmanFiltering = kalmanFiltering;
        this._maxCourseDeviation = maxCourseDeviation;
        this._maxSpeedDeviation = maxSpeedDeviation;
        this._minimumSpeedThreshold = minimumSpeedThreshold;
    }

    @Override
    public int getObjectType( ) {
        return Kind.TrackingServiceOptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackingServiceOptionsObject( );
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

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getTimerInterval( ) {
        return _timerInterval;
    }
    public void setTimerInterval( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _timerInterval, value ) ) {
            _timerInterval = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxAgeOfCurrentTrackValue( ) {
        return _maxAgeOfCurrentTrackValue;
    }
    public void setMaxAgeOfCurrentTrackValue( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxAgeOfCurrentTrackValue, value ) ) {
            _maxAgeOfCurrentTrackValue = value;
            onPropertyChanged( );
        }
    }

    public double getFalseThreshold( ) {
        return _falseThreshold;
    }
    public void setFalseThreshold( double value ) {
        if( !Comparer.equalsDouble( _falseThreshold, value ) ) {
            _falseThreshold = value;
            onPropertyChanged( );
        }
    }

    public double getDistanceThreshold( ) {
        return _distanceThreshold;
    }
    public void setDistanceThreshold( double value ) {
        if( !Comparer.equalsDouble( _distanceThreshold, value ) ) {
            _distanceThreshold = value;
            onPropertyChanged( );
        }
    }

    public double getDistanceUnmergeThreshold( ) {
        return _distanceUnmergeThreshold;
    }
    public void setDistanceUnmergeThreshold( double value ) {
        if( !Comparer.equalsDouble( _distanceUnmergeThreshold, value ) ) {
            _distanceUnmergeThreshold = value;
            onPropertyChanged( );
        }
    }

    public long getUnmergeLatency( ) {
        return _unmergeLatency;
    }
    public void setUnmergeLatency( long value ) {
        if( !Comparer.equalsInt64( _unmergeLatency, value ) ) {
            _unmergeLatency = value;
            onPropertyChanged( );
        }
    }

    public boolean getKalmanFiltering( ) {
        return _kalmanFiltering;
    }
    public void setKalmanFiltering( boolean value ) {
        if( !Comparer.equalsBoolean( _kalmanFiltering, value ) ) {
            _kalmanFiltering = value;
            onPropertyChanged( );
        }
    }

    public double getMaxCourseDeviation( ) {
        return _maxCourseDeviation;
    }
    public void setMaxCourseDeviation( double value ) {
        if( !Comparer.equalsDouble( _maxCourseDeviation, value ) ) {
            _maxCourseDeviation = value;
            onPropertyChanged( );
        }
    }

    public double getMaxSpeedDeviation( ) {
        return _maxSpeedDeviation;
    }
    public void setMaxSpeedDeviation( double value ) {
        if( !Comparer.equalsDouble( _maxSpeedDeviation, value ) ) {
            _maxSpeedDeviation = value;
            onPropertyChanged( );
        }
    }

    public double getMinimumSpeedThreshold( ) {
        return _minimumSpeedThreshold;
    }
    public void setMinimumSpeedThreshold( double value ) {
        if( !Comparer.equalsDouble( _minimumSpeedThreshold, value ) ) {
            _minimumSpeedThreshold = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TrackingServiceOptionsObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._timestamp = this._timestamp;
        targetObject._timerInterval = this._timerInterval;
        targetObject._maxAgeOfCurrentTrackValue = this._maxAgeOfCurrentTrackValue;
        targetObject._falseThreshold = this._falseThreshold;
        targetObject._distanceThreshold = this._distanceThreshold;
        targetObject._distanceUnmergeThreshold = this._distanceUnmergeThreshold;
        targetObject._unmergeLatency = this._unmergeLatency;
        targetObject._kalmanFiltering = this._kalmanFiltering;
        targetObject._maxCourseDeviation = this._maxCourseDeviation;
        targetObject._maxSpeedDeviation = this._maxSpeedDeviation;
        targetObject._minimumSpeedThreshold = this._minimumSpeedThreshold;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TrackingServiceOptionsObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._timerInterval, other._timerInterval ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._maxAgeOfCurrentTrackValue, other._maxAgeOfCurrentTrackValue ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._falseThreshold, other._falseThreshold ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._distanceThreshold, other._distanceThreshold ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._distanceUnmergeThreshold, other._distanceUnmergeThreshold ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._unmergeLatency, other._unmergeLatency ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._kalmanFiltering, other._kalmanFiltering ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._maxCourseDeviation, other._maxCourseDeviation ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._maxSpeedDeviation, other._maxSpeedDeviation ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._minimumSpeedThreshold, other._minimumSpeedThreshold ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeDateTime( _timestamp );
        destination.writeTimeSpan( _timerInterval );
        destination.writeTimeSpan( _maxAgeOfCurrentTrackValue );
        destination.writeDouble( _falseThreshold );
        destination.writeDouble( _distanceThreshold );
        destination.writeDouble( _distanceUnmergeThreshold );
        destination.writeInt64( _unmergeLatency );
        destination.writeBoolean( _kalmanFiltering );
        destination.writeDouble( _maxCourseDeviation );
        destination.writeDouble( _maxSpeedDeviation );
        destination.writeDouble( _minimumSpeedThreshold );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _timestamp = source.readDateTime( );
        _timerInterval = source.readTimeSpan( );
        _maxAgeOfCurrentTrackValue = source.readTimeSpan( );
        _falseThreshold = source.readDouble( );
        _distanceThreshold = source.readDouble( );
        _distanceUnmergeThreshold = source.readDouble( );
        _unmergeLatency = source.readInt64( );
        _kalmanFiltering = source.readBoolean( );
        _maxCourseDeviation = source.readDouble( );
        _maxSpeedDeviation = source.readDouble( );
        _minimumSpeedThreshold = source.readDouble( );
    }

}
