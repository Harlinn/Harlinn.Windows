package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AidToNavigationReportMessageObject extends AisMessageObject {

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
