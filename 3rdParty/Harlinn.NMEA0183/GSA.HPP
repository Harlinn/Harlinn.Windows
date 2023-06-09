#if ! defined( GSA_CLASS_HEADER )

#define GSA_CLASS_HEADER

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

class GSA : public RESPONSE
{
   public:

      inline GSA() noexcept : RESPONSE(STRING_VIEW("GSA")) {}

      /*
      ** Data
      */

      enum class OPERATING_MODE
      {
         UnknownOperatingMode = 0,
         Manual,
         Automatic
      };

      enum class FIX_MODE
      {
         FixUnknown = 0,
         FixUnavailable,
         TwoDimensional,
         ThreeDimensional
      };

      OPERATING_MODE OperatingMode{ OPERATING_MODE::UnknownOperatingMode };
      FIX_MODE       FixMode{ FIX_MODE::FixUnknown };
      int            SatelliteNumber[12]{ 0 };
      double         PDOP{ 0.0 };
      double         HDOP{ 0.0 };
      double         VDOP{ 0.0 };

      /*
      ** Methods
      */

      NMEA0183_EXPORT void Empty( void ) noexcept override;
      NMEA0183_EXPORT bool Parse( SENTENCE const& sentence ) noexcept override;
      NMEA0183_EXPORT bool Write( SENTENCE& sentence ) const noexcept override;

      /*
      ** Operators
      */

      NMEA0183_EXPORT virtual GSA const& operator = ( GSA const& source ) noexcept;
};

#endif // GSA_CLASS_HEADER
