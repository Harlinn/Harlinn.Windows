/******************************************************************************
 
gif_lib.h - service library for decoding and encoding GIF images
                                                                             
SPDX-License-Identifier: MIT

*****************************************************************************/

#ifndef _GIF_LIB_H_
#define _GIF_LIB_H_ 1

#include "hgifdef.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GIFLIB_MAJOR 5
#define GIFLIB_MINOR 2
#define GIFLIB_RELEASE 1

#define GIF_ERROR   0
#define GIF_OK      1

#include <stddef.h>
#include <stdbool.h>

#define GIF_STAMP "GIFVER"          /* First chars in file - GIF stamp.  */
#define GIF_STAMP_LEN sizeof(GIF_STAMP) - 1
#define GIF_VERSION_POS 3           /* Version first character in stamp. */
#define GIF87_STAMP "GIF87a"        /* First chars in file - GIF stamp.  */
#define GIF89_STAMP "GIF89a"        /* First chars in file - GIF stamp.  */

typedef unsigned char GifPixelType;
typedef unsigned char *GifRowType;
typedef unsigned char GifByteType;
typedef unsigned int GifPrefixType;
typedef int GifWord;

typedef struct GifColorType {
    GifByteType Red, Green, Blue;
} GifColorType;

typedef struct ColorMapObject {
    int ColorCount;
    int BitsPerPixel;
    bool SortFlag;
    GifColorType *Colors;    /* on malloc(3) heap */
} ColorMapObject;

typedef struct GifImageDesc {
    GifWord Left, Top, Width, Height;   /* Current image dimensions. */
    bool Interlace;                     /* Sequential/Interlaced lines. */
    ColorMapObject *ColorMap;           /* The local color map */
} GifImageDesc;

typedef struct ExtensionBlock {
    int ByteCount;
    GifByteType *Bytes; /* on malloc(3) heap */
    int Function;       /* The block function code */
#define CONTINUE_EXT_FUNC_CODE    0x00    /* continuation subblock */
#define COMMENT_EXT_FUNC_CODE     0xfe    /* comment */
#define GRAPHICS_EXT_FUNC_CODE    0xf9    /* graphics control (GIF89) */
#define PLAINTEXT_EXT_FUNC_CODE   0x01    /* plaintext */
#define APPLICATION_EXT_FUNC_CODE 0xff    /* application block (GIF89) */
} ExtensionBlock;

typedef struct SavedImage {
    GifImageDesc ImageDesc;
    GifByteType *RasterBits;         /* on malloc(3) heap */
    int ExtensionBlockCount;         /* Count of extensions before image */    
    ExtensionBlock *ExtensionBlocks; /* Extensions before image */    
} SavedImage;

typedef struct GifFileType {
    GifWord SWidth, SHeight;         /* Size of virtual canvas */
    GifWord SColorResolution;        /* How many colors can we generate? */
    GifWord SBackGroundColor;        /* Background color for virtual canvas */
    GifByteType AspectByte;	     /* Used to compute pixel aspect ratio */
    ColorMapObject *SColorMap;       /* Global colormap, NULL if nonexistent. */
    int ImageCount;                  /* Number of current image (both APIs) */
    GifImageDesc Image;              /* Current image (low-level API) */
    SavedImage *SavedImages;         /* Image sequence (high-level API) */
    int ExtensionBlockCount;         /* Count extensions past last image */
    ExtensionBlock *ExtensionBlocks; /* Extensions past last image */    
    int Error;			     /* Last error condition reported */
    void *UserData;                  /* hook to attach user data (TVT) */
    void *Private;                   /* Don't mess with this! */
} GifFileType;

#define GIF_ASPECT_RATIO(n)	((n)+15.0/64.0)

typedef enum {
    UNDEFINED_RECORD_TYPE,
    SCREEN_DESC_RECORD_TYPE,
    IMAGE_DESC_RECORD_TYPE, /* Begin with ',' */
    EXTENSION_RECORD_TYPE,  /* Begin with '!' */
    TERMINATE_RECORD_TYPE   /* Begin with ';' */
} GifRecordType;

/* func type to read gif data from arbitrary sources (TVT) */
typedef int (*InputFunc) (GifFileType *, GifByteType *, int);

/* func type to write gif data to arbitrary targets.
 * Returns count of bytes written. (MRB)
 */
typedef int (*OutputFunc) (GifFileType *, const GifByteType *, int);

/******************************************************************************
 GIF89 structures
******************************************************************************/

typedef struct GraphicsControlBlock {
    int DisposalMode;
#define DISPOSAL_UNSPECIFIED      0       /* No disposal specified. */
#define DISPOSE_DO_NOT            1       /* Leave image in place */
#define DISPOSE_BACKGROUND        2       /* Set area too background color */
#define DISPOSE_PREVIOUS          3       /* Restore to previous content */
    bool UserInputFlag;      /* User confirmation required before disposal */
    int DelayTime;           /* pre-display delay in 0.01sec units */
    int TransparentColor;    /* Palette index for transparency, -1 if none */
#define NO_TRANSPARENT_COLOR	-1
} GraphicsControlBlock;

