package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisPositionReportClassAMessageObject extends AisPositionReportClassAMessageBaseObject {


    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportClassAMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportClassAMessageObject( );
    }

}
