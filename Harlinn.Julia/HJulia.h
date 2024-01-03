#pragma once
#ifndef __HJULIA_H__
#define __HJULIA_H__
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

#include <HJDef.h>
#include <HCCString.h>

#pragma pack(push,8)

namespace Harlinn::Julia
{
    class Symbol 
    {
        jl_sym_t* sym_;
#pragma warning(push)
#pragma warning(disable:4200)
        char name_[64];
#pragma warning(pop)
    public:
        explicit Symbol( )
            : sym_( nullptr )
        { }
        explicit Symbol( std::atomic<jl_sym_t*> sym )
            : sym_( sym.load() )
        { }

        Symbol& operator = ( const Symbol& other ) = delete;
        Symbol& operator = ( Symbol&& other ) = delete;

        Symbol Left( ) const
        {
            return Symbol(sym_->left.load());
        }
        Symbol Right( ) const
        {
            return Symbol(sym_->right.load( ) );
        }
        uintptr_t Hash( ) const
        {
            return sym_->hash;
        }

        constexpr const char* Name( ) const
        {
            return name_;
        }
    };

    class DataType;


    class Value
    {
        ValueT* value_;
    public:
        constexpr Value( ) noexcept
            : value_( nullptr )
        {

        }

        constexpr Value( ValueT* value ) noexcept
            : value_( value )
        {

        }
    protected:
        constexpr ValueT* InternalValue( ) const
        {
            return value_;
        }
    public:

        Value( bool value )
            : value_( jl_box_bool( value ) )
        {
        }
        Value( SByte value )
            : value_( jl_box_int8( value ) )
        {
        }
        Value( Byte value )
            : value_( jl_box_uint8( value ) )
        {
        }
        Value( Int16 value )
            : value_( jl_box_int16( value ) )
        {
        }
        Value( UInt16 value )
            : value_( jl_box_uint16( value ) )
        {
        }
        Value( Int32 value )
            : value_( jl_box_int32( value ) )
        {
        }
        Value( UInt32 value )
            : value_( jl_box_uint32( value ) )
        {
        }
        Value( Int64 value )
            : value_( jl_box_int64( value ) )
        {
        }
        Value( uint64_t value )
            : value_( jl_box_uint64( value ) )
        {
        }
        Value( float value )
            : value_( jl_box_float32( value ) )
        {
        }
        Value( double value )
            : value_( jl_box_float64( value ) )
        {
        }

        bool IsA( const Value& type )
        {
            return jl_isa( value_, type.value_ );
        }
        DataType Type( ) const;

        bool IsNothing( ) const
        {
            return jl_is_nothing( value_ );
        }
        bool IsTuple( ) const
        {
            return jl_is_tuple( value_ );
        }
        bool IsNamedTuple( ) const
        {
            return jl_is_namedtuple( value_ );
        }
        bool IsSimpleVector( ) const
        {
            return jl_is_simplevector( value_ );
        }
        bool IsUnionType( ) const
        {
            return jl_is_uniontype( value_ );
        }
        bool IsTypeVar( ) const
        {
            return jl_is_typevar( value_ );
        }
        bool IsUnionAll( ) const
        {
            return jl_is_unionall( value_ );
        }
        bool IsTypename( ) const
        {
            return jl_is_typename( value_ );
        }

        template<typename T>
        bool IsA() const;

        bool IsBoolean( ) const
        {
            return jl_is_bool( value_ );
        }
        template<>
        bool IsA<bool>( ) const
        {
            return jl_is_bool( value_ );
        }

        bool IsInt8( ) const
        {
            return jl_is_int8( value_ );
        }
        bool IsSByte( ) const
        {
            return jl_is_int8( value_ );
        }
        template<>
        bool IsA<SByte>( ) const
        {
            return jl_is_int8( value_ );
        }

        bool IsUInt8( ) const
        {
            return jl_is_uint8( value_ );
        }
        bool IsByte( ) const
        {
            return jl_is_uint8( value_ );
        }
        template<>
        bool IsA<Byte>( ) const
        {
            return jl_is_uint8( value_ );
        }


        bool IsInt16( ) const
        {
            return jl_is_int16( value_ );
        }
        template<>
        bool IsA<Int16>( ) const
        {
            return jl_is_int16( value_ );
        }

        bool IsUInt16( ) const
        {
            return jl_is_uint16( value_ );
        }
        template<>
        bool IsA<UInt16>( ) const
        {
            return jl_is_uint16( value_ );
        }

