#pragma once


#include <HWCommon.h>

// Media Foundation headers

#include <HWMFIDL.h>
#include <HWEVR.h>

using namespace Harlinn::Windows;

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
    void RenderURL(PCWSTR url, HWND videoHwnd);

    // get the created topology
    const MFTopology& GetTopology() const
    {
        return topology_;
    }

    // shutdown the media source for the topology
    void ShutdownSource();

private:


    void CreateMediaSource(PCWSTR sURL);
    void CreateTopology();

    void AddBranchToPartialTopology(const MFPresentationDescriptor& presDescriptor, DWORD streamIndex);

    MFTopologyNode CreateSourceStreamNode(const MFPresentationDescriptor& presDescr, const MFStreamDescriptor& streamDescr);

    MFTopologyNode CreateOutputNode(const MFStreamDescriptor& streamDescr, HWND hwndVideo);
};

