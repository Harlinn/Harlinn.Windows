#pragma once
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



#include <HWCommon.h>

// Media Foundation headers

#include <HWMFIDL.h>
#include <HWEVR.h>

using namespace Harlinn::Windows;
using namespace Harlinn::Windows::Media;

class TopologyBuilder
{
    // the topology itself
    MFTopology topology_;
    // the MF source
    MFMediaSource source_;
    // the EVR
    MFVideoDisplayControl videoDisplay_;
    // the target window
    HWND videoHwnd_ = nullptr;

public:
    TopologyBuilder()
    {
    };
    ~TopologyBuilder()
    {
        ShutdownSource();
    };

    // create a topology for the URL that will be rendered in the specified window
    void RenderURL(const WideString& url, HWND videoHwnd);

    // get the created topology
    const MFTopology& GetTopology() const
    {
        return topology_;
    }

    // shutdown the media source for the topology
    void ShutdownSource();

private:


    void CreateMediaSource( const WideString& url );
    void CreateTopology();

    void AddBranchToPartialTopology(const MFPresentationDescriptor& presDescriptor, DWORD streamIndex);

    MFTopologyNode CreateSourceStreamNode(const MFPresentationDescriptor& presDescr, const MFStreamDescriptor& streamDescr);

    MFTopologyNode CreateOutputNode(const MFStreamDescriptor& streamDescr, HWND hwndVideo);
};

