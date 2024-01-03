#pragma once
#ifndef __HCCAPPLICATIONOPTIONS_H__
#define __HCCAPPLICATIONOPTIONS_H__
/*
   Copyright 2024 Espen Harlinn

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

#include <HCCDef.h>
#include <HCCLoggerOptions.h>

namespace Harlinn::Common::Core
{
    class ApplicationOptions : public std::enable_shared_from_this<ApplicationOptions>
    {
        std::shared_ptr<Logging::LoggerOptions> loggerOptions_;
    public:
        using Element = Xml::Dom::Element;
        ApplicationOptions()
            : loggerOptions_( std::make_shared<Logging::LoggerOptions>() )
        { }

        ApplicationOptions( const std::shared_ptr<Logging::LoggerOptions>& loggerOptions )
            : loggerOptions_( loggerOptions )
        {
        }

        ApplicationOptions( const ApplicationOptions& other ) = delete;
        ApplicationOptions( ApplicationOptions&& other ) = delete;
        ApplicationOptions& operator = ( const ApplicationOptions& other ) = delete;
        ApplicationOptions& operator = ( ApplicationOptions&& other ) = delete;

        virtual void ReadFrom( const Element& element )
        {
            auto loggingElement = element.FindElement( L"Logging" );
            if ( loggingElement )
            {
                if ( loggerOptions_ == nullptr )
                {
                    loggerOptions_ = std::make_shared<Logging::LoggerOptions>( );
                }
                loggerOptions_->ReadFrom( loggingElement );
            }
        }

        static WideString DefaultConfigurationFilename( )
        {
            return IO::File::GetExecutableW( ) + L".options";
        }


        void Load( const WideString& filename )
        {
            Xml::Dom::Document document = Xml::Dom::Document::Create( );
            document.SetAsync( false );
            document.SetValidateOnParse( false );
            document.SetResolveExternals( false );
            document.SetPreserveWhiteSpace( false );
            if ( document.Load( filename ) )
            {
                auto documentElement = document.DocumentElement( );
                if ( documentElement )
                {
                    this->ReadFrom( documentElement );
                }
            }
        }
        void Load( )
        {
            auto filename = DefaultConfigurationFilename( );
            if ( IO::File::Exist( filename ) )
            {
                Load( filename );
            }
        }


        template<typename ApplicationOptionsT = ApplicationOptions>
            requires std::is_base_of_v<ApplicationOptions, ApplicationOptionsT>
        static std::shared_ptr<ApplicationOptionsT> LoadFromFile( const WideString& filename, const WideString& elementTagName )
        {
            Xml::Dom::Document document = Xml::Dom::Document::Create( );
            document.SetAsync( false );
            document.SetValidateOnParse( false );
            document.SetResolveExternals( false );
            document.SetPreserveWhiteSpace( false );
            if ( document.Load( filename ) )
            {
                auto documentElement = document.DocumentElement( );
                if ( documentElement )
                {
                    auto element = documentElement.FindElement( elementTagName.c_str( ) );
                    if ( element )
                    {
                        auto result = std::make_shared<ApplicationOptionsT>( );
                        result->ReadFrom( element );
                        return result;
                    }
                }
            }
            return {};
        }

        template<typename ApplicationOptionsT = ApplicationOptions>
            requires std::is_base_of_v<ApplicationOptions, ApplicationOptionsT>
        static std::shared_ptr<ApplicationOptionsT> LoadFromFile( const WideString& filename )
        {
            Xml::Dom::Document document = Xml::Dom::Document::Create( );
            document.SetAsync( false );
            document.SetValidateOnParse( false );
            document.SetResolveExternals( false );
            document.SetPreserveWhiteSpace( false );
            if ( document.Load( filename ) )
            {
                auto documentElement = document.DocumentElement( );
                if ( documentElement )
                {
                    auto result = std::make_shared<ApplicationOptionsT>( );
                    result->ReadFrom( documentElement );
                    return result;
                }
            }
            return {};
        }

        template<typename ApplicationOptionsT = ApplicationOptions>
            requires std::is_base_of_v<ApplicationOptions, ApplicationOptionsT>
        static std::shared_ptr<ApplicationOptionsT> LoadFromFile( )
        {
            auto filename = DefaultConfigurationFilename( );
            if ( IO::File::Exist( filename ) )
            {
                return LoadFromFile<ApplicationOptionsT>( filename );
            }
            else
            {
                return std::make_shared<ApplicationOptionsT>( );
            }
        }



        const std::shared_ptr<Logging::LoggerOptions>& LoggerOptions( ) const noexcept
        {
            return loggerOptions_;
        }


    };
}

#endif
