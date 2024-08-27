#pragma once
#ifndef BARRELMANEXPORT_H_
#define BARRELMANEXPORT_H_

#ifdef BUILDING_BARRELMAN
 #define BARRELMAN_EXPORT __declspec(dllexport)
#else
 #define BARRELMAN_EXPORT __declspec(dllimport)
#endif

#endif
