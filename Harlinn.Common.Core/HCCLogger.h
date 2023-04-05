#pragma once
#ifndef __HCCLOGGER_H__
#define __HCCLOGGER_H__

#include <HCCPersistent.h>
#include <HCCLoggerLevel.h>

namespace Harlinn::Common::Core::Logging
{


    template< Level enabledLevels = Level::Default >
    struct BuildOptions
    {
        static constexpr Level EnabledLevels = enabledLevels;
    };

    class LogSite
    {
        UInt64 id_ = 0;
        Logging::Level level_ = Logging::Level::None;
        std::string message_;
        std::vector<Byte> argumentsDescriptor_;
        bool isFixedSize_ = false;
        size_t fixedSize_ = 0;
        UInt32 line_ = 0;
        UInt32 column_ = 0;
        std::string file_;
        std::string function_;
    public:
        using PrimaryKeyType = UInt64;

        LogSite()
        { }

        constexpr LogSite( Logging::Level level, const char* message, const Byte* argumentsDescriptor, size_t argumentsDescriptorSize, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function ) noexcept
            : level_( level ), message_( message ), argumentsDescriptor_( argumentsDescriptor, argumentsDescriptor + argumentsDescriptorSize ), isFixedSize_( isFixedSize ), fixedSize_( fixedSize ), line_( line ), column_( column ), file_( file ), function_( function )
        { }

        auto operator<=>( const LogSite& ) const = default;


        template<typename ReaderT>
        void Read( ReaderT& reader )
        {
            ReadKey( reader );
            ReadData( reader );
        }

        template<typename ReaderT>
        void ReadKey( ReaderT& reader )
        {
            reader.Read( id_ );
        }

        template<typename ReaderT>
        void ReadData( ReaderT& reader )
        {
            reader.Read( level_ );
            reader.Read( message_ );
            reader.Read( argumentsDescriptor_ );
            reader.Read( isFixedSize_ );
            reader.Read( fixedSize_ );
            reader.Read( line_ );
            reader.Read( column_ );
            reader.Read( file_ );
            reader.Read( function_ );
        }

        template<typename WriterT>
        void Write( WriterT& writer ) const
        {
            WriteKey( writer );
            WriteData( writer );
        }

        template<typename WriterT>
        void WriteKey( WriterT& writer ) const
        {
            writer.Write( id_ );
        }

        template<typename WriterT>
        void WriteData( WriterT& writer ) const
        {
            writer.Write( level_ );
            writer.Write( message_ );
            writer.Write( argumentsDescriptor_ );
            writer.Write( isFixedSize_ );
            writer.Write( fixedSize_ );
            writer.Write( line_ );
            writer.Write( column_ );
            writer.Write( file_ );
            writer.Write( function_ );
        }

        void AddTo( XXH64Hasher& hasher ) const noexcept
        {
            hasher.Add( static_cast<UInt16>(level_) );
            hasher.Add( message_ );
            hasher.Add( argumentsDescriptor_.data(), argumentsDescriptor_.size() );
            hasher.Add( isFixedSize_ );
            hasher.Add( fixedSize_ );
            hasher.Add( line_ );
            hasher.Add( column_ );
            hasher.Add( file_ );
            hasher.Add( function_ );
        }

        size_t Hash( ) const noexcept
        {
            XXH64Hasher hasher;
            AddTo( hasher );
            auto result = hasher.Digest( );
            return result;
        }

        const PrimaryKeyType& PrimaryKey( ) const noexcept
        {
            return id_;
        }
        void SetPrimaryKey( const PrimaryKeyType& primaryKey ) noexcept
        {
            id_ = primaryKey;
        }

        constexpr UInt64 Id( ) const noexcept
        {
            return id_;
        }
        constexpr void SetId( UInt64 id ) noexcept
        {
            id_ = id;
        }

        constexpr Logging::Level Level( ) const noexcept
        {
            return level_;
        }
        constexpr const std::string& Message( ) const noexcept
        {
            return message_;
        }
        constexpr const std::vector<Byte>& ArgumentsDescriptor( ) const noexcept
        {
            return argumentsDescriptor_;
        }

        constexpr bool IsFixedSize( ) const noexcept
        {
            return isFixedSize_;
        }
        const size_t FixedSize( ) const noexcept
        {
            return fixedSize_;
        }


        constexpr UInt32 Line( ) const noexcept
        {
            return line_;
        }
        constexpr UInt32 Column( ) const noexcept
        {
            return column_;
        }
        constexpr const std::string& File( ) const noexcept
        {
            return file_;
        }
        constexpr const std::string& Function( ) const noexcept
        {
            return function_;
        }


    };

    namespace Writers
    {
        class ConsoleWriter
        {
        public:
            ConsoleWriter( )
            { }

            template<typename ...Args>
            void WriteLogRecord( const LogSite* site, Args&& ...args ) noexcept
            {
                fmt::print( site->Message(), std::forward<Args>( args )... );
                std::puts( "" );
            }

            void Flush()
            { }
        };
    }


    template< typename WriterT, typename BuildOptionsT = BuildOptions<Level::Default> >
    class Logger
    {
    public:
        using WriterType = WriterT;
        static constexpr Level EnabledLevels = BuildOptionsT::EnabledLevels;
        static constexpr bool HasFixedSizeOptimization = false;
    private:
        Level enabledLevels_;
        WriterType writer_;
    public:
        template<typename ...WriterArgs>
        constexpr Logger( Level enabledLevels, WriterArgs&& ... writerArgs ) noexcept
            : enabledLevels_( enabledLevels ), writer_( std::forward<WriterArgs>( writerArgs )... )
        { }

        WriterType& Writer( )
        {
            return writer_;
        }

        void Flush( )
        {
            writer_.Flush( );
        }


        constexpr bool IsTraceEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Trace ) && IsSet( enabledLevels_, Level::Trace );
        }
        constexpr bool IsDebugEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Debug ) && IsSet( enabledLevels_, Level::Debug );
        }
        constexpr bool IsInfoEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Info ) && IsSet( enabledLevels_, Level::Info );
        }
        constexpr bool IsNoticeEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Notice ) && IsSet( enabledLevels_, Level::Notice );
        }
        constexpr bool IsWarningEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Warning ) && IsSet( enabledLevels_, Level::Warning );
        }
        constexpr bool IsErrorEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Error ) && IsSet( enabledLevels_, Level::Error );
        }
        constexpr bool IsExceptionEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Exception ) && IsSet( enabledLevels_, Level::Exception );
        }
        constexpr bool IsCriticalEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Critical ) && IsSet( enabledLevels_, Level::Critical );
        }
        constexpr bool IsAlertEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Alert ) && IsSet( enabledLevels_, Level::Alert );
        }
        constexpr bool IsEmergencyEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Emergency ) && IsSet( enabledLevels_, Level::Emergency );
        }


        template<typename ... Args>
        void Trace( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsTraceEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Debug( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsDebugEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Info( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsInfoEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Notice( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsNoticeEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Warning( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsWarningEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Error( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsErrorEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Critical( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsCriticalEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Alert( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsAlertEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Emergency( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsEmergencyEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
    };


    



}


#endif

