# A simple RTSP server publishing video from the integrated camera as a H.264 video stream  

This example uses the [LIVE555 Streaming Media](http://www.live555.com/liveMedia) library to publish
live video over RTSP from the integrated camera of my computer as a H.264 video stream encoded using
the [Microsoft Media Foundation H.264 Video Encoder](https://learn.microsoft.com/en-us/windows/win32/medfound/h-264-video-encoder).

The example demonstrates how to:

1. Publish the output of a Microsoft Media Foundation Transform as a LIVE555 Streaming Media FramedSource implementation.
2. Implement a LIVE555 Streaming Media sub-session.


