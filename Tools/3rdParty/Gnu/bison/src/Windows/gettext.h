#pragma once
#ifndef HARLINN_WINDOWS_BISON_GETTEXT_H_
#define HARLINN_WINDOWS_BISON_GETTEXT_H_

#define gettext( MessageId ) ( (const char*)(MessageId) )
#define ngettext( MessageId1, MessageId2, n ) ( (n) == 1? ((const char*)(MessageId1)):((const char*)(MessageId2)) )

#endif
