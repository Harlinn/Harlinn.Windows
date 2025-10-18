package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeseriesCatalogObject extends TimeseriesCatalogElementObject {

    public final int KIND = Kind.TimeseriesCatalog;


    public TimeseriesCatalogObject( ) {
    }
    public TimeseriesCatalogObject( byte objectState, Guid id, long rowVersion, Guid catalog, String name ) {
        super( objectState, id, rowVersion, catalog, name );
    }

    @Override
    public int getObjectType( ) {
        return Kind.TimeseriesCatalog;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeseriesCatalogObject( );
    }

}
