#include "HWSkiaSampleDrawAtlas.h"

class DrawAtlasViewImpl : public Harlinn::Windows::Skia::DrawAtlasView
{
public:
    using Base = Harlinn::Windows::Skia::DrawAtlasView;

    DrawAtlasViewImpl()
        : Base("DrawAtlas", Harlinn::Windows::Skia::draw_atlas )
    { }

};


int main()
{
    using namespace Harlinn::Windows::Skia;
    

    int result = SampleApplication<DrawAtlasViewImpl>::Run( );
    return result;
}

