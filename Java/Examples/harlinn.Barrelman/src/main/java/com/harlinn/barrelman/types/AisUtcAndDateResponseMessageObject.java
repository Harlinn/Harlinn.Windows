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
        if( _datetime != value ) {
            this._datetime = value;
            onPropertyChanged( );
        }
    }

    public int getPositionAccuracy( ) {
        return _positionAccuracy;
    }
    public void setPositionAccuracy( int value ) {
        if( _positionAccuracy != value ) {
            this._positionAccuracy = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( _longitude != value ) {
            this._longitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( _latitude != value ) {
            this._latitude = value;
            onPropertyChanged( );
        }
    }

    public int getPositionFixType( ) {
        return _positionFixType;
    }
    public void setPositionFixType( int value ) {
        if( _positionFixType != value ) {
            this._positionFixType = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( _spare != value ) {
            this._spare = value;
            onPropertyChanged( );
        }
    }

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( _raim != value ) {
            this._raim = value;
            onPropertyChanged( );
        }
    }

    public int getRadioStatus( ) {
        return _radioStatus;
    }
    public void setRadioStatus( int value ) {
        if( _radioStatus != value ) {
            this._radioStatus = value;
            onPropertyChanged( );
        }
    }


}
