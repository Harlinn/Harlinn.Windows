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

public class AidToNavigationReportMessageObject extends AisMessageObject {

    public final int KIND = Kind.AidToNavigationReportMessage;

    private int _navigationalAidType = NavigationalAidType.NotSpecified;
    private String _name = "";
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private int _dimensionToBow = 0;
    private int _dimensionToStern = 0;
    private int _dimensionToPort = 0;
    private int _dimensionToStarboard = 0;
    private int _positionFixType = PositionFixType.Undefined1;
    private int _timestamp = 0;
    private boolean _offPosition = false;
    private int _regionalReserved = 0;
    private int _raim = Raim.NotInUse;
    private boolean _virtualAid = false;
    private boolean _assigned = false;
    private int _spare = 0;
    private String _nameExtension = "";

    public AidToNavigationReportMessageObject( ) {
    }
    public AidToNavigationReportMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int navigationalAidType, String name, int positionAccuracy, double longitude, double latitude, int dimensionToBow, int dimensionToStern, int dimensionToPort, int dimensionToStarboard, int positionFixType, int timestamp, boolean offPosition, int regionalReserved, int raim, boolean virtualAid, boolean assigned, int spare, String nameExtension ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._navigationalAidType = navigationalAidType;
        this._name = name;
        this._positionAccuracy = positionAccuracy;
        this._longitude = longitude;
        this._latitude = latitude;
        this._dimensionToBow = dimensionToBow;
        this._dimensionToStern = dimensionToStern;
        this._dimensionToPort = dimensionToPort;
        this._dimensionToStarboard = dimensionToStarboard;
        this._positionFixType = positionFixType;
        this._timestamp = timestamp;
        this._offPosition = offPosition;
        this._regionalReserved = regionalReserved;
        this._raim = raim;
        this._virtualAid = virtualAid;
        this._assigned = assigned;
        this._spare = spare;
        this._nameExtension = nameExtension;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AidToNavigationReportMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AidToNavigationReportMessageObject( );
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

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( !Comparer.equalsString( _name, value ) ) {
            _name = value;
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

    public int getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( int value ) {
        if( !Comparer.equalsInt32( _timestamp, value ) ) {
            _timestamp = value;
            onPropertyChanged( );
        }
    }

    public boolean getOffPosition( ) {
        return _offPosition;
    }
    public void setOffPosition( boolean value ) {
        if( !Comparer.equalsBoolean( _offPosition, value ) ) {
            _offPosition = value;
            onPropertyChanged( );
        }
    }

    public int getRegionalReserved( ) {
        return _regionalReserved;
    }
    public void setRegionalReserved( int value ) {
        if( !Comparer.equalsInt32( _regionalReserved, value ) ) {
            _regionalReserved = value;
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

    public boolean getVirtualAid( ) {
        return _virtualAid;
    }
    public void setVirtualAid( boolean value ) {
        if( !Comparer.equalsBoolean( _virtualAid, value ) ) {
            _virtualAid = value;
            onPropertyChanged( );
        }
    }

    public boolean getAssigned( ) {
        return _assigned;
    }
    public void setAssigned( boolean value ) {
        if( !Comparer.equalsBoolean( _assigned, value ) ) {
            _assigned = value;
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

    public String getNameExtension( ) {
        return _nameExtension;
    }
    public void setNameExtension( String value ) {
        if( !Comparer.equalsString( _nameExtension, value ) ) {
            _nameExtension = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AidToNavigationReportMessageObject )target;
        targetObject._navigationalAidType = this._navigationalAidType;
        targetObject._name = this._name;
        targetObject._positionAccuracy = this._positionAccuracy;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._dimensionToBow = this._dimensionToBow;
        targetObject._dimensionToStern = this._dimensionToStern;
        targetObject._dimensionToPort = this._dimensionToPort;
        targetObject._dimensionToStarboard = this._dimensionToStarboard;
        targetObject._positionFixType = this._positionFixType;
        targetObject._timestamp = this._timestamp;
        targetObject._offPosition = this._offPosition;
        targetObject._regionalReserved = this._regionalReserved;
        targetObject._raim = this._raim;
        targetObject._virtualAid = this._virtualAid;
        targetObject._assigned = this._assigned;
        targetObject._spare = this._spare;
        targetObject._nameExtension = this._nameExtension;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AidToNavigationReportMessageObject)obj;
        if( !Comparer.equalsInt32( this._navigationalAidType, other._navigationalAidType ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._name, other._name ) ) {
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
        if( !Comparer.equalsInt32( this._timestamp, other._timestamp ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._offPosition, other._offPosition ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._regionalReserved, other._regionalReserved ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._raim, other._raim ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._virtualAid, other._virtualAid ) ) {
            return false;
        }
        if( !Comparer.equalsBoolean( this._assigned, other._assigned ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._nameExtension, other._nameExtension ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _navigationalAidType );
        destination.writeStringUtf8( _name );
        destination.writeInt32( _positionAccuracy );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeInt32( _dimensionToBow );
        destination.writeInt32( _dimensionToStern );
        destination.writeInt32( _dimensionToPort );
        destination.writeInt32( _dimensionToStarboard );
        destination.writeInt32( _positionFixType );
        destination.writeInt32( _timestamp );
        destination.writeBoolean( _offPosition );
        destination.writeInt32( _regionalReserved );
        destination.writeInt32( _raim );
        destination.writeBoolean( _virtualAid );
        destination.writeBoolean( _assigned );
        destination.writeInt32( _spare );
        destination.writeStringUtf8( _nameExtension );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _navigationalAidType = source.readInt32( );
        _name = source.readString( );
        _positionAccuracy = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _dimensionToBow = source.readInt32( );
        _dimensionToStern = source.readInt32( );
        _dimensionToPort = source.readInt32( );
        _dimensionToStarboard = source.readInt32( );
        _positionFixType = source.readInt32( );
        _timestamp = source.readInt32( );
        _offPosition = source.readBoolean( );
        _regionalReserved = source.readInt32( );
        _raim = source.readInt32( );
        _virtualAid = source.readBoolean( );
        _assigned = source.readBoolean( );
        _spare = source.readInt32( );
        _nameExtension = source.readString( );
    }

}
