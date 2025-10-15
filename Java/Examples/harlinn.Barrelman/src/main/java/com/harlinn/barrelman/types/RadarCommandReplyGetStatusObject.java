package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarCommandReplyGetStatusObject extends RadarCommandReplyObject {

    private int _azimuthCount = 0;
    private int _triggerCount = 0;
    private TimeSpan _rotationCount;
    private int _pulse = RadarPulse.Short;
    private boolean _tx = false;

    @Override
    public int getObjectType( ) {
        return Kind.RadarCommandReplyGetStatus;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new RadarCommandReplyGetStatusObject( );
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

    public TimeSpan getRotationCount( ) {
        return _rotationCount;
    }
    public void setRotationCount( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _rotationCount, value ) ) {
            _rotationCount = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadarCommandReplyGetStatusObject )target;
        targetObject._azimuthCount = this._azimuthCount;
        targetObject._triggerCount = this._triggerCount;
        targetObject._rotationCount = this._rotationCount;
        targetObject._pulse = this._pulse;
        targetObject._tx = this._tx;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadarCommandReplyGetStatusObject)obj;
        if( !Comparer.equalsInt32( this._azimuthCount, other._azimuthCount ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._triggerCount, other._triggerCount ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._rotationCount, other._rotationCount ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._pulse, other._pulse ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._tx, other._tx ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _azimuthCount );
        destination.writeInt32( _triggerCount );
        destination.writeTimeSpan( _rotationCount );
        destination.writeInt32( _pulse );
        destination.writeBoolean( _tx );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _azimuthCount = source.readInt32( );
        _triggerCount = source.readInt32( );
        _rotationCount = source.readTimeSpan( );
        _pulse = source.readInt32( );
        _tx = source.readBoolean( );
    }

}
