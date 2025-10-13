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
        if( _rowVersion != value ) {
            this._rowVersion = value;
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

    public TimeSpan getTimerInterval( ) {
        return _timerInterval;
    }
    public void setTimerInterval( TimeSpan value ) {
        if( _timerInterval != value ) {
            this._timerInterval = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getMaxAgeOfCurrentTrackValue( ) {
        return _maxAgeOfCurrentTrackValue;
    }
    public void setMaxAgeOfCurrentTrackValue( TimeSpan value ) {
        if( _maxAgeOfCurrentTrackValue != value ) {
            this._maxAgeOfCurrentTrackValue = value;
            onPropertyChanged( );
        }
    }

    public double getFalseThreshold( ) {
        return _falseThreshold;
    }
    public void setFalseThreshold( double value ) {
        if( _falseThreshold != value ) {
            this._falseThreshold = value;
            onPropertyChanged( );
        }
    }

    public double getDistanceThreshold( ) {
        return _distanceThreshold;
    }
    public void setDistanceThreshold( double value ) {
        if( _distanceThreshold != value ) {
            this._distanceThreshold = value;
            onPropertyChanged( );
        }
    }

    public double getDistanceUnmergeThreshold( ) {
        return _distanceUnmergeThreshold;
    }
    public void setDistanceUnmergeThreshold( double value ) {
        if( _distanceUnmergeThreshold != value ) {
            this._distanceUnmergeThreshold = value;
            onPropertyChanged( );
        }
    }

    public long getUnmergeLatency( ) {
        return _unmergeLatency;
    }
    public void setUnmergeLatency( long value ) {
        if( _unmergeLatency != value ) {
            this._unmergeLatency = value;
            onPropertyChanged( );
        }
    }

    public boolean getKalmanFiltering( ) {
        return _kalmanFiltering;
    }
    public void setKalmanFiltering( boolean value ) {
        if( _kalmanFiltering != value ) {
            this._kalmanFiltering = value;
            onPropertyChanged( );
        }
    }

    public double getMaxCourseDeviation( ) {
        return _maxCourseDeviation;
    }
    public void setMaxCourseDeviation( double value ) {
        if( _maxCourseDeviation != value ) {
            this._maxCourseDeviation = value;
            onPropertyChanged( );
        }
    }

    public double getMaxSpeedDeviation( ) {
        return _maxSpeedDeviation;
    }
    public void setMaxSpeedDeviation( double value ) {
        if( _maxSpeedDeviation != value ) {
            this._maxSpeedDeviation = value;
            onPropertyChanged( );
        }
    }

    public double getMinimumSpeedThreshold( ) {
        return _minimumSpeedThreshold;
    }
    public void setMinimumSpeedThreshold( double value ) {
        if( _minimumSpeedThreshold != value ) {
            this._minimumSpeedThreshold = value;
            onPropertyChanged( );
        }
    }


}
