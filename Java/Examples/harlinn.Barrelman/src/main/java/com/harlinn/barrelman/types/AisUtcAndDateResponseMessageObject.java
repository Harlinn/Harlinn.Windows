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

public class AisUtcAndDateResponseMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisUtcAndDateResponseMessage;

    private DateTime _datetime;
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private int _positionFixType = PositionFixType.Undefined1;
    private int _spare = 0;
    private int _raim = Raim.NotInUse;
    private int _radioStatus = 0;

    public AisUtcAndDateResponseMessageObject( ) {
    }
    public AisUtcAndDateResponseMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, DateTime datetime, int positionAccuracy, double longitude, double latitude, int positionFixType, int spare, int raim, int radioStatus ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._datetime = datetime;
        this._positionAccuracy = positionAccuracy;
        this._longitude = longitude;
        this._latitude = latitude;
        this._positionFixType = positionFixType;
        this._spare = spare;
        this._raim = raim;
        this._radioStatus = radioStatus;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisUtcAndDateResponseMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisUtcAndDateResponseMessageObject( );
    }

    public DateTime getDatetime( ) {
        return _datetime;
    }
    public void setDatetime( DateTime value ) {
        if( !Comparer.equalsDateTime( _datetime, value ) ) {
            _datetime = value;
            onPropertyChanged( );
        }
    }

    public int getPositionAccuracy( ) {
        return _positionAccuracy;
    }
    public void setPositionAccuracy( int value ) {
        if( !Comparer.equalsInt32( _positionAccuracy, value ) ) {
            _positionAccuracy = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public int getPositionFixType( ) {
        return _positionFixType;
    }
    public void setPositionFixType( int value ) {
        if( !Comparer.equalsInt32( _positionFixType, value ) ) {
            _positionFixType = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( !Comparer.equalsInt32( _spare, value ) ) {
            _spare = value;
            onPropertyChanged( );
        }
    }

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( !Comparer.equalsInt32( _raim, value ) ) {
            _raim = value;
            onPropertyChanged( );
        }
    }

    public int getRadioStatus( ) {
        return _radioStatus;
    }
    public void setRadioStatus( int value ) {
        if( !Comparer.equalsInt32( _radioStatus, value ) ) {
            _radioStatus = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisUtcAndDateResponseMessageObject )target;
        targetObject._datetime = this._datetime;
        targetObject._positionAccuracy = this._positionAccuracy;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._positionFixType = this._positionFixType;
        targetObject._spare = this._spare;
        targetObject._raim = this._raim;
        targetObject._radioStatus = this._radioStatus;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisUtcAndDateResponseMessageObject)obj;
        if( !Comparer.equalsDateTime( this._datetime, other._datetime ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionAccuracy, other._positionAccuracy ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionFixType, other._positionFixType ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._raim, other._raim ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._radioStatus, other._radioStatus ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeDateTime( _datetime );
        destination.writeInt32( _positionAccuracy );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeInt32( _positionFixType );
        destination.writeInt32( _spare );
        destination.writeInt32( _raim );
        destination.writeInt32( _radioStatus );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _datetime = source.readDateTime( );
        _positionAccuracy = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _positionFixType = source.readInt32( );
        _spare = source.readInt32( );
        _raim = source.readInt32( );
        _radioStatus = source.readInt32( );
    }

}
