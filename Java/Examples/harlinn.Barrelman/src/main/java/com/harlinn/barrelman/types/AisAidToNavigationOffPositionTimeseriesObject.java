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

public class AisAidToNavigationOffPositionTimeseriesObject extends BooleanTimeseriesObject {

    public final int KIND = Kind.AisAidToNavigationOffPositionTimeseries;

    private Guid _aidToNavigation;

    public AisAidToNavigationOffPositionTimeseriesObject( ) {
    }
    public AisAidToNavigationOffPositionTimeseriesObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name, TimeSpan maxRetention, Guid aidToNavigation ) {
        super( objectState, id, rowVersion, catalog, name, maxRetention );
        this._aidToNavigation = aidToNavigation;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisAidToNavigationOffPositionTimeseries;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAidToNavigationOffPositionTimeseriesObject( );
    }

    public Guid getAidToNavigation( ) {
        return _aidToNavigation;
    }
    public void setAidToNavigation( Guid value ) {
        if( !Comparer.equalsNullableGuid( _aidToNavigation, value ) ) {
            _aidToNavigation = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisAidToNavigationOffPositionTimeseriesObject )target;
        targetObject._aidToNavigation = this._aidToNavigation;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisAidToNavigationOffPositionTimeseriesObject)obj;
        if( !Comparer.equalsNullableGuid( this._aidToNavigation, other._aidToNavigation ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeNullableGuid( _aidToNavigation );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _aidToNavigation = source.readNullableGuid( );
    }

}
