#pragma once
#ifndef HCCSERVICERUNNER_H_
#define HCCSERVICERUNNER_H_
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

#include <HCCDebugServiceHost.h>

namespace Harlinn::Common::Core::Services
{

    template<typename DerivedT, typename ServiceT, typename ApplicationOptionsT = Core::ApplicationOptions>
    class ServiceRunner
    {
    public:
        using DerivedType = DerivedT;
        using ServiceType = ServiceT;
        using ApplicationOptionsType = ApplicationOptionsT;

        class Options
        {
        public:

            WideString username_;
            WideString password_;
            bool help_ = false;
            bool install_ = false;
            bool uninstall_ = false;
            bool start_ = false;
            bool stop_ = false;
            bool debug_ = false;
            WideString optionsFilename_;
            boost::program_options::options_description optionsDescription_;
            boost::program_options::variables_map variablesMap_;
        public:
            Options( )
                : optionsDescription_( "Allowed options" )
            {
                MakeOptionsDescription( );
            }
        private:
            void MakeOptionsDescription( )
            {
                namespace po = boost::program_options;
                optionsDescription_.add_options( )
                    ( "help", po::wvalue<bool>( &help_ )->implicit_value( true ), "produce help message" )
                    ( "username", po::wvalue<WideString>( &username_ ), "The user name of the service login account" )
                    ( "password", po::wvalue<WideString>( &password_ ), "The password of the service login account" )
                    ( "install", po::wvalue<bool>( &install_ )->implicit_value( true ), "Installs this application as a service." )
                    ( "uninstall", po::wvalue<bool>( &uninstall_ )->implicit_value( true ), "Uninstall this application as a service." )
                    ( "start", po::wvalue<bool>( &start_ )->implicit_value( true ), "Starts the service." )
                    ( "stop", po::wvalue<bool>( &stop_ )->implicit_value( true ), "Stops the service." )
                    ( "debug", po::wvalue<bool>( &debug_ )->implicit_value( true ), "Runs this application as a console application." )
                    ( "options", po::wvalue<WideString>( &optionsFilename_ ), "Specifies the application options filename" );
            }
        public:
            void Parse( int argc, const wchar_t** argv )
            {
                namespace po = boost::program_options;
                po::store( po::wcommand_line_parser( argc, argv )
                    .options( optionsDescription_ )
                    .run( ),
                    variablesMap_ );
                po::notify( variablesMap_ );
            }

            void DisplayOptions( ) const
            {
                optionsDescription_.print( std::cout );
            }

            [[nodiscard]] const WideString& Username( ) const noexcept
            {
                return username_;
            }

            [[nodiscard]] const WideString& Password( ) const noexcept
            {
                return password_;
            }

            [[nodiscard]] bool Help( ) const noexcept
            {
                return help_;
            }
            [[nodiscard]] bool Install( ) const noexcept
            {
                return install_;
            }
            [[nodiscard]] bool Uninstall( ) const noexcept
            {
                return uninstall_;
            }
            [[nodiscard]] bool Start( ) const noexcept
            {
                return start_;
            }
            [[nodiscard]] bool Stop( ) const noexcept
            {
                return stop_;
            }
            [[nodiscard]] bool Debug( ) const noexcept
            {
                return debug_;
            }

            [[nodiscard]] bool Execute( ) const noexcept
            {
                return help_ == false &&
                    install_ == false &&
                    uninstall_ == false &&
                    start_ == false &&
                    stop_ == false;
            }


            [[nodiscard]] const WideString& OptionsFilename( ) const noexcept
            {
                return optionsFilename_;
            }

            [[nodiscard]] bool UseDefaultOptionsFilename( ) const noexcept
            {
                if ( optionsFilename_.size( ) )
                {
                    return IO::File::Exist( optionsFilename_ ) == false;
                }
                return true;
            }
        };

        virtual void AfterApplicationStart( const std::shared_ptr<Harlinn::Common::Core::Application>& application )
        {

        }

        virtual void BeforeApplicationStop( const std::shared_ptr<Harlinn::Common::Core::Application>& application )
        {

        }

        int RunServiceApplication( const std::shared_ptr<Services::Application>& application )
        {
            //ReportMessage( "In RunServiceApplication" );
            application->RegisterServiceType<ServiceType>( );
            
            application->Start( );
            this->AfterApplicationStart( application );
            HCC_DEBUG( "Service started." );
            application->Run( );
            HCC_DEBUG( "Service stopped." );
            this->BeforeApplicationStop( application );
            application->Stop( );
            return 0;
        }


