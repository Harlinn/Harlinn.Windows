#include <cstdio>
#include <string>
#include <unordered_map>

#include "utilities/blob_db/blob_dump_tool.h"

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

namespace po = boost::program_options;

namespace ROCKSDB_NAMESPACE::blob_db
{
    std::ostream& operator << ( std::ostream& stream, const BlobDumpTool::DisplayType& displayType )
    {
        using DisplayType = BlobDumpTool::DisplayType;
        switch ( displayType )
        {
            case DisplayType::kNone:
                stream << "none";
                break;
            case DisplayType::kRaw:
                stream << "raw";
                break;
            case DisplayType::kHex:
                stream << "hex";
                break;
            case DisplayType::kDetail:
                stream << "detail";
                break;
        }
        return stream;
    }

    std::istream& operator>> ( std::istream& in, BlobDumpTool::DisplayType& displayType )
    {
        using DisplayType = BlobDumpTool::DisplayType;
        std::string token;
        in >> token;

        boost::to_upper( token );

        if ( token == "NONE" )
        {
            displayType = DisplayType::kNone;
        }
        else if ( token == "RAW" )
        {
            displayType = DisplayType::kRaw;
        }
        else if ( token == "HEX" )
        {
            displayType = DisplayType::kHex;
        }
        else if ( token == "DETAIL" )
        {
            displayType = DisplayType::kDetail;
        }
        else
        {
            throw po::validation_error( po::validation_error::invalid_option_value, "Invalid DisplayType" );
        }

        return in;
    }

}


using namespace ROCKSDB_NAMESPACE;
using namespace ROCKSDB_NAMESPACE::blob_db;



int main( int argc, char** argv )
{
    
    using DisplayType = BlobDumpTool::DisplayType;
    const std::unordered_map<std::string, DisplayType> display_types = {
        {"none", DisplayType::kNone},
        {"raw", DisplayType::kRaw},
        {"hex", DisplayType::kHex},
        {"detail", DisplayType::kDetail},
    };

    DisplayType show_key = DisplayType::kRaw;
    DisplayType show_blob = DisplayType::kNone;
    DisplayType show_uncompressed_blob = DisplayType::kNone;
    bool show_summary = false;
    std::string file;

    po::options_description desc( "Usage:" );
    desc.add_options( )
        ( "help,h", "Displays this help message." )
        ( "file,f", po::value<std::string>(&file ), "Name of database file" )
        ( "show_key,k", po::value<DisplayType>(&show_key )->default_value( DisplayType::kRaw ), "none|raw|hex|detail" )
        ( "show_blob,b", po::value<DisplayType>( &show_blob )->default_value( DisplayType::kNone ), "none|raw|hex|detail" )
        ( "show_uncompressed_blob,r", po::value<DisplayType>( &show_uncompressed_blob )->default_value( DisplayType::kNone ), "none|raw|hex|detail" )
        ( "show_summary,s", po::value<bool>( &show_summary )->default_value( false ), "true|false" );

    po::positional_options_description p;
    p.add( "file", -1 );

    po::variables_map vm;
    po::store( po::command_line_parser( argc, argv ).options( desc ).positional( p ).run( ), vm );
    po::notify( vm );


    BlobDumpTool tool;
    Status s = tool.Run( file, show_key, show_blob, show_uncompressed_blob, show_summary );
    if ( !s.ok( ) )
    {
        fprintf( stderr, "Failed: %s\n", s.ToString( ).c_str( ) );
        return -1;
    }
    return 0;
}