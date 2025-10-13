package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisDeviceRawSentenceObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _aisDevice;
    private DateTime _timestamp;
    private String _sentence = "";

    @Override
    public int getObjectType( ) {
        return Kind.AisDeviceRawSentence;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisDeviceRawSentenceObject( );
    }

    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getAisDevice( ) {
        return _aisDevice;
    }
    public void setAisDevice( Guid value ) {
        if( _aisDevice != value ) {
            this._aisDevice = value;
            onPropertyChanged( );
        }
    }

    public DateTime getTimestamp( ) {
        return _timestamp;
    }
    public void setTimestamp( DateTime value ) {
        if( _timestamp != value ) {
            this._timestamp = value;
            onPropertyChanged( );
        }
    }

    public String getSentence( ) {
        return _sentence;
    }
    public void setSentence( String value ) {
        if( _sentence != value ) {
            this._sentence = value;
            onPropertyChanged( );
        }
    }


}
