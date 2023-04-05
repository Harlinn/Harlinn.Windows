/*
Copyright 2015 Esri

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

A local copy of the license and additional notices are located with the
source distribution at:

http://github.com/Esri/lerc/

Contributors:  Thomas Maurer
*/

#pragma once

#include <cstring>
#include <vector>
#include "include/Lerc_types.h"
#include "BitMask.h"
#include "Lerc2.h"

#ifdef _MSC_VER
#ifdef HAVE_LERC1_DECODE
#include "Lerc1Decode/CntZImage.h"
#endif
#endif


NAMESPACE_LERC_START

#ifdef HAVE_LERC1_DECODE
  class CntZImage;
#endif

  class Lerc
  {
  public:
    Lerc() {}
    ~Lerc() {}

    // data types supported by Lerc
    enum DataType { DT_Char, DT_Byte, DT_Short, DT_UShort, DT_Int, DT_UInt, DT_Float, DT_Double, DT_Undefined };

    // all functions are provided in 2 flavors
    // - using void pointers to the image data, can be called on a Lerc lib or dll
    // - data templated, can be called if compiled together


    // Encode

    // if more than 1 band, the outgoing Lerc blob has the single band Lerc blobs concatenated; 
    // or, if you have multiple values per pixel and stored as [RGB, RGB, ... ], then set nDim accordingly (e.g., 3)

    // computes the number of bytes needed to allocate the buffer, accurate to the byte;
    // does not encode the image data, but uses statistics and formulas to compute the buffer size needed;
    // this function is optional, you can also use a buffer large enough to call Encode() directly, 
    // or, if encoding a batch of same width / height tiles, call this function once, double the buffer size, and
    // then just call Encode() on all tiles;

    HLERC_EXPORT static ErrCode ComputeCompressedSize(
      const void* pData,               // raw image data, row by row, band by band
      int version,                     // 2 = v2.2, 3 = v2.3, 4 = v2.4
      DataType dt,                     // data type, char to double
      int nDim,                        // number of values per pixel
      int nCols,                       // number of cols
      int nRows,                       // number of rows
      int nBands,                      // number of bands
      int nMasks,                      // number of masks (0, 1, or nBands)
      const Byte* pValidBytes,         // masks (size = nMasks * nRows * nCols)
      double maxZErr,                  // max coding error per pixel, defines the precision
      unsigned int& numBytesNeeded);   // size of outgoing Lerc blob

    // encodes or compresses the image data into the buffer

    HLERC_EXPORT static ErrCode Encode(
      const void* pData,               // raw image data, row by row, band by band
      int version,                     // 2 = v2.2, 3 = v2.3, 4 = v2.4
      DataType dt,                     // data type, char to double
      int nDim,                        // number of values per pixel
      int nCols,                       // number of cols
      int nRows,                       // number of rows
      int nBands,                      // number of bands
      int nMasks,                      // number of masks (0, 1, or nBands)
      const Byte* pValidBytes,         // masks (size = nMasks * nRows * nCols)
      double maxZErr,                  // max coding error per pixel, defines the precision
      Byte* pBuffer,                   // buffer to write to, function fails if buffer too small
      unsigned int numBytesBuffer,     // buffer size
      unsigned int& numBytesWritten);  // num bytes written to buffer


    // Decode

    struct LercInfo
    {
      int version,        // Lerc version number (0 for old Lerc1, 1 to 4 for Lerc 2.1 to 2.4)
        nDim,             // number of values per pixel
        nCols,            // number of columns
        nRows,            // number of rows
        numValidPixel,    // number of valid pixels
        nBands,           // number of bands
        blobSize,         // total blob size in bytes
        nMasks;           // number of masks (0, 1, or nBands)
      DataType dt;        // data type (float only for old Lerc1)
      double zMin,        // min pixel value, over all data values
        zMax,             // max pixel value, over all data values
        maxZError;        // maxZError used for encoding

      void RawInit()  { memset(this, 0, sizeof(struct LercInfo)); }
    };

    // again, this function is optional;
    // call it on a Lerc blob to get the above struct returned, from this the data arrays
    // can be constructed before calling Decode();
    // same as above, for a batch of Lerc blobs of the same kind, you can call this function on 
    // the first blob, get the info, and on the other Lerc blobs just call Decode();
    // this function is very fast on (newer) Lerc2 blobs as it only reads the blob headers;

    // Remark on param numBytesBlob. Usually it is known, either the file size of the blob written to disk, 
    // or the size of the blob transmitted. It should be accurate for 2 reasons:
    // _ function finds out how many single band Lerc blobs are concatenated
    // _ function checks for truncated file or blob
    // It is OK to pass numBytesBlob too large as long as there is no other (valid) Lerc blob following next.
    // If in doubt, check the code in Lerc::GetLercInfo(...) for the exact logic. 

    HLERC_EXPORT static ErrCode GetLercInfo(const Byte* pLercBlob,       // Lerc blob to decode
                               unsigned int numBytesBlob,   // size of Lerc blob in bytes
                               struct LercInfo& lercInfo);

    // setup outgoing arrays accordingly, then call Decode()

    HLERC_EXPORT static ErrCode Decode(
      const Byte* pLercBlob,           // Lerc blob to decode
      unsigned int numBytesBlob,       // size of Lerc blob in bytes
      int nMasks,                      // number of masks (0, 1, or nBands)
      Byte* pValidBytes,               // masks (fails if not big enough to take the masks decoded, fills with 1 if all valid)
      int nDim,                        // number of values per pixel
      int nCols,                       // number of cols
      int nRows,                       // number of rows
      int nBands,                      // number of bands
      DataType dt,                     // data type of outgoing array
      void* pData);                    // outgoing data bands


    HLERC_EXPORT static ErrCode ConvertToDouble(
      const void* pDataIn,             // pixel data of image tile of data type dt (< double)
      DataType dt,                     // data type of input data
      size_t nDataValues,              // total number of data values (nDim * nCols * nRows * nBands)
      double* pDataOut);               // pixel data converted to double


    // same as functions above, but data templated instead of using void pointers

    template<class T> static ErrCode ComputeCompressedSizeTempl(
        const T* pData,                  // raw image data, row by row, band by 
        int version,                     // 2 = v2.2, 3 = v2.3, 4 = v2.4
        int nDim,                        // number of values per pixel
        int nCols,                       // number of cols
        int nRows,                       // number of rows
        int nBands,                      // number of bands
        int nMasks,                      // number of masks (0, 1, or nBands)
        const Byte* pValidBytes,         // masks (size = nMasks * nRows * nCols)
        double maxZErr,                  // max coding error per pixel, defines the precision
        unsigned int& numBytesNeeded )         // size of outgoing Lerc blob
#ifdef _MSC_VER
    {
        numBytesNeeded = 0;

        if ( !pData || nDim <= 0 || nCols <= 0 || nRows <= 0 || nBands <= 0 || maxZErr < 0 )
            return ErrCode::WrongParam;

        if ( !( nMasks == 0 || nMasks == 1 || nMasks == nBands ) || ( nMasks > 0 && !pValidBytes ) )
            return ErrCode::WrongParam;

        unsigned int numBytesWritten = 0;

        return EncodeInternal( pData, version, nDim, nCols, nRows, nBands, nMasks, pValidBytes, maxZErr,
            numBytesNeeded, nullptr, 0, numBytesWritten );
    }
#else
        ;
#endif

    template<class T> static ErrCode EncodeTempl(
        const T* pData,                  // raw image data, row by row, band by band
        int version,                     // 2 = v2.2, 3 = v2.3, 4 = v2.4
        int nDim,                        // number of values per pixel
        int nCols,                       // number of cols
        int nRows,                       // number of rows
        int nBands,                      // number of bands
        int nMasks,                      // number of masks (0, 1, or nBands)
        const Byte* pValidBytes,         // masks (size = nMasks * nRows * nCols)
        double maxZErr,                  // max coding error per pixel, defines the precision
        Byte* pBuffer,                   // buffer to write to, function will fail if buffer too small
        unsigned int numBytesBuffer,     // buffer size
        unsigned int& numBytesWritten )  // num bytes written to buffer
#ifdef _MSC_VER
    {
        numBytesWritten = 0;

        if ( !pData || nDim <= 0 || nCols <= 0 || nRows <= 0 || nBands <= 0 || maxZErr < 0 || !pBuffer || !numBytesBuffer )
            return ErrCode::WrongParam;

        if ( !( nMasks == 0 || nMasks == 1 || nMasks == nBands ) || ( nMasks > 0 && !pValidBytes ) )
            return ErrCode::WrongParam;

        unsigned int numBytesNeeded = 0;

        return EncodeInternal( pData, version, nDim, nCols, nRows, nBands, nMasks, pValidBytes, maxZErr,
            numBytesNeeded, pBuffer, numBytesBuffer, numBytesWritten );
    }
#else
        ;
#endif

    template<class T> static ErrCode DecodeTempl(
          T* pData,                        // outgoing data bands
          const Byte* pLercBlob,           // Lerc blob to decode
          unsigned int numBytesBlob,       // size of Lerc blob in bytes
          int nDim,                        // number of values per pixel
          int nCols,                       // number of cols
          int nRows,                       // number of rows
          int nBands,                      // number of bands
          int nMasks,                      // number of masks (0, 1, or nBands)
          Byte* pValidBytes)              // masks (fails if not big enough to take the masks decoded, fills with 1 if all valid)
#ifdef _MSC_VER
        {
            if ( !pData || nDim <= 0 || nCols <= 0 || nRows <= 0 || nBands <= 0 || !pLercBlob || !numBytesBlob )
                return ErrCode::WrongParam;

            if ( !( nMasks == 0 || nMasks == 1 || nMasks == nBands ) || ( nMasks > 0 && !pValidBytes ) )
                return ErrCode::WrongParam;

            const Byte* pByte = pLercBlob;
            Lerc2::HeaderInfo hdInfo;
            bool bHasMask = false;

            if ( Lerc2::GetHeaderInfo( pByte, numBytesBlob, hdInfo, bHasMask ) && hdInfo.version >= 1 )    // if Lerc2
            {
                LercInfo lercInfo;
                ErrCode errCode = GetLercInfo( pLercBlob, numBytesBlob, lercInfo );    // fast for Lerc2
                if ( errCode != ErrCode::Ok )
                    return errCode;

                const int nMasksEncoded = lercInfo.nMasks;    // 0, 1, or nBands

                if ( nMasks < nMasksEncoded )
                    return ErrCode::WrongParam;

                size_t nBytesRemaining = numBytesBlob;
                Lerc2 lerc2;
                BitMask bitMask;

                for ( int iBand = 0; iBand < nBands; iBand++ )
                {
                    if ( ( (size_t)( pByte - pLercBlob ) < numBytesBlob ) && Lerc2::GetHeaderInfo( pByte, nBytesRemaining, hdInfo, bHasMask ) )
                    {
                        if ( hdInfo.nDim != nDim || hdInfo.nCols != nCols || hdInfo.nRows != nRows )
                            return ErrCode::Failed;

                        if ( ( pByte - pLercBlob ) + (size_t)hdInfo.blobSize > numBytesBlob )
                            return ErrCode::BufferTooSmall;

                        size_t nPix = (size_t)iBand * nRows * nCols;
                        T* arr = pData + nPix * nDim;

                        bool bGetMask = iBand < nMasks;

                        if ( bGetMask && !bitMask.SetSize( nCols, nRows ) )
                            return ErrCode::Failed;

                        if ( !lerc2.Decode( &pByte, nBytesRemaining, arr, bGetMask ? bitMask.Bits( ) : nullptr ) )
                            return ErrCode::Failed;

                        if ( bGetMask && !Convert( bitMask, pValidBytes + nPix ) )
                            return ErrCode::Failed;
                    }
                }  // iBand
            }  // Lerc2

            else    // might be old Lerc1
            {
#ifdef HAVE_LERC1_DECODE
                unsigned int numBytesHeaderBand0 = CntZImage::computeNumBytesNeededToReadHeader( false );
                unsigned int numBytesHeaderBand1 = CntZImage::computeNumBytesNeededToReadHeader( true );
                Byte* pByte1 = const_cast<Byte*>( pLercBlob );
                CntZImage zImg;

                for ( int iBand = 0; iBand < nBands; iBand++ )
                {
                    unsigned int numBytesHeader = iBand == 0 ? numBytesHeaderBand0 : numBytesHeaderBand1;
                    if ( (size_t)( pByte - pLercBlob ) + numBytesHeader > numBytesBlob )
                        return ErrCode::BufferTooSmall;

                    bool onlyZPart = iBand > 0;
                    if ( !zImg.read( &pByte1, 1e12, false, onlyZPart ) )
                        return ErrCode::Failed;

                    if ( zImg.getWidth( ) != nCols || zImg.getHeight( ) != nRows )
                        return ErrCode::Failed;

                    size_t nPix = (size_t)iBand * nRows * nCols;
                    T* arr = pData + nPix;
                    Byte* pDst = iBand < nMasks ? pValidBytes + nPix : nullptr;

                    if ( !Convert( zImg, arr, pDst, iBand == 0 ) )
                        return ErrCode::Failed;
                }
#else
                return ErrCode::Failed;
#endif
            }

            return ErrCode::Ok;
        }
#else
      ;
#endif

  private:

      template<class T> static ErrCode EncodeInternal(
          const T* pData,                  // raw image data, row by row, band by band
          int version,                     // 2 = v2.2, 3 = v2.3, 4 = v2.4
          int nDim,                        // number of values per pixel
          int nCols,                       // number of cols
          int nRows,                       // number of rows
          int nBands,                      // number of bands
          int nMasks,                      // number of masks (0, 1, or nBands)
          const Byte* pValidBytes,         // masks (size = nMasks * nRows * nCols)
          double maxZErr,                  // max coding error per pixel, defines the precision
          unsigned int& numBytesNeeded,    // size of outgoing Lerc blob
          Byte* pBuffer,                   // buffer to write to, function will fail if buffer too small
          unsigned int numBytesBuffer,     // buffer size
          unsigned int& numBytesWritten )   // num bytes written to buffer
#ifdef _MSC_VER
      {
          numBytesNeeded = 0;
          numBytesWritten = 0;

          Lerc2 lerc2;
          if ( version >= 0 && !lerc2.SetEncoderToOldVersion( version ) )
              return ErrCode::WrongParam;

          Byte* pDst = pBuffer;

          const size_t nPix = (size_t)nCols * nRows;
          const size_t nElem = nPix * nDim;

          const Byte* pPrevByteMask = nullptr;
          std::vector<T> dataBuffer;
          std::vector<Byte> maskBuffer, prevMaskBuffer;
          BitMask bitMask;

          // loop over the bands
          for ( int iBand = 0; iBand < nBands; iBand++ )
          {
              bool bEncMsk = ( iBand == 0 );

              // using the proper section of valid bytes, check this band for NaN
              const T* arr = pData + nElem * iBand;
              const Byte* pByteMask = ( nMasks > 0 ) ? ( pValidBytes + ( ( nMasks > 1 ) ? nPix * iBand : 0 ) ) : nullptr;

              ErrCode errCode = CheckForNaN( arr, nDim, nCols, nRows, pByteMask );
              if ( errCode != ErrCode::Ok && errCode != ErrCode::NaN )
                  return errCode;

              if ( errCode == ErrCode::NaN )    // found NaN values
              {
                  if ( !Resize( dataBuffer, nElem ) || !Resize( maskBuffer, nPix ) )
                      return ErrCode::Failed;

                  memcpy( &dataBuffer[0], arr, nElem * sizeof( T ) );
                  pByteMask ? memcpy( &maskBuffer[0], pByteMask, nPix ) : memset( &maskBuffer[0], 1, nPix );

                  if ( !ReplaceNaNValues( dataBuffer, maskBuffer, nDim, nCols, nRows ) )
                      return ErrCode::Failed;

                  if ( iBand > 0 && MasksDiffer( &maskBuffer[0], pPrevByteMask, nPix ) )
                      bEncMsk = true;

                  if ( iBand < nBands - 1 )
                  {
                      // keep current mask as new previous band mask
                      prevMaskBuffer = maskBuffer;
                      pPrevByteMask = &prevMaskBuffer[0];
                  }

                  arr = &dataBuffer[0];
                  pByteMask = &maskBuffer[0];
              }

              else    // no NaN in this band, the common case
              {
                  if ( iBand > 0 && MasksDiffer( pByteMask, pPrevByteMask, nPix ) )
                      bEncMsk = true;

                  pPrevByteMask = pByteMask;
              }

              if ( bEncMsk )
              {
                  if ( pByteMask && !Convert( pByteMask, nCols, nRows, bitMask ) )
                      return ErrCode::Failed;

                  if ( !lerc2.Set( nDim, nCols, nRows, pByteMask ? bitMask.Bits( ) : nullptr ) )
                      return ErrCode::Failed;
              }

              unsigned int nBytes = lerc2.ComputeNumBytesNeededToWrite( arr, maxZErr, bEncMsk );
              if ( nBytes <= 0 )
                  return ErrCode::Failed;

              numBytesNeeded += nBytes;

              if ( pBuffer )
              {
                  if ( (size_t)( pDst - pBuffer ) + nBytes > numBytesBuffer )    // check we have enough space left
                      return ErrCode::BufferTooSmall;

                  if ( !lerc2.Encode( arr, &pDst ) )
                      return ErrCode::Failed;
              }
          }

          numBytesWritten = (unsigned int)( pDst - pBuffer );
          return ErrCode::Ok;
      }
#else
          ;
#endif

#ifdef HAVE_LERC1_DECODE
    template<class T> static bool Convert( const CntZImage& zImg, T* arr, Byte* pByteMask, bool bMustFillMask )
#ifdef _MSC_VER
    {
        if ( !arr || !zImg.getSize( ) )
            return false;

        const bool fltPnt = ( typeid( *arr ) == typeid( double ) ) || ( typeid( *arr ) == typeid( float ) );

        int h = zImg.getHeight( );
        int w = zImg.getWidth( );

        const CntZ* srcPtr = zImg.getData( );
        T* dstPtr = arr;
        int num = w * h;

        if ( pByteMask )
        {
            memset( pByteMask, 0, num );

            for ( int k = 0; k < num; k++ )
            {
                if ( srcPtr->cnt > 0 )
                {
                    *dstPtr = fltPnt ? (T)srcPtr->z : (T)floor( srcPtr->z + 0.5 );
                    pByteMask[k] = 1;
                }

                srcPtr++;
                dstPtr++;
            }
        }
        else
        {
            for ( int k = 0; k < num; k++ )
            {
                if ( srcPtr->cnt > 0 )
                {
                    *dstPtr = fltPnt ? (T)srcPtr->z : (T)floor( srcPtr->z + 0.5 );
                }
                else if ( bMustFillMask )
                    return false;

                srcPtr++;
                dstPtr++;
            }
        }

        return true;
    }
#else
        ;
#endif
#endif
    template<class T> static ErrCode ConvertToDoubleTempl(const T* pDataIn, size_t nDataValues, double* pDataOut)
#ifdef _MSC_VER
    {
        if ( !pDataIn || !nDataValues || !pDataOut )
            return ErrCode::WrongParam;

        for ( size_t k = 0; k < nDataValues; k++ )
            pDataOut[k] = pDataIn[k];

        return ErrCode::Ok;
    }
#else
        ;
#endif

    template<class T> static ErrCode CheckForNaN(const T* arr, int nDim, int nCols, int nRows, const Byte* pByteMask)
#ifdef _MSC_VER
    {
        if ( !arr || nDim <= 0 || nCols <= 0 || nRows <= 0 )
            return ErrCode::WrongParam;

        if ( typeid( T ) != typeid( double ) && typeid( T ) != typeid( float ) )
            return ErrCode::Ok;

        for ( size_t k = 0, i = 0; i < (size_t)nRows; i++ )
        {
            bool bFoundNaN = false;
            const T* rowArr = &( arr[i * nCols * nDim] );

            if ( !pByteMask )    // all valid
            {
                size_t num = (size_t)nCols * nDim;
                for ( size_t m = 0; m < num; m++ )
                    if ( std::isnan( (double)rowArr[m] ) )
                        bFoundNaN = true;
            }
            else    // not all valid
            {
                for ( size_t n = 0, j = 0; j < (size_t)nCols; j++, k++, n += nDim )
                    if ( pByteMask[k] )
                    {
                        for ( int m = 0; m < nDim; m++ )
                            if ( std::isnan( (double)rowArr[n + m] ) )
                                bFoundNaN = true;
                    }
            }

            if ( bFoundNaN )
                return ErrCode::NaN;
        }

        return ErrCode::Ok;
    }
#else
        ;
#endif

    template<class T> static bool ReplaceNaNValues(std::vector<T>& dataBuffer, std::vector<Byte>& maskBuffer, int nDim, int nCols, int nRows)
#ifdef _MSC_VER
    {
        if ( nDim <= 0 || nCols <= 0 || nRows <= 0 || dataBuffer.size( ) != (size_t)nDim * nCols * nRows || maskBuffer.size( ) != (size_t)nCols * nRows )
            return false;

        bool bIsFloat = ( typeid( T ) == typeid( float ) );
        const T noDataValue = (T)( bIsFloat ? -FLT_MAX : -DBL_MAX );

        for ( size_t k = 0, i = 0; i < (size_t)nRows; i++ )
        {
            T* rowArr = &( dataBuffer[i * nCols * nDim] );

            for ( size_t n = 0, j = 0; j < (size_t)nCols; j++, k++, n += nDim )
            {
                if ( maskBuffer[k] )
                {
                    int cntNaN = 0;

                    for ( int m = 0; m < nDim; m++ )
                        if ( std::isnan( (double)rowArr[n + m] ) )
                        {
                            cntNaN++;
                            rowArr[n + m] = noDataValue;
                        }

                    if ( cntNaN == nDim )
                        maskBuffer[k] = 0;
                }
            }
        }

        return true;
    }

#else
        ;
#endif

    template<class T> static bool Resize(std::vector<T>& buffer, size_t nElem)
#ifdef _MSC_VER
    {
        try
        {
            buffer.resize( nElem );
        }
        catch ( ... )
        {
            return false;
        }
        return true;
    }

#else
        ;
#endif

    HLERC_EXPORT bool static Convert(const Byte* pByteMask, int nCols, int nRows, BitMask& bitMask);
    HLERC_EXPORT bool static Convert(const BitMask& bitMask, Byte* pByteMask);
    HLERC_EXPORT bool static MasksDiffer(const Byte* p0, const Byte* p1, size_t n);
  };
NAMESPACE_LERC_END
