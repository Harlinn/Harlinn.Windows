// abseil_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gtest/gtest.h>

#include "absl/base/config.h"
#include "absl/base/internal/per_thread_tls.h"
#include "absl/debugging/symbolize.h"
#include "absl/flags/usage.h"
#include "absl/flags/internal/parse.h"
#include "absl/flags/flag.h"
#include "absl/flags/internal/program_name.h"
#include "absl/strings/string_view.h"

static const char kTestUsageMessage[] = "Custom usage message";

#if ABSL_PER_THREAD_TLS
extern ABSL_PER_THREAD_TLS_KEYWORD char symbolize_test_thread_small[1];
extern ABSL_PER_THREAD_TLS_KEYWORD char
symbolize_test_thread_big[2 * 1024 * 1024];
#endif



int main( int argc, char** argv )
{
#if ABSL_PER_THREAD_TLS
    // Touch the per-thread variables.
    symbolize_test_thread_small[0] = 0;
    symbolize_test_thread_big[0] = 0;
#endif

    absl::InitializeSymbolizer( argv[0] );

    (void)absl::GetFlag( FLAGS_undefok );  // Force linking of parse.cc
    absl::flags_internal::SetProgramInvocationName( "usage_test" );
    absl::SetProgramUsageMessage( kTestUsageMessage );

    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}

