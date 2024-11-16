#include "pch.h"
#include "HCCDemangle.h"
#include <boost/locale.hpp>
#include "HCCException.h"

// Original comment:

// Pharos Demangler
//
// Copyright 2017 Carnegie Mellon University. All Rights Reserved.
//
// NO WARRANTY. THIS CARNEGIE MELLON UNIVERSITY AND SOFTWARE ENGINEERING
// INSTITUTE MATERIAL IS FURNISHED ON AN "AS-IS" BASIS. CARNEGIE MELLON
// UNIVERSITY MAKES NO WARRANTIES OF ANY KIND, EITHER EXPRESSED OR
// IMPLIED, AS TO ANY MATTER INCLUDING, BUT NOT LIMITED TO, WARRANTY OF
// FITNESS FOR PURPOSE OR MERCHANTABILITY, EXCLUSIVITY, OR RESULTS
// OBTAINED FROM USE OF THE MATERIAL. CARNEGIE MELLON UNIVERSITY DOES NOT
// MAKE ANY WARRANTY OF ANY KIND WITH RESPECT TO FREEDOM FROM PATENT,
// TRADEMARK, OR COPYRIGHT INFRINGEMENT.
//
// Released under a BSD-style license, please see license.txt or contact
// permission@sei.cmu.edu for full terms.
//
// [DISTRIBUTION STATEMENT A] This material has been approved for public
// release and unlimited distribution.  Please see Copyright notice for
// non-US Government use and distribution.
//
// DM17-0949

