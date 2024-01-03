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


// ============================================================================
// This is a rewrite of the MFWebCamRtp example application 
// originally written by by Aaron Clauson:
// ============================================================================
/******************************************************************************
* Filename: MFWebCamRtp.cpp
*
* Description:
* This file contains a C++ console application that captures the real-time video
* stream from a webcam using Windows Media Foundation, encodes it as H264 and then
* transmits it to an RTP end point.
*
* To view the RTP feed produced by this sample the steps are:
* 1. Download ffplay from http://ffmpeg.zeranoe.com/builds/ (the static build has
*    a ready to go ffplay executable),
*
* 2. Create a file called test.sdp with contents as below:
* v=0
* o=-0 0 IN IP4 127.0.0.1
* s=No Name
* t=0 0
* c=IN IP4 127.0.0.1
* m=video 1234 RTP/AVP 96
* a=rtpmap:96 H264/90000
* a=fmtp:96 packetization-mode=1
*
* 3. Start ffplay BEFORE running this sample:
* ffplay -i test.sdp -x 640 -y 480 -profile:v baseline -protocol_whitelist "file,rtp,udp"
*
* Author:
* Aaron Clauson (aaron@sipsorcery.com)
*
* History:
* 07 Sep 2015	Aaron Clauson	Created, Hobart, Australia.
* 04 Jan 2020	Aaron Clauson	Removed live555 (sledgehammer for a nail for this sample).
* 10 Jan 2020 Aaron Clauson   Added rudimentary RTP packetisation (suitable for proof of concept only).
*
* License: Public Domain (no warranty, use at own risk)
/******************************************************************************/

#include <iostream>
#include "HWMFIDL.h"
#include "HWMFReadWrite.h"
#include "HWMediaFoundation.h"
#include "HCCSocket.h"

#include <wmcodecdsp.h>
#include <codecapi.h>
#include <wmsdkidl.h>

using namespace Harlinn::Common;
using namespace Harlinn::Common::Core;
using namespace Harlinn::Common::Core::IO::Sockets;
using namespace Harlinn::Windows;

#define WEBCAM_DEVICE_INDEX 0	    // Adjust according to desired video capture device.
#define OUTPUT_FRAME_WIDTH (640)		// Adjust if the webcam does not support this frame width.
#define OUTPUT_FRAME_HEIGHT (480)		// Adjust if the webcam does not support this frame height.
#define OUTPUT_FRAME_RATE 30      // Adjust if the webcam does not support this frame rate.
#define RTP_MAX_PAYLOAD 1400      // Maximum size of an RTP packet, needs to be under the Ethernet MTU.
#define RTP_HEADER_LENGTH 12
#define RTP_VERSION 2
#define RTP_PAYLOAD_ID 96         // Needs to match the attribute set in the SDP (a=rtpmap:96 H264/90000).
#define H264_RTP_HEADER_LENGTH 2
#define FFPLAY_RTP_PORT 1234      // The port this sample will send to.

/**
* Minimal 12 byte RTP header structure. No facility for extensions etc.
*/
class RtpHeader
{
public:
    uint8_t Version = RTP_VERSION;   // 2 bits.
    uint8_t PaddingFlag = 0;        // 1 bit.
    uint8_t HeaderExtensionFlag = 0; // 1 bit.
    uint8_t CSRCCount = 0;           // 4 bits.
    uint8_t MarkerBit = 0;           // 1 bit.
    uint8_t PayloadType = 0;         // 7 bits.
    uint16_t SeqNum = 0;             // 16 bits.
    uint32_t Timestamp = 0;          // 32 bits.
    uint32_t SyncSource = 0;         // 32 bits.

    void Serialise(uint8_t** buf)
    {
        *buf = (uint8_t*)calloc(RTP_HEADER_LENGTH, 1);
        *(*buf) = (Version << 6 & 0xC0) | (PaddingFlag << 5 & 0x20) | (HeaderExtensionFlag << 4 & 0x10) | (CSRCCount & 0x0f);
        *(*buf + 1) = (MarkerBit << 7 & 0x80) | (PayloadType & 0x7f);
        *(*buf + 2) = SeqNum >> 8 & 0xff;
        *(*buf + 3) = SeqNum & 0xff;
        *(*buf + 4) = Timestamp >> 24 & 0xff;
        *(*buf + 5) = Timestamp >> 16 & 0xff;
        *(*buf + 6) = Timestamp >> 8 & 0xff;
        *(*buf + 7) = Timestamp & 0xff;
        *(*buf + 8) = SyncSource >> 24 & 0xff;
        *(*buf + 9) = SyncSource >> 16 & 0xff;
        *(*buf + 10) = SyncSource >> 8 & 0xff;
        *(*buf + 11) = SyncSource & 0xff;
    }
};


