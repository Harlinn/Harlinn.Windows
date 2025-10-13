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
        if( _navigationalAidType != value ) {
            this._navigationalAidType = value;
            onPropertyChanged( );
        }
    }

    public String getName( ) {
        return _name;
    }
    public void setName( String value ) {
        if( _name != value ) {
            this._name = value;
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

    public int getDimensionToBow( ) {
        return _dimensionToBow;
    }
    public void setDimensionToBow( int value ) {
        if( _dimensionToBow != value ) {
            this._dimensionToBow = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToStern( ) {
        return _dimensionToStern;
    }
    public void setDimensionToStern( int value ) {
        if( _dimensionToStern != value ) {
            this._dimensionToStern = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToPort( ) {
        return _dimensionToPort;
    }
    public void setDimensionToPort( int value ) {
        if( _dimensionToPort != value ) {
            this._dimensionToPort = value;
            onPropertyChanged( );
        }
    }

    public int getDimensionToStarboard( ) {
        return _dimensionToStarboard;
    }
    public void setDimensionToStarboard( int value ) {
        if( _dimensionToStarboard != value ) {
            this._dimensionToStarboard = value;
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

    public int getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( int value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public boolean getOffPosition( ) {
        return _offPosition;
    }
    public void setOffPosition( boolean value ) {
        if( _offPosition != value ) {
            this._offPosition = value;
            onPropertyChanged( );
        }
    }

    public int getRegionalReserved( ) {
        return _regionalReserved;
    }
    public void setRegionalReserved( int value ) {
        if( _regionalReserved != value ) {
            this._regionalReserved = value;
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

    public boolean getVirtualAid( ) {
        return _virtualAid;
    }
    public void setVirtualAid( boolean value ) {
        if( _virtualAid != value ) {
            this._virtualAid = value;
            onPropertyChanged( );
        }
    }

    public boolean getAssigned( ) {
        return _assigned;
    }
    public void setAssigned( boolean value ) {
        if( _assigned != value ) {
            this._assigned = value;
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

    public String getNameExtension( ) {
        return _nameExtension;
    }
    public void setNameExtension( String value ) {
        if( _nameExtension != value ) {
            this._nameExtension = value;
            onPropertyChanged( );
        }
    }


}
