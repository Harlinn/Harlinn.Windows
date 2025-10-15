package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticDataReportPartBMessageObject extends AisStaticDataReportMessageObject {

    private int _shipType = ShipType.NotAvailable;
    private String _vendorId = "";
    private int _unitModelCode = 0;
    private int _serialNumber = 0;
    private Guid _callsign;
    private int _dimensionToBow = 0;
    private int _dimensionToStern = 0;
    private int _dimensionToPort = 0;
    private int _dimensionToStarboard = 0;
    private Guid _mothershipMmsi;
    private int _positionFixType = PositionFixType.Undefined1;
    private int _spare = 0;

    @Override
    public int getObjectType( ) {
        return Kind.AisStaticDataReportPartBMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStaticDataReportPartBMessageObject( );
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

    public String getVendorId( ) {
        return _vendorId;
    }
    public void setVendorId( String value ) {
        if( !Comparer.equalsString( _vendorId, value ) ) {
            _vendorId = value;
            onPropertyChanged( );
        }
    }

    public int getUnitModelCode( ) {
        return _unitModelCode;
    }
    public void setUnitModelCode( int value ) {
        if( !Comparer.equalsInt32( _unitModelCode, value ) ) {
            _unitModelCode = value;
            onPropertyChanged( );
        }
    }

    public int getSerialNumber( ) {
        return _serialNumber;
    }
    public void setSerialNumber( int value ) {
        if( !Comparer.equalsInt32( _serialNumber, value ) ) {
            _serialNumber = value;
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

    public Guid getMothershipMmsi( ) {
        return _mothershipMmsi;
    }
    public void setMothershipMmsi( Guid value ) {
        if( !Comparer.equalsNullableGuid( _mothershipMmsi, value ) ) {
            _mothershipMmsi = value;
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



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisStaticDataReportPartBMessageObject )target;
        targetObject._shipType = this._shipType;
        targetObject._vendorId = this._vendorId;
        targetObject._unitModelCode = this._unitModelCode;
        targetObject._serialNumber = this._serialNumber;
        targetObject._callsign = this._callsign;
        targetObject._dimensionToBow = this._dimensionToBow;
        targetObject._dimensionToStern = this._dimensionToStern;
        targetObject._dimensionToPort = this._dimensionToPort;
        targetObject._dimensionToStarboard = this._dimensionToStarboard;
        targetObject._mothershipMmsi = this._mothershipMmsi;
        targetObject._positionFixType = this._positionFixType;
        targetObject._spare = this._spare;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisStaticDataReportPartBMessageObject)obj;
        if( !Comparer.equalsInt32( this._shipType, other._shipType ) ) {
            return false;
        }
        if( !Comparer.equalsString( this._vendorId, other._vendorId ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._unitModelCode, other._unitModelCode ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._serialNumber, other._serialNumber ) ) {
            return false;
        }
        if( !Comparer.equalsNullableGuid( this._callsign, other._callsign ) ) {
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
        if( !Comparer.equalsNullableGuid( this._mothershipMmsi, other._mothershipMmsi ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._positionFixType, other._positionFixType ) ) {
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
        destination.writeInt32( _shipType );
        destination.writeStringUtf8( _vendorId );
        destination.writeInt32( _unitModelCode );
        destination.writeInt32( _serialNumber );
        destination.writeNullableGuid( _callsign );
        destination.writeInt32( _dimensionToBow );
        destination.writeInt32( _dimensionToStern );
        destination.writeInt32( _dimensionToPort );
        destination.writeInt32( _dimensionToStarboard );
        destination.writeNullableGuid( _mothershipMmsi );
        destination.writeInt32( _positionFixType );
        destination.writeInt32( _spare );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _shipType = source.readInt32( );
        _vendorId = source.readString( );
        _unitModelCode = source.readInt32( );
        _serialNumber = source.readInt32( );
        _callsign = source.readNullableGuid( );
        _dimensionToBow = source.readInt32( );
        _dimensionToStern = source.readInt32( );
        _dimensionToPort = source.readInt32( );
        _dimensionToStarboard = source.readInt32( );
        _mothershipMmsi = source.readNullableGuid( );
        _positionFixType = source.readInt32( );
        _spare = source.readInt32( );
    }

}