std::pair<MF::TransformOutputResult, MFSample> GetTransformOutput(const MFTransform& transform, BOOL* transformFlushed);

// Forward function definitions.
HRESULT SendH264RtpSample(const Socket& socket, const Address& dst, const MFSample& pH264Sample, uint32_t ssrc, uint32_t timestamp, uint16_t* seqNum);

int main()
{
    try
    {
        ComInitialize init;
        MF::Init mfInit;
        IO::Sockets::WSAInitTerm wsaInitTerm;

        uint16_t rtpSsrc = 3334; // Supposed to be pseudo-random.
        uint16_t rtpSeqNum = 0;
        uint32_t rtpTimestamp = 0;

        Socket rtpSocket(AddressFamily::INet, SocketType::Datagram, ProtocolType::UserDatagram);
        rtpSocket.Bind(0);
        Address dest(L"127.0.0.1", FFPLAY_RTP_PORT);


        // Get video capture device.
        auto videoSource = MF::GetCameraMediaSource(WEBCAM_DEVICE_INDEX);

        // Create source reader
        auto videoReaderAttributes = MFAttributes::Create(1);
        videoReaderAttributes.SetUINT32(MF_SOURCE_READER_ENABLE_VIDEO_PROCESSING, 1);
        auto videoReader = MFSourceReader::CreateSourceReaderFromMediaSource(videoSource, videoReaderAttributes);

        auto videoReaderNativeMediaTypes = videoReader.GetNativeMediaTypes(0);
        for (auto& videoReaderNativeMediaType : videoReaderNativeMediaTypes)
        {
            auto description = MF::GetMediaTypeDescription(videoReaderNativeMediaType);
            _putws(description.c_str());
        }


        // Note the webcam needs to support this media type. 
        auto srcOutMediaType = MFMediaType::Create();
        srcOutMediaType.SetMajorType(MFMediaType_Video);
        srcOutMediaType.SetSubType(MFVideoFormat_YUY2);
        srcOutMediaType.SetFrameRate(OUTPUT_FRAME_RATE);
        srcOutMediaType.SetFrameSize(OUTPUT_FRAME_WIDTH, OUTPUT_FRAME_HEIGHT);
        videoReader.SetCurrentMediaType(0, srcOutMediaType);

        // Create H.264 encoder.
        auto encoderTransfromUnk = Unknown::CoCreateInstanceFromClassId<Core::Unknown>(CLSID_CMSH264EncoderMFT);
        auto encoderTransfrom = encoderTransfromUnk.As<MFTransform>();

        auto interfaceNames = Com::GetSupportedKnownInterfaces(encoderTransfrom);

        auto mftInputMediaType = MFMediaType::Clone(srcOutMediaType);
        //mftInputMediaType.SetSubType(MFVideoFormat_YUY2);


        auto mftOutputMediaType = MFMediaType::Clone(mftInputMediaType);
        mftOutputMediaType.SetSubType(MFVideoFormat_H264);
        mftOutputMediaType.SetAverageBitRate(240000);
        mftOutputMediaType.SetInterlaceMode(MFVideoInterlaceMode::MFVideoInterlace_Progressive);
        mftOutputMediaType.SetMPEG2Profile(eAVEncH264VProfile::eAVEncH264VProfile_ConstrainedBase);


        encoderTransfrom.SetOutputType(0, mftOutputMediaType);
        encoderTransfrom.SetInputType(0, mftInputMediaType);


        if (auto status = encoderTransfrom.GetInputStatus(0); status != MFT_INPUT_STATUS_ACCEPT_DATA)
        {
            printf("encoderTransfrom.GetInputStatus(0) not ready to accept data.\n");
            return -1;
        }
        encoderTransfrom.ProcessMessage(MFT_MESSAGE_NOTIFY_BEGIN_STREAMING);
        encoderTransfrom.ProcessMessage(MFT_MESSAGE_NOTIFY_START_OF_STREAM);

        // Ready to go.

        printf("Reading video samples from webcam.\n");


        int sampleCount = 0;


        while (true)
        {
            LONGLONG llVideoTimeStamp = 0;
            DWORD streamIndex = 0;
            DWORD flags = 0;

            auto videoSample = videoReader.ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, &streamIndex, &flags, &llVideoTimeStamp);

            if (flags & MF_SOURCE_READERF_STREAMTICK)
            {
                printf("\tStream tick.\n");
            }
            if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
            {
                printf("\tEnd of stream.\n");
                break;
            }
            if (flags & MF_SOURCE_READERF_NEWSTREAM)
            {
                printf("\tNew stream.\n");
                break;
            }
            if (flags & MF_SOURCE_READERF_NATIVEMEDIATYPECHANGED)
            {
                printf("\tNative type changed.\n");
                break;
            }
            if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
            {
                printf("\tCurrent type changed.\n");
                break;
            }

            if (videoSample)
            {
                videoSample.SetSampleTime(llVideoTimeStamp);

                auto sampleDuration = videoSample.GetSampleDuration();
                auto sampleFlags = videoSample.GetSampleFlags();

                auto totalLength = videoSample.GetTotalLength();

                
                //printf("Sample count %d, Sample flags %d, sample duration %I64d, sample time %I64d\n", sampleCount, sampleFlags, llSampleDuration, llVideoTimeStamp);

                // Apply the H264 encoder transform
                encoderTransfrom.ProcessInput(0, videoSample, 0);


                // H264 Encoder transform processing loop. 

                MF::TransformOutputResult transformOutputResult = MF::TransformOutputResult::Success;
                while (transformOutputResult == MF::TransformOutputResult::Success)
                {

                    BOOL h264EncodeTransformFlushed = FALSE;
                    auto transformOutput = GetTransformOutput(encoderTransfrom, &h264EncodeTransformFlushed);
                    transformOutputResult = transformOutput.first;

                    auto h264EncodeOutSample = std::move(transformOutput.second);

                    if (h264EncodeTransformFlushed == TRUE)
                    {
                        // H264 encoder format changed. Clear the capture file and start again.
                        printf("H264 encoder transform flushed stream.\n");
                    }
                    else if (h264EncodeOutSample)
                    {
                        static size_t sampleCount = 0;
                        static size_t sampleTotalSize = 0;
                        sampleCount++;
                        //printf("H264 sample ready for transmission.\n");

                        SendH264RtpSample(rtpSocket, dest, h264EncodeOutSample, rtpSsrc, (uint32_t)(llVideoTimeStamp / 10000), &rtpSeqNum);
                        sampleTotalSize += h264EncodeOutSample.GetTotalLength();

                        if (h264EncodeOutSample.IsKeyFrame())
                        {
                            static size_t keyFrameCount = 0;
                            keyFrameCount++;
                            
                            if ((keyFrameCount % 100) == 0)
                            {
                                printf("Samples=%zu, key frames=%zu, total size:%zu \n", sampleCount, keyFrameCount, sampleTotalSize);
                                
                            }
                        }
                    }
                }
                

                sampleCount++;

            }
        }
    }
    catch (Exception& exc)
    {
        auto message = exc.Message();
        wprintf(L"Exception: %s\n", message.c_str());
    }
    catch (std::exception& exc)
    {
        auto message = exc.what();
        printf("Exception: %s\n", message);
    }
    catch (...)
    {
        puts("Unknown exception in main");
    }

