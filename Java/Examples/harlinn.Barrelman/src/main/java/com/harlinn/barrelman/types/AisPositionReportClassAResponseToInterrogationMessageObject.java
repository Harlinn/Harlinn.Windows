package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisPositionReportClassAResponseToInterrogationMessageObject extends AisPositionReportClassAMessageBaseObject {


    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportClassAResponseToInterrogationMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportClassAResponseToInterrogationMessageObject( );
    }

}
