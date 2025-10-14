package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class WeatherStationCommandReplyObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _weatherStation;
    private DateTime _timestamp;
    private Guid _command;
    private int _status = DeviceCommandReplyStatus.Unknown;
    private String _message = "";

    @Override
    public int getObjectType( ) {
        return Kind.WeatherStationCommandReply;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new WeatherStationCommandReplyObject( );
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

    public Guid getWeatherStation( ) {
        return _weatherStation;
    }
    public void setWeatherStation( Guid value ) {
        if( !Comparer.equalsGuid( _weatherStation, value ) ) {
            _weatherStation = value;
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

    public Guid getCommand( ) {
        return _command;
    }
    public void setCommand( Guid value ) {
        if( !Comparer.equalsNullableGuid( _command, value ) ) {
            _command = value;
            onPropertyChanged( );
        }
    }

    public int getStatus( ) {
        return _status;
    }
    public void setStatus( int value ) {
        if( !Comparer.equalsInt32( _status, value ) ) {
            _status = value;
            onPropertyChanged( );
        }
    }

    public String getMessage( ) {
        return _message;
    }
    public void setMessage( String value ) {
        if( !Comparer.equalsString( _message, value ) ) {
            _message = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _weatherStation );
        destination.writeDateTime( _timestamp );
        destination.writeNullableGuid( _command );
        destination.writeInt32( _status );
        destination.writeStringUtf8( _message );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _weatherStation = source.readGuid( );
        _timestamp = source.readDateTime( );
        _command = source.readNullableGuid( );
        _status = source.readInt32( );
        _message = source.readString( );
    }

}
