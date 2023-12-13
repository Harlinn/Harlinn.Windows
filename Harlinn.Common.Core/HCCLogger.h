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

    /// <summary>
    /// Instances of this class are created with static storage duration
    /// inside the functions that call the ThreadLogger API.
    /// 
    /// This implementation assumes that the storage of pointed to by
    /// the formatString, argumentsDescriptor, file and function pointers remain valid 
    /// for the lifetime of the objects.
    /// 
    /// LogSite instances can serialized, but not deserialized. Serialization
    /// copies the data pointed to by the message_, argumentsDescriptor_,
    /// file_ and function_ to the output.
    /// 
    /// Use Types::LogSiteData to deserialize the serialized representation
    /// of the LogSite objects.
    /// </summary>
    class LogSite
    {
        UInt64 id_ = 0;
        Logging::Level level_ = Logging::Level::None;
        const char* formatString_;
        const Byte* argumentsDescriptor_ = nullptr;
        size_t argumentsDescriptorSize_ = 0;
        bool isFixedSize_ = false;
        size_t fixedSize_ = 0;
        UInt32 line_ = 0;
        UInt32 column_ = 0;
        const char* file_ = nullptr;
        const char* function_ = nullptr;
    public:
        using PrimaryKeyType = UInt64;

        constexpr LogSite()
        { }

        constexpr LogSite( Logging::Level level, const char* formatString, const Byte* argumentsDescriptor, size_t argumentsDescriptorSize, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function ) noexcept
            : level_( level ), formatString_( formatString ), argumentsDescriptor_( argumentsDescriptor ), argumentsDescriptorSize_( argumentsDescriptorSize ), isFixedSize_( isFixedSize ), fixedSize_( fixedSize ), line_( line ), column_( column ), file_( file ), function_( function )
        { }

        template<typename ...Types>
        constexpr LogSite( Logging::Level level, const char* formatString, const Tuple<Types...>& argumentsDescriptor, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function ) noexcept
            : level_( level ), formatString_( formatString ), argumentsDescriptor_( reinterpret_cast< const Byte* >( &argumentsDescriptor) ), argumentsDescriptorSize_( sizeof( argumentsDescriptor ) ), isFixedSize_( isFixedSize ), fixedSize_( fixedSize ), line_( line ), column_( column ), file_( file ), function_( function )
        { }

        auto operator<=>( const LogSite& ) const = default;


        /*
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
            reader.Read( argumentsDescriptorBytes_ );
            reader.Read( isFixedSize_ );
            reader.Read( fixedSize_ );
            reader.Read( line_ );
            reader.Read( column_ );
            reader.Read( file_ );
            reader.Read( function_ );
        }
        */

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
            writer.Write( formatString_ );
            writer.Write( argumentsDescriptor_, argumentsDescriptorSize_ );
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
            hasher.Add( formatString_ );
            hasher.Add( argumentsDescriptor_, argumentsDescriptorSize_ );
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
        constexpr std::string_view FormatString( ) const noexcept
        {
            return formatString_;
        }

        constexpr std::span<const Byte> ArgumentsDescriptor( ) const noexcept
        {
            return std::span<const Byte>( argumentsDescriptor_, argumentsDescriptorSize_ );
        }

        constexpr size_t ArgumentsDescriptorSize( ) const noexcept
        {
            return argumentsDescriptorSize_;
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
        constexpr std::string_view File( ) const noexcept
        {
            return file_;
        }
        constexpr std::string_view Function( ) const noexcept
        {
            return function_;
        }
    };

    namespace Types
    {
        class LogSiteData
        {
            UInt64 id_ = 0;
            Logging::Level level_ = Logging::Level::None;
            std::string formatString_;
            std::vector<Byte> argumentsDescriptor_;
            bool isFixedSize_ = false;
            size_t fixedSize_ = 0;
            UInt32 line_ = 0;
            UInt32 column_ = 0;
            std::string file_;
            std::string function_;
            static std::string ToString( std::string_view stringView )
            {
                return std::string( stringView.data( ), stringView.size( ) );
            }
            static std::vector<Byte> ToBytes( std::span<const Byte> data )
            {
                return std::vector<Byte>( data.data( ), data.data( ) + data.size( ) );
            }
        public:
            using PrimaryKeyType = UInt64;

            constexpr LogSiteData( )
            {
            }

            explicit LogSiteData( const LogSite* logSite )
                : level_( logSite->Level() ), formatString_( ToString( logSite->FormatString() ) ), argumentsDescriptor_( ToBytes(logSite->ArgumentsDescriptor() ) ), 
                    isFixedSize_( logSite->IsFixedSize() ), fixedSize_( logSite->FixedSize() ), line_( logSite->Line() ), column_( logSite->Column() ), file_( ToString( logSite->File() ) ), function_( ToString( logSite->Function() ) )
            {
            }

            explicit LogSiteData( const LogSite& logSite )
                : LogSiteData( &logSite )
            { }

            constexpr LogSiteData( Logging::Level level, const char* formatString, const std::vector<Byte>& argumentsDescriptor, bool isFixedSize, size_t fixedSize, UInt32 line, UInt32 column, const char* file, const char* function ) noexcept
                : level_( level ), formatString_( formatString ), argumentsDescriptor_( argumentsDescriptor ), isFixedSize_( isFixedSize ), fixedSize_( fixedSize ), line_( line ), column_( column ), file_( file ), function_( function )
            {
            }

            auto operator<=>( const LogSiteData& ) const = default;


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
                reader.Read( formatString_ );
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
                writer.Write( formatString_ );
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
                hasher.Add( static_cast< UInt16 >( level_ ) );
                hasher.Add( formatString_ );
                hasher.Add( argumentsDescriptor_.data( ), argumentsDescriptor_.size( ) );
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
            constexpr std::string_view FormatString( ) const noexcept
            {
                return formatString_;
            }

            constexpr std::span<const Byte> ArgumentsDescriptor( ) const noexcept
            {
                return std::span<const Byte>(argumentsDescriptor_.data(), argumentsDescriptor_.size() );
            }

            constexpr size_t ArgumentsDescriptorSize( ) const noexcept
            {
                return argumentsDescriptor_.size();
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
            constexpr std::string_view File( ) const noexcept
            {
                return file_;
            }
            constexpr std::string_view Function( ) const noexcept
            {
                return function_;
            }
        };
    }


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
                auto message = std::vformat( site->FormatString(), std::make_format_args( args... ) );
                std::puts( message.c_str() );
            }

            void Flush( FlushType flushType = FlushType::Normal )
            { }

            void Poll( DateTime now, UInt64 referenceRdtscCycle, TimeSpan maxAge )
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

        void Flush( FlushType flushType = FlushType::Normal )
        {
            writer_.Flush( flushType );
        }

        void Poll( DateTime now, UInt64 referenceRdtscCycle, TimeSpan maxAge )
        {
            writer_.Poll( now, referenceRdtscCycle, maxAge );
        }


        constexpr bool IsTraceEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Trace ) && IsSet( enabledLevels_, Level::Trace );
        }
        constexpr bool IsVerboseEnabled( ) const noexcept
        {
            return IsSet( EnabledLevels, Level::Verbose ) && IsSet( enabledLevels_, Level::Verbose );
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
        void Entering( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsTraceEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }
        template<typename ... Args>
        void Leaving( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsTraceEnabled( ) )
            {
                writer_.WriteLogRecord( logSite, std::forward<Args>( args )... );
            }
        }

        template<typename ... Args>
        void Verbose( const LogSite* logSite, Args&& ... args ) noexcept
        {
            if ( IsVerboseEnabled( ) )
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

    using ConsoleLogger = Logger<Writers::ConsoleWriter>;
    



}


#endif

