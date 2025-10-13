package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisStaticDataReportMessageObject extends AisMessageObject {

    private int _partNumber = 0;

    @Override
    public int getObjectType( ) {
        return Kind.AisStaticDataReportMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisStaticDataReportMessageObject( );
    }

    public int getPartNumber( ) {
        return _partNumber;
    }
    public void setPartNumber( int value ) {
        if( _partNumber != value ) {
            this._partNumber = value;
            onPropertyChanged( );
        }
    }


}