        bool IsInt32( ) const
        {
            return jl_is_int32( value_ );
        }
        template<>
        bool IsA<Int32>( ) const
        {
            return jl_is_int32( value_ );
        }

        bool IsUInt32( ) const
        {
            return jl_is_uint32( value_ );
        }
        template<>
        bool IsA<UInt32>( ) const
        {
            return jl_is_uint32( value_ );
        }


        bool IsInt64( ) const
        {
            return jl_is_int64( value_ );
        }
        template<>
        bool IsA<Int64>( ) const
        {
            return jl_is_int64( value_ );
        }

        bool IsUInt64( ) const
        {
            return jl_is_uint64( value_ );
        }
        template<>
        bool IsA<UInt64>( ) const
        {
            return jl_is_uint64( value_ );
        }

        bool IsSingle( ) const
        {
            return jl_typeis( value_, jl_float32_type );
        }
        template<>
        bool IsA<float>( ) const
        {
            return jl_typeis( value_, jl_float32_type );
        }

        bool IsDouble( ) const
        {
            return jl_typeis( value_, jl_float64_type );
        }
        template<>
        bool IsA<double>( ) const
        {
            return jl_typeis( value_, jl_float64_type );
        }

        bool IsSymbol( ) const
        {
            return jl_is_symbol( value_ );
        }
        bool IsSSAValue( ) const
        {
            return jl_is_ssavalue( value_ );
        }
        bool IsSlot( ) const
        {
            return jl_is_slot( value_ );
        }
        bool IsExpression( ) const
        {
            return jl_is_expr( value_ );
        }
        bool IsGlobalRef( ) const
        {
            return jl_is_globalref( value_ );
        }
        bool IsGotoNode( ) const
        {
            return jl_is_gotonode( value_ );
        }
        bool IsPiNode( ) const
        {
            return jl_is_pinode( value_ );
        }
        bool IsPhiNode( ) const
        {
            return jl_is_phinode( value_ );
        }
        bool IsPhiCNode( ) const
        {
            return jl_is_phicnode( value_ );
        }
        bool IsUpsilonNode( ) const
        {
            return jl_is_upsilonnode( value_ );
        }
        bool IsQuoteNode( ) const
        {
            return jl_is_quotenode( value_ );
        }
        bool IsNewVarNode( ) const
        {
            return jl_is_newvarnode( value_ );
        }
        bool IsLineNumberNode( ) const
        {
            return jl_is_linenode( value_ );
        }
        bool IsMethodInstance( ) const
        {
            return jl_is_method_instance( value_ );
        }
        bool IsCodeInstance( ) const
        {
            return jl_is_code_instance( value_ );
        }
        bool IsCodeInfo( ) const
        {
            return jl_is_code_info( value_ );
        }
        bool IsMethod( ) const
        {
            return jl_is_method( value_ );
        }
        bool IsModule( ) const
        {
            return jl_is_module( value_ );
        }
        bool IsMethodTable( ) const
        {
            return jl_is_mtable( value_ );
        }
        bool IsTask( ) const
        {
            return jl_is_task( value_ );
        }
        bool IsString( ) const
        {
            return jl_is_string( value_ );
        }
        bool IsPointer( ) const
        {
            return jl_is_pointer( value_ );
        }
        bool IsIntrinsic( ) const
        {
            return jl_is_intrinsic( value_ );
        }

        bool IsKind( ) const
        {
            return jl_is_kind( value_ );
        }
        bool IsType( ) const
        {
            return jl_is_type( value_ );
        }
        bool IsPrimitiveType( ) const
        {
            return jl_is_primitivetype( value_ );
        }
        bool IsStructType( ) const
        {
            return jl_is_structtype( value_ );
        }
        bool IsBitsType( ) const
        {
            return jl_isbits( value_ );
        }
        bool IsArray( ) const
        {
            return jl_is_array( value_ );
        }

        template<typename T>
        T As() const;

        bool ToBool( ) const
        {
            return jl_unbox_bool( value_ );
        }
        template<>
        bool As<bool>( ) const
        {
            return jl_unbox_bool( value_ );
        }


