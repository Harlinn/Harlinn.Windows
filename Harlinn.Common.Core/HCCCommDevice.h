#pragma once
#ifndef HARLINN_COMMON_CORE_HCCSERIALPORT_H_
#define HARLINN_COMMON_CORE_HCCSERIALPORT_H_
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

#include <HCCIOContext.h>
#include <HCCException.h>
#include <HCCString.h>

namespace Harlinn::Common::Core::IO
{
    /// <summary>
    /// The parity scheme.
    /// </summary>
    enum class Parity : Byte
    {
        None = NOPARITY,
        Odd = ODDPARITY,
        Even = EVENPARITY,
        Mark = MARKPARITY,
        Space = SPACEPARITY
    };

    /// <summary>
    /// The number of stop bits
    /// </summary>
    enum class StopBits : Byte
    {
        One = ONESTOPBIT,
        One5 = ONE5STOPBITS,
        Two = TWOSTOPBITS
    };

    /// <summary>
    /// The DTR (data-terminal-ready) flow control.
    /// </summary>
    enum class DtrControl : DWORD
    {
        /// <summary>
        /// Disables the DTR line when the device is opened and leaves it disabled.
        /// </summary>
        Disable = DTR_CONTROL_DISABLE,
        /// <summary>
        /// Enables the DTR line when the device is opened and leaves it on.
        /// </summary>
        Enable = DTR_CONTROL_ENABLE,
        /// <summary>
        /// Enables DTR handshaking. If handshaking is enabled, it is an error for the 
        /// application to adjust the line by using the EscapeCommFunction function.
        /// </summary>
        Handshake = DTR_CONTROL_HANDSHAKE
    };

    /// <summary>
    /// The RTS (request-to-send) flow control.
    /// </summary>
    enum class RtsControl : DWORD
    {
        /// <summary>
        /// Disables the RTS line when the device is opened and leaves it disabled.
        /// </summary>
        Disable = RTS_CONTROL_DISABLE,
        /// <summary>
        /// Enables the RTS line when the device is opened and leaves it on.
        /// </summary>
        Enable = RTS_CONTROL_ENABLE,
        /// <summary>
        /// Enables RTS handshaking. The driver raises the RTS line when the "type-ahead" 
        /// (input) buffer is less than one-half full and lowers the RTS line when the buffer 
        /// is more than three-quarters full. If handshaking is enabled, it is an error for 
        /// the application to adjust the line by using the EscapeCommFunction function.
        /// </summary>
        Handshake = RTS_CONTROL_HANDSHAKE,
        /// <summary>
        /// Specifies that the RTS line will be high if bytes are available for transmission. 
        /// After all buffered bytes have been sent, the RTS line will be low.
        /// </summary>
        Toggle = RTS_CONTROL_TOGGLE
    };

    enum class FlowControl
    {
        None,
        XonXoff,
        CtsRts,
        CtsDtr,
        DsrRts,
        DsrDtr
    };

    enum class PurgeFlags : UInt32
    {
        // Kill the pending/current writes to the comm port.
        TxAbort = PURGE_TXABORT, 
        // Kill the pending/current reads to the comm port.
        RxAbort = PURGE_RXABORT,
        // Kill the transmit queue if there.
        TxClear = PURGE_TXCLEAR,
        // Kill the typeahead buffer if there.
        RxClear = PURGE_RXCLEAR
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( PurgeFlags, UInt32 );

    enum class EscapeFunction : UInt32
    {
        // Simulate XOFF received
        SetXOff = SETXOFF,
        // Simulate XON received
        SetXOn = SETXON,
        // Set RTS high
        SetRTS = SETRTS,
        // Set RTS low
        ClearRTS = CLRRTS,
        // Set DTR high
        SetDTR = SETDTR,
        // Set DTR low
        ClearDTR = CLRDTR,
        // Reset device if possible
        Reset = RESETDEV,
        // Set the device break line.
        SetBreak = SETBREAK,
        // Clear the device break line.
        ClearBreak = CLRBREAK
    };


    class CommDeviceStream;

    class DeviceControlBlock
    {
    private:
        friend class CommDeviceStream;
        DCB data_ = 
        {
            .BaudRate = sizeof( DCB ),
            .fBinary = 1,
        };
    public:
        DeviceControlBlock( ) = default;

        inline DeviceControlBlock( const CommDeviceStream& CommDeviceStream );

