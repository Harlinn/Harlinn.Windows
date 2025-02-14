/*
   Copyright 2024-2025 Espen Harlinn

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


#include <HWSkiaSample3D.h>



class SampleBump3D : public SampleCubeBase
{
    sk_sp<SkShader>        fBmpShader, fImgShader;
    sk_sp<SkRuntimeEffect> fEffect;
    SkRRect                fRR;

public:
    SampleBump3D( ) 
        : SampleCubeBase( Flags( kCanRunOnCPU | kShowLightDome ) ) 
    {}

    SkString name( ) override 
    { 
        return SkString( "bump3d" ); 
    }

    void onOnceBeforeDraw( ) override
    {
        fRR = SkRRect::MakeRectXY( { 20, 20, 380, 380 }, 50, 50 );
        auto img = GetResourceAsImage( "images/brickwork-texture.jpg" );
        fImgShader = img->makeShader( SkSamplingOptions( ), SkMatrix::Scale( 2, 2 ) );
        img = GetResourceAsImage( "images/brickwork_normal-map.jpg" );
        fBmpShader = img->makeShader( SkSamplingOptions( ), SkMatrix::Scale( 2, 2 ) );

        const char code[] = R"(
            uniform shader color_map;
            uniform shader normal_map;

            uniform float4x4 localToWorld;
            uniform float4x4 localToWorldAdjInv;
            uniform float3   lightPos;

            float3 convert_normal_sample(half4 c) {
                float3 n = 2 * c.rgb - 1;
                n.y = -n.y;
                return n;
            }

            half4 main(float2 p) {
                float3 norm = convert_normal_sample(normal_map.eval(p));
                float3 plane_norm = normalize(localToWorldAdjInv * norm.xyz0).xyz;

                float3 plane_pos = (localToWorld * p.xy01).xyz;
                float3 light_dir = normalize(lightPos - plane_pos);

                float ambient = 0.2;
                float dp = dot(plane_norm, light_dir);
                float scale = min(ambient + max(dp, 0), 1);

                return color_map.eval(p) * scale.xxx1;
            }
        )";
        auto [effect, error] = SkRuntimeEffect::MakeForShader( SkString( code ) );
        if ( !effect )
        {
            SkDebugf( "runtime error %s\n", error.c_str( ) );
        }
        fEffect = effect;
    }

    void drawContent( SkCanvas* canvas,
        SkColor color,
        int index,
        bool drawFront,
        const SkM44& localToWorld ) override
    {
        if ( !drawFront || !front( canvas->getLocalToDevice( ) ) )
        {
            return;
        }

        SkRuntimeShaderBuilder builder( fEffect );
        builder.uniform( "lightPos" ) = fLight.computeWorldPos( fSphere );
        builder.uniform( "localToWorld" ) = localToWorld;
        builder.uniform( "localToWorldAdjInv" ) = normals( localToWorld );

        builder.child( "color_map" ) = fImgShader;
        builder.child( "normal_map" ) = fBmpShader;

        SkPaint paint;
        paint.setColor( color );
        paint.setShader( builder.makeShader( nullptr, true ) );

        canvas->drawRRect( fRR, paint );
    }
};

int main()
{
    using namespace Harlinn::Windows::Skia;
    int result = SampleApplication<SampleBump3D>::Run( );
    return result;

}