        SByte ToSByte( ) const
        {
            return jl_unbox_int8( value_ );
        }
        template<>
        SByte As<SByte>( ) const
        {
            return jl_unbox_int8( value_ );
        }
        uint8_t ToByte( ) const
        {
            return jl_unbox_uint8( value_ );
        }
        template<>
        Byte As<Byte>( ) const
        {
            return jl_unbox_uint8( value_ );
        }
        Int16 ToInt16( ) const
        {
            return jl_unbox_int16( value_ );
        }
        template<>
        Int16 As<Int16>( ) const
        {
            return jl_unbox_int16( value_ );
        }
        UInt16 ToUInt16( ) const
        {
            return jl_unbox_uint16( value_ );
        }
        template<>
        UInt16 As<UInt16>( ) const
        {
            return jl_unbox_uint16( value_ );
        }

        Int32 ToInt32( ) const
        {
            return jl_unbox_int32( value_ );
        }
        template<>
        Int32 As<Int32>( ) const
        {
            return jl_unbox_int32( value_ );
        }

        UInt32 ToUInt32( ) const
        {
            return jl_unbox_uint32( value_ );
        }
        template<>
        UInt32 As<UInt32>( ) const
        {
            return jl_unbox_uint32( value_ );
        }

        Int64 ToInt64( ) const
        {
            return jl_unbox_int64( value_ );
        }
        template<>
        Int64 As<Int64>( ) const
        {
            return jl_unbox_int64( value_ );
        }

        UInt64 ToUInt64( ) const
        {
            return jl_unbox_uint64( value_ );
        }
        template<>
        UInt64 As<UInt64>( ) const
        {
            return jl_unbox_uint64( value_ );
        }

        float ToSingle( ) const
        {
            return jl_unbox_float32( value_ );
        }
        template<>
        float As<float>( ) const
        {
            return jl_unbox_float32( value_ );
        }

        double ToDouble( ) const
        {
            return jl_unbox_float64( value_ );
        }
        template<>
        double As<double>( ) const
        {
            return jl_unbox_float64( value_ );
        }

        AnsiString ToString( ) const
        {
            return jl_string_ptr( value_ );
        }
        template<>
        AnsiString As<AnsiString>( ) const
        {
            return jl_string_ptr( value_ );
        }
        template<>
        AnsiStringView As<AnsiStringView>( ) const
        {
            return jl_string_ptr( value_ );
        }

        const char* ToStringPtr( ) const
        {
            return jl_string_ptr( value_ );
        }
        template<>
        const char* As<const char*>( ) const
        {
            return jl_string_ptr( value_ );
        }

        template<>
        const Byte* As<const Byte*>( ) const
        {
            return jl_unbox_uint8pointer( value_ );
        }
        template<>
        Byte* As<Byte*>( ) const
        {
            return jl_unbox_uint8pointer( value_ );
        }
        template<>
        const void* As<const void*>( ) const
        {
            return jl_unbox_voidpointer( value_ );
        }
        template<>
        void* As<void*>( ) const
        {
            return jl_unbox_voidpointer( value_ );
        }

        size_t FieldCount( ) const
        {
            auto type = jl_typeof( value_ );
            auto fieldCount = jl_datatype_nfields( type );
            return fieldCount;
        }
        Value Field( size_t index ) const
        {
            return jl_get_nth_field( value_, index );
        }

        void Show( ) const
        {
            auto* stream = jl_stdout_stream( );
            jl_static_show( stream, value_ );
            jl_flush_cstdio( );
        }

    };

    class DataType : public Value
    {
        friend class Value;
    public:
        using Base = Value;
        constexpr DataType( ) noexcept
            : Base( )
        {

        }

        constexpr DataType( DataTypeT* dataType ) noexcept
            : Base( (ValueT*)dataType )
        {

        }
    protected:
        DataTypeT* InternalValue( ) const
        {
            return (DataTypeT*)Base::InternalValue( );
        }
    public:

        size_t FieldCount( ) const
        {
            return jl_datatype_nfields( InternalValue( ) );
        }

        size_t Size( ) const
        {
            return jl_datatype_size( InternalValue( ) );
        }
        size_t Align( ) const
        {
            return jl_datatype_align( InternalValue( ) );
        }
        /*
        bool IsAllocatedInline( ) const
        {
            return jl_datatype_isinlinealloc( InternalValue( ) );
        }

        const Symbol* FieldName( size_t index ) const
        {
            return (const Symbol*)jl_field_names( InternalValue( ), index );
        }
        */
    };

    inline DataType Value::Type( ) const
    {
        return (DataTypeT*)jl_typeof( value_ );
    }




    class ArrayType : public DataType
    {
    public:
        using Base = DataType;
    public:
        constexpr ArrayType( ) noexcept
            : Base( )
        {

        }

