package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class OilSpillDetectorConfigurationObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _oilSpillDetector;
    private DateTime _timestamp;
    private double _range = 0.0;
    private double _startAngle = 0.0;
    private double _endAngle = 0.0;
    private double _startRange = 0.0;
    private double _endRange = 0.0;
    private int _updateRate = 0;
    private TimeSpan _statusSendTime;
    private boolean _drawBorder = false;
    private byte[] _colors = new byte[0];
    private boolean _sendToServer = false;
    private String _directory = "";
    private boolean _transparentWater = false;
    private boolean _savePictures = false;
    private boolean _sendAsTarget = false;
    private boolean _writeLog = false;
    private String _targetFilePrefix = "";
    private Guid _targetMMSI;
    private double _latitude = 0.0;
    private double _longitude = 0.0;
    private boolean _testSourceEnabled = false;
    private String _proxyServer = "";
    private boolean _useProxyServer = false;

    @Override
    public int getObjectType( ) {
        return Kind.OilSpillDetectorConfiguration;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new OilSpillDetectorConfigurationObject( );
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

    public Guid getOilSpillDetector( ) {
        return _oilSpillDetector;
    }
    public void setOilSpillDetector( Guid value ) {
        if( _oilSpillDetector != value ) {
            this._oilSpillDetector = value;
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

    public double getRange( ) {
        return _range;
    }
    public void setRange( double value ) {
        if( _range != value ) {
            this._range = value;
            onPropertyChanged( );
        }
    }

    public double getStartAngle( ) {
        return _startAngle;
    }
    public void setStartAngle( double value ) {
        if( _startAngle != value ) {
            this._startAngle = value;
            onPropertyChanged( );
        }
    }

    public double getEndAngle( ) {
        return _endAngle;
    }
    public void setEndAngle( double value ) {
        if( _endAngle != value ) {
            this._endAngle = value;
            onPropertyChanged( );
        }
    }

    public double getStartRange( ) {
        return _startRange;
    }
    public void setStartRange( double value ) {
        if( _startRange != value ) {
            this._startRange = value;
            onPropertyChanged( );
        }
    }

    public double getEndRange( ) {
        return _endRange;
    }
    public void setEndRange( double value ) {
        if( _endRange != value ) {
            this._endRange = value;
            onPropertyChanged( );
        }
    }

    public int getUpdateRate( ) {
        return _updateRate;
    }
    public void setUpdateRate( int value ) {
        if( _updateRate != value ) {
            this._updateRate = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getStatusSendTime( ) {
        return _statusSendTime;
    }
    public void setStatusSendTime( TimeSpan value ) {
        if( _statusSendTime != value ) {
            this._statusSendTime = value;
            onPropertyChanged( );
        }
    }

    public boolean getDrawBorder( ) {
        return _drawBorder;
    }
    public void setDrawBorder( boolean value ) {
        if( _drawBorder != value ) {
            this._drawBorder = value;
            onPropertyChanged( );
        }
    }

    public byte[] getColors( ) {
        return _colors;
    }
    public void setColors( byte[] value ) {
        if( _colors != value ) {
            this._colors = value;
            onPropertyChanged( );
        }
    }

    public boolean getSendToServer( ) {
        return _sendToServer;
    }
    public void setSendToServer( boolean value ) {
        if( _sendToServer != value ) {
            this._sendToServer = value;
            onPropertyChanged( );
        }
    }

    public String getDirectory( ) {
        return _directory;
    }
    public void setDirectory( String value ) {
        if( _directory != value ) {
            this._directory = value;
            onPropertyChanged( );
        }
    }

    public boolean getTransparentWater( ) {
        return _transparentWater;
    }
    public void setTransparentWater( boolean value ) {
        if( _transparentWater != value ) {
            this._transparentWater = value;
            onPropertyChanged( );
        }
    }

    public boolean getSavePictures( ) {
        return _savePictures;
    }
    public void setSavePictures( boolean value ) {
        if( _savePictures != value ) {
            this._savePictures = value;
            onPropertyChanged( );
        }
    }

    public boolean getSendAsTarget( ) {
        return _sendAsTarget;
    }
    public void setSendAsTarget( boolean value ) {
        if( _sendAsTarget != value ) {
            this._sendAsTarget = value;
            onPropertyChanged( );
        }
    }

    public boolean getWriteLog( ) {
        return _writeLog;
    }
    public void setWriteLog( boolean value ) {
        if( _writeLog != value ) {
            this._writeLog = value;
            onPropertyChanged( );
        }
    }

    public String getTargetFilePrefix( ) {
        return _targetFilePrefix;
    }
    public void setTargetFilePrefix( String value ) {
        if( _targetFilePrefix != value ) {
            this._targetFilePrefix = value;
            onPropertyChanged( );
        }
    }

    public Guid getTargetMMSI( ) {
        return _targetMMSI;
    }
    public void setTargetMMSI( Guid value ) {
        if( _targetMMSI != value ) {
            this._targetMMSI = value;
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

    public boolean getTestSourceEnabled( ) {
        return _testSourceEnabled;
    }
    public void setTestSourceEnabled( boolean value ) {
        if( _testSourceEnabled != value ) {
            this._testSourceEnabled = value;
            onPropertyChanged( );
        }
    }

    public String getProxyServer( ) {
        return _proxyServer;
    }
    public void setProxyServer( String value ) {
        if( _proxyServer != value ) {
            this._proxyServer = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseProxyServer( ) {
        return _useProxyServer;
    }
    public void setUseProxyServer( boolean value ) {
        if( _useProxyServer != value ) {
            this._useProxyServer = value;
            onPropertyChanged( );
        }
    }


}
