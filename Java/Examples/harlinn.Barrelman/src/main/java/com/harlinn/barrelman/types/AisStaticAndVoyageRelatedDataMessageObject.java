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

public class AisStaticAndVoyageRelatedDataMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisStaticAndVoyageRelatedDataMessage;

    private int _aisVersion = 0;
    private Guid _imoNumber;
    private Guid _callsign;
    private Guid _shipName;
    private int _shipType = ShipType.NotAvailable;
    private int _dimensionToBow = 0;
    private int _dimensionToStern = 0;
    private int _dimensionToPort = 0;
    private int _dimensionToStarboard = 0;
    private int _positionFixType = PositionFixType.Undefined1;
    private DateTime _estimatedTimeOfArrival;
    private double _draught = 0.0;
    private String _destination = "";
    private boolean _dataTerminalReady = false;
    private int _spare = 0;

    public AisStaticAndVoyageRelatedDataMessageObject( ) {
    }
    public AisStaticAndVoyageRelatedDataMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int aisVersion, Guid imoNumber, Guid callsign, Guid shipName, int shipType, int dimensionToBow, int dimensionToStern, int dimensionToPort, int dimensionToStarboard, int positionFixType, DateTime estimatedTimeOfArrival, double draught, String destination, boolean dataTerminalReady, int spare ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._aisVersion = aisVersion;
        this._imoNumber = imoNumber;
        this._callsign = callsign;
        this._shipName = shipName;
        this._shipType = shipType;
        this._dimensionToBow = dimensionToBow;
        this._dimensionToStern = dimensionToStern;
        this._dimensionToPort = dimensionToPort;
        this._dimensionToStarboard = dimensionToStarboard;
        this._positionFixType = positionFixType;
        this._estimatedTimeOfArrival = estimatedTimeOfArrival;
        this._draught = draught;
        this._destination = destination;
        this._dataTerminalReady = dataTerminalReady;
        this._spare = spare;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisStaticAndVoyageRelatedDataMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStaticAndVoyageRelatedDataMessageObject( );
    }

    public int getAisVersion( ) {
        return _aisVersion;
    }
    public void setAisVersion( int value ) {
        if( !Comparer.equalsInt32( _aisVersion, value ) ) {
            _aisVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getImoNumber( ) {
        return _imoNumber;
    }
    public void setImoNumber( Guid value ) {
        if( !Comparer.equalsNullableGuid( _imoNumber, value ) ) {
            _imoNumber = value;
            onPropertyChanged( );
        }
    }

    public Guid getCallsign( ) {
        return _callsign;
    }
    public void setCallsign( Guid value ) {
        if( !Comparer.equalsNullableGuid( _callsign, value ) ) {
            _callsign = value;
            onPropertyChanged( );
        }
    }

    public Guid getShipName( ) {
        return _shipName;
    }
    public void setShipName( Guid value ) {
        if( !Comparer.equalsNullableGuid( _shipName, value ) ) {
            _shipName = value;
            onPropertyChanged( );
        }
    }

    public int getShipType( ) {
        return _shipType;
    }
    public void setShipType( int value ) {
        if( !Comparer.equalsInt32( _shipType, value ) ) {
            _shipType = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToBow( ) {
        return _dimensionToBow;
    }
    public void setDimensionToBow( int value ) {
        if( !Comparer.equalsInt32( _dimensionToBow, value ) ) {
            _dimensionToBow = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToStern( ) {
        return _dimensionToStern;
    }
    public void setDimensionToStern( int value ) {
        if( !Comparer.equalsInt32( _dimensionToStern, value ) ) {
            _dimensionToStern = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToPort( ) {
        return _dimensionToPort;
    }
    public void setDimensionToPort( int value ) {
        if( !Comparer.equalsInt32( _dimensionToPort, value ) ) {
            _dimensionToPort = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToStarboard( ) {
        return _dimensionToStarboard;
    }
    public void setDimensionToStarboard( int value ) {
        if( !Comparer.equalsInt32( _dimensionToStarboard, value ) ) {
            _dimensionToStarboard = value;
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

    public DateTime getEstimatedTimeOfArrival( ) {
        return _estimatedTimeOfArrival;
    }
    public void setEstimatedTimeOfArrival( DateTime value ) {
        if( !Comparer.equalsNullableDateTime( _estimatedTimeOfArrival, value ) ) {
            _estimatedTimeOfArrival = value;
            onPropertyChanged( );
        }
    }

    public double getDraught( ) {
        return _draught;
    }
    public void setDraught( double value ) {
        if( !Comparer.equalsDouble( _draught, value ) ) {
            _draught = value;
            onPropertyChanged( );
        }
    }

    public String getDestination( ) {
        return _destination;
    }
    public void setDestination( String value ) {
        if( !Comparer.equalsString( _destination, value ) ) {
            _destination = value;
            onPropertyChanged( );
        }
    }

    public boolean getDataTerminalReady( ) {
        return _dataTerminalReady;
    }
    public void setDataTerminalReady( boolean value ) {
        if( !Comparer.equalsBoolean( _dataTerminalReady, value ) ) {
            _dataTerminalReady = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisStaticAndVoyageRelatedDataMessageObject )target;
        targetObject._aisVersion = this._aisVersion;
        targetObject._imoNumber = this._imoNumber;
        targetObject._callsign = this._callsign;
        targetObject._shipName = this._shipName;
        targetObject._shipType = this._shipType;
        targetObject._dimensionToBow = this._dimensionToBow;
        targetObject._dimensionToStern = this._dimensionToStern;
        targetObject._dimensionToPort = this._dimensionToPort;
        targetObject._dimensionToStarboard = this._dimensionToStarboard;
        targetObject._positionFixType = this._positionFixType;
        targetObject._estimatedTimeOfArrival = this._estimatedTimeOfArrival;
        targetObject._draught = this._draught;
        targetObject._destination = this._destination;
        targetObject._dataTerminalReady = this._dataTerminalReady;
        targetObject._spare = this._spare;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisStaticAndVoyageRelatedDataMessageObject)obj;
        if( !Comparer.equalsInt32( this._aisVersion, other._aisVersion ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._imoNumber, other._imoNumber ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._callsign, other._callsign ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._shipName, other._shipName ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._shipType, other._shipType ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._dimensionToBow, other._dimensionToBow ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._dimensionToStern, other._dimensionToStern ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._dimensionToPort, other._dimensionToPort ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._dimensionToStarboard, other._dimensionToStarboard ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionFixType, other._positionFixType ) ) {
            return false;
        }
        if( !Comparer.equalsNullableDateTime( this._estimatedTimeOfArrival, other._estimatedTimeOfArrival ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._draught, other._draught ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._destination, other._destination ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._dataTerminalReady, other._dataTerminalReady ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _aisVersion );
        destination.writeNullableGuid( _imoNumber );
        destination.writeNullableGuid( _callsign );
        destination.writeNullableGuid( _shipName );
        destination.writeInt32( _shipType );
        destination.writeInt32( _dimensionToBow );
        destination.writeInt32( _dimensionToStern );
        destination.writeInt32( _dimensionToPort );
        destination.writeInt32( _dimensionToStarboard );
        destination.writeInt32( _positionFixType );
        destination.writeNullableDateTime( _estimatedTimeOfArrival );
        destination.writeDouble( _draught );
        destination.writeStringUtf8( _destination );
        destination.writeBoolean( _dataTerminalReady );
        destination.writeInt32( _spare );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _aisVersion = source.readInt32( );
        _imoNumber = source.readNullableGuid( );
        _callsign = source.readNullableGuid( );
        _shipName = source.readNullableGuid( );
        _shipType = source.readInt32( );
        _dimensionToBow = source.readInt32( );
        _dimensionToStern = source.readInt32( );
        _dimensionToPort = source.readInt32( );
        _dimensionToStarboard = source.readInt32( );
        _positionFixType = source.readInt32( );
        _estimatedTimeOfArrival = source.readNullableDateTime( );
        _draught = source.readDouble( );
        _destination = source.readString( );
        _dataTerminalReady = source.readBoolean( );
        _spare = source.readInt32( );
    }

}
