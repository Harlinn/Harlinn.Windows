#include "Utils.h"
#include "bullet/LinearMath/btAlignedAllocator.h"
#include <math.h>
#include <stdlib.h>
#include <intrin.h>


int gReportNanoseconds = 0;
int gReportAverageTimes = 0;
int gExitOnError = 0;
const char* gAppName = NULL;

uint64_t ReadTicks( void )
{
	return __rdtsc( );
}
double TicksToCycles( uint64_t delta )
{
	return double( delta );
}

double TicksToSeconds( uint64_t delta )
{
	return double( delta );
}

void* GuardCalloc( size_t count, size_t size, size_t* objectStride )
{
	if ( objectStride )
		*objectStride = size;
	return (void*)btAlignedAlloc( count * size, 16 );
}
void GuardFree( void* buf )
{
	btAlignedFree( buf );
}




uint32_t random_number32( void )
{
	return ( (uint32_t)rand( ) << 16 ) ^ rand( );
}

uint64_t random_number64( void )
{
	return ( (uint64_t)rand( ) << 48 ) ^
		( (uint64_t)rand( ) << 32 ) ^
		( (uint64_t)rand( ) << 16 ) ^
		rand( );
}