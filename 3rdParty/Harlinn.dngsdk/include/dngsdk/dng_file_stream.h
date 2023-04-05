/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/** \file
 * Simple, portable, file read/write support.
 */

/*****************************************************************************/

#ifndef __dng_file_stream__
#define __dng_file_stream__

/*****************************************************************************/

#include "dng_stream.h"

/*****************************************************************************/

/// \brief A stream to/from a disk file. See dng_stream for read/write interface

class dng_file_stream: public dng_stream
	{
	
	private:
	
		FILE *fFile;
	
	public:
	
		/// Open a stream on a file.
		/// \param filename Pathname in platform synax.
		/// \param output Set to true if writing, false otherwise.
		/// \param bufferSize size of internal buffer to use. Defaults to 4k.

		DNG_EXPORT dng_file_stream (const char *filename,
						 bool output = false,
						 uint32 bufferSize = kDefaultBufferSize);

#if qWinOS

		DNG_EXPORT dng_file_stream (const wchar_t *filename,
						 bool output = false,
						 uint32 bufferSize = kDefaultBufferSize);

#endif	// qWinOS
		
		DNG_EXPORT virtual ~dng_file_stream ();
	
	protected:
	
		DNG_EXPORT virtual uint64 DoGetLength ();
	
		DNG_EXPORT virtual void DoRead (void *data,
							 uint32 count,
							 uint64 offset);
		
		DNG_EXPORT virtual void DoWrite (const void *data,
							  uint32 count,
							  uint64 offset);
		
	};
		
/*****************************************************************************/

#endif
	
/*****************************************************************************/
