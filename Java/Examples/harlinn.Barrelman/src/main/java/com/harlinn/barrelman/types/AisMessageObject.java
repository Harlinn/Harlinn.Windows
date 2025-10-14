package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class AisMessageObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _receivedTimestamp;
    private long _messageSequenceNumber = 0;
    private int _repeat = 0;
    private Guid _mmsi;


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

    public DateTime getReceivedTimestamp( ) {
        return _receivedTimestamp;
    }
    public void setReceivedTimestamp( DateTime value ) {
        if( !Comparer.equalsDateTime( _receivedTimestamp, value ) ) {
            _receivedTimestamp = value;
            onPropertyChanged( );
        }
    }

    public long getMessageSequenceNumber( ) {
        return _messageSequenceNumber;
    }
    public void setMessageSequenceNumber( long value ) {
        if( !Comparer.equalsInt64( _messageSequenceNumber, value ) ) {
            _messageSequenceNumber = value;
            onPropertyChanged( );
        }
    }

    public int getRepeat( ) {
        return _repeat;
    }
    public void setRepeat( int value ) {
        if( !Comparer.equalsInt32( _repeat, value ) ) {
            _repeat = value;
            onPropertyChanged( );
        }
    }

    public Guid getMmsi( ) {
        return _mmsi;
    }
    public void setMmsi( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mmsi, value ) ) {
            _mmsi = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _aisDevice );
        destination.writeDateTime( _receivedTimestamp );
        destination.writeInt64( _messageSequenceNumber );
        destination.writeInt32( _repeat );
        destination.writeNullableGuid( _mmsi );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _aisDevice = source.readGuid( );
        _receivedTimestamp = source.readDateTime( );
        _messageSequenceNumber = source.readInt64( );
        _repeat = source.readInt32( );
        _mmsi = source.readNullableGuid( );
    }

}
