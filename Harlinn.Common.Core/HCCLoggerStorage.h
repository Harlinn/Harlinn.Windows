#pragma once
#ifndef HCCLOGGERSTORAGE_H_
#define HCCLOGGERSTORAGE_H_

#include <HCCLoggerTypes.h>
#include <HCCLoggerImpl.h>

namespace Harlinn::Common::Core::Logging
{
    class Storage : public std::enable_shared_from_this<Storage>
    {
    public:
        template<typename DerivedT>
        using LoggerObject = LoggerObject<DerivedT>;
        template<typename DerivedT>
        using Identified = Types::Identified<DerivedT>;
        using DomainObject = Types::DomainObject;
        using ComputerInfo = Types::ComputerInfo;
        using UserInfo = Types::UserInfo;
        using ExecutableInfo = Types::ExecutableInfo;
        using ConfigurationFileInfo = Types::ConfigurationFileInfo;
        using WindowsVersionInfoKey = Types::WindowsVersionInfoKey;
        using WindowsVersionInfo = Types::WindowsVersionInfo;
        using ProcessInfo = Types::ProcessInfo;
        using LogSiteData = Types::LogSiteData;
        using Buffer = Internal::Buffer;
        using BufferKey = Internal::BufferKey;

        


    };
}

#endif
