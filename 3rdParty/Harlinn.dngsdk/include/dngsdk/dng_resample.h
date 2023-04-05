/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_resample__
#define __dng_resample__

/*****************************************************************************/

#include "dng_assertions.h"
#include "dng_auto_ptr.h"
#include "dng_classes.h"
#include "dng_memory.h"
#include "dng_point.h"
#include "dng_types.h"

/*****************************************************************************/

class dng_resample_function
	{
	
	public:
	
		dng_resample_function ()
			{
			}
			
		virtual ~dng_resample_function ()
			{
			}
	
		virtual real64 Extent () const = 0;
		
		virtual real64 Evaluate (real64 x) const = 0;
	
	};

/*****************************************************************************/

class dng_resample_bicubic: public dng_resample_function
	{
	
	public:
	
		DNG_EXPORT virtual real64 Extent () const;
		
		DNG_EXPORT virtual real64 Evaluate (real64 x) const;
		
		DNG_EXPORT static const dng_resample_function & Get ();
		
	};
	
/******************************************************************************/

constexpr uint32 kResampleSubsampleBits  = 7;
constexpr uint32 kResampleSubsampleCount = 1 << kResampleSubsampleBits;
constexpr uint32 kResampleSubsampleMask  = kResampleSubsampleCount - 1;

/*****************************************************************************/

class dng_resample_coords
	{
	
	protected:
	
		int32 fOrigin;
	
		AutoPtr<dng_memory_block> fCoords;
		
	public:
	
		DNG_EXPORT dng_resample_coords ();
		
		DNG_EXPORT virtual ~dng_resample_coords ();
		
		DNG_EXPORT void Initialize (int32 srcOrigin,
						 int32 dstOrigin,
						 uint32 srcCount,
						 uint32 dstCount,
						 dng_memory_allocator &allocator);
						 
		const int32 * Coords (int32 index) const
			{
			return fCoords->Buffer_int32 () + (index - fOrigin);
			}
						 
		int32 Pixel (int32 index) const
			{
			return Coords (index) [0] >> kResampleSubsampleBits;
			}
	
	};

/*****************************************************************************/

class dng_resample_weights
	{
	
	protected:
	
		uint32 fRadius;
		
		uint32 fWeightStep;
		
		AutoPtr<dng_memory_block> fWeights32;
		AutoPtr<dng_memory_block> fWeights16;
	
	public:
	
		DNG_EXPORT dng_resample_weights ();
		
		DNG_EXPORT virtual ~dng_resample_weights ();
			
		DNG_EXPORT void Initialize (real64 scale,
						 const dng_resample_function &kernel,
						 dng_memory_allocator &allocator);
						 
		uint32 Radius () const
			{
			return fRadius;
			}
						 
		uint32 Width () const
			{
			return fRadius * 2;
			}
			
		int32 Offset () const
			{
			return 1 - (int32) fRadius;
			}
			
		uint32 Step () const
			{
			return fWeightStep;
			}
			
		const real32 *Weights32 (uint32 fract) const
			{
			
			DNG_ASSERT (fWeights32->Buffer (), "Weights32 is NULL");
			
			if (fract >= kResampleSubsampleCount)
				{
				
				ThrowBadFormat ();
				
				}
			
			return fWeights32->Buffer_real32 () + fract * fWeightStep;
			
			}

		const int16 *Weights16 (uint32 fract) const
			{
			
			DNG_ASSERT (fWeights16->Buffer (), "Weights16 is NULL");
			
			if (fract >= kResampleSubsampleCount)
				{
				
				ThrowBadFormat ();
				
				}
			
			return fWeights16->Buffer_int16 () + fract * fWeightStep;
			
			}

	};

/*****************************************************************************/

constexpr uint32 kResampleSubsampleBits2D  = 5;
constexpr uint32 kResampleSubsampleCount2D = 1 << kResampleSubsampleBits2D;
constexpr uint32 kResampleSubsampleMask2D  = kResampleSubsampleCount2D - 1;

/*****************************************************************************/

class dng_resample_weights_2d
	{
	
	protected:
	
		uint32 fRadius;
		
		uint32 fRowStep;
		uint32 fColStep;
		
		AutoPtr<dng_memory_block> fWeights32;
		AutoPtr<dng_memory_block> fWeights16;
	
	public:
	
		DNG_EXPORT dng_resample_weights_2d ();
		
		DNG_EXPORT virtual ~dng_resample_weights_2d ();
			
		DNG_EXPORT void Initialize (const dng_resample_function &kernel,
						 dng_memory_allocator &allocator);
						 
		uint32 Radius () const
			{
			return fRadius;
			}
						 
		uint32 Width () const
			{
			return fRadius * 2;
			}
			
		int32 Offset () const
			{
			return 1 - (int32) fRadius;
			}
			
		uint32 RowStep () const
			{
			return fRowStep;
			}
			
		uint32 ColStep () const
			{
			return fColStep;
			}
			
		const real32 *Weights32 (dng_point fract) const
			{
			
			DNG_ASSERT (fWeights32->Buffer (), "Weights32 is NULL");
			
			const uint32 offset = fract.v * fRowStep + fract.h * fColStep;

			return fWeights32->Buffer_real32 () + offset;
			
			}

		const int16 *Weights16 (dng_point fract) const
			{
			
			DNG_ASSERT (fWeights16->Buffer (), "Weights16 is NULL");
			
			const uint32 offset = fract.v * fRowStep + fract.h * fColStep;
			
			return fWeights16->Buffer_int16 () + offset;
			
			}

	};

/*****************************************************************************/

DNG_EXPORT void ResampleImage (dng_host &host,
					const dng_image &srcImage,
					dng_image &dstImage,
					const dng_rect &srcBounds,
					const dng_rect &dstBounds,
					const dng_resample_function &kernel);
						
/*****************************************************************************/

#endif
	
/*****************************************************************************/