/******************************************************************************
 GIF encoding routines
******************************************************************************/

/* Main entry points */
HGIF_EXPORT GifFileType *EGifOpenFileName(const char *GifFileName,
                              const bool GifTestExistence, int *Error);
HGIF_EXPORT GifFileType *EGifOpenFileHandle(const int GifFileHandle, int *Error);
HGIF_EXPORT GifFileType *EGifOpen(void *userPtr, OutputFunc writeFunc, int *Error);
HGIF_EXPORT int EGifSpew(GifFileType * GifFile);
HGIF_EXPORT const char *EGifGetGifVersion(GifFileType *GifFile); /* new in 5.x */
HGIF_EXPORT int EGifCloseFile(GifFileType *GifFile, int *ErrorCode);

#define E_GIF_SUCCEEDED          0
#define E_GIF_ERR_OPEN_FAILED    1    /* And EGif possible errors. */
#define E_GIF_ERR_WRITE_FAILED   2
#define E_GIF_ERR_HAS_SCRN_DSCR  3
#define E_GIF_ERR_HAS_IMAG_DSCR  4
#define E_GIF_ERR_NO_COLOR_MAP   5
#define E_GIF_ERR_DATA_TOO_BIG   6
#define E_GIF_ERR_NOT_ENOUGH_MEM 7
#define E_GIF_ERR_DISK_IS_FULL   8
#define E_GIF_ERR_CLOSE_FAILED   9
#define E_GIF_ERR_NOT_WRITEABLE  10

/* These are legacy.  You probably do not want to call them directly */
HGIF_EXPORT int EGifPutScreenDesc(GifFileType *GifFile,
                      const int GifWidth, const int GifHeight, 
		      const int GifColorRes,
                      const int GifBackGround,
                      const ColorMapObject *GifColorMap);
HGIF_EXPORT int EGifPutImageDesc(GifFileType *GifFile,
		     const int GifLeft, const int GifTop,
                     const int GifWidth, const int GifHeight, 
		     const bool GifInterlace,
                     const ColorMapObject *GifColorMap);
HGIF_EXPORT void EGifSetGifVersion(GifFileType *GifFile, const bool gif89);
HGIF_EXPORT int EGifPutLine(GifFileType *GifFile, GifPixelType *GifLine,
                int GifLineLen);
HGIF_EXPORT int EGifPutPixel(GifFileType *GifFile, const GifPixelType GifPixel);
HGIF_EXPORT int EGifPutComment(GifFileType *GifFile, const char *GifComment);
HGIF_EXPORT int EGifPutExtensionLeader(GifFileType *GifFile, const int GifExtCode);
HGIF_EXPORT int EGifPutExtensionBlock(GifFileType *GifFile,
                         const int GifExtLen, const void *GifExtension);
HGIF_EXPORT int EGifPutExtensionTrailer(GifFileType *GifFile);
HGIF_EXPORT int EGifPutExtension(GifFileType *GifFile, const int GifExtCode,
		     const int GifExtLen,
                     const void *GifExtension);
HGIF_EXPORT int EGifPutCode(GifFileType *GifFile, int GifCodeSize,
                const GifByteType *GifCodeBlock);
HGIF_EXPORT int EGifPutCodeNext(GifFileType *GifFile,
                    const GifByteType *GifCodeBlock);

/******************************************************************************
 GIF decoding routines
******************************************************************************/

/* Main entry points */
HGIF_EXPORT GifFileType *DGifOpenFileName(const char *GifFileName, int *Error);
HGIF_EXPORT GifFileType *DGifOpenFileHandle(int GifFileHandle, int *Error);
HGIF_EXPORT int DGifSlurp(GifFileType * GifFile);
HGIF_EXPORT GifFileType *DGifOpen(void *userPtr, InputFunc readFunc, int *Error);    /* new one (TVT) */
HGIF_EXPORT int DGifCloseFile(GifFileType * GifFile, int *ErrorCode);

#define D_GIF_SUCCEEDED          0
#define D_GIF_ERR_OPEN_FAILED    101    /* And DGif possible errors. */
#define D_GIF_ERR_READ_FAILED    102
#define D_GIF_ERR_NOT_GIF_FILE   103
#define D_GIF_ERR_NO_SCRN_DSCR   104
#define D_GIF_ERR_NO_IMAG_DSCR   105
#define D_GIF_ERR_NO_COLOR_MAP   106
#define D_GIF_ERR_WRONG_RECORD   107
#define D_GIF_ERR_DATA_TOO_BIG   108
#define D_GIF_ERR_NOT_ENOUGH_MEM 109
#define D_GIF_ERR_CLOSE_FAILED   110
#define D_GIF_ERR_NOT_READABLE   111
#define D_GIF_ERR_IMAGE_DEFECT   112
#define D_GIF_ERR_EOF_TOO_SOON   113

