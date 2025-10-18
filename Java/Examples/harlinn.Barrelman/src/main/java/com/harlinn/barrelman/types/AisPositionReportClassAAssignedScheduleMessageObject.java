package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisPositionReportClassAAssignedScheduleMessageObject extends AisPositionReportClassAMessageBaseObject {

    public final int KIND = Kind.AisPositionReportClassAAssignedScheduleMessage;


    public AisPositionReportClassAAssignedScheduleMessageObject( ) {
    }
    public AisPositionReportClassAAssignedScheduleMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int navigationStatus, Integer rateOfTurn, double speedOverGround, int positionAccuracy, double longitude, double latitude, double courseOverGround, Integer trueHeading, int timestamp, int maneuverIndicator, int spare, int raim, int radioStatus ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, navigationStatus, rateOfTurn, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, maneuverIndicator, spare, raim, radioStatus );
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportClassAAssignedScheduleMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportClassAAssignedScheduleMessageObject( );
    }

}
