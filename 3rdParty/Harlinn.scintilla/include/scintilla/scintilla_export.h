#pragma once
#ifndef HARLINN_SCINTILLA_SCINTILLA_EXPORT_H_
#define HARLINN_SCINTILLA_SCINTILLA_EXPORT_H_

#ifdef BUILDING_HARLINN_SCINTILLA
#define SCINTILLA_EXPORT __declspec(dllexport)
#else
#define SCINTILLA_EXPORT __declspec(dllimport)
#pragma comment(lib,"Harlinn.scintilla.lib")
#endif

#endif
