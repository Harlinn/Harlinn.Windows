#pragma once
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

namespace Harlinn::GeographicLib::Net
{
    public value class DistanceAndBearing
    {
        // distance in meters.
        double distance_;

        // bearing from first position.
        double azimuth1_;

        // bearing from second position.
        double azimuth2_;
    public:
        DistanceAndBearing( double distance, double azimuth1, double azimuth2 )
            : distance_( distance ), azimuth1_( azimuth1 ), azimuth2_( azimuth2 )
        {
        }

        void Assign( double distance, double azimuth1, double azimuth2 )
        {
            distance_ = distance;
            azimuth1_ = azimuth1;
            azimuth2_ = azimuth2;
        }

        /// <summary>
        /// Distance in meters
        /// </summary>
        property double Distance
        {
            double get( )
            {
                return distance_;
            }

            void set( double value )
            {
                distance_ = value;
            }
        }


        /// <summary>
        /// bearing/azimuth from first position.
        /// </summary>
        property double Azimuth1
        {
            double get( )
            {
                return azimuth1_;
            }

            void set( double value )
            {
                azimuth1_ = value;
            }
        }


        /// <summary>
        /// bearing/azimuth from second position.
        /// </summary>
        property double Azimuth2
        {
            double get( )
            {
                return azimuth2_;
            }

            void set( double value )
            {
                azimuth2_ = value;
            }
        }
    };

}
