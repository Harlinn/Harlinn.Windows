package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _radarProtocolVersion = 0;
    private String _radarIPAddress = "";
    private int _radarPort = 0;
    private int _radarConfigurationPort = 0;
    private TimeSpan _skipMagicTimeout;
    private TimeSpan _readTimeout;
    private TimeSpan _synchronizationInterval;
    private int _targetsRefreshRate = 0;
    private int _range = 0;
    private int _sectorCount = 0;
    private int _sectorOffset = 0;
    private int _imageColor = 0;
    private Integer _imageSubstitutionColor;
    private int _transparentColor = 0;
    private double _imageScaleFactorX = 0.0;
    private double _imageOffsetX = 0.0;
    private double _imageScaleFactorY = 0.0;
    private double _imageOffsetY = 0.0;
    private int _radarImageType = RadarImageType.MaskedProcessed;
    private int _trackColor = 0;
    private int _vectorColor = 0;
    private boolean _enableNmea = false;
    private String _nmeaReceiverIPAddress = "";
    private int _nmeaReceiverPort = 0;
    private String _nmeaReceiverSourceId = "";

    @Override
    public int getObjectType( ) {
        return Kind.RadarConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarConfigurationObject( );
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

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( !Comparer.equalsGuid( _radar, value ) ) {
            _radar = value;
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

    public int getRadarProtocolVersion( ) {
        return _radarProtocolVersion;
    }
    public void setRadarProtocolVersion( int value ) {
        if( !Comparer.equalsInt32( _radarProtocolVersion, value ) ) {
            _radarProtocolVersion = value;
            onPropertyChanged( );
        }
    }

    public String getRadarIPAddress( ) {
        return _radarIPAddress;
    }
    public void setRadarIPAddress( String value ) {
        if( !Comparer.equalsString( _radarIPAddress, value ) ) {
            _radarIPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getRadarPort( ) {
        return _radarPort;
    }
    public void setRadarPort( int value ) {
        if( !Comparer.equalsInt32( _radarPort, value ) ) {
            _radarPort = value;
            onPropertyChanged( );
        }
    }

    public int getRadarConfigurationPort( ) {
        return _radarConfigurationPort;
    }
    public void setRadarConfigurationPort( int value ) {
        if( !Comparer.equalsInt32( _radarConfigurationPort, value ) ) {
            _radarConfigurationPort = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getSkipMagicTimeout( ) {
        return _skipMagicTimeout;
    }
    public void setSkipMagicTimeout( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _skipMagicTimeout, value ) ) {
            _skipMagicTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getReadTimeout( ) {
        return _readTimeout;
    }
    public void setReadTimeout( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _readTimeout, value ) ) {
            _readTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getSynchronizationInterval( ) {
        return _synchronizationInterval;
    }
    public void setSynchronizationInterval( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _synchronizationInterval, value ) ) {
            _synchronizationInterval = value;
            onPropertyChanged( );
        }
    }

    public int getTargetsRefreshRate( ) {
        return _targetsRefreshRate;
    }
    public void setTargetsRefreshRate( int value ) {
        if( !Comparer.equalsInt32( _targetsRefreshRate, value ) ) {
            _targetsRefreshRate = value;
            onPropertyChanged( );
        }
    }

    public int getRange( ) {
        return _range;
    }
    public void setRange( int value ) {
        if( !Comparer.equalsInt32( _range, value ) ) {
            _range = value;
            onPropertyChanged( );
        }
    }

    public int getSectorCount( ) {
        return _sectorCount;
    }
    public void setSectorCount( int value ) {
        if( !Comparer.equalsInt32( _sectorCount, value ) ) {
            _sectorCount = value;
            onPropertyChanged( );
        }
    }

    public int getSectorOffset( ) {
        return _sectorOffset;
    }
    public void setSectorOffset( int value ) {
        if( !Comparer.equalsInt32( _sectorOffset, value ) ) {
            _sectorOffset = value;
            onPropertyChanged( );
        }
    }

    public int getImageColor( ) {
        return _imageColor;
    }
    public void setImageColor( int value ) {
        if( !Comparer.equalsUInt32( _imageColor, value ) ) {
            _imageColor = value;
            onPropertyChanged( );
        }
    }

    public Integer getImageSubstitutionColor( ) {
        return _imageSubstitutionColor;
    }
    public void setImageSubstitutionColor( Integer value ) {
        if( !Comparer.equalsNullableUInt32( _imageSubstitutionColor, value ) ) {
            _imageSubstitutionColor = value;
            onPropertyChanged( );
        }
    }

    public int getTransparentColor( ) {
        return _transparentColor;
    }
    public void setTransparentColor( int value ) {
        if( !Comparer.equalsUInt32( _transparentColor, value ) ) {
            _transparentColor = value;
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

    public int getRadarImageType( ) {
        return _radarImageType;
    }
    public void setRadarImageType( int value ) {
        if( !Comparer.equalsInt32( _radarImageType, value ) ) {
            _radarImageType = value;
            onPropertyChanged( );
        }
    }

    public int getTrackColor( ) {
        return _trackColor;
    }
    public void setTrackColor( int value ) {
        if( !Comparer.equalsUInt32( _trackColor, value ) ) {
            _trackColor = value;
            onPropertyChanged( );
        }
    }

    public int getVectorColor( ) {
        return _vectorColor;
    }
    public void setVectorColor( int value ) {
        if( !Comparer.equalsUInt32( _vectorColor, value ) ) {
            _vectorColor = value;
            onPropertyChanged( );
        }
    }

    public boolean getEnableNmea( ) {
        return _enableNmea;
    }
    public void setEnableNmea( boolean value ) {
        if( !Comparer.equalsBoolean( _enableNmea, value ) ) {
            _enableNmea = value;
            onPropertyChanged( );
        }
    }

    public String getNmeaReceiverIPAddress( ) {
        return _nmeaReceiverIPAddress;
    }
    public void setNmeaReceiverIPAddress( String value ) {
        if( !Comparer.equalsString( _nmeaReceiverIPAddress, value ) ) {
            _nmeaReceiverIPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getNmeaReceiverPort( ) {
        return _nmeaReceiverPort;
    }
    public void setNmeaReceiverPort( int value ) {
        if( !Comparer.equalsInt32( _nmeaReceiverPort, value ) ) {
            _nmeaReceiverPort = value;
            onPropertyChanged( );
        }
    }

    public String getNmeaReceiverSourceId( ) {
        return _nmeaReceiverSourceId;
    }
    public void setNmeaReceiverSourceId( String value ) {
        if( !Comparer.equalsString( _nmeaReceiverSourceId, value ) ) {
            _nmeaReceiverSourceId = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radar );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _radarProtocolVersion );
        destination.writeStringUtf8( _radarIPAddress );
        destination.writeInt32( _radarPort );
        destination.writeInt32( _radarConfigurationPort );
        destination.writeTimeSpan( _skipMagicTimeout );
        destination.writeTimeSpan( _readTimeout );
        destination.writeTimeSpan( _synchronizationInterval );
        destination.writeInt32( _targetsRefreshRate );
        destination.writeInt32( _range );
        destination.writeInt32( _sectorCount );
        destination.writeInt32( _sectorOffset );
        destination.writeUInt32( _imageColor );
        destination.writeNullableUInt32( _imageSubstitutionColor );
        destination.writeUInt32( _transparentColor );
        destination.writeDouble( _imageScaleFactorX );
        destination.writeDouble( _imageOffsetX );
        destination.writeDouble( _imageScaleFactorY );
        destination.writeDouble( _imageOffsetY );
        destination.writeInt32( _radarImageType );
        destination.writeUInt32( _trackColor );
        destination.writeUInt32( _vectorColor );
        destination.writeBoolean( _enableNmea );
        destination.writeStringUtf8( _nmeaReceiverIPAddress );
        destination.writeInt32( _nmeaReceiverPort );
        destination.writeStringUtf8( _nmeaReceiverSourceId );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radar = source.readGuid( );
        _timestamp = source.readDateTime( );
        _radarProtocolVersion = source.readInt32( );
        _radarIPAddress = source.readString( );
        _radarPort = source.readInt32( );
        _radarConfigurationPort = source.readInt32( );
        _skipMagicTimeout = source.readTimeSpan( );
        _readTimeout = source.readTimeSpan( );
        _synchronizationInterval = source.readTimeSpan( );
        _targetsRefreshRate = source.readInt32( );
        _range = source.readInt32( );
        _sectorCount = source.readInt32( );
        _sectorOffset = source.readInt32( );
        _imageColor = source.readUInt32( );
        _imageSubstitutionColor = source.readNullableUInt32( );
        _transparentColor = source.readUInt32( );
        _imageScaleFactorX = source.readDouble( );
        _imageOffsetX = source.readDouble( );
        _imageScaleFactorY = source.readDouble( );
        _imageOffsetY = source.readDouble( );
        _radarImageType = source.readInt32( );
        _trackColor = source.readUInt32( );
        _vectorColor = source.readUInt32( );
        _enableNmea = source.readBoolean( );
        _nmeaReceiverIPAddress = source.readString( );
        _nmeaReceiverPort = source.readInt32( );
        _nmeaReceiverSourceId = source.readString( );
    }

}
