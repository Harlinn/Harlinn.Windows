package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class CatalogObject extends CatalogElementObject {

    public final int KIND = Kind.Catalog;


    public CatalogObject( ) {
    }
    public CatalogObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name ) {
        super( objectState, id, rowVersion, catalog, name );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Catalog;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new CatalogObject( );
    }

}
