package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisAidToNavigationObject extends TrackableItemObject {

    private String _name = "";
    private Guid _mMSI;
    private int _navigationalAidType = NavigationalAidType.NotSpecified;
    private Guid _position;
    private boolean _isVirtual = false;
    private int _toBow = 0;
    private int _toStern = 0;
    private int _toPort = 0;
    private int _toStarboard = 0;
    private Guid _offPositionTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.AisAidToNavigation;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisAidToNavigationObject( );
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

    public Guid getMMSI( ) {
        return _mMSI;
    }
    public void setMMSI( Guid value ) {
        if( _mMSI != value ) {
            this._mMSI = value;
            onPropertyChanged( );
        }
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

    public Guid getPosition( ) {
        return _position;
    }
    public void setPosition( Guid value ) {
        if( _position != value ) {
            this._position = value;
            onPropertyChanged( );
        }
    }

    public boolean getIsVirtual( ) {
        return _isVirtual;
    }
    public void setIsVirtual( boolean value ) {
        if( _isVirtual != value ) {
            this._isVirtual = value;
            onPropertyChanged( );
        }
    }

    public int getToBow( ) {
        return _toBow;
    }
    public void setToBow( int value ) {
        if( _toBow != value ) {
            this._toBow = value;
            onPropertyChanged( );
        }
    }

    public int getToStern( ) {
        return _toStern;
    }
    public void setToStern( int value ) {
        if( _toStern != value ) {
            this._toStern = value;
            onPropertyChanged( );
        }
    }

    public int getToPort( ) {
        return _toPort;
    }
    public void setToPort( int value ) {
        if( _toPort != value ) {
            this._toPort = value;
            onPropertyChanged( );
        }
    }

    public int getToStarboard( ) {
        return _toStarboard;
    }
    public void setToStarboard( int value ) {
        if( _toStarboard != value ) {
            this._toStarboard = value;
            onPropertyChanged( );
        }
    }

    public Guid getOffPositionTimeseries( ) {
        return _offPositionTimeseries;
    }
    public void setOffPositionTimeseries( Guid value ) {
        if( _offPositionTimeseries != value ) {
            this._offPositionTimeseries = value;
            onPropertyChanged( );
        }
    }


}
