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
        if( !Comparer.equalsInt32( _partNumber, value ) ) {
            _partNumber = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _partNumber );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _partNumber = source.readInt32( );
    }

}
