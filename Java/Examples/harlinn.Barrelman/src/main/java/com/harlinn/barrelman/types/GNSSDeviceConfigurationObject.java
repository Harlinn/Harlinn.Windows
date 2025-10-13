package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class GNSSDeviceConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _gNSSDevice;
    private DateTime _timestamp;
    private double _defaultLatitude = 0.0;
    private double _defaultLongitude = 0.0;
    private double _defaultAltitude = 0.0;
    private double _latitudeOffset = 0.0;
    private double _longitudeOffset = 0.0;
    private double _altitudeOffset = 0.0;

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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( _gNSSDevice != value ) {
            this._gNSSDevice = value;
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

    public double getDefaultLatitude( ) {
        return _defaultLatitude;
    }
    public void setDefaultLatitude( double value ) {
        if( _defaultLatitude != value ) {
            this._defaultLatitude = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultLongitude( ) {
        return _defaultLongitude;
    }
    public void setDefaultLongitude( double value ) {
        if( _defaultLongitude != value ) {
            this._defaultLongitude = value;
            onPropertyChanged( );
        }
    }

    public double getDefaultAltitude( ) {
        return _defaultAltitude;
    }
    public void setDefaultAltitude( double value ) {
        if( _defaultAltitude != value ) {
            this._defaultAltitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitudeOffset( ) {
        return _latitudeOffset;
    }
    public void setLatitudeOffset( double value ) {
        if( _latitudeOffset != value ) {
            this._latitudeOffset = value;
            onPropertyChanged( );
        }
    }

    public double getLongitudeOffset( ) {
        return _longitudeOffset;
    }
    public void setLongitudeOffset( double value ) {
        if( _longitudeOffset != value ) {
            this._longitudeOffset = value;
            onPropertyChanged( );
        }
    }

    public double getAltitudeOffset( ) {
        return _altitudeOffset;
    }
    public void setAltitudeOffset( double value ) {
        if( _altitudeOffset != value ) {
            this._altitudeOffset = value;
            onPropertyChanged( );
        }
    }


}
