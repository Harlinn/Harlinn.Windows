/*****************************************************************************/
// Copyright 2006-2019 Adobe Systems Incorporated
// All Rights Reserved.
//
// NOTICE:  Adobe permits you to use, modify, and distribute this file in
// accordance with the terms of the Adobe license agreement accompanying it.
/*****************************************************************************/

#ifndef __dng_mutex__
#define __dng_mutex__

/******************************************************************************/

#include "dng_flags.h"
#include "dng_types.h"
#include "dng_uncopyable.h"

#if qDNGThreadSafe
#include "dng_pthread.h"
#endif

#include <mutex>

typedef std::mutex					 dng_std_mutex;
typedef std::lock_guard<std::mutex>	 dng_lock_std_mutex;
typedef std::unique_lock<std::mutex> dng_unique_lock;

// We should try to phase out use of dng_mutex over time.
// 
// Note that dng_mutex differs from dng_std_mutex (std::mutex) in that
// dng_mutex supports recursive locking (hierarchical mutex).

/******************************************************************************/

class dng_mutex: private dng_uncopyable
	{
	
	public:
	
		enum
			{
			kDNGMutexLevelLeaf   = 0x70000000u,
            kDNGMutexLevelIgnore = 0x7FFFFFFFu
			};

		DNG_EXPORT dng_mutex (const char *mutexName,
				   uint32 mutexLevel = kDNGMutexLevelLeaf);

		DNG_EXPORT virtual ~dng_mutex ();

		DNG_EXPORT void Lock ();

		DNG_EXPORT void Unlock ();
		
		DNG_EXPORT const char *MutexName () const;

	protected:
	
#if qDNGThreadSafe
	
		pthread_mutex_t fPthreadMutex;
	
		const uint32 fMutexLevel;

		uint32 fRecursiveLockCount;

		dng_mutex *fPrevHeldMutex;

		const char * const fMutexName;

		friend class dng_condition;
		
#endif

	};
		
/*****************************************************************************/

class dng_lock_mutex: private dng_uncopyable
	{
	
	private:
	
		dng_mutex *fMutex;
	
	public:
	
		DNG_EXPORT dng_lock_mutex (dng_mutex *mutex);
        
		DNG_EXPORT dng_lock_mutex (dng_mutex &mutex);
			
		DNG_EXPORT ~dng_lock_mutex ();
			
	};
	
/*****************************************************************************/

class dng_unlock_mutex: private dng_uncopyable
	{
	
	private:
	
		dng_mutex *fMutex;
	
	public:
	
		DNG_EXPORT dng_unlock_mutex (dng_mutex *mutex);
        
		DNG_EXPORT dng_unlock_mutex (dng_mutex &mutex);
			
		DNG_EXPORT ~dng_unlock_mutex ();
			
	};

/*****************************************************************************/

class dng_condition: private dng_uncopyable
	{
	
	public:

		DNG_EXPORT dng_condition ();

		DNG_EXPORT ~dng_condition ();

		DNG_EXPORT bool Wait (dng_mutex &mutex, double timeoutSecs = -1.0);

		DNG_EXPORT void Signal ();
		
		DNG_EXPORT void Broadcast ();

	protected:
	
	
#if qDNGThreadSafe
		pthread_cond_t fPthreadCondition;
#endif // qDNGThreadSafe

	};

/*****************************************************************************/

#endif
	
/*****************************************************************************/
