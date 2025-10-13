package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticDataReportPartAMessageObject extends AisStaticDataReportMessageObject {

    private Guid _shipName;
    private int _spare = 0;

    @Override
    public int getObjectType( ) {
        return Kind.AisStaticDataReportPartAMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStaticDataReportPartAMessageObject( );
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
