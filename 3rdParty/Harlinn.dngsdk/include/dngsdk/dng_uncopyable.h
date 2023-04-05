/*****************************************************************************/
// Copyright 2012-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_uncopyable__
#define __dng_uncopyable__

#include "dng_export.h"

/*****************************************************************************/

// Virtual base class to prevent object copies.

class dng_uncopyable
	{

	protected:

		dng_uncopyable ()
			{
			}

		~dng_uncopyable ()
			{
			}

	private:
		
		DNG_EXPORT dng_uncopyable (const dng_uncopyable &);
		
		DNG_EXPORT dng_uncopyable & operator= (const dng_uncopyable &);
		
	};

/*****************************************************************************/

#endif	// __dng_uncopyable__
	
/*****************************************************************************/
