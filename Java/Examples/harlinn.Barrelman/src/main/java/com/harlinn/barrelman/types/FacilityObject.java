package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class FacilityObject extends ItemObject {

    private String _name = "";
    private Guid _type;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _altitude = 0.0;

    @Override
    public int getObjectType( ) {
        return Kind.Facility;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new FacilityObject( );
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

    public double getAltitude( ) {
        return _altitude;
    }
    public void setAltitude( double value ) {
        if( _altitude != value ) {
            this._altitude = value;
            onPropertyChanged( );
        }
    }


}
