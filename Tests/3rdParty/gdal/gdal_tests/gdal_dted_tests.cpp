#include "test_utils.h"

#include "port/cpl_conv.h"

#include "alg/gdal_alg.h"
#include "alg/gdalwarper.h"
#include "gcore/gdal_priv.h"

namespace
{
    class GDAL_DTED : public ::testing::Test
    {
    protected:
        struct raster_t
        {
            std::string file_;
            int band_;
            int checksum_;
            raster_t( std::string const& f, int b, int c )
                : file_( f ), band_( b ), checksum_( c )
            {
            }
        };
        typedef std::vector<raster_t> rasters_t;

        GDALDriverH drv_ = nullptr;
        std::string drv_name_ = "DTED";
        std::string data_;
        std::string data_tmp_;
        rasters_t rasters_;


        void SetUp( ) override
        {
            drv_ = GDALGetDriverByName( drv_name_.c_str( ) );

            // Compose data path for test group
            data_ = GetCppDataDirecory( );
            data_tmp_ = GetTempDirecory( );

            rasters_.push_back( raster_t( "n43.dt0", 1, 49187 ) );
        }
    };

    // Test driver availability
    TEST_F( GDAL_DTED, DriverAvailability_Test )
    {
        EXPECT_TRUE( "DTED driver not available", nullptr != drv_ );
    }

    // Test open dataset
    TEST_F( GDAL_DTED, OpenDataset_Test )
    {
        rasters_t::const_iterator it;
        for ( it = rasters_.begin( ); it != rasters_.end( ); ++it )
        {
            auto directory = GetCppDataDirecory( );

            std::string file = directory + "\\" + it->file_;
            GDALDatasetH ds = GDALOpen( file.c_str( ), GA_ReadOnly );
            EXPECT_TRUE( nullptr != ds );
            GDALClose( ds );
        }
    }

    // Test dataset checksums
    TEST_F( GDAL_DTED, ChecksumImage_Test )
    {
        rasters_t::const_iterator it;
        for ( it = rasters_.begin( ); it != rasters_.end( ); ++it )
        {
            auto directory = GetCppDataDirecory( );

            std::string file = directory + "\\" + it->file_;
            GDALDatasetH ds = GDALOpen( file.c_str( ), GA_ReadOnly );

            EXPECT_TRUE( nullptr != ds );

            GDALRasterBandH band = GDALGetRasterBand( ds, it->band_ );
            EXPECT_TRUE( nullptr != band );

            const int xsize = GDALGetRasterXSize( ds );
            const int ysize = GDALGetRasterYSize( ds );
            const int checksum = GDALChecksumImage( band, 0, 0, xsize, ysize );

            EXPECT_EQ( checksum, it->checksum_ );

            GDALClose( ds );
        }
    }

    // Test affine transformation coefficients
    TEST_F( GDAL_DTED, AffineTransformationCoefficients_Test )
    {
        const std::size_t fileIdx = 0;

        auto directory = GetCppDataDirecory( );
        std::string file = directory + "\\" + rasters_.at( fileIdx ).file_;

        GDALDatasetH ds = GDALOpen( file.c_str( ), GA_ReadOnly );
        EXPECT_TRUE( nullptr != ds );

        double geoTransform[6] = { 0 };
        CPLErr err = GDALGetGeoTransform( ds, geoTransform );
        EXPECT_EQ( err, CE_None );

        // Test affine transformation coefficients
        const double maxError = 0.000001;
        const double expect[6] = {
            -80.004166666666663, 0.0083333333333333332, 0,
            44.00416666666667, 0, -0.0083333333333333332
        };
        EXPECT_NEAR( expect[0], geoTransform[0], maxError );
        EXPECT_NEAR( expect[1], geoTransform[1], maxError );
        EXPECT_NEAR( expect[2], geoTransform[2], maxError );
        EXPECT_NEAR( expect[3], geoTransform[3], maxError );
        EXPECT_NEAR( expect[4], geoTransform[4], maxError );
        EXPECT_NEAR( expect[5], geoTransform[5], maxError );

        GDALClose( ds );
    }

    // Test projection definition
    TEST_F( GDAL_DTED, ProjectionDefinition_Test )
    {
        const std::size_t fileIdx = 0;

        auto directory = GetCppDataDirecory( );
        std::string file = directory + "\\" + rasters_.at( fileIdx ).file_;

        GDALDatasetH ds = GDALOpen( file.c_str( ), GA_ReadOnly );
        EXPECT_TRUE( nullptr != ds );

        std::string proj( GDALGetProjectionRef( ds ) );
        EXPECT_EQ( proj.empty( ), false );

        std::string expect( "GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9122\"]],AXIS[\"Latitude\",NORTH],AXIS[\"Longitude\",EAST],AUTHORITY[\"EPSG\",\"4326\"]]" );
        EXPECT_EQ( proj, expect );

        GDALClose( ds );
    }

    // Test band data type and NODATA value
    TEST_F( GDAL_DTED, BandDataTypeAndNODATA_Test )
    {
        const std::size_t fileIdx = 0;

        auto directory = GetCppDataDirecory( );
        std::string file = directory + "\\" + rasters_.at( fileIdx ).file_;

        GDALDatasetH ds = GDALOpen( file.c_str( ), GA_ReadOnly );
        EXPECT_TRUE( nullptr != ds );

        GDALRasterBandH band = GDALGetRasterBand( ds, rasters_.at( fileIdx ).band_ );
        EXPECT_TRUE( nullptr != band );

        const double noData = GDALGetRasterNoDataValue( band, nullptr );
        EXPECT_EQ( noData, -32767 );

        EXPECT_EQ( GDALGetRasterDataType( band ), GDT_Int16 );

        GDALClose( ds );
    }



}