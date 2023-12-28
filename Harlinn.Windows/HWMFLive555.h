#pragma once
#ifndef HARLINN_WINDOWS_HWMFLIVE555_H_
#define HARLINN_WINDOWS_HWMFLIVE555_H_

#include <liveMedia.hh>
#include <BasicUsageEnvironment.hh>
#include <GroupsockHelper.hh>

#include <HWMediaFoundation.h>
#include <HWMFReadWrite.h>
#include <HWStrmif.h>

namespace Harlinn::Windows::LiveMedia
{
	class MediaFoundationH264LiveSource : public FramedSource
	{
	public:
		using Base = FramedSource;
		static constexpr size_t BufferSize = 300'000;
	private:
		
		// Note that this if the video device does not support this frame rate the video source reader will fail to initialise.
		static const int TARGET_FRAME_RATE = 30; // 5; 15; 30
		
		// Adjusting this affects the quality of the H264 bit stream.
		static const int TARGET_AVERAGE_BIT_RATE = 5000000; 
		
		// Set to 0 to use default system webcam.
		static const int WEBCAM_DEVICE_INDEX = 0;

		bool _isInitialised = false;
		EventTriggerId eventTriggerId = 0;
		int _frameCount = 0;
		long int _lastSendAt;

		MFMediaSource videoSource_;
		MFSourceReader videoSourceReader_;

		// The H264 Encoder MFT
		MFTransform encoderTransform_; 
		
		MFT_OUTPUT_DATA_BUFFER outputDataBuffer_;
		
		MFMediaType videoSourceReaderMediaType_;
		MFMediaType encoderTransformInputMediaType_; 
		MFMediaType encoderTransformOutputMediaType_;
		DWORD mftStatus = 0;

	public:
		static MediaFoundationH264LiveSource* createNew( UsageEnvironment& env )
		{
			return new MediaFoundationH264LiveSource( env );
		}

		MediaFoundationH264LiveSource( UsageEnvironment& env ) :
			Base( env )
		{
			_lastSendAt = GetTickCount( );
			eventTriggerId = envir( ).taskScheduler( ).createEventTrigger( deliverFrame0 );
		}

		~MediaFoundationH264LiveSource( )
		{
		}

		bool isH264VideoStreamFramer( ) const override
		{
			return true;
		}

		static void deliverFrame0( void* clientData )
		{
			( ( MediaFoundationH264LiveSource* )clientData )->doGetNextFrame( );
		}

		bool initialise( )
		{
			// Get the first available webcam.
			MFAttributes videoSourceConfig = MFAttributes::Create( 1 );

			// Request video capture devices.
			videoSourceConfig.SetGUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID );

			auto deviceSources = MF::DeviceSources::CreateVideoDeviceSources( );
			auto deviceSource = deviceSources[ WEBCAM_DEVICE_INDEX ];
			auto webcamFriendlyName = deviceSource.GetString( MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME );

			wprintf( L"First available webcam: %s\n", webcamFriendlyName.c_str() );
			
			videoSource_ = deviceSource.ActivateObject<MFMediaSource>( );

			//auto videoSourceKnownInterfaces = Com::GetSupportedKnownInterfaces( videoSource_.GetInterfacePointer( ) );

			videoSourceReader_ = MFSourceReader::CreateSourceReaderFromMediaSource( videoSource_, videoSourceConfig );

			//auto videoSourceReaderKnownInterfaces = Com::GetSupportedKnownInterfaces( videoSourceReader_.GetInterfacePointer( ) );

			//MF::PrintMediaTypeDescriptions( 0, videoSourceReader_ );


			videoSourceReaderMediaType_ = videoSourceReader_.GetCurrentMediaType( 0 );

			MF::PrintMediaTypeDescription( videoSourceReaderMediaType_ );
			 
			encoderTransform_ = Unknown::CoCreateInstanceFromClassId<MFTransform>( CLSID_CMSH264EncoderMFT );

