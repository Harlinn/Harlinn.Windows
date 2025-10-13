package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CursorInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private int _typeCode = 0;

    @Override
    public int getObjectType( ) {
        return Kind.CursorInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CursorInfoObject( );
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

    public int getTypeCode( ) {
        return _typeCode;
    }
    public void setTypeCode( int value ) {
        if( _typeCode != value ) {
            this._typeCode = value;
            onPropertyChanged( );
        }
    }


}
