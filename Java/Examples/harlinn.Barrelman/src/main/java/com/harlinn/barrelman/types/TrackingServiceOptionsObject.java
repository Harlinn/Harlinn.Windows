package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackingServiceOptionsObject extends AbstractDataObjectWithGuidKey {

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