        int RunInDebugHost( const Options& options )
        {
            //ReportMessage( "In RunInDebugHost" );
            std::shared_ptr<ApplicationOptions> applicationOptions;
            if ( options.UseDefaultOptionsFilename( ) )
            {
                applicationOptions = ApplicationOptions::LoadFromFile<ApplicationOptionsType>( );
            }
            else
            {
                applicationOptions = ApplicationOptions::LoadFromFile<ApplicationOptionsType>( options.OptionsFilename( ) );
            }
            Services::DebugServiceHost serviceHost;
            auto application = std::make_shared<Services::Application>( applicationOptions, &serviceHost );
            auto result = RunServiceApplication( application );
            return result;
        }

        int RunInWindowsHost( const Options& options )
        {
            //ReportMessage( "In RunInWindowsHost" );
            if ( ServiceType::IsRegistered( ) == false )
            {
                return RunInDebugHost( options );
            }
            else
            {
                std::shared_ptr<ApplicationOptions> applicationOptions;
                if ( options.UseDefaultOptionsFilename( ) )
                {
                    applicationOptions = ApplicationOptions::LoadFromFile<ApplicationOptionsType>( );
                }
                else
                {
                    applicationOptions = ApplicationOptions::LoadFromFile<ApplicationOptionsType>( options.OptionsFilename( ) );
                }
                Services::WindowsServiceHost serviceHost;
                auto application = std::make_shared<Services::Application>( applicationOptions, &serviceHost );
                auto result = RunServiceApplication( application );
                return result;
            }
        }


        int InstallService( const Options& options )
        {
            int result = 0;
            auto username = options.Username( );
            auto password = options.Password( );

            if ( username.empty( ) )
            {
                username = Services::ServiceControlManager::NetworkService;
                password.clear( );
            }
            else if ( username == Services::ServiceControlManager::LocalSystem || username == Services::ServiceControlManager::LocalService )
            {
                password.clear( );
            }
            if ( password.empty( ) )
            {
                ServiceType::RegisterService( username.c_str( ), nullptr );
            }
            else
            {
                ServiceType::RegisterService( username.c_str( ), password.c_str( ) );
            }
            return result;
        }

        int UninstallService( const Options& options )
        {
            int result = 0;
            ServiceType::UnregisterService( );
            return result;
        }

        int StartService( const Options& options )
        {
            int result = 0;
            ServiceType::StartService( );
            return result;
        }

        int StopService( const Options& options )
        {
            int result = 0;
            ServiceType::StopService( );
            return result;
        }

        

        int Run( const Options& options )
        {
            int result = 0;
            std::shared_ptr<ApplicationOptions> applicationOptions;
            if ( options.UseDefaultOptionsFilename( ) )
            {
                applicationOptions = ApplicationOptions::LoadFromFile<ApplicationOptionsType>( );
            }
            else
            {
                applicationOptions = ApplicationOptions::LoadFromFile<ApplicationOptionsType>( options.OptionsFilename( ) );
            }
            auto application = std::make_shared<Harlinn::Common::Core::Application>( applicationOptions );
            application->Start( );
            this->AfterApplicationStart( application );
            try
            {
                if ( options.Help( ) )
                {
                    options.DisplayOptions( );
                }
                else if ( options.Install( ) )
                {
                    InstallService( options );
                }
                else if ( options.Uninstall( ) )
                {
                    UninstallService( options );
                }
                else if ( options.Start( ) )
                {
                    StartService( options );
                }
                else if ( options.Stop( ) )
                {
                    StopService( options );
                }
            }
            catch ( const Exception& exception )
            {
                auto typeName = ToWideString( typeid( exception ).name( ) );
                auto exceptionMessage = exception.Message( );

                auto message = std::format( L"{}:{}", typeName, exceptionMessage );
                _putws( message.c_str( ) );
            }
            catch ( const std::exception& exception )
            {
                auto typeName = typeid( exception ).name( );
                auto exceptionMessage = exception.what( );

                auto message = std::format( "{}:{}", typeName, exceptionMessage );
                puts( message.c_str( ) );

            }
            catch ( ... )
            {
                std::puts( "Unknown exception caught in Run" );
            }
            this->BeforeApplicationStop( application );
            application->Stop( );
            return result;
        }


        int Main( int argc, const wchar_t** argv )
        {
            Harlinn::Common::Core::Com::Initialize( );
            int result = 0;
            Options options;
            options.Parse( argc, argv );
            if ( options.Execute( ) )
            {
                if ( options.Debug( ) )
                {
                    result = RunInDebugHost( options );
                }
                else
                {
                    result = RunInWindowsHost( options );
                }
            }
            else
            {
                result = Run( options );
            }
            Harlinn::Common::Core::Com::Uninitialize( );
            return result;

        }



    };

}

#endif
