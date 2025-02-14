#pragma once
#ifndef HCCLOGGERSTORAGE_H_
#define HCCLOGGERSTORAGE_H_
/*
   Copyright 2024-2025 Espen Harlinn

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

#include <HCCLoggerTypes.h>
#include <HCCLoggerImpl.h>

namespace Harlinn::Common::Core::Logging
{
    namespace Cursors
    {
        class Cursor
        {
        public:
            Cursor( ) = default;
            virtual ~Cursor( ) = default;
            virtual UInt32 AddRef( ) = 0;
            virtual UInt32 Release( ) = 0;
            virtual bool MoveFirst( ) = 0;
            virtual bool MovePrevious( ) = 0;
            virtual bool MoveNext( ) = 0;
            virtual bool MoveLast( ) = 0;
            virtual bool Delete( ) = 0;

        };

        class ComputerInfoCursor : public Cursor
        {
        public:
            using ValueType = Types::ComputerInfo;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class UserInfoCursor : public Cursor
        {
        public:
            using ValueType = Types::UserInfo;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class ExecutableInfoCursor : public Cursor
        {
        public:
            using ValueType = Types::ExecutableInfo;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class ConfigurationFileInfoCursor : public Cursor
        {
        public:
            using ValueType = Types::ConfigurationFileInfo;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class WindowsVersionInfoCursor : public Cursor
        {
        public:
            using ValueType = Types::WindowsVersionInfo;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class ProcessInfoCursor : public Cursor
        {
        public:
            using ValueType = Types::ProcessInfo;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class LogSiteDataCursor : public Cursor
        {
        public:
            using ValueType = Types::LogSiteData;
            using ValuePtr = std::unique_ptr<ValueType>;

            virtual ValuePtr Current( ) = 0;
        };

        class BufferCursor : public Cursor
        {
        public:
            using ValueType = Internal::Buffer;
            using ValuePtr = Internal::BufferPointer;

            virtual ValuePtr Current( ) = 0;
        };

    }

    class Storage : public std::enable_shared_from_this<Storage>
    {
    public:
        template<typename DerivedT>
        using LoggerObject = LoggerObject<DerivedT>;
        template<typename DerivedT>
        using Identified = Types::Identified<DerivedT>;
        using DomainObject = Types::DomainObject;

        using ComputerInfo = Types::ComputerInfo;
        using ComputerInfoPtr = std::unique_ptr<ComputerInfo>;

        using UserInfo = Types::UserInfo;
        using UserInfoPtr = std::unique_ptr<UserInfo>;

        using ExecutableInfo = Types::ExecutableInfo;
        using ExecutableInfoPtr = std::unique_ptr<ExecutableInfo>;

        using ConfigurationFileInfo = Types::ConfigurationFileInfo;
        using ConfigurationFileInfoPtr = std::unique_ptr<ConfigurationFileInfo>;

        using WindowsVersionInfoKey = Types::WindowsVersionInfoKey;
        using WindowsVersionInfoKeyPtr = std::unique_ptr<WindowsVersionInfoKey>;

        using WindowsVersionInfo = Types::WindowsVersionInfo;
        using WindowsVersionInfoPtr = std::unique_ptr<WindowsVersionInfo>;

        using ProcessInfo = Types::ProcessInfo;
        using ProcessInfoPtr = std::unique_ptr<ProcessInfo>;

        using LogSiteData = Types::LogSiteData;
        using LogSiteDataPtr = std::unique_ptr<LogSiteData>;

        using BufferKey = Internal::BufferKey;
        using Buffer = Internal::Buffer;
        using BufferPointer = Internal::BufferPointer;

        using ComputerInfoCursor = Cursors::ComputerInfoCursor;
        using ComputerInfoCursorPtr = ReferenceCountedPtr<ComputerInfoCursor>;

        using UserInfoCursor = Cursors::UserInfoCursor;
        using UserInfoCursorPtr = ReferenceCountedPtr<UserInfoCursor>;

        using ExecutableInfoCursor = Cursors::ExecutableInfoCursor;
        using ExecutableInfoCursorPtr = ReferenceCountedPtr<ExecutableInfoCursor>;

        using ConfigurationFileInfoCursor = Cursors::ConfigurationFileInfoCursor;
        using ConfigurationFileInfoCursorPtr = ReferenceCountedPtr<ConfigurationFileInfoCursor>;

        using WindowsVersionInfoCursor = Cursors::WindowsVersionInfoCursor;
        using WindowsVersionInfoCursorPtr = ReferenceCountedPtr<WindowsVersionInfoCursor>;

        using ProcessInfoCursor = Cursors::ProcessInfoCursor;
        using ProcessInfoCursorPtr = ReferenceCountedPtr<ProcessInfoCursor>;

        using LogSiteDataCursor = Cursors::LogSiteDataCursor;
        using LogSiteDataCursorPtr = ReferenceCountedPtr<LogSiteDataCursor>;

        using BufferCursor = Cursors::BufferCursor;
        using BufferCursorPtr = ReferenceCountedPtr<BufferCursor>;


        Storage( ) = default;
        virtual ~Storage( ) = default;

        
        virtual ComputerInfoCursorPtr GetComputerInfoCursor( ) = 0;
        virtual ComputerInfoPtr GetComputerInfoById( const Guid& id ) = 0;
        virtual ComputerInfoPtr GetComputerInfoByDomainAndName( const WideString& domainName, const WideString& computerName ) = 0;

        virtual UserInfoCursorPtr GetUserInfoCursor( ) = 0;
        virtual UserInfoPtr GetUserInfoById( const Guid& id ) = 0;
        virtual UserInfoPtr GetUserInfoByDomainAndName( const WideString& domainName, const WideString& computerName ) = 0;

        virtual ExecutableInfoCursorPtr GetExecutableInfoCursor( ) = 0;
        virtual ExecutableInfoPtr GetExecutableInfoById( const Guid& id ) = 0;
        virtual ExecutableInfoPtr GetExecutableInfoByPath( const WideString& path ) = 0;

        virtual ConfigurationFileInfoCursorPtr GetConfigurationFileInfoCursor( ) = 0;
        virtual ConfigurationFileInfoPtr GetConfigurationFileInfoById( const Guid& id ) = 0;
        virtual ConfigurationFileInfoPtr GetConfigurationFileInfoByPath( const WideString& path ) = 0;

        virtual WindowsVersionInfoCursorPtr GetWindowsVersionInfoCursor( ) = 0;
        virtual WindowsVersionInfoPtr GetWindowsVersionInfoByKey( const WindowsVersionInfoKey& id ) = 0;
        virtual WindowsVersionInfoPtr GetWindowsVersionInfoByVersionInfo( const WindowsVersionInfo& versionInfo ) = 0;

        virtual ProcessInfoCursorPtr GetProcessInfoCursor( ) = 0;
        virtual ProcessInfoPtr GetProcessInfoById( const Guid& id ) = 0;
        virtual ProcessInfoPtr GetProcessInfoByPath( const WideString& path ) = 0;

        virtual LogSiteDataCursorPtr GetLogSiteDataCursor( ) = 0;
        virtual LogSiteDataPtr GetLogSiteDataById( const Guid& id ) = 0;
        virtual LogSiteDataPtr GetLogSiteDataByLogSite( const LogSite& logSite ) = 0;

        virtual BufferCursorPtr GetBufferCursor( ) = 0;
        virtual BufferPointer GetBufferById( const Guid& id ) = 0;
        virtual BufferPointer GetBufferByKey( const BufferKey& bufferKey ) = 0;


    };
}

#endif