/* These are legacy.  You probably do not want to call them directly */
HGIF_EXPORT int DGifGetScreenDesc(GifFileType *GifFile);
HGIF_EXPORT int DGifGetRecordType(GifFileType *GifFile, GifRecordType *GifType);
HGIF_EXPORT int DGifGetImageHeader(GifFileType *GifFile);
HGIF_EXPORT int DGifGetImageDesc(GifFileType *GifFile);
HGIF_EXPORT int DGifGetLine(GifFileType *GifFile, GifPixelType *GifLine, int GifLineLen);
HGIF_EXPORT int DGifGetPixel(GifFileType *GifFile, GifPixelType GifPixel);
HGIF_EXPORT int DGifGetExtension(GifFileType *GifFile, int *GifExtCode,
                     GifByteType **GifExtension);
HGIF_EXPORT int DGifGetExtensionNext(GifFileType *GifFile, GifByteType **GifExtension);
HGIF_EXPORT int DGifGetCode(GifFileType *GifFile, int *GifCodeSize,
                GifByteType **GifCodeBlock);
HGIF_EXPORT int DGifGetCodeNext(GifFileType *GifFile, GifByteType **GifCodeBlock);
HGIF_EXPORT int DGifGetLZCodes(GifFileType *GifFile, int *GifCode);
HGIF_EXPORT const char *DGifGetGifVersion(GifFileType *GifFile);


/******************************************************************************
 Error handling and reporting.
******************************************************************************/
HGIF_EXPORT extern const char *GifErrorString(int ErrorCode);     /* new in 2012 - ESR */

/*****************************************************************************
 Everything below this point is new after version 1.2, supporting `slurp
 mode' for doing I/O in two big belts with all the image-bashing in core.
******************************************************************************/

/******************************************************************************
 Color map handling from gif_alloc.c
******************************************************************************/

HGIF_EXPORT extern ColorMapObject *GifMakeMapObject(int ColorCount,
                                     const GifColorType *ColorMap);
HGIF_EXPORT extern void GifFreeMapObject(ColorMapObject *Object);
HGIF_EXPORT extern ColorMapObject *GifUnionColorMap(const ColorMapObject *ColorIn1,
                                     const ColorMapObject *ColorIn2,
                                     GifPixelType ColorTransIn2[]);
HGIF_EXPORT extern int GifBitSize(int n);

/******************************************************************************
 Support for the in-core structures allocation (slurp mode).              
******************************************************************************/

HGIF_EXPORT extern void GifApplyTranslation(SavedImage *Image, GifPixelType Translation[]);
HGIF_EXPORT extern int GifAddExtensionBlock(int *ExtensionBlock_Count,
				ExtensionBlock **ExtensionBlocks, 
				int Function, 
				unsigned int Len, unsigned char ExtData[]);
HGIF_EXPORT extern void GifFreeExtensions(int *ExtensionBlock_Count,
			      ExtensionBlock **ExtensionBlocks);
HGIF_EXPORT extern SavedImage *GifMakeSavedImage(GifFileType *GifFile,
                                  const SavedImage *CopyFrom);
HGIF_EXPORT extern void GifFreeSavedImages(GifFileType *GifFile);

/******************************************************************************
 5.x functions for GIF89 graphics control blocks
******************************************************************************/

HGIF_EXPORT int DGifExtensionToGCB(const size_t GifExtensionLength,
		       const GifByteType *GifExtension,
		       GraphicsControlBlock *GCB);
HGIF_EXPORT size_t EGifGCBToExtension(const GraphicsControlBlock *GCB,
		       GifByteType *GifExtension);

HGIF_EXPORT int DGifSavedExtensionToGCB(GifFileType *GifFile,
			    int ImageIndex, 
			    GraphicsControlBlock *GCB);
HGIF_EXPORT int EGifGCBToSavedExtension(const GraphicsControlBlock *GCB,
			    GifFileType *GifFile, 
			    int ImageIndex);

/******************************************************************************
 The library's internal utility font                          
******************************************************************************/

#define GIF_FONT_WIDTH  8
#define GIF_FONT_HEIGHT 8
extern const unsigned char GifAsciiTable8x8[][GIF_FONT_WIDTH];

HGIF_EXPORT extern void GifDrawText8x8(SavedImage *Image,
                     const int x, const int y,
                     const char *legend, const int color);

HGIF_EXPORT extern void GifDrawBox(SavedImage *Image,
                    const int x, const int y,
                    const int w, const int d, const int color);

HGIF_EXPORT extern void GifDrawRectangle(SavedImage *Image,
                   const int x, const int y,
                   const int w, const int d, const int color);

HGIF_EXPORT extern void GifDrawBoxedText8x8(SavedImage *Image,
                          const int x, const int y,
                          const char *legend,
                          const int border, const int bg, const int fg);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* _GIF_LIB_H */

/* end */
