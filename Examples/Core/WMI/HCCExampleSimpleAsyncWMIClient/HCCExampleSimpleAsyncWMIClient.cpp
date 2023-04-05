#include <HCCwbem.h>
namespace hcc = Harlinn::Common::Core;

int main()
{
    int result = 1;

    // Step 1: Initialize COM.
    hcc::Com::Initialize( );
    // Step 2: Set general COM security levels
    hcc::Com::InitializeClientSecurity( );

    try
    {
        // Step 3: Obtain the initial locator to WMI 
        auto locator = hcc::WbemLocator::Create( );

        // Step 4: Connect to WMI using the locator
        auto services = locator.ConnectServer( L"ROOT\\CIMV2" );

        std::cout << "Connected to ROOT\\CIMV2 WMI namespace" << std::endl;

        // Step 5: Set security levels on the proxy 
        hcc::Com::SetClientProxyBlanket( services );

        // Step 6: Set up the event sink 
        hcc::IWbemObjectSinkDispatcher sink;
        hcc::IWbemObjectSinkDispatcher<>::ContainerType container;

        sink.OnIndicate.connect( [&container]( auto& objects )
        {
            for ( auto& object : objects )
            {
                container.emplace_back( std::move(object) );
            }
        } );

        std::atomic<bool> done = false;
        sink.OnSetStatus.connect( [&done]( long flags, HRESULT hResult, const hcc::SysString& paramName, const hcc::WbemClassObject& paramObject )
        {
            if ( flags == WBEM_STATUS_COMPLETE )
            {
                done = true;
            }
        } );


        // Step 7: Use the WbemServices object to make requests of WMI
        // For example, get the name of the operating system
        services.ExecQueryAsync( L"SELECT * FROM Win32_OperatingSystem", &sink );

        // Step 8: Wait until the async operation is done ...
        while ( done == false )
        {
            Sleep( 500 );
        }
        services.CancelAsyncCall( &sink );


        // Step 9: Get the data from the query in step 7 
        for ( auto& object : container )
        {
            // Get the value of the Name property
            hcc::Variant property = object.Get( L"Name" );
            std::wcout << "OS Name : " << property.bstrVal << std::endl;
        }
        result = 0;
    }
    catch ( const hcc::Exception& exc )
    {
    }
    catch ( const std::exception& exc )
    {
    }
    catch ( ... )
    {
    }
    hcc::Com::Uninitialize( );
    return result;

}


