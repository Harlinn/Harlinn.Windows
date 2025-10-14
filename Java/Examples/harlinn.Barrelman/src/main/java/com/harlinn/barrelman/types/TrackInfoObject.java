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
