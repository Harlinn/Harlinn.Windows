package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class Track3DObject extends TrackBaseObject {

    public final int KIND = Kind.Track3D;


    public Track3DObject( ) {
    }
    public Track3DObject( byte objectState, Guid id, long rowVersion, Guid tracker, long trackNumber, DateTime timestamp ) {
        super( objectState, id, rowVersion, tracker, trackNumber, timestamp );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Track3D;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new Track3DObject( );
    }

}
