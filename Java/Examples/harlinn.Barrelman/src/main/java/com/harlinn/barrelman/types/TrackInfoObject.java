package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private DateTime _firstTimestamp;
    private DateTime _lastTimestamp;
    private long _count = 0;
    private Double _northWestLatitude;
    private Double _northWestLongitude;
    private Double _southEastLatitude;
    private Double _southEastLongitude;

    @Override
    public int getObjectType( ) {
        return Kind.TrackInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackInfoObject( );
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

    public DateTime getFirstTimestamp( ) {
        return _firstTimestamp;
    }
    public void setFirstTimestamp( DateTime value ) {
        if( _firstTimestamp != value ) {
            this._firstTimestamp = value;
            onPropertyChanged( );
        }
    }

    public DateTime getLastTimestamp( ) {
        return _lastTimestamp;
    }
    public void setLastTimestamp( DateTime value ) {
        if( _lastTimestamp != value ) {
            this._lastTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getCount( ) {
        return _count;
    }
    public void setCount( long value ) {
        if( _count != value ) {
            this._count = value;
            onPropertyChanged( );
        }
    }

    public Double getNorthWestLatitude( ) {
        return _northWestLatitude;
    }
    public void setNorthWestLatitude( Double value ) {
        if( _northWestLatitude != value ) {
            this._northWestLatitude = value;
            onPropertyChanged( );
        }
    }

    public Double getNorthWestLongitude( ) {
        return _northWestLongitude;
    }
    public void setNorthWestLongitude( Double value ) {
        if( _northWestLongitude != value ) {
            this._northWestLongitude = value;
            onPropertyChanged( );
        }
    }

    public Double getSouthEastLatitude( ) {
        return _southEastLatitude;
    }
    public void setSouthEastLatitude( Double value ) {
        if( _southEastLatitude != value ) {
            this._southEastLatitude = value;
            onPropertyChanged( );
        }
    }

    public Double getSouthEastLongitude( ) {
        return _southEastLongitude;
    }
    public void setSouthEastLongitude( Double value ) {
        if( _southEastLongitude != value ) {
            this._southEastLongitude = value;
            onPropertyChanged( );
        }
    }


}
