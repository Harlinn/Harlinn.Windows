/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/** \file
 * Stream abstraction to/from in-memory data.
 */

/*****************************************************************************/

#ifndef __dng_memory_stream__
#define __dng_memory_stream__

/*****************************************************************************/

#include "dng_stream.h"

/*****************************************************************************/

/// \brief A dng_stream which can be read from or written to memory.
///
/// Stream is populated via writing and either read or accessed by asking for contents as a pointer.

class dng_memory_stream: public dng_stream
	{
	
	protected:
	
		dng_memory_allocator &fAllocator;
		
		uint32 fPageSize;
		
		uint32 fPageCount;
		uint32 fPagesAllocated;
		
		dng_memory_block **fPageList;
		
		uint64 fMemoryStreamLength;
        
        uint64 fLengthLimit;
		
	public:

		/// Construct a new memory-based stream.
		/// \param allocator Allocator to use to allocate memory in stream as needed.
		/// \param sniffer If non-NULL used to check for user cancellation.
		/// \param pageSize Unit of allocation for data stored in stream.

		DNG_EXPORT dng_memory_stream (dng_memory_allocator &allocator,
						   dng_abort_sniffer *sniffer = NULL,
						   uint32 pageSize = 64 * 1024);
						   
		DNG_EXPORT virtual ~dng_memory_stream ();
        
        /// Sets a maximum length limit.
        
        void SetLengthLimit (uint64 limit)
            {
            fLengthLimit = limit;
            }

		/// Copy a specified number of bytes to a target stream.
		/// \param dstStream The target stream.
		/// \param count The number of bytes to copy.
		
		DNG_EXPORT virtual void CopyToStream (dng_stream &dstStream,
								   uint64 count);
		
	protected:
		
		DNG_EXPORT virtual uint64 DoGetLength ();
	
		DNG_EXPORT virtual void DoRead (void *data,
							 uint32 count,
							 uint64 offset);
							 
		DNG_EXPORT virtual void DoSetLength (uint64 length);
							 
		DNG_EXPORT virtual void DoWrite (const void *data,
							  uint32 count,
							  uint64 offset);
		
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/
