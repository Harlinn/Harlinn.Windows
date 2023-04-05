#pragma once
#ifndef __HCCSERVICE_H__
#define __HCCSERVICE_H__

#include <HCCDef.h> 

namespace Harlinn::Common::Core::Services
{

    class ServiceBase
    {
    public:
        virtual ~ServiceBase()
        { }

        virtual void OnStart( ) noexcept
        {

        }

        virtual void OnStop( ) noexcept
        {

        }


    };


    class Service
    {

    };
    


    class ServiceControlManager
    {

    };


    class ServiceApplication
    {
    public:
        using Container = std::unordered_map<std::string_view, std::unique_ptr<ServiceBase> >;
    private:

        Container container_;
    public:
        ServiceApplication( )
        {

        }

        Int32 Run( )
        {
            return 0;
        }

    };
}

#endif
