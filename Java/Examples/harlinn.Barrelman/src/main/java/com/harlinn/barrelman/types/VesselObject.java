package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class VesselObject extends TrackableItemObject {

    private String _name = "";
    private Guid _type;
    private int _toBow = 0;
    private int _toStern = 0;
    private int _toPort = 0;
    private int _toStarboard = 0;
    private Guid _draughtTimeseries;
    private Guid _personsOnBoardTimeseries;

    @Override
    public int getObjectType( ) {
        return Kind.Vessel;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new VesselObject( );
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

    public Guid getType( ) {
        return _type;
    }
    public void setType( Guid value ) {
        if( _type != value ) {
            this._type = value;
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

    public Guid getDraughtTimeseries( ) {
        return _draughtTimeseries;
    }
    public void setDraughtTimeseries( Guid value ) {
        if( _draughtTimeseries != value ) {
            this._draughtTimeseries = value;
            onPropertyChanged( );
        }
    }

    public Guid getPersonsOnBoardTimeseries( ) {
        return _personsOnBoardTimeseries;
    }
    public void setPersonsOnBoardTimeseries( Guid value ) {
        if( _personsOnBoardTimeseries != value ) {
            this._personsOnBoardTimeseries = value;
            onPropertyChanged( );
        }
    }


}
