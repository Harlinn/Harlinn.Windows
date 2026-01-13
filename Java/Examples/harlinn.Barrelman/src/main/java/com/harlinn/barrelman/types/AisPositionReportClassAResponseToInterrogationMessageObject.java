/*
    Copyright 2024-2026 Espen Harlinn
 
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
 
        http://www.apache.org/licenses/LICENSE-2.0
 
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
package com.harlinn.barrelman.types;

import com.harlinn.common.io.*;
import com.harlinn.common.types.*;
import com.harlinn.common.util.*;

public class AisPositionReportClassAResponseToInterrogationMessageObject extends AisPositionReportClassAMessageBaseObject {

    public final int KIND = Kind.AisPositionReportClassAResponseToInterrogationMessage;


    public AisPositionReportClassAResponseToInterrogationMessageObject( ) {
    }
    public AisPositionReportClassAResponseToInterrogationMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int navigationStatus, Integer rateOfTurn, double speedOverGround, int positionAccuracy, double longitude, double latitude, double courseOverGround, Integer trueHeading, int timestamp, int maneuverIndicator, int spare, int raim, int radioStatus ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi, navigationStatus, rateOfTurn, speedOverGround, positionAccuracy, longitude, latitude, courseOverGround, trueHeading, timestamp, maneuverIndicator, spare, raim, radioStatus );
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportClassAResponseToInterrogationMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportClassAResponseToInterrogationMessageObject( );
    }

}
