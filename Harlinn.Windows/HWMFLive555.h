#pragma once
#ifndef HARLINN_WINDOWS_HWMFLIVE555_H_
#define HARLINN_WINDOWS_HWMFLIVE555_H_
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

#include <liveMedia.hh>
#include <BasicUsageEnvironment.hh>
#include <GroupsockHelper.hh>

#include <HWMediaFoundation.h>
#include <HWMFReadWrite.h>
#include <HWStrmif.h>

namespace Harlinn::Windows::Media::LiveMedia
{

	class MediaFoundationH264LiveSource : public FramedSource
	{
	public:
		using Base = FramedSource;
	public:
		static constexpr int DeviceIndex = 0;
	private:
		bool initialised_ = false;
		EventTriggerId eventTriggerId_ = 0;
		int frameCount_ = 0;

		MFMediaSource videoSource_;
		MFSourceReader videoSourceReader_;

		// The H264 Encoder MFT
		MFTransform encoderTransform_; 
		
		MFMediaType videoSourceReaderMediaType_;
		MFMediaType encoderTransformInputMediaType_; 
		MFMediaType encoderTransformOutputMediaType_;
	public:
		static MediaFoundationH264LiveSource* createNew( UsageEnvironment& env )
		{
			return new MediaFoundationH264LiveSource( env );
		}

		MediaFoundationH264LiveSource( UsageEnvironment& env ) 
			: Base( env )
		{
			eventTriggerId_ = envir( ).taskScheduler( ).createEventTrigger( deliverFrame0 );
		}

		~MediaFoundationH264LiveSource( )
		{
		}

		bool isH264VideoStreamFramer( ) const override
		{
			return true;
		}

		virtual unsigned maxFrameSize( ) const override
		{
			return 150000; 
		}

		static void deliverFrame0( void* clientData )
		{
			( ( MediaFoundationH264LiveSource* )clientData )->doGetNextFrame( );
		}

		bool Initialise( )
		{
			auto deviceSources = Media::DeviceSources::CreateVideoDeviceSources( );
			
			// Get the first available webcam.
			auto deviceSource = deviceSources[ DeviceIndex ];
			auto webcamFriendlyName = deviceSource.GetString( MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME );
			
			videoSource_ = deviceSource.ActivateObject<MFMediaSource>( );
			
			// Request video capture devices.
			MFAttributes videoSourceConfig = MFAttributes::Create( 1 );
			videoSourceConfig.SetGUID( MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID );

			videoSourceReader_ = MFSourceReader::CreateSourceReaderFromMediaSource( videoSource_, videoSourceConfig );

			videoSourceReaderMediaType_ = videoSourceReader_.GetCurrentMediaType( 0 );
			

			encoderTransform_ = Unknown::CoCreateInstanceFromClassId<MFTransform>( CLSID_CMSH264EncoderMFT );

			//Media::PrintOutputMediaTypeDescriptions( 0, encoderTransform_ );

			encoderTransformOutputMediaType_ = MFMediaType::Create( MFMediaType_Video, MFVideoFormat_H264 );
			encoderTransformOutputMediaType_.SetAverageBitRate( 442368000 );
			encoderTransformOutputMediaType_.SetFrameSize( videoSourceReaderMediaType_.GetFrameSize() );
			encoderTransformOutputMediaType_.SetFrameRate( videoSourceReaderMediaType_.GetFrameRate() );
			encoderTransformOutputMediaType_.SetPixelAspectRatio( 1, 1 );
			encoderTransformOutputMediaType_.SetUINT32( MF_MT_MPEG2_PROFILE, eAVEncH264VProfile::eAVEncH264VProfile_High );
			encoderTransformOutputMediaType_.SetInterlaceMode( MFVideoInterlaceMode::MFVideoInterlace_Progressive );
			encoderTransformOutputMediaType_.SetAllSamplesIndependent( );

			encoderTransform_.SetOutputType(0, encoderTransformOutputMediaType_ );

			//Media::PrintInputMediaTypeDescriptions( 0, encoderTransform_ );

			encoderTransformInputMediaType_ = videoSourceReaderMediaType_.Clone( );
			
			encoderTransform_.SetInputType( 0, encoderTransformInputMediaType_ );

			auto encoderTransformStatus = encoderTransform_.GetInputStatus( 0 );

			return encoderTransformStatus == MFT_INPUT_STATUS_ACCEPT_DATA;

		}

		virtual void doGetNextFrame( )
		{
			if ( !initialised_ )
			{
				initialised_ = true;
				if ( !Initialise( ) )
				{
					printf( "Video device initialisation failed, stopping." );
					return;
				}
			}

			if ( isCurrentlyAwaitingData( ) == 0 )
			{
				return;
			}
			
			DWORD streamIndex; 
			DWORD flags;
			LONGLONG videoTimeStamp;
			bool frameSent = false;

			auto videoSample = videoSourceReader_.ReadSample( MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, &streamIndex, &flags, &videoTimeStamp );
			if ( videoSample )
			{
				frameCount_++;
				videoSample.SetSampleTime( videoTimeStamp );
				auto sampleDuration = videoSample.GetSampleDuration( );

				// Pass the video sample to the H.264 transform.
				encoderTransform_.ProcessInput( 0, videoSample, 0 );

				auto encoderTransformOutputStatus = encoderTransform_.GetOutputStatus( );

				if ( encoderTransformOutputStatus == MFT_OUTPUT_STATUS_SAMPLE_READY )
				{
					auto outputStreamInfo = encoderTransform_.GetOutputStreamInfo( 0 );

					auto outSample = MFSample::Create( );

					auto memoryBuffer = MFMediaBuffer::CreateMemoryBuffer( outputStreamInfo.cbSize );
					outSample.AddBuffer( memoryBuffer );

					while ( true )
					{
						MFT_OUTPUT_DATA_BUFFER outputDataBuffer{};
						outputDataBuffer.pSample = outSample;

						DWORD processOutputStatus = 0;

						auto mftProcessOutput = encoderTransform_.ProcessOutput( 0, 1, &outputDataBuffer, &processOutputStatus );

						if ( mftProcessOutput != Media::TransformOutputResult::NeedMoreInput )
						{
							outSample.SetSampleTime( videoTimeStamp );
							outSample.SetSampleDuration( sampleDuration );

							auto buf = outSample.ConvertToContiguousBuffer( );
							auto bufLength = buf.GetCurrentLength( );
							BYTE* rawBuffer = NULL;

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
							
							buf.Unlock( );
							FramedSource::afterGetting( this );
							frameSent = true;
						}
						break;
					}
				}
			}

			if ( !frameSent )
			{
				envir( ).taskScheduler( ).triggerEvent( eventTriggerId_, this );
			}

			return;
		}

	};

	class MediaFoundationMediaSubsession : public OnDemandServerMediaSubsession
	{
		char* auxSDPLine_ = nullptr;

		// used when setting up "auxSDPLine_"
		char doneFlag_ = 0; 
		RTPSink* dummyRTPSink_ = nullptr;
		
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
			doneFlag_ = static_cast<Byte>(0xFF);
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
