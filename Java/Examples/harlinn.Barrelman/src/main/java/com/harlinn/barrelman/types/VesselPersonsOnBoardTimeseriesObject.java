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

public class VesselPersonsOnBoardTimeseriesObject extends Int32TimeseriesObject {

    public final int KIND = Kind.VesselPersonsOnBoardTimeseries;

    private Guid _vessel;

    public VesselPersonsOnBoardTimeseriesObject( ) {
    }
    public VesselPersonsOnBoardTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid vessel ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._vessel = vessel;
    }

    @Override
    public int getObjectType( ) {
        return Kind.VesselPersonsOnBoardTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselPersonsOnBoardTimeseriesObject( );
    }

    public Guid getVessel( ) {
        return _vessel;
    }
    public void setVessel( Guid value ) {
        if( !Comparer.equalsNullableGuid( _vessel, value ) ) {
            _vessel = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( VesselPersonsOnBoardTimeseriesObject )target;
        targetObject._vessel = this._vessel;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (VesselPersonsOnBoardTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._vessel, other._vessel ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _vessel );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _vessel = source.readNullableGuid( );
    }

}