        [[nodiscard]] DCB* data( ) noexcept
        {
            return &data_;
        }

        [[nodiscard]] const DCB* data( ) const noexcept
        {
            return &data_;
        }

        /// <summary>
        /// Returns the baud rate at which the communications device operates. 
        /// </summary>
        /// <returns>The baud rate at which the communications device operates.</returns>
        [[nodiscard]] UInt32 BaudRate( ) const noexcept
        {
            return data_.BaudRate;
        }
        void SetBaudRate( UInt32 baudRate ) noexcept
        {
            data_.BaudRate = baudRate;
        }

        /// <summary>
        /// Windows does not support nonbinary mode transfers, so this function must return true.
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] bool Binary( ) const noexcept
        {
            return data_.fBinary == 1;
        }

        /// <summary>
        /// If this member is TRUE, parity checking is performed and errors are reported.
        /// </summary>
        [[nodiscard]] bool ParityEnabled( ) const noexcept
        {
            return data_.fParity == 1;
        }
        void SetParityEnabled( bool value = true ) noexcept
        {
            data_.fParity = value ? 1 : 0;
        }

        /// <summary>
        /// CTS handshaking on output
        /// </summary>
        [[nodiscard]] bool CtsFlowControlEnabled( ) const noexcept
        {
            return data_.fOutxCtsFlow == 1;
        }

        /// <summary>
        /// DSR handshaking on output
        /// </summary>
        [[nodiscard]] bool DsrFlowControlEnabled( ) const noexcept
        {
            return data_.fOutxDsrFlow == 1;
        }

        /// <summary>
        /// DTR Flow control
        /// </summary>
        [[nodiscard]] IO::DtrControl DtrControl( ) const noexcept
        {
            return static_cast< IO::DtrControl >( data_.fDtrControl );
        }

        /// <summary>
        /// If true the communications driver is sensitive to the state of the DSR signal. 
        /// The driver ignores any bytes received, unless the DSR modem input line is high.
        /// </summary>
        [[nodiscard]] bool DsrSensitivity( ) const noexcept
        {
            return data_.fDsrSensitivity == 1;
        }

        /// <summary>
        /// If true, transmission continues after the input buffer has come within XoffLim 
        /// bytes of being full and the driver has transmitted the XoffChar character to stop 
        /// receiving bytes. If this member is FALSE, transmission does not continue until the 
        /// input buffer is within XonLim bytes of being empty and the driver has transmitted 
        /// the XonChar character to resume reception.
        /// </summary>
        [[nodiscard]] bool TXContinueOnXoff( ) const noexcept
        {
            return data_.fTXContinueOnXoff == 1;
        }

        [[nodiscard]] bool OutputXonXoffEnabled( ) const noexcept
        {
            return data_.fOutX == 1;
        }

        [[nodiscard]] bool InputXonXoffEnabled( ) const noexcept
        {
            return data_.fInX == 1;
        }

        [[nodiscard]] bool ErrorCharEnabled( ) const noexcept
        {
            return data_.fErrorChar == 1;
        }

        [[nodiscard]] bool NullStrippingEnabled( ) const noexcept
        {
            return data_.fNull == 1;
        }


        [[nodiscard]] IO::RtsControl RtsControl( ) const noexcept
        {
            return static_cast< IO::RtsControl >( data_.fRtsControl );
        }

        [[nodiscard]] bool AbortOnError( ) const noexcept
        {
            return data_.fAbortOnError == 1;
        }

        [[nodiscard]] UInt16 XonLim( ) const noexcept
        {
            return data_.XonLim;
        }

        [[nodiscard]] UInt16 XoffLim( ) const noexcept
        {
            return data_.XoffLim;
        }

        [[nodiscard]] Byte ByteSize( ) const noexcept
        {
            return data_.ByteSize;
        }

        [[nodiscard]] IO::Parity Parity( ) const noexcept
        {
            return static_cast< IO::Parity >( data_.Parity );
        }

        [[nodiscard]] IO::StopBits StopBits( ) const noexcept
        {
            return static_cast< IO::StopBits >( data_.StopBits );
        }

        [[nodiscard]] char XonChar( ) const noexcept
        {
            return data_.XonChar;
        }

        [[nodiscard]] char XoffChar( ) const noexcept
        {
            return data_.XoffChar;
        }

        [[nodiscard]] char ErrorChar( ) const noexcept
        {
            return data_.ErrorChar;
        }