			//auto encoderTransformKnownInterfaces = Com::GetSupportedKnownInterfaces( videoSource_.GetInterfacePointer( ) );
			Com::PrintSupportedKnownInterfaces( videoSource_.GetInterfacePointer( ) );

			puts( "Transform output type descritions;" );
			MF::PrintOutputMediaTypeDescriptions( 0, encoderTransform_ );

			//auto codecAPI = encoderTransform_.As<DirectShow::CodecAPI>( );
			//codecAPI.SetValue( CODECAPI_AVLowLatencyMode, true );
			

			encoderTransformOutputMediaType_ = MFMediaType::Create( MFMediaType_Video, MFVideoFormat_H264 );
			//encoderTransformOutputMediaType_.SetAverageBitRate( videoSourceReaderMediaType_.GetAverageBitRate() );
			encoderTransformOutputMediaType_.SetAverageBitRate( 4423680000 );
			encoderTransformOutputMediaType_.SetFrameSize( videoSourceReaderMediaType_.GetFrameSize() );
			encoderTransformOutputMediaType_.SetFrameRate( TARGET_FRAME_RATE );
			encoderTransformOutputMediaType_.SetPixelAspectRatio( 1, 1 );
			encoderTransformOutputMediaType_.SetInterlaceMode( MFVideoInterlaceMode::MFVideoInterlace_Progressive );
			encoderTransformOutputMediaType_.SetAllSamplesIndependent( );

			encoderTransform_.SetOutputType(0, encoderTransformOutputMediaType_ );

			puts( "Transform Input type descritions;" );
			MF::PrintInputMediaTypeDescriptions( 0, encoderTransform_ );

			
			encoderTransformInputMediaType_ = videoSourceReaderMediaType_.Clone( );
			
			encoderTransform_.SetInputType( 0, encoderTransformInputMediaType_ );


			mftStatus = encoderTransform_.GetInputStatus( 0 );

			if ( MFT_INPUT_STATUS_ACCEPT_DATA != mftStatus )
			{
				printf( "E: ApplyTransform() pTransform->GetInputStatus() not accept data.\n" );
				printf( "MediaFoundationH264LiveSource initialisation failed.\n" );
				return false;
			}
			encoderTransform_.ProcessMessage( MFT_MESSAGE_NOTIFY_BEGIN_STREAMING );
			encoderTransform_.ProcessMessage( MFT_MESSAGE_NOTIFY_START_OF_STREAM );

			auto hr = MFTRegisterLocalByCLSID(__uuidof( CColorConvertDMO ), MFT_CATEGORY_VIDEO_PROCESSOR, L"", MFT_ENUM_FLAG_SYNCMFT, 0, nullptr, 0, nullptr );
			HCC_COM_CHECK_HRESULT( hr );
			
			memset( &outputDataBuffer_, 0, sizeof outputDataBuffer_ );

			return true;

		}

