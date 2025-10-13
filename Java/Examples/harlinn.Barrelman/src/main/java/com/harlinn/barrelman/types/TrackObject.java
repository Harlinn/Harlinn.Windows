package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackObject extends TrackBaseObject {


    @Override
    public int getObjectType( ) {
        return Kind.Track;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackObject( );
    }

}
