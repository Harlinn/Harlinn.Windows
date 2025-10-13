package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class ElementTypeObject extends NamespaceElementObject {


    @Override
    public int getObjectType( ) {
        return Kind.ElementType;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new ElementTypeObject( );
    }

}
