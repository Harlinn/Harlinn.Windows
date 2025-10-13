package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CollectionInfoObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private long _count = 0;

    @Override
    public int getObjectType( ) {
        return Kind.CollectionInfo;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CollectionInfoObject( );
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

    public long getCount( ) {
        return _count;
    }
    public void setCount( long value ) {
        if( _count != value ) {
            this._count = value;
            onPropertyChanged( );
        }
    }


}
