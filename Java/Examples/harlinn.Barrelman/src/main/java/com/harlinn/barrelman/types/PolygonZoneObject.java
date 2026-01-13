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

public class PolygonZoneObject extends ZoneObject {

    public final int KIND = Kind.PolygonZone;

    private byte[] _polygon = new byte[0];

    public PolygonZoneObject( ) {
    }
    public PolygonZoneObject( byte objectState, Guid id, long rowVersion, String name, double longitude, double latitude, int alarmType, TimeSpan alarmTime, TimeSpan radarTrackMinimumLifetime, double speed, int strokeColor, int fillColor, byte[] polygon ) {
        super( objectState, id, rowVersion, name, longitude, latitude, alarmType, alarmTime, radarTrackMinimumLifetime, speed, strokeColor, fillColor );
        this._polygon = polygon;
    }

    @Override
    public int getObjectType( ) {
        return Kind.PolygonZone;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new PolygonZoneObject( );
    }

    public byte[] getPolygon( ) {
        return _polygon;
    }
    public void setPolygon( byte[] value ) {
        if( !Comparer.equalsUInt8Array( _polygon, value ) ) {
            _polygon = value != null ? value.clone() : value;;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( PolygonZoneObject )target;
        targetObject._polygon = this._polygon != null ? this._polygon.clone() : this._polygon;;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (PolygonZoneObject)obj;
        if( !Comparer.equalsUInt8Array( this._polygon, other._polygon ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeUInt8Array( _polygon );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _polygon = source.readUInt8Array( );
    }

}
