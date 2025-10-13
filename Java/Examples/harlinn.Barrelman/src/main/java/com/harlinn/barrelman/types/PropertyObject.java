package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class PropertyObject extends AbstractDataObjectWithGuidKey {

    private long _rowVersion = 0;
    private Guid _element;
    private Guid _definition;


    public long getRowVersion( ) {
        return _rowVersion;
    }
    public void setRowVersion( long value ) {
        if( _rowVersion != value ) {
            this._rowVersion = value;
            onPropertyChanged( );
        }
    }

    public Guid getElement( ) {
        return _element;
    }
    public void setElement( Guid value ) {
        if( _element != value ) {
            this._element = value;
            onPropertyChanged( );
        }
    }

    public Guid getDefinition( ) {
        return _definition;
    }
    public void setDefinition( Guid value ) {
        if( _definition != value ) {
            this._definition = value;
            onPropertyChanged( );
        }
    }


}
