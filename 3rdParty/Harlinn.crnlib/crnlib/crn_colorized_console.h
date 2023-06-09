// File: crn_colorized_console.h
// This software is in the public domain. Please see license.txt.
#pragma once
#include "crn_console.h"

namespace crnlib
{
   class colorized_console
   {
   public:
      static void init();
      static void deinit();
      static void tick();

   private:
      static bool console_output_func(eConsoleMessageType type, const char* pMsg, void* pData);
   };

} // namespace crnlib
