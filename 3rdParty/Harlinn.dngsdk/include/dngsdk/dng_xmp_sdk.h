/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_xmp_sdk__
#define __dng_xmp_sdk__

/*****************************************************************************/

#include "dng_auto_ptr.h"
#include "dng_classes.h"
#include "dng_flags.h"
#include "dng_types.h"

/*****************************************************************************/

extern const char *XMP_NS_TIFF;
extern const char *XMP_NS_EXIF;
extern const char *XMP_NS_EXIFEX;
extern const char *XMP_NS_PHOTOSHOP;
extern const char *XMP_NS_XAP;
extern const char *XMP_NS_XAP_RIGHTS;
extern const char *XMP_NS_DC;
extern const char *XMP_NS_XMP_NOTE;
extern const char *XMP_NS_MM;

extern const char *XMP_NS_CRS;
extern const char *XMP_NS_CRSS;
extern const char *XMP_NS_CRD;

extern const char *XMP_NS_LCP;

extern const char *XMP_NS_AUX;

extern const char *XMP_NS_IPTC;
extern const char *XMP_NS_IPTC_EXT;

extern const char *XMP_NS_CRX;

extern const char *XMP_NS_DNG;

extern const char *XMP_NS_PANO;

/*****************************************************************************/

class dng_xmp_private;

/*****************************************************************************/

typedef bool (IteratePathsCallback) (const char *ns,
			  				   	     const char *path,
			  				         void *callbackData);

/*****************************************************************************/

struct dng_xmp_namespace
	{
	const char * fullName;
	const char * shortName;
	};

/*****************************************************************************/

class dng_xmp_sdk
	{
	
	private:
	
		dng_xmp_private *fPrivate;
		
	public:
	
		DNG_EXPORT dng_xmp_sdk ();
		
		DNG_EXPORT dng_xmp_sdk (const dng_xmp_sdk &sdk);
		
		DNG_EXPORT virtual ~dng_xmp_sdk ();
		
		DNG_EXPORT static void InitializeSDK (dng_xmp_namespace * extraNamespaces = NULL,
								   const char *software = NULL);
		
		DNG_EXPORT static void TerminateSDK ();
	
		DNG_EXPORT bool HasMeta () const;

        void RequireMeta ()
            {
            NeedMeta ();
            }

		DNG_EXPORT void * GetPrivateMeta ();
						   
		DNG_EXPORT void Parse (dng_host &host,
					const char *buffer,
				    uint32 count);

		DNG_EXPORT bool Exists (const char *ns,
					 const char *path) const;
		
		DNG_EXPORT void AppendArrayItem (const char *ns,
							  const char *arrayName,
							  const char *itemValue,
							  bool isBag = true,
							  bool propIsStruct = false);
							  		
		DNG_EXPORT int32 CountArrayItems (const char *ns,
		                       const char *path) const;
							
		DNG_EXPORT bool HasNameSpace (const char *ns) const;

		DNG_EXPORT void Remove (const char *ns,
				     const char *path);

		DNG_EXPORT void RemoveProperties (const char *ns);
		
		DNG_EXPORT bool IsEmptyString (const char *ns,
					        const char *path);
								
		DNG_EXPORT bool IsEmptyArray (const char *ns,
					       const char *path);
								
		DNG_EXPORT void ComposeArrayItemPath (const char *ns,
								   const char *arrayName,
								   int32 itemNumber,
								   dng_string &s) const;
		
		DNG_EXPORT void ComposeStructFieldPath (const char *ns,
								     const char *structName,
								     const char *fieldNS,
									 const char *fieldName,
								     dng_string &s) const;
									 
		DNG_EXPORT bool GetNamespacePrefix (const char *uri,
								 dng_string &s) const;
																																					
		DNG_EXPORT bool GetString (const char *ns,
				   		const char *path,
				   		dng_string &s) const;
				   		  		
		DNG_EXPORT void ValidateStringList (const char *ns,
								 const char *path);
								   
		DNG_EXPORT bool GetStringList (const char *ns,
							const char *path,
							dng_string_list &list) const;

		DNG_EXPORT bool GetAltLangDefault (const char *ns,
								const char *path,
								dng_string &s,
                                bool silent = false) const;
								
		DNG_EXPORT bool GetLocalString (const char *ns,
							 const char *path,
							 dng_local_string &s) const;
								
		DNG_EXPORT bool GetStructField (const char *ns,
							 const char *path,
							 const char *fieldNS,
							 const char *fieldName,
							 dng_string &s) const;
						   		   
		DNG_EXPORT void Set (const char *ns,
				  const char *path,
				  const char *text);

		DNG_EXPORT void SetString (const char *ns,
				  		const char *path,
				  		const dng_string &s);

		DNG_EXPORT void SetStringList (const char *ns,
				  		    const char *path,
				  		    const dng_string_list &list,
				  		    bool isBag);

		DNG_EXPORT void SetAltLangDefault (const char *ns,
								const char *path,
								const dng_string &s);

		DNG_EXPORT void SetLocalString (const char *ns,
                             const char *path,
                             const dng_local_string &s);
								
		DNG_EXPORT void SetStructField (const char *ns,
							 const char *path,
							 const char *fieldNS,
							 const char *fieldName,
							 const char *text);
		
		DNG_EXPORT void DeleteStructField (const char *ns,
								const char *structName,
								const char *fieldNS,
								const char *fieldName);
														   				   		   
		DNG_EXPORT dng_memory_block * Serialize (dng_memory_allocator &allocator,
									  bool asPacket,
									  uint32 targetBytes,
									  uint32 padBytes,
									  bool forJPEG,
									  bool compact) const;
		
		DNG_EXPORT void PackageForJPEG (dng_memory_allocator &allocator,
							 AutoPtr<dng_memory_block> &stdBlock,
							 AutoPtr<dng_memory_block> &extBlock,
							 dng_string &extDigest) const;
							 
		DNG_EXPORT void MergeFromJPEG (const dng_xmp_sdk *xmp);

		DNG_EXPORT void ReplaceXMP (dng_xmp_sdk *xmp);
		
		DNG_EXPORT bool IteratePaths (IteratePathsCallback *callback,
						   void *callbackData = NULL,
						   const char *startNS = 0,
						   const char *startingPath = 0);
						   
#if qDNGXMPDocOps
		
		DNG_EXPORT void DocOpsOpenXMP (const char *srcMIME);
		
		DNG_EXPORT void DocOpsPrepareForSave (const char *srcMIME,
								   const char *dstMIME,
								   bool newPath = true);
								   
		DNG_EXPORT void DocOpsUpdateMetadata (const char *srcMIME);
		
#endif
						   
	private:

		DNG_EXPORT void ClearMeta ();

		DNG_EXPORT void MakeMeta ();

		DNG_EXPORT void NeedMeta ();
		
		// Hidden assignment operator.
		
		DNG_EXPORT dng_xmp_sdk & operator= (const dng_xmp_sdk &sdk);

	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/
