package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class TrackObject extends TrackBaseObject {

    public final int KIND = Kind.Track;


    public TrackObject( ) {
    }
    public TrackObject( byte objectState, Guid id, long rowVersion, Guid tracker, long trackNumber, DateTime timestamp ) {
        super( objectState, id, rowVersion, tracker, trackNumber, timestamp );
    }

    @Override
    public int getObjectType( ) {
        return Kind.Track;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new TrackObject( );
    }

}
