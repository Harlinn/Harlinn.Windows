package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TimeseriesObject extends TimeseriesCatalogElementObject {

    private TimeSpan _maxRetention;


    public TimeSpan getMaxRetention( ) {
        return _maxRetention;
    }
    public void setMaxRetention( TimeSpan value ) {
        if( !Comparer.equalsTimeSpan( _maxRetention, value ) ) {
            _maxRetention = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeTimeSpan( _maxRetention );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _maxRetention = source.readTimeSpan( );
    }

}
