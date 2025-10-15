package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MapInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private int _scale = 0;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private double _northWestLatitude = 0.0;
    private double _northWestLongitude = 0.0;
    private double _southEastLatitude = 0.0;
    private double _southEastLongitude = 0.0;
    private byte[] _image = new byte[0];

    @Override
    public int getObjectType( ) {
        return Kind.MapInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MapInfoObject( );
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

    public int getScale( ) {
        return _scale;
    }
    public void setScale( int value ) {
        if( !Comparer.equalsInt32( _scale, value ) ) {
            _scale = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLatitude( ) {
        return _northWestLatitude;
    }
    public void setNorthWestLatitude( double value ) {
        if( !Comparer.equalsDouble( _northWestLatitude, value ) ) {
            _northWestLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLongitude( ) {
        return _northWestLongitude;
    }
    public void setNorthWestLongitude( double value ) {
        if( !Comparer.equalsDouble( _northWestLongitude, value ) ) {
            _northWestLongitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLatitude( ) {
        return _southEastLatitude;
    }
    public void setSouthEastLatitude( double value ) {
        if( !Comparer.equalsDouble( _southEastLatitude, value ) ) {
            _southEastLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLongitude( ) {
        return _southEastLongitude;
    }
    public void setSouthEastLongitude( double value ) {
        if( !Comparer.equalsDouble( _southEastLongitude, value ) ) {
            _southEastLongitude = value;
            onPropertyChanged( );
        }
    }

    public byte[] getImage( ) {
        return _image;
    }
    public void setImage( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _image, value ) ) {
            _image = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MapInfoObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._scale = this._scale;
        targetObject._latitude = this._latitude;
        targetObject._longitude = this._longitude;
        targetObject._northWestLatitude = this._northWestLatitude;
        targetObject._northWestLongitude = this._northWestLongitude;
        targetObject._southEastLatitude = this._southEastLatitude;
        targetObject._southEastLongitude = this._southEastLongitude;
        targetObject._image = this._image != null ? this._image.clone() : this._image;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MapInfoObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._scale, other._scale ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._northWestLatitude, other._northWestLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._northWestLongitude, other._northWestLongitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._southEastLatitude, other._southEastLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._southEastLongitude, other._southEastLongitude ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._image, other._image ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeInt32( _scale );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeDouble( _northWestLatitude );
        destination.writeDouble( _northWestLongitude );
        destination.writeDouble( _southEastLatitude );
        destination.writeDouble( _southEastLongitude );
        destination.writeUInt8Array( _image );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _scale = source.readInt32( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _northWestLatitude = source.readDouble( );
        _northWestLongitude = source.readDouble( );
        _southEastLatitude = source.readDouble( );
        _southEastLongitude = source.readDouble( );
        _image = source.readUInt8Array( );
    }

}
