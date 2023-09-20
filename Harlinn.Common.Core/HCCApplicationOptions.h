#pragma once
#ifndef __HCCAPPLICATIONOPTIONS_H__
#define __HCCAPPLICATIONOPTIONS_H__

#include <HCCDef.h>
#include <HCCLoggerBackendOptions.h>

namespace Harlinn::Common::Core
{
    class ApplicationOptions : public std::enable_shared_from_this<ApplicationOptions>
    {
        std::shared_ptr<Logging::BackendOptions> loggingBackendOptions_;
    public:
        using Element = Xml::Dom::Element;
        ApplicationOptions()
            : loggingBackendOptions_( std::make_shared<Logging::BackendOptions>() )
        { }

        ApplicationOptions( const std::shared_ptr<Logging::BackendOptions>& loggingBackendOptions )
            : loggingBackendOptions_( loggingBackendOptions )
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
                if ( loggingBackendOptions_ == nullptr )
                {
                    loggingBackendOptions_ = std::make_shared<Logging::BackendOptions>( );
                }
                loggingBackendOptions_->ReadFrom( loggingElement );
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



        const std::shared_ptr<Logging::BackendOptions>& LoggingBackendOptions( ) const noexcept
        {
            return loggingBackendOptions_;
        }


    };
}

#endif
