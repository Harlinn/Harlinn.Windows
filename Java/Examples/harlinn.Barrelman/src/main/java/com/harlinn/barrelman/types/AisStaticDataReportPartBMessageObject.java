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
        if( _shipType != value ) {
            this._shipType = value;
            onPropertyChanged( );
        }
    }

    public String getVendorId( ) {
        return _vendorId;
    }
    public void setVendorId( String value ) {
        if( _vendorId != value ) {
            this._vendorId = value;
            onPropertyChanged( );
        }
    }

    public int getUnitModelCode( ) {
        return _unitModelCode;
    }
    public void setUnitModelCode( int value ) {
        if( _unitModelCode != value ) {
            this._unitModelCode = value;
            onPropertyChanged( );
        }
    }

    public int getSerialNumber( ) {
        return _serialNumber;
    }
    public void setSerialNumber( int value ) {
        if( _serialNumber != value ) {
            this._serialNumber = value;
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

    public Guid getMothershipMmsi( ) {
        return _mothershipMmsi;
    }
    public void setMothershipMmsi( Guid value ) {
        if( _mothershipMmsi != value ) {
            this._mothershipMmsi = value;
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


}
