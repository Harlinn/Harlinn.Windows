#include "HWSkiaSampleDrawAtlas.h"

class DrawAtlasSimViewImpl : public Harlinn::Windows::Skia::DrawAtlasView
{
public:
    using Base = Harlinn::Windows::Skia::DrawAtlasView;

    DrawAtlasSimViewImpl( )
        : Base( "DrawAtlas sim", Harlinn::Windows::Skia::draw_atlas_sim )
    {
    }

};


int main( )
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<DrawAtlasSimViewImpl>::Run( );
    return result;
}

