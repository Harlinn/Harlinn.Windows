#pragma once
/*
   Copyright 2024 Espen Harlinn

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
    public value struct Point
    {
        double x_;
        double y_;
    public:
        Point( double x, double y )
            : x_( x ), y_( y )
        {
        }

        property double X
        {
            double get( )
            {
                return x_;
            }

            void set( double value )
            {
                x_ = value;
            }
        }

        property double Y
        {
            double get( )
            {
                return y_;
            }

            void set( double value )
            {
                y_ = value;
            }
        }

        bool operator == ( Point other )
        {
            return x_ == other.x_ && y_ == other.y_;
        }

        bool operator != ( Point other )
        {
            return x_ != other.x_ || y_ != other.y_;
        }
    };

    public value struct Point3D 
    {
        double x_;
        double y_;
        double z_;
    public:
        Point3D( double x, double y, double z )
            : x_( x ), y_( y ), z_( z )
        {
        }

        property double X
        {
            double get( )
            {
                return x_;
            }

            void set( double value )
            {
                x_ = value;
            }
        }

        property double Y
        {
            double get( )
            {
                return y_;
            }

            void set( double value )
            {
                y_ = value;
            }
        }

        property double Z
        {
            double get( )
            {
                return z_;
            }

            void set( double value )
            {
                z_ = value;
            }
        }

        bool operator == ( Point3D other )
        {
            return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
        }

        bool operator != ( Point3D other )
        {
            return x_ != other.x_ || y_ != other.y_ || z_ != other.z_;
        }
    };
}


