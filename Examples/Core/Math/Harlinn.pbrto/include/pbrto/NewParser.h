#pragma once
#ifndef PBRTO_NEWPARSER_H_
#define PBRTO_NEWPARSER_H_

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


// pbrt is Copyright(c) 1998-2020 Matt Pharr, Wenzel Jakob, and Greg Humphreys.
// The pbrt source code is licensed under the Apache License, Version 2.0.
// SPDX: Apache-2.0

#include <pbrto/NewPbrt.h>

#include <pbrto/NewParamdict.h>
#include <pbrto/util/NewCheck.h>
#include <pbrto/util/NewContainers.h>
#include <pbrto/util/NewError.h>
#include <pbrto/util/NewPStd.h>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>

namespace pbrto
{

    // ParserTarget Definition
    class ParserTarget
    {
    public:
        // ParserTarget Interface
        virtual void Scale( Float sx, Float sy, Float sz, FileLoc loc ) = 0;

        virtual void Shape( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;

        PBRTO_EXPORT
            virtual ~ParserTarget( );

        virtual void Option( const std::string& name, const std::string& value,
            FileLoc loc ) = 0;

        virtual void Identity( FileLoc loc ) = 0;
        virtual void Translate( Float dx, Float dy, Float dz, FileLoc loc ) = 0;
        virtual void Rotate( Float angle, Float ax, Float ay, Float az, FileLoc loc ) = 0;
        virtual void LookAt( Float ex, Float ey, Float ez, Float lx, Float ly, Float lz,
            Float ux, Float uy, Float uz, FileLoc loc ) = 0;
        virtual void ConcatTransform( const std::array<Float, 16>& transform, FileLoc loc ) = 0;
        virtual void Transform( const std::array<Float, 16>& transform, FileLoc loc ) = 0;
        virtual void CoordinateSystem( const std::string&, FileLoc loc ) = 0;
        virtual void CoordSysTransform( const std::string&, FileLoc loc ) = 0;
        virtual void ActiveTransformAll( FileLoc loc ) = 0;
        virtual void ActiveTransformEndTime( FileLoc loc ) = 0;
        virtual void ActiveTransformStartTime( FileLoc loc ) = 0;
        virtual void TransformTimes( Float start, Float end, FileLoc loc ) = 0;

        virtual void ColorSpace( const std::string& n, FileLoc loc ) = 0;
        virtual void PixelFilter( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void Film( const std::string& type, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void Accelerator( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void Integrator( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void Camera( const std::string&, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void MakeNamedMedium( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void MediumInterface( const std::string& insideName,
            const std::string& outsideName, FileLoc loc ) = 0;
        virtual void Sampler( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;

        virtual void WorldBegin( FileLoc loc ) = 0;
        virtual void AttributeBegin( FileLoc loc ) = 0;
        virtual void AttributeEnd( FileLoc loc ) = 0;
        virtual void Attribute( const std::string& target, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void Texture( const std::string& name, const std::string& type,
            const std::string& texname, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void Material( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void MakeNamedMaterial( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void NamedMaterial( const std::string& name, FileLoc loc ) = 0;
        virtual void LightSource( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void AreaLightSource( const std::string& name, ParsedParameterVector params,
            FileLoc loc ) = 0;
        virtual void ReverseOrientation( FileLoc loc ) = 0;
        virtual void ObjectBegin( const std::string& name, FileLoc loc ) = 0;
        virtual void ObjectEnd( FileLoc loc ) = 0;
        virtual void ObjectInstance( const std::string& name, FileLoc loc ) = 0;

        virtual void EndOfFiles( ) = 0;

    protected:
        // ParserTarget Protected Methods
        template <typename... Args>
        void ErrorExitDeferred( const char* fmt, Args &&...args ) const
        {
            errorExit = true;
            Error( fmt, std::forward<Args>( args )... );
        }
        template <typename... Args>
        void ErrorExitDeferred( const FileLoc* loc, const char* fmt, Args &&...args ) const
        {
            errorExit = true;
            Error( loc, fmt, std::forward<Args>( args )... );
        }

        mutable bool errorExit = false;
    };

    // Scene Parsing Declarations
    PBRTO_EXPORT
        void ParseFiles( ParserTarget* target, pstdo::span<const std::string> filenames );
    PBRTO_EXPORT
        void ParseString( ParserTarget* target, std::string str );

    // Token Definition
    struct Token
    {
        Token( ) = default;
        Token( std::string_view token, FileLoc loc ) : token( token ), loc( loc ) {}
        std::string ToString( ) const;
        std::string_view token;
        FileLoc loc;
    };

    // Tokenizer Definition
    class Tokenizer
    {
    public:
        // Tokenizer Public Methods
        Tokenizer( std::string str, std::string filename,
            std::function<void( const char*, const FileLoc* )> errorCallback );
#if defined(PBRT_HAVE_MMAP) || defined(PBRT_IS_WINDOWS)
        Tokenizer( void* ptr, size_t len, std::string filename,
            std::function<void( const char*, const FileLoc* )> errorCallback );
#endif
        ~Tokenizer( );

        static std::unique_ptr<Tokenizer> CreateFromFile(
            const std::string& filename,
            std::function<void( const char*, const FileLoc* )> errorCallback );
        static std::unique_ptr<Tokenizer> CreateFromString(
            std::string str,
            std::function<void( const char*, const FileLoc* )> errorCallback );

        pstdo::optional<Token> Next( );

        // Just for parse().
        // TODO? Have a method to set this?
        FileLoc loc;

    private:
        // Tokenizer Private Methods
        void CheckUTF( const void* ptr, int len ) const;

        int getChar( )
        {
            if ( pos == end )
                return EOF;
            int ch = *pos++;
            if ( ch == '\n' )
            {
                ++loc.line;
                loc.column = 0;
            }
            else
                ++loc.column;
            return ch;
        }
        void ungetChar( )
        {
            --pos;
            if ( *pos == '\n' )
                // Don't worry about the column; we'll be going to the start of
                // the next line again shortly...
                --loc.line;
        }

        // Tokenizer Private Members
        // This function is called if there is an error during lexing.
        std::function<void( const char*, const FileLoc* )> errorCallback;

#if defined(PBRT_HAVE_MMAP) || defined(PBRT_IS_WINDOWS)
        // Scene files on disk are mapped into memory for lexing.  We need to
        // hold on to the starting pointer and total length so they can be
        // unmapped in the destructor.
        void* unmapPtr = nullptr;
        size_t unmapLength = 0;
#endif

        // If the input is stdin, then we copy everything until EOF into this
        // string and then start lexing.  This is a little wasteful (versus
        // tokenizing directly from stdin), but makes the implementation
        // simpler.
        std::string contents;

        // Pointers to the current position in the file and one past the end of
        // the file.
        const char* pos, * end;

        // If there are escaped characters in the string, we can't just return
        // a std::string_view into the mapped file. In that case, we handle the
        // escaped characters and return a std::string_view to sEscaped.  (And
        // thence, std::string_views from previous calls to Next() must be invalid
        // after a subsequent call, since we may reuse sEscaped.)
        std::string sEscaped;
    };

    // FormattingParserTarget Definition
    class FormattingParserTarget : public ParserTarget
    {
    public:
        FormattingParserTarget( bool toPly, bool upgrade ) : toPly( toPly ), upgrade( upgrade ) {}
        PBRTO_EXPORT
            ~FormattingParserTarget( );

        PBRTO_EXPORT
            void Option( const std::string& name, const std::string& value, FileLoc loc );
        PBRTO_EXPORT
            void Identity( FileLoc loc );
        PBRTO_EXPORT
            void Translate( Float dx, Float dy, Float dz, FileLoc loc );
        PBRTO_EXPORT
            void Rotate( Float angle, Float ax, Float ay, Float az, FileLoc loc );
        PBRTO_EXPORT
            void Scale( Float sx, Float sy, Float sz, FileLoc loc );
        PBRTO_EXPORT
            void LookAt( Float ex, Float ey, Float ez, Float lx, Float ly, Float lz, Float ux,
                Float uy, Float uz, FileLoc loc );
        PBRTO_EXPORT
            void ConcatTransform( const std::array<Float, 16>& transform, FileLoc loc );
        PBRTO_EXPORT
            void Transform( const std::array<Float, 16>& transform, FileLoc loc );
        PBRTO_EXPORT
            void CoordinateSystem( const std::string&, FileLoc loc );
        PBRTO_EXPORT
            void CoordSysTransform( const std::string&, FileLoc loc );
        PBRTO_EXPORT
            void ActiveTransformAll( FileLoc loc );
        PBRTO_EXPORT
            void ActiveTransformEndTime( FileLoc loc );
        PBRTO_EXPORT
            void ActiveTransformStartTime( FileLoc loc );
        PBRTO_EXPORT
            void TransformTimes( Float start, Float end, FileLoc loc );
        PBRTO_EXPORT
            void TransformBegin( FileLoc loc );
        PBRTO_EXPORT
            void TransformEnd( FileLoc loc );
        PBRTO_EXPORT
            void ColorSpace( const std::string& n, FileLoc loc );
        PBRTO_EXPORT
            void PixelFilter( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Film( const std::string& type, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Sampler( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Accelerator( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Integrator( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Camera( const std::string&, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void MakeNamedMedium( const std::string& name, ParsedParameterVector params,
                FileLoc loc );
        PBRTO_EXPORT
            void MediumInterface( const std::string& insideName, const std::string& outsideName,
                FileLoc loc );
        PBRTO_EXPORT
            void WorldBegin( FileLoc loc );
        PBRTO_EXPORT
            void AttributeBegin( FileLoc loc );
        PBRTO_EXPORT
            void AttributeEnd( FileLoc loc );
        PBRTO_EXPORT
            void Attribute( const std::string& target, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Texture( const std::string& name, const std::string& type,
                const std::string& texname, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void Material( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void MakeNamedMaterial( const std::string& name, ParsedParameterVector params,
                FileLoc loc );
        PBRTO_EXPORT
            void NamedMaterial( const std::string& name, FileLoc loc );
        PBRTO_EXPORT
            void LightSource( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void AreaLightSource( const std::string& name, ParsedParameterVector params,
                FileLoc loc );
        PBRTO_EXPORT
            void Shape( const std::string& name, ParsedParameterVector params, FileLoc loc );
        PBRTO_EXPORT
            void ReverseOrientation( FileLoc loc );
        PBRTO_EXPORT
            void ObjectBegin( const std::string& name, FileLoc loc );
        PBRTO_EXPORT
            void ObjectEnd( FileLoc loc );
        PBRTO_EXPORT
            void ObjectInstance( const std::string& name, FileLoc loc );

        PBRTO_EXPORT
            void EndOfFiles( );

        std::string indent( int extra = 0 ) const
        {
            return std::string( catIndentCount + 4 * extra, ' ' );
        }

    private:
        PBRTO_EXPORT
            std::string upgradeMaterialIndex( const std::string& name, ParameterDictionary* dict,
                FileLoc loc ) const;
        PBRTO_EXPORT
            std::string upgradeMaterial( std::string* name, ParameterDictionary* dict,
                FileLoc loc ) const;

        int catIndentCount = 0;
        bool toPly, upgrade;
        std::map<std::string, std::string> definedTextures;
        std::map<std::string, std::string> definedNamedMaterials;
        std::map<std::string, ParameterDictionary> namedMaterialDictionaries;
        std::map<std::string, std::string> definedObjectInstances;
    };

}


#endif
