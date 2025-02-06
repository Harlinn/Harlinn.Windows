#pragma once
#include <windows.h>
#include <string>

HRESULT FileOpen(const std::wstring& title, std::wstring& file, bool bVideo, bool& bAddModel);
