/*
* Copyright 2016 Google Inc.
*
* Use of this source code is governed by a BSD-style license that can be
* found in the LICENSE file.
*/

#ifndef Application_DEFINED
#define Application_DEFINED

#include <skia/core/SkTypes.h>

namespace sk_app {

class ApplicationFactory;
class SK_API Application 
{
public:
    virtual ~Application() {}

    virtual void onIdle() = 0;

    static int Run( ApplicationFactory& applicationFactory, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow );
    static int Run( ApplicationFactory& applicationFactory, HINSTANCE hInstance, int show, int argc, char** argv );
    static int Run( ApplicationFactory& applicationFactory, int argc, char** argv );

};

class SK_API ApplicationFactory
{
public:
    virtual ~ApplicationFactory( )
    {
    }

    virtual Application* Create( int argc, char** argv, void* platformData ) = 0;

};


}   // namespace sk_app

#endif
