#if ! defined( LATLONG_CLASS_HEADER )

#define LATLONG_CLASS_HEADER

/*
Author: Samuel R. Blackburn
Internet: wfc@pobox.com

"You can get credit for something or get it done, but not both."
Dr. Richard Garwin

The MIT License (MIT)

Copyright (c) 1996-2019 Sam Blackburn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* SPDX-License-Identifier: MIT */

class SENTENCE;

class COORDINATE
{
   public:

      inline COORDINATE() noexcept {}
     ~COORDINATE() { Coordinate = 0.0; }

      double Coordinate{ 0.0 };

      NMEA0183_EXPORT double GetDecimalDegrees( void ) const noexcept;
      NMEA0183_EXPORT double GetDecimalMinutes( void ) const noexcept;
      NMEA0183_EXPORT double GetDecimalSeconds( void ) const noexcept;

      inline int GetWholeDegrees(void) const noexcept
      {
          return(static_cast<int>(::floor(GetDecimalDegrees())));
      }

      inline int GetWholeMinutes(void) const noexcept
      {
          return(static_cast<int>(::floor(GetDecimalMinutes())));
      }

      int GetWholeSeconds(void) const noexcept
      {
          return(static_cast<int>(::floor(GetDecimalSeconds())));
      }
};

class LATITUDE : public COORDINATE
{
   public:

       inline LATITUDE() noexcept : Latitude(0.0), Northing(NORTHSOUTH::NS_Unknown) {}

      /*
      ** Data
      */

      double Latitude{ 0.0 };
      NORTHSOUTH Northing{ NORTHSOUTH::NS_Unknown };

      /*
      ** Methods
      */

      NMEA0183_EXPORT virtual void Empty( void ) noexcept;
      NMEA0183_EXPORT virtual bool IsDataValid( void ) const noexcept;
      NMEA0183_EXPORT virtual void Parse( int PositionFieldNumber, int NorthingFieldNumber, SENTENCE const& LineToParse ) noexcept;
      NMEA0183_EXPORT virtual void Set( double Position, std::string_view Northing ) noexcept;
      NMEA0183_EXPORT virtual void Write( SENTENCE& sentence ) const noexcept;

      /*
      ** Operators
      */

      NMEA0183_EXPORT virtual LATITUDE const& operator = (LATITUDE const& source) noexcept;
};

class LONGITUDE : public COORDINATE
{
   public:

       inline LONGITUDE() noexcept : Longitude(0.0), Easting(EASTWEST::EW_Unknown) {}

      /*
      ** Data
      */

      double Longitude{ 0.0 };

      EASTWEST Easting{ EASTWEST::EW_Unknown };

      /*
      ** Methods
      */

      NMEA0183_EXPORT virtual void Empty( void ) noexcept;
      NMEA0183_EXPORT virtual bool IsDataValid( void ) const noexcept;
      NMEA0183_EXPORT virtual void Parse( int PositionFieldNumber, int EastingFieldNumber, SENTENCE const& LineToParse ) noexcept;
      NMEA0183_EXPORT virtual void Set( double Position, std::string_view Easting ) noexcept;
      NMEA0183_EXPORT virtual void Write( SENTENCE& sentence ) const noexcept;

      /*
      ** Operators
      */

      NMEA0183_EXPORT virtual LONGITUDE const& operator = ( LONGITUDE const& source ) noexcept;
};

class LATLONG
{
   public:

      inline LATLONG() noexcept {};

      /*
      ** Data
      */

      LATITUDE  Latitude;
      LONGITUDE Longitude;

      /*
      ** Methods
      */

      NMEA0183_EXPORT virtual void Empty( void ) noexcept;
      NMEA0183_EXPORT virtual bool Parse( int LatitudePostionFieldNumber, int NorthingFieldNumber, int LongitudePositionFieldNumber, int EastingFieldNumber, SENTENCE const& LineToParse ) noexcept;
      NMEA0183_EXPORT virtual std::string PlainEnglish( void ) const noexcept;
      NMEA0183_EXPORT virtual void Write( SENTENCE& sentence ) const noexcept;

      /*
      ** Operators
      */

      NMEA0183_EXPORT virtual LATLONG const& operator = ( LATLONG const& source ) noexcept;
};

#endif // LATLONG_CLASS_HEADER
