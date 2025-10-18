package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class NamespaceObject extends NamespaceElementObject {

    public final int KIND = Kind.Namespace;


    public NamespaceObject( ) {
    }
    public NamespaceObject( byte objectState, Guid id, long rowVersion, Guid namespace, String name, String description ) {
        super( objectState, id, rowVersion, namespace, name, description );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Namespace;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new NamespaceObject( );
    }

}
