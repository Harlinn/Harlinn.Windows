
/***************************************************************************************************
**
** Real-Time Hierarchical Profiling for Game Programming Gems 3
**
** by Greg Hjelstrom & Byon Garrabrant
**
***************************************************************************************************/

// Credits: The Clock class was inspired by the Timer classes in
// Ogre (www.ogre3d.org).

#ifndef BT_QUICK_PROF_H
#define BT_QUICK_PROF_H

#include "btScalar.h"
#define USE_BT_CLOCK 1

#ifdef USE_BT_CLOCK

///The btClock is a portable basic clock that measures accurate time in seconds, use for profiling.
class btClock
{
public:
	BT_EXPORT btClock();

	BT_EXPORT btClock(const btClock& other);
	BT_EXPORT btClock& operator=(const btClock& other);

	BT_EXPORT ~btClock();

	/// Resets the initial reference time.
	BT_EXPORT void reset();

	/// Returns the time in ms since the last call to reset or since
	/// the btClock was created.
	BT_EXPORT unsigned long long int getTimeMilliseconds();

	/// Returns the time in us since the last call to reset or since
	/// the Clock was created.
	BT_EXPORT unsigned long long int getTimeMicroseconds();

	BT_EXPORT unsigned long long int getTimeNanoseconds();

	/// Returns the time in s since the last call to reset or since
	/// the Clock was created.
	BT_EXPORT btScalar getTimeSeconds();

private:
	struct btClockData* m_data;
};

#endif  //USE_BT_CLOCK

typedef void(btEnterProfileZoneFunc)(const char* msg);
typedef void(btLeaveProfileZoneFunc)();

BT_EXPORT btEnterProfileZoneFunc* btGetCurrentEnterProfileZoneFunc();
BT_EXPORT btLeaveProfileZoneFunc* btGetCurrentLeaveProfileZoneFunc();

BT_EXPORT void btSetCustomEnterProfileZoneFunc(btEnterProfileZoneFunc* enterFunc);
BT_EXPORT void btSetCustomLeaveProfileZoneFunc(btLeaveProfileZoneFunc* leaveFunc);

#ifndef BT_ENABLE_PROFILE
#define BT_NO_PROFILE 1
#endif  //BT_NO_PROFILE

const unsigned int BT_QUICKPROF_MAX_THREAD_COUNT = 64;

//btQuickprofGetCurrentThreadIndex will return -1 if thread index cannot be determined,
//otherwise returns thread index in range [0..maxThreads]
BT_EXPORT unsigned int btQuickprofGetCurrentThreadIndex2();

#ifndef BT_NO_PROFILE


#include <stdio.h>  //@todo remove this, backwards compatibility

#include "btAlignedAllocator.h"
#include <new>

///A node in the Profile Hierarchy Tree
class CProfileNode
{
public:
	BT_EXPORT CProfileNode(const char* name, CProfileNode* parent);
	BT_EXPORT ~CProfileNode(void);

	BT_EXPORT CProfileNode* Get_Sub_Node(const char* name);

	CProfileNode* Get_Parent(void) { return Parent; }
	CProfileNode* Get_Sibling(void) { return Sibling; }
	CProfileNode* Get_Child(void) { return Child; }

	BT_EXPORT void CleanupMemory();
	BT_EXPORT void Reset(void);
	BT_EXPORT void Call(void);
	BT_EXPORT bool Return(void);

	const char* Get_Name(void) { return Name; }
	int Get_Total_Calls(void) { return TotalCalls; }
	float Get_Total_Time(void) { return TotalTime; }
	void* GetUserPointer() const { return m_userPtr; }
	void SetUserPointer(void* ptr) { m_userPtr = ptr; }

protected:
	const char* Name;
	int TotalCalls;
	float TotalTime;
	unsigned long int StartTime;
	int RecursionCounter;

	CProfileNode* Parent;
	CProfileNode* Child;
	CProfileNode* Sibling;
	void* m_userPtr;
};

///An iterator to navigate through the tree
class CProfileIterator
{
public:
	// Access all the children of the current parent
	BT_EXPORT void First(void);
	BT_EXPORT void Next(void);
	BT_EXPORT bool Is_Done(void);
	bool Is_Root(void) { return (CurrentParent->Get_Parent() == 0); }

	BT_EXPORT void Enter_Child(int index);     // Make the given child the new parent
	BT_EXPORT void Enter_Largest_Child(void);  // Make the largest child the new parent
	BT_EXPORT void Enter_Parent(void);         // Make the current parent's parent the new parent

	// Access the current child
	const char* Get_Current_Name(void) { return CurrentChild->Get_Name(); }
	int Get_Current_Total_Calls(void) { return CurrentChild->Get_Total_Calls(); }
	float Get_Current_Total_Time(void) { return CurrentChild->Get_Total_Time(); }

	void* Get_Current_UserPointer(void) { return CurrentChild->GetUserPointer(); }
	void Set_Current_UserPointer(void* ptr) { CurrentChild->SetUserPointer(ptr); }
	// Access the current parent
	const char* Get_Current_Parent_Name(void) { return CurrentParent->Get_Name(); }
	int Get_Current_Parent_Total_Calls(void) { return CurrentParent->Get_Total_Calls(); }
	float Get_Current_Parent_Total_Time(void) { return CurrentParent->Get_Total_Time(); }

protected:
	CProfileNode* CurrentParent;
	CProfileNode* CurrentChild;

	BT_EXPORT CProfileIterator(CProfileNode* start);
	friend class CProfileManager;
};

///The Manager for the Profile system
class CProfileManager
{
public:
	BT_EXPORT static void Start_Profile(const char* name);
	BT_EXPORT static void Stop_Profile(void);

	BT_EXPORT static void CleanupMemory(void);
	//	{
	//		Root.CleanupMemory();
	//	}

	BT_EXPORT static void Reset(void);
	BT_EXPORT static void Increment_Frame_Counter(void);
	static int Get_Frame_Count_Since_Reset(void) { return FrameCounter; }
	BT_EXPORT static float Get_Time_Since_Reset(void);

	BT_EXPORT static CProfileIterator* Get_Iterator(void);
	//	{
	//
	//		return new CProfileIterator( &Root );
	//	}
	static void Release_Iterator(CProfileIterator* iterator) { delete (iterator); }

	BT_EXPORT static void dumpRecursive(CProfileIterator* profileIterator, int spacing);

	BT_EXPORT static void dumpAll();

private:
	static int FrameCounter;
	static unsigned long int ResetTime;
};

#endif  //#ifndef BT_NO_PROFILE

///ProfileSampleClass is a simple way to profile a function's scope
///Use the BT_PROFILE macro at the start of scope to time
class CProfileSample
{
public:
	BT_EXPORT CProfileSample(const char* name);

	BT_EXPORT ~CProfileSample(void);
};

#define BT_PROFILE(name) CProfileSample __profile(name)

#endif  //BT_QUICK_PROF_H