        [[nodiscard]] char EofChar( ) const noexcept
        {
            return data_.EofChar;
        }

        [[nodiscard]] char EvtChar( ) const noexcept
        {
            return data_.EvtChar;
        }
    };


    class CommConfig
    {
        std::vector<Byte> data_;
    public:
        CommConfig()
            : data_( sizeof(COMMCONFIG) )
        {
            reinterpret_cast<COMMCONFIG*>( data_.data( ) )->dwSize = sizeof( COMMCONFIG );
        }

        COMMCONFIG* data( )
        {
            return reinterpret_cast<COMMCONFIG*>( data_.data( ) );
        }
        const COMMCONFIG* data( ) const
        {
            return reinterpret_cast<const COMMCONFIG*>( data_.data( ) );
        }

        IO::DeviceControlBlock& DeviceControlBlock( )
        {
            return reinterpret_cast< IO::DeviceControlBlock& >( data( )->dcb );
        }
        const IO::DeviceControlBlock& DeviceControlBlock( ) const
        {
            return reinterpret_cast< const IO::DeviceControlBlock& >( data( )->dcb );
        }


        void resize( size_t newSize )
        {
            if ( newSize != data_.size( ) )
            {
                data_.resize( newSize );
            }
        }

        size_t size( ) const
        {
            return data_.size( );
        }


    };

    
    class SerialPort
    {
        UInt32 portNumber_ = 0;
    public:
        SerialPort( ) = default;
        SerialPort( UInt32 portNumber )
            : portNumber_( portNumber )
        { }

        static constexpr UInt32 DefaultAccess = GENERIC_READ | GENERIC_WRITE;
        static constexpr DWORD DefaultBaudRate = CBR_57600;

        HCC_EXPORT WideString Name( ) const;

        inline CommDeviceStream Open( bool overlapped, DWORD desiredAccess ) const;
        inline CommDeviceStream Open( bool overlapped ) const;
        inline CommDeviceStream Open( UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false ) const;

