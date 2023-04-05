#include "TopoBuilder.h"



//
// Initiates topology building from the file URL by first creating a media source, and then
// adding source and sink nodes for every stream found in the file.
//
void TopologyBuilder::RenderURL(PCWSTR fileUrl, HWND videoHwnd)
{
    videoHwnd_ = videoHwnd;

    // first create the media source for the file/stream passed in.  Fail and fall out if
    // the media source creation fails (e.g. if the file format is not recognized)
    CreateMediaSource(fileUrl);

    CreateTopology();
}



//
// Create a media source for the specified URL string.  The URL can be a path to a stream, 
// or it can be a path to a local file.
//
void TopologyBuilder::CreateMediaSource(PCWSTR sURL)
{
    // Create the source resolver.
    auto sourceResolver = MFSourceResolver::Create();

    // Use the synchronous source resolver to create the media source.
    // indicate that we want a source object, and 
    // pass in optional source search parameters
    auto source = sourceResolver.CreateObjectFromURL( sURL, MF_RESOLUTION_MEDIASOURCE |  MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE );

    // Get the MFMediaSource from the media source.
    source_ = source.As<MFMediaSource>();
}



//
// Since we created the source, we are responsible for shutting it down.
//
void TopologyBuilder::ShutdownSource(void)
{    
    if(source_)
    {
        // shut down the source
        source_.Shutdown();
        
        // release the source, since all subsequent calls to it will fail
        source_.ResetPtr();
    }
}



//
// Create a playback topology from the media source by extracting presentation
// and stream descriptors from the source, and creating a sink for each of them.
//
void TopologyBuilder::CreateTopology(void)
{
    

    
    // release the old topology if there was one        
    topology_.ResetPtr();
        
    // Create a new topology.
    topology_ = MFTopology::Create();

    

    // Create the presentation descriptor for the media source - a container object that
    // holds a list of the streams and allows selection of streams that will be used.
    auto presDescriptor = source_.CreatePresentationDescriptor();
    

    // Get the number of streams in the media source
    auto nSourceStreams = presDescriptor.GetStreamDescriptorCount();
    

    // For each stream, create source and sink nodes and add them to the topology.
    for (DWORD x = 0; x < nSourceStreams; x++)
    {
        try
        {
            AddBranchToPartialTopology(presDescriptor, x);
        }
        catch (Exception& exc)
        {
            // if we failed to build a branch for this stream type, then deselect it
            // that will cause the stream to be disabled, and the source will not produce
            // any data for it
            presDescriptor.DeselectStream(x);
        }
    }
    
    
}


//
//  Adds a topology branch for one stream.
//
//  pPresDescriptor: The source's presentation descriptor.
//  nStream: Index of the stream to render.
//
//  For each stream, we must do the following steps:
//    1. Create a source node associated with the stream.
//    2. Create a sink node for the renderer.
//    3. Connect the two nodes.
//  The media session will resolve the topology, inserting intermediate decoder and other 
//  transform MFTs that will process the data in preparation for consumption by the 
// renderers.
//
void TopologyBuilder::AddBranchToPartialTopology( const MFPresentationDescriptor& presDescriptor, DWORD streamIndex )
{
    BOOL streamSelected = FALSE;

    // Get the stream descriptor for this stream (information about stream).
    auto streamDescriptor = presDescriptor.GetStreamDescriptorByIndex(streamIndex, &streamSelected);
        
    // Create the topology branch only if the stream is selected - IE if the user wants
    // to play it.
    if (streamSelected)
    {
        // Create a source node for this stream.
        auto sourceNode = CreateSourceStreamNode(presDescriptor, streamDescriptor);
        

        // Create the sink node for the renderer.
        auto outputNode = CreateOutputNode(streamDescriptor, videoHwnd_);
        

        // Add the source and sink nodes to the topology.
        topology_.AddNode(sourceNode);

        topology_.AddNode(outputNode);

        // Connect the source node to the sink node.  The resolver will find the
        // intermediate nodes needed to convert media types.
        sourceNode.ConnectOutput(0, outputNode, 0);
    }
}



//
//  Create a source node for the specified stream
//
//  pPresDescriptor: Presentation descriptor for the media source.
//  pStreamDescriptor: Stream descriptor for the stream.
//  returns the new node.
//
MFTopologyNode TopologyBuilder::CreateSourceStreamNode(const MFPresentationDescriptor& presDescr, const MFStreamDescriptor& streamDescr)
{
    // Create the topology node, indicating that it must be a source node.
    auto node = MFTopologyNode::Create(MF_TOPOLOGY_SOURCESTREAM_NODE);

    // Associate the node with the source by passing in a pointer to the media source
    // and indicating that it is the source
    node.SetUnknown(MF_TOPONODE_SOURCE, source_);

    // Set the node presentation descriptor attribute of the node by passing 
    // in a pointer to the presentation descriptor
    node.SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, presDescr);

    // Set the node stream descriptor attribute by passing in a pointer to the stream
    // descriptor
    node.SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, streamDescr);

    return node;
}




//
//  This function creates an output node for a stream (sink).
//
MFTopologyNode TopologyBuilder::CreateOutputNode(const MFStreamDescriptor& streamDescr, HWND hwndVideo)
{
    // Get the media type handler for the stream, which will be used to process
    // the media types of the stream.  The handler stores the media type.
    auto handler = streamDescr.GetMediaTypeHandler();

    // Get the major media type (e.g. video or audio)
    auto majorType = handler.GetMajorType();
    
    MFActivate rendererActivate;


    // Create an IMFActivate controller object for the renderer, based on the media type
    // The activation objects are used by the session in order to create the renderers 
    // only when they are needed - i.e. only right before starting playback.  The 
    // activation objects are also used to shut down the renderers.
    if (majorType == MFMediaType_Audio)
    {
        // if the stream major type is audio, create the audio renderer.
        rendererActivate = MFActivate::CreateAudioRendererActivate();
    }
    else if (majorType == MFMediaType_Video)
    {
        // if the stream major type is video, create the video renderer, passing in the
        // video window handle - that's where the video will be playing.
        rendererActivate = MFActivate::CreateVideoRendererActivate(hwndVideo);
    }
    else
    {
        // fail if the stream type is not video or audio.  For example, fail
        // if we encounter a CC stream.
        throw Exception("Unexpected media type");
    }
    
    // Create the node that will represent the renderer
    auto node = MFTopologyNode::Create(MF_TOPOLOGY_OUTPUT_NODE);

    // Store the IActivate object in the sink node - it will be extracted later by the
    // media session during the topology render phase.
    node.SetObject(rendererActivate);

    return node;
}









