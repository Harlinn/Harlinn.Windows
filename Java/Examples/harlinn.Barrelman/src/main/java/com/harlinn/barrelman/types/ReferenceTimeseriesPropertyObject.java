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

public class ReferenceTimeseriesPropertyObject extends TimeseriesPropertyObject {

    public final int KIND = Kind.ReferenceTimeseriesProperty;

    private Guid _timeseries;

    public ReferenceTimeseriesPropertyObject( ) {
    }
    public ReferenceTimeseriesPropertyObject( byte objectState, Guid id, long rowVersion, Guid element, Guid definition, Guid timeseries ) {
        super( objectState, id, rowVersion, element, definition );
        this._timeseries = timeseries;
    }

    @Override
    public int getObjectType( ) {
        return Kind.ReferenceTimeseriesProperty;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferenceTimeseriesPropertyObject( );
    }

    public Guid getTimeseries( ) {
        return _timeseries;
    }
    public void setTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _timeseries, value ) ) {
            _timeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( ReferenceTimeseriesPropertyObject )target;
        targetObject._timeseries = this._timeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (ReferenceTimeseriesPropertyObject)obj;
        if( !Comparer.equalsNullableGuid( this._timeseries, other._timeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _timeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _timeseries = source.readNullableGuid( );
    }

}
