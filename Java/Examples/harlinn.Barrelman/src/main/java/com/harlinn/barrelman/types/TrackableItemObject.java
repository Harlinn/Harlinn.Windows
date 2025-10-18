package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public abstract class TrackableItemObject extends ItemObject {

    public final int KIND = Kind.TrackableItem;


    public TrackableItemObject( ) {
    }
    public TrackableItemObject( byte objectState, Guid id, long rowVersion ) {
        super( objectState, id, rowVersion );
    }


}
