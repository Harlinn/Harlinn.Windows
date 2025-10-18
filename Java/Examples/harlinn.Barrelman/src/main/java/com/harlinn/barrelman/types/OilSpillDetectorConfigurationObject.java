package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class OilSpillDetectorConfigurationObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.OilSpillDetectorConfiguration;

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

    public OilSpillDetectorConfigurationObject( ) {
    }
    public OilSpillDetectorConfigurationObject( byte objectState, Guid id, long rowVersion, Guid oilSpillDetector, DateTime timestamp, double range, double startAngle, double endAngle, double startRange, double endRange, int updateRate, TimeSpan statusSendTime, boolean drawBorder, byte[] colors, boolean sendToServer, String directory, boolean transparentWater, boolean savePictures, boolean sendAsTarget, boolean writeLog, String targetFilePrefix, Guid targetMMSI, double latitude, double longitude, boolean testSourceEnabled, String proxyServer, boolean useProxyServer ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._oilSpillDetector = oilSpillDetector;
        this._timestamp = timestamp;
        this._range = range;
        this._startAngle = startAngle;
        this._endAngle = endAngle;
        this._startRange = startRange;
        this._endRange = endRange;
        this._updateRate = updateRate;
        this._statusSendTime = statusSendTime;
        this._drawBorder = drawBorder;
        this._colors = colors;
        this._sendToServer = sendToServer;
        this._directory = directory;
        this._transparentWater = transparentWater;
        this._savePictures = savePictures;
        this._sendAsTarget = sendAsTarget;
        this._writeLog = writeLog;
        this._targetFilePrefix = targetFilePrefix;
        this._targetMMSI = targetMMSI;
        this._latitude = latitude;
        this._longitude = longitude;
        this._testSourceEnabled = testSourceEnabled;
        this._proxyServer = proxyServer;
        this._useProxyServer = useProxyServer;
    }

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
        if( !Comparer.equalsInt64( _rowVersion, value ) ) {
            _rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getOilSpillDetector( ) {
        return _oilSpillDetector;
    }
    public void setOilSpillDetector( Guid value ) {
        if( !Comparer.equalsGuid( _oilSpillDetector, value ) ) {
            _oilSpillDetector = value;
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

    public double getRange( ) {
        return _range;
    }
    public void setRange( double value ) {
        if( !Comparer.equalsDouble( _range, value ) ) {
            _range = value;
            onPropertyChanged( );
        }
    }

    public double getStartAngle( ) {
        return _startAngle;
    }
    public void setStartAngle( double value ) {
        if( !Comparer.equalsDouble( _startAngle, value ) ) {
            _startAngle = value;
            onPropertyChanged( );
        }
    }

    public double getEndAngle( ) {
        return _endAngle;
    }
    public void setEndAngle( double value ) {
        if( !Comparer.equalsDouble( _endAngle, value ) ) {
            _endAngle = value;
            onPropertyChanged( );
        }
    }

    public double getStartRange( ) {
        return _startRange;
    }
    public void setStartRange( double value ) {
        if( !Comparer.equalsDouble( _startRange, value ) ) {
            _startRange = value;
            onPropertyChanged( );
        }
    }

    public double getEndRange( ) {
        return _endRange;
    }
    public void setEndRange( double value ) {
        if( !Comparer.equalsDouble( _endRange, value ) ) {
            _endRange = value;
            onPropertyChanged( );
        }
    }

    public int getUpdateRate( ) {
        return _updateRate;
    }
    public void setUpdateRate( int value ) {
        if( !Comparer.equalsInt32( _updateRate, value ) ) {
            _updateRate = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getStatusSendTime( ) {
        return _statusSendTime;
    }
    public void setStatusSendTime( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _statusSendTime, value ) ) {
            _statusSendTime = value;
            onPropertyChanged( );
        }
    }

    public boolean getDrawBorder( ) {
        return _drawBorder;
    }
    public void setDrawBorder( boolean value ) {
        if( !Comparer.equalsBoolean( _drawBorder, value ) ) {
            _drawBorder = value;
            onPropertyChanged( );
        }
    }

    public byte[] getColors( ) {
        return _colors;
    }
    public void setColors( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _colors, value ) ) {
            _colors = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }

    public boolean getSendToServer( ) {
        return _sendToServer;
    }
    public void setSendToServer( boolean value ) {
        if( !Comparer.equalsBoolean( _sendToServer, value ) ) {
            _sendToServer = value;
            onPropertyChanged( );
        }
    }

    public String getDirectory( ) {
        return _directory;
    }
    public void setDirectory( String value ) {
        if( !Comparer.equalsString( _directory, value ) ) {
            _directory = value;
            onPropertyChanged( );
        }
    }

    public boolean getTransparentWater( ) {
        return _transparentWater;
    }
    public void setTransparentWater( boolean value ) {
        if( !Comparer.equalsBoolean( _transparentWater, value ) ) {
            _transparentWater = value;
            onPropertyChanged( );
        }
    }

    public boolean getSavePictures( ) {
        return _savePictures;
    }
    public void setSavePictures( boolean value ) {
        if( !Comparer.equalsBoolean( _savePictures, value ) ) {
            _savePictures = value;
            onPropertyChanged( );
        }
    }

    public boolean getSendAsTarget( ) {
        return _sendAsTarget;
    }
    public void setSendAsTarget( boolean value ) {
        if( !Comparer.equalsBoolean( _sendAsTarget, value ) ) {
            _sendAsTarget = value;
            onPropertyChanged( );
        }
    }

    public boolean getWriteLog( ) {
        return _writeLog;
    }
    public void setWriteLog( boolean value ) {
        if( !Comparer.equalsBoolean( _writeLog, value ) ) {
            _writeLog = value;
            onPropertyChanged( );
        }
    }

    public String getTargetFilePrefix( ) {
        return _targetFilePrefix;
    }
    public void setTargetFilePrefix( String value ) {
        if( !Comparer.equalsString( _targetFilePrefix, value ) ) {
            _targetFilePrefix = value;
            onPropertyChanged( );
        }
    }

    public Guid getTargetMMSI( ) {
        return _targetMMSI;
    }
    public void setTargetMMSI( Guid value ) {
        if( !Comparer.equalsNullableGuid( _targetMMSI, value ) ) {
            _targetMMSI = value;
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

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public boolean getTestSourceEnabled( ) {
        return _testSourceEnabled;
    }
    public void setTestSourceEnabled( boolean value ) {
        if( !Comparer.equalsBoolean( _testSourceEnabled, value ) ) {
            _testSourceEnabled = value;
            onPropertyChanged( );
        }
    }

    public String getProxyServer( ) {
        return _proxyServer;
    }
    public void setProxyServer( String value ) {
        if( !Comparer.equalsString( _proxyServer, value ) ) {
            _proxyServer = value;
            onPropertyChanged( );
        }
    }

    public boolean getUseProxyServer( ) {
        return _useProxyServer;
    }
    public void setUseProxyServer( boolean value ) {
        if( !Comparer.equalsBoolean( _useProxyServer, value ) ) {
            _useProxyServer = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( OilSpillDetectorConfigurationObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._oilSpillDetector = this._oilSpillDetector;
        targetObject._timestamp = this._timestamp;
        targetObject._range = this._range;
        targetObject._startAngle = this._startAngle;
        targetObject._endAngle = this._endAngle;
        targetObject._startRange = this._startRange;
        targetObject._endRange = this._endRange;
        targetObject._updateRate = this._updateRate;
        targetObject._statusSendTime = this._statusSendTime;
        targetObject._drawBorder = this._drawBorder;
        targetObject._colors = this._colors != null ? this._colors.clone() : this._colors;;
        targetObject._sendToServer = this._sendToServer;
        targetObject._directory = this._directory;
        targetObject._transparentWater = this._transparentWater;
        targetObject._savePictures = this._savePictures;
        targetObject._sendAsTarget = this._sendAsTarget;
        targetObject._writeLog = this._writeLog;
        targetObject._targetFilePrefix = this._targetFilePrefix;
        targetObject._targetMMSI = this._targetMMSI;
        targetObject._latitude = this._latitude;
        targetObject._longitude = this._longitude;
        targetObject._testSourceEnabled = this._testSourceEnabled;
        targetObject._proxyServer = this._proxyServer;
        targetObject._useProxyServer = this._useProxyServer;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (OilSpillDetectorConfigurationObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._oilSpillDetector, other._oilSpillDetector ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._range, other._range ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._startAngle, other._startAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._endAngle, other._endAngle ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._startRange, other._startRange ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._endRange, other._endRange ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._updateRate, other._updateRate ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._statusSendTime, other._statusSendTime ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._drawBorder, other._drawBorder ) ) {
            return false;
        }
        if( !Comparer.equalsUInt8Array( this._colors, other._colors ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._sendToServer, other._sendToServer ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._directory, other._directory ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._transparentWater, other._transparentWater ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._savePictures, other._savePictures ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._sendAsTarget, other._sendAsTarget ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._writeLog, other._writeLog ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._targetFilePrefix, other._targetFilePrefix ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._targetMMSI, other._targetMMSI ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._testSourceEnabled, other._testSourceEnabled ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._proxyServer, other._proxyServer ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._useProxyServer, other._useProxyServer ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _oilSpillDetector );
        destination.writeDateTime( _timestamp );
        destination.writeDouble( _range );
        destination.writeDouble( _startAngle );
        destination.writeDouble( _endAngle );
        destination.writeDouble( _startRange );
        destination.writeDouble( _endRange );
        destination.writeInt32( _updateRate );
        destination.writeTimeSpan( _statusSendTime );
        destination.writeBoolean( _drawBorder );
        destination.writeUInt8Array( _colors );
        destination.writeBoolean( _sendToServer );
        destination.writeStringUtf8( _directory );
        destination.writeBoolean( _transparentWater );
        destination.writeBoolean( _savePictures );
        destination.writeBoolean( _sendAsTarget );
        destination.writeBoolean( _writeLog );
        destination.writeStringUtf8( _targetFilePrefix );
        destination.writeNullableGuid( _targetMMSI );
        destination.writeDouble( _latitude );
        destination.writeDouble( _longitude );
        destination.writeBoolean( _testSourceEnabled );
        destination.writeStringUtf8( _proxyServer );
        destination.writeBoolean( _useProxyServer );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _oilSpillDetector = source.readGuid( );
        _timestamp = source.readDateTime( );
        _range = source.readDouble( );
        _startAngle = source.readDouble( );
        _endAngle = source.readDouble( );
        _startRange = source.readDouble( );
        _endRange = source.readDouble( );
        _updateRate = source.readInt32( );
        _statusSendTime = source.readTimeSpan( );
        _drawBorder = source.readBoolean( );
        _colors = source.readUInt8Array( );
        _sendToServer = source.readBoolean( );
        _directory = source.readString( );
        _transparentWater = source.readBoolean( );
        _savePictures = source.readBoolean( );
        _sendAsTarget = source.readBoolean( );
        _writeLog = source.readBoolean( );
        _targetFilePrefix = source.readString( );
        _targetMMSI = source.readNullableGuid( );
        _latitude = source.readDouble( );
        _longitude = source.readDouble( );
        _testSourceEnabled = source.readBoolean( );
        _proxyServer = source.readString( );
        _useProxyServer = source.readBoolean( );
    }

}
