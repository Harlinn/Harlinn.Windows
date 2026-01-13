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

public class AisAidToNavigationObject extends TrackableItemObject {

    public final int KIND = Kind.AisAidToNavigation;

    private String _name = "";
    private Guid _mMSI;
    private int _navigationalAidType = NavigationalAidType.NotSpecified;
    private Guid _position;
    private boolean _isVirtual = false;
    private int _toBow = 0;
    private int _toStern = 0;
    private int _toPort = 0;
    private int _toStarboard = 0;
    private Guid _offPositionTimeseries;

    public AisAidToNavigationObject( ) {
    }
    public AisAidToNavigationObject( byte objectState, Guid id, long rowVersion, String name, Guid mMSI, int navigationalAidType, Guid position, boolean isVirtual, int toBow, int toStern, int toPort, int toStarboard, Guid offPositionTimeseries ) {
        super( objectState, id, rowVersion );
        this._name = name;
        this._mMSI = mMSI;
        this._navigationalAidType = navigationalAidType;
        this._position = position;
        this._isVirtual = isVirtual;
        this._toBow = toBow;
        this._toStern = toStern;
        this._toPort = toPort;
        this._toStarboard = toStarboard;
        this._offPositionTimeseries = offPositionTimeseries;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisAidToNavigation;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAidToNavigationObject( );
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
            onPropertyChanged( );
        }
    }

    public Guid getMMSI( ) {
        return _mMSI;
    }
    public void setMMSI( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mMSI, value ) ) {
            _mMSI = value;
            onPropertyChanged( );
        }
    }

    public int getNavigationalAidType( ) {
        return _navigationalAidType;
    }
    public void setNavigationalAidType( int value ) {
        if( !Comparer.equalsInt32( _navigationalAidType, value ) ) {
            _navigationalAidType = value;
            onPropertyChanged( );
        }
    }

    public Guid getPosition( ) {
        return _position;
    }
    public void setPosition( Guid value ) {
        if( !Comparer.equalsNullableGuid( _position, value ) ) {
            _position = value;
            onPropertyChanged( );
        }
    }

    public boolean getIsVirtual( ) {
        return _isVirtual;
    }
    public void setIsVirtual( boolean value ) {
        if( !Comparer.equalsBoolean( _isVirtual, value ) ) {
            _isVirtual = value;
            onPropertyChanged( );
        }
    }

    public int getToBow( ) {
        return _toBow;
    }
    public void setToBow( int value ) {
        if( !Comparer.equalsInt32( _toBow, value ) ) {
            _toBow = value;
            onPropertyChanged( );
        }
    }

    public int getToStern( ) {
        return _toStern;
    }
    public void setToStern( int value ) {
        if( !Comparer.equalsInt32( _toStern, value ) ) {
            _toStern = value;
            onPropertyChanged( );
        }
    }

    public int getToPort( ) {
        return _toPort;
    }
    public void setToPort( int value ) {
        if( !Comparer.equalsInt32( _toPort, value ) ) {
            _toPort = value;
            onPropertyChanged( );
        }
    }

    public int getToStarboard( ) {
        return _toStarboard;
    }
    public void setToStarboard( int value ) {
        if( !Comparer.equalsInt32( _toStarboard, value ) ) {
            _toStarboard = value;
            onPropertyChanged( );
        }
    }

    public Guid getOffPositionTimeseries( ) {
        return _offPositionTimeseries;
    }
    public void setOffPositionTimeseries( Guid value ) {
        if( !Comparer.equalsNullableGuid( _offPositionTimeseries, value ) ) {
            _offPositionTimeseries = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisAidToNavigationObject )target;
        targetObject._name = this._name;
        targetObject._mMSI = this._mMSI;
        targetObject._navigationalAidType = this._navigationalAidType;
        targetObject._position = this._position;
        targetObject._isVirtual = this._isVirtual;
        targetObject._toBow = this._toBow;
        targetObject._toStern = this._toStern;
        targetObject._toPort = this._toPort;
        targetObject._toStarboard = this._toStarboard;
        targetObject._offPositionTimeseries = this._offPositionTimeseries;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisAidToNavigationObject)obj;
        if( !Comparer.equalsString( this._name, other._name ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._mMSI, other._mMSI ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._navigationalAidType, other._navigationalAidType ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._position, other._position ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._isVirtual, other._isVirtual ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toBow, other._toBow ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toStern, other._toStern ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toPort, other._toPort ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._toStarboard, other._toStarboard ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._offPositionTimeseries, other._offPositionTimeseries ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeStringUtf8( _name );
        destination.writeNullableGuid( _mMSI );
        destination.writeInt32( _navigationalAidType );
        destination.writeNullableGuid( _position );
        destination.writeBoolean( _isVirtual );
        destination.writeInt32( _toBow );
        destination.writeInt32( _toStern );
        destination.writeInt32( _toPort );
        destination.writeInt32( _toStarboard );
        destination.writeNullableGuid( _offPositionTimeseries );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _name = source.readString( );
        _mMSI = source.readNullableGuid( );
        _navigationalAidType = source.readInt32( );
        _position = source.readNullableGuid( );
        _isVirtual = source.readBoolean( );
        _toBow = source.readInt32( );
        _toStern = source.readInt32( );
        _toPort = source.readInt32( );
        _toStarboard = source.readInt32( );
        _offPositionTimeseries = source.readNullableGuid( );
    }

}