		virtual void doGetNextFrame( )
		{
			if ( !_isInitialised )
			{
				_isInitialised = true;
				if ( !initialise( ) )
				{
					printf( "Video device initialisation failed, stopping." );
					return;
				}
			}

			if ( !isCurrentlyAwaitingData( ) ) return;

			DWORD processOutputStatus = 0;
			DWORD streamIndex, flags;
			LONGLONG llVideoTimeStamp, llSampleDuration;
			bool frameSent = false;

			auto videoSample = videoSourceReader_.ReadSample( MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, &streamIndex, &flags, &llVideoTimeStamp );


			if ( videoSample )
			{
				_frameCount++;
				videoSample.SetSampleTime( llVideoTimeStamp );
				videoSample.GetSampleDuration( &llSampleDuration );

				// Pass the video sample to the H.264 transform.
				encoderTransform_.ProcessInput( 0, videoSample, 0 );

				auto mftOutFlags = encoderTransform_.GetOutputStatus( );

				if ( mftOutFlags == MFT_OUTPUT_STATUS_SAMPLE_READY )
				{
					//printf( "Sample ready.\n" );

					auto StreamInfo = encoderTransform_.GetOutputStreamInfo( 0 );

					auto mftOutSample = MFSample::Create( );

					auto pBuffer = MFMediaBuffer::CreateMemoryBuffer( StreamInfo.cbSize );
					mftOutSample.AddBuffer( pBuffer );

					while ( true )
					{
						outputDataBuffer_.dwStreamID = 0;
						outputDataBuffer_.dwStatus = 0;
						outputDataBuffer_.pEvents = NULL;
						outputDataBuffer_.pSample = mftOutSample;

						auto mftProcessOutput = encoderTransform_.ProcessOutput( 0, 1, &outputDataBuffer_, &processOutputStatus );

						if ( mftProcessOutput != MF::TransformOutputResult::NeedMoreInput )
						{
							mftOutSample.SetSampleTime( llVideoTimeStamp );
							mftOutSample.SetSampleDuration( llSampleDuration );

							auto buf = mftOutSample.ConvertToContiguousBuffer( );
							auto bufLength = buf.GetCurrentLength( );
							BYTE* rawBuffer = NULL;

							auto now = GetTickCount( );

							//printf( "Writing sample %i, spacing %I64dms, sample time %I64d, sample duration %I64d, sample size %i.\n", _frameCount, now - _lastSendAt, llVideoTimeStamp, llSampleDuration, bufLength );

							
							fDurationInMicroseconds = 0;
							gettimeofday( &fPresentationTime, NULL );

							
							buf.Lock( &rawBuffer, NULL, NULL );
							if ( bufLength <= fMaxSize )
							{
								fFrameSize = bufLength;
								memmove( fTo, rawBuffer, fFrameSize );
								fNumTruncatedBytes = 0;
							}
							else
							{
								fFrameSize = fMaxSize;
								memmove( fTo, rawBuffer, fMaxSize );
								fNumTruncatedBytes = bufLength - fMaxSize;
							}

							FramedSource::afterGetting( this );
							buf.Unlock( );
							frameSent = true;
							_lastSendAt = GetTickCount( );
						}
						break;
					}
				}
				else
				{
					//printf( "No sample.\n" );
				}
			}

			if ( !frameSent )
			{
				envir( ).taskScheduler( ).triggerEvent( eventTriggerId, this );
			}

			return;
		}

	};

	class MediaFoundationMediaSubsession : public OnDemandServerMediaSubsession
	{
		char* auxSDPLine_;

		// used when setting up "auxSDPLine_"
		char doneFlag_; 
		RTPSink* dummyRTPSink_; 
		
	public:
		using Base = OnDemandServerMediaSubsession;
		MediaFoundationMediaSubsession( UsageEnvironment& env, Boolean reuseFirstSource, portNumBits initialPortNum = 6970, Boolean multiplexRTCPWithRTP = False )
			: Base( env, reuseFirstSource, initialPortNum, multiplexRTCPWithRTP )
		{ }
	
		~MediaFoundationMediaSubsession( )
		{
			delete[ ] auxSDPLine_;
		}

		static MediaFoundationMediaSubsession* createNew( UsageEnvironment& env, Boolean reuseFirstSource, portNumBits initialPortNum = 6970, Boolean multiplexRTCPWithRTP = False )
		{
			return new MediaFoundationMediaSubsession( env, reuseFirstSource, initialPortNum, multiplexRTCPWithRTP );
		}

	private: 
		void afterPlayingDummy1( )
		{
			// Unschedule any pending 'checking' task:
			envir( ).taskScheduler( ).unscheduleDelayedTask( nextTask( ) );
			// Signal the event loop that we're done:
			setDoneFlag( );
		}
		static void afterPlayingDummy( void* clientData )
		{
			MediaFoundationMediaSubsession* subsess = ( MediaFoundationMediaSubsession* )clientData;
			subsess->afterPlayingDummy1( );
		}

		void checkForAuxSDPLine1( )
		{
			nextTask( ) = nullptr;

			char const* dasl;
			if ( auxSDPLine_ != nullptr )
			{
				// Signal the event loop that we're done:
				setDoneFlag( );
			}
			else if ( dummyRTPSink_ != nullptr && ( dasl = dummyRTPSink_->auxSDPLine( ) ) != nullptr )
			{
				auxSDPLine_ = strDup( dasl );
				dummyRTPSink_ = nullptr;

				// Signal the event loop that we're done:
				setDoneFlag( );
			}
			else if ( !doneFlag_ )
			{
				// Try again after 100 ms:
				int uSecsToDelay = 100000;
				nextTask( ) = envir( ).taskScheduler( ).scheduleDelayedTask( uSecsToDelay, ( TaskFunc* )checkForAuxSDPLine, this );
			}
		}

		static void checkForAuxSDPLine( void* clientData )
		{
			MediaFoundationMediaSubsession* subsess = ( MediaFoundationMediaSubsession* )clientData;
			subsess->checkForAuxSDPLine1( );
		}
		
		
	protected:
		virtual char const* getAuxSDPLine( RTPSink* rtpSink, FramedSource* inputSource ) override
		{
			
			if ( auxSDPLine_ != nullptr )
			{
				// it's already been set up (for a previous client)
				return auxSDPLine_; 
			}

			if ( dummyRTPSink_ == nullptr )
			{ 
				// we're not already setting it up for another, concurrent stream
				// Note: For H264 video files, the 'config' information ("profile-level-id" and "sprop-parameter-sets") isn't known
				// until we start reading the file.  This means that "rtpSink"s "auxSDPLine()" will be NULL initially,
				// and we need to start reading data from our file until this changes.
				dummyRTPSink_ = rtpSink;

				// Start reading the file:
				dummyRTPSink_->startPlaying( *inputSource, afterPlayingDummy, this );

				// Check whether the sink's 'auxSDPLine()' is ready:
				checkForAuxSDPLine( this );
			}

			envir( ).taskScheduler( ).doEventLoop( &doneFlag_ );

			return auxSDPLine_;
			
		}
		virtual FramedSource* createNewStreamSource( unsigned clientSessionId, unsigned& estBitrate ) override
		{
			estBitrate = 500; // kbps, estimate

			// Create the video source:
			auto* result = MediaFoundationH264LiveSource::createNew( envir( ) );

			return H264VideoStreamFramer::createNew( envir( ), result );

			//return result;
		}
		virtual RTPSink* createNewRTPSink( Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource ) override
		{
			return H264VideoRTPSink::createNew( envir( ), rtpGroupsock, rtpPayloadTypeIfDynamic );
		}
	private:
		void setDoneFlag( ) 
		{ 
			doneFlag_ = 0xFF;
			puts( "setDoneFlag!!!!!" );
		}
	};

	class MediaFoundationRTSPServer : public RTSPServer
	{
	public:
		using Base = RTSPServer;
		MediaFoundationRTSPServer( UsageEnvironment& env, int ourSocketIPv4, int ourSocketIPv6, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationSeconds )
			: Base( env, ourSocketIPv4, ourSocketIPv6, ourPort, authDatabase, reclamationSeconds )
		{ }

		static std::unique_ptr<MediaFoundationRTSPServer> Create( UsageEnvironment& env, Port ourPort = 554, UserAuthenticationDatabase* authDatabase = nullptr, unsigned reclamationSeconds = 65 )
		{
			int ourSocketIPv4 = setUpOurSocket( env, ourPort, AF_INET );
			int ourSocketIPv6 = setUpOurSocket( env, ourPort, AF_INET6 );
			if ( ourSocketIPv4 < 0 && ourSocketIPv6 < 0 )
			{
				return nullptr;
			}

			return std::make_unique<MediaFoundationRTSPServer>( env, ourSocketIPv4, ourSocketIPv6, ourPort, authDatabase, reclamationSeconds );
		}
	};


}

#endif
