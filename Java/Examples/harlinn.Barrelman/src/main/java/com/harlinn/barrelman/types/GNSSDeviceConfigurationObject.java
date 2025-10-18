package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GNSSDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.GNSSDeviceConfiguration;

    private long _rowVersion = 0;
    private Guid _gNSSDevice;
    private DateTime _timestamp;
    private double _defaultLatitude = 0.0;
    private double _defaultLongitude = 0.0;
    private double _defaultAltitude = 0.0;
    private double _latitudeOffset = 0.0;
    private double _longitudeOffset = 0.0;
    private double _altitudeOffset = 0.0;

    public GNSSDeviceConfigurationObject( ) {
    }
    public GNSSDeviceConfigurationObject( byte objectState, Guid id, long rowVersion, Guid gNSSDevice, DateTime timestamp, double defaultLatitude, double defaultLongitude, double defaultAltitude, double latitudeOffset, double longitudeOffset, double altitudeOffset ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._gNSSDevice = gNSSDevice;
        this._timestamp = timestamp;
        this._defaultLatitude = defaultLatitude;
        this._defaultLongitude = defaultLongitude;
        this._defaultAltitude = defaultAltitude;
        this._latitudeOffset = latitudeOffset;
        this._longitudeOffset = longitudeOffset;
        this._altitudeOffset = altitudeOffset;
    }

    @Override
    public int getObjectType( ) {
        return Kind.GNSSDeviceConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSDeviceConfigurationObject( );
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

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( !Comparer.equalsGuid( _gNSSDevice, value ) ) {
            _gNSSDevice = value;
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

    public double getDefaultLatitude( ) {
        return _defaultLatitude;
    }
    public void setDefaultLatitude( double value ) {
        if( !Comparer.equalsDouble( _defaultLatitude, value ) ) {
            _defaultLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultLongitude( ) {
        return _defaultLongitude;
    }
    public void setDefaultLongitude( double value ) {
        if( !Comparer.equalsDouble( _defaultLongitude, value ) ) {
            _defaultLongitude = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultAltitude( ) {
        return _defaultAltitude;
    }
    public void setDefaultAltitude( double value ) {
        if( !Comparer.equalsDouble( _defaultAltitude, value ) ) {
            _defaultAltitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitudeOffset( ) {
        return _latitudeOffset;
    }
    public void setLatitudeOffset( double value ) {
        if( !Comparer.equalsDouble( _latitudeOffset, value ) ) {
            _latitudeOffset = value;
            onPropertyChanged( );
        }
    }

    public double getLongitudeOffset( ) {
        return _longitudeOffset;
    }
    public void setLongitudeOffset( double value ) {
        if( !Comparer.equalsDouble( _longitudeOffset, value ) ) {
            _longitudeOffset = value;
            onPropertyChanged( );
        }
    }

    public double getAltitudeOffset( ) {
        return _altitudeOffset;
    }
    public void setAltitudeOffset( double value ) {
        if( !Comparer.equalsDouble( _altitudeOffset, value ) ) {
            _altitudeOffset = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GNSSDeviceConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._gNSSDevice = this._gNSSDevice;
        targetObject._timestamp = this._timestamp;
        targetObject._defaultLatitude = this._defaultLatitude;
        targetObject._defaultLongitude = this._defaultLongitude;
        targetObject._defaultAltitude = this._defaultAltitude;
        targetObject._latitudeOffset = this._latitudeOffset;
        targetObject._longitudeOffset = this._longitudeOffset;
        targetObject._altitudeOffset = this._altitudeOffset;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GNSSDeviceConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._gNSSDevice, other._gNSSDevice ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._defaultLatitude, other._defaultLatitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._defaultLongitude, other._defaultLongitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._defaultAltitude, other._defaultAltitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitudeOffset, other._latitudeOffset ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitudeOffset, other._longitudeOffset ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._altitudeOffset, other._altitudeOffset ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _gNSSDevice );
        destination.writeDateTime( _timestamp );
        destination.writeDouble( _defaultLatitude );
        destination.writeDouble( _defaultLongitude );
        destination.writeDouble( _defaultAltitude );
        destination.writeDouble( _latitudeOffset );
        destination.writeDouble( _longitudeOffset );
        destination.writeDouble( _altitudeOffset );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _gNSSDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _defaultLatitude = source.readDouble( );
        _defaultLongitude = source.readDouble( );
        _defaultAltitude = source.readDouble( );
        _latitudeOffset = source.readDouble( );
        _longitudeOffset = source.readDouble( );
        _altitudeOffset = source.readDouble( );
    }

}
