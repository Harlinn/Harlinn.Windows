/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_xmp__
#define __dng_xmp__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_types.h"
#include "dng_xmp_sdk.h"

/*****************************************************************************/

class dng_xmp
	{
	
	protected:
	
		// Sync option bits.
	
		enum
			{
			ignoreXMP		= 1,		// Force XMP values to match non-XMP
			preferXMP 		= 2,		// Prefer XMP values if conflict
			preferNonXMP	= 4,		// Prefer non-XMP values if conflict
			removeXMP		= 8			// Remove XMP value after syncing
			};	
	
		dng_memory_allocator &fAllocator;
	
		dng_xmp_sdk *fSDK;
	
	public:
	
		DNG_EXPORT dng_xmp (dng_memory_allocator &allocator);
		
		DNG_EXPORT dng_xmp (const dng_xmp &xmp);
		
		DNG_EXPORT virtual ~dng_xmp ();
		
		DNG_EXPORT virtual dng_xmp * Clone () const;

        dng_memory_allocator & Allocator () const
            {
            return fAllocator;
            }
	
		DNG_EXPORT void Parse (dng_host &host,
					const void *buffer,
				    uint32 count);

		DNG_EXPORT dng_memory_block * Serialize (bool asPacket = false,
									  uint32 targetBytes = 0,
									  uint32 padBytes = 4096,
									  bool forJPEG = false,
									  bool compact = true) const;
									  
		// Kludge: Due to a bug in Premere Elements 9, we need to pass non-compact XMP
		// to the host, until we drop support for this Premere version.  This bug
		// is fixed in Premere Elements 10 and later.
											  
		dng_memory_block * SerializeNonCompact () const
			{
			return Serialize (false,
							  0,
							  4096,
							  false,
							  false);
			}
											  
		DNG_EXPORT void PackageForJPEG (AutoPtr<dng_memory_block> &stdBlock,
							 AutoPtr<dng_memory_block> &extBlock,
							 dng_string &extDigest) const;
							 
		DNG_EXPORT void MergeFromJPEG (const dng_xmp &xmp);
									  
		DNG_EXPORT bool HasMeta () const;

        void RequireMeta ()
            {
            fSDK->RequireMeta ();
            }

		DNG_EXPORT void * GetPrivateMeta ();
									  
		DNG_EXPORT bool Exists (const char *ns,
					 const char *path) const;
		
		DNG_EXPORT bool HasNameSpace (const char *ns) const;

		DNG_EXPORT bool IteratePaths (IteratePathsCallback *callback,
						   void *callbackData,
						   const char *ns = 0,
						   const char *path = 0);

		DNG_EXPORT void Remove (const char *ns,
				     const char *path);

		DNG_EXPORT void RemoveProperties (const char *ns);
		
		DNG_EXPORT void RemoveEmptyStringOrArray (const char *ns,
									   const char *path);
		
		DNG_EXPORT void RemoveEmptyStringsAndArrays (const char *ns = 0);
		
		DNG_EXPORT void Set (const char *ns,
				  const char *path,
				  const char *text);
				  
		DNG_EXPORT bool GetString (const char *ns,
						const char *path,
						dng_string &s) const;
				  
		DNG_EXPORT void SetString (const char *ns,
						const char *path,
						const dng_string &s);
						
		DNG_EXPORT bool GetStringList (const char *ns,
						    const char *path,
						    dng_string_list &list) const;
				  
		DNG_EXPORT void SetStringList (const char *ns,
						    const char *path,
						    const dng_string_list &list,
						    bool isBag = false);
						
		DNG_EXPORT void SetStructField (const char *ns,
							 const char *path,
						     const char *fieldNS,
							 const char *fieldName,
							 const dng_string &s);

		DNG_EXPORT void SetStructField (const char *ns,
							 const char *path,
						     const char *fieldNS,
							 const char *fieldName,
							 const char *s);
		
		DNG_EXPORT void DeleteStructField (const char *ns,
								const char *path,
								const char *fieldNS,
								const char *fieldName);								
												 				 	 
		DNG_EXPORT bool GetStructField (const char *ns,
							 const char *path,
							 const char *fieldNS,
							 const char *fieldName,
							 dng_string &s) const;

		DNG_EXPORT void SetAltLangDefault (const char *ns,
								const char *path,
								const dng_string &s);

		DNG_EXPORT void SetLocalString (const char *ns,
                             const char *path,
                             const dng_local_string &s);
								
		DNG_EXPORT bool GetAltLangDefault (const char *ns,
								const char *path,
								dng_string &s,
                                bool silent = false) const;
								
		DNG_EXPORT bool GetLocalString (const char *ns,
							 const char *path,
							 dng_local_string &s) const;
								
		DNG_EXPORT bool GetBoolean (const char *ns,
						 const char *path,
						 bool &x) const;
						 
		DNG_EXPORT void SetBoolean (const char *ns,
						 const char *path,
						 bool x);
						 
		DNG_EXPORT bool Get_int32 (const char *ns,
						const char *path,
						int32 &x) const;
						 
		DNG_EXPORT void Set_int32 (const char *ns,
						const char *path,
						int32 x,
						bool usePlus = false);
						 
		DNG_EXPORT bool Get_uint32 (const char *ns,
						 const char *path,
						 uint32 &x) const;
						 
		DNG_EXPORT void Set_uint32 (const char *ns,
						 const char *path,
						 uint32 x);
						 
		DNG_EXPORT bool Get_real64 (const char *ns,
					     const char *path,
					     real64 &x) const;
	
		DNG_EXPORT void Set_real64 (const char *ns,
					     const char *path,
					     real64 x,
				         uint32 places = 6,
					     bool trim = true,
					     bool usePlus = false);

		DNG_EXPORT bool Get_urational (const char *ns,
							const char *path,
							dng_urational &r) const;
							
		DNG_EXPORT void Set_urational (const char *ns,
							const char *path,
							const dng_urational &r);
							
		DNG_EXPORT bool Get_srational (const char *ns,
							const char *path,
							dng_srational &r) const;
							
		DNG_EXPORT void Set_srational (const char *ns,
							const char *path,
							const dng_srational &r);
							
		DNG_EXPORT bool GetFingerprint (const char *ns,
							 const char *path,
							 dng_fingerprint &print) const;
					 	 
		DNG_EXPORT void SetFingerprint (const char *ns,
							 const char *path,
							 const dng_fingerprint &print,
							 bool allowInvalid = false);
							 
		DNG_EXPORT void SetVersion2to4 (const char *ns,
							 const char *path,
							 uint32 version);
							   
		DNG_EXPORT dng_fingerprint GetIPTCDigest () const;
		
		DNG_EXPORT void SetIPTCDigest (dng_fingerprint &digest);
		
		DNG_EXPORT void ClearIPTCDigest ();
		
		DNG_EXPORT void IngestIPTC (dng_metadata &metadata,
					     bool xmpIsNewer = false);
			
		DNG_EXPORT void RebuildIPTC (dng_metadata &metadata,
						  dng_memory_allocator &allocator,
						  bool padForTIFF);
		
		DNG_EXPORT virtual void SyncExif (dng_exif &exif,
							   const dng_exif *originalExif = NULL,
							   bool doingUpdateFromXMP = false,
							   bool removeFromXMP = false);
							   
		DNG_EXPORT void ValidateStringList (const char *ns,
							     const char *path);
							   
		DNG_EXPORT void ValidateMetadata ();
		
		DNG_EXPORT void UpdateDateTime (const dng_date_time_info &dt);
		
		DNG_EXPORT void UpdateMetadataDate (const dng_date_time_info &dt);

		DNG_EXPORT void UpdateExifDates (dng_exif &exif,
							  bool removeFromXMP = false);
		
		DNG_EXPORT bool HasOrientation () const;
						   
		DNG_EXPORT dng_orientation GetOrientation () const;
		
		DNG_EXPORT void ClearOrientation ();
						  
		DNG_EXPORT void SetOrientation (const dng_orientation &orientation);
		
		DNG_EXPORT void SyncOrientation (dng_negative &negative,
					   		  bool xmpIsMaster);
			// FIX_ME_API: Backwards compatibility
					   		  
		DNG_EXPORT void SyncOrientation (dng_metadata &metadata,
					   		  bool xmpIsMaster);
					   		  
		DNG_EXPORT void ClearImageInfo ();
		
		DNG_EXPORT void SetImageSize (const dng_point &size);
		
		DNG_EXPORT void SetSampleInfo (uint32 samplesPerPixel,
							uint32 bitsPerSample);
		
		DNG_EXPORT void SetPhotometricInterpretation (uint32 pi);
		
		DNG_EXPORT void SetResolution (const dng_resolution &res);

		DNG_EXPORT void ComposeArrayItemPath (const char *ns,
								   const char *arrayName,
								   int32 itemNumber,
								   dng_string &s) const;
		
		DNG_EXPORT void ComposeStructFieldPath (const char *ns,
								     const char *structName,
								     const char *fieldNS,
									 const char *fieldName,
								     dng_string &s) const;

		DNG_EXPORT int32 CountArrayItems (const char *ns,
		                       const char *path) const;

		DNG_EXPORT void AppendArrayItem (const char *ns,
							  const char *arrayName,
							  const char *itemValue,
							  bool isBag = true,
							  bool propIsStruct = false);

		DNG_EXPORT static dng_string EncodeFingerprint (const dng_fingerprint &f,
											 bool allowInvalid = false);
		
		DNG_EXPORT static dng_fingerprint DecodeFingerprint (const dng_string &s);
							 
#if qDNGXMPDocOps
		
		DNG_EXPORT void DocOpsOpenXMP (const char *srcMIME);
		
		DNG_EXPORT void DocOpsPrepareForSave (const char *srcMIME,
								   const char *dstMIME,
								   bool newPath = true);
								   
		DNG_EXPORT void DocOpsUpdateMetadata (const char *srcMIME);
		
#endif

	protected:
	
		DNG_EXPORT static void TrimDecimal (char *s);

		DNG_EXPORT static dng_string EncodeGPSVersion (uint32 version);
		
		DNG_EXPORT static uint32 DecodeGPSVersion (const dng_string &s);
		
		DNG_EXPORT static dng_string EncodeGPSCoordinate (const dng_string &ref,
							   				   const dng_urational *coord);
							   				   
		DNG_EXPORT static void DecodeGPSCoordinate (const dng_string &s,
										 dng_string &ref,
										 dng_urational *coord);
										 
		DNG_EXPORT static dng_string EncodeGPSDateTime (const dng_string &dateStamp,
											 const dng_urational *timeStamp);
											 
		DNG_EXPORT static void DecodeGPSDateTime (const dng_string &s,
									   dng_string &dateStamp,
									   dng_urational *timeStamp);
									   
		DNG_EXPORT bool SyncString (const char *ns,
						 const char *path,
						 dng_string &s,
						 uint32 options = 0);
						 
		DNG_EXPORT void SyncStringList (const char *ns,
						 	 const char *path,
						 	 dng_string_list &list,
						 	 bool isBag = false,
						 	 uint32 options = 0);

		DNG_EXPORT bool SyncAltLangDefault (const char *ns,
								 const char *path,
								 dng_string &s,
								 uint32 options = 0);
						 
		DNG_EXPORT void Sync_uint32 (const char *ns,
						  const char *path,
						  uint32 &x,
						  bool isDefault = false,
						  uint32 options = 0);
						  
		DNG_EXPORT void Sync_uint32_array (const char *ns,
						   		const char *path,
						   		uint32 *data,
						   		uint32 &count,
						   		uint32 maxCount,
						   		uint32 options = 0);
						 
		DNG_EXPORT void Sync_urational (const char *ns,
							 const char *path,
							 dng_urational &r,
							 uint32 options = 0);
		
		DNG_EXPORT void Sync_srational (const char *ns,
							 const char *path,
							 dng_srational &r,
							 uint32 options = 0);
							 
		DNG_EXPORT void SyncIPTC (dng_iptc &iptc,
					   uint32 options);
		
		DNG_EXPORT void SyncFlash (uint32 &flashState,
						uint32 &flashMask,
						uint32 options);
      
		DNG_EXPORT void SyncExifDate (const char *ns,
                           const char *path,
                           dng_date_time_info &exifDateTime,
                           bool canRemoveFromXMP,
                           bool removeFromXMP,
                           const dng_time_zone &fakeTimeZone);
						
		DNG_EXPORT virtual void SyncApproximateFocusDistance (dng_exif &exif,
												   const uint32 readOnly);
		
		DNG_EXPORT virtual void SyncLensName (dng_exif &exif);
		
		DNG_EXPORT virtual void GenerateDefaultLensName (dng_exif &exif);

	private:
	
		// Hidden assignment operator.

		DNG_EXPORT dng_xmp & operator= (const dng_xmp &xmp);
		
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/
