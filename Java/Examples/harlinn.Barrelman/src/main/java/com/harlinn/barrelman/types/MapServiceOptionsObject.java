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

    public String getIpAddress( ) {
        return _ipAddress;
    }
    public void setIpAddress( String value ) {
        if( !Comparer.equalsString( _ipAddress, value ) ) {
            _ipAddress = value;
            onPropertyChanged( );
        }
    }

    public int getPort( ) {
        return _port;
    }
    public void setPort( int value ) {
        if( !Comparer.equalsInt32( _port, value ) ) {
            _port = value;
            onPropertyChanged( );
        }
    }

    public double getImageScaleFactorX( ) {
        return _imageScaleFactorX;
    }
    public void setImageScaleFactorX( double value ) {
        if( !Comparer.equalsDouble( _imageScaleFactorX, value ) ) {
            _imageScaleFactorX = value;
            onPropertyChanged( );
        }
    }

    public double getImageOffsetX( ) {
        return _imageOffsetX;
    }
    public void setImageOffsetX( double value ) {
        if( !Comparer.equalsDouble( _imageOffsetX, value ) ) {
            _imageOffsetX = value;
            onPropertyChanged( );
        }
    }

    public double getImageScaleFactorY( ) {
        return _imageScaleFactorY;
    }
    public void setImageScaleFactorY( double value ) {
        if( !Comparer.equalsDouble( _imageScaleFactorY, value ) ) {
            _imageScaleFactorY = value;
            onPropertyChanged( );
        }
    }

    public double getImageOffsetY( ) {
        return _imageOffsetY;
    }
    public void setImageOffsetY( double value ) {
        if( !Comparer.equalsDouble( _imageOffsetY, value ) ) {
            _imageOffsetY = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( MapServiceOptionsObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._timestamp = this._timestamp;
        targetObject._ipAddress = this._ipAddress;
        targetObject._port = this._port;
        targetObject._imageScaleFactorX = this._imageScaleFactorX;
        targetObject._imageOffsetX = this._imageOffsetX;
        targetObject._imageScaleFactorY = this._imageScaleFactorY;
        targetObject._imageOffsetY = this._imageOffsetY;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (MapServiceOptionsObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._ipAddress, other._ipAddress ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._port, other._port ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._imageScaleFactorX, other._imageScaleFactorX ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._imageOffsetX, other._imageOffsetX ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._imageScaleFactorY, other._imageScaleFactorY ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._imageOffsetY, other._imageOffsetY ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeDateTime( _timestamp );
        destination.writeStringUtf8( _ipAddress );
        destination.writeInt32( _port );
        destination.writeDouble( _imageScaleFactorX );
        destination.writeDouble( _imageOffsetX );
        destination.writeDouble( _imageScaleFactorY );
        destination.writeDouble( _imageOffsetY );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _timestamp = source.readDateTime( );
        _ipAddress = source.readString( );
        _port = source.readInt32( );
        _imageScaleFactorX = source.readDouble( );
        _imageOffsetX = source.readDouble( );
        _imageScaleFactorY = source.readDouble( );
        _imageOffsetY = source.readDouble( );
    }

}
