/*
   Copyright 2024-2026 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <HCCServiceRunner.h>

using namespace Harlinn::Common::Core;

class MyService : public Services::Service<MyService>
{
public:
    using Base = Services::Service<MyService>;

    MyService()
        : Base()
    { }

protected:
    virtual void Done( ) override
    {
        // Add service termination code here
        Base::Done( );
    }

    virtual void Run( ) override
    {
        // Add service initialization code here
        Base::Run( );
    }
public:
    static constexpr const wchar_t* ServiceName( )
    {
        return L"MyTestService";
    }

    static constexpr const wchar_t* ServiceDisplayName( )
    {
        return L"MyTestService version 1.0";
    }
};

class MyServiceRunner : public Services::ServiceRunner<MyServiceRunner, MyService>
{

};


int wmain( int argc, const wchar_t** argv )
{
    MyServiceRunner serviceRunner;
    return serviceRunner.Main( argc, argv );
}

