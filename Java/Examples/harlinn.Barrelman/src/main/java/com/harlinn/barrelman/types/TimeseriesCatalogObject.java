package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TimeseriesCatalogObject extends TimeseriesCatalogElementObject {


    @Override
    public int getObjectType( ) {
        return Kind.TimeseriesCatalog;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TimeseriesCatalogObject( );
    }

}
