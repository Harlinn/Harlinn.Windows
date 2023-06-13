#if ! defined( SENTENCE_CLASS_HEADER )

#define SENTENCE_CLASS_HEADER

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

class LATLONG;

class SENTENCE
{
   public:

      inline SENTENCE() noexcept {};

      /*
      ** Data
      */

      std::string Sentence;

      /*
      ** Methods
      */

      NMEA0183_EXPORT virtual NMEA0183_BOOLEAN Boolean( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual uint8_t ComputeChecksum( void ) const noexcept;
      NMEA0183_EXPORT virtual COMMUNICATIONS_MODE CommunicationsMode( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual double Double( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual EASTWEST EastOrWest( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual std::string_view Field( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual void Finish( void ) noexcept;
      NMEA0183_EXPORT virtual uint16_t GetNumberOfDataFields( void ) const noexcept;
      NMEA0183_EXPORT virtual int Integer( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual NMEA0183_BOOLEAN IsChecksumBad( int checksum_field_number ) const noexcept;
      NMEA0183_EXPORT virtual LEFTRIGHT LeftOrRight( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual NORTHSOUTH NorthOrSouth( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual REFERENCE Reference( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual time_t Time( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual TRANSDUCER_TYPE TransducerType( int field_number ) const noexcept;
      NMEA0183_EXPORT virtual FAA_MODE FAAMode(int field_number) const noexcept;

      /*
      ** Operators
      */

      NMEA0183_EXPORT operator std::string() const noexcept;
      NMEA0183_EXPORT operator std::string_view() const noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator  = ( SENTENCE const& source ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator  = ( std::string_view source ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( std::string_view source ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( double const value ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( int const value ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( COMMUNICATIONS_MODE const mode ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( EASTWEST const easting ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( LATLONG const& source ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( NMEA0183_BOOLEAN const boolean ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( NORTHSOUTH const northing ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( time_t const time ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( TRANSDUCER_TYPE const transducer ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( LEFTRIGHT const left_or_right ) noexcept;
      NMEA0183_EXPORT virtual SENTENCE const& operator += ( REFERENCE const a_reference ) noexcept;
};

#endif // SENTENCE_CLASS_HEADER
