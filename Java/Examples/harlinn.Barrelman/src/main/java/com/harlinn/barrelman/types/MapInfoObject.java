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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public int getScale( ) {
        return _scale;
    }
    public void setScale( int value ) {
        if( _scale != value ) {
            this._scale = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLatitude( ) {
        return _northWestLatitude;
    }
    public void setNorthWestLatitude( double value ) {
        if( _northWestLatitude != value ) {
            this._northWestLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getNorthWestLongitude( ) {
        return _northWestLongitude;
    }
    public void setNorthWestLongitude( double value ) {
        if( _northWestLongitude != value ) {
            this._northWestLongitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLatitude( ) {
        return _southEastLatitude;
    }
    public void setSouthEastLatitude( double value ) {
        if( _southEastLatitude != value ) {
            this._southEastLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getSouthEastLongitude( ) {
        return _southEastLongitude;
    }
    public void setSouthEastLongitude( double value ) {
        if( _southEastLongitude != value ) {
            this._southEastLongitude = value;
            onPropertyChanged( );
        }
    }

    public byte[] getImage( ) {
        return _image;
    }
    public void setImage( byte[] value ) {
        if( _image != value ) {
            this._image = value;
            onPropertyChanged( );
        }
    }


}
