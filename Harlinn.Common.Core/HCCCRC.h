#pragma once
#ifndef __HCCCRC_H__
#define __HCCCRC_H__
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

#include <HCCDef.h>
#include <HCCExport.h>

namespace Harlinn::Common::Core
{
    HCC_EXPORT uint32_t crc32( const void* buffer, size_t bufferSize, uint32_t crc = 0 );

    // Initial CRC value.
    // Initial value can be used to chain CRC from multiple buffers.
    HCC_EXPORT uint32_t crc32c( const uint8_t* input, size_t length, uint32_t crc = 0 );


    // Software fallback version of CRC-32C (Castagnoli) checksum.
    HCC_EXPORT uint32_t crc32c_sw( const uint8_t* input, size_t length, uint32_t crc = 0 );

    // Hardware version of CRC-32C (Castagnoli) checksum.
    // Will fail, if CPU does not support related instructions.
    // Use the crc32c version instead of.
    HCC_EXPORT uint32_t crc32c_hw( const uint8_t* input, size_t length, uint32_t crc = 0 );

    // Checks is hardware version of CRC-32C is available.
    HCC_EXPORT int crc32c_hw_available( );


    namespace Internal
    {
        constexpr UInt32 crc24qLookupTable[256] = 
        {
            0x00000000u, 0x01864CFBu, 0x028AD50Du, 0x030C99F6u,
            0x0493E6E1u, 0x0515AA1Au, 0x061933ECu, 0x079F7F17u,
            0x08A18139u, 0x0927CDC2u, 0x0A2B5434u, 0x0BAD18CFu,
            0x0C3267D8u, 0x0DB42B23u, 0x0EB8B2D5u, 0x0F3EFE2Eu,
            0x10C54E89u, 0x11430272u, 0x124F9B84u, 0x13C9D77Fu,
            0x1456A868u, 0x15D0E493u, 0x16DC7D65u, 0x175A319Eu,
            0x1864CFB0u, 0x19E2834Bu, 0x1AEE1ABDu, 0x1B685646u,
            0x1CF72951u, 0x1D7165AAu, 0x1E7DFC5Cu, 0x1FFBB0A7u,
            0x200CD1E9u, 0x218A9D12u, 0x228604E4u, 0x2300481Fu,
            0x249F3708u, 0x25197BF3u, 0x2615E205u, 0x2793AEFEu,
            0x28AD50D0u, 0x292B1C2Bu, 0x2A2785DDu, 0x2BA1C926u,
            0x2C3EB631u, 0x2DB8FACAu, 0x2EB4633Cu, 0x2F322FC7u,
            0x30C99F60u, 0x314FD39Bu, 0x32434A6Du, 0x33C50696u,
            0x345A7981u, 0x35DC357Au, 0x36D0AC8Cu, 0x3756E077u,
            0x38681E59u, 0x39EE52A2u, 0x3AE2CB54u, 0x3B6487AFu,
            0x3CFBF8B8u, 0x3D7DB443u, 0x3E712DB5u, 0x3FF7614Eu,
            0x4019A3D2u, 0x419FEF29u, 0x429376DFu, 0x43153A24u,
            0x448A4533u, 0x450C09C8u, 0x4600903Eu, 0x4786DCC5u,
            0x48B822EBu, 0x493E6E10u, 0x4A32F7E6u, 0x4BB4BB1Du,
            0x4C2BC40Au, 0x4DAD88F1u, 0x4EA11107u, 0x4F275DFCu,
            0x50DCED5Bu, 0x515AA1A0u, 0x52563856u, 0x53D074ADu,
            0x544F0BBAu, 0x55C94741u, 0x56C5DEB7u, 0x5743924Cu,
            0x587D6C62u, 0x59FB2099u, 0x5AF7B96Fu, 0x5B71F594u,
            0x5CEE8A83u, 0x5D68C678u, 0x5E645F8Eu, 0x5FE21375u,
            0x6015723Bu, 0x61933EC0u, 0x629FA736u, 0x6319EBCDu,
            0x648694DAu, 0x6500D821u, 0x660C41D7u, 0x678A0D2Cu,
            0x68B4F302u, 0x6932BFF9u, 0x6A3E260Fu, 0x6BB86AF4u,
            0x6C2715E3u, 0x6DA15918u, 0x6EADC0EEu, 0x6F2B8C15u,
            0x70D03CB2u, 0x71567049u, 0x725AE9BFu, 0x73DCA544u,
            0x7443DA53u, 0x75C596A8u, 0x76C90F5Eu, 0x774F43A5u,
            0x7871BD8Bu, 0x79F7F170u, 0x7AFB6886u, 0x7B7D247Du,
            0x7CE25B6Au, 0x7D641791u, 0x7E688E67u, 0x7FEEC29Cu,
            0x803347A4u, 0x81B50B5Fu, 0x82B992A9u, 0x833FDE52u,
            0x84A0A145u, 0x8526EDBEu, 0x862A7448u, 0x87AC38B3u,
            0x8892C69Du, 0x89148A66u, 0x8A181390u, 0x8B9E5F6Bu,
            0x8C01207Cu, 0x8D876C87u, 0x8E8BF571u, 0x8F0DB98Au,
            0x90F6092Du, 0x917045D6u, 0x927CDC20u, 0x93FA90DBu,
            0x9465EFCCu, 0x95E3A337u, 0x96EF3AC1u, 0x9769763Au,
            0x98578814u, 0x99D1C4EFu, 0x9ADD5D19u, 0x9B5B11E2u,
            0x9CC46EF5u, 0x9D42220Eu, 0x9E4EBBF8u, 0x9FC8F703u,
            0xA03F964Du, 0xA1B9DAB6u, 0xA2B54340u, 0xA3330FBBu,
            0xA4AC70ACu, 0xA52A3C57u, 0xA626A5A1u, 0xA7A0E95Au,
            0xA89E1774u, 0xA9185B8Fu, 0xAA14C279u, 0xAB928E82u,
            0xAC0DF195u, 0xAD8BBD6Eu, 0xAE872498u, 0xAF016863u,
            0xB0FAD8C4u, 0xB17C943Fu, 0xB2700DC9u, 0xB3F64132u,
            0xB4693E25u, 0xB5EF72DEu, 0xB6E3EB28u, 0xB765A7D3u,
            0xB85B59FDu, 0xB9DD1506u, 0xBAD18CF0u, 0xBB57C00Bu,
            0xBCC8BF1Cu, 0xBD4EF3E7u, 0xBE426A11u, 0xBFC426EAu,
            0xC02AE476u, 0xC1ACA88Du, 0xC2A0317Bu, 0xC3267D80u,
            0xC4B90297u, 0xC53F4E6Cu, 0xC633D79Au, 0xC7B59B61u,
            0xC88B654Fu, 0xC90D29B4u, 0xCA01B042u, 0xCB87FCB9u,
            0xCC1883AEu, 0xCD9ECF55u, 0xCE9256A3u, 0xCF141A58u,
            0xD0EFAAFFu, 0xD169E604u, 0xD2657FF2u, 0xD3E33309u,
            0xD47C4C1Eu, 0xD5FA00E5u, 0xD6F69913u, 0xD770D5E8u,
            0xD84E2BC6u, 0xD9C8673Du, 0xDAC4FECBu, 0xDB42B230u,
            0xDCDDCD27u, 0xDD5B81DCu, 0xDE57182Au, 0xDFD154D1u,
            0xE026359Fu, 0xE1A07964u, 0xE2ACE092u, 0xE32AAC69u,
            0xE4B5D37Eu, 0xE5339F85u, 0xE63F0673u, 0xE7B94A88u,
            0xE887B4A6u, 0xE901F85Du, 0xEA0D61ABu, 0xEB8B2D50u,
            0xEC145247u, 0xED921EBCu, 0xEE9E874Au, 0xEF18CBB1u,
            0xF0E37B16u, 0xF16537EDu, 0xF269AE1Bu, 0xF3EFE2E0u,
            0xF4709DF7u, 0xF5F6D10Cu, 0xF6FA48FAu, 0xF77C0401u,
            0xF842FA2Fu, 0xF9C4B6D4u, 0xFAC82F22u, 0xFB4E63D9u,
            0xFCD11CCEu, 0xFD575035u, 0xFE5BC9C3u, 0xFFDD8538u,
        };
    }


    inline constexpr UInt32 crc24q( const uint8_t* input, size_t length, UInt32 crc = 0 )
    {
        for ( size_t i = 0; i < length; i++ )
        {
            crc = ( crc << 8 ) ^ Core::Internal::crc24qLookupTable[input[i] ^ (Byte)( crc >> 16 )];
        }

        crc = ( crc & 0x00ffffff );

        return crc;
    }

}

#endif
