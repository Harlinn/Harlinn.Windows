#include "pch.h"
#include "HCCService.h"
#include "HCCDebugServiceHost.h"

namespace Harlinn::Common::Core::Services
{
    Application::Application( const std::shared_ptr<ApplicationOptions>& options, IServiceHost* serviceHost )
        : Base( options ), serviceHost_( serviceHost )
    {

    }
    Application::~Application( ) = default;
}
