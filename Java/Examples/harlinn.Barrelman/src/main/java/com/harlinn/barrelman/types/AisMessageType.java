package com.harlinn.barrelman.types;

public class AisMessageType {
    public final static int PositionReportClassA = 1;
    public final static int PositionReportClassAAssignedSchedule = 2;
    public final static int PositionReportClassAResponseToInterrogation = 3;
    public final static int BaseStationReport = 4;
    public final static int StaticAndVoyageRelatedData = 5;
    public final static int BinaryAddressedMessage = 6;
    public final static int BinaryAcknowledge = 7;
    public final static int BinaryBroadcastMessage = 8;
    public final static int StandardSarAircraftPositionReport = 9;
    public final static int UtcAndDateInquiry = 10;
    public final static int UtcAndDateResponse = 11;
    public final static int AddressedSafetyRelatedMessage = 12;
    public final static int SafetyRelatedAcknowledgment = 13;
    public final static int SafetyRelatedBroadcastMessage = 14;
    public final static int Interrogation = 15;
    public final static int AssignmentModeCommand = 16;
    public final static int DgnssBinaryBroadcastMessage = 17;
    public final static int StandardClassBCsPositionReport = 18;
    public final static int ExtendedClassBCsPositionReport = 19;
    public final static int DataLinkManagement = 20;
    public final static int AidToNavigationReport = 21;
    public final static int ChannelManagement = 22;
    public final static int GroupAssignmentCommand = 23;
    public final static int StaticDataReport = 24;
    public final static int SingleSlotBinaryMessage = 25;
    public final static int MultipleSlotBinaryMessageWithCommunicationsState = 26;
    public final static int PositionReportForLongRangeApplications = 27;

    public final static String toString(int value) {
    	switch(value) {
    	    case PositionReportClassA:
    	        return "PositionReportClassA";
    	    case PositionReportClassAAssignedSchedule:
    	        return "PositionReportClassAAssignedSchedule";
    	    case PositionReportClassAResponseToInterrogation:
    	        return "PositionReportClassAResponseToInterrogation";
    	    case BaseStationReport:
    	        return "BaseStationReport";
    	    case StaticAndVoyageRelatedData:
    	        return "StaticAndVoyageRelatedData";
    	    case BinaryAddressedMessage:
    	        return "BinaryAddressedMessage";
    	    case BinaryAcknowledge:
    	        return "BinaryAcknowledge";
    	    case BinaryBroadcastMessage:
    	        return "BinaryBroadcastMessage";
    	    case StandardSarAircraftPositionReport:
    	        return "StandardSarAircraftPositionReport";
    	    case UtcAndDateInquiry:
    	        return "UtcAndDateInquiry";
    	    case UtcAndDateResponse:
    	        return "UtcAndDateResponse";
    	    case AddressedSafetyRelatedMessage:
    	        return "AddressedSafetyRelatedMessage";
    	    case SafetyRelatedAcknowledgment:
    	        return "SafetyRelatedAcknowledgment";
    	    case SafetyRelatedBroadcastMessage:
    	        return "SafetyRelatedBroadcastMessage";
    	    case Interrogation:
    	        return "Interrogation";
    	    case AssignmentModeCommand:
    	        return "AssignmentModeCommand";
    	    case DgnssBinaryBroadcastMessage:
    	        return "DgnssBinaryBroadcastMessage";
    	    case StandardClassBCsPositionReport:
    	        return "StandardClassBCsPositionReport";
    	    case ExtendedClassBCsPositionReport:
    	        return "ExtendedClassBCsPositionReport";
    	    case DataLinkManagement:
    	        return "DataLinkManagement";
    	    case AidToNavigationReport:
    	        return "AidToNavigationReport";
    	    case ChannelManagement:
    	        return "ChannelManagement";
    	    case GroupAssignmentCommand:
    	        return "GroupAssignmentCommand";
    	    case StaticDataReport:
    	        return "StaticDataReport";
    	    case SingleSlotBinaryMessage:
    	        return "SingleSlotBinaryMessage";
    	    case MultipleSlotBinaryMessageWithCommunicationsState:
    	        return "MultipleSlotBinaryMessageWithCommunicationsState";
    	    case PositionReportForLongRangeApplications:
    	        return "PositionReportForLongRangeApplications";
    	    default:
    	        throw new IllegalArgumentException( "Unknown AisMessageType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "PositionReportClassA":
    	        return PositionReportClassA;
    	    case "PositionReportClassAAssignedSchedule":
    	        return PositionReportClassAAssignedSchedule;
    	    case "PositionReportClassAResponseToInterrogation":
    	        return PositionReportClassAResponseToInterrogation;
    	    case "BaseStationReport":
    	        return BaseStationReport;
    	    case "StaticAndVoyageRelatedData":
    	        return StaticAndVoyageRelatedData;
    	    case "BinaryAddressedMessage":
    	        return BinaryAddressedMessage;
    	    case "BinaryAcknowledge":
    	        return BinaryAcknowledge;
    	    case "BinaryBroadcastMessage":
    	        return BinaryBroadcastMessage;
    	    case "StandardSarAircraftPositionReport":
    	        return StandardSarAircraftPositionReport;
    	    case "UtcAndDateInquiry":
    	        return UtcAndDateInquiry;
    	    case "UtcAndDateResponse":
    	        return UtcAndDateResponse;
    	    case "AddressedSafetyRelatedMessage":
    	        return AddressedSafetyRelatedMessage;
    	    case "SafetyRelatedAcknowledgment":
    	        return SafetyRelatedAcknowledgment;
    	    case "SafetyRelatedBroadcastMessage":
    	        return SafetyRelatedBroadcastMessage;
    	    case "Interrogation":
    	        return Interrogation;
    	    case "AssignmentModeCommand":
    	        return AssignmentModeCommand;
    	    case "DgnssBinaryBroadcastMessage":
    	        return DgnssBinaryBroadcastMessage;
    	    case "StandardClassBCsPositionReport":
    	        return StandardClassBCsPositionReport;
    	    case "ExtendedClassBCsPositionReport":
    	        return ExtendedClassBCsPositionReport;
    	    case "DataLinkManagement":
    	        return DataLinkManagement;
    	    case "AidToNavigationReport":
    	        return AidToNavigationReport;
    	    case "ChannelManagement":
    	        return ChannelManagement;
    	    case "GroupAssignmentCommand":
    	        return GroupAssignmentCommand;
    	    case "StaticDataReport":
    	        return StaticDataReport;
    	    case "SingleSlotBinaryMessage":
    	        return SingleSlotBinaryMessage;
    	    case "MultipleSlotBinaryMessageWithCommunicationsState":
    	        return MultipleSlotBinaryMessageWithCommunicationsState;
    	    case "PositionReportForLongRangeApplications":
    	        return PositionReportForLongRangeApplications;
    	    default:
    	        throw new IllegalArgumentException( "Unknown AisMessageType constant name:" + value );
    	}
    }

}

