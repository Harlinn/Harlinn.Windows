/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/** \file
 * Text string representation.
 */

/*****************************************************************************/

#ifndef __dng_string__
#define __dng_string__

/*****************************************************************************/

#include "dng_types.h"
#include "dng_memory.h"

/*****************************************************************************/

class dng_string
	{
	
	private:
	
		// Always stored internally as a UTF-8 encoded string.
	
		dng_memory_data fData;
		
	public:
	
		DNG_EXPORT dng_string ();
		
		DNG_EXPORT dng_string (const dng_string &s);
		
		DNG_EXPORT dng_string & operator= (const dng_string &s);
		
		DNG_EXPORT ~dng_string ();
		
		DNG_EXPORT const char * Get () const;
		
		DNG_EXPORT bool IsASCII () const;
		
		DNG_EXPORT void Set (const char *s);
	
		DNG_EXPORT void Set_ASCII (const char *s);
		
		DNG_EXPORT void Set_UTF8 (const char *s);
		
		DNG_EXPORT uint32 Get_SystemEncoding (dng_memory_data &buffer) const;
		
		DNG_EXPORT void Set_SystemEncoding (const char *s);
		
		DNG_EXPORT bool ValidSystemEncoding () const;
		
		DNG_EXPORT void Set_JIS_X208_1990 (const char *s);
				  
		DNG_EXPORT static uint32 DecodeUTF8 (const char *&s,
								  uint32 maxBytes = 6,
								  bool *isValid = NULL);
								  
		DNG_EXPORT static bool IsUTF8 (const char *s);
		
		DNG_EXPORT void Set_UTF8_or_System (const char *s);

		DNG_EXPORT uint32 Get_UTF16 (dng_memory_data &buffer) const;
		
		DNG_EXPORT void Set_UTF16 (const uint16 *s);
		
		DNG_EXPORT void Clear ();
		
		DNG_EXPORT void Truncate (uint32 maxBytes);
		
		DNG_EXPORT bool TrimTrailingBlanks ();
		
		DNG_EXPORT bool TrimLeadingBlanks ();
		
		DNG_EXPORT bool IsEmpty () const;
		
		bool NotEmpty () const
			{
			return !IsEmpty ();
			}
			
		DNG_EXPORT uint32 Length () const;
		
		DNG_EXPORT bool operator== (const dng_string &s) const;
		
		bool operator!= (const dng_string &s) const
			{
			return !(*this == s);
			}
			
		// A utility for doing case insensitive comparisons on strings...
		
		DNG_EXPORT static bool Matches (const char *t,
							 const char *s,
							 bool case_sensitive = false);
							 
		// ...wrapped up for use with dng_string.

		DNG_EXPORT bool Matches (const char *s,
					  bool case_sensitive = false) const;

		DNG_EXPORT bool StartsWith (const char *s,
						 bool case_sensitive = false) const;
						 
		DNG_EXPORT bool EndsWith (const char *s,
					   bool case_sensitive = false) const;
					   
		DNG_EXPORT bool Contains (const char *s,
					   bool case_sensitive = false,
					   int32 *match_offset = NULL) const;
						 
		DNG_EXPORT bool Replace (const char *old_string,
					  const char *new_string,
					  bool case_sensitive = true);
		
		DNG_EXPORT void ReplaceChars (char oldChar,
                           char newChar);
		
		DNG_EXPORT bool TrimLeading (const char *s,
						  bool case_sensitive = false);
						  
		DNG_EXPORT void Append (const char *s);
		
		DNG_EXPORT void SetUppercase ();
		
		DNG_EXPORT void SetLowercase ();
        
		DNG_EXPORT void SetLineEndings (char ending);
		
		void SetLineEndingsToNewLines ()
			{
			SetLineEndings ('\n');
			}
			
		void SetLineEndingsToReturns ()
			{
			SetLineEndings ('\r');
			}
			
		DNG_EXPORT void StripLowASCII ();
		
		DNG_EXPORT void ForceASCII ();
		
		DNG_EXPORT int32 Compare (const dng_string &s,
                       bool digitsAsNumber = true) const;

		// A utility to convert fields of numbers into comma separated numbers.

		DNG_EXPORT void NormalizeAsCommaSeparatedNumbers ();

	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/
