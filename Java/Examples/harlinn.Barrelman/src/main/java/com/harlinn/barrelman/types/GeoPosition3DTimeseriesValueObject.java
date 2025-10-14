package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GeoPosition3DTimeseriesValueObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _timeseries;
    private DateTime _timestamp;
    private Double _latitude;
    private Double _longitude;
    private Double _altitude;

    @Override
    public int getObjectType( ) {
        return Kind.GeoPosition3DTimeseriesValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GeoPosition3DTimeseriesValueObject( );
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

    public Double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public Double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public Double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( Double value ) {
        if( !Comparer.equalsNullableDouble( _altitude, value ) ) {
            _altitude = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _timeseries );
        destination.writeDateTime( _timestamp );
        destination.writeNullableDouble( _latitude );
        destination.writeNullableDouble( _longitude );
        destination.writeNullableDouble( _altitude );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _timeseries = source.readGuid( );
        _timestamp = source.readDateTime( );
        _latitude = source.readNullableDouble( );
        _longitude = source.readNullableDouble( );
        _altitude = source.readNullableDouble( );
    }

}
