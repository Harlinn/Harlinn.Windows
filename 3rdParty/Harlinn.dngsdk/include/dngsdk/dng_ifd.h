/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/** \file
 *  DNG image file directory support.
 */

/*****************************************************************************/

#ifndef __dng_ifd__
#define __dng_ifd__

/*****************************************************************************/

#include "dng_fingerprint.h"
#include "dng_negative.h"
#include "dng_rect.h"
#include "dng_shared.h"
#include "dng_stream.h"
#include "dng_string.h"
#include "dng_sdk_limits.h"
#include "dng_tag_values.h"

/*****************************************************************************/

class dng_preview_info
	{
	
	public:
	
		bool fIsPrimary;
		
		dng_string fApplicationName;
		
		dng_string fApplicationVersion;
		
		dng_string fSettingsName;
		
		dng_fingerprint fSettingsDigest;
		
		PreviewColorSpaceEnum fColorSpace;
		
		dng_string fDateTime;
		
		real64 fRawToPreviewGain;
		
		uint32 fCacheVersion;
		
	public:
	
		DNG_EXPORT dng_preview_info ();
		
		DNG_EXPORT ~dng_preview_info ();
		
	};

/*****************************************************************************/

/// \brief Container for a single image file directory of a digital negative.
///
/// See \ref spec_dng "DNG 1.1.0 specification" for documentation of specific tags.

