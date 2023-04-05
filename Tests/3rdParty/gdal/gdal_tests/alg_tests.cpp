#include "test_utils.h"

#include "port/cpl_conv.h"

#include "alg/gdal_alg.h"
#include "alg/gdalwarper.h"
#include "gcore/gdal_priv.h"

namespace
{
    constexpr double nearEnough = 0.0001;

    struct test_alg_data
    {
    };

    typedef struct
    {
        double dfLevel;
        int nPoints;
        double x;
        double y;
    } writeCbkData;

    static CPLErr writeCbk( double dfLevel, int nPoints,
        double* padfX, double* padfY, void* userData )
    {
        writeCbkData* data = (writeCbkData*)userData;
        data->dfLevel = dfLevel;
        data->nPoints = nPoints;
        if ( nPoints == 1 )
        {
            data->x = padfX[0];
            data->y = padfY[0];
        }
        return CE_None;
    }

    // Dummy test
    TEST( ALG, Dummy_Test )
    {
        writeCbkData data;
        memset( &data, 0, sizeof( data ) );
        GDALContourGeneratorH hCG = GDAL_CG_Create( 1, 1, FALSE, 0, 1, 0, writeCbk, &data );
        double scanline[] = { 0 };
        EXPECT_EQ( GDAL_CG_FeedLine( hCG, scanline ), CE_None );
        EXPECT_EQ( data.dfLevel, 0 );
        EXPECT_EQ( data.nPoints, 0 );
        EXPECT_NEAR( data.x, 0.0, nearEnough );
        EXPECT_NEAR( data.y, 0.0, nearEnough );
        GDAL_CG_Destroy( hCG );
    }

    // GDALWarpResolveWorkingDataType: default type
    TEST( ALG, GDALWarpResolveWorkingDataType_Default_Type_Test )
    {
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );
        GDALDestroyWarpOptions( psOptions );
    }

    // GDALWarpResolveWorkingDataType: do not change user specified type
    TEST( ALG, GDALWarpResolveWorkingDataType_Do_Not_Change_User_Specified_Type_Test )
    {
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        psOptions->eWorkingDataType = GDT_CFloat64;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CFloat64 );
        GDALDestroyWarpOptions( psOptions );
    }

    // GDALWarpResolveWorkingDataType: effect of padfSrcNoDataReal
    TEST( ALG, GDALWarpResolveWorkingDataType_Effect_Of_padfSrcNoDataReal_Test )
    {
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        psOptions->nBandCount = 1;
        psOptions->padfSrcNoDataReal =
            static_cast<double*>( CPLMalloc( sizeof( double ) ) );
        psOptions->padfSrcNoDataReal[0] = 0.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = -1.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Int16 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 2.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 256.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_UInt16 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 2.5;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Float32 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 2.12345678;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Float64 );

        GDALDestroyWarpOptions( psOptions );
    }

    // GDALWarpResolveWorkingDataType: effect of padfSrcNoDataImag
    TEST( ALG, GDALWarpResolveWorkingDataType_Effect_Of_padfSrcNoDataImag_Test )
    {
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        psOptions->nBandCount = 1;
        psOptions->padfSrcNoDataReal =
            static_cast<double*>( CPLMalloc( sizeof( double ) ) );
        psOptions->padfSrcNoDataImag =
            static_cast<double*>( CPLMalloc( sizeof( double ) ) );
        psOptions->padfSrcNoDataReal[0] = 0.0;
        psOptions->padfSrcNoDataImag[0] = 0.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 0.0;
        psOptions->padfSrcNoDataImag[0] = 1.0;
        GDALWarpResolveWorkingDataType( psOptions );
        // Could probably be CInt16
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CInt32 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 0.0;
        psOptions->padfSrcNoDataImag[0] = 1.5;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CFloat32 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfSrcNoDataReal[0] = 0.0;
        psOptions->padfSrcNoDataImag[0] = 2.12345678;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CFloat64 );

        GDALDestroyWarpOptions( psOptions );
    }


    // GDALWarpResolveWorkingDataType: effect of padfDstNoDataReal
    TEST( ALG, GDALWarpResolveWorkingDataType_Effect_Of_padfDstNoDataReal_Test )
    {
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        psOptions->nBandCount = 1;
        psOptions->padfDstNoDataReal =
            static_cast<double*>( CPLMalloc( sizeof( double ) ) );
        psOptions->padfDstNoDataReal[0] = 0.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataReal[0] = -1.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Int16 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataReal[0] = 2.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataReal[0] = 256.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_UInt16 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataReal[0] = 2.5;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Float32 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataReal[0] = 2.12345678;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Float64 );

        GDALDestroyWarpOptions( psOptions );
    }


    // GDALWarpResolveWorkingDataType: effect of padfDstNoDataImag
    TEST( ALG, GDALWarpResolveWorkingDataType_Effect_Of_padfDstNoDataImag_Test )
    {
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        psOptions->nBandCount = 1;
        psOptions->padfDstNoDataReal =
            static_cast<double*>( CPLMalloc( sizeof( double ) ) );
        psOptions->padfDstNoDataImag =
            static_cast<double*>( CPLMalloc( sizeof( double ) ) );
        psOptions->padfDstNoDataReal[0] = 0.0;
        psOptions->padfDstNoDataImag[0] = 0.0;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_Byte );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataReal[0] = 0.0;
        psOptions->padfDstNoDataImag[0] = 1.0;
        GDALWarpResolveWorkingDataType( psOptions );
        // Could probably be CInt16
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CInt32 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataImag[0] = 0.0;
        psOptions->padfDstNoDataImag[0] = 1.5;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CFloat32 );

        psOptions->eWorkingDataType = GDT_Unknown;
        psOptions->padfDstNoDataImag[0] = 0.0;
        psOptions->padfDstNoDataImag[0] = 2.12345678;
        GDALWarpResolveWorkingDataType( psOptions );
        EXPECT_EQ( psOptions->eWorkingDataType, GDT_CFloat64 );

        GDALDestroyWarpOptions( psOptions );
    }

    // Test GDALAutoCreateWarpedVRT() with creatino of an alpha band
    TEST( ALG, GDALAutoCreateWarpedVRT_Test )
    {
        GDALDatasetUniquePtr poDS(
            GDALDriver::FromHandle(
                GDALGetDriverByName( "MEM" ) )->Create( "", 1, 1, 1, GDT_Byte, nullptr ) );
        poDS->SetProjection( SRS_WKT_WGS84_LAT_LONG );
        double adfGeoTransform[6] = { 10, 1, 0, 20, 0, -1 };
        poDS->SetGeoTransform( adfGeoTransform );
        GDALWarpOptions* psOptions = GDALCreateWarpOptions( );
        psOptions->nDstAlphaBand = 2;
        GDALDatasetH hWarpedVRT =
            GDALAutoCreateWarpedVRT( GDALDataset::ToHandle( poDS.get( ) ), nullptr, nullptr,
                GRA_NearestNeighbour, 0.0,
                psOptions );
        EXPECT_TRUE( hWarpedVRT != nullptr );
        EXPECT_EQ( GDALGetRasterCount( hWarpedVRT ), 2 );
        EXPECT_EQ( GDALGetRasterColorInterpretation(
            GDALGetRasterBand( hWarpedVRT, 2 ) ), GCI_AlphaBand );
        GDALDestroyWarpOptions( psOptions );
        GDALClose( hWarpedVRT );
    }

}