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

public class GNSSAltitudeTimeseriesObject extends DoubleTimeseriesObject {

    public final int KIND = Kind.GNSSAltitudeTimeseries;

    private Guid _gNSSDevice;

    public GNSSAltitudeTimeseriesObject( ) {
    }
    public GNSSAltitudeTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid gNSSDevice ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._gNSSDevice = gNSSDevice;
    }

    @Override
    public int getObjectType( ) {
        return Kind.GNSSAltitudeTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new GNSSAltitudeTimeseriesObject( );
    }

    public Guid getGNSSDevice( ) {
        return _gNSSDevice;
    }
    public void setGNSSDevice( Guid value ) {
        if( !Comparer.equalsNullableGuid( _gNSSDevice, value ) ) {
            _gNSSDevice = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( GNSSAltitudeTimeseriesObject )target;
        targetObject._gNSSDevice = this._gNSSDevice;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (GNSSAltitudeTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._gNSSDevice, other._gNSSDevice ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _gNSSDevice );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _gNSSDevice = source.readNullableGuid( );
    }

}
