package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceRawMessageObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _timestamp;
    private boolean _isSent = false;
    private String _message = "";

    @Override
    public int getObjectType( ) {
        return Kind.AisDeviceRawMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceRawMessageObject( );
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

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( !Comparer.equalsGuid( _aisDevice, value ) ) {
            _aisDevice = value;
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

    public boolean getIsSent( ) {
        return _isSent;
    }
    public void setIsSent( boolean value ) {
        if( !Comparer.equalsBoolean( _isSent, value ) ) {
            _isSent = value;
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
        destination.writeGuid( _aisDevice );
        destination.writeDateTime( _timestamp );
        destination.writeBoolean( _isSent );
        destination.writeStringUtf8( _message );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _aisDevice = source.readGuid( );
        _timestamp = source.readDateTime( );
        _isSent = source.readBoolean( );
        _message = source.readString( );
    }

}
