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

public class BooleanTimeseriesValueObject extends AbstractDataObjectWithGuidKey {

    public final int KIND = Kind.BooleanTimeseriesValue;

    private long _rowVersion = 0;
    private Guid _timeseries;
    private DateTime _timestamp;
    private Boolean _value;

    public BooleanTimeseriesValueObject( ) {
    }
    public BooleanTimeseriesValueObject( byte objectState, Guid id, long rowVersion, Guid timeseries, DateTime timestamp, Boolean value ) {
        super( objectState, id );
        this._rowVersion = rowVersion;
        this._timeseries = timeseries;
        this._timestamp = timestamp;
        this._value = value;
    }

    @Override
    public int getObjectType( ) {
        return Kind.BooleanTimeseriesValue;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new BooleanTimeseriesValueObject( );
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

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( !Comparer.equalsGuid( _timeseries, value ) ) {
            _timeseries = value;
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

    public Boolean getValue( ) {
        return _value;
    }
    public void setValue( Boolean value ) {
        if( !Comparer.equalsNullableBoolean( _value, value ) ) {
            _value = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( BooleanTimeseriesValueObject )target;
        targetObject._rowVersion = this._rowVersion;
        targetObject._timeseries = this._timeseries;
        targetObject._timestamp = this._timestamp;
        targetObject._value = this._value;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (BooleanTimeseriesValueObject)obj;
        if( !Comparer.equalsInt64( this._rowVersion, other._rowVersion ) ) {
            return false;
        }
        if( !Comparer.equalsGuid( this._timeseries, other._timeseries ) ) {
            return false;
        }
        if( !Comparer.equalsDateTime( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsNullableBoolean( this._value, other._value ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt64( _rowVersion );
        destination.writeGuid( _timeseries );
        destination.writeDateTime( _timestamp );
        destination.writeNullableBoolean( _value );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _rowVersion = source.readInt64( );
        _timeseries = source.readGuid( );
        _timestamp = source.readDateTime( );
        _value = source.readNullableBoolean( );
    }

}
