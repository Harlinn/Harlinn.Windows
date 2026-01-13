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

public abstract class TimeseriesObject extends TimeseriesCatalogElementObject {

    public final int KIND = Kind.Timeseries;

    private TimeSpan _maxRetention;

    public TimeseriesObject( ) {
    }
    public TimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention ) {
        super( objectState, id, rowVersion, catalog, name );
        this._maxRetention = maxRetention;
    }


    public TimeSpan getMaxRetention( ) {
        return _maxRetention;
    }
    public void setMaxRetention( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxRetention, value ) ) {
            _maxRetention = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( TimeseriesObject )target;
        targetObject._maxRetention = this._maxRetention;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (TimeseriesObject)obj;
        if( !Comparer.equalsTimeSpan( this._maxRetention, other._maxRetention ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _maxRetention );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _maxRetention = source.readTimeSpan( );
    }

}
