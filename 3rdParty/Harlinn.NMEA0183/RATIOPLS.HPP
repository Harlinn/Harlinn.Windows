#if ! defined( RATIO_AND_PULSE_CLASS_HEADER )

#define RATIO_AND_PULSE_CLASS_HEADER

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

class RATIO_AND_PULSE
{
   public:

      inline RATIO_AND_PULSE() noexcept {};

      /*
      ** Data
      */

      int SignalToNoiseRatio{ 0 };
      int PulseShapeECD{ 0 };

      /*
      ** Methods
      */

      NMEA0183_EXPORT void Empty( void ) noexcept;
      NMEA0183_EXPORT void Parse( int field_number, SENTENCE const& sentence ) noexcept;
      NMEA0183_EXPORT void Write( SENTENCE& sentence ) const noexcept;

      /*
      ** Operators
      */

      NMEA0183_EXPORT virtual RATIO_AND_PULSE const& operator = ( RATIO_AND_PULSE const& source ) noexcept;
};

#endif // RATIO_AND_PULSE_CLASS_HEADER
