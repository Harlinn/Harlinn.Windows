/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class RadarStatusObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.RadarStatus;

    private long _rowVersion = 0;
    private Guid _radar;
    private DateTime _timestamp;
    private int _azimuthCount = 0;
    private int _triggerCount = 0;
    private TimeSpan _rotationTime;
    private int _pulse = RadarPulse.Short;
    private boolean _tx = false;
    private boolean _tracking = false;

    public RadarStatusObject( ) {
    }
    public RadarStatusObject( byte objectState, Guid id, long rowVersion, Guid radar, DateTime timestamp, int azimuthCount, int triggerCount, TimeSpan rotationTime, int pulse, boolean tx, boolean tracking ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._radar = radar;
        this._timestamp = timestamp;
        this._azimuthCount = azimuthCount;
        this._triggerCount = triggerCount;
        this._rotationTime = rotationTime;
        this._pulse = pulse;
        this._tx = tx;
        this._tracking = tracking;
    }

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
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( RadarStatusObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._radar = this._radar;
        targetObject._timestamp = this._timestamp;
        targetObject._azimuthCount = this._azimuthCount;
        targetObject._triggerCount = this._triggerCount;
        targetObject._rotationTime = this._rotationTime;
        targetObject._pulse = this._pulse;
        targetObject._tx = this._tx;
        targetObject._tracking = this._tracking;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (RadarStatusObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._radar, other._radar ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._azimuthCount, other._azimuthCount ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._triggerCount, other._triggerCount ) ) {
            return false;
        }
        if( !Comparer.equalsTimeSpan( this._rotationTime, other._rotationTime ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._pulse, other._pulse ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._tx, other._tx ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._tracking, other._tracking ) ) {
            return false;
        }
        return true;
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
