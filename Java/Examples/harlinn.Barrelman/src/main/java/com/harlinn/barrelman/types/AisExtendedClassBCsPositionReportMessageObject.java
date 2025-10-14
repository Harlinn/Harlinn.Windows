package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisExtendedClassBCsPositionReportMessageObject extends AisMessageObject {

    private int _reserved = 0;
    private double _speedOverGround = 0.0;
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _courseOverGround = 0.0;
    private Integer _trueHeading;
    private int _timestamp = 0;
    private int _regionalReserved = 0;
    private Guid _name;
    private int _shipType = ShipType.NotAvailable;
    private int _dimensionToBow = 0;
    private int _dimensionToStern = 0;
    private int _dimensionToPort = 0;
    private int _dimensionToStarboard = 0;
    private int _positionFixType = PositionFixType.Undefined1;
    private int _raim = Raim.NotInUse;
    private boolean _dataTerminalReady = false;
    private boolean _assigned = false;
    private int _spare = 0;

    @Override
    public int getObjectType( ) {
        return Kind.AisExtendedClassBCsPositionReportMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisExtendedClassBCsPositionReportMessageObject( );
    }

    public int getReserved( ) {
        return _reserved;
    }
    public void setReserved( int value ) {
        if( !Comparer.equalsInt32( _reserved, value ) ) {
            _reserved = value;
            onPropertyChanged( );
        }
    }

    public double getSpeedOverGround( ) {
        return _speedOverGround;
    }
    public void setSpeedOverGround( double value ) {
        if( !Comparer.equalsDouble( _speedOverGround, value ) ) {
            _speedOverGround = value;
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

    public double getCourseOverGround( ) {
        return _courseOverGround;
    }
    public void setCourseOverGround( double value ) {
        if( !Comparer.equalsDouble( _courseOverGround, value ) ) {
            _courseOverGround = value;
            onPropertyChanged( );
        }
    }

    public Integer getTrueHeading( ) {
        return _trueHeading;
    }
    public void setTrueHeading( Integer value ) {
        if( !Comparer.equalsNullableInt32( _trueHeading, value ) ) {
            _trueHeading = value;
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

    public int getRegionalReserved( ) {
        return _regionalReserved;
    }
    public void setRegionalReserved( int value ) {
        if( !Comparer.equalsInt32( _regionalReserved, value ) ) {
            _regionalReserved = value;
            onPropertyChanged( );
        }
    }

    public Guid getName( ) {
        return _name;
    }
    public void setName( Guid value ) {
        if( !Comparer.equalsNullableGuid( _name, value ) ) {
            _name = value;
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

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( !Comparer.equalsInt32( _raim, value ) ) {
            _raim = value;
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



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _reserved );
        destination.writeDouble( _speedOverGround );
        destination.writeInt32( _positionAccuracy );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _courseOverGround );
        destination.writeNullableInt32( _trueHeading );
        destination.writeInt32( _timestamp );
        destination.writeInt32( _regionalReserved );
        destination.writeNullableGuid( _name );
        destination.writeInt32( _shipType );
        destination.writeInt32( _dimensionToBow );
        destination.writeInt32( _dimensionToStern );
        destination.writeInt32( _dimensionToPort );
        destination.writeInt32( _dimensionToStarboard );
        destination.writeInt32( _positionFixType );
        destination.writeInt32( _raim );
        destination.writeBoolean( _dataTerminalReady );
        destination.writeBoolean( _assigned );
        destination.writeInt32( _spare );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _reserved = source.readInt32( );
        _speedOverGround = source.readDouble( );
        _positionAccuracy = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _courseOverGround = source.readDouble( );
        _trueHeading = source.readNullableInt32( );
        _timestamp = source.readInt32( );
        _regionalReserved = source.readInt32( );
        _name = source.readNullableGuid( );
        _shipType = source.readInt32( );
        _dimensionToBow = source.readInt32( );
        _dimensionToStern = source.readInt32( );
        _dimensionToPort = source.readInt32( );
        _dimensionToStarboard = source.readInt32( );
        _positionFixType = source.readInt32( );
        _raim = source.readInt32( );
        _dataTerminalReady = source.readBoolean( );
        _assigned = source.readBoolean( );
        _spare = source.readInt32( );
    }

}
