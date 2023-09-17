#include "pch.h"
#include <HCCApplication.h>
#include <HCCSync.h>

namespace Harlinn::Common::Core
{

    HCC_EXPORT Application* Application::instance_ = nullptr;

    Application::Application( const std::shared_ptr<ApplicationOptions>& options )
        : options_( options ),
          loggingBackend_( options->LoggingBackendOptions() )
    {
        instance_ = this;
    }
    Application::~Application( )
    {
        instance_ = nullptr;
    }

    void Application::HandleDllMainEvent( HMODULE moduleHandle, DWORD reason, LPVOID freeLibrary ) noexcept
    {
        try
        {
            switch ( reason )
            {
                case DLL_PROCESS_ATTACH:
                    break;
                case DLL_THREAD_ATTACH:
                    break;
                case DLL_THREAD_DETACH:
                    if ( instance_ )
                    {

                    }
                    break;
                case DLL_PROCESS_DETACH:
                    break;
            }
        }
        catch ( ... )
        {
        }
    }

    void Application::Process( const Message& message ) noexcept
    {
    }

    

}
