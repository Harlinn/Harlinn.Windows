#pragma once //HWMGstRTSPException.h
#ifndef HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPEXCEPTION_H_
#define HARLINN_MEDIA_GST_RTSP_HWMGSTRTSPEXCEPTION_H_
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

#include <gst/HWMGstException.h>
#include <glib/HWMgstring.h>

namespace Harlinn::Common::Core
{
    inline AnsiString ToAnsiString( GstRTSPResult rtspResult )
    {
        Harlinn::Media::GLib::StringPtr messageText( gst_rtsp_strresult( rtspResult ) );
        return ToAnsiString( messageText.c_str( ) );
    }

    inline WideString ToWideString( GstRTSPResult rtspResult )
    {
        Harlinn::Media::GLib::StringPtr messageText( gst_rtsp_strresult( rtspResult ) );
        return ToWideString( messageText.c_str( ) );
    }
}


namespace Harlinn::Media::GStreamer::Rtsp
{
    class RTSPException : public GStreamer::Exception
    {
    public:
        using Base = GStreamer::Exception;
        HARLINN_COMMON_DECLARE_STANDARD_EXCEPTION_MEMBERS2( RTSPException, HWM_EXPORT );
    };


    inline __declspec( noreturn ) void ThrowRTSPException( GstRTSPResult result, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        auto messageText = ToWideString( result );
        ExceptionLocation exceptionLocation( function, filename, lineNumber );
        RTSPException exception( exceptionLocation, static_cast< long long >( result ), messageText );
        throw exception;
    }

    inline void CheckRTSPResult( GstRTSPResult result, const wchar_t* function, const wchar_t* filename, int lineNumber )
    {
        if ( result != GstRTSPResult::GST_RTSP_OK )
        {
            ThrowRTSPException( result, function, filename, lineNumber );
        }
    }



}

#endif
