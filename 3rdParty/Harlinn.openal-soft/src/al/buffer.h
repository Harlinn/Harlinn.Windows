#ifndef AL_BUFFER_H
#define AL_BUFFER_H

#include <atomic>

#include "AL/al.h"

#include "albyte.h"
#include "almalloc.h"
#include "atomic.h"
#include "buffer_storage.h"
#include "inprogext.h"
#include "vector.h"


/* User formats */
enum UserFmtType : unsigned char {
    UserFmtUByte = FmtUByte,
    UserFmtShort = FmtShort,
    UserFmtFloat = FmtFloat,
    UserFmtMulaw = FmtMulaw,
    UserFmtAlaw = FmtAlaw,
    UserFmtDouble = FmtDouble,

    UserFmtIMA4 = 128,
    UserFmtMSADPCM,
};
enum UserFmtChannels : unsigned char {
    UserFmtMono = FmtMono,
    UserFmtStereo = FmtStereo,
    UserFmtRear = FmtRear,
    UserFmtQuad = FmtQuad,
    UserFmtX51 = FmtX51,
    UserFmtX61 = FmtX61,
    UserFmtX71 = FmtX71,
    UserFmtBFormat2D = FmtBFormat2D,
    UserFmtBFormat3D = FmtBFormat3D,
};


struct ALbuffer : public BufferStorage {
    ALbitfieldSOFT Access{0u};

    al::vector<al::byte,16> mData;

    UserFmtType OriginalType{UserFmtShort};
    ALuint OriginalSize{0};
    ALuint OriginalAlign{0};

    ALuint UnpackAlign{0};
    ALuint PackAlign{0};
    ALuint UnpackAmbiOrder{1};

    ALbitfieldSOFT MappedAccess{0u};
    ALsizei MappedOffset{0};
    ALsizei MappedSize{0};

    ALuint mLoopStart{0u};
    ALuint mLoopEnd{0u};

    /* Number of times buffer was attached to a source (deletion can only occur when 0) */
    RefCount ref{0u};

    /* Self ID */
    ALuint id{0};

    DISABLE_ALLOC()
};

#endif
