/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_string_list__
#define __dng_string_list__

/*****************************************************************************/

#include "dng_classes.h"
#include "dng_types.h"
#include "dng_uncopyable.h"

/*****************************************************************************/

class dng_string_list: private dng_uncopyable
	{
	
	private:
	
		uint32 fCount;
		
		uint32 fAllocated;
	
		dng_string **fList;
		
	public:
	
		DNG_EXPORT dng_string_list ();
		
		DNG_EXPORT ~dng_string_list ();
		
		uint32 Count () const
			{
			return fCount;
			}
			
		dng_string & operator[] (uint32 index)
			{
			return *(fList [index]);
			}
		
		const dng_string & operator[] (uint32 index) const
			{
			return *(fList [index]);
			}
		
		DNG_EXPORT void Allocate (uint32 minSize);
		
		DNG_EXPORT void Insert (uint32 index,
					 const dng_string &s);
					 
		void Append (const dng_string &s)
			{
			Insert (Count (), s);
			}
			
		DNG_EXPORT bool Contains (const dng_string &s) const;
		
		DNG_EXPORT void Clear ();
		
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/
