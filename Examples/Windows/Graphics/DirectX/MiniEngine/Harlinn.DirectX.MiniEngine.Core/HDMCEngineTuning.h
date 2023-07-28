//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{
    class VariableGroup;
    class TextContext;

    class EngineVar
    {
    public:

        virtual ~EngineVar( ) {}

        virtual void Increment( void ) { m_ActionCallback( ActionType::Increment ); }	// DPad Right
        virtual void Decrement( void ) { m_ActionCallback( ActionType::Decrement ); }	// DPad Left
        virtual void Bang( void ) { m_ActionCallback( ActionType::Bang ); }		// A Button

        virtual void DisplayValue( TextContext& ) const {}
        virtual std::string ToString( void ) const { return ""; }
        virtual void SetValue( FILE* file, const std::string& setting ) = 0; //set value read from file

        HDMC_EXPORT EngineVar* NextVar( void );
        HDMC_EXPORT EngineVar* PrevVar( void );

        enum class ActionType
        {
            Increment,
            Decrement,
            Bang
        };

        typedef std::function<void( ActionType )> ActionCallback;

    protected:

        HDMC_EXPORT EngineVar( void );
        HDMC_EXPORT EngineVar( const std::string& path, ActionCallback pfnCallback = DefaultActionHandler );

        static void DefaultActionHandler( ActionType )
        {
            // nothing
        }

    private:
        friend class VariableGroup;
        VariableGroup* m_GroupPtr;

        ActionCallback m_ActionCallback;
    };

    class BoolVar : public EngineVar
    {
    public:
        HDMC_EXPORT BoolVar( const std::string& path, bool val, ActionCallback pfnCallback = EngineVar::DefaultActionHandler );
        BoolVar& operator=( bool val ) { m_Flag = val; return *this; }
        operator bool( ) const { return m_Flag; }

        virtual void Increment( void ) override { m_Flag = true; EngineVar::Increment( ); }
        virtual void Decrement( void ) override { m_Flag = false; EngineVar::Decrement( ); }
        virtual void Bang( void ) override { m_Flag = !m_Flag;  EngineVar::Bang( ); }

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual std::string ToString( void ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting ) override;

    private:
        bool m_Flag;
    };

    class NumVar : public EngineVar
    {
    public:
        HDMC_EXPORT NumVar( const std::string& path, float val, float minValue = -FLT_MAX, float maxValue = FLT_MAX, float stepSize = 1.0f, ActionCallback pfnCallback = EngineVar::DefaultActionHandler );
        NumVar& operator=( float val ) { m_Value = Clamp( val ); return *this; }
        operator float( ) const { return m_Value; }

        virtual void Increment( void ) override { m_Value = Clamp( m_Value + m_StepSize ); EngineVar::Increment( ); }
        virtual void Decrement( void ) override { m_Value = Clamp( m_Value - m_StepSize ); EngineVar::Decrement( ); }

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual std::string ToString( void ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting )  override;

    protected:
        float Clamp( float val ) { return val > m_MaxValue ? m_MaxValue : val < m_MinValue ? m_MinValue : val; }

        float m_Value;
        float m_MinValue;
        float m_MaxValue;
        float m_StepSize;
    };

    class ExpVar : public NumVar
    {
    public:
        HDMC_EXPORT ExpVar( const std::string& path, float val, float minExp = -FLT_MAX, float maxExp = FLT_MAX, float expStepSize = 1.0f, ActionCallback pfnCallback = EngineVar::DefaultActionHandler );
        HDMC_EXPORT ExpVar& operator=( float val );	// m_Value = log2(val)
        HDMC_EXPORT operator float( ) const;			// returns exp2(m_Value)

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual std::string ToString( void ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting ) override;

    };

    class IntVar : public EngineVar
    {
    public:
        HDMC_EXPORT IntVar( const std::string& path, int32_t val, int32_t minValue = 0, int32_t maxValue = ( 1 << 24 ) - 1, int32_t stepSize = 1, ActionCallback pfnCallback = EngineVar::DefaultActionHandler );
        IntVar& operator=( int32_t val ) { m_Value = Clamp( val ); return *this; }
        operator int32_t( ) const { return m_Value; }

        virtual void Increment( void ) override { m_Value = Clamp( m_Value + m_StepSize ); EngineVar::Increment( ); }
        virtual void Decrement( void ) override { m_Value = Clamp( m_Value - m_StepSize ); EngineVar::Decrement( ); }

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual std::string ToString( void ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting ) override;

    protected:
        int32_t Clamp( int32_t val ) { return val > m_MaxValue ? m_MaxValue : val < m_MinValue ? m_MinValue : val; }

        int32_t m_Value;
        int32_t m_MinValue;
        int32_t m_MaxValue;
        int32_t m_StepSize;
    };

    class EnumVar : public EngineVar
    {
    public:
        HDMC_EXPORT EnumVar( const std::string& path, int32_t initialVal, int32_t listLength, const char** listLabels, ActionCallback pfnCallback = EngineVar::DefaultActionHandler );
        EnumVar& operator=( int32_t val ) { m_Value = Clamp( val ); return *this; }
        operator int32_t( ) const { return m_Value; }

        virtual void Increment( void ) override { m_Value = ( m_Value + 1 ) % m_EnumLength; EngineVar::Increment( ); }
        virtual void Decrement( void ) override { m_Value = ( m_Value + m_EnumLength - 1 ) % m_EnumLength; EngineVar::Decrement( ); }

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual std::string ToString( void ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting ) override;

        void SetListLength( int32_t listLength ) { m_EnumLength = listLength; m_Value = Clamp( m_Value ); }

    private:
        int32_t Clamp( int32_t val ) { return val < 0 ? 0 : val >= m_EnumLength ? m_EnumLength - 1 : val; }

        int32_t m_Value;
        int32_t m_EnumLength;
        const char** m_EnumLabels;
    };

    class DynamicEnumVar : public EngineVar
    {
    public:
        HDMC_EXPORT DynamicEnumVar( const std::string& path, ActionCallback pfnCallback = EngineVar::DefaultActionHandler );
        DynamicEnumVar& operator=( int32_t val ) { m_Value = Clamp( val ); return *this; }
        operator int32_t( ) const { return m_Value; }

        virtual void Increment( void ) override { m_Value = ( m_Value + 1 ) % m_EnumCount; EngineVar::Increment( ); }
        virtual void Decrement( void ) override { m_Value = ( m_Value + m_EnumCount - 1 ) % m_EnumCount; EngineVar::Decrement( ); }

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual std::string ToString( void ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting ) override;

        void AddEnum( const std::wstring& enumLabel ) { m_EnumLabels.push_back( enumLabel ); m_EnumCount++; }

    private:
        int32_t Clamp( int32_t val ) { return val < 0 ? 0 : val >= m_EnumCount ? m_EnumCount - 1 : val; }

        int32_t m_Value;
        int32_t m_EnumCount;
        std::vector<std::wstring> m_EnumLabels;
    };

    class CallbackTrigger : public EngineVar
    {
    public:
        HDMC_EXPORT CallbackTrigger( const std::string& path, std::function<void( void* )> callback, void* args = nullptr );

        virtual void Bang( void ) override { m_Callback( m_Arguments ); m_BangDisplay = 64; }

        HDMC_EXPORT virtual void DisplayValue( TextContext& Text ) const override;
        HDMC_EXPORT virtual void SetValue( FILE* file, const std::string& setting ) override;

    private:
        std::function<void( void* )> m_Callback;
        void* m_Arguments;
        mutable uint32_t m_BangDisplay;
    };

    class GraphicsContext;

    namespace EngineTuning
    {
        HDMC_EXPORT void Initialize( void );
        HDMC_EXPORT void Update( float frameTime );
        HDMC_EXPORT void Display( GraphicsContext& Context, float x, float y, float w, float h );
        HDMC_EXPORT bool IsFocused( void );

    } // namespace EngineTuning
}