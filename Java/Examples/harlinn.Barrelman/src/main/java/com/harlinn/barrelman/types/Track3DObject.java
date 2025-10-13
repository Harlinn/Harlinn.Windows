package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Track3DObject extends TrackBaseObject {


    @Override
    public int getObjectType( ) {
        return Kind.Track3D;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Track3DObject( );
    }

}
