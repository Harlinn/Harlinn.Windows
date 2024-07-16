#include <stdlib.h>

#include "common/tools_common.h"

HAOM_EXPORT void _usage_exit(void) { exit(EXIT_FAILURE); }

usage_exit_func current_usage_exit_func = &_usage_exit;

HAOM_EXPORT usage_exit_func set_usage_exit( usage_exit_func new_usage_exit_func )
{
    current_usage_exit_func = new_usage_exit_func;
}

HAOM_EXPORT void usage_exit( void )
{
    if ( current_usage_exit_func != NULL )
    {
        current_usage_exit_func( );
    }
    else
    {
        _usage_exit;
    }
}
