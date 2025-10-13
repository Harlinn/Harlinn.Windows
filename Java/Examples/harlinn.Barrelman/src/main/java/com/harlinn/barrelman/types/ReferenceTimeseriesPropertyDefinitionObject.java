package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ReferenceTimeseriesPropertyDefinitionObject extends TimeseriesPropertyDefinitionObject {

    private Guid _referencedElementType;

    @Override
    public int getObjectType( ) {
        return Kind.ReferenceTimeseriesPropertyDefinition;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ReferenceTimeseriesPropertyDefinitionObject( );
    }

    public Guid getReferencedElementType( ) {
        return _referencedElementType;
    }
    public void setReferencedElementType( Guid value ) {
        if( _referencedElementType != value ) {
            this._referencedElementType = value;
            onPropertyChanged( );
        }
    }


}
