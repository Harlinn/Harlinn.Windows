package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Position3DTimeseriesValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _timeseries;
    private DateTime _timestamp;
    private Double _x;
    private Double _y;
    private Double _z;

    @Override
    public int getObjectType( ) {
        return Kind.Position3DTimeseriesValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Position3DTimeseriesValueObject( );
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

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( !Comparer.equalsGuid( _timeseries, value ) ) {
            _timeseries = value;
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

    public Double getX( ) {
        return _x;
    }
    public void setX( Double value ) {
        if( !Comparer.equalsNullableDouble( _x, value ) ) {
            _x = value;
            onPropertyChanged( );
        }
    }

    public Double getY( ) {
        return _y;
    }
    public void setY( Double value ) {
        if( !Comparer.equalsNullableDouble( _y, value ) ) {
            _y = value;
            onPropertyChanged( );
        }
    }

    public Double getZ( ) {
        return _z;
    }
    public void setZ( Double value ) {
        if( !Comparer.equalsNullableDouble( _z, value ) ) {
            _z = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _timeseries );
        destination.writeDateTime( _timestamp );
        destination.writeNullableDouble( _x );
        destination.writeNullableDouble( _y );
        destination.writeNullableDouble( _z );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _timeseries = source.readGuid( );
        _timestamp = source.readDateTime( );
        _x = source.readNullableDouble( );
        _y = source.readNullableDouble( );
        _z = source.readNullableDouble( );
    }

}