        CommConfig DefaultConfig( ) const
        {
            auto name = Name( );
            CommConfig result;
            DWORD dwSize = static_cast<DWORD>( result.size( ) );
            auto rc = GetDefaultCommConfigW( name.c_str( ), result.data( ), &dwSize );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error != ERROR_MORE_DATA )
                {
                    ThrowOSError( error );
                }
                result.resize( dwSize );
                rc = GetDefaultCommConfigW( name.c_str( ), result.data( ), &dwSize );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
            return result;
        }

    };

    class SerialPorts : public std::vector<SerialPort>
    {
    public:
        HCC_EXPORT SerialPorts( );
    };


    class CommDeviceStream : public SystemStream<CommDeviceStream>
    {
    public:
        using Base = SystemStream<CommDeviceStream>;
        static constexpr UInt32 DefaultAccess = SerialPort::DefaultAccess;
        static constexpr DWORD DefaultBaudRate = SerialPort::DefaultBaudRate;
    private:
        HCC_EXPORT static HANDLE Create( ULONG portNumber, bool overlapped, DWORD desiredAccess = DefaultAccess );
        HCC_EXPORT static HANDLE Create( const wchar_t* name, bool overlapped = false );
        HCC_EXPORT static HANDLE Create( const char* name, bool overlapped = false );
        HCC_EXPORT static HANDLE Create( const wchar_t* name, UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false );
        HCC_EXPORT static HANDLE Create( const char* name, UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false );
    public:
        enum class ErrorFlags : UInt32
        {
            None = 0,
            // Receive Queue overflow
            ReceiveQueueOverflow = CE_RXOVER,
            // Receive Overrun Error
            ReceiveOverrun = CE_OVERRUN,
            // Receive Parity Error
            ReceiveParity = CE_RXPARITY,
            // Receive Framing error
            ReceiveFraming = CE_FRAME,
            // Break Detected
            BreakDetected = CE_BREAK,
            // TX Queue is full
            TxQueueFull = CE_TXFULL,
            // LPTx Timeout
            LPTTimeout = CE_PTO,
            // LPTx I/O Error
            LPTIOError = CE_IOE,
            // LPTx Device not selected
            LPTDeviceNotSelected = CE_DNS,
            // LPTx Out-Of-Paper
            LPTOutOfPaper = CE_OOP,
            // Requested mode unsupported
            RequestedModeNotSupported = CE_MODE
        };

        enum class EventFlags : UInt32
        {
            None = 0,
            // Any Character received
            RxChar = EV_RXCHAR,
            // Received certain character
            RxFlag = EV_RXFLAG,
            // Transmit Queue Empty
            TxEmpty = EV_TXEMPTY,
            // CTS changed state
            CTS = EV_CTS,
            // DSR changed state
            DSR = EV_DSR,
            // RLSD changed state
            RLSD = EV_RLSD,
            // BREAK received
            Break = EV_BREAK,
            // Line status error occurred
            LineError = EV_ERR,
            // Ring signal detected
            Ring = EV_RING,
            // Printer error occurred
            PrinterError = EV_PERR,
            // Receive buffer is 80 percent full
            Rx80Full = EV_RX80FULL,
            // Provider specific event 1
            ProviderEvent1 = EV_EVENT1,
            // Provider specific event 2
            ProviderEvent2 = EV_EVENT2
        };

        enum class ModemStatusFlags : UInt32
        {
            // The CTS (clear-to-send) signal is on.
            CtsOn = MS_CTS_ON,
            // The DSR (data-set-ready) signal is on.
            DsrOn = MS_DSR_ON,
            // The ring indicator signal is on.
            RingOn = MS_RING_ON,
            // The RLSD (receive-line-signal-detect) signal is on.
            RlsdOn = MS_RLSD_ON,
        };



        CommDeviceStream( )
            : Base( )
        { }

        CommDeviceStream( HANDLE handle )
            : Base( handle )
        { }

        CommDeviceStream( ULONG portNumber, bool overlapped, DWORD desiredAccess )
            : Base( Create( portNumber, overlapped, desiredAccess ) )
        { }
        explicit CommDeviceStream( const wchar_t* name, bool overlapped )
            : Base( Create( name, overlapped ) )
        { }
        explicit CommDeviceStream( const WideString& name, bool overlapped )
            : Base( Create( name.c_str(), overlapped ) )
        { }
        explicit CommDeviceStream( const char* name, bool overlapped )
            : Base( Create( name, overlapped ) )
        { }
        explicit CommDeviceStream( const AnsiString& name, bool overlapped )
            : Base( Create( name.c_str(), overlapped ) )
        { }

        explicit CommDeviceStream( const wchar_t* name, UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false )
            : Base( Create( name, baudRate, parity, dataBits, stopBits, flowControl, overlapped ) )
        { }
        explicit CommDeviceStream( const WideString& name, UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false )
            : Base( Create( name.c_str(), baudRate, parity, dataBits, stopBits, flowControl, overlapped ) )
        { }
        explicit CommDeviceStream( const char* name, UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false )
            : Base( Create( name, baudRate, parity, dataBits, stopBits, flowControl, overlapped ) )
        { }
        explicit CommDeviceStream( const AnsiString& name, UInt32 baudRate = DefaultBaudRate, Parity parity = Parity::None, Byte dataBits = 8, StopBits stopBits = StopBits::One, FlowControl flowControl = FlowControl::None, bool overlapped = false )
            : Base( Create( name.c_str(), baudRate, parity, dataBits, stopBits, flowControl, overlapped ) )
        { }

        CommDeviceStream( const CommDeviceStream& ) = delete;
        CommDeviceStream& operator = ( const CommDeviceStream& ) = delete;

        /// <summary>
        /// Initializes the communications parameters for a specified communications device.
        /// </summary>
        /// <param name="inQueueSize">The recommended size of the device's internal input buffer, in bytes.</param>
        /// <param name="outQueueSize">The recommended size of the device's internal output buffer, in bytes.</param>
        void Setup( UInt32 inQueueSize, UInt32 outQueueSize ) const
        {
            auto rc = SetupComm( Handle( ), inQueueSize, outQueueSize );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Transmits a specified character ahead of any pending data in the output buffer of the specified communications device.
        /// </summary>
        void Transmit( Byte value ) const
        {
            auto rc = TransmitCommChar( Handle( ), std::bit_cast<char>( value ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


        /// <summary>
        /// Retrieves the current configuration of a communications device.
        /// </summary>
        /// <returns></returns>
        CommConfig GetConfig( ) const
        {
            CommConfig result;
            DWORD dwSize = static_cast<DWORD>( result.size( ) );
            auto rc = GetCommConfig( Handle( ), result.data( ), &dwSize );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error != ERROR_MORE_DATA )
                {
                    ThrowOSError( error );
                }
                result.resize( dwSize );
                rc = GetCommConfig( Handle( ), result.data( ), &dwSize );
                if ( !rc )
                {
                    ThrowLastOSError( );
                }
            }
            return result;
        }

        /// <summary>
        /// Sets the current configuration of a communications device.
        /// </summary>
        /// <param name="commConfig">A pointer to a COMMCONFIG structure.</param>
        /// <param name="sizeOfData">The size of the structure pointed to by commConfig, in bytes.</param>
        void SetConfig( const COMMCONFIG* commConfig, DWORD sizeOfData ) const
        {
            auto rc = SetCommConfig(Handle(), const_cast<LPCOMMCONFIG>(commConfig), sizeOfData );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


        /// <summary>
        /// Waits for an event to occur for a specified communications device. The set of events 
        /// that are monitored by this function is contained in the event mask associated with the 
        /// device handle.
        /// </summary>
        /// <param name="eventMask">A pointer to a variable that receives a mask indicating the type of event that occurred</param>
        /// <param name="overlapped">A pointer to an OVERLAPPED structure. This is required if the device was opened in overlapped mode.</param>
        /// <returns>Returns true if the wait completed successfully, or false if the operation will complete asynchronously.</returns>
        bool WaitEvent( EventFlags* eventMask, OVERLAPPED* overlapped = nullptr ) const
        {
            auto rc = WaitCommEvent( Handle( ), (LPDWORD)eventMask, overlapped );
            if ( !rc )
            {
                auto error = GetLastError( );
                if ( error != ERROR_IO_PENDING )
                {
                    ThrowOSError( error );
                }
                return false;
            }
            return true;
        }




        /// <summary>
        /// Discards all characters from the output or input buffer of a specified communications 
        /// resource. It can also terminate pending read or write operations on the resource.
        /// </summary>
        /// <param name="flags"></param>
        /// <remarks>
        /// If a thread uses Purge to flush an output buffer, the deleted characters are not transmitted. 
        /// To empty the output buffer while ensuring that the contents are transmitted, call the Flush 
        /// member function (a synchronous operation). Note, however, that Flush is subject to flow control 
        /// but not to write time-outs, and it will not return until all pending write operations have been 
        /// transmitted.
        /// </remarks>
        void Purge( PurgeFlags flags ) const
        {
            auto rc = PurgeComm(Handle(), static_cast<DWORD>( flags ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Directs the specified communications device to perform an extended function.
        /// </summary>
        /// <param name="escapeFunction">The identifier of the function to be performed</param>
        void Escape( EscapeFunction escapeFunction ) const
        {
            auto rc = EscapeCommFunction( Handle( ), static_cast<DWORD>( escapeFunction ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Restores character transmission for a specified communications device and places the 
        /// transmission line in a non-break state.
        /// </summary>
        /// <remarks>
        /// A communications device is placed in a break state by the SetBreak or Escape function. 
        /// Character transmission is then suspended until the break state is cleared by calling ClearBreak.
        /// </remarks>
        void ClearBreak( ) const
        {
            auto rc = ClearCommBreak( Handle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Suspends character transmission for a specified communications device and places the 
        /// transmission line in a break state until the ClearBreak function is called.
        /// </summary>
        void SetBreak( ) const
        {
            auto rc = SetCommBreak( Handle( ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Retrieves information about a communications error and reports the current status of a 
        /// communications device. The function is called when a communications error occurs, and 
        /// it clears the device's error flag to enable additional input and output (I/O) operations.
        /// </summary>
        /// <param name="comStatus">
        /// A pointer to a COMSTAT structure in which the device's status information is returned. 
        /// If this parameter is nullptr, no status information is returned.
        /// </param>
        /// <returns>
        /// A mask indicating the type of error.
        /// </returns>
        ErrorFlags ClearError( COMSTAT* comStatus = nullptr ) const
        {
            DWORD errorFlags = 0;
            auto rc = ClearCommError( Handle( ), &errorFlags, comStatus );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<ErrorFlags>( errorFlags );
        }

        /// <summary>
        /// Retrieves the value of the event mask for a specified communications device.
        /// </summary>
        /// <returns>The event mask</returns>
        EventFlags Mask( ) const
        {
            DWORD mask = 0;
            auto rc = GetCommMask( Handle( ), &mask );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<EventFlags>( mask );
        }

        void SetMask( EventFlags eventFlags ) const
        {
            auto rc = SetCommMask( Handle( ), static_cast<DWORD>( eventFlags ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Retrieves the modem control-register values.
        /// </summary>
        /// <returns>A mask holding the value of the modem control-register</returns>
        ModemStatusFlags ModemStatus( ) const
        {
            DWORD mask = 0;
            auto rc = GetCommModemStatus( Handle( ), &mask );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return static_cast<ModemStatusFlags>( mask );
        }

        /// <summary>
        /// Retrieves information about the communications properties for a specified communications device.
        /// </summary>
        void GetProperties( COMMPROP& properties ) const
        {
            auto rc = GetCommProperties( Handle( ), &properties );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Retrieves information about the communications properties for a specified communications device.
        /// </summary>
        COMMPROP Properties( ) const
        {
            COMMPROP result{};
            GetProperties( result );
            return result;
        }
        
        /// <summary>
        /// Retrieves the current control settings for a specified communications device.
        /// </summary>
        void GetState( DCB& dcb ) const
        {
            auto rc = GetCommState( Handle( ), &dcb );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Retrieves the current control settings for a specified communications device.
        /// </summary>
        void GetState( DeviceControlBlock& dcb ) const
        {
            GetState( dcb.data_ );
        }


        /// <summary>
        /// Retrieves the current control settings for a specified communications device.
        /// </summary>
        DeviceControlBlock State( ) const
        {
            return DeviceControlBlock( *this );
        }

        /// <summary>
        /// Configures a communications device according to the specifications in a device-control 
        /// block (a DCB structure). The function reinitializes all hardware and control settings, 
        /// but it does not empty output or input queues.
        /// </summary>
        void SetState( const DCB& dcb ) const
        {
            auto rc = SetCommState(Handle(), const_cast<LPDCB>( &dcb ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Configures a communications device according to the specifications in a device-control 
        /// block (a DCB structure). The function reinitializes all hardware and control settings, 
        /// but it does not empty output or input queues.
        /// </summary>
        void SetState( DeviceControlBlock& dcb ) const
        {
            SetState( dcb.data_ );
        }


        /// <summary>
        /// Retrieves the time-out parameters for all read and write operations on a specified communications device.
        /// </summary>
        COMMTIMEOUTS Timeouts( ) const
        {
            COMMTIMEOUTS result{};
            auto rc = GetCommTimeouts( Handle( ), &result );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        /// <summary>
        /// Retrieves the time-out parameters for all read and write operations on a specified communications device.
        /// </summary>
        void GetTimeouts( COMMTIMEOUTS& commTimeouts ) const
        {
            auto rc = GetCommTimeouts( Handle( ), &commTimeouts );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Sets the time-out parameters for all read and write operations on a specified communications device.
        /// </summary>
        void SetTimeouts( const COMMTIMEOUTS& commTimeouts ) const
        {
            auto rc = SetCommTimeouts( Handle( ), const_cast<LPCOMMTIMEOUTS>( &commTimeouts ) );
            if ( !rc )
            {
                ThrowLastOSError( );
            }
        }


    };

    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommDeviceStream::ErrorFlags, UInt32 );
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommDeviceStream::EventFlags, UInt32 );
    HCC_DEFINE_ENUM_FLAG_OPERATORS( CommDeviceStream::ModemStatusFlags, UInt32 );

    static_assert( StreamReader<CommDeviceStream> );
    static_assert( StreamWriter<CommDeviceStream> );
    static_assert( StreamSeek<CommDeviceStream> );
    static_assert( StreamPosition<CommDeviceStream> );
    static_assert( StreamSize<CommDeviceStream> );
    static_assert( StreamFlush<CommDeviceStream> );
    static_assert( StreamFeatureTests<CommDeviceStream> );
    static_assert( Stream<CommDeviceStream> );


    inline DeviceControlBlock::DeviceControlBlock( const CommDeviceStream& commDeviceStream )
    {
        auto rc = GetCommState( commDeviceStream.Handle( ), &data_ );
        if ( !rc )
        {
            ThrowLastOSError( );
        }
    }

    inline CommDeviceStream SerialPort::Open( bool overlapped, DWORD desiredAccess ) const
    {
        return { portNumber_, overlapped, desiredAccess };
    }
    inline CommDeviceStream SerialPort::Open( bool overlapped ) const
    {
        auto name = Name( );
        return CommDeviceStream( name, overlapped );
    }
    inline CommDeviceStream SerialPort::Open( UInt32 baudRate, Parity parity, Byte dataBits, StopBits stopBits, FlowControl flowControl, bool overlapped ) const
    {
        auto name = Name( );
        return CommDeviceStream( name, baudRate, parity, dataBits, stopBits, flowControl, overlapped );
    }

    enum class CommDeviceRequestType
    {
        Unknown,
        Read,
        Write,
        ReadScatter,
        WriteGather,
        WaitEvent
    };


    class CommDeviceRequest : public IO::Request
    {
    public:
        using Base = IO::Request;
    private:
        CommDeviceRequestType type_;
    protected:
        CommDeviceRequest( HANDLE handle, CommDeviceRequestType type )
            : Base( handle ), type_( type )
        {
        }

        constexpr CommDeviceRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, CommDeviceRequestType type ) noexcept
            : Base( handle, manualResetEvent, ownsEvent ), type_( type )
        {
        }
    public:
        constexpr CommDeviceRequestType Type( ) const noexcept
        {
            return type_;
        }
    };




    class ReadCommDeviceRequest : public CommDeviceRequest
    {
    public:
        using Base = CommDeviceRequest;
        static constexpr CommDeviceRequestType RequestType = CommDeviceRequestType::Read;
    private:
        Byte* buffer_;
        UInt32 numberOfBytesToRead_;
    public:
        ReadCommDeviceRequest( HANDLE handle, Byte* buffer, UInt32 numberOfBytesToRead )
            : Base( handle, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        constexpr ReadCommDeviceRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToRead ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        ReadCommDeviceRequest( const CommDeviceStream& commDeviceStream, Byte* buffer, UInt32 numberOfBytesToRead )
            : Base( commDeviceStream.Handle( ), RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        constexpr ReadCommDeviceRequest( const CommDeviceStream& commDeviceStream, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToRead ) noexcept
            : Base( commDeviceStream.Handle( ), manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToRead_( numberOfBytesToRead )
        {
        }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        constexpr UInt32 NumberOfBytesToRead( ) const noexcept
        {
            return numberOfBytesToRead_;
        }

    };

    class WriteCommDeviceRequest : public CommDeviceRequest
    {
    public:
        using Base = CommDeviceRequest;
        static constexpr CommDeviceRequestType RequestType = CommDeviceRequestType::Write;
    private:
        Byte* buffer_;
        UInt32 numberOfBytesToWrite_;
    public:
        WriteCommDeviceRequest( HANDLE handle, Byte* buffer, UInt32 numberOfBytesToWrite )
            : Base( handle, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        constexpr WriteCommDeviceRequest( HANDLE handle, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToWrite ) noexcept
            : Base( handle, manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        WriteCommDeviceRequest( const CommDeviceStream& commDeviceStream, Byte* buffer, UInt32 numberOfBytesToWrite )
            : Base( commDeviceStream.Handle( ), RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        constexpr WriteCommDeviceRequest( const CommDeviceStream& commDeviceStream, HANDLE manualResetEvent, bool ownsEvent, Byte* buffer, UInt32 numberOfBytesToWrite ) noexcept
            : Base( commDeviceStream.Handle( ), manualResetEvent, ownsEvent, RequestType ), buffer_( buffer ), numberOfBytesToWrite_( numberOfBytesToWrite )
        {
        }

        constexpr Byte* Buffer( ) const noexcept
        {
            return buffer_;
        }
        constexpr UInt32 NumberOfBytesToWrite( ) const noexcept
        {
            return numberOfBytesToWrite_;
        }
    };

    class WaitEventCommDeviceRequest : public CommDeviceRequest
    {
    public:
        using Base = CommDeviceRequest;
        using EventFlags = CommDeviceStream::EventFlags;
        static constexpr CommDeviceRequestType RequestType = CommDeviceRequestType::WaitEvent;
    private:
        EventFlags* eventMask_;
    public:
        WaitEventCommDeviceRequest( HANDLE handle, EventFlags* eventMask )
            : Base( handle, RequestType ), eventMask_( eventMask )
        {
        }

        WaitEventCommDeviceRequest( CommDeviceStream& commDeviceStream, EventFlags* eventMask )
            : Base( commDeviceStream.Handle( ), RequestType ), eventMask_( eventMask )
        {
        }
        
        constexpr EventFlags* EventMask( ) const noexcept
        {
            return eventMask_;
        }
    };

    template<typename DerivedT>
    class CommDeviceHandler : public ContextHandler
    {
    public:
        using Base = ContextHandler;
        using DerivedType = DerivedT;
    private:
        CommDeviceStream& commDeviceStream_;
    public:
        CommDeviceHandler( const std::shared_ptr<IO::Context>& context, CommDeviceStream& commDeviceStream )
            : Base( context ), commDeviceStream_( commDeviceStream )
        {
            context->Bind( commDeviceStream.Handle( ), this );
        }
    public:
        constexpr const CommDeviceStream& Stream( ) const noexcept
        {
            return commDeviceStream_;
        }

        bool BeginAsyncRead( ReadCommDeviceRequest* request )
        {
            BindRequestToContext( request );
            auto handle = request->Handle( );
            auto rc = ReadFile( handle, request->Buffer( ), request->NumberOfBytesToRead( ), nullptr, request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    ThrowOSError( errorCode );
                }
            }
            return false;
        }

        bool BeginAsyncWrite( WriteCommDeviceRequest* request )
        {
            BindRequestToContext( request );
            auto handle = request->Handle( );
            auto rc = WriteFile( handle, request->Buffer( ), request->NumberOfBytesToWrite( ), nullptr, request );
            if ( !rc )
            {
                auto errorCode = GetLastError( );
                if ( errorCode != ERROR_IO_PENDING )
                {
                    ThrowOSError( errorCode );
                }
            }
            return false;
        }

        bool BeginAsyncWait( WaitEventCommDeviceRequest* request )
        {
            BindRequestToContext( request );
            auto result = commDeviceStream_.WaitEvent( request->EventMask( ), request );
            if ( result )
            {
                DerivedType& self = static_cast<DerivedType&>( *this );
                result = self.HandleWaitEventCompleted( static_cast<WaitEventCommDeviceRequest*>( request ) );
            }
            return result;
        }



        virtual bool Process( Message& message ) override
        {
            bool result = false;
            auto request = static_cast<CommDeviceRequest*>( message.Request( ) );
            CommDeviceRequestType requestType = request->Type( );
            DerivedType& self = static_cast<DerivedType&>( *this );
            switch ( requestType )
            {
                case CommDeviceRequestType::Read:
                {
                    result = self.HandleReadCompleted( static_cast<ReadCommDeviceRequest*>( request ) );
                }
                break;
                case CommDeviceRequestType::Write:
                {
                    result = self.HandleWriteCompleted( static_cast<WriteCommDeviceRequest*>( request ) );
                }
                break;
                case CommDeviceRequestType::WaitEvent:
                {
                    result = self.HandleWaitEventCompleted( static_cast<WaitEventCommDeviceRequest*>( request ) );
                }
                break;
            }
            return result;
        }
    protected:
        constexpr bool HandleReadCompleted( ReadCommDeviceRequest* request ) noexcept
        {
            return false;
        }

        constexpr bool HandleWriteCompleted( WriteCommDeviceRequest* request ) noexcept
        {
            return false;
        }

        constexpr bool HandleWaitEventCompleted( WaitEventCommDeviceRequest* request ) noexcept
        {
            return false;
        }

    };


    class CommDeviceDispatcher : public CommDeviceHandler<CommDeviceDispatcher>
    {
        template<typename DerivedT>
        friend class CommDeviceHandler;
    public:
        using Base = CommDeviceHandler<CommDeviceDispatcher>;
        boost::signals2::signal<void( const CommDeviceDispatcher& dispatcher, ReadCommDeviceRequest* request )> OnReadCompleted;
        boost::signals2::signal<void( const CommDeviceDispatcher& dispatcher, WriteCommDeviceRequest* request )> OnWriteCompleted;
        boost::signals2::signal<void( const CommDeviceDispatcher& dispatcher, WaitEventCommDeviceRequest* request )> OnWaitEventCompleted;

        CommDeviceDispatcher( const std::shared_ptr<IO::Context>& context, CommDeviceStream& commDeviceStream )
            : Base( context, commDeviceStream )
        {
        }

    private:
        bool HandleReadCompleted( ReadCommDeviceRequest* request )
        {
            OnReadCompleted( *this, request );
            return true;
        }

        bool HandleWriteCompleted( WriteCommDeviceRequest* request )
        {
            OnWriteCompleted( *this, request );
            return true;
        }

        bool HandleWaitEventCompleted( WaitEventCommDeviceRequest* request )
        {
            OnWaitEventCompleted( *this, request );
            return true;
        }

    };


}



#endif
