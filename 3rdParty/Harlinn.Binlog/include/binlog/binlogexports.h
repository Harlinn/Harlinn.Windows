#pragma once
#ifndef HARLINN_BINLOG_BINLOGEXPORTS_H_
#define HARLINN_BINLOG_BINLOGEXPORTS_H_

#ifdef BUILDING_HARLINN_BINLOG
#define HBINLOG_EXPORT __declspec(dllexport)
#define HBINLOG_TEMPLATE_EXPORT __declspec(dllexport)
#define HBINLOG_TEMPLATE_EXPORT_DECL
#else
#define HBINLOG_EXPORT __declspec(dllimport)
#define HBINLOG_TEMPLATE_EXPORT __declspec(dllimport)
#define HBINLOG_TEMPLATE_EXPORT_DECL __declspec(dllimport)
#pragma comment(lib,"Harlinn.Binlog.lib")
#endif

#ifdef _DEBUG
#define HBINLOG_INLINE_DECL HBINLOG_EXPORT
#define HBINLOG_INLINE 
#else
#define HBINLOG_INLINE_DECL 
#define HBINLOG_INLINE inline
#endif

#endif
