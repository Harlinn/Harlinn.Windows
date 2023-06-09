/*****************************************************************************/
// Copyright 2008-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/** \file
 * Opcode to fix 2D uniformity defects, such as shading.
 */

/*****************************************************************************/

#ifndef __dng_gain_map__
#define __dng_gain_map__

/*****************************************************************************/

#include "dng_memory.h"
#include "dng_misc_opcodes.h"
#include "dng_tag_types.h"
#include "dng_uncopyable.h"

/*****************************************************************************/

/// \brief Holds a discrete (i.e., sampled) 2D representation of a gain map. This is
/// effectively an image containing scale factors. 

class dng_gain_map: private dng_uncopyable
	{
	
	private:
	
		dng_point fPoints;
		
		dng_point_real64 fSpacing;
		
		dng_point_real64 fOrigin;
		
		uint32 fPlanes;
		
		uint32 fRowStep;
		
		AutoPtr<dng_memory_block> fBuffer;
		
	public:
	
		/// Construct a gain map with the specified memory allocator, number of
		/// samples (points), sample spacing, origin, and number of color planes.

		DNG_EXPORT dng_gain_map (dng_memory_allocator &allocator,
					  const dng_point &points,
					  const dng_point_real64 &spacing,
					  const dng_point_real64 &origin,
					  uint32 planes);

		/// The number of samples in the horizontal and vertical directions.

		const dng_point & Points () const
			{
			return fPoints;
			}
			
		/// The space between adjacent samples in the horizontal and vertical
		/// directions.

		const dng_point_real64 & Spacing () const
			{
			return fSpacing;
			}
			
		/// The 2D coordinate for the first (i.e., top-left-most) sample.

		const dng_point_real64 & Origin () const
			{
			return fOrigin;
			}
			
		/// The number of color planes.

		uint32 Planes () const
			{
			return fPlanes;
			}

		/// Getter for a gain map sample (specified by row, column, and plane).

		real32 & Entry (uint32 rowIndex,
						uint32 colIndex,
						uint32 plane)
			{
			
			return *(fBuffer->Buffer_real32 () +
				     rowIndex * fRowStep +
				     colIndex * fPlanes  +
				     plane);
			
			}
			
		/// Getter for a gain map sample (specified by row index, column index, and
		/// plane index).

		const real32 & Entry (uint32 rowIndex,
							  uint32 colIndex,
							  uint32 plane) const
			{
			
			return *(fBuffer->Buffer_real32 () +
				     rowIndex * fRowStep +
				     colIndex * fPlanes  +
				     plane);
			
			}
			
		/// Compute the interpolated gain (i.e., scale factor) at the specified pixel
		/// position and color plane, within the specified image bounds (in pixels).

		DNG_EXPORT real32 Interpolate (int32 row,
							int32 col,
							uint32 plane,
							const dng_rect &bounds) const;
							
		/// The number of bytes needed to hold the gain map data.

		DNG_EXPORT uint32 PutStreamSize () const;
		
		/// Write the gain map to the specified stream.

		DNG_EXPORT void PutStream (dng_stream &stream) const;
		
		/// Read a gain map from the specified stream.

		DNG_EXPORT static dng_gain_map * GetStream (dng_host &host,
										 dng_stream &stream);

	};

/*****************************************************************************/

/// \brief An opcode to fix 2D spatially-varying light falloff or color casts (i.e.,
/// uniformity issues). This is commonly due to shading.

class dng_opcode_GainMap: public dng_inplace_opcode,
						  private dng_uncopyable
	{
	
	private:
	
		dng_area_spec fAreaSpec;
	
		AutoPtr<dng_gain_map> fGainMap;
	
	public:
	
		/// Construct a GainMap opcode for the specified image area and the specified
		/// gain map.

		DNG_EXPORT dng_opcode_GainMap (const dng_area_spec &areaSpec,
							AutoPtr<dng_gain_map> &gainMap);
	
		/// Construct a GainMap opcode from the specified stream.

		DNG_EXPORT dng_opcode_GainMap (dng_host &host,
							dng_stream &stream);
	
		/// Write the opcode to the specified stream.

		DNG_EXPORT virtual void PutData (dng_stream &stream) const;
		
		/// The pixel data type of this opcode.

		virtual uint32 BufferPixelType (uint32 /* imagePixelType */)
			{
			return ttFloat;
			}
	
		/// The adjusted bounds (processing area) of this opcode. It is limited to
		/// the intersection of the specified image area and the GainMap area.

		virtual dng_rect ModifiedBounds (const dng_rect &imageBounds)
			{
			return fAreaSpec.Overlap (imageBounds);
			}
	
		/// Apply the gain map.

		DNG_EXPORT virtual void ProcessArea (dng_negative &negative,
								  uint32 threadIndex,
								  dng_pixel_buffer &buffer,
								  const dng_rect &dstArea,
								  const dng_rect &imageBounds);
	
	};
	
/*****************************************************************************/

#endif
	
/*****************************************************************************/
