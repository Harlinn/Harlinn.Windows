/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_parse_utils__
#define __dng_parse_utils__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_flags.h"
#include "dng_types.h"
#include "dng_stream.h"
#include "dng_string.h"
#include "dng_matrix.h"

/*****************************************************************************/

#if qDNGValidate

/*****************************************************************************/

DNG_EXPORT const char * LookupParentCode (uint32 parentCode);

/*****************************************************************************/

DNG_EXPORT const char * LookupTagCode (uint32 parentCode,
							uint32 tagCode);

/*****************************************************************************/

DNG_EXPORT const char * LookupTagType (uint32 tagType);

/*****************************************************************************/

DNG_EXPORT const char * LookupNewSubFileType (uint32 key);

DNG_EXPORT const char * LookupCompression (uint32 key);

DNG_EXPORT const char * LookupPredictor (uint32 key);

DNG_EXPORT const char * LookupSampleFormat (uint32 key);

DNG_EXPORT const char * LookupPhotometricInterpretation (uint32 key);

DNG_EXPORT const char * LookupOrientation (uint32 key);

DNG_EXPORT const char * LookupResolutionUnit (uint32 key);

DNG_EXPORT const char * LookupCFAColor (uint32 key);

DNG_EXPORT const char * LookupSensingMethod (uint32 key);

DNG_EXPORT const char * LookupExposureProgram (uint32 key);

DNG_EXPORT const char * LookupMeteringMode (uint32 key);

DNG_EXPORT const char * LookupLightSource (uint32 key);

DNG_EXPORT const char * LookupColorSpace (uint32 key);

DNG_EXPORT const char * LookupFileSource (uint32 key);

DNG_EXPORT const char * LookupSceneType (uint32 key);

DNG_EXPORT const char * LookupCustomRendered (uint32 key);

DNG_EXPORT const char * LookupExposureMode (uint32 key);

DNG_EXPORT const char * LookupWhiteBalance (uint32 key);

DNG_EXPORT const char * LookupSceneCaptureType (uint32 key);

DNG_EXPORT const char * LookupGainControl (uint32 key);

DNG_EXPORT const char * LookupContrast (uint32 key);

DNG_EXPORT const char * LookupSaturation (uint32 key);

DNG_EXPORT const char * LookupSharpness (uint32 key);

DNG_EXPORT const char * LookupSubjectDistanceRange (uint32 key);

DNG_EXPORT const char * LookupComponent (uint32 key);

DNG_EXPORT const char * LookupCFALayout (uint32 key);

DNG_EXPORT const char * LookupMakerNoteSafety (uint32 key);

DNG_EXPORT const char * LookupColorimetricReference (uint32 key);

DNG_EXPORT const char * LookupPreviewColorSpace (uint32 key);

DNG_EXPORT const char * LookupJPEGMarker (uint32 key);

DNG_EXPORT const char * LookupSensitivityType (uint32 key);

DNG_EXPORT const char * LookupDepthFormat (uint32 key);

DNG_EXPORT const char * LookupDepthUnits (uint32 key);

DNG_EXPORT const char * LookupDepthMeasureType (uint32 key);

/*****************************************************************************/

DNG_EXPORT void DumpHexAscii (dng_stream &stream,
				   uint32 count);
				   
DNG_EXPORT void DumpHexAscii (const uint8 *buf,
				   uint32 count);

DNG_EXPORT void DumpXMP (dng_stream &stream,
			  uint32 count);

DNG_EXPORT void DumpString (const dng_string &s);

DNG_EXPORT void DumpTagValues (dng_stream &stream,
					const char *entry_name,
					uint32 parentCode,
					uint32 tagCode,
					uint32 tagType,
					uint32 tagCount,
					const char *tag_name = NULL);
					
DNG_EXPORT void DumpMatrix (const dng_matrix &m);

DNG_EXPORT void DumpVector (const dng_vector &v);

DNG_EXPORT void DumpDateTime (const dng_date_time &dt);

DNG_EXPORT void DumpExposureTime (real64 x);

DNG_EXPORT void DumpFingerprint (const dng_fingerprint &p);

DNG_EXPORT void DumpHueSatMap (dng_stream &stream,
				    uint32 hues,
					uint32 sats,
					uint32 vals,
					bool skipSat0);

/*****************************************************************************/

#endif

/*****************************************************************************/

DNG_EXPORT bool CheckTagType (uint32 parentCode,
				   uint32 tagCode,
				   uint32 tagType,
				   uint16 validType0,
				   uint16 validType1 = 0,
				   uint16 validType2 = 0,
				   uint16 validType3 = 0);

DNG_EXPORT bool CheckTagCount (uint32 parentCode,
					uint32 tagCode,
				    uint32 tagCount,
				    uint32 minCount,
				    uint32 maxCount = 0);
				    		
DNG_EXPORT bool CheckColorImage (uint32 parentCode,
					  uint32 tagCode,
				      uint32 colorPlanes);
				      
DNG_EXPORT bool CheckMainIFD (uint32 parentCode,
				   uint32 tagCode,
				   uint32 newSubFileType);

DNG_EXPORT bool CheckRawIFD (uint32 parentCode,
				  uint32 tagCode,
				  uint32 photometricInterpretation);

DNG_EXPORT bool CheckCFA (uint32 parentCode,
			   uint32 tagCode,
		       uint32 photometricInterpretation);

/*****************************************************************************/

DNG_EXPORT void ParseStringTag (dng_stream &stream,
					 uint32 parentCode,
					 uint32 tagCode,
				     uint32 tagCount,
				     dng_string &s,
				     bool trimBlanks = true);
				    	  
DNG_EXPORT void ParseDualStringTag (dng_stream &stream,
					 	 uint32 parentCode,
					 	 uint32 tagCode,
				     	 uint32 tagCount,
				     	 dng_string &s1,
				     	 dng_string &s2);

DNG_EXPORT void ParseEncodedStringTag (dng_stream &stream,
							uint32 parentCode,
							uint32 tagCode,
				    		uint32 tagCount,
				    		dng_string &s);
				    		
DNG_EXPORT bool ParseMatrixTag (dng_stream &stream,
					 uint32 parentCode,
					 uint32 tagCode,
					 uint32 tagType,
					 uint32 tagCount,
					 uint32 rows,
					 uint32 cols,
					 dng_matrix &m);
				    		
DNG_EXPORT bool ParseVectorTag (dng_stream &stream,
					 uint32 parentCode,
					 uint32 tagCode,
					 uint32 tagType,
					 uint32 tagCount,
					 uint32 count,
					 dng_vector &v);
					 
DNG_EXPORT bool ParseDateTimeTag (dng_stream &stream,
					   uint32 parentCode,
					   uint32 tagCode,
					   uint32 tagType,
					   uint32 tagCount,
					   dng_date_time &dt);
				    		
/*****************************************************************************/

#endif
	
/*****************************************************************************/
