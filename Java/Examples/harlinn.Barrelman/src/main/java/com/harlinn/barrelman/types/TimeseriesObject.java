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
        if( _maxRetention != value ) {
            this._maxRetention = value;
            onPropertyChanged( );
        }
    }


}
