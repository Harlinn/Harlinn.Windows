package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadioConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radio;
    private DateTime _timestamp;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private String _playbackUrl = "";
    private String _radioIPAddress = "";
    private int _radioPort = 0;
    private String _ed137IPAddress = "";
    private int _ed137Port = 0;

    @Override
    public int getObjectType( ) {
        return Kind.RadioConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadioConfigurationObject( );
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

    public Guid getRadio( ) {
        return _radio;
    }
    public void setRadio( Guid value ) {
        if( _radio != value ) {
            this._radio = value;
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

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
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

    public String getPlaybackUrl( ) {
        return _playbackUrl;
    }
    public void setPlaybackUrl( String value ) {
        if( _playbackUrl != value ) {
            this._playbackUrl = value;
            onPropertyChanged( );
        }
    }

    public String getRadioIPAddress( ) {
        return _radioIPAddress;
    }
    public void setRadioIPAddress( String value ) {
        if( _radioIPAddress != value ) {
            this._radioIPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getRadioPort( ) {
        return _radioPort;
    }
    public void setRadioPort( int value ) {
        if( _radioPort != value ) {
            this._radioPort = value;
            onPropertyChanged( );
        }
    }

    public String getEd137IPAddress( ) {
        return _ed137IPAddress;
    }
    public void setEd137IPAddress( String value ) {
        if( _ed137IPAddress != value ) {
            this._ed137IPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getEd137Port( ) {
        return _ed137Port;
    }
    public void setEd137Port( int value ) {
        if( _ed137Port != value ) {
            this._ed137Port = value;
            onPropertyChanged( );
        }
    }


}
