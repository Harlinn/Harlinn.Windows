#include "pch.h"
#include "HWMediaFoundation.h"
#include "HWCameraUIControl.h"
#include "HWDXVA2Api.h"
#include "HWMFTransform.h"
#include "HWMFReadWrite.h"

namespace Harlinn::Windows::MF
{

#ifndef IF_EQUAL_RETURN
#define IF_EQUAL_RETURN(param, val) if(val == param) return L#val
#endif

    HW_EXPORT WideString GetGUIDNameConst(const Guid& guid)
    {
        IF_EQUAL_RETURN(guid, MF_MT_MAJOR_TYPE);
        IF_EQUAL_RETURN(guid, MF_MT_MAJOR_TYPE);
        IF_EQUAL_RETURN(guid, MF_MT_SUBTYPE);
        IF_EQUAL_RETURN(guid, MF_MT_ALL_SAMPLES_INDEPENDENT);
        IF_EQUAL_RETURN(guid, MF_MT_FIXED_SIZE_SAMPLES);
        IF_EQUAL_RETURN(guid, MF_MT_COMPRESSED);
        IF_EQUAL_RETURN(guid, MF_MT_SAMPLE_SIZE);
        IF_EQUAL_RETURN(guid, MF_MT_WRAPPED_TYPE);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_NUM_CHANNELS);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_SAMPLES_PER_SECOND);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_FLOAT_SAMPLES_PER_SECOND);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_AVG_BYTES_PER_SECOND);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_BLOCK_ALIGNMENT);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_BITS_PER_SAMPLE);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_VALID_BITS_PER_SAMPLE);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_SAMPLES_PER_BLOCK);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_CHANNEL_MASK);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_FOLDDOWN_MATRIX);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_PEAKREF);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_PEAKTARGET);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_AVGREF);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_WMADRC_AVGTARGET);
        IF_EQUAL_RETURN(guid, MF_MT_AUDIO_PREFER_WAVEFORMATEX);
        IF_EQUAL_RETURN(guid, MF_MT_AAC_PAYLOAD_TYPE);
        IF_EQUAL_RETURN(guid, MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION);
        IF_EQUAL_RETURN(guid, MF_MT_FRAME_SIZE);
        IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE);
        IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE_RANGE_MAX);
        IF_EQUAL_RETURN(guid, MF_MT_FRAME_RATE_RANGE_MIN);
        IF_EQUAL_RETURN(guid, MF_MT_PIXEL_ASPECT_RATIO);
        IF_EQUAL_RETURN(guid, MF_MT_DRM_FLAGS);
        IF_EQUAL_RETURN(guid, MF_MT_PAD_CONTROL_FLAGS);
        IF_EQUAL_RETURN(guid, MF_MT_SOURCE_CONTENT_HINT);
        IF_EQUAL_RETURN(guid, MF_MT_VIDEO_CHROMA_SITING);
        IF_EQUAL_RETURN(guid, MF_MT_INTERLACE_MODE);
        IF_EQUAL_RETURN(guid, MF_MT_TRANSFER_FUNCTION);
        IF_EQUAL_RETURN(guid, MF_MT_VIDEO_PRIMARIES);
        IF_EQUAL_RETURN(guid, MF_MT_CUSTOM_VIDEO_PRIMARIES);
        IF_EQUAL_RETURN(guid, MF_MT_YUV_MATRIX);
        IF_EQUAL_RETURN(guid, MF_MT_VIDEO_LIGHTING);
        IF_EQUAL_RETURN(guid, MF_MT_VIDEO_NOMINAL_RANGE);
        IF_EQUAL_RETURN(guid, MF_MT_GEOMETRIC_APERTURE);
        IF_EQUAL_RETURN(guid, MF_MT_MINIMUM_DISPLAY_APERTURE);
        IF_EQUAL_RETURN(guid, MF_MT_PAN_SCAN_APERTURE);
        IF_EQUAL_RETURN(guid, MF_MT_PAN_SCAN_ENABLED);
        IF_EQUAL_RETURN(guid, MF_MT_AVG_BITRATE);
        IF_EQUAL_RETURN(guid, MF_MT_AVG_BIT_ERROR_RATE);
        IF_EQUAL_RETURN(guid, MF_MT_MAX_KEYFRAME_SPACING);
        IF_EQUAL_RETURN(guid, MF_MT_DEFAULT_STRIDE);
        IF_EQUAL_RETURN(guid, MF_MT_PALETTE);
        IF_EQUAL_RETURN(guid, MF_MT_USER_DATA);
        IF_EQUAL_RETURN(guid, MF_MT_AM_FORMAT_TYPE);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG_START_TIME_CODE);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG2_PROFILE);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG2_LEVEL);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG2_FLAGS);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG_SEQUENCE_HEADER);
        IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_SRC_PACK_0);
        IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_CTRL_PACK_0);
        IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_SRC_PACK_1);
        IF_EQUAL_RETURN(guid, MF_MT_DV_AAUX_CTRL_PACK_1);
        IF_EQUAL_RETURN(guid, MF_MT_DV_VAUX_SRC_PACK);
        IF_EQUAL_RETURN(guid, MF_MT_DV_VAUX_CTRL_PACK);
        IF_EQUAL_RETURN(guid, MF_MT_ARBITRARY_HEADER);
        IF_EQUAL_RETURN(guid, MF_MT_ARBITRARY_FORMAT);
        IF_EQUAL_RETURN(guid, MF_MT_IMAGE_LOSS_TOLERANT);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG4_SAMPLE_DESCRIPTION);
        IF_EQUAL_RETURN(guid, MF_MT_MPEG4_CURRENT_SAMPLE_ENTRY);
        IF_EQUAL_RETURN(guid, MF_MT_ORIGINAL_4CC);
        IF_EQUAL_RETURN(guid, MF_MT_ORIGINAL_WAVE_FORMAT_TAG);

        // Media types

        IF_EQUAL_RETURN(guid, MFMediaType_Audio);
        IF_EQUAL_RETURN(guid, MFMediaType_Video);
        IF_EQUAL_RETURN(guid, MFMediaType_Protected);
        IF_EQUAL_RETURN(guid, MFMediaType_SAMI);
        IF_EQUAL_RETURN(guid, MFMediaType_Script);
        IF_EQUAL_RETURN(guid, MFMediaType_Image);
        IF_EQUAL_RETURN(guid, MFMediaType_HTML);
        IF_EQUAL_RETURN(guid, MFMediaType_Binary);
        IF_EQUAL_RETURN(guid, MFMediaType_FileTransfer);

        IF_EQUAL_RETURN(guid, MFVideoFormat_AI44); //     FCC('AI44')
        IF_EQUAL_RETURN(guid, MFVideoFormat_ARGB32); //   D3DFMT_A8R8G8B8 
        IF_EQUAL_RETURN(guid, MFVideoFormat_AYUV); //     FCC('AYUV')
        IF_EQUAL_RETURN(guid, MFVideoFormat_DV25); //     FCC('dv25')
        IF_EQUAL_RETURN(guid, MFVideoFormat_DV50); //     FCC('dv50')
        IF_EQUAL_RETURN(guid, MFVideoFormat_DVH1); //     FCC('dvh1')
        IF_EQUAL_RETURN(guid, MFVideoFormat_DVSD); //     FCC('dvsd')
        IF_EQUAL_RETURN(guid, MFVideoFormat_DVSL); //     FCC('dvsl')
        IF_EQUAL_RETURN(guid, MFVideoFormat_H264); //     FCC('H264')
        IF_EQUAL_RETURN(guid, MFVideoFormat_I420); //     FCC('I420')
        IF_EQUAL_RETURN(guid, MFVideoFormat_IYUV); //     FCC('IYUV')
        IF_EQUAL_RETURN(guid, MFVideoFormat_M4S2); //     FCC('M4S2')
        IF_EQUAL_RETURN(guid, MFVideoFormat_MJPG);
        IF_EQUAL_RETURN(guid, MFVideoFormat_MP43); //     FCC('MP43')
        IF_EQUAL_RETURN(guid, MFVideoFormat_MP4S); //     FCC('MP4S')
        IF_EQUAL_RETURN(guid, MFVideoFormat_MP4V); //     FCC('MP4V')
        IF_EQUAL_RETURN(guid, MFVideoFormat_MPG1); //     FCC('MPG1')
        IF_EQUAL_RETURN(guid, MFVideoFormat_MSS1); //     FCC('MSS1')
        IF_EQUAL_RETURN(guid, MFVideoFormat_MSS2); //     FCC('MSS2')
        IF_EQUAL_RETURN(guid, MFVideoFormat_NV11); //     FCC('NV11')
        IF_EQUAL_RETURN(guid, MFVideoFormat_NV12); //     FCC('NV12')
        IF_EQUAL_RETURN(guid, MFVideoFormat_P010); //     FCC('P010')
        IF_EQUAL_RETURN(guid, MFVideoFormat_P016); //     FCC('P016')
        IF_EQUAL_RETURN(guid, MFVideoFormat_P210); //     FCC('P210')
        IF_EQUAL_RETURN(guid, MFVideoFormat_P216); //     FCC('P216')
        IF_EQUAL_RETURN(guid, MFVideoFormat_RGB24); //    D3DFMT_R8G8B8 
        IF_EQUAL_RETURN(guid, MFVideoFormat_RGB32); //    D3DFMT_X8R8G8B8 
        IF_EQUAL_RETURN(guid, MFVideoFormat_RGB555); //   D3DFMT_X1R5G5B5 
        IF_EQUAL_RETURN(guid, MFVideoFormat_RGB565); //   D3DFMT_R5G6B5 
        IF_EQUAL_RETURN(guid, MFVideoFormat_RGB8);
        IF_EQUAL_RETURN(guid, MFVideoFormat_UYVY); //     FCC('UYVY')
        IF_EQUAL_RETURN(guid, MFVideoFormat_v210); //     FCC('v210')
        IF_EQUAL_RETURN(guid, MFVideoFormat_v410); //     FCC('v410')
        IF_EQUAL_RETURN(guid, MFVideoFormat_WMV1); //     FCC('WMV1')
        IF_EQUAL_RETURN(guid, MFVideoFormat_WMV2); //     FCC('WMV2')
        IF_EQUAL_RETURN(guid, MFVideoFormat_WMV3); //     FCC('WMV3')
        IF_EQUAL_RETURN(guid, MFVideoFormat_WVC1); //     FCC('WVC1')
        IF_EQUAL_RETURN(guid, MFVideoFormat_Y210); //     FCC('Y210')
        IF_EQUAL_RETURN(guid, MFVideoFormat_Y216); //     FCC('Y216')
        IF_EQUAL_RETURN(guid, MFVideoFormat_Y410); //     FCC('Y410')
        IF_EQUAL_RETURN(guid, MFVideoFormat_Y416); //     FCC('Y416')
        IF_EQUAL_RETURN(guid, MFVideoFormat_Y41P);
        IF_EQUAL_RETURN(guid, MFVideoFormat_Y41T);
        IF_EQUAL_RETURN(guid, MFVideoFormat_YUY2); //     FCC('YUY2')
        IF_EQUAL_RETURN(guid, MFVideoFormat_YV12); //     FCC('YV12')
        IF_EQUAL_RETURN(guid, MFVideoFormat_YVYU);

        IF_EQUAL_RETURN(guid, MFAudioFormat_PCM); //              WAVE_FORMAT_PCM 
        IF_EQUAL_RETURN(guid, MFAudioFormat_Float); //            WAVE_FORMAT_IEEE_FLOAT 
        IF_EQUAL_RETURN(guid, MFAudioFormat_DTS); //              WAVE_FORMAT_DTS 
        IF_EQUAL_RETURN(guid, MFAudioFormat_Dolby_AC3_SPDIF); //  WAVE_FORMAT_DOLBY_AC3_SPDIF 
        IF_EQUAL_RETURN(guid, MFAudioFormat_DRM); //              WAVE_FORMAT_DRM 
        IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudioV8); //        WAVE_FORMAT_WMAUDIO2 
        IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudioV9); //        WAVE_FORMAT_WMAUDIO3 
        IF_EQUAL_RETURN(guid, MFAudioFormat_WMAudio_Lossless); // WAVE_FORMAT_WMAUDIO_LOSSLESS 
        IF_EQUAL_RETURN(guid, MFAudioFormat_WMASPDIF); //         WAVE_FORMAT_WMASPDIF 
        IF_EQUAL_RETURN(guid, MFAudioFormat_MSP1); //             WAVE_FORMAT_WMAVOICE9 
        IF_EQUAL_RETURN(guid, MFAudioFormat_MP3); //              WAVE_FORMAT_MPEGLAYER3 
        IF_EQUAL_RETURN(guid, MFAudioFormat_MPEG); //             WAVE_FORMAT_MPEG 
        IF_EQUAL_RETURN(guid, MFAudioFormat_AAC); //              WAVE_FORMAT_MPEG_HEAAC 
        IF_EQUAL_RETURN(guid, MFAudioFormat_ADTS); //             WAVE_FORMAT_MPEG_ADTS_AAC 

        return {};
    }

    HW_EXPORT WideString GetMediaTypeDescription(const MFMediaType& mediaType)
    {
        WideString description;

        if (mediaType == nullptr)
        {
            description = L"<NULL>";
            return description;
        }

        auto majorType = mediaType.GetMajorType();

        auto majorTypeStr = GetGUIDNameConst(majorType);
        if (majorTypeStr.size())
        {
            description += majorTypeStr;
            description += L": \n";
        }
        else
        {
            description += majorType.ToString();
            description += L": \n";
        }

        auto attributeCount = mediaType.GetCount();
        

        for (UINT32 i = 0; i < attributeCount; i++)
        {
            auto attributeKey = mediaType.GetItemKeyByIndex(i);
            auto attrType = mediaType.GetItemType(attributeKey);

            
            auto attributeKeyStr = GetGUIDNameConst(attributeKey);
            if (attributeKeyStr.empty())
            {
                attributeKeyStr = attributeKey.ToString();
            }
            
            description += L"    " + attributeKeyStr + L"=";
            switch (attrType)
            {
                case MF_ATTRIBUTE_UINT32:
                {
                    auto Val = mediaType.GetUINT32(attributeKey);
                    

                    description += std::to_wstring(Val);
                    break;
                }
                case MF_ATTRIBUTE_UINT64:
                {
                    auto Val = mediaType.GetUINT64(attributeKey);
                    

                    if (attributeKey == MF_MT_FRAME_SIZE)
                    {
                        description += L"W:" + std::to_wstring(HI32(Val)) + L" H: " + std::to_wstring(LO32(Val));
                    }
                    else if (attributeKey == MF_MT_FRAME_RATE)
                    {
                        // Frame rate is numerator/denominator.
                        description += std::to_wstring(HI32(Val)) + L"/" + std::to_wstring(LO32(Val));
                    }
                    else if (attributeKey == MF_MT_PIXEL_ASPECT_RATIO)
                    {
                        description += std::to_wstring(HI32(Val)) + L":" + std::to_wstring(LO32(Val));
                    }
                    else
                    {
                        description += std::to_wstring(Val);
                    }

                    break;
                }
                case MF_ATTRIBUTE_DOUBLE:
                {
                    auto Val = mediaType.GetDouble(attributeKey);
                    
                    description += std::to_wstring(Val);
                    break;
                }
                case MF_ATTRIBUTE_GUID:
                {
                    

                    auto Val = mediaType.GetGUID(attributeKey);
                    
                    auto valStr = GetGUIDNameConst(Val);
                    if (valStr.empty())
                    {
                        valStr = Val.ToString();
                    }
                    description += valStr;

                    break;
                }
                case MF_ATTRIBUTE_STRING:
                {
                    auto Val = mediaType.GetString(attributeKey);
                    description += Val;


                    break;
                }
                case MF_ATTRIBUTE_BLOB:
                {
                    description += L"<BLOB>";
                    break;
                }
                case MF_ATTRIBUTE_IUNKNOWN:
                {
                    description += L"<UNK>";
                    break;
                }
            }

            description += L"\n";
        }

        return description;
    }

    Attributes::Attributes(const MFAttributes& attributes)
    { 
        Add(attributes);
    }

    void Attributes::Add(const MFAttributes& attributes)
    {
        auto count = attributes.GetCount();
        for(int i = 0; i < count; i++)
        { 
            Add(attributes, i);
        }
    }
    void Attributes::Add(const MFAttributes& attributes, UInt32 index)
    {
        auto key = attributes.GetItemKeyByIndex(index);
        auto attributeType = attributes.GetItemType(key);
        switch (attributeType)
        {
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT32:
                AddInt32(attributes, key);
                break;
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT64:
                AddInt64(attributes, key);
                break;
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_DOUBLE:
                AddDouble(attributes, key);
                break;
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_GUID:
                AddGuid(attributes, key);
                break;
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_STRING:
                AddString(attributes, key);
                break;
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_BLOB:
                AddBlob(attributes, key);
                break;
            case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_IUNKNOWN:
                AddUnknown(attributes, key);
                break;
        }
    }

    void Attributes::AssignTo(const MFAttributes& attributes) const
    {
        for (auto& entry : container_)
        {
            auto* attr = entry.second.get();
            auto attrType = attr->Type();
            switch (attrType)
            {
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT32:
                    AssignToInt32(static_cast<const Int32Attribute*>(attr), attributes);
                    break;
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_UINT64:
                    AssignToInt64(static_cast<const Int64Attribute*>(attr), attributes);
                    break;
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_DOUBLE:
                    AssignToDouble(static_cast<const DoubleAttribute*>(attr), attributes);
                    break;
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_GUID:
                    AssignToGuid(static_cast<const GuidAttribute*>(attr), attributes);
                    break;
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_STRING:
                    AssignToString(static_cast<const StringAttribute*>(attr), attributes);
                    break;
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_BLOB:
                    AssignToBlob(static_cast<const BlobAttribute*>(attr), attributes);
                    break;
                case MF_ATTRIBUTE_TYPE::MF_ATTRIBUTE_IUNKNOWN:
                    AssignToUnknown(static_cast<const UnknownAttribute*>(attr), attributes);
                    break;
            }
        }
    }


    void Attributes::AddInt32(const MFAttributes& attributes, const Guid& key)
    {
        auto value = attributes.GetUINT32(key);
        auto ptr = std::make_shared<Int32Attribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }
    void Attributes::AddInt64(const MFAttributes& attributes, const Guid& key)
    {
        auto value = attributes.GetUINT64(key);
        auto ptr = std::make_shared<Int64Attribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }
    void Attributes::AddDouble(const MFAttributes& attributes, const Guid& key)
    {
        auto value = attributes.GetDouble(key);
        auto ptr = std::make_shared<DoubleAttribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }
    void Attributes::AddGuid(const MFAttributes& attributes, const Guid& key)
    {
        auto value = attributes.GetGUID(key);
        auto ptr = std::make_shared<GuidAttribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }
    void Attributes::AddString(const MFAttributes& attributes, const Guid& key)
    {
        auto value = attributes.GetString(key);
        auto ptr = std::make_shared<StringAttribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }
    void Attributes::AddBlob(const MFAttributes& attributes, const Guid& key)
    {
        auto blobSize = attributes.GetBlobSize(key);
        std::vector<Byte> value;
        value.resize(blobSize);
        attributes.GetBlob(key, value.data(), blobSize);
        auto ptr = std::make_shared<BlobAttribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }
    void Attributes::AddUnknown(const MFAttributes& attributes, const Guid& key)
    {
        auto value = attributes.GetUnknown<Unknown>(key);
        auto ptr = std::make_shared<UnknownAttribute>(key, value);
        container_.insert_or_assign(key, std::move(ptr));
    }

    void Attributes::AssignToInt32(const Int32Attribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto value = attribute->Value();
        attributes.SetUINT32(key, value);
    }
    void Attributes::AssignToInt64(const Int64Attribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto value = attribute->Value();
        attributes.SetUINT64(key, value);
    }
    void Attributes::AssignToDouble(const DoubleAttribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto value = attribute->Value();
        attributes.SetDouble(key, value);
    }
    void Attributes::AssignToGuid(const GuidAttribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto& value = attribute->Value();
        attributes.SetGUID(key, value);
    }
    void Attributes::AssignToString(const StringAttribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto& value = attribute->Value();
        attributes.SetString(key, value);
    }
    void Attributes::AssignToBlob(const BlobAttribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto& value = attribute->Value();
        attributes.SetBlob(key, value);
    }
    void Attributes::AssignToUnknown(const UnknownAttribute* attribute, const MFAttributes& attributes)
    {
        auto& key = attribute->Key();
        auto& value = attribute->Value();
        attributes.SetUnknown(key, value.GetInterfacePointer<IUnknown>());
    }



}