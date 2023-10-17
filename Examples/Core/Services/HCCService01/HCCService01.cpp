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

