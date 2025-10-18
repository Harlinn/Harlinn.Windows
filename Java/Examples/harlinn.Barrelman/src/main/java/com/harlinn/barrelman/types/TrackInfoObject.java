package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackInfoObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.TrackInfo;

    private long _rowVersion = 0;
    private DateTime _firstTimestamp;
    private DateTime _lastTimestamp;
    private long _count = 0;
    private Double _northWestLatitude;
    private Double _northWestLongitude;
    private Double _southEastLatitude;
    private Double _southEastLongitude;

    public TrackInfoObject( ) {
    }
    public TrackInfoObject( byte objectState, Guid id, long rowVersion, DateTime firstTimestamp, DateTime lastTimestamp, long count, Double northWestLatitude, Double northWestLongitude, Double southEastLatitude, Double southEastLongitude ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._firstTimestamp = firstTimestamp;
        this._lastTimestamp = lastTimestamp;
        this._count = count;
        this._northWestLatitude = northWestLatitude;
        this._northWestLongitude = northWestLongitude;
        this._southEastLatitude = southEastLatitude;
        this._southEastLongitude = southEastLongitude;
    }

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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public DateTime getFirstTimestamp( ) {
        return _firstTimestamp;
    }
    public void setFirstTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _firstTimestamp, value ) ) {
            _firstTimestamp = value;
            onPropertyChanged( );
        }
    }

    public DateTime getLastTimestamp( ) {
        return _lastTimestamp;
    }
    public void setLastTimestamp( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _lastTimestamp, value ) ) {
            _lastTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getCount( ) {
        return _count;
    }
    public void setCount( long value ) {
        if( !Comparer.equalsInt64( _count, value ) ) {
            _count = value;
            onPropertyChanged( );
        }
    }

    public Double getNorthWestLatitude( ) {
        return _northWestLatitude;
    }
    public void setNorthWestLatitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _northWestLatitude, value ) ) {
            _northWestLatitude = value;
            onPropertyChanged( );
        }
    }

    public Double getNorthWestLongitude( ) {
        return _northWestLongitude;
    }
    public void setNorthWestLongitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _northWestLongitude, value ) ) {
            _northWestLongitude = value;
            onPropertyChanged( );
        }
    }

    public Double getSouthEastLatitude( ) {
        return _southEastLatitude;
    }
    public void setSouthEastLatitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _southEastLatitude, value ) ) {
            _southEastLatitude = value;
            onPropertyChanged( );
        }
    }

    public Double getSouthEastLongitude( ) {
        return _southEastLongitude;
    }
    public void setSouthEastLongitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _southEastLongitude, value ) ) {
            _southEastLongitude = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TrackInfoObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._firstTimestamp = this._firstTimestamp;
        targetObject._lastTimestamp = this._lastTimestamp;
        targetObject._count = this._count;
        targetObject._northWestLatitude = this._northWestLatitude;
        targetObject._northWestLongitude = this._northWestLongitude;
        targetObject._southEastLatitude = this._southEastLatitude;
        targetObject._southEastLongitude = this._southEastLongitude;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TrackInfoObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._firstTimestamp, other._firstTimestamp ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._lastTimestamp, other._lastTimestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt64( this._count, other._count ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._northWestLatitude, other._northWestLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._northWestLongitude, other._northWestLongitude ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._southEastLatitude, other._southEastLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDouble( this._southEastLongitude, other._southEastLongitude ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeNullableDateTime( _firstTimestamp );
        destination.writeNullableDateTime( _lastTimestamp );
        destination.writeInt64( _count );
        destination.writeNullableDouble( _northWestLatitude );
        destination.writeNullableDouble( _northWestLongitude );
        destination.writeNullableDouble( _southEastLatitude );
        destination.writeNullableDouble( _southEastLongitude );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _firstTimestamp = source.readNullableDateTime( );
        _lastTimestamp = source.readNullableDateTime( );
        _count = source.readInt64( );
        _northWestLatitude = source.readNullableDouble( );
        _northWestLongitude = source.readNullableDouble( );
        _southEastLatitude = source.readNullableDouble( );
        _southEastLongitude = source.readNullableDouble( );
    }

}