done:

    printf("finished.\n");
    auto c = getchar();
    return 0;
}

std::pair<MF::TransformOutputResult,MFSample> GetTransformOutput(const MFTransform& transform, BOOL* transformFlushed)
{
    MFSample resultSample;
    MFT_OUTPUT_STREAM_INFO StreamInfo = { 0 };
    MF::TransformOutputDataBuffer outputDataBuffer;
    DWORD processOutputStatus = 0;
    //IMFMediaType* pChangedOutMediaType = NULL;

    *transformFlushed = FALSE;

    transform.GetOutputStreamInfo(0, &StreamInfo);

    if ((StreamInfo.dwFlags & MFT_OUTPUT_STREAM_PROVIDES_SAMPLES) == 0)
    {
        auto sample = MFSample::Create(StreamInfo.cbSize);
        outputDataBuffer.SetSample(std::move(sample));
    }

    auto outputResult = transform.ProcessOutput(0, outputDataBuffer, &processOutputStatus);


    //printf("Process output result %.2X, MFT status %.2X.\n", mftProcessOutput, processOutputStatus);

    if (outputResult == MF::TransformOutputResult::Success)
    {
        // Sample is ready and allocated on the transform output buffer.
        outputDataBuffer.MoveSampleTo(resultSample);
    }
    else if (outputResult == MF::TransformOutputResult::StreamChange)
    {
        // Format of the input stream has changed. https://docs.microsoft.com/en-us/windows/win32/medfound/handling-stream-changes
        if (outputDataBuffer.Status() == MFT_OUTPUT_DATA_BUFFER_FORMAT_CHANGE)
        {
            printf("MFT stream changed.\n");

            auto changedOutMediaType = transform.GetOutputAvailableType(0, 0);
            changedOutMediaType.SetSubType(MFVideoFormat_IYUV);


            transform.SetOutputType(0, changedOutMediaType);
            

            transform.ProcessMessage(MFT_MESSAGE_COMMAND_FLUSH);

            *transformFlushed = TRUE;
        }
        else
        {
            printf("MFT stream changed but didn't have the data format change flag set. Don't know what to do.\n");
        }

    }
    return { outputResult, std::move(resultSample)};

}



