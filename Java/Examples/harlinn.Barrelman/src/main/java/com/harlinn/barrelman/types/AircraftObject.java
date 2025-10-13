package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AircraftObject extends TrackableItemObject {

    private String _name = "";
    private Guid _type;

    @Override
    public int getObjectType( ) {
        return Kind.Aircraft;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AircraftObject( );
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


}
