package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class MapServiceOptionsObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private DateTime _timestamp;
    private String _ipAddress = "";
    private int _port = 0;
    private double _imageScaleFactorX = 0.0;
    private double _imageOffsetX = 0.0;
    private double _imageScaleFactorY = 0.0;
    private double _imageOffsetY = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.MapServiceOptions;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new MapServiceOptionsObject( );
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

    public String getIpAddress( ) {
        return _ipAddress;
    }
    public void setIpAddress( String value ) {
        if( _ipAddress != value ) {
            this._ipAddress = value;
            onPropertyChanged( );
        }
    }

    public int getPort( ) {
        return _port;
    }
    public void setPort( int value ) {
        if( _port != value ) {
            this._port = value;
            onPropertyChanged( );
        }
    }

    public double getImageScaleFactorX( ) {
        return _imageScaleFactorX;
    }
    public void setImageScaleFactorX( double value ) {
        if( _imageScaleFactorX != value ) {
            this._imageScaleFactorX = value;
            onPropertyChanged( );
        }
    }

    public double getImageOffsetX( ) {
        return _imageOffsetX;
    }
    public void setImageOffsetX( double value ) {
        if( _imageOffsetX != value ) {
            this._imageOffsetX = value;
            onPropertyChanged( );
        }
    }

    public double getImageScaleFactorY( ) {
        return _imageScaleFactorY;
    }
    public void setImageScaleFactorY( double value ) {
        if( _imageScaleFactorY != value ) {
            this._imageScaleFactorY = value;
            onPropertyChanged( );
        }
    }

    public double getImageOffsetY( ) {
        return _imageOffsetY;
    }
    public void setImageOffsetY( double value ) {
        if( _imageOffsetY != value ) {
            this._imageOffsetY = value;
            onPropertyChanged( );
        }
    }


}
