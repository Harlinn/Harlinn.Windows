package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarStatusObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _azimuthCount = 0;
    private int _triggerCount = 0;
    private TimeSpan _rotationTime;
    private int _pulse = RadarPulse.Short;
    private boolean _tx = false;
    private boolean _tracking = false;

    @Override
    public int getObjectType( ) {
        return Kind.RadarStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarStatusObject( );
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

    public int getAzimuthCount( ) {
        return _azimuthCount;
    }
    public void setAzimuthCount( int value ) {
        if( !Comparer.equalsInt32( _azimuthCount, value ) ) {
            _azimuthCount = value;
            onPropertyChanged( );
        }
    }

    public int getTriggerCount( ) {
        return _triggerCount;
    }
    public void setTriggerCount( int value ) {
        if( !Comparer.equalsInt32( _triggerCount, value ) ) {
            _triggerCount = value;
            onPropertyChanged( );
        }
    }

    public TimeSpan getRotationTime( ) {
        return _rotationTime;
    }
    public void setRotationTime( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _rotationTime, value ) ) {
            _rotationTime = value;
            onPropertyChanged( );
        }
    }

    public int getPulse( ) {
        return _pulse;
    }
    public void setPulse( int value ) {
        if( !Comparer.equalsInt32( _pulse, value ) ) {
            _pulse = value;
            onPropertyChanged( );
        }
    }

    public boolean getTx( ) {
        return _tx;
    }
    public void setTx( boolean value ) {
        if( !Comparer.equalsBoolean( _tx, value ) ) {
            _tx = value;
            onPropertyChanged( );
        }
    }

    public boolean getTracking( ) {
        return _tracking;
    }
    public void setTracking( boolean value ) {
        if( !Comparer.equalsBoolean( _tracking, value ) ) {
            _tracking = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _radar );
        destination.writeDateTime( _timestamp );
        destination.writeInt32( _azimuthCount );
        destination.writeInt32( _triggerCount );
        destination.writeTimeSpan( _rotationTime );
        destination.writeInt32( _pulse );
        destination.writeBoolean( _tx );
        destination.writeBoolean( _tracking );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _radar = source.readGuid( );
        _timestamp = source.readDateTime( );
        _azimuthCount = source.readInt32( );
        _triggerCount = source.readInt32( );
        _rotationTime = source.readTimeSpan( );
        _pulse = source.readInt32( );
        _tx = source.readBoolean( );
        _tracking = source.readBoolean( );
    }

}
