package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class NamespaceObject extends NamespaceElementObject {


    @Override
    public int getObjectType( ) {
        return Kind.Namespace;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new NamespaceObject( );
    }

}
