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

#include "pch.h"
using namespace Harlinn::Common::Core;
namespace
{
    class LocalFixture
    {
    public:
        LocalFixture( ) {}
        ~LocalFixture( ) {}
    };
}

BOOST_FIXTURE_TEST_SUITE( FileTests, LocalFixture )

// --run_test=FileTests/WriteReadTest1
BOOST_AUTO_TEST_CASE( WriteReadTest1 )
{
    auto filename = IO::Directory::GetTemporary( ) + L"WriteReadTest1.txt";

    IO::FileStream fileStream( filename,
        IO::FileAccess::Default,
        IO::FileShare::ReadWrite,
        IO::FileMode::OpenOrCreate,
        IO::FileAttributes::Normal,
        IO::FileOptions::DeleteOnClose );

    std::vector<AnsiString> lines1(
        {
            { AnsiString("line1") },
            { AnsiString("line2") },
            { AnsiString("line3") },
            { AnsiString("line4") },
            { AnsiString("line5") }
        } );

    fileStream.WriteFile( lines1 );

    std::vector<AnsiString> lines2;
    fileStream.ReadFile( lines2 );

    auto linesAreEqual = lines1 == lines2;

    BOOST_CHECK( linesAreEqual );
}

// --run_test=FileTests/WriteReadTest2
BOOST_AUTO_TEST_CASE( WriteReadTest2 )
{
    auto filename = IO::Directory::GetTemporaryA( ) + "WriteReadTest2.txt";

    std::vector<AnsiString> lines1(
        {
            { AnsiString("line1") },
            { AnsiString("line2") },
            { AnsiString("line3") },
            { AnsiString("line4") },
            { AnsiString("line5") }
        } );

    IO::File::WriteAllLines( filename, lines1 );

    std::vector<AnsiString> lines2;
    IO::File::ReadAllLines( filename, lines2 );

    IO::File::Delete( filename );

    auto linesAreEqual = lines1 == lines2;

    BOOST_CHECK( linesAreEqual );
}

// --run_test=FileTests/WriteReadTest3
BOOST_AUTO_TEST_CASE( WriteReadTest3 )
{
    auto filename = IO::Directory::GetTemporaryA( ) + "WriteReadTest3.txt";

    AnsiString lines1( "line1\r\nline2\r\nline3\r\nline4\r\nline5");

    IO::File::WriteAllText( filename, lines1 );

    auto filesize = IO::File::Size( filename );

    AnsiString lines2;
    IO::File::ReadAllText( filename, lines2 );

    IO::File::Delete( filename );

    auto linesAreEqual = lines1 == lines2;

    BOOST_CHECK( linesAreEqual );
}

// --run_test=FileTests/WriteReadTest4
BOOST_AUTO_TEST_CASE( WriteReadTest4 )
{
    auto filename = IO::Directory::GetTemporaryA( ) + "WriteReadTest4.txt";

    std::vector<AnsiString> expectedLines(
        {
            { AnsiString("line1") },
            { AnsiString("line2") },
            { AnsiString("line3") },
            { AnsiString("line4") },
            { AnsiString("line5") }
        } );

    AnsiString lines1( "line1\r\nline2\r\nline3\r\nline4\r\nline5" );

    IO::File::WriteAllText( filename, lines1 );
    

    std::vector<AnsiString> lines2;
    IO::File::ReadAllLines( filename, lines2 );

    IO::File::Delete( filename );

    auto linesAreEqual = lines2 == expectedLines;

    BOOST_CHECK( linesAreEqual );
}



BOOST_AUTO_TEST_SUITE_END( )