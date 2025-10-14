package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AlarmStateChangeObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _alarm;
    private DateTime _timestamp;
    private int _state = AlarmState.Unknown;

    @Override
    public int getObjectType( ) {
        return Kind.AlarmStateChange;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AlarmStateChangeObject( );
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

    public Guid getAlarm( ) {
        return _alarm;
    }
    public void setAlarm( Guid value ) {
        if( !Comparer.equalsGuid( _alarm, value ) ) {
            _alarm = value;
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

    public int getState( ) {
        return _state;
    }
    public void setState( int value ) {
        if( !Comparer.equalsInt32( _state, value ) ) {
            _state = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _alarm );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _state );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _alarm = source.readGuid( );
        _timestamp = source.readDateTime( );
        _state = source.readInt32( );
    }

}