HRESULT SendH264RtpSample(const Socket& socket, const Address& dst, const MFSample& h264Sample, uint32_t ssrc, uint32_t timestamp, uint16_t* seqNum)
{
    static uint16_t h264HeaderStart = 0x1c89;   // Start RTP packet in frame 0x1c 0x89
    static uint16_t h264HeaderMiddle = 0x1c09;  // Middle RTP packet in frame 0x1c 0x09
    static uint16_t h264HeaderEnd = 0x1c49;     // Last RTP packet in frame 0x1c 0x49

    HRESULT hr = S_OK;

    

    auto buf = h264Sample.ConvertToContiguousBuffer();
    DWORD frameLength = buf.GetCurrentLength();
    

    DWORD buffCurrLen = 0, buffMaxLen = 0;
    byte* frameData = NULL;
    buf.Lock(&frameData, &buffMaxLen, &buffCurrLen);

    uint16_t pktSeqNum = *seqNum;

    for (UINT offset = 0; offset < frameLength;)
    {
        bool isLast = ((offset + RTP_MAX_PAYLOAD) >= frameLength); // Note can be first and last packet at same time if a small frame.
        UINT payloadLength = !isLast ? RTP_MAX_PAYLOAD : frameLength - offset;

        RtpHeader rtpHeader;
        rtpHeader.SyncSource = ssrc;
        rtpHeader.SeqNum = pktSeqNum++;
        rtpHeader.Timestamp = timestamp;
        rtpHeader.MarkerBit = 0;    // Set on first and last packet in frame.
        rtpHeader.PayloadType = RTP_PAYLOAD_ID;

        uint16_t h264Header = h264HeaderMiddle;

        if (isLast)
        {
            // This is the First AND Last RTP packet in the frame.
            h264Header = h264HeaderEnd;
            rtpHeader.MarkerBit = 1;
        }
        else if (offset == 0)
        {
            h264Header = h264HeaderStart;
            rtpHeader.MarkerBit = 1;
        }

        uint8_t* hdrSerialised = NULL;
        rtpHeader.Serialise(&hdrSerialised);

        int rtpPacketSize = RTP_HEADER_LENGTH + H264_RTP_HEADER_LENGTH + payloadLength;
        uint8_t* rtpPacket = (uint8_t*)malloc(rtpPacketSize);
        memcpy_s(rtpPacket, rtpPacketSize, hdrSerialised, RTP_HEADER_LENGTH);
        rtpPacket[RTP_HEADER_LENGTH] = (byte)(h264Header >> 8 & 0xff);
        rtpPacket[RTP_HEADER_LENGTH + 1] = (byte)(h264Header & 0xff);
        memcpy_s(&rtpPacket[RTP_HEADER_LENGTH + H264_RTP_HEADER_LENGTH], payloadLength, &frameData[offset], payloadLength);

        //printf("Sending RTP packet, length %d.\n", rtpPacketSize);

        socket.SendTo((const char*)rtpPacket, rtpPacketSize, dst);

        offset += payloadLength;

        free(hdrSerialised);
        free(rtpPacket);
    }

    buf.Unlock();

    *seqNum = pktSeqNum;

    return hr;
}
