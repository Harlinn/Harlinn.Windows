package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ElementTypeObject extends NamespaceElementObject {

    public final int KIND = Kind.ElementType;


    public ElementTypeObject( ) {
    }
    public ElementTypeObject( byte objectState, Guid id, long rowVersion, Guid namespace, String name, String description ) {
        super( objectState, id, rowVersion, namespace, name, description );
    }

    @Override
    public int getObjectType( ) {
        return Kind.ElementType;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ElementTypeObject( );
    }

}