/*
   Copyright 2024 Espen Harlinn

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


namespace Harlinn::Common::Core::Demangle
{
    HARLINN_COMMON_IMPLEMENT_STANDARD_EXCEPTION_MEMBERS( Error )

    namespace
    {

#ifdef X
#undef X
#endif
#define X(e, s) s

        const char* code_strings[] = {
#include "HCCDemangle.m"
        };
#undef X
    }

    HCC_EXPORT const char* code_string( Code c )
    {
        auto result = code_strings[ static_cast< size_t >( c ) ];
        return result;
    }

    namespace detail
    {

        class VisualStudioDemangler;

        // Wrapper object that saves a reference stack, replacing it with an empty one.  The reference
        // stack will be re-replaced when the save_stack object exists scope.
        struct save_stack
        {
            save_stack( ReferenceStack& stack, VisualStudioDemangler& dm, char const* n );
            ~save_stack( );

            VisualStudioDemangler& demangler;
            ReferenceStack saved;
            ReferenceStack& original;
            char const* name;
        };

        AnsiString str( DemangledTypePtr const& p )
        {
            if ( p )
            {
                return TextOutput( ).convert( *p );
            }
            return AnsiString( );
        }

        class VisualStudioDemangler
        {
        private:
            friend struct save_stack;

            const AnsiString& mangled;
            bool debug;
            size_t offset;
            AnsiString error;

            // These are pointers because we need to swap them out when we enter and leave templates.
            ReferenceStack name_stack;
            ReferenceStack type_stack;

            char get_next_char( );
            char get_current_char( );
            void advance_to_next_char( );

            [[noreturn]] void bad_code( char c, const AnsiString& desc );
            [[noreturn]] void bad_code( char c, const char* desc );
            [[noreturn]] void general_error( const AnsiString& e );
            [[noreturn]] void general_error( const char* e );

            // Given a stack and a position character, safely resolve and return the reference.
            DemangledTypePtr resolve_reference( ReferenceStack& stack, char poschar );

            DemangledTypePtr get_type( DemangledTypePtr t, bool push = false );
            DemangledTypePtr get_type( bool push = false ) { return get_type( nullptr, push ); }
            DemangledTypePtr get_array_type( DemangledTypePtr& t );
            DemangledTypePtr& get_pointer_type( DemangledTypePtr& t );
            DemangledTypePtr add_templated_type( DemangledTypePtr& t );
            DemangledTypePtr& get_return_type( DemangledTypePtr& t );
            DemangledTypePtr& get_fully_qualified_name( DemangledTypePtr& t, bool push = true );
            DemangledTypePtr& get_symbol_type( DemangledTypePtr& t );
            DemangledTypePtr& get_function( DemangledTypePtr& t );
            DemangledTypePtr& get_storage_class( DemangledTypePtr& t );
            DemangledTypePtr& get_storage_class_modifiers( DemangledTypePtr& t );
            DemangledTypePtr& get_managed_properties( DemangledTypePtr& t, int& cli_array );
            DemangledTypePtr& get_real_enum_type( DemangledTypePtr& t );
            DemangledTypePtr& add_rtti( DemangledTypePtr& t );
            DemangledTypePtr& process_return_storage_class( DemangledTypePtr& t );
            DemangledTypePtr& process_calling_convention( DemangledTypePtr& t );
            DemangledTypePtr& process_method_storage_class( DemangledTypePtr& t );
            DemangledTypePtr& add_special_name_code( DemangledTypePtr& t );
            DemangledTypePtr& get_string( DemangledTypePtr& t );
            DemangledTypePtr get_anonymous_namespace( );

            // Get symbol always allocates a new DemangledType.
            DemangledTypePtr get_symbol( );

            // This is a mocked up helper for basic types.   More work is needed.
            DemangledTypePtr& update_simple_type( DemangledTypePtr& t, Code code );
            DemangledTypePtr& update_method( DemangledTypePtr& t, Scope scope,
                MethodProperty property, Distance distance );
            DemangledTypePtr& update_member( DemangledTypePtr& t, Scope scope, MethodProperty property );
            DemangledTypePtr& update_storage_class( DemangledTypePtr& t, Distance distance,
                bool is_const, bool is_volatile,
                bool is_func, bool is_based, bool is_member );

            AnsiString get_literal( );
            void get_symbol_start( );
            int64_t get_number( );

            // Some helper functions to make debugging a little prettier.
            void progress( const AnsiString& msg );
            void progress( const char* msg );
            void print_stack( ReferenceStack const& stack, const AnsiString& msg );
            void print_stack( ReferenceStack const& stack, const char* msg );
            void stack_debug( ReferenceStack const& stack, size_t position, const AnsiString& msg );
            void stack_debug( ReferenceStack const& stack, size_t position, const char* msg );
            save_stack push_names( );
            save_stack push_types( );

            void stack_saver( ReferenceStack& stack, char const* stack_name,
                DemangledTypePtr const& name )
            {
                if ( stack.size( ) < 10 )
                {
                    stack.push_back( std::make_shared<DemangledType>( *name ) );
                    stack_debug( stack, stack.size( ) - 1, AnsiString(stack_name) );
                }
            }

            void save_name( DemangledTypePtr const& name )
            {
                stack_saver( name_stack, "name", name );
            }

            void save_type( DemangledTypePtr const& type )
            {
                stack_saver( type_stack, "type", type );
            }
        public:

            VisualStudioDemangler( const AnsiString& mangled, bool debug = false );

            DemangledTypePtr analyze( );
        };

        save_stack::save_stack( ReferenceStack& stack, VisualStudioDemangler& dm, char const* n )
            : demangler( dm ), original( stack ), name( n )
        {
            swap( saved, original );
            if ( demangler.debug )
            {
                std::cerr << "Pushing " << name << " stack and resetting to empty" << std::endl;
            }
        }

        inline save_stack::~save_stack( )
        {
            swap( saved, original );
            if ( demangler.debug )
            {
                std::cerr << "Popping " << name << " stack" << std::endl;
                demangler.print_stack( original, AnsiString( name ) );
            }
        }

        inline save_stack VisualStudioDemangler::push_names( )
        {
            return save_stack( name_stack, *this, "name" );
        }

        inline save_stack VisualStudioDemangler::push_types( )
        {
            return save_stack( type_stack, *this, "type" );
        }

    } // namespace detail

    HCC_EXPORT DemangledTypePtr visual_studio_demangle( const AnsiString& mangled, bool debug )
    {
        detail::VisualStudioDemangler demangler( mangled, debug );
        return demangler.analyze( );
    }

    AnsiString quote_string( const AnsiString& input )
    {
        static auto special_chars = "\"\\\a\b\f\n\r\t\v";
        static auto names = "\"\\abfnrtv";
        AnsiString output;
        output.reserve( input.size( ) + 2 );
        output.push_back( '\"' );
        for ( auto c : input )
        {
            if ( c == '\0' )
            {
                output.push_back( '\\' );
                output.push_back( '0' );
            }
            else
            {
                auto pos = std::strchr( special_chars, c );
                if ( pos )
                {
                    output.push_back( '\\' );
                    output.push_back( *( names + ( pos - special_chars ) ) );
                }
                else
                {
                    output.push_back( c );
                }
            }
        }
        output.push_back( '\"' );
        return output;
    }

    DemangledTemplateParameter::DemangledTemplateParameter( DemangledTypePtr t )
        : type( t ), constant_value( 0 )
    {
    }

    DemangledTemplateParameter::DemangledTemplateParameter( int64_t c )
        : type( nullptr ), constant_value( c )
    {
    }

    namespace detail
    {

        VisualStudioDemangler::VisualStudioDemangler( const AnsiString& m, bool d )
            : mangled( m ), debug( d ), offset( 0 )
        {
        }

        char VisualStudioDemangler::get_next_char( )
        {
            // Check bounds and all that...
            offset++;
            return get_current_char( );
        }

        void VisualStudioDemangler::advance_to_next_char( )
        {
            offset++;
        }

        char VisualStudioDemangler::get_current_char( )
        {
            if ( offset >= mangled.size( ) )
            {
                general_error( AnsiString("Attempt to read past end of mangled string.") );
            }
            return mangled[ offset ];
        }

        [[noreturn]] void VisualStudioDemangler::bad_code( char c, const AnsiString& desc )
        {
            error = Format( "Unrecognized {} code '{}' at offset {}", desc, c, offset );
            throw Error( error );
        }

        [[noreturn]] void VisualStudioDemangler::bad_code( char c, const char* desc )
        {
            error = Format( "Unrecognized {} code '{}' at offset {}", desc, c, offset );
            throw Error( error );
        }

        [[noreturn]] void VisualStudioDemangler::general_error( const AnsiString& e )
        {
            error = e;
            throw Error( error );
        }

        [[noreturn]] void VisualStudioDemangler::general_error( const char* e )
        {
            error = e;
            throw Error( error );
        }

        void VisualStudioDemangler::progress( const AnsiString& msg )
        {
            if ( debug )
            {
                std::cerr << "Parsing " << msg << " at character '" << get_current_char( ) << "' at offset " << offset << std::endl;
            }
        }

        void VisualStudioDemangler::progress( const char* msg )
        {
            progress( AnsiString( msg ) );
        }

        void VisualStudioDemangler::print_stack( ReferenceStack const& stack, const AnsiString& msg )
        {
            std::cerr << "The full " << msg << " stack currently contains:" << std::endl;
            size_t p = 0;
            for ( auto& t : stack )
            {
                std::cerr << "  " << p << " : " << str( t ) << std::endl;
                p++;
            }
        }

        void VisualStudioDemangler::print_stack( ReferenceStack const& stack, const char* msg )
        {
            return print_stack( stack, AnsiString( msg ) );
        }

        void VisualStudioDemangler::stack_debug( ReferenceStack const& stack, size_t position, const AnsiString& msg )
        {
            AnsiString entry;

            if ( !debug ) return;

            if ( stack.size( ) >= position + 1 )
            {
                entry = str( stack.at( position ) );
            }
            else
            {
                entry = Format( "INVALID {}", position );
            }

            std::cerr << "Pushing " << msg << " position " << position << " in stack refers to " << entry << std::endl;
            print_stack( stack, msg );
        }

        void VisualStudioDemangler::stack_debug( ReferenceStack const& stack, size_t position, const char* msg )
        {
            stack_debug( stack, position, AnsiString( msg ) );
        }

        DemangledTypePtr& VisualStudioDemangler::process_calling_convention( DemangledTypePtr& t )
        {
            progress( "calling convention" );
            char c = get_current_char( );
            switch ( c )
            {
                case 'A': t->is_exported = false; t->calling_convention = "__cdecl"; break;
                case 'B': t->is_exported = true;  t->calling_convention = "__cdecl"; break;
                case 'C': t->is_exported = false; t->calling_convention = "__pascal"; break;
                case 'D': t->is_exported = true;  t->calling_convention = "__pascal"; break;
                case 'E': t->is_exported = false; t->calling_convention = "__thiscall"; break;
                case 'F': t->is_exported = true;  t->calling_convention = "__thiscall"; break;
                case 'G': t->is_exported = false; t->calling_convention = "__stdcall"; break;
                case 'H': t->is_exported = true;  t->calling_convention = "__stdcall"; break;
                case 'I': t->is_exported = false; t->calling_convention = "__fastcall"; break;
                case 'J': t->is_exported = true;  t->calling_convention = "__fastcall"; break;
                case 'K': t->is_exported = false; t->calling_convention = "__unknown"; break;
                case 'L': t->is_exported = true;  t->calling_convention = "__unknown"; break;
                case 'M': t->is_exported = false; t->calling_convention = "__clrcall"; break;
                default:
                    bad_code( c, AnsiString( "calling convention" ) );
            }

            advance_to_next_char( );
            return t;
        }

        DemangledTypePtr& VisualStudioDemangler::update_simple_type( DemangledTypePtr& t, Code code )
        {
            t->simple_code = code;
            advance_to_next_char( );
            return t;
        }

        DemangledTypePtr& VisualStudioDemangler::get_managed_properties( DemangledTypePtr& t, int& cli_array )
        {
            cli_array = 0;

            char c = get_current_char( );

            if ( c == '$' )
            {
                c = get_next_char( );
                switch ( c )
                {
                    case 'A':
                        t->is_gc = true;
                        break;
                    case 'B': // __pin  BUG!!! Unimplemented!
                        t->is_pin = true;
                        break;
                    case '0': case '1': case '2':
                    {
                        // C++/CLI array
                        auto xdigit = [ this ]( char d ) -> int {
                            if ( d >= '0' && d <= '9' )
                                return ( d - '0' );
                            else if ( d >= 'a' && d <= 'f' )
                                return ( d - 'a' );
                            else if ( d >= 'A' && d <= 'F' )
                                return ( d - 'A' );
                            else bad_code( d, AnsiString( "hex digit") ); };
                        int val = xdigit( c ) * 16;
                        c = get_next_char( );
                        val += xdigit( c );
                        cli_array = val ? val : -1;
                    }
                    break;
                    default:
                        bad_code( c, "managed C++ property" );
                }
                advance_to_next_char( );
            }
            return t;
        }

        DemangledTypePtr& VisualStudioDemangler::get_storage_class_modifiers( DemangledTypePtr& t )
        {
            char c = get_current_char( );

            // Type storage class modifiers.  These letters are currently non-overlapping with the
            // storage class and can occur zero or more times.  Technically it's probably invalid for
            // them to occur more than once each however.
            bool cont = true;
            while ( cont )
            {
                progress( "pointer storage class modifier" );
                switch ( c )
                {
                    case 'E':
                        t->ptr64++;             // <type> __ptr64
                        break;
                    case 'F':
                        t->unaligned = true;    // __unaligned <type>
                        break;
                    case 'G':
                        t->is_reference = true; // <type> &
                        break;
                    case 'H':
                        t->is_refref = true;    // <type> &&
                        break;
                    case 'I':
                        t->restrict = true;     // <type> __restrict
                        break;
                    default:
                        cont = false;
                }
                if ( cont )
                {
                    c = get_next_char( );
                }
            }

            return t;
        }

        // Pointer base codes.  Agner Fog's Table 13.
        DemangledTypePtr&
            VisualStudioDemangler::get_pointer_type( DemangledTypePtr& t )
        {
            advance_to_next_char( );
            get_storage_class_modifiers( t );
            int handling_cli_array;
            get_managed_properties( t, handling_cli_array );

            progress( "pointer storage class" );
            // Const and volatile for the thing being pointed to (or referenced).
            t->inner_type = std::make_shared<DemangledType>( );
            get_storage_class( t->inner_type );

            if ( t->inner_type->is_member && !t->inner_type->is_based )
            {
                get_fully_qualified_name( t );
            }

            // Hack (like undname).
            if ( t->inner_type->is_func )
            {
                progress( "function pointed to" );
                get_function( t->inner_type );
            }
            else
            {
                progress( "type pointed to" );
                t->inner_type = get_type( t->inner_type );
            }
            if ( debug )
            {
                std::cerr << "Inner type was: " << str( t->inner_type ) << std::endl;
            }

            if ( handling_cli_array )
            {
                auto at = std::make_shared<DemangledType>( );
                at->name.push_back( std::make_shared<DemangledType>( "array" ) );
                at->name.push_back( std::make_shared<DemangledType>( "cli" ) );
                at->template_parameters.push_back(
                    std::make_shared<DemangledTemplateParameter>( t->inner_type ) );
                if ( handling_cli_array > 1 )
                {
                    at->template_parameters.push_back(
                        std::make_shared<DemangledTemplateParameter>( handling_cli_array ) );
                }
                t->inner_type = at;
                t->is_gc = true;
            }

            return t;
        }

        DemangledTypePtr& VisualStudioDemangler::get_real_enum_type( DemangledTypePtr& t )
        {
            char c = get_current_char( );
            progress( "enum real type" );
            auto& rt = t->enum_real_type = std::make_shared<DemangledType>( );
            switch ( c )
            {
                case '0': update_simple_type( rt, Code::SByte ); break;
                case '1': update_simple_type( rt, Code::UNSIGNED_CHAR ); break;
                case '2': update_simple_type( rt, Code::SHORT ); break;
                case '3': update_simple_type( rt, Code::UNSIGNED_SHORT ); break;
                case '4': update_simple_type( rt, Code::INT ); break;
                case '5': update_simple_type( rt, Code::UNSIGNED_INT ); break;
                case '6': update_simple_type( rt, Code::LONG ); break;
                case '7': update_simple_type( rt, Code::UNSIGNED_LONG ); break;
                default:
                    bad_code( c, "enum real type" );
            }

            return t;
        }

        DemangledTypePtr VisualStudioDemangler::get_array_type( DemangledTypePtr& t )
        {
            t->is_array = true;
            auto num_dim = get_number( );
            for ( decltype( num_dim ) i = 0; i < num_dim; ++i )
            {
                t->dimensions.push_back( uint64_t( get_number( ) ) );
            }
            return get_type( t );
        }

        // Return a demangled type, for a global variables, a return code, or a function argument.
        // This function may require a optional argument saying whether we're in function args or not.

        // Presently, the push boolean indicates whether the conplex type should be pushed onto the
        // stack or not.  The default is true (push the value onto
        DemangledTypePtr VisualStudioDemangler::get_type( DemangledTypePtr t, bool push )
        {
            if ( !t )
            {
                t = std::make_shared<DemangledType>( );
            }

            char c = get_current_char( );
            progress( "type" );
            switch ( c )
            {
                case 'A': // X&
                    t->is_reference = true; get_pointer_type( t ); break;
                case 'B': // X& volatile
                    t->is_reference = true; t->is_volatile = true; get_pointer_type( t ); break;
                case 'C': return update_simple_type( t, Code::SByte );
                case 'D': return update_simple_type( t, Code::CHAR );
                case 'E': return update_simple_type( t, Code::UNSIGNED_CHAR );
                case 'F': return update_simple_type( t, Code::SHORT );
                case 'G': return update_simple_type( t, Code::UNSIGNED_SHORT );
                case 'H': return update_simple_type( t, Code::INT );
                case 'I': return update_simple_type( t, Code::UNSIGNED_INT );
                case 'J': return update_simple_type( t, Code::LONG );
                case 'K': return update_simple_type( t, Code::UNSIGNED_LONG );
                case 'M': return update_simple_type( t, Code::FLOAT );
                case 'N': return update_simple_type( t, Code::DOUBLE );
                case 'O': return update_simple_type( t, Code::LONG_DOUBLE );
                case 'P': // X*
                    t->is_pointer = true; get_pointer_type( t ); break;
                case 'Q': // X* const
                    t->is_pointer = true; t->is_const = true; get_pointer_type( t ); break;
                case 'R': // X* volatile
                    t->is_pointer = true; t->is_volatile = true; return get_pointer_type( t ); break;
                case 'S': // X* const volatile
                    t->is_pointer = true; t->is_const = true; t->is_volatile = true; get_pointer_type( t );
                    break;
                case 'T':
                    update_simple_type( t, Code::UNION );
                    get_fully_qualified_name( t );
                    break;
                case 'U':
                    update_simple_type( t, Code::STRUCT );
                    get_fully_qualified_name( t );
                    break;
                case 'V':
                    update_simple_type( t, Code::CLASS );
                    get_fully_qualified_name( t );
                    break;
                case 'W':
                    update_simple_type( t, Code::ENUM );
                    get_real_enum_type( t );
                    get_fully_qualified_name( t );
                    break;
                case 'X': return update_simple_type( t, Code::Void );
                case 'Y': // array
                    advance_to_next_char( );
                    get_array_type( t );
                    break;
                case 'Z': return update_simple_type( t, Code::ELLIPSIS );
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9':
                    // Consume the reference character...
                    advance_to_next_char( );
                    return resolve_reference( type_stack, c );
                case '_': // Extended simple types.
                    c = get_next_char( );
                    switch ( c )
                    {
                        case '$': bad_code( c, "_w64 prefix" );
                        case 'D': update_simple_type( t, Code::INT8 ); break;
                        case 'E': update_simple_type( t, Code::UINT8 ); break;
                        case 'F': update_simple_type( t, Code::INT16 ); break;
                        case 'G': update_simple_type( t, Code::UINT16 ); break;
                        case 'H': update_simple_type( t, Code::INT32 ); break;
                        case 'I': update_simple_type( t, Code::UINT32 ); break;
                        case 'J': update_simple_type( t, Code::INT64 ); break;
                        case 'K': update_simple_type( t, Code::UINT64 ); break;
                        case 'L': update_simple_type( t, Code::INT128 ); break;
                        case 'M': update_simple_type( t, Code::UINT128 ); break;
                        case 'N': update_simple_type( t, Code::Boolean ); break;
                        case 'O': bad_code( c, "unhandled array" );
                        case 'S': update_simple_type( t, Code::CHAR16 ); break;
                        case 'U': update_simple_type( t, Code::CHAR32 ); break;
                        case 'W': update_simple_type( t, Code::WCHAR ); break;
                        case 'X': bad_code( c, "coclass" );
                        case 'Y': bad_code( c, "cointerface" );
                        default:
                            bad_code( c, "extended '_' type" );
                    }
                    break;
                case '?': // Documented at wikiversity as "type modifier, template parameter"
                    advance_to_next_char( );
                    get_storage_class( t );
                    get_type( t );
                    break;
                case '$':
                    c = get_next_char( );
                    // A second '$' (two in a row)...
                    if ( c == '$' )
                    {
                        c = get_next_char( );
                        switch ( c )
                        {
                            case 'Q':
                                t->is_refref = true; get_pointer_type( t ); break;
                            case 'R':
                                t->is_volatile = true; t->is_refref = true; get_pointer_type( t ); break;
                            case 'A':
                                t->is_func = true; get_pointer_type( t ); break;
                            case 'B':
                                // Seems to be array type in template.  Next char should be 'Y'
                                advance_to_next_char( ); get_type( t ); break;
                            case 'C':
                                advance_to_next_char( ); get_storage_class( t ); get_type( t ); break;
                            case 'T':
                                advance_to_next_char( );
                                t->name.push_back( std::make_shared<DemangledType>( "nullptr_t" ) );
                                t->name.push_back( std::make_shared<DemangledType>( "std" ) );
                                break;
                            case 'V':
                            case 'Z':
                                // end of parameter pack.  Return null
                                advance_to_next_char( );
                                return DemangledTypePtr( );
                            default:
                                bad_code( c, "extended '$$' type" );
                        }
                    }
                    // All characters after a single '$' are template parameters.
                    else
                    {
                        bad_code( c, "type" );
                    }
                    break;
                default:
                    bad_code( c, "type" );
            }
            if ( push ) save_type( t );
            return t;
        }

        DemangledTypePtr& VisualStudioDemangler::add_special_name_code( DemangledTypePtr& t )
        {
            char c = get_current_char( );
            progress( "special name" );
            switch ( c )
            {
                case '0': t->add_name( )->is_ctor = true; break;
                case '1': t->add_name( )->is_dtor = true; break;
                case '2': t->add_name( Code::OP_NEW ); break;
                case '3': t->add_name( Code::OP_DELETE ); break;
                case '4': t->add_name( Code::OP_ASSIGN ); break;
                case '5': t->add_name( Code::OP_RSHIFT ); break;
                case '6': t->add_name( Code::OP_LSHIFT ); break;
                case '7': t->add_name( Code::OP_NOT ); break;
                case '8': t->add_name( Code::OP_EQUAL ); break;
                case '9': t->add_name( Code::OP_NOTEQUAL ); break;
                case 'A': t->add_name( Code::OP_INDEX ); break;
                case 'B': t->add_name( Code::OP_TYPE ); break;
                case 'C': t->add_name( Code::OP_INDIRECT ); break;
                case 'D': t->add_name( Code::OP_STAR ); break;
                case 'E': t->add_name( Code::OP_PLUSPLUS ); break;
                case 'F': t->add_name( Code::OP_MINUSMINUS ); break;
                case 'G': t->add_name( Code::OP_MINUS ); break;
                case 'H': t->add_name( Code::OP_PLUS ); break;
                case 'I': t->add_name( Code::OP_AMP ); break;
                case 'J': t->add_name( Code::OP_INDIRECT_METHOD ); break;
                case 'K': t->add_name( Code::OP_DIV ); break;
                case 'L': t->add_name( Code::OP_MOD ); break;
                case 'M': t->add_name( Code::OP_LESS ); break;
                case 'N': t->add_name( Code::OP_LESSEQ ); break;
                case 'O': t->add_name( Code::OP_GREATER ); break;
                case 'P': t->add_name( Code::OP_GREATEREQ ); break;
                case 'Q': t->add_name( Code::OP_COMMA ); break;
                case 'R': t->add_name( Code::OP_CALL ); break;
                case 'S': t->add_name( Code::OP_BNOT ); break;
                case 'T': t->add_name( Code::OP_BXOR ); break;
                case 'U': t->add_name( Code::OP_BOR ); break;
                case 'V': t->add_name( Code::OP_AND ); break;
                case 'W': t->add_name( Code::OP_OR ); break;
                case 'X': t->add_name( Code::OP_STAR_ASSIGN ); break;
                case 'Y': t->add_name( Code::OP_PLUS_ASSIGN ); break;
                case 'Z': t->add_name( Code::OP_MINUS_ASSIGN ); break;
                case '?':
                {
                    auto embedded = get_symbol( );
                    embedded->is_embedded = true;
                    if ( debug ) std::cerr << "The fully embedded type was:" << str( embedded ) << std::endl;
                    t->name.push_back( std::move( embedded ) );
                    return t->name.back( );
                }
                case '_':
                    c = get_next_char( );
                    switch ( c )
                    {
                        case '0': t->add_name( Code::OP_DIV_ASSIGN ); break;
                        case '1': t->add_name( Code::OP_MOD_ASSIGN ); break;
                        case '2': t->add_name( Code::OP_RSHIFT_ASSIGN ); break;
                        case '3': t->add_name( Code::OP_LSHIFT_ASSIGN ); break;
                        case '4': t->add_name( Code::OP_AMP_ASSIGN ); break;
                        case '5': t->add_name( Code::OP_BOR_ASSIGN ); break;
                        case '6': t->add_name( Code::OP_BXOR_ASSIGN ); break;
                        case '7': t->add_name( Code::VFTABLE ); break;
                        case '8': t->add_name( Code::VBTABLE ); break;
                        case '9': t->add_name( Code::VCALL ); break;
                        case 'A': t->add_name( Code::TYPEOF ); break;
                        case 'B': t->add_name( Code::LOCAL_STATIC_GUARD ); break;
                        case 'C': return get_string( t->add_name( ) );
                        case 'D': t->add_name( Code::VBASE_DTOR ); break;
                        case 'E': t->add_name( Code::VECTOR_DELETING_DTOR ); break;
                        case 'F': t->add_name( Code::DEFAULT_CTOR_CLOSURE ); break;
                        case 'G': t->add_name( Code::SCALAR_DELETING_DTOR ); break;
                        case 'H': t->add_name( Code::VECTOR_CTOR_ITER ); break;
                        case 'I': t->add_name( Code::VECTOR_DTOR_ITER ); break;
                        case 'J': t->add_name( Code::VECTOR_VBASE_CTOR_ITER ); break;
                        case 'K': t->add_name( Code::VIRTUAL_DISPLACEMENT_MAP ); break;
                        case 'L': t->add_name( Code::EH_VECTOR_CTOR_ITER ); break;
                        case 'M': t->add_name( Code::EH_VECTOR_DTOR_ITER ); break;
                        case 'N': t->add_name( Code::EH_VECTOR_VBASE_CTOR_ITER ); break;
                        case 'O': t->add_name( Code::COPY_CTOR_CLOSURE ); break;
                        case 'P': t->add_name( Code::UDT_RETURNING ); break;
                        case 'R': return add_rtti( t );
                        case 'S': t->add_name( Code::LOCAL_VFTABLE ); break;
                        case 'T': t->add_name( Code::LOCAL_VFTABLE_CTOR_CLOSURE ); break;
                        case 'U': t->add_name( Code::OP_NEW_ARRAY ); break;
                        case 'V': t->add_name( Code::OP_DELETE_ARRAY ); break;
                        case 'X': t->add_name( Code::PLACEMENT_DELETE_CLOSURE ); break;
                        case 'Y': t->add_name( Code::PLACEMENT_DELETE_ARRAY_CLOSURE ); break;
                        case '_':
                            c = get_next_char( );
                            switch ( c )
                            {
                                case 'A': t->add_name( Code::MANAGED_VECTOR_CTOR_ITER ); break;
                                case 'B': t->add_name( Code::MANAGED_VECTOR_DTOR_ITER ); break;
                                case 'C': t->add_name( Code::EH_VECTOR_COPY_CTOR_ITER ); break;
                                case 'D': t->add_name( Code::EH_VECTOR_VBASE_COPY_CTOR_ITER ); break;
                                case 'E': t->add_name( Code::DYNAMIC_INITIALIZER ); break;
                                case 'F': t->add_name( Code::DYNAMIC_ATEXIT_DTOR ); break;
                                case 'G': t->add_name( Code::VECTOR_COPY_CTOR_ITER ); break;
                                case 'H': t->add_name( Code::VECTOR_VBASE_COPY_CTOR_ITER ); break;
                                case 'I': t->add_name( Code::MANAGED_VECTOR_COPY_CTOR_ITER ); break;
                                case 'J': t->add_name( Code::LOCAL_STATIC_THREAD_GUARD ); break;
                                case 'K': t->add_name( Code::OP_DQUOTE ); break;
                                default:
                                    bad_code( c, "special name '__')" );
                            }
                            break;
                        default:
                            bad_code( c, "special name '_'" );
                    }
                    break;
                case '@':
                {
                    auto name = t->add_name( );
                    name->symbol_type = SymbolType::HexSymbol;
                    advance_to_next_char( );
                    name->simple_string = get_literal( );
                    return t->name.back( );
                }
                break;
                default:
                    bad_code( c, "special name" );
            }

            advance_to_next_char( );
            return t->name.back( );
        }

        DemangledTypePtr& VisualStudioDemangler::get_string( DemangledTypePtr& t )
        {
            char c = get_next_char( );
            if ( c != '@' )
            {
                bad_code( c, "string constant" );
            }
            c = get_next_char( );
            if ( c != '_' )
            {
                bad_code( c, "string constant" );
            }
            c = get_next_char( );
            bool multibyte = false;
            switch ( c )
            {
                case '0': break;
                case '1': multibyte = true; break;
                default:
                    bad_code( c, "string constant" );
            }
            advance_to_next_char( );
            auto real_len = get_number( );
            auto len = std::min( real_len, int64_t( multibyte ? 64 : 32 ) );
            get_number( );
            AnsiString result;
            for ( int64_t i = 0; i < len; ++i )
            {
                char v;
                c = get_current_char( );
                if ( c == '@' )
                {
                    break;
                }
                if ( c == '?' )
                {
                    c = get_next_char( );
                    if ( c == '$' )
                    {
                        // Hexadecimal byte
                        v = 0;
                        for ( int j = 0; j < 2; ++j )
                        {
                            c = get_next_char( );
                            if ( c < 'A' || c > 'P' )
                            {
                                bad_code( c, "character hex digit" );
                            }
                            v = v * 16 + ( c - 'A' );
                        }
                    }
                    else if ( c >= '0' && c <= '9' )
                    {
                        // Special encodings
                        static char const* special = ",/\\:. \v\n'-";
                        v = special[ c - '0' ];
                    }
                    else if ( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) )
                    {
                        v = c + 0x80;
                    }
                    else
                    {
                        bad_code( c, "string special char" );
                    }
                }
                else
                {
                    v = c;
                }
                result.push_back( v );
                advance_to_next_char( );
            }

            if ( multibyte )
            {
                WideString wide;
                for ( size_t i = 0; i < result.size( ); i += 2 )
                {
                    char16_t c16 = result[ i ] * 0x100 + result[ i + 1 ];
                    wide.push_back( c16 );
                }
                result = ToAnsiString( wide );
            }
            if ( !result.empty( ) && result.back( ) == 0 )
            {
                result.pop_back( );
            }

            t->symbol_type = SymbolType::String;
            t->inner_type = std::make_shared<DemangledType>( );
            t->inner_type->simple_code = multibyte ? Code::CHAR16 : Code::CHAR;
            t->simple_string = "`string'";
            t->n.reserve( 1 );
            t->n.push_back( multibyte ? ( real_len / 2 ) : real_len );
            t->is_pointer = true;
            t->add_name( std::move( result ) );
            return t;
        }

        // It's still a little unclear what this returns.   Maybe a custom RTTI object?
        DemangledTypePtr& VisualStudioDemangler::add_rtti( DemangledTypePtr& t )
        {
            // UNDNAME sets a flag to  prevent later processing of return values?

            // Character advancement is confusing and ugly here...  get_special_name_code() currently
            // expects us to leave a character to be advanced past. :-(

            char c = get_next_char( );
            switch ( c )
            {
                case '0':
                    advance_to_next_char( );
                    // Why there's a return type for RTTI descriptor is a little unclear to me...
                    t->retval = std::make_shared<DemangledType>( );
                    get_return_type( t->retval );
                    t->add_name( Code::RTTI_TYPE_DESC );
                    break;
                case '1':
                {
                    advance_to_next_char( );
                    auto n = t->add_name( Code::RTTI_BASE_CLASS_DESC );
                    n->n.reserve( 4 );
                    n->n.push_back( get_number( ) );
                    n->n.push_back( get_number( ) );
                    n->n.push_back( get_number( ) );
                    n->n.push_back( get_number( ) );
                }
                break;
                case '2':
                    advance_to_next_char( );
                    t->add_name( Code::RTTI_BASE_CLASS_ARRAY ); break;
                case '3':
                    advance_to_next_char( );
                    t->add_name( Code::RTTI_CLASS_HEIRARCHY_DESC ); break;
                case '4':
                    advance_to_next_char( );
                    t->add_name( Code::RTTI_COMPLETE_OBJ_LOCATOR ); break;
                default:
                    bad_code( c, "RTTI" );
            }
            return t->name.back( );
        }

        DemangledTypePtr&
            VisualStudioDemangler::update_storage_class( DemangledTypePtr& t, Distance distance,
                bool is_const, bool is_volatile,
                bool is_func, bool is_based, bool is_member )
        {
            t->distance = distance;
            t->is_const = is_const;
            t->is_volatile = is_volatile;
            t->is_func = is_func;
            t->is_member = is_member;

            // Unused currently...
            t->is_based = is_based;

            // Successfully consume this character code.
            advance_to_next_char( );
            return t;
        }

        // Storage class codes.  Agner Fog's Table 10.
        DemangledTypePtr& VisualStudioDemangler::get_storage_class( DemangledTypePtr& t )
        {
            char c = get_current_char( );
            switch ( c )
            {

                // Ordinary variables?
                //                                      distance        const  volat  func   based  member
                case 'A': return update_storage_class( t, Distance::Near, false, false, false, false, false );
                case 'B': return update_storage_class( t, Distance::Near, true, false, false, false, false );
                case 'C': return update_storage_class( t, Distance::Near, false, true, false, false, false );
                case 'D': return update_storage_class( t, Distance::Near, true, true, false, false, false );

                    // E & F are not valid on their own in this context.

                case 'G': return update_storage_class( t, Distance::Near, false, true, false, false, false );
                case 'H': return update_storage_class( t, Distance::Near, true, true, false, false, false );

                    // I is not valid on it's own in this context.

                case 'J': return update_storage_class( t, Distance::Near, true, false, false, false, false );
                case 'K': return update_storage_class( t, Distance::Near, false, true, false, false, false );
                case 'L': return update_storage_class( t, Distance::Near, true, true, false, false, false );

                    // __based() variables, distance presumed to be near.
                case 'M': return update_storage_class( t, Distance::Near, false, false, false, true, false );
                case 'N': return update_storage_class( t, Distance::Near, true, false, false, true, false );
                case 'O': return update_storage_class( t, Distance::Near, false, true, false, true, false );
                case 'P': return update_storage_class( t, Distance::Near, true, true, false, true, false );

                    // Ordinary members?, distance presumed to be near.
                case 'Q': return update_storage_class( t, Distance::Near, false, false, false, false, true );
                case 'R': return update_storage_class( t, Distance::Near, true, false, false, false, true );
                case 'S': return update_storage_class( t, Distance::Near, false, true, false, false, true );
                case 'T': return update_storage_class( t, Distance::Near, true, true, false, false, true );

                    // Ordinary members?, distance wildly guessed to be far to distinguish from Q,R,S,T.
                case 'U': return update_storage_class( t, Distance::Far, false, false, false, false, true );
                case 'V': return update_storage_class( t, Distance::Far, true, false, false, false, true );
                case 'W': return update_storage_class( t, Distance::Far, false, true, false, false, true );
                case 'X': return update_storage_class( t, Distance::Far, true, true, false, false, true );

                    // Ordinary members?, distance wildly guessed to be huge to distinguish from U,V,W,X.
                case 'Y': return update_storage_class( t, Distance::Far, false, false, false, false, true );
                case 'Z': return update_storage_class( t, Distance::Far, true, false, false, false, true );
                case '0': return update_storage_class( t, Distance::Far, false, true, false, false, true );
                case '1': return update_storage_class( t, Distance::Far, true, true, false, false, true );

                    // __based() members, distance presumed to be near
                case '2': return update_storage_class( t, Distance::Near, false, false, false, true, true );
                case '3': return update_storage_class( t, Distance::Near, true, false, false, true, true );
                case '4': return update_storage_class( t, Distance::Near, false, true, false, true, true );
                case '5': return update_storage_class( t, Distance::Near, true, true, false, true, true );

                    // Functions (no const/volatile), near/far arbitrary to create a distinction.
                case '6': return update_storage_class( t, Distance::Near, false, false, true, false, false );
                case '7': return update_storage_class( t, Distance::Far, false, false, true, false, false );
                case '8': return update_storage_class( t, Distance::Near, false, false, true, false, true );
                case '9': return update_storage_class( t, Distance::Far, false, false, true, false, true );

                    // Extended storage class modifiers.
                case '_':
                    c = get_next_char( );
                    switch ( c )
                    {
                        case 'A': return update_storage_class( t, Distance::Near, false, false, true, true, false );
                        case 'B': return update_storage_class( t, Distance::Far, false, false, true, true, false );
                        case 'C': return update_storage_class( t, Distance::Near, false, false, true, true, true );
                        case 'D': return update_storage_class( t, Distance::Far, false, false, true, true, true );
                        default:
                            bad_code( c, "extended storage class" );
                    }
                    break;
                default:
                    bad_code( c, "storage class" );
            }

            advance_to_next_char( );
            return t;
        }

        // It looks like these two should be combined, but I'm waiting for further evidence before
        // changing all of the code.
        DemangledTypePtr& VisualStudioDemangler::get_return_type( DemangledTypePtr& t )
        {
            char c = get_current_char( );

            // The return type of constructors and destructors are simply coded as an '@'.
            if ( c == '@' )
            {
                // There's nothing to actually do except skip the '@'?  Perhaps in a post-fixup step we
                // should create a return type that is the type of the class?
                advance_to_next_char( );
                return t;
            }

            progress( "return value storage class" );
            process_return_storage_class( t );
            progress( "return value type" );
            get_type( t );
            return t;
        }

        // Storage class codes for return values.  Agner Fog's Table 12.
        // A lot of overlap with tables 10 & 15, but apparently distinct...
        DemangledTypePtr& VisualStudioDemangler::process_return_storage_class( DemangledTypePtr& t )
        {
            char c = get_current_char( );

            // If there's no question mark, we're the default storage class?
            // There are special rules according
            if ( c != '?' )
            {
                t->is_const = false;
                t->is_volatile = false;
                return t;
            }
            c = get_next_char( );

            switch ( c )
            {
                case 'A':
                    t->is_const = false;
                    t->is_volatile = false;
                    break;
                case 'B':
                    t->is_const = true;
                    t->is_volatile = false;
                    break;
                case 'C':
                    t->is_const = false;
                    t->is_volatile = true;
                    break;
                case 'D':
                    t->is_const = true;
                    t->is_volatile = true;
                    break;
                default:
                    bad_code( c, "return storage class" );
            }

            advance_to_next_char( );
            return t;
        }

        DemangledTypePtr&
            VisualStudioDemangler::update_method( DemangledTypePtr& t, Scope scope,
                MethodProperty prop, Distance distance )
        {
            t->symbol_type = SymbolType::ClassMethod;
            t->is_func = true;
            t->is_member = true;
            t->scope = scope;
            t->method_property = prop;
            t->distance = distance;
            return t;
        }

        DemangledTypePtr&
            VisualStudioDemangler::update_member( DemangledTypePtr& t, Scope scope, MethodProperty prop )
        {
            t->is_func = true;
            t->is_member = true;
            t->symbol_type = SymbolType::StaticClassMember;
            t->scope = scope;
            t->method_property = prop;
            return t;
        }

        // Agner Fog's Table 14.
        // Could be three methods that read the same byte and return individual values.
        DemangledTypePtr& VisualStudioDemangler::get_symbol_type( DemangledTypePtr& t )
        {
            // This is the symbol type character code.
            progress( "symbol type" );
            char c = get_current_char( );
            // Pre-consume this character code, so we can just return -- BREAKS errors and reporting!
            advance_to_next_char( );
            switch ( c )
            {

                case '0': return update_member( t, Scope::Private, MethodProperty::Static );
                case '1': return update_member( t, Scope::Protected, MethodProperty::Static );
                case '2': return update_member( t, Scope::Public, MethodProperty::Static );

                case '3': // ?x@@3HA = int x
                case '4': // ?x@@4HA = int x
                    t->symbol_type = SymbolType::GlobalObject;
                    return t;

                case '5':
                    t->symbol_type = SymbolType::StaticGuard;
                    return t;

                    // Appears to be vtable entries.
                case '6':
                case '7':
                    t->symbol_type = SymbolType::VTable; return t;

                    // These always seem to be RTTI information
                case '8':
                case '9':
                    t->symbol_type = SymbolType::RTTI; return t;

                    // Codes A-X are for class methods.
                case 'A': return update_method( t, Scope::Private, MethodProperty::Ordinary, Distance::Near );
                case 'B': return update_method( t, Scope::Private, MethodProperty::Ordinary, Distance::Far );
                case 'C': return update_method( t, Scope::Private, MethodProperty::Static, Distance::Near );
                case 'D': return update_method( t, Scope::Private, MethodProperty::Static, Distance::Far );
                case 'E': return update_method( t, Scope::Private, MethodProperty::Virtual, Distance::Near );
                case 'F': return update_method( t, Scope::Private, MethodProperty::Virtual, Distance::Far );
                case 'G': return update_method( t, Scope::Private, MethodProperty::Thunk, Distance::Near );
                case 'H': return update_method( t, Scope::Private, MethodProperty::Thunk, Distance::Far );

                case 'I': return update_method( t, Scope::Protected, MethodProperty::Ordinary,
                    Distance::Near );
                case 'J': return update_method( t, Scope::Protected, MethodProperty::Ordinary, Distance::Far );
                case 'K': return update_method( t, Scope::Protected, MethodProperty::Static, Distance::Near );
                case 'L': return update_method( t, Scope::Protected, MethodProperty::Static, Distance::Far );
                case 'M': return update_method( t, Scope::Protected, MethodProperty::Virtual, Distance::Near );
                case 'N': return update_method( t, Scope::Protected, MethodProperty::Virtual, Distance::Far );
                case 'O': return update_method( t, Scope::Protected, MethodProperty::Thunk, Distance::Near );
                case 'P': return update_method( t, Scope::Protected, MethodProperty::Thunk, Distance::Far );

                case 'Q': return update_method( t, Scope::Public, MethodProperty::Ordinary, Distance::Near );
                case 'R': return update_method( t, Scope::Public, MethodProperty::Ordinary, Distance::Far );
                case 'S': return update_method( t, Scope::Public, MethodProperty::Static, Distance::Near );
                case 'T': return update_method( t, Scope::Public, MethodProperty::Static, Distance::Far );
                case 'U': return update_method( t, Scope::Public, MethodProperty::Virtual, Distance::Near );
                case 'V': return update_method( t, Scope::Public, MethodProperty::Virtual, Distance::Far );
                case 'W': return update_method( t, Scope::Public, MethodProperty::Thunk, Distance::Near );
                case 'X': return update_method( t, Scope::Public, MethodProperty::Thunk, Distance::Far );

                    // Codes Y & Z are for global (non-method) functions.
                case 'Y':
                    t->symbol_type = SymbolType::GlobalFunction; t->is_func = true;
                    t->distance = Distance::Near; return t;
                case 'Z':
                    t->symbol_type = SymbolType::GlobalFunction; t->is_func = true;
                    t->distance = Distance::Far; return t;

                case '$':
                    c = get_current_char( );
                    advance_to_next_char( );
                    switch ( c )
                    {
                        case '0': update_method( t, Scope::Private, MethodProperty::Thunk, Distance::Near ); break;
                        case '1': update_method( t, Scope::Private, MethodProperty::Thunk, Distance::Far ); break;
                        case '2': update_method( t, Scope::Protected, MethodProperty::Thunk, Distance::Near ); break;
                        case '3': update_method( t, Scope::Protected, MethodProperty::Thunk, Distance::Far ); break;
                        case '4': update_method( t, Scope::Public, MethodProperty::Thunk, Distance::Near ); break;
                        case '5': update_method( t, Scope::Public, MethodProperty::Thunk, Distance::Far ); break;
                        case 'B':
                            t->method_property = MethodProperty::Thunk;
                            t->symbol_type = SymbolType::MethodThunk;
                            return t;
                        case '$':
                            // Prefix codes
                            c = get_current_char( );
                            advance_to_next_char( );
                            switch ( c )
                            {
                                case 'J':
                                {
                                    t->extern_c = true;
                                    // Ignore the next <number> - 1 characters
                                    auto n = get_number( ) - 1;
                                    for ( int i = 0; i < n; ++i )
                                    {
                                        advance_to_next_char( );
                                    }
                                }
                                break;
                                case 'F':
                                case 'H':
                                    // Unknown.  No difference in undname output
                                    break;
                                default:
                                    bad_code( c, "symbol type prefix" );
                            }
                            return get_symbol_type( t );
                        default:
                            bad_code( c, "extended symbol type" );
                    }
                    t->symbol_type = SymbolType::VtorDisp;
                    return t;
                    break;
                default:
                    bad_code( c, "symbol type" );
            }
        }

        // Storage class codes for methods.  Agner Fog's Table 15.
        // Nearly identical to Table 12, but needs to update a function and lacks '?' introducer.
        DemangledTypePtr& VisualStudioDemangler::process_method_storage_class( DemangledTypePtr& t )
        {
            get_storage_class_modifiers( t );
            int handling_cli_array;
            get_managed_properties( t, handling_cli_array );
            if ( handling_cli_array )
            {
                general_error( "unexpected cli array" );
            }

            char c = get_current_char( );
            switch ( c )
            {
                case 'A':
                    t->is_const = false;
                    t->is_volatile = false;
                    break;
                case 'B':
                    t->is_const = true;
                    t->is_volatile = false;
                    break;
                case 'C':
                    t->is_const = false;
                    t->is_volatile = true;
                    break;
                case 'D':
                    t->is_const = true;
                    t->is_volatile = true;
                    break;
                default:
                    bad_code( c, "method storage class" );
            }

            advance_to_next_char( );
            return t;
        }

        void VisualStudioDemangler::get_symbol_start( )
        {
            char c = get_current_char( );
            // Each symbol should begin with a question mark.
            if ( c != '?' )
            {
                error = Format( "'{}' at position {}", c, offset );
                error = "Expected '?' code at start of symbol, instead found character " + error;
                throw Error( error );
            }
            progress( "new symbol" );
            advance_to_next_char( );
        }

        DemangledTypePtr VisualStudioDemangler::resolve_reference(
            ReferenceStack& stack, char poschar )
        {
            size_t stack_offset = poschar - '0';

            bool fake = false;
            if ( stack.size( ) >= stack_offset + 1 )
            {
                auto& reference = stack.at( stack_offset );
                if ( debug ) std::cerr << "Reference refers to " << str( reference ) << std::endl;

                // This is the "correct" thing to do.
                if ( !fake ) return reference;
            }

            // Even if our position was invalid kludge something up for debugging.
            return std::make_shared<DemangledType>( Format( "ref#{}", stack_offset ) );
        }

        DemangledTypePtr VisualStudioDemangler::add_templated_type( DemangledTypePtr& type )
        {
            // The current character was the '$' when this method was called.
            char c = get_next_char( );
            progress( "templated symbol" );

            // Whenever we start a new template, we start a new name stack.
            auto saved_name_stack = push_names( );

            DemangledTypePtr templated_type;

            // The name can be either a special name or a literal, but not a fully qualified name
            // because there's no '@' after the special name code.
            if ( c == '?' )
            {
                c = get_next_char( );
                if ( c == '$' )
                {
                    templated_type = add_templated_type( type->add_name( ) );
                    save_name( templated_type );
                }
                else
                {
                    templated_type = add_special_name_code( type );
                }
            }
            else
            {
                templated_type = type->add_name( get_literal( ) );
                save_name( templated_type );
            }

            // We also need a new type stack for the template parameters.
            auto saved_type_stack = push_types( );

            size_t params = 0;
            c = get_current_char( );
            while ( c != '@' )
            {
                DemangledTemplateParameterPtr parameter;
                if ( get_current_char( ) == '$' )
                {
                    c = get_next_char( );
                    switch ( c )
                    {
                        case '0':
                            advance_to_next_char( );
                            progress( "constant template parameter" );
                            parameter = std::make_shared<DemangledTemplateParameter>( get_number( ) );
                            break;
                        case '1':
                            advance_to_next_char( );
                            progress( "constant pointer template parameter" );
                            parameter = std::make_shared<DemangledTemplateParameter>( get_symbol( ) );
                            parameter->pointer = true;
                            break;
                        case 'H':
                            advance_to_next_char( );
                            progress( "constant function pointer template parameter" );
                            parameter = std::make_shared<DemangledTemplateParameter>( get_symbol( ) );
                            parameter->pointer = true;
                            parameter->type->n.reserve( 1 );
                            parameter->type->n.push_back( get_number( ) );
                            break;
                        case 'I':
                            advance_to_next_char( );
                            progress( "constant member pointer template parameter" );
                            parameter = std::make_shared<DemangledTemplateParameter>( get_symbol( ) );
                            parameter->pointer = true;
                            parameter->type->n.reserve( 2 );
                            parameter->type->n.push_back( get_number( ) );
                            parameter->type->n.push_back( get_number( ) );
                            break;
                        case 'S':
                            // Empty non-type parameter pack.  Treat similar to $$V
                            advance_to_next_char( );
                            progress( "empty non-type parameter pack" );
                            break;
                        case '$':
                        {
                            // We'll interpret as a $$ type, but there could be any number of $s first.  So skip
                            // past the last $ and then go back two
                            auto pos = mangled.find_first_not_of( '$', offset );
                            if ( pos == AnsiString::npos )
                            {
                                bad_code( c, "template argument" );
                            }
                            offset = pos - 2;
                            if ( auto t = get_type( ) )
                            {
                                parameter = std::make_shared<DemangledTemplateParameter>( std::move( t ) );
                            }
                        }
                        break;
                        default:
                            bad_code( c, "template argument" );
                    }
                }
                else
                {
                    parameter = std::make_shared<DemangledTemplateParameter>( get_type( ) );
                }

                templated_type->template_parameters.push_back( std::move( parameter ) );
                params++;
                c = get_current_char( );
            }

            progress( "end of template parameters" );
            if ( debug ) std::cerr << "Templated symbol was: " << str( templated_type ) << std::endl;

            // Advance past the '@' that marked the end of the template parameters.
            advance_to_next_char( );

            return templated_type;
        }


        DemangledTypePtr& VisualStudioDemangler::get_fully_qualified_name(
            DemangledTypePtr& t, bool push )
        {
            char c = get_current_char( );
            size_t argno = 0;
            while ( c != '@' )
            {
                // Are we the first argument?
                bool first = ( argno == 0 );
                //bool first = false;
                // Push all names except when we're the first, then use the push parameter.
                bool pushing = ( !first || push );

                if ( c == '?' )
                {
                    c = get_next_char( );
                    if ( c == '$' )
                    {
                        auto tt = add_templated_type( t );
                        if ( pushing ) save_name( tt );
                    }
                    else
                    {
                        // This feels wrong...  If it's the first term in the name it's a special name, but if
                        // it's not the first term it's a numbered namespace?  This seems like more evidence
                        // that the parsing of the first term is definitely a different routine than the
                        // namespace terms in a fully qualified name...   Perhaps some code cleanup is needed?
                        if ( first || get_current_char( ) == '?' )
                        {
                            auto tt = add_special_name_code( t );
                            if ( tt->symbol_type != t->symbol_type && !tt->is_embedded )
                            {
                                // Used for constant String symbols
                                return t = std::move( tt );
                            }
                        }
                        else
                        {
                            // Wow is this ugly.  But it looks like Microsoft really did it this way, so what
                            // else can we do?  A number that starts with 'A' would be a namespace number that
                            // has a leading zero digit, which is not required.  Thus it signals a strangely
                            // handled "anonymous namespace" with a discarded unqie identifier.
                            if ( get_current_char( ) == 'A' )
                            {
                                auto ns = get_anonymous_namespace( );
                                t->name.push_back( ns );
                                save_name( ns );
                            }
                            else
                            {
                                uint64_t number = get_number( );
                                AnsiString numbered_namespace = Format( "`{}'" , number );
                                if ( debug ) std::cerr << "Found numbered namespace: "
                                    << numbered_namespace << std::endl;
                                auto nns = std::make_shared<DemangledType>( numbered_namespace );
                                t->name.push_back( std::move( nns ) );
                            }
                        }
                    }
                }
                else if ( c >= '0' && c <= '9' )
                {
                    progress( "reference to symbol" );
                    t->name.push_back( resolve_reference( name_stack, c ) );
                    advance_to_next_char( );
                }
                else
                {
                    auto ns = std::make_shared<DemangledType>( get_literal( ) );
                    t->name.push_back( ns );
                    save_name( ns );
                }
                c = get_current_char( );
                argno++;
            }

            progress( "end of fully qualified name" );
            if ( debug ) std::cerr << "Qualified name was: " << str( t ) << std::endl;

            // Advance past the terminating '@' character.
            advance_to_next_char( );
            return t;
        }

        DemangledTypePtr VisualStudioDemangler::get_anonymous_namespace( )
        {

            progress( "anonymous namespace" );

            // This should be re-written to just call get_literal() instead, now that we know that it is
            // '@' terminated like a normal literal.

            char c = get_next_char( );
            size_t start_offset = offset;
            if ( c != '0' )
            {
                general_error( Format( "Expected '0' in anonymous namespace, found '{}'.", c ) );
            }
            c = get_next_char( );
            if ( c != 'x' )
            {
                general_error( Format( "Expected 'x' in anonymous namespace, found '{}'.", c ) );
            }

            size_t digits = 0;
            c = get_next_char( );
            progress( "anonymous namespace digits" );
            while ( c != '@' )
            {
                if ( ( c >= 'a' && c <= 'z' ) || ( c >= '0' && c <= '9' ) )
                {
                    // Allowed
                }
                else
                {
                    general_error( Format( "Disallowed character '{}' in anonymous namespace digits.", c ) );
                }
                c = get_next_char( );
                digits++;
            }

            // Now build the return string from the bytes we consumed.
            AnsiString literal = mangled.substr( start_offset, offset - start_offset );
            if ( debug ) std::cerr << "Anonymous namespace ID was: " << literal << std::endl;

            // Advance past the '@' that terminated the literal.
            advance_to_next_char( );

            auto ans = std::make_shared<DemangledType>( literal );
            ans->is_anonymous = true;
            return ans;
        }

        AnsiString VisualStudioDemangler::get_literal( )
        {
            AnsiString literal;

            size_t start_offset = offset;
            progress( "literal" );

            char c = get_current_char( );
            while ( c != '@' )
            {
                switch ( c )
                {
                    // misc punctuation
                    case '_': case '$':
                    case '<': case '>':
                    case '-': case '.':
                        break;
                    default:
                        if ( !( ( c >= 'A' && c <= 'Z' ) || // uppercase letters
                            ( c >= 'a' && c <= 'z' ) || // lowercase letters
                            ( c >= '0' && c <= '9' ) ) ) // digits
                        {
                            general_error( Format( "Disallowed character '{}' in literal string.", c ) );
                        }
                }
                c = get_next_char( );
            }

            // Now build the return string from the bytes we consumed.
            literal = mangled.substr( start_offset, offset - start_offset );

            if ( debug )
            {
                std::cerr << "Extracted literal from " << start_offset << " to " << offset
                    << " (len=" << ( offset - start_offset )
                    << ") resulting in string: " << literal << std::endl;
            }

            // Advance past the '@' that terminated the literal.
            advance_to_next_char( );
            // We should also add the literal to the "stack".
            return literal;
        }

        int64_t VisualStudioDemangler::get_number( )
        {
            // Is the number signed?
            bool negative = false;
            int64_t num = 0;

            char c = get_current_char( );
            progress( "number" );

            // If the string starts with '?' then it's negative.
            if ( c == '?' )
            {
                negative = true;
                c = get_next_char( );
            }

            // Numbers between 1 and 10 expressed as 0-9.
            if ( c >= '0' && c <= '9' )
            {
                advance_to_next_char( );
                num = ( c - '0' ) + 1;
                if ( negative ) return -num;
                return num;
            }

            // The wikiversity article claims that '@' and '?@' both represent zero, but I've not found
            // that to be true (yet?).  My experience matches Agner's that it's encoded as 'A@' (or
            // perhaps '?A@').

            // All other codings are variations of hexadecimal values encoded as A-P.
            // Count the digits found to prevent integer overflows.
            size_t digits_found = 0;

            while ( c >= 'A' && c <= 'P' )
            {
                num *= 16;
                num += ( c - 'A' );
                digits_found++;
                c = get_next_char( );
            }

            if ( c != '@' )
            {
                general_error( "Numbers must be terminated with an '@' character. " );
            }
            progress( "end of number" );
            advance_to_next_char( );

            if ( digits_found <= 0 )
            {
                general_error( "There were too few hex digits endecoded in the number." );
            }

            if ( digits_found > 16 )
            {
                general_error( "There were too many hex digits encoded in the number." );
            }

            if ( negative ) return -num;
            return num;
        }

        DemangledTypePtr& VisualStudioDemangler::get_function( DemangledTypePtr& t )
        {
            // Storage class for methods
            if ( t->symbol_type == SymbolType::Unspecified && t->is_func && t->is_member )
            {
                auto tmp = std::make_shared<DemangledType>( );
                get_storage_class_modifiers( tmp );
                get_storage_class( tmp );
                t->is_const = tmp->is_const;
                t->is_volatile = tmp->is_volatile;
                t->ptr64 += tmp->ptr64;
                t->unaligned = tmp->unaligned;
                t->restrict = tmp->restrict;
            }
            // And then the remaining codes are the same for functions and methods.
            process_calling_convention( t );
            // Return code.  It's annoying that the modifiers come first and require us to allocate it.
            t->retval = std::make_shared<DemangledType>( );
            get_return_type( t->retval );
            if ( debug ) std::cerr << "Return value was: " << str( t->retval ) << std::endl;


            // Whenever we start a nex set of function arguments, we start a new type stack?
            //auto saved_type_stack = push_types();

            // Function arguments.
            size_t argno = 0;
            progress( "start of function arguments" );
            while ( true )
            {
                // Must be at least one argument, but after that '@' marks the end.
                if ( argno > 0 && get_current_char( ) == '@' )
                {
                    progress( "end of args" );
                    advance_to_next_char( );
                    break;
                }
                progress( "function argument" );
                auto arg = get_type( true );
                t->args.push_back( arg );
                if ( debug ) std::cerr << "Arg #" << argno << " was: " << str( arg ) << std::endl;
                // If the first parameter is void, it's the only parameter.
                argno++;
                if ( argno == 1 && arg->simple_code == Code::Void ) break;
                // If the most recent parameter is '...', it's the last parameter.
                if ( arg->simple_code == Code::ELLIPSIS ) break;
            }

            progress( "end of function arguments" );

            // I'm confused about how certain this 'Z' is...
            if ( get_current_char( ) == 'Z' )
            {
                advance_to_next_char( );
            }

            //if (get_current_char() != 'Z') {
            //  general_error("Expected 'Z' to terminate function.");
            //}
            return t;
        }

        DemangledTypePtr VisualStudioDemangler::get_symbol( )
        {
            get_symbol_start( );

            auto t = std::make_shared<DemangledType>( );
            get_fully_qualified_name( t, false );
            if ( t->symbol_type == SymbolType::Unspecified )
            {
                get_symbol_type( t );
            }

            switch ( t->symbol_type )
            {
                case SymbolType::VTable:
                {
                    t->instance_name = t->name;
                    t->name.clear( );
                    process_method_storage_class( t );
                    // The interface name is optional.
                    while ( get_current_char( ) != '@' )
                    {
                        auto n = std::make_shared<DemangledType>( );
                        t->com_interface.push_back( get_fully_qualified_name( n, false ) );
                    }
                }
                return t;
                case SymbolType::String:
                case SymbolType::RTTI:
                case SymbolType::HexSymbol:
                    return t;
                case SymbolType::GlobalObject:
                case SymbolType::StaticClassMember:
                    // This is backwards.  We should have read the initial name into a special place, and then
                    // had all other places use the default place...
                    t->instance_name = std::move( t->name );
                    t->name.clear( );
                    get_type( t ); // Table 9
                    get_storage_class_modifiers( t );
                    get_storage_class( t ); // Table 10
                    return t;
                case SymbolType::VtorDisp:
                    // Get the displacement, then treat as method
                    t->n.reserve( 2 );
                    t->n.push_back( get_number( ) );
                    // Fall through
                case SymbolType::ClassMethod:
                    if ( t->method_property == MethodProperty::Thunk )
                    {
                        // get the thunk offset
                        t->n.resize( 1 );
                        t->n.push_back( get_number( ) );
                    }
                    // There's no storage class code for static class methods.
                    if ( t->method_property != MethodProperty::Static )
                    {
                        process_method_storage_class( t ); // Table 15
                    }
                    // Fall through
                case SymbolType::GlobalFunction:
                    return get_function( t );
                case SymbolType::StaticGuard:
                    t->n.reserve( 1 );
                    t->n.push_back( get_number( ) );
                    return t;
                case SymbolType::MethodThunk:
                    t->n.reserve( 1 );
                    t->n.push_back( get_number( ) );
                    switch ( char c = get_current_char( ) )
                    {
                        case 'A': break; // Only known type: flat
                        default: bad_code( c, "method thunk type" );
                    }
                    advance_to_next_char( );
                    process_calling_convention( t );
                    return t;
                default:
                    general_error( "Unrecognized symbol type." );
            }
        }


        // Not part of the constructor because it throws.
        DemangledTypePtr VisualStudioDemangler::analyze( )
        {

            char c = get_current_char( );
            if ( c == '_' )
            {
                general_error( "Mangled names beginning with '_' are currently not supported." );
                throw Error( error );
            }
            else if ( c == '.' )
            {
                advance_to_next_char( );
                // Why there's a return type for RTTI descriptor is a little unclear to me...
                auto t = std::make_shared<DemangledType>( );
                get_return_type( t );
                return t;
            }
            else
            {
                return get_symbol( );
            }
        }

    } // namespace detail

    namespace detail
    {

        constexpr bool SPACE_MUNGING = true;

        class Converter
        {

            template <typename T>
            struct Raw
            {
                T val;
            };

            template <typename T>
            static Raw<T> raw( T val )
            {
                return Raw<T>{val};
            }

            struct ConvStream
            {
                std::ostream& stream;
                TextAttributes const& attr;

                ConvStream( std::ostream& s, TextAttributes const& a ) : stream( s ), attr( a ) {}

                template <typename T>
                ConvStream& operator<<( Raw<T>&& x )
                {
                    stream << x.val;
                    last = '\0';
                    return *this;
                }

                template <typename T>
                ConvStream& operator<<( T&& x )
                {
                    std::ostringstream os;
                    os << std::forward<T>( x );
                    ( *this ) << os.str( );
                    return *this;
                }

                ConvStream& operator<<( AnsiString&& x )
                {
                    ( *this ) << const_cast< AnsiString const& >( x );
                    return *this;
                }

                ConvStream& operator<<( std::string&& x )
                {
                    ( *this ) << const_cast< std::string const& >( x );
                    return *this;
                }

                static bool is_symbol_char( char c )
                {
                    return c == '_' || std::isalnum( c );
                }

                ConvStream& operator<<( AnsiString const& s )
                {
                    if ( SPACE_MUNGING && !s.empty( ) && is_symbol_char( last ) && is_symbol_char( s.front( ) ) )
                    {
                        // Ensure a space between symbols
                        stream << ' ' << s;
                    }
                    else if ( SPACE_MUNGING && last == ' ' && !s.empty( ) && s.front( ) == ' ' )
                    {
                        // Don't allow double-spaces
                        stream << s.substr( 1 );
                    }
                    else
                    {
                        stream << s;
                    }
                    if ( !s.empty( ) )
                    {
                        last = s.back( );
                    }
                    fixup( );
                    return *this;
                }

                ConvStream& operator<<( std::string const& s )
                {
                    if ( SPACE_MUNGING && !s.empty( ) && is_symbol_char( last ) && is_symbol_char( s.front( ) ) )
                    {
                        // Ensure a space between symbols
                        stream << ' ' << s;
                    }
                    else if ( SPACE_MUNGING && last == ' ' && !s.empty( ) && s.front( ) == ' ' )
                    {
                        // Don't allow double-spaces
                        stream << s.substr( 1 );
                    }
                    else
                    {
                        stream << s;
                    }
                    if ( !s.empty( ) )
                    {
                        last = s.back( );
                    }
                    fixup( );
                    return *this;
                }


                ConvStream& operator<<( char const* s )
                {
                    return ( *this ) << AnsiString( s );
                }

                ConvStream& operator<<( char c )
                {
                    if ( SPACE_MUNGING && c == ' ' && c == last )
                    {
                        // Don't allow double-spaces
                        return *this;
                    }
                    if ( ( c == '<' || c == '>' ) && c == last
                        && attr[ TextAttribute::SPACE_BETWEEN_TEMPLATE_BRACKETS ] )
                    {
                        ( *this ) << ' ';
                    }
                    stream << c;
                    last = c;
                    fixup( );
                    return *this;
                }

                void fixup( )
                {
                    if ( last == ',' && attr[ TextAttribute::SPACE_AFTER_COMMA ] )
                    {
                        ( *this ) << ' ';
                        last = ' ';
                    }
                }

                char last = ' ';
            };

            ConvStream stream;
            DemangledType const& t;
            bool do_cconv = true;
            bool in_op_type = false;

            enum cv_context_t { BEFORE, AFTER };

        public:
            Converter( TextAttributes const& a, std::ostream& s, DemangledType const& dt )
                : stream( s, a ), t( dt )
            {
            }
            void operator()( );

            void class_name( );
            void method_name( );
            void method_signature( );

        private:
            Converter sub( DemangledType const& dt )
            {
                return Converter( stream.attr, stream.stream, dt );
            }
            void do_name( DemangledType const& n );
            void do_name( FullyQualifiedName const& name );
            void do_name( FullyQualifiedName::const_reverse_iterator b,
                FullyQualifiedName::const_reverse_iterator e,
                bool only_last = false );
            void do_template_params( DemangledTemplate const& tmpl );
            void do_template_param( DemangledTemplateParameter const& param );
            void do_args( FunctionArgs const& args );
            void do_type( DemangledType const& type, std::function<void( )> name = nullptr );
            void do_pointer( DemangledType const& ptr, std::function<void( )> name = nullptr );
            void do_function( DemangledType const& fn, std::function<void( )> name = nullptr );
            void do_storage_properties( DemangledType const& type, cv_context_t ctx );
            void do_method_properties( DemangledType const& m );
            void output_quoted_string( AnsiString const& s );

            bool template_parameters_ = true;
            DemangledType const* retval_ = nullptr;

            template <typename R, typename T>
            struct tset_impl
            {
                tset_impl( R& lc, T&& val ) : loc( lc ), v( lc )
                {
                    loc = std::forward<T>( val );
                }
                ~tset_impl( )
                {
                    loc = std::move( v );
                }
            private:
                R& loc;
                R v;
            };
            template <typename R, typename T>
            static tset_impl<R, T> tset( R& lc, T&& val )
            {
                return tset_impl<R, T>( lc, std::forward<T>( val ) );
            }
        };

        template <typename Stream>
        Stream& operator<<( Stream& stream, Scope scope )
        {
            switch ( scope )
            {
                case Scope::Unspecified: break;
                case Scope::Private: stream << "private: "; break;
                case Scope::Protected: stream << "protected: "; break;
                case Scope::Public: stream << "public: "; break;
            }
            return stream;
        }

        template <typename Stream>
        Stream& operator<<( Stream& stream, Distance distance )
        {
            switch ( distance )
            {
                case Distance::Unspecified: break;
                case Distance::Near: stream << "near "; break;
                case Distance::Far: stream << "far "; break;
                case Distance::Huge: stream << "huge "; break;
            }
            return stream;
        }

        void Converter::output_quoted_string( AnsiString const& s )
        {
            static AnsiString special_chars( "\"\\\a\b\f\n\r\t\v\0", 10 );
            static AnsiString names( "\"\\abfnrtv0", 10 );
            stream << '\"';
            for ( auto c : s )
            {
                auto pos = special_chars.find_first_of( c );
                if ( pos == AnsiString::npos )
                {
                    stream << raw( c );
                }
                else
                {
                    stream << raw( '\\' ) << raw( names[ pos ] );
                }
            }
            stream << '\"';
        }

        void Converter::do_method_properties( DemangledType const& m )
        {
            if ( stream.attr[ TextAttribute::OUTPUT_EXTERN ] && m.extern_c ) stream << "extern \"C\"";
            if ( stream.attr[ TextAttribute::OUTPUT_THUNKS ]
                && m.method_property == MethodProperty::Thunk )
            {
                stream << "[thunk]: ";
            }
            stream.operator<<( m.scope ); // written this way due to operator lookup ambiguity
            if ( m.method_property == MethodProperty::Static ) stream << "static ";
            if ( m.method_property == MethodProperty::Virtual
                // Thunks are virtual
                || ( m.method_property == MethodProperty::Thunk &&
                    // Except for vcall?
                    ( !m.name.empty( ) && m.name.front( )->simple_code != Code::VCALL ) ) )
            {
                stream << "virtual ";
            }
        }

        void Converter::operator()( )
        {
            switch ( t.symbol_type )
            {
                case SymbolType::ClassMethod:
                case SymbolType::GlobalFunction:
                case SymbolType::VtorDisp:
                    // function-like
                    do_type( t, [ this ] { do_name( t ); } );
                    break;
                case SymbolType::RTTI:
                    // RTTI
                    if ( t.retval )
                    {
                        do_type( *t.retval );
                        stream << ' ';
                    }
                    do_name( t );
                    break;
                case SymbolType::StaticClassMember:
                case SymbolType::GlobalObject:
                    // static objects
                    do_type( t, [ this ] { stream << ' '; do_name( t.instance_name ); } );
                    break;
                case SymbolType::MethodThunk:
                    do_method_properties( t );
                    stream << t.calling_convention << ' ';
                    do_name( t );
                    stream << '{' << t.n[ 0 ] << ",{flat}}'";
                    if ( stream.attr[ TextAttribute::BROKEN_UNDNAME ] )
                    {
                        // undname.exe ouputs an extra brace and quote
                        stream << " }'";
                    }
                    break;
                case SymbolType::VTable:
                    // vtables
                    do_storage_properties( t, AFTER );
                    do_name( t.instance_name );
                    if ( !t.com_interface.empty( ) )
                    {
                        stream << "{for ";
                        auto i = t.com_interface.begin( );
                        auto e = t.com_interface.end( );
                        while ( i != e )
                        {
                            stream << '`';
                            do_name( ( *i++ )->name );
                            stream << '\'';
                            if ( i != e )
                            {
                                stream << "s ";
                            }
                        }
                        stream << '}';
                    }
                    break;
                case SymbolType::StaticGuard:
                    // Static variable guards
                    do_name( t.name );
                    stream << '{' << t.n[ 0 ] << '}';
                    if ( stream.attr[ TextAttribute::BROKEN_UNDNAME ] )
                    {
                        // undname.exe ouputs an extra quote
                        stream << '\'';
                    }
                    break;
                case SymbolType::String:
                    // Constant string
                    if ( !stream.attr[ TextAttribute::VERBOSE_CONSTANT_STRING ] )
                    {
                        stream << "`string'";
                    }
                    else
                    {
                        do_type( *t.inner_type );
                        stream << '[' << t.n[ 0 ] << "] = ";
                        output_quoted_string( t.name[ 0 ]->simple_string );
                        if ( t.n[ 0 ] > 32 )
                        {
                            stream << "...";
                        }
                    }
                    break;
                case SymbolType::HexSymbol:
                    // Simple hex numbers
                    stream << t.simple_string;
                    break;
                case SymbolType::Unspecified:
                    // Guess based on contents
                    if ( t.instance_name.empty( ) )
                    {
                        do_type( t );
                    }
                    else
                    {
                        do_type( t, [ this ] { stream << ' '; do_name( t.instance_name ); } );
                    }
                    break;
            }
        }

        void Converter::do_name(
            FullyQualifiedName const& name )
        {
            do_name( name.rbegin( ), name.rend( ) );
        }

        void Converter::do_name(
            FullyQualifiedName::const_reverse_iterator b,
            FullyQualifiedName::const_reverse_iterator e,
            bool only_last )
        {
            // Iterate over the name fragments
            for ( auto i = only_last ? std::prev( e ) : b; i != e; ++i )
            {
                if ( !only_last && i != b )
                {
                    stream << "::";
                }
                auto& frag = *i;
                auto next = std::next( i );
                if ( next != e && ( *next )->simple_code == Code::DYNAMIC_ATEXIT_DTOR )
                {
                    // Special case for DYNAMIC_ATEXIT_DTOR
                    stream << "`dynamic atexit destructor for '";
                    do_name( i, next );
                    stream << "''";
                    i = next;
                }
                else if ( frag->is_embedded )
                {
                    // Embedded symbols get `' around them
                    stream << '`';
                    sub( *frag )( );
                    stream << '\'';
                }
                else if ( frag->is_ctor || frag->is_dtor )
                {
                    // ctors and dtors need to get their name from the class name,
                    // which should be the previous name
                    if ( frag->is_dtor )
                    {
                        stream << '~';
                    }
                    if ( i == b )
                    {
                        stream << "{ERRNOCLASS}";
                    }
                    else
                    {
                        auto save = tset( template_parameters_,
                            stream.attr[ TextAttribute::CDTOR_CLASS_TEMPLATE_PARAMETERS ] );
                        do_name( std::prev( i ), i );
                    }
                }
                else if ( frag->simple_code == Code::OP_TYPE )
                {
                    // Where do we place template parameters in an operator type construct?  Microsoft does
                    // it one way, the rest of the world does it another.
                    stream << "operator";
                    if ( stream.attr[ TextAttribute::USER_DEFINED_CONVERSION_TEMPLATE_BEFORE_TYPE ] )
                    {
                        do_template_params( frag->template_parameters );
                    }
                    stream << ' ';
                    if ( retval_ )
                    {
                        auto save = tset( in_op_type, true );
                        do_type( *retval_ );
                    }
                    else
                    {
                        stream << "{UNKNOWN_TYPE}";
                    }
                    if ( stream.attr[ TextAttribute::USER_DEFINED_CONVERSION_TEMPLATE_BEFORE_TYPE ] )
                    {
                        continue;
                    }
                }
                else
                {
                    // Normal case
                    do_name( *frag );
                }
                do_template_params( frag->template_parameters );
            }
        }


        void Converter::do_name(
            DemangledType const& name )
        {
            auto stype = [ this, &name ]( char const* s ) {
                if ( stream.attr[ TextAttribute::MS_SIMPLE_TYPES ] )
                {
                    stream << s;
                }
                else
                {
                    stream << "std::" << code_string( name.simple_code );
                }
            };

            switch ( name.simple_code )
            {
                case Code::Undefined:
                    if ( name.name.empty( ) )
                    {
                        if ( name.is_anonymous )
                        {
                            stream << "`anonymous namespace";
                            if ( stream.attr[ TextAttribute::OUTPUT_ANONYMOUS_NUMBERS ] )
                            {
                                stream << ' ' << name.simple_string;
                            }
                            stream << '\'';
                        }
                        else
                        {
                            stream << name.simple_string;
                        }
                    }
                    else
                    {
                        do_name( name.name );
                    }
                    break;

                case Code::CLASS: case Code::STRUCT: case Code::UNION: case Code::ENUM:
                    if ( !stream.attr[ TextAttribute::DISABLE_PREFIXES ] )
                    {
                        stream << static_cast<Int32>(name.simple_code) << ' ';
                    }
                    do_name( name.name );
                    break;

                case Code::INT8:    stype( "__int8" ); break;
                case Code::INT16:   stype( "__int16" ); break;
                case Code::INT32:   stype( "__int32" ); break;
                case Code::INT64:   stype( "__int64" ); break;
                case Code::UINT8:   stype( "unsigned __int8" ); break;
                case Code::UINT16:  stype( "unsigned __int16" ); break;
                case Code::UINT32:  stype( "unsigned __int32" ); break;
                case Code::UINT64:  stype( "unsigned __int64" ); break;

                case Code::OP_TYPE:
                    if ( retval_ )
                    {
                        stream << "operator ";
                        do_type( *retval_ );
                    }
                    else
                    {
                        stream << static_cast< Int32 >( name.simple_code );
                    }
                    break;

                case Code::RTTI_BASE_CLASS_DESC:
                    stream << "`RTTI Base Class Descriptor at ("
                        << name.n[ 0 ] << "," << name.n[ 1 ] << ","
                        << name.n[ 2 ] << "," << name.n[ 3 ] << ")'";
                    break;

                default:
                    stream << static_cast< Int32 >( name.simple_code );
            }
        }

        void Converter::do_template_param(
            DemangledTemplateParameter const& p )
        {
            if ( !p.type )
            {
                stream << p.constant_value;
            }
            else if ( p.pointer )
            {
                if ( p.type->is_func && p.type->is_member && !p.type->n.empty( ) )
                {
                    stream << '{';
                    sub( *p.type )( );
                    for ( auto v : p.type->n )
                    {
                        stream << ',' << v;
                    }
                    stream << '}';
                }
                else
                {
                    stream << '&';
                    sub( *p.type )( );
                }
            }
            else
            {
                do_type( *p.type );
            }
        }

        void Converter::do_template_params(
            DemangledTemplate const& tmpl )
        {
            if ( template_parameters_ && !tmpl.empty( ) )
            {
                stream << '<';
                bool first = true;
                for ( auto& tp : tmpl )
                {
                    if ( tp )
                    {
                        if ( first )
                        {
                            first = false;
                        }
                        else
                        {
                            stream << ',';
                        }
                        do_template_param( *tp );
                    }
                }
                stream << '>';
            }
        }

        void Converter::do_args(
            FunctionArgs const& args )
        {
            stream << '(';
            auto b = std::begin( args );
            auto e = std::end( args );
            for ( auto i = b; i != e; ++i )
            {
                if ( i != b )
                {
                    stream << ',';
                }
                do_type( **i );
            }
            stream << ')';
        }

        void Converter::do_pointer(
            DemangledType const& type,
            std::function<void( )> name )
        {
            auto iname = [ this, &name, &type ]( ) {
                auto& inner = *type.inner_type;
                bool parens = inner.is_func || inner.is_array;
                stream << ( parens ? '(' : ' ' );
                if ( inner.is_func )
                {
                    stream << inner.calling_convention << ' ';
                }
                if ( inner.is_member && !type.name.empty( ) )
                {
                    // Method or member pointer
                    do_name( type );
                    stream << "::";
                }
                do_storage_properties( type, BEFORE );
                if ( type.ptr64 > 1 )
                {
                    // Gross hack to deal with the fact the the symbol can be __ptr64 as well as the type
                    stream << " __ptr64";
                }
                if ( name ) name( );
                if ( parens ) stream << ')';
            };
            if ( type.inner_type->is_func )
            {
                auto save = tset( do_cconv, false );
                do_type( *type.inner_type, iname );
            }
            else
            {
                do_type( *type.inner_type, iname );
            }
        }

        void Converter::do_type(
            DemangledType const& type,
            std::function<void( )> name )
        {
            do_method_properties( type );
            if ( type.distance != Distance::Near || stream.attr[ TextAttribute::OUTPUT_NEAR ] )
            {
                stream.operator<<( type.distance ); // written this way due to operator lookup ambiguity
            }
            auto pname = name;
            if ( type.is_array )
            {
                auto aname = [ this, &type, name ]( ) {
                    if ( name ) name( );
                    for ( auto dim : type.dimensions )
                    {
                        stream << '[' << dim << ']';
                    }
                };
                pname = aname;
            }
            if ( type.is_func )
            {
                do_function( type.inner_type ? *type.inner_type : type, pname );
                return;
            }
            if ( type.is_pointer || type.is_reference || type.is_refref )
            {
                do_pointer( type, pname );
                return;
            }
            do_name( type );
            do_storage_properties( type, BEFORE );
            if ( pname )
            {
                pname( );
            }
        }

        void Converter::do_function(
            DemangledType const& fn,
            std::function<void( )> name )
        {
            auto cconv = do_cconv;
            auto fname = [ this, &fn, name, cconv ]( ) {
                {
                    stream << ' ';
                    if ( fn.symbol_type != SymbolType::Unspecified || cconv )
                    {
                        stream << fn.calling_convention << ' ';
                    }
                    if ( name ) name( );
                    if ( fn.symbol_type == SymbolType::VtorDisp )
                    {
                        stream << "`vtordisp{" << fn.n[ 0 ] << ',' << fn.n[ 1 ] << "}' ";
                    }
                    else if ( fn.method_property == MethodProperty::Thunk && fn.n.size( ) >= 2 )
                    {
                        stream << "`adjustor{" << fn.n[ 1 ] << "}' ";
                    }
                    do_args( fn.args );
                    do_storage_properties( fn, AFTER );
                }
            };
            auto rv = fn.retval;
            if ( !rv )
            {
                rv.reset( new DemangledType( "void" ) );
            }
            auto save = tset( retval_, rv.get( ) );
            auto save2 = tset( do_cconv, true );
            if ( !fn.name.empty( ) && fn.name.front( )->simple_code == Code::OP_TYPE )
            {
                // operator <type>
                fname( );
            }
            else
            {
                do_type( *retval_, fname );
            }
        }

        void Converter::do_storage_properties(
            DemangledType const& type, cv_context_t ctx )
        {
            bool is_retval = retval_ == &type;
            bool discard = stream.attr[ TextAttribute::DISCARD_CV_ON_RETURN_POINTER ]
                && type.is_pointer && is_retval && !in_op_type;
            char const* a = ( ctx == BEFORE ) ? " " : "";
            char const* b = ( ctx == AFTER ) ? " " : "";

            auto cv = [ this, &type, a, b ]( ) {
                if ( type.is_const ) stream << a << "const" << b;
                if ( type.is_volatile ) stream << a << "volatile" << b;
            };

            if ( !discard && ctx == AFTER ) cv( );
            if ( type.unaligned && stream.attr[ TextAttribute::MS_QUALIFIERS ] )
            {
                stream << a << "__unaligned" << b;
            }
            if ( type.is_pointer ) stream << a << ( type.is_gc ? '^' : '*' ) << b;
            if ( type.is_reference ) stream << a << ( type.is_gc ? '%' : '&' ) << b;
            if ( type.is_refref ) stream << a << "&&" << b;
            if ( type.ptr64 && stream.attr[ TextAttribute::OUTPUT_PTR64 ] ) stream << a << "__ptr64" << b;
            if ( type.restrict && stream.attr[ TextAttribute::MS_QUALIFIERS ] )
            {
                stream << a << "__restrict" << b;
            }
            if ( !discard && ctx == BEFORE ) cv( );
        }

        void Converter::class_name( )
        {
            if ( !t.name.empty( ) )
            {
                do_name( t.name.rbegin( ), std::prev( t.name.rend( ) ) );
            }
        }

        void Converter::method_name( )
        {
            if ( !t.name.empty( ) )
            {
                auto rv = t.retval;
                if ( !rv )
                {
                    rv.reset( new DemangledType( "void" ) );
                }
                auto save = tset( retval_, rv.get( ) );
                do_name( t.name.rbegin( ), t.name.rend( ), true );
            }
        }

        void Converter::method_signature( )
        {
            auto rv = t.retval;
            if ( !rv )
            {
                rv.reset( new DemangledType( "void" ) );
            }
            auto save = tset( retval_, rv.get( ) );
            do_type( t, [ this ] { method_name( ); } );
        }

    } // namespace detail

    AnsiString TextOutput::convert( DemangledType const& sym ) const
    {
        std::ostringstream os;
        convert( os, sym );
        return ToAnsiString( os.str( ) );
    }

    void TextOutput::convert_( std::ostream& stream, DemangledType const& sym ) const
    {
        detail::Converter( attr, stream, sym )( );
    }

    AnsiString TextOutput::get_class_name( DemangledType const& sym ) const
    {
        std::ostringstream os;
        detail::Converter( attr, os, sym ).class_name( );
        return ToAnsiString( os.str( ) );
    }

    AnsiString TextOutput::get_method_name( DemangledType const& sym ) const
    {
        std::ostringstream os;
        detail::Converter( attr, os, sym ).method_name( );
        return ToAnsiString( os.str( ) );
    }

    AnsiString TextOutput::get_method_signature( DemangledType const& sym ) const
    {
        std::ostringstream os;
        detail::Converter( attr, os, sym ).method_signature( );
        return ToAnsiString( os.str( ) );
    }

    std::vector<std::pair<const TextAttribute, const AnsiString>> const&
        TextAttributes::explain( )
    {
        static std::vector<std::pair<const TextAttribute, const AnsiString>> names{
            {TextAttribute::SPACE_AFTER_COMMA,
            AnsiString("Add a space after a comma")},
            { TextAttribute::SPACE_BETWEEN_TEMPLATE_BRACKETS,
             AnsiString( "Output spaces between adjacent identical template brackets" ) },
            { TextAttribute::VERBOSE_CONSTANT_STRING,
             AnsiString( "Include partial string content for constant string symbols" ) },
            { TextAttribute::CDTOR_CLASS_TEMPLATE_PARAMETERS,
             AnsiString( "Output a class's template parameters on the ctor or dtor name as well" ) },
            { TextAttribute::USER_DEFINED_CONVERSION_TEMPLATE_BEFORE_TYPE,
             AnsiString( "On templated user-defined conversion operators, put the template before the type" ) },
            { TextAttribute::OUTPUT_NEAR,
             AnsiString( "Include the near keyword on symbols marked as near" ) },
            { TextAttribute::MS_SIMPLE_TYPES,
             AnsiString( "Use Microsoft legacy names for [u]intX_t, like __int64" ) },
            { TextAttribute::OUTPUT_THUNKS,
             AnsiString( "Output [thunk]: in front of thunks" ) },
            { TextAttribute::OUTPUT_EXTERN,
             AnsiString( "Include extern \"C\" on names mangled(!) as extern \"C\"") },
            { TextAttribute::OUTPUT_ANONYMOUS_NUMBERS,
             AnsiString( "Include namespace numbers in anonymous namespace outputs") },
            { TextAttribute::DISCARD_CV_ON_RETURN_POINTER,
             AnsiString( "Discard const on pointer return values") },
            { TextAttribute::MS_QUALIFIERS,
             AnsiString( "Output Microsoft type qualifiers (__restrict, __unaligned)") },
            { TextAttribute::OUTPUT_PTR64,
             AnsiString( "Output __ptr64") },
            { TextAttribute::DISABLE_PREFIXES,
             AnsiString( "Disable enum/class/struct/union prefixes") },
            { TextAttribute::BROKEN_UNDNAME,
             AnsiString( "Include incorrect output that matches undname.exe when possible") },
        };

        return names;
    }


}
