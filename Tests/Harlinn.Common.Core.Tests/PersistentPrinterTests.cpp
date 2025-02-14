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

#include "pch.h"
#include <HCCPersistentPrinter.h>

using namespace Harlinn::Common;
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

BOOST_FIXTURE_TEST_SUITE( PersistentPrinterTests, LocalFixture )

// --run_test=PersistentPrinterTests/EmptyTest1
BOOST_AUTO_TEST_CASE( EmptyTest1 )
{
    auto descriptor = Persistent::Descriptor( );
    IO::MemoryStream argumentsStream;
    AnsiString formatString;

    IO::MemoryStream memoryStream;
    Persistent::Printer printer( formatString.data(), formatString.size(), reinterpret_cast<const Byte*>(&descriptor), argumentsStream, memoryStream );
    printer.Print( );
    auto memoryStreamSize = memoryStream.Size( );
    BOOST_CHECK( memoryStreamSize == 0);
}

// --run_test=PersistentPrinterTests/SimpleBooleanTest1
BOOST_AUTO_TEST_CASE( SimpleBooleanTest1 )
{
    // The argument type
    using ValueType = bool;

    // The argument
    ValueType argumentValue = true;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );
    
    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "true";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleBooleanTest2
BOOST_AUTO_TEST_CASE( SimpleBooleanTest2 )
{
    // The argument type
    using ValueType = bool;

    // The argument
    ValueType argumentValue = true;

    // The format string that will be used to format the data
    AnsiString formatString{ "Arg={}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "Arg=true";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleSByteTest1
BOOST_AUTO_TEST_CASE( SimpleSByteTest1 )
{
    // The argument type
    using ValueType = SByte;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleSByteTest2
BOOST_AUTO_TEST_CASE( SimpleSByteTest2 )
{
    // The argument type
    using ValueType = SByte;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleSByteTest3
BOOST_AUTO_TEST_CASE( SimpleSByteTest3 )
{
    // The argument type
    using ValueType = SByte;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleByteTest1
BOOST_AUTO_TEST_CASE( SimpleByteTest1 )
{
    // The argument type
    using ValueType = Byte;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleByteTest2
BOOST_AUTO_TEST_CASE( SimpleByteTest2 )
{
    // The argument type
    using ValueType = Byte;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleByteTest3
BOOST_AUTO_TEST_CASE( SimpleByteTest3 )
{
    // The argument type
    using ValueType = Byte;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt16Test1
BOOST_AUTO_TEST_CASE( SimpleInt16Test1 )
{
    // The argument type
    using ValueType = Int16;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt16Test2
BOOST_AUTO_TEST_CASE( SimpleInt16Test2 )
{
    // The argument type
    using ValueType = Int16;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt16Test3
BOOST_AUTO_TEST_CASE( SimpleInt16Test3 )
{
    // The argument type
    using ValueType = Int16;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt16Test1
BOOST_AUTO_TEST_CASE( SimpleUInt16Test1 )
{
    // The argument type
    using ValueType = UInt16;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt16Test2
BOOST_AUTO_TEST_CASE( SimpleUInt16Test2 )
{
    // The argument type
    using ValueType = UInt16;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt16Test3
BOOST_AUTO_TEST_CASE( SimpleUInt16Test3 )
{
    // The argument type
    using ValueType = UInt16;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt32Test1
BOOST_AUTO_TEST_CASE( SimpleInt32Test1 )
{
    // The argument type
    using ValueType = Int32;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt32Test2
BOOST_AUTO_TEST_CASE( SimpleInt32Test2 )
{
    // The argument type
    using ValueType = Int32;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt32Test3
BOOST_AUTO_TEST_CASE( SimpleInt32Test3 )
{
    // The argument type
    using ValueType = Int32;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt32Test1
BOOST_AUTO_TEST_CASE( SimpleUInt32Test1 )
{
    // The argument type
    using ValueType = UInt32;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt32Test2
BOOST_AUTO_TEST_CASE( SimpleUInt32Test2 )
{
    // The argument type
    using ValueType = UInt32;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt32Test3
BOOST_AUTO_TEST_CASE( SimpleUInt32Test3 )
{
    // The argument type
    using ValueType = UInt32;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}


// --run_test=PersistentPrinterTests/SimpleInt64Test1
BOOST_AUTO_TEST_CASE( SimpleInt64Test1 )
{
    // The argument type
    using ValueType = Int64;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt64Test2
BOOST_AUTO_TEST_CASE( SimpleInt64Test2 )
{
    // The argument type
    using ValueType = Int64;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleInt64Test3
BOOST_AUTO_TEST_CASE( SimpleInt64Test3 )
{
    // The argument type
    using ValueType = Int64;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt64Test1
BOOST_AUTO_TEST_CASE( SimpleUInt64Test1 )
{
    // The argument type
    using ValueType = UInt64;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt64Test2
BOOST_AUTO_TEST_CASE( SimpleUInt64Test2 )
{
    // The argument type
    using ValueType = UInt64;

    // The argument
    ValueType argumentValue = 0b10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:b}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleUInt64Test3
BOOST_AUTO_TEST_CASE( SimpleUInt64Test3 )
{
    // The argument type
    using ValueType = UInt64;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleSingleTest1
BOOST_AUTO_TEST_CASE( SimpleSingleTest1 )
{
    // The argument type
    using ValueType = float;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "10";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleSingleTest2
BOOST_AUTO_TEST_CASE( SimpleSingleTest2 )
{
    // The argument type
    using ValueType = float;

    // The argument
    ValueType argumentValue = 10;

    // The format string that will be used to format the data
    AnsiString formatString{ "{:e}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "1.000000e+01";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleSingleTest3
BOOST_AUTO_TEST_CASE( SimpleSingleTest3 )
{
    // The argument type
    using ValueType = float;

    // The argument
    ValueType argumentValue1 = 10;
    ValueType argumentValue2 = 11;

    // The format string that will be used to format the data
    AnsiString formatString{ "first:({}), second:({})" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue1, argumentValue2 );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue1, argumentValue2 );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "first:(10), second:(11)";
    BOOST_CHECK( equal );
}


// --run_test=PersistentPrinterTests/SimpleCStringTest1
BOOST_AUTO_TEST_CASE( SimpleCStringTest1 )
{
    // The argument type
    //using ValueType = char*;

    // The argument
    auto argumentValue = "12345678901234567890";

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "12345678901234567890";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleVectorBoolTest1
BOOST_AUTO_TEST_CASE( SimpleVectorBoolTest1 )
{
    // The argument type
    //using ValueType = char*;

    // The argument
    std::vector<bool> argumentValue = { true, false };

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "{true;false}";
    BOOST_CHECK( equal );
}

// --run_test=PersistentPrinterTests/SimpleVectorTest1
BOOST_AUTO_TEST_CASE( SimpleVectorTest1 )
{
    // The argument type
    //using ValueType = char*;

    // The argument
    std::vector<double> argumentValue = { .01, .02 };

    // The format string that will be used to format the data
    AnsiString formatString{ "{}" };

    // The stream that will provide the serialized binary 
    // representation of the arguments to the format string
    IO::MemoryStream argumentsStream;
    IO::BinaryWriter<IO::MemoryStream> writer( argumentsStream );

    // The stream that will receive the formatted output
    IO::MemoryStream destinationStream;

    // 1. Create a descriptor based on the type of the arguments passed to 
    //    Persistent::Descriptor - it does not care about the contents of the 
    //    arguments, and it can be fully evaluated at compile time.
    constexpr auto descriptor = Persistent::Descriptor( argumentValue );

    // 2. Persistent::Write uses the writer to serialize the remaining arguments 
    //    to argumentsStream. Note that, except for the writer argument, the type, 
    //    number, and order of the additional arguments to Persistent::Write
    //    must match the type, number, and order of the arguments passed to
    //    Persistent::Descriptor.
    Persistent::Write( writer, argumentValue );

    // 3. Reset the position pf the stream, as the Persistent::Printer 
    //    object will start reading argument data from the current position 
    //    of the argumentsStream.
    argumentsStream.SetPosition( 0 );

    // 4. Set up the Persistent::Printer object
    Persistent::Printer printer( formatString, descriptor, argumentsStream, destinationStream );

    // 5. Generate the formatted output
    printer.Print( );

    // 6. Verify the result 
    auto destinationStreamSize = destinationStream.Size( );
    BOOST_CHECK( destinationStreamSize != 0 );
    AnsiString streamedResult = ToAnsiString( destinationStream );
    bool equal = streamedResult == "{0.01;0.02}";
    BOOST_CHECK( equal );
}




BOOST_AUTO_TEST_SUITE_END( )