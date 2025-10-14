package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisUtcAndDateResponseMessageObject extends AisMessageObject {

    private DateTime _datetime;
    private int _positionAccuracy = PositionAccuracy.Low;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private int _positionFixType = PositionFixType.Undefined1;
    private int _spare = 0;
    private int _raim = Raim.NotInUse;
    private int _radioStatus = 0;

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
