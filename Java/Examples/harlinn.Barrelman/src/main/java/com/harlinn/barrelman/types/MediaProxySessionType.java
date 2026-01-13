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
package com.harlinn.barrelman.types;

public class MediaProxySessionType {
    public final static int Unknown = 0;
    public final static int ACCAudio = 1;
    public final static int AMRAudio = 2;
    public final static int AC3Audio = 3;
    public final static int MPEGAudio = 4;
    public final static int WAVAudio = 5;
    public final static int MPEG4Video = 6;
    public final static int H264Video = 7;
    public final static int H265Video = 8;
    public final static int MPEGVideo = 9;
    public final static int MPEGVideoWithAC3Audio = 10;
    public final static int MatroskaVideo = 11;
    public final static int Oggvideo = 12;

    public final static String toString(int value) {
    	switch(value) {
    	    case Unknown:
    	        return "Unknown";
    	    case ACCAudio:
    	        return "ACCAudio";
    	    case AMRAudio:
    	        return "AMRAudio";
    	    case AC3Audio:
    	        return "AC3Audio";
    	    case MPEGAudio:
    	        return "MPEGAudio";
    	    case WAVAudio:
    	        return "WAVAudio";
    	    case MPEG4Video:
    	        return "MPEG4Video";
    	    case H264Video:
    	        return "H264Video";
    	    case H265Video:
    	        return "H265Video";
    	    case MPEGVideo:
    	        return "MPEGVideo";
    	    case MPEGVideoWithAC3Audio:
    	        return "MPEGVideoWithAC3Audio";
    	    case MatroskaVideo:
    	        return "MatroskaVideo";
    	    case Oggvideo:
    	        return "Oggvideo";
    	    default:
    	        throw new IllegalArgumentException( "Unknown MediaProxySessionType constant:" + Integer.toUnsignedString(value, 10) );
    	}
    }

    public final static int toInt(String value) {
    	switch(value) {
    	    case "Unknown":
    	        return Unknown;
    	    case "ACCAudio":
    	        return ACCAudio;
    	    case "AMRAudio":
    	        return AMRAudio;
    	    case "AC3Audio":
    	        return AC3Audio;
    	    case "MPEGAudio":
    	        return MPEGAudio;
    	    case "WAVAudio":
    	        return WAVAudio;
    	    case "MPEG4Video":
    	        return MPEG4Video;
    	    case "H264Video":
    	        return H264Video;
    	    case "H265Video":
    	        return H265Video;
    	    case "MPEGVideo":
    	        return MPEGVideo;
    	    case "MPEGVideoWithAC3Audio":
    	        return MPEGVideoWithAC3Audio;
    	    case "MatroskaVideo":
    	        return MatroskaVideo;
    	    case "Oggvideo":
    	        return Oggvideo;
    	    default:
    	        throw new IllegalArgumentException( "Unknown MediaProxySessionType constant name:" + value );
    	}
    }

}

