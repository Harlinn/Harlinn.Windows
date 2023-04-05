/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_simple_image__
#define __dng_simple_image__

/*****************************************************************************/

#include "dng_auto_ptr.h"
#include "dng_image.h"
#include "dng_pixel_buffer.h"

/*****************************************************************************/

/// dng_image derived class with simple Trim and Rotate functionality.
 
class dng_simple_image : public dng_image
	{
	
	protected:
	
		dng_pixel_buffer fBuffer;
		
		AutoPtr<dng_memory_block> fMemory;
		
		dng_memory_allocator &fAllocator;
		
	public:
	
		DNG_EXPORT dng_simple_image (const dng_rect &bounds,
				  		  uint32 planes,
				  		  uint32 pixelType,
				  		  dng_memory_allocator &allocator);
		
		DNG_EXPORT virtual ~dng_simple_image ();
	
		DNG_EXPORT virtual dng_image * Clone () const;

		/// Setter for pixel type.
		
		DNG_EXPORT virtual void SetPixelType (uint32 pixelType);
		
		/// Trim image data outside of given bounds. Memory is not reallocated or freed.

		DNG_EXPORT virtual void Trim (const dng_rect &r);

		/// Rotate image according to orientation.
		
		DNG_EXPORT virtual void Rotate (const dng_orientation &orientation);
		
		/// Get the buffer for direct processing. (Unique to dng_simple_image.)
		
		void GetPixelBuffer (dng_pixel_buffer &buffer)
			{
			buffer = fBuffer;
			}

	protected:
	
		DNG_EXPORT virtual void AcquireTileBuffer (dng_tile_buffer &buffer,
										const dng_rect &area,
										bool dirty) const;
		
	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/
