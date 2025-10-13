package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisPositionReportClassAAssignedScheduleMessageObject extends AisPositionReportClassAMessageBaseObject {


    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportClassAAssignedScheduleMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportClassAAssignedScheduleMessageObject( );
    }

}
