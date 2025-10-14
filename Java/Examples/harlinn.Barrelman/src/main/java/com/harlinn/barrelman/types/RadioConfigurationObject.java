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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadio( ) {
        return _radio;
    }
    public void setRadio( Guid value ) {
        if( !Comparer.equalsGuid( _radio, value ) ) {
            _radio = value;
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

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
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

    public String getPlaybackUrl( ) {
        return _playbackUrl;
    }
    public void setPlaybackUrl( String value ) {
        if( !Comparer.equalsString( _playbackUrl, value ) ) {
            _playbackUrl = value;
            onPropertyChanged( );
        }
    }

    public String getRadioIPAddress( ) {
        return _radioIPAddress;
    }
    public void setRadioIPAddress( String value ) {
        if( !Comparer.equalsString( _radioIPAddress, value ) ) {
            _radioIPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getRadioPort( ) {
        return _radioPort;
    }
    public void setRadioPort( int value ) {
        if( !Comparer.equalsInt32( _radioPort, value ) ) {
            _radioPort = value;
            onPropertyChanged( );
        }
    }

    public String getEd137IPAddress( ) {
        return _ed137IPAddress;
    }
    public void setEd137IPAddress( String value ) {
        if( !Comparer.equalsString( _ed137IPAddress, value ) ) {
            _ed137IPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getEd137Port( ) {
        return _ed137Port;
    }
    public void setEd137Port( int value ) {
        if( !Comparer.equalsInt32( _ed137Port, value ) ) {
            _ed137Port = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radio );
        destination.writeDateTime( _timestamp );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeStringUtf8( _playbackUrl );
        destination.writeStringUtf8( _radioIPAddress );
        destination.writeInt32( _radioPort );
        destination.writeStringUtf8( _ed137IPAddress );
        destination.writeInt32( _ed137Port );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radio = source.readGuid( );
        _timestamp = source.readDateTime( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _playbackUrl = source.readString( );
        _radioIPAddress = source.readString( );
        _radioPort = source.readInt32( );
        _ed137IPAddress = source.readString( );
        _ed137Port = source.readInt32( );
    }

}
