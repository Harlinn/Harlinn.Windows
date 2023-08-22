#include <HCCDebugServiceHost.h>


using namespace Harlinn::Common::Core;

namespace po = boost::program_options;


class Options
{
    WideString name_;
public:
    Options( ) = default;

    void Parse( int argc, const wchar_t** argv )
    {
        AnsiString name;
        po::options_description desc( "Allowed options" );
        desc.add_options( )
            ( "help", "produce help message" )
            ( "name", po::wvalue<WideString>( &name_ ), "set name" );


        po::variables_map vm;
        po::store( po::wcommand_line_parser( argc, argv ) // <<<
            .options( desc )
            .run( ),
            vm );
        po::notify( vm );

        //po::variables_map vm;
        //po::store( po::parse_command_line( argc, argv, desc ), vm );
        //po::notify( vm );

    }

};


class MyService : public Services::Service<MyService>
{
public:
    using Base = Services::Service<MyService>;

    MyService()
        : Base()
    { }

    static constexpr const wchar_t* ServiceName( )
    {
        return L"MyTestService";
    }
};










int main( int argc, const wchar_t** argv )
{
    std::cout << "Hello World!\n";
}

