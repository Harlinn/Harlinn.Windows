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

public class AisPositionReportForLongRangeApplicationsMessageObject extends AisMessageObject {

    public final int KIND = Kind.AisPositionReportForLongRangeApplicationsMessage;

    private int _positionAccuracy = PositionAccuracy.Low;
    private int _raim = Raim.NotInUse;
    private int _navigationStatus = NavigationStatus.UnderWayUsingEngine;
    private double _longitude = 0.0;
    private double _latitude = 0.0;
    private double _speedOverGround = 0.0;
    private double _courseOverGround = 0.0;
    private int _gnssPositionStatus = GnssPositionStatus.CurrentGnssPosition;
    private int _spare = 0;

    public AisPositionReportForLongRangeApplicationsMessageObject( ) {
    }
    public AisPositionReportForLongRangeApplicationsMessageObject( byte objectState, Guid id, long rowVersion, Guid aisDevice, DateTime receivedTimestamp, long messageSequenceNumber, int repeat, Guid mmsi, int positionAccuracy, int raim, int navigationStatus, double longitude, double latitude, double speedOverGround, double courseOverGround, int gnssPositionStatus, int spare ) {
        super( objectState, id, rowVersion, aisDevice, receivedTimestamp, messageSequenceNumber, repeat, mmsi );
        this._positionAccuracy = positionAccuracy;
        this._raim = raim;
        this._navigationStatus = navigationStatus;
        this._longitude = longitude;
        this._latitude = latitude;
        this._speedOverGround = speedOverGround;
        this._courseOverGround = courseOverGround;
        this._gnssPositionStatus = gnssPositionStatus;
        this._spare = spare;
    }

    @Override
    public int getObjectType( ) {
        return Kind.AisPositionReportForLongRangeApplicationsMessage;
    }
    @Override
    protected AbstractDataObject create( ) {
        return new AisPositionReportForLongRangeApplicationsMessageObject( );
    }

    public int getPositionAccuracy( ) {
        return _positionAccuracy;
    }
    public void setPositionAccuracy( int value ) {
        if( !Comparer.equalsInt32( _positionAccuracy, value ) ) {
            _positionAccuracy = value;
            onPropertyChanged( );
        }
    }

    public int getRaim( ) {
        return _raim;
    }
    public void setRaim( int value ) {
        if( !Comparer.equalsInt32( _raim, value ) ) {
            _raim = value;
            onPropertyChanged( );
        }
    }

    public int getNavigationStatus( ) {
        return _navigationStatus;
    }
    public void setNavigationStatus( int value ) {
        if( !Comparer.equalsInt32( _navigationStatus, value ) ) {
            _navigationStatus = value;
            onPropertyChanged( );
        }
    }

    public double getLongitude( ) {
        return _longitude;
    }
    public void setLongitude( double value ) {
        if( !Comparer.equalsDouble( _longitude, value ) ) {
            _longitude = value;
            onPropertyChanged( );
        }
    }

    public double getLatitude( ) {
        return _latitude;
    }
    public void setLatitude( double value ) {
        if( !Comparer.equalsDouble( _latitude, value ) ) {
            _latitude = value;
            onPropertyChanged( );
        }
    }

    public double getSpeedOverGround( ) {
        return _speedOverGround;
    }
    public void setSpeedOverGround( double value ) {
        if( !Comparer.equalsDouble( _speedOverGround, value ) ) {
            _speedOverGround = value;
            onPropertyChanged( );
        }
    }

    public double getCourseOverGround( ) {
        return _courseOverGround;
    }
    public void setCourseOverGround( double value ) {
        if( !Comparer.equalsDouble( _courseOverGround, value ) ) {
            _courseOverGround = value;
            onPropertyChanged( );
        }
    }

    public int getGnssPositionStatus( ) {
        return _gnssPositionStatus;
    }
    public void setGnssPositionStatus( int value ) {
        if( !Comparer.equalsInt32( _gnssPositionStatus, value ) ) {
            _gnssPositionStatus = value;
            onPropertyChanged( );
        }
    }

    public int getSpare( ) {
        return _spare;
    }
    public void setSpare( int value ) {
        if( !Comparer.equalsInt32( _spare, value ) ) {
            _spare = value;
            onPropertyChanged( );
        }
    }



    @Override
    public void assignTo( AbstractDataObject target ) {
        super.assignTo( target );
        var targetObject = ( AisPositionReportForLongRangeApplicationsMessageObject )target;
        targetObject._positionAccuracy = this._positionAccuracy;
        targetObject._raim = this._raim;
        targetObject._navigationStatus = this._navigationStatus;
        targetObject._longitude = this._longitude;
        targetObject._latitude = this._latitude;
        targetObject._speedOverGround = this._speedOverGround;
        targetObject._courseOverGround = this._courseOverGround;
        targetObject._gnssPositionStatus = this._gnssPositionStatus;
        targetObject._spare = this._spare;
    }

    @Override
    public boolean equals(Object obj) {
        var result = super.equals( obj );
        if( !result ) {
            return false;
        }
        var other = (AisPositionReportForLongRangeApplicationsMessageObject)obj;
        if( !Comparer.equalsInt32( this._positionAccuracy, other._positionAccuracy ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._raim, other._raim ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._navigationStatus, other._navigationStatus ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._longitude, other._longitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._latitude, other._latitude ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._speedOverGround, other._speedOverGround ) ) {
            return false;
        }
        if( !Comparer.equalsDouble( this._courseOverGround, other._courseOverGround ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._gnssPositionStatus, other._gnssPositionStatus ) ) {
            return false;
        }
        if( !Comparer.equalsInt32( this._spare, other._spare ) ) {
            return false;
        }
        return true;
    }

    @Override
    public void writeTo( BinaryWriter destination ) {
        super.writeTo( destination );
        destination.writeInt32( _positionAccuracy );
        destination.writeInt32( _raim );
        destination.writeInt32( _navigationStatus );
        destination.writeDouble( _longitude );
        destination.writeDouble( _latitude );
        destination.writeDouble( _speedOverGround );
        destination.writeDouble( _courseOverGround );
        destination.writeInt32( _gnssPositionStatus );
        destination.writeInt32( _spare );
    }

    @Override
    public void readFrom(BinaryReader source) {
        super.readFrom( source );
        _positionAccuracy = source.readInt32( );
        _raim = source.readInt32( );
        _navigationStatus = source.readInt32( );
        _longitude = source.readDouble( );
        _latitude = source.readDouble( );
        _speedOverGround = source.readDouble( );
        _courseOverGround = source.readDouble( );
        _gnssPositionStatus = source.readInt32( );
        _spare = source.readInt32( );
    }

}
