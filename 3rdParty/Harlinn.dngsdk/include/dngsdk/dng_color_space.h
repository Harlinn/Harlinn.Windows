/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

/** \file
 *  Standard gamma functions and color spaces used within the DNG SDK.
 */

#ifndef __dng_color_space__
#define __dng_color_space__

/*****************************************************************************/

#include "dng_1d_function.h"
#include "dng_classes.h"
#include "dng_matrix.h"
#include "dng_types.h"

/*****************************************************************************/

/// \brief A dng_1d_function for gamma encoding in sRGB color space

class dng_function_GammaEncode_sRGB: public dng_1d_function
	{
	
	public:
	
		DNG_EXPORT virtual real64 Evaluate (real64 x) const;
			
		DNG_EXPORT virtual real64 EvaluateInverse (real64 y) const;
	
		DNG_EXPORT static const dng_1d_function & Get ();
	
	};

/*****************************************************************************/

/// \brief A dng_1d_function for gamma encoding with 1.8 gamma.

class dng_function_GammaEncode_1_8: public dng_1d_function
	{
	
	public:
	
		DNG_EXPORT virtual real64 Evaluate (real64 x) const;
			
		DNG_EXPORT virtual real64 EvaluateInverse (real64 y) const;
	
		DNG_EXPORT static const dng_1d_function & Get ();
	
	};
			
/*****************************************************************************/

/// \brief A dng_1d_function for gamma encoding with 2.2 gamma.

class dng_function_GammaEncode_2_2: public dng_1d_function
	{
	
	public:
	
		DNG_EXPORT virtual real64 Evaluate (real64 x) const;
			
		DNG_EXPORT virtual real64 EvaluateInverse (real64 y) const;
	
		DNG_EXPORT static const dng_1d_function & Get ();
	
	};
			
/*****************************************************************************/

/// \brief An abstract color space

class dng_color_space
	{
	
	protected:
	
		dng_matrix fMatrixToPCS;
		
		dng_matrix fMatrixFromPCS;
		
	public:
	
		DNG_EXPORT virtual ~dng_color_space ();
	
		/// Return a matrix which transforms source data in this color space into the
		/// Profile Connection Space.

		const dng_matrix & MatrixToPCS () const
			{
			return fMatrixToPCS;
			}
		
		/// Return a matrix which transforms Profile Connection Space data into this
		/// color space.

		const dng_matrix & MatrixFromPCS () const
			{
			return fMatrixFromPCS;
			}

		/// Predicate which is true if this color space is monochrome (has only a
		/// single column).

		bool IsMonochrome () const
			{
			return fMatrixToPCS.Cols () == 1;
			}
		
		/// Getter for the gamma function for this color space.

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;

		/// Returns true if this color space is linear. (I.e. has gamma 1.0.)

		bool IsLinear () const
			{
			return GammaFunction ().IsIdentity ();
			}

		/// Map an input value through this color space's encoding gamma.

		real64 GammaEncode (real64 x) const
			{
			return GammaFunction ().Evaluate (x);
			}

		/// Map an input value through this color space's decoding gamma (inverse of
		/// the encoding gamma).

		real64 GammaDecode (real64 y) const
			{
			return GammaFunction ().EvaluateInverse (y);
			}
			
		/// Getter for ICC profile, if this color space has one.
		/// \param size Out parameter which receives size on return.
		/// \param data Receives bytes of profile.
		/// \retval Returns true if this color space has an ICC profile, false otherwise.

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;
								 
	protected:
	
		DNG_EXPORT dng_color_space ();
			
		DNG_EXPORT void SetMonochrome ();
		
		DNG_EXPORT void SetMatrixToPCS (const dng_matrix_3by3 &M);
		
	};

/*****************************************************************************/

/// Singleton class for sRGB color space.

class dng_space_sRGB: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_sRGB ();
		
	public:

		/// Returns dng_function_GammaEncode_sRGB

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;

		/// Returns sRGB IEC61966-2.1 ICC profile

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;

		/// Static method for getting single global instance of this color space.

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

/// \brief Singleton class for AdobeRGB color space.

class dng_space_AdobeRGB: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_AdobeRGB ();
		
	public:
	
		/// Returns dng_function_GammaEncode_2_2

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;

		/// Returns AdobeRGB (1998) ICC profile

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;
		
		/// Static method for getting single global instance of this color space.

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

/// \brief Singleton class for ColorMatch color space.

class dng_space_ColorMatch: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_ColorMatch ();
		
	public:
	
		/// Returns dng_function_GammaEncode_1_8

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;
		
		/// Returns ColorMatch RGB ICC profile

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;
		
		/// Static method for getting single global instance of this color space.

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

/// \brief Singleton class for ProPhoto RGB color space.

class dng_space_ProPhoto: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_ProPhoto ();
		
	public:
	
		/// Returns dng_function_GammaEncode_1_8

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;
		
		/// Returns ProPhoto RGB ICC profile

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;
		
		/// Static method for getting single global instance of this color space.

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

/// \brief Singleton class for gamma 1.8 grayscale color space.

class dng_space_GrayGamma18: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_GrayGamma18 ();
		
	public:
	
		/// Returns dng_function_GammaEncode_1_8

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;
		
		/// Returns simple grayscale gamma 1.8 ICC profile

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;
		
		/// Static method for getting single global instance of this color space.

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

/// \brief Singleton class for gamma 2.2 grayscale color space.

class dng_space_GrayGamma22: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_GrayGamma22 ();
		
	public:

		/// Returns dng_function_GammaEncode_2_2

		DNG_EXPORT virtual const dng_1d_function & GammaFunction () const;
		
		/// Returns simple grayscale gamma 2.2 ICC profile

		DNG_EXPORT virtual bool ICCProfile (uint32 &size,
								 const uint8 *&data) const;
		
		/// Static method for getting single global instance of this color space.

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

class dng_space_fakeRGB: public dng_color_space
	{
	
	protected:
	
		DNG_EXPORT dng_space_fakeRGB ();
		
	public:

		DNG_EXPORT static const dng_color_space & Get ();
	
	};

/*****************************************************************************/

#endif

/*****************************************************************************/
