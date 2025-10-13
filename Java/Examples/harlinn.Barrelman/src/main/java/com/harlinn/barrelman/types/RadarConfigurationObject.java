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
    private UnsignedInteger _imageSubstitutionColor;
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
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getRadar( ) {
        return _radar;
    }
    public void setRadar( Guid value ) {
        if( _radar != value ) {
            this._radar = value;
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

    public int getRadarProtocolVersion( ) {
        return _radarProtocolVersion;
    }
    public void setRadarProtocolVersion( int value ) {
        if( _radarProtocolVersion != value ) {
            this._radarProtocolVersion = value;
            onPropertyChanged( );
        }
    }

    public String getRadarIPAddress( ) {
        return _radarIPAddress;
    }
    public void setRadarIPAddress( String value ) {
        if( _radarIPAddress != value ) {
            this._radarIPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getRadarPort( ) {
        return _radarPort;
    }
    public void setRadarPort( int value ) {
        if( _radarPort != value ) {
            this._radarPort = value;
            onPropertyChanged( );
        }
    }

    public int getRadarConfigurationPort( ) {
        return _radarConfigurationPort;
    }
    public void setRadarConfigurationPort( int value ) {
        if( _radarConfigurationPort != value ) {
            this._radarConfigurationPort = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getSkipMagicTimeout( ) {
        return _skipMagicTimeout;
    }
    public void setSkipMagicTimeout( TimeSpan value ) {
        if( _skipMagicTimeout != value ) {
            this._skipMagicTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getReadTimeout( ) {
        return _readTimeout;
    }
    public void setReadTimeout( TimeSpan value ) {
        if( _readTimeout != value ) {
            this._readTimeout = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getSynchronizationInterval( ) {
        return _synchronizationInterval;
    }
    public void setSynchronizationInterval( TimeSpan value ) {
        if( _synchronizationInterval != value ) {
            this._synchronizationInterval = value;
            onPropertyChanged( );
        }
    }

    public int getTargetsRefreshRate( ) {
        return _targetsRefreshRate;
    }
    public void setTargetsRefreshRate( int value ) {
        if( _targetsRefreshRate != value ) {
            this._targetsRefreshRate = value;
            onPropertyChanged( );
        }
    }

    public int getRange( ) {
        return _range;
    }
    public void setRange( int value ) {
        if( _range != value ) {
            this._range = value;
            onPropertyChanged( );
        }
    }

    public int getSectorCount( ) {
        return _sectorCount;
    }
    public void setSectorCount( int value ) {
        if( _sectorCount != value ) {
            this._sectorCount = value;
            onPropertyChanged( );
        }
    }

    public int getSectorOffset( ) {
        return _sectorOffset;
    }
    public void setSectorOffset( int value ) {
        if( _sectorOffset != value ) {
            this._sectorOffset = value;
            onPropertyChanged( );
        }
    }

    public int getImageColor( ) {
        return _imageColor;
    }
    public void setImageColor( int value ) {
        if( _imageColor != value ) {
            this._imageColor = value;
            onPropertyChanged( );
        }
    }

    public UnsignedInteger getImageSubstitutionColor( ) {
        return _imageSubstitutionColor;
    }
    public void setImageSubstitutionColor( UnsignedInteger value ) {
        if( _imageSubstitutionColor != value ) {
            this._imageSubstitutionColor = value;
            onPropertyChanged( );
        }
    }

    public int getTransparentColor( ) {
        return _transparentColor;
    }
    public void setTransparentColor( int value ) {
        if( _transparentColor != value ) {
            this._transparentColor = value;
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

    public int getRadarImageType( ) {
        return _radarImageType;
    }
    public void setRadarImageType( int value ) {
        if( _radarImageType != value ) {
            this._radarImageType = value;
            onPropertyChanged( );
        }
    }

    public int getTrackColor( ) {
        return _trackColor;
    }
    public void setTrackColor( int value ) {
        if( _trackColor != value ) {
            this._trackColor = value;
            onPropertyChanged( );
        }
    }

    public int getVectorColor( ) {
        return _vectorColor;
    }
    public void setVectorColor( int value ) {
        if( _vectorColor != value ) {
            this._vectorColor = value;
            onPropertyChanged( );
        }
    }

    public boolean getEnableNmea( ) {
        return _enableNmea;
    }
    public void setEnableNmea( boolean value ) {
        if( _enableNmea != value ) {
            this._enableNmea = value;
            onPropertyChanged( );
        }
    }

    public String getNmeaReceiverIPAddress( ) {
        return _nmeaReceiverIPAddress;
    }
    public void setNmeaReceiverIPAddress( String value ) {
        if( _nmeaReceiverIPAddress != value ) {
            this._nmeaReceiverIPAddress = value;
            onPropertyChanged( );
        }
    }

    public int getNmeaReceiverPort( ) {
        return _nmeaReceiverPort;
    }
    public void setNmeaReceiverPort( int value ) {
        if( _nmeaReceiverPort != value ) {
            this._nmeaReceiverPort = value;
            onPropertyChanged( );
        }
    }

    public String getNmeaReceiverSourceId( ) {
        return _nmeaReceiverSourceId;
    }
    public void setNmeaReceiverSourceId( String value ) {
        if( _nmeaReceiverSourceId != value ) {
            this._nmeaReceiverSourceId = value;
            onPropertyChanged( );
        }
    }


}
