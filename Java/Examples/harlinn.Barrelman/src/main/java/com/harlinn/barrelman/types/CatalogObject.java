package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CatalogObject extends CatalogElementObject {


    @Override
    public int getObjectType( ) {
        return Kind.Catalog;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CatalogObject( );
    }

}