class dng_ifd
	{
	
	public:
	
		bool fUsesNewSubFileType;
	
		uint32 fNewSubFileType;
		
		uint32 fImageWidth;
		uint32 fImageLength;
		
		uint32 fBitsPerSample [kMaxSamplesPerPixel];
		
		uint32 fCompression;
		
		uint32 fPredictor;
		
		uint32 fPhotometricInterpretation;
		
		uint32 fFillOrder;
		
		uint32 fOrientation;
		uint32 fOrientationType;
		uint64 fOrientationOffset;
		bool   fOrientationBigEndian;
		
		uint32 fSamplesPerPixel;
		
		uint32 fPlanarConfiguration;
		
		real64 fXResolution;
		real64 fYResolution;
		
		uint32 fResolutionUnit;
		
		bool fUsesStrips;
		bool fUsesTiles;

		uint32 fTileWidth;
		uint32 fTileLength;
		
		enum
			{
			kMaxTileInfo = 32
			};
		
		uint32 fTileOffsetsType;
		uint32 fTileOffsetsCount;
		uint64 fTileOffsetsOffset;
		uint64 fTileOffset [kMaxTileInfo];
		
		uint32 fTileByteCountsType;
		uint32 fTileByteCountsCount;
		uint64 fTileByteCountsOffset;
		uint32 fTileByteCount [kMaxTileInfo];

		uint32 fSubIFDsCount;
		uint64 fSubIFDsOffset;
		
		uint32 fExtraSamplesCount;
		uint32 fExtraSamples [kMaxSamplesPerPixel];
		
		uint32 fSampleFormat [kMaxSamplesPerPixel];
		
		uint32 fJPEGTablesCount;
		uint64 fJPEGTablesOffset;
		
		uint64 fJPEGInterchangeFormat;
		uint32 fJPEGInterchangeFormatLength;

		real64 fYCbCrCoefficientR;
		real64 fYCbCrCoefficientG;
		real64 fYCbCrCoefficientB;
		
		uint32 fYCbCrSubSampleH;
		uint32 fYCbCrSubSampleV;
		
		uint32 fYCbCrPositioning;
		
		real64 fReferenceBlackWhite [6];
		
		uint32 fCFARepeatPatternRows;
		uint32 fCFARepeatPatternCols;
		
		uint8 fCFAPattern [kMaxCFAPattern] [kMaxCFAPattern];
		
		uint8 fCFAPlaneColor [kMaxColorPlanes];
		
		uint32 fCFALayout;
		
		uint32 fLinearizationTableType;
		uint32 fLinearizationTableCount;
		uint64 fLinearizationTableOffset;
		
		uint32 fBlackLevelRepeatRows;
		uint32 fBlackLevelRepeatCols;
		
		real64 fBlackLevel [kMaxBlackPattern] [kMaxBlackPattern] [kMaxSamplesPerPixel];
		
		uint32 fBlackLevelDeltaHType;
		uint32 fBlackLevelDeltaHCount;
		uint64 fBlackLevelDeltaHOffset;
		
		uint32 fBlackLevelDeltaVType;
		uint32 fBlackLevelDeltaVCount;
		uint64 fBlackLevelDeltaVOffset;
		
		real64 fWhiteLevel [kMaxSamplesPerPixel];
		
		dng_urational fDefaultScaleH;
		dng_urational fDefaultScaleV;
		
		dng_urational fBestQualityScale;
		
		dng_urational fDefaultCropOriginH;
		dng_urational fDefaultCropOriginV;
		
		dng_urational fDefaultCropSizeH;
		dng_urational fDefaultCropSizeV;
		
		dng_urational fDefaultUserCropT;
		dng_urational fDefaultUserCropL;
		dng_urational fDefaultUserCropB;
		dng_urational fDefaultUserCropR;
		
		uint32 fBayerGreenSplit;
		
		dng_urational fChromaBlurRadius;
		
		dng_urational fAntiAliasStrength;
		
		dng_rect fActiveArea;
		
		uint32   fMaskedAreaCount;
		dng_rect fMaskedArea [kMaxMaskedAreas];
		
		uint32 fRowInterleaveFactor;
		
		uint32 fSubTileBlockRows;
		uint32 fSubTileBlockCols;
		
		dng_preview_info fPreviewInfo;
		
		uint32 fOpcodeList1Count;
		uint64 fOpcodeList1Offset;
		
		uint32 fOpcodeList2Count;
		uint64 fOpcodeList2Offset;
		
		uint32 fOpcodeList3Count;
		uint64 fOpcodeList3Offset;

		dng_noise_profile fNoiseProfile;
  
        dng_string fEnhanceParams;
        
        dng_urational fBaselineSharpness;
        
        dng_urational fNoiseReductionApplied;
        
		bool fLosslessJPEGBug16;
		
		uint32 fSampleBitShift;
		
		uint64 fThisIFD;
		uint64 fNextIFD;
		
		int32 fCompressionQuality;
		
		bool fPatchFirstJPEGByte;

	public:
	
		DNG_EXPORT dng_ifd ();
		
		DNG_EXPORT virtual ~dng_ifd ();

		DNG_EXPORT virtual dng_ifd * Clone () const;
		
		DNG_EXPORT virtual bool ParseTag (dng_stream &stream,
							   uint32 parentCode,
							   uint32 tagCode,
							   uint32 tagType,
							   uint32 tagCount,
							   uint64 tagOffset);
							   
		DNG_EXPORT virtual void PostParse ();
		
		DNG_EXPORT virtual bool IsValidDNG (dng_shared &shared,
								 uint32 parentCode);

		dng_rect Bounds () const
			{
			return dng_rect (0,
							 0,
							 fImageLength,
							 fImageWidth);
			}
					      		 
		DNG_EXPORT uint32 TilesAcross () const;
		
		DNG_EXPORT uint32 TilesDown () const;
		
		DNG_EXPORT uint32 TilesPerImage () const;
		
		DNG_EXPORT dng_rect TileArea (uint32 rowIndex,
						   uint32 colIndex) const;
						   
		DNG_EXPORT virtual uint32 TileByteCount (const dng_rect &tile) const;
		
		DNG_EXPORT void SetSingleStrip ();
		
		DNG_EXPORT void FindTileSize (uint32 bytesPerTile = 128 * 1024,
						   uint32 cellH = 16,
						   uint32 cellV = 16);
		
		DNG_EXPORT void FindStripSize (uint32 bytesPerStrip = 128 * 1024,
						    uint32 cellV = 16);
		
		DNG_EXPORT virtual uint32 PixelType () const;
		
		DNG_EXPORT virtual bool IsBaselineJPEG () const;
		
		DNG_EXPORT virtual bool CanRead () const;
		
		DNG_EXPORT virtual void ReadImage (dng_host &host,
								dng_stream &stream,
								dng_image &image,
								dng_jpeg_image *jpegImage = NULL,
								dng_fingerprint *jpegDigest = NULL) const;
			
	protected:
							   
		DNG_EXPORT virtual bool IsValidCFA (dng_shared &shared,
					      		 uint32 parentCode);
					      
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/
