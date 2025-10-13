package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticAndVoyageRelatedDataMessageObject extends AisMessageObject {

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
        if( _aisVersion != value ) {
            this._aisVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getImoNumber( ) {
        return _imoNumber;
    }
    public void setImoNumber( Guid value ) {
        if( _imoNumber != value ) {
            this._imoNumber = value;
            onPropertyChanged( );
        }
    }

    public Guid getCallsign( ) {
        return _callsign;
    }
    public void setCallsign( Guid value ) {
        if( _callsign != value ) {
            this._callsign = value;
            onPropertyChanged( );
        }
    }

    public Guid getShipName( ) {
        return _shipName;
    }
    public void setShipName( Guid value ) {
        if( _shipName != value ) {
            this._shipName = value;
            onPropertyChanged( );
        }
    }

    public int getShipType( ) {
        return _shipType;
    }
    public void setShipType( int value ) {
        if( _shipType != value ) {
            this._shipType = value;
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

    public DateTime getEstimatedTimeOfArrival( ) {
        return _estimatedTimeOfArrival;
    }
    public void setEstimatedTimeOfArrival( DateTime value ) {
        if( _estimatedTimeOfArrival != value ) {
            this._estimatedTimeOfArrival = value;
            onPropertyChanged( );
        }
    }

    public double getDraught( ) {
        return _draught;
    }
    public void setDraught( double value ) {
        if( _draught != value ) {
            this._draught = value;
            onPropertyChanged( );
        }
    }

    public String getDestination( ) {
        return _destination;
    }
    public void setDestination( String value ) {
        if( _destination != value ) {
            this._destination = value;
            onPropertyChanged( );
        }
    }

    public boolean getDataTerminalReady( ) {
        return _dataTerminalReady;
    }
    public void setDataTerminalReady( boolean value ) {
        if( _dataTerminalReady != value ) {
            this._dataTerminalReady = value;
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


}