        constexpr ArrayType( DataTypeT* dataType ) noexcept
            : Base( dataType )
        {

        }
    };


    class ArrayBase : public Value
    {
    public:
        using Base = Value;

        constexpr ArrayBase( ) noexcept
            : Base( )
        {

        }

        constexpr ArrayBase( ValueT* value ) noexcept
            : Base( value )
        {

        }

        constexpr ArrayBase( const Value& value ) noexcept
            : Base( value )
        {

        }


        size_t size( ) const
        {
            return jl_array_len( InternalValue( ) );
        }
        size_t Length( ) const
        {
            return jl_array_len( InternalValue( ) );
        }
        size_t ElementSize( ) const
        {
            auto a = (jl_array_t*)InternalValue( );
            return a->elsize;
        }
        void* data( ) const
        {
            return jl_array_data( InternalValue( ) );
        }
        size_t Rank( ) const
        {
            return jl_array_rank( InternalValue( ) );
        }
        size_t RowCount( ) const
        {
            return jl_array_nrows( InternalValue( ) );
        }
        size_t ColumnCount( ) const
        {
            auto a = (jl_array_t*)InternalValue( );
            return a->ncols;
        }
        size_t DimensionCount( ) const
        {
            auto a = (jl_array_t*)InternalValue( );
            return a->flags.ndims;
        }
        size_t Dimension( size_t index ) const
        {
            return jl_array_dim( InternalValue( ), index );
        }

    };

    template<typename T>
    class ArrayTemplate : public ArrayBase
    {
    public:
        using Base = ArrayBase;
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using size_type = size_t;

        constexpr ArrayTemplate( ) noexcept
            : Base( )
        {

        }

        constexpr ArrayTemplate( ValueT* value ) noexcept
            : Base( value )
        {

        }

        constexpr ArrayTemplate( const Value& value ) noexcept
            : Base( value )
        {

        }

        reference operator[]( size_type index )
        {
            return *( static_cast<pointer>( Base::data( ) ) + index );
        }
        const_reference operator[]( size_type index ) const
        {
            return *( static_cast<const_pointer>( Base::data( ) ) + index );
        }

        iterator begin( )
        {
            return static_cast<pointer>( Base::data( ) );
        }
        const_iterator begin( ) const
        {
            return static_cast<const_pointer>( Base::data( ) );
        }
        const_iterator cbegin( ) const
        {
            return static_cast<const_pointer>( Base::data( ) );
        }

        iterator end( )
        {
            return static_cast<pointer>( Base::data( ) ) + size( );
        }
        const_iterator end( ) const
        {
            return static_cast<const_pointer>( Base::data( ) ) + size( );
        }
        const_iterator cend( ) const
        {
            return static_cast<const_pointer>( Base::data( ) ) + size( );
        }

        reference front( )
        {
            return *static_cast<pointer>( Base::data( ) );
        }
        const_reference front( ) const
        {
            return *static_cast<const_pointer>( Base::data( ) );
        }

        reference back( )
        {
            return *( end( ) - 1 );
        }
        const_reference back( ) const
        {
            return *( end( ) - 1 );
        }
    };




    //class Module;
    class Function
    {
        FunctionT* function_;
    public:
        constexpr Function( ) noexcept
            : function_( nullptr )
        {
        }

        constexpr Function( FunctionT* function ) noexcept
            : function_( function )
        {
        }

    };

    /*
    class Module
    {
        ModuleT* module_;
    public:
        constexpr Module( ) noexcept
            : module_( nullptr )
        {
        }

        constexpr Module( ModuleT* module ) noexcept
            : module_( module )
        {
        }

        HJ_EXPORT const Symbol Name( ) const noexcept;
        HJ_EXPORT Module Parent( ) const noexcept;

        HJ_EXPORT static Module Main( );
        HJ_EXPORT static Module Core( );
        HJ_EXPORT static Module Base( );
        HJ_EXPORT static Module Top( );
    };
    */


    HJ_EXPORT void Init( );
    HJ_EXPORT void Finalize( int status );


    inline Value Eval( const char* script )
    {
        auto* ret = jl_eval_string( script );

        auto exceptionOccurred = jl_exception_occurred( );
        if ( exceptionOccurred )
        {
            const char* p = jl_string_ptr( jl_eval_string( "sprint(showerror, ccall(:jl_exception_occurred, Any, ()))" ) );
            puts( p );
        }

        return Value( ret );
    }


}
#pragma pack(pop)


#endif
