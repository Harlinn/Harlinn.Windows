#pragma once
#ifndef __HWSTDCTRLS_H__
#define __HWSTDCTRLS_H__

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


#include <HWControl.h>
#include <HWMenu.h>
#include <HCCDateTime.h>


namespace Harlinn::Windows
{
    class Range
    {
        UINT start_;
        UINT end_;
    public:
        constexpr Range( ) noexcept
            : start_( 0 ), end_( 0 )
        {
        }

        constexpr Range( UINT start, UINT end ) noexcept
            : start_( start ), end_( end )
        {
            if ( end_ < start_ )
            {
                std::swap( start_, end_ );
            }
        }

        constexpr UINT Start( ) const noexcept { return start_; }
        constexpr void SetStart( UINT value ) noexcept { start_ = value; if ( end_ < start_ ) { end_ = start_; } }
        constexpr UINT End( ) const noexcept { return end_; }
        constexpr void SetEnd( UINT value ) { end_ = value; if ( end_ < start_ ) { start_ = end_; } }

        constexpr void SetRange( UINT start, UINT end ) noexcept
        {
            start_ = start;
            end_ = end;
            if ( end_ < start_ )
            {
                std::swap( start_, end_ );
            }
        }

        constexpr UINT Length( ) const noexcept { return end_ - start_; }


    };


    enum class CheckState : int
    {
        Unchecked = 0x0000,
        Checked = 0x0001,
        Indeterminate = 0x0002
    };

    /// <summary>
    /// Specifies the palette for an ImageList
    /// </summary>
    enum class ImageListColor : int
    {
        /// <summary>
        /// Use the default behavior if none of the other flags is specified. 
        /// Typically, the default is Color4, but for older display drivers, 
        /// the default is ColorDDB.
        /// </summary>
        ColorDefault = 0x00000000,
        /// <summary>
        /// Use a 4-bit (16-color) device-independent bitmap (DIB) section as 
        /// the bitmap for the image list.
        /// </summary>
        Color4 = 0x00000004,
        /// <summary>
        /// Use an 8-bit DIB section. The colors used for the color table are 
        /// the same colors as the halftone palette.
        /// </summary>
        Color8 = 0x00000008,
        /// <summary>
        /// Use a 16-bit (32/64k-color) DIB section.
        /// </summary>
        Color16 = 0x00000010,
        /// <summary>
        /// Use a 24-bit DIB section.
        /// </summary>
        Color24 = 0x00000018,
        /// <summary>
        /// Use a 32-bit DIB section.
        /// </summary>
        Color32 = 0x00000020,
        /// <summary>
        /// Use a device-dependent bitmap.
        /// </summary>
        ColorDDB = 0x000000FE
    };

    /// <summary>
    /// Specifies the flags for an ImageList
    /// </summary>
    enum class ImageListFlags : int
    {
        /// <summary>
        /// Use a mask. The image list contains two bitmaps, one of which 
        /// is a monochrome bitmap used as a mask. If this value is not 
        /// included, the image list contains only one bitmap.
        /// </summary>
        Mask = 0x00000001,
        /// <summary>
        /// Mirror the icons contained, if the process is mirrored
        /// </summary>
        Mirror = 0x00002000,
        /// <summary>
        /// Causes the mirroring code to mirror each item when inserting a 
        /// set of images, versus the whole strip.
        /// </summary>
        PerItemMirror = 0x00008000,
        /// <summary>
        /// Imagelist should accept smaller than set images and apply 
        /// original size based on image added.
        /// </summary>
        OriginalSize = 0x00010000,
        /// <summary>
        /// Imagelist should enable use of the high quality scaler.
        /// </summary>
        HighQualityScale = 0x00020000
    };
    DEFINE_ENUM_FLAG_OPERATORS( ImageListFlags )

    /// <summary>
    /// Flags used for drawing ImageList elements
    /// </summary>
    enum class ImageListDrawFlags : int
    {
        Normal = 0x00000000,
        Transparent = 0x00000001,
        Mask = 0x00000010,
        Image = 0x00000020,
        Rop = 0x00000040,
        /// <summary>
        /// Draws the image, blending 25 percent with the 
        /// system highlight color, or the blend color specified by rgbFg. 
        /// This value has no effect if the image list does not contain a mask.
        /// </summary>
        Blend25 = 0x00000002,
        /// <summary>
        /// Draws the image, blending 50 percent with the 
        /// system highlight color, or the blend color specified by rgbFg. 
        /// This value has no effect if the image list does not contain a mask.
        /// </summary>
        Blend50 = 0x00000004,

        OverlayMask = 0x00000F00,
        PreserveAlpha = 0x00001000,
        Scale = 0x00002000,
        DpiScale = 0x00004000,
        Async = 0x00008000,
        Selected = 0x00000004,
        Focus = 0x00000002,
        Blend = 0x00000004
    };
    DEFINE_ENUM_FLAG_OPERATORS( ImageListDrawFlags )

    /// <summary>
    /// Flags for loading an ImageList
    /// </summary>
    enum class ImageListLoadFlags : int
    {
        /// <summary>
        /// Uses the color format of the display.
        /// </summary>
        DefaultColor = 0x00000000,
        /// <summary>
        /// Loads the image in black and white.
        /// </summary>
        Monochrome = 0x00000001,
        /// <summary>
        /// Loads the image from the file specified by the name parameter.
        /// </summary>
        LoadFromFile = 0x00000010,
        /// <summary>
        /// Retrieves the color value of the first pixel in the image and 
        /// replaces the corresponding entry in the color table with the default 
        /// window color (the COLOR_WINDOW display color). All pixels in the 
        /// image that use that color become the default window value color. 
        /// This value applies only to images that have a corresponding color table.
        /// </summary>
        LoadTransparent = 0x00000020,
        /// <summary>
        /// Uses the width or height specified by the system metric values 
        /// for cursors and icons if the cx parameter is set to zero. If 
        /// this value is not specified and cx is set to zero, the function 
        /// sets the size to the one specified in the resource. If the resource 
        /// contains multiple images, the function sets the size to that of 
        /// the first image.
        /// </summary>
        DefaultSize = 0x00000040,
        /// <summary>
        /// Searches the color table for the image and replaces the following 
        /// shades of gray with the corresponding three-dimensional color:
        /// <ul>
        /// <li>Dk Gray: RGB(128, 128, 128)COLOR_3DSHADOW</li>
        /// <li>Gray: RGB(192, 192, 192)COLOR_3DFACE</li>
        /// <li>Lt Gray: RGB(223, 223, 223)COLOR_3DLIGHT</li>
        /// </ul>
        /// </summary>
        LoadMap3DColors = 0x00001000,
        /// <summary>
        /// Causes the function to return a DIB section bitmap rather than a 
        /// compatible bitmap when the uType parameter specifies IMAGE_BITMAP. 
        /// LR_CREATEDIBSECTION is useful for loading a bitmap without mapping 
        /// it to the colors of the display device.
        /// </summary>
        CreateDibSection = 0x00002000,
        /// <summary>
        /// Shares the image handle if the image is loaded multiple times. 
        /// Do not use this value for images that have nontraditional sizes 
        /// that might change after loading or for images that are loaded 
        /// from a file.
        /// </summary>
        Shared = 0x00008000
    };
    DEFINE_ENUM_FLAG_OPERATORS( ImageListLoadFlags )

    // --------------------------------------------------------------------
    // ImageList
    // --------------------------------------------------------------------
    class ImageList : public Handle<ImageList, HIMAGELIST>
    {
        static HIMAGELIST CreateImageList( int elementWidth, int elementHeight, int count, int growBy, ImageListFlags flags, ImageListColor color )
        {
            int flagsValue = int( flags ) | int( color );
            HIMAGELIST result = ImageList_Create( elementWidth, elementHeight, flagsValue, count, growBy );
            if ( !result )
            {
                ThrowLastOSError( );
            }
            return result;
        }
    public:
        using Base = Handle<ImageList, HIMAGELIST>;
        constexpr ImageList( ) noexcept
        {
        }

        constexpr explicit ImageList( HIMAGELIST handle, bool closeHandle = true ) noexcept
            : Base( handle, closeHandle )
        { }

        /// <summary>
        /// Creates a new image list
        /// </summary>
        /// <param name="elementWidth">The width, in pixels, of each image</param>
        /// <param name="elementHeight">The height, in pixels, of each image</param>
        /// <param name="count">The number of images that the image list initially contains.</param>
        /// <param name="growBy">The number of images by which the image list can grow when the system needs to make room for new images. This parameter represents the number of new images that the resized image list can contain.</param>
        /// <param name="flags">A set of bit flags that specify the type of image list to create.</param>
        /// <param name="color">Specifies the color-depth of the imagelist</param>
        ImageList( int elementWidth, int elementHeight, int count, int growBy, ImageListFlags flags, ImageListColor color )
            : Base( CreateImageList( elementWidth, elementHeight, count, growBy, flags, color ), true )
        { }

        /// <summary>
        /// Destroys the image list.
        /// </summary>
        void Close( ) noexcept
        {
            if ( OwnsHandle( ) )
            {
                ImageList_Destroy( Value( ) );
                Base::SetValue( nullptr, false );
            }
        }

        /// <summary>
        /// Adds an image or images to an image list.
        /// </summary>
        /// <param name="bitmap">A handle to the bitmap that contains the image or images. The number of images is inferred from the width of the bitmap.</param>
        /// <returns>Returns the index of the first new image</returns>
        int Add( const BitmapHandle& bitmap ) const
        {
            auto result = ImageList_Add( Value( ), bitmap, nullptr );
            if ( result < 0 )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        /// <summary>
        /// Adds an image or images to an image list.
        /// </summary>
        /// <param name="bitmap">A handle to the bitmap that contains the image or images. The number of images is inferred from the width of the bitmap.</param>
        /// <param name="mask">A handle to the bitmap that contains the mask. If no mask is used with the image list, this parameter is ignored.</param>
        /// <returns>Returns the index of the first new image</returns>
        int Add( const BitmapHandle& bitmap, const BitmapHandle& mask ) const
        {
            auto result = ImageList_Add( Value( ), bitmap, mask );
            if ( result < 0 )
            {
                ThrowLastOSError( );
            }
            return result;
        }

        /// <summary>
        /// Adds an image or images to an image list, generating a mask from the specified bitmap.
        /// </summary>
        /// <param name="bitmap">A handle to the bitmap that contains one or more images. The number of images is inferred from the width of the bitmap.</param>
        /// <param name="maskColor">The color used to generate the mask. Each pixel of this color in the specified bitmap is changed to black, and the corresponding bit in the mask is set to 1.</param>
        /// <returns>Returns the index of the first new image</returns>
        int Add( const BitmapHandle& bitmap, COLORREF maskColor ) const
        {
            auto result = ImageList_AddMasked( Value( ), bitmap, maskColor );
            if ( result < 0 )
            {
                ThrowLastOSError( );
            }
            return result;
        }
        /// <summary>
        /// The source image is copied to the destination image's index. This operation results in multiple instances of a given image
        /// </summary>
        /// <param name="indexOfDestinationImage">The zero-based index of the image to be used as the destination of the copy operation.</param>
        /// <param name="indexOfSourceImage">The zero-based index of the image to be used as the source of the copy operation.</param>
        void Move( int indexOfDestinationImage, int indexOfSourceImage ) const
        {
            if ( indexOfDestinationImage != indexOfSourceImage )
            {
                if ( ImageList_Copy( Value( ), indexOfDestinationImage, Value( ), indexOfSourceImage, ILCF_MOVE ) == 0 )
                {
                    ThrowLastOSError( );
                }
            }
        }
        /// <summary>
        /// The source and destination images exchange positions within the image list.
        /// </summary>
        /// <param name="indexOfFirstImage">The zero-based index of the first image</param>
        /// <param name="indexOfSecondImage">The zero-based index of the second image</param>
        void Swap( int indexOfFirstImage, int indexOfSecondImage ) const
        {
            if ( indexOfFirstImage != indexOfSecondImage )
            {
                if ( ImageList_Copy( Value( ), indexOfFirstImage, Value( ), indexOfSecondImage, ILCF_SWAP ) == 0 )
                {
                    ThrowLastOSError( );
                }
            }
        }

        /// <summary>
        /// Creates a duplicate of an existing image list.
        /// </summary>
        /// <returns>the duplicate</returns>
        ImageList Clone( ) const
        {
            HIMAGELIST hImageList = ImageList_Duplicate( Value( ) );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, true );
            return result;
        }

        /// <summary>
        /// Begins dragging an image
        /// </summary>
        /// <param name="indexOfTrackImage">The index of the image to drag.</param>
        /// <param name="dxHotspot">The x-coordinate of the location of the drag position relative to the upper-left corner of the image.</param>
        /// <param name="dyHotspot">The y-coordinate of the location of the drag position relative to the upper-left corner of the image.</param>
        void BeginDrag( int indexOfTrackImage, int dxHotspot, int dyHotspot ) const
        {
            if ( ImageList_BeginDrag( Value( ), indexOfTrackImage, dxHotspot, dyHotspot ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Begins dragging an image
        /// </summary>
        /// <param name="indexOfTrackImage">The index of the image to drag.</param>
        /// <param name="hotspot">The x and y coordinates of the location of the drag position relative to the upper-left corner of the image.</param>
        void BeginDrag( int indexOfTrackImage, const POINT& hotspot ) const
        {
            BeginDrag( indexOfTrackImage, hotspot.x, hotspot.y );
        }
        /// <summary>
        /// Begins dragging an image
        /// </summary>
        /// <param name="indexOfTrackImage">The index of the image to drag.</param>
        /// <param name="hotspot">The x and y coordinates of the location of the drag position relative to the upper-left corner of the image.</param>
        void BeginDrag( int indexOfTrackImage, const Point& hotspot ) const
        {
            BeginDrag( indexOfTrackImage, hotspot.X(), hotspot.Y() );
        }

        /// <summary>
        /// Displays the drag image at the specified position within the window.
        /// </summary>
        /// <param name="hwndLock">A handle to the window that owns the drag image.</param>
        /// <param name="x">The x-coordinate at which to display the drag image. The coordinate is relative to the upper-left corner of the window, not the client area.</param>
        /// <param name="y">The y-coordinate at which to display the drag image. The coordinate is relative to the upper-left corner of the window, not the client area.</param>
        static void DragEnter( HWND hwndLock, int x, int y ) 
        {
            if ( ImageList_DragEnter( hwndLock, x, y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Displays the drag image at the specified position within the control.
        /// </summary>
        /// <param name="control">The control that owns the drag image.</param>
        /// <param name="x">The x-coordinate at which to display the drag image. The coordinate is relative to the upper-left corner of the control, not the client area.</param>
        /// <param name="y">The y-coordinate at which to display the drag image. The coordinate is relative to the upper-left corner of the control, not the client area.</param>
        static void DragEnter( Control& control, int x, int y )
        {
            DragEnter( control.GetHandle( ), x, y );
        }
        /// <summary>
        /// Unlocks the specified window and hides the drag image, allowing the window to be updated.
        /// </summary>
        /// <param name="hwndLock">A handle to the window that owns the drag image</param>
        static void DragLeave( HWND hwndLock )
        {
            if ( ImageList_DragLeave( hwndLock ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Unlocks the specified control and hides the drag image, allowing the control to be updated.
        /// </summary>
        /// <param name="control">The Control that owns the drag image</param>
        static void DragLeave( Control& control )
        {
            DragLeave( control.GetHandle( ) );
        }

        /// <summary>
        /// Moves the image that is being dragged during a drag-and-drop 
        /// operation. This function is typically called in response to a 
        /// WM_MOUSEMOVE message.
        /// </summary>
        /// <param name="x">The x-coordinate at which to display the drag image. The coordinate is relative to the upper-left corner of the window, not the client area.</param>
        /// <param name="y">The y-coordinate at which to display the drag image. The coordinate is relative to the upper-left corner of the window, not the client area.</param>
        static void DragMove( int x, int y )
        {
            if ( ImageList_DragMove( x, y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Shows or hides the image being dragged.
        /// </summary>
        /// <param name="showImage">A value specifying whether to show or hide the image being dragged. Specify true to show the image or false to hide the image.</param>
        static void DragShowNolock( bool showImage )
        {
            if ( ImageList_DragShowNolock( showImage ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Ends a drag operation.
        /// </summary>
        static void EndDrag( )
        {
            ImageList_EndDrag( );
        }
        /// <summary>
        /// Retrieves the temporary image list that is used for the drag image. 
        /// The function also retrieves the current drag position and the offset 
        /// of the drag image relative to the drag position.
        /// </summary>
        /// <param name="ppt">A pointer to a POINT structure that receives the current drag position. Can be nullptr.</param>
        /// <param name="pptHotspot">A pointer to a POINT structure that receives the offset of the drag image relative to the drag position. Can be nullptr.</param>
        /// <remarks>
        /// The temporary image list is destroyed when the EndDrag function is called. 
        /// To begin a drag operation, use the ImageList::BeginDrag function.
        /// <remarks>
        /// <returns>Returns the handle to the image list</returns>
        static ImageList GetDragImage( POINT* ppt, POINT* pptHotspot )
        {
            HIMAGELIST hImageList = ImageList_GetDragImage( ppt, pptHotspot );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, false );
            return result;
        }

        /// <summary>
        /// Retrieves the temporary image list that is used for the drag image. 
        /// The function also retrieves the current drag position and the offset 
        /// of the drag image relative to the drag position.
        /// </summary>
        /// <param name="ppt">A pointer to a Point object that receives the current drag position. Can be nullptr.</param>
        /// <param name="pptHotspot">A pointer to a Point object that receives the offset of the drag image relative to the drag position. Can be nullptr.</param>
        /// <remarks>
        /// The temporary image list is destroyed when the EndDrag function is called. 
        /// To begin a drag operation, use the ImageList::BeginDrag function.
        /// <remarks>
        /// <returns>Returns the handle to the image list</returns>
        static ImageList GetDragImage( Point* ppt, Point* pptHotspot )
        {
            return GetDragImage( ( POINT* )ppt, ( POINT* )pptHotspot );
        }

        /// <summary>
        /// Draws an image list item in the specified device context.
        /// </summary>
        /// <param name="indexOfImage">The index of the image to draw.</param>
        /// <param name="hDC">A handle to the destination device context.</param>
        /// <param name="x">The x-coordinate at which to draw within the specified device context.</param>
        /// <param name="y">The y-coordinate at which to draw within the specified device context.</param>
        /// <param name="flags">The drawing style and, optionally, the overlay image.</param>
        void Draw( int indexOfImage, HDC hDC, int x, int y, ImageListDrawFlags flags ) const
        {
            if ( ImageList_Draw( Value( ), indexOfImage, hDC, x, y, UINT( flags ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Draws an image list item in the specified device context. The function uses the specified drawing style and blends the image with the specified color.
        /// </summary>
        /// <param name="indexOfImage">The index of the image to draw.</param>
        /// <param name="hDC">A handle to the destination device context.</param>
        /// <param name="x">The x-coordinate at which to draw within the specified device context.</param>
        /// <param name="y">The y-coordinate at which to draw within the specified device context.</param>
        /// <param name="dx">The width of the portion of the image to draw relative to the upper-left corner of the image. If dx and dy are zero, the function draws the entire image. The function does not ensure that the parameters are valid.</param>
        /// <param name="dy">The height of the portion of the image to draw, relative to the upper-left corner of the image. If dx and dy are zero, the function draws the entire image. The function does not ensure that the parameters are valid.</param>
        /// <param name="background">
        /// The background color of the image. This parameter can be an application-defined RGB value or one of the following values:
        /// <ul>
        /// <li>CLR_NONE: No background color. The image is drawn transparently.</li>
        /// <li>CLR_DEFAULT: The default background color. The image is drawn using the background color of the image list.</li>
        /// </ul>
        /// </param>
        /// <param name="foreground">
        /// The foreground color of the image. This parameter can be an application-defined RGB value or one of the following values:
        /// <ul>
        /// <li>CLR_NONE: No blend color. The image is blended with the color of the destination device context.</li>
        /// <li>CLR_DEFAULT: The default foreground color. The image is drawn using the system highlight color as the foreground color.</li>
        /// </ul>
        /// </param>
        /// <param name="flags"></param>
        void Draw( int indexOfImage, HDC hDC, int x, int y, int dx, int dy, COLORREF background, COLORREF foreground, ImageListDrawFlags flags ) const
        {
            if ( ImageList_DrawEx( Value( ), indexOfImage, hDC, x, y, dx, dy, background, foreground, UINT( flags ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Draws an image list image based on an IMAGELISTDRAWPARAMS structure.
        /// </summary>
        /// <param name="imagelistDrawOarams">A pointer to an IMAGELISTDRAWPARAMS 
        /// structure that contains information about the draw operation.
        /// </param>
        static void Draw( const IMAGELISTDRAWPARAMS* imagelistDrawOarams )
        {
            if ( ImageList_DrawIndirect( const_cast<IMAGELISTDRAWPARAMS*>( imagelistDrawOarams ) ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Draws an image list image based on an IMAGELISTDRAWPARAMS structure.
        /// </summary>
        /// <param name="imagelistDrawParams">A reference to an IMAGELISTDRAWPARAMS 
        /// structure that contains information about the draw operation.</param>
        static void Draw( const IMAGELISTDRAWPARAMS& imagelistDrawParams )
        {
            Draw( &imagelistDrawParams );
        }

        /// <summary>
        /// Retrieves the current background color for an image list.
        /// </summary>
        /// <returns>The return value is the background color.</returns>
        COLORREF GetBkColor( ) const
        {
            return ImageList_GetBkColor( Value( ) );
        }
        /// <summary>
        /// Retrieves the current background color for an image list.
        /// </summary>
        /// <returns>The return value is the background color.</returns>
        COLORREF BackgroundColor( ) const
        {
            return GetBkColor( );
        }

        /// <summary>
        /// Creates an icon from an image and mask in an image list.
        /// </summary>
        /// <param name="indexOfImage">An index of the image.</param>
        /// <param name="flags">A combination of flags that specify the drawing style</param>
        /// <returns>Returns the handle to the icon</returns>
        IconHandle GetIcon( int indexOfImage, ImageListDrawFlags flags = ImageListDrawFlags::Normal ) const
        {
            auto hIcon = ImageList_GetIcon( Value( ), indexOfImage, UINT( flags ) );
            if ( !hIcon )
            {
                ThrowLastOSError( );
            }
            IconHandle result( hIcon, true );
            return result;
        }

        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <param name="x">A pointer to an integer variable that receives the width, in pixels, of each image.</param>
        /// <param name="y">A pointer to an integer variable that receives the height, in pixels, of each image.</param>
        void GetIconSize( int* x, int* y ) const
        {
            if ( ImageList_GetIconSize( Value( ), x, y ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }
        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <param name="size">A reference to a SIZE structure that receives the width and height, in pixels, of each image.</param>
        void GetIconSize( SIZE& size ) const
        {
            GetIconSize( (Int32*)&size.cx, (Int32*)&size.cy );
        }
        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <param name="size">A reference to a Size object that receives the width and height, in pixels, of each image.</param>
        void GetIconSize( Size& size ) const
        {
            GetIconSize( reinterpret_cast<SIZE&>( size ) );
        }

        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <returns>A Size object with the width and height, in pixels, of each image.</returns>
        Size GetIconSize( ) const
        {
            Size size;
            GetIconSize( size );
            return size;
        }

        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <param name="x">A pointer to an integer variable that receives the width, in pixels, of each image.</param>
        /// <param name="y">A pointer to an integer variable that receives the height, in pixels, of each image.</param>
        void GetImageSize( int* x, int* y ) const
        {
            GetIconSize( x, y );
        }
        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <param name="size">A reference to a SIZE structure that receives the width and height, in pixels, of each image.</param>
        void GetImageSize( SIZE& size ) const
        {
            GetIconSize( (Int32*)&size.cx, (Int32*)&size.cy );
        }
        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <param name="size">A reference to a Size object that receives the width and height, in pixels, of each image.</param>
        void GetImageSize( Size& size ) const
        {
            GetIconSize( reinterpret_cast<SIZE&>( size ) );
        }

        /// <summary>
        /// Retrieves the dimensions of images in an image list. All images in an image list have the same dimensions.
        /// </summary>
        /// <returns>A Size object with the width and height, in pixels, of each image.</returns>
        Size GetImageSize( ) const
        {
            return GetIconSize( );
        }

        /// <summary>
        /// Retrieves the number of images in an image list.
        /// </summary>
        /// <returns>Returns the number of images.</returns>
        int Count( ) const
        {
            return ImageList_GetImageCount( Value( ) );
        }

        /// <summary>
        /// Retrieves information about an image.
        /// </summary>
        /// <remarks>
        /// An application should not call DeleteObject to destroy the 
        /// bitmaps retrieved by GetImageInfo. The system destroys the 
        /// bitmaps when the imagelist is desroyed.
        /// </remarks>
        /// <param name="imageIndex">The index of the image.</param>
        /// <param name="imageinfo">
        /// A reference to an IMAGEINFO structure that receives information 
        /// about the image. The information in this structure can be used 
        /// to directly manipulate the bitmaps for the image.</param>
        void GetImageInfo( int imageIndex, IMAGEINFO& imageinfo ) const
        {
            if ( ImageList_GetImageInfo( Value( ), imageIndex, &imageinfo ) == FALSE )
            {
                ThrowLastOSError( );
            }
        }

        /// <summary>
        /// Retrieves information about an image.
        /// </summary>
        /// <remarks>
        /// An application should not call DeleteObject to destroy the 
        /// bitmaps retrieved by GetImageInfo. The system destroys the 
        /// bitmaps when the imagelist is desroyed.
        /// </remarks>
        /// <param name="imageIndex">The index of the image.</param>
        /// <param name="imageinfo">
        /// A pointer to an IMAGEINFO structure that receives information 
        /// about the image. The information in this structure can be used 
        /// to directly manipulate the bitmaps for the image.</param>
        void GetImageInfo( int imageIndex, IMAGEINFO* imageinfo ) const
        {
            GetImageInfo( imageIndex, *imageinfo );
        }
        
        /// <summary>
        /// Creates an image list from the specified bitmap.
        /// </summary>
        /// <param name="hInstance">A handle to the instance that contains the resource.</param>
        /// <param name="name">The address of a null-terminated string that contains the name of the image resource in the module</param>
        /// <param name="imageWidth">The width of each image. The height of each image and the initial number of images are inferred by the dimensions of the specified resource.</param>
        /// <param name="growBy">The number of images by which the image list can grow when the system needs to make room for new images. This parameter represents the number of new images that the resized image list can contain.</param>
        /// <param name="maskColor">The color used to generate a mask. Each pixel of this color in the specified bitmap, cursor, or icon is changed to black, and the corresponding bit in the mask is set to 1. If this parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT value, the color of the pixel at the upper-left corner of the image is treated as the mask color.</param>
        /// <param name="flags">Flags that specify how to load the image</param>
        /// <returns>Returns the handle to the image list</returns>
        static ImageList Load( HINSTANCE hInstance, const wchar_t* name, int imageWidth, int growBy, COLORREF maskColor, ImageListLoadFlags flags )
        {
            HIMAGELIST hImageList = ImageList_LoadImageW( hInstance, name, imageWidth, growBy, maskColor, IMAGE_BITMAP, UINT( flags ) );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, int( flags & ImageListLoadFlags::Shared ) != 0 ? false : true );
            return result;
        }
        /// <summary>
        /// Creates an image list from the specified bitmap.
        /// </summary>
        /// <param name="name">The address of a null-terminated string that names the file containing the image to load.</param>
        /// <param name="imageWidth">The width of each image. The height of each image and the initial number of images are inferred by the dimensions of the specified resource.</param>
        /// <param name="growBy">The number of images by which the image list can grow when the system needs to make room for new images. This parameter represents the number of new images that the resized image list can contain.</param>
        /// <param name="maskColor">The color used to generate a mask. Each pixel of this color in the specified bitmap, cursor, or icon is changed to black, and the corresponding bit in the mask is set to 1. If this parameter is the CLR_NONE value, no mask is generated. If this parameter is the CLR_DEFAULT value, the color of the pixel at the upper-left corner of the image is treated as the mask color.</param>
        /// <param name="flags">Flags that specify how to load the image</param>
        /// <returns>Returns the handle to the image list</returns>
        static ImageList LoadFromFile( const wchar_t* name, int imageWidth, int growBy, COLORREF maskColor, ImageListLoadFlags flags )
        {
            flags |= ImageListLoadFlags::LoadFromFile;
            HIMAGELIST hImageList = ImageList_LoadImageW( nullptr, name, imageWidth, growBy, maskColor, IMAGE_BITMAP, UINT( flags ) );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, int( flags & ImageListLoadFlags::Shared ) != 0 ? false : true );
            return result;
        }
        /// <summary>
        /// Creates an image list from the specified bitmap.
        /// </summary>
        /// <param name="name">The address of a null-terminated string that names the file containing the image to load.</param>
        /// <param name="imageWidth">The width of each image. The height of each image and the initial number of images are inferred by the dimensions of the specified resource.</param>
        /// <returns>Returns the handle to the image list</returns>
        static ImageList LoadFromFile( const wchar_t* name, int imageWidth )
        {
            ImageListLoadFlags flags = ImageListLoadFlags::LoadFromFile;
            HIMAGELIST hImageList = ImageList_LoadImageW( nullptr, name, imageWidth, 1, CLR_DEFAULT, IMAGE_BITMAP, UINT( flags ) );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, true );
            return result;
        }
        /// <summary>
        /// Creates a new image by combining two existing images. The function also 
        /// creates a new image list in which to store the image.
        /// </summary>
        /// <param name="himl1">A handle to the first image list.</param>
        /// <param name="i1">The index of the first existing image.</param>
        /// <param name="himl2">A handle to the second image list.</param>
        /// <param name="i2">The index of the second existing image.</param>
        /// <param name="dx">The x-offset of the second image relative to the first image.</param>
        /// <param name="dy">The y-offset of the second image relative to the first image.</param>
        /// <returns>Returns the handle to the new image list</returns>
        static ImageList Merge( HIMAGELIST himl1, int i1, HIMAGELIST himl2, int i2, int dx, int dy )
        {
            HIMAGELIST hImageList = ImageList_Merge( himl1, i1, himl2, i2, dx, dy );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, true );
            return result;
        }
        /// <summary>
        /// Creates a new image by combining two existing images. The function also 
        /// creates a new image list in which to store the image.
        /// </summary>
        /// <param name="i1">The index of the first existing image.</param>
        /// <param name="himl2">A handle to the second image list.</param>
        /// <param name="i2">The index of the second existing image.</param>
        /// <param name="dx">The x-offset of the second image relative to the first image.</param>
        /// <param name="dy">The y-offset of the second image relative to the first image.</param>
        /// <returns>Returns the handle to the new image list</returns>
        ImageList Merge( int i1, HIMAGELIST himl2, int i2, int dx, int dy ) const
        {
            return Merge( Value( ), i1, himl2, i2, dx, dy );
        }

        /// <summary>
        /// Reads an image list from a stream.
        /// </summary>
        /// <param name="stream">A pointer to the stream</param>
        /// <returns>Returns the handle to the image list</returns>
        static ImageList Read( LPSTREAM stream )
        {
            HIMAGELIST hImageList = ImageList_Read( stream );
            if ( !hImageList )
            {
                ThrowLastOSError( );
            }
            ImageList result( hImageList, true );
            return result;
        }

        /// <summary>
        /// Removes an image from the image list.
        /// </summary>
        /// <param name="index">The index of the image to remove. If this parameter is -1, the function removes all images.</param>
        /// <returns>Returns true if successful, or false if not.</returns>
        bool Remove( int index ) const
        {
            return ImageList_Remove( Value( ), index ) != 0;
        }


        /// <summary>
        /// Replaces an image in the image list with a new image.
        /// </summary>
        /// <param name="index">The index of the image to replace</param>
        /// <param name="image">The handle to the bitmap that contains the new image.</param>
        /// <param name="mask">The handle to the bitmap that contains the mask. If no mask is used with the image list, this parameter is ignored.</param>
        /// <returns>Returns true if successful, or false otherwise</returns>
        bool Replace( int index, HBITMAP image, HBITMAP mask ) const
        {
            return ImageList_Replace( Value( ), index, image, mask ) != 0;
        }


        /// <summary>
        /// Replaces an image with an icon or cursor.
        /// </summary>
        /// <param name="index">The index of the image to replace. If index is -1, the function appends the image to the end of the list.</param>
        /// <param name="icon">The handle to the icon or cursor that contains the bitmap and mask for the new image.</param>
        /// <returns>Returns the index of the image if successful, or -1 if not.</returns>
        int Replace( int index, HICON icon ) const
        {
            return ImageList_ReplaceIcon( Value( ), index, icon );
        }

        /// <summary>
        /// Sets the background color for an image list. This function only works 
        /// if you add an icon or use Add with a black and white bitmap. Without a mask, 
        /// the entire image is drawn; hence the background color is not visible.
        /// </summary>
        /// <param name="newBackgroundColor">
        /// The background color to set. This parameter can be the value returned from ColorRef::None( ), 
        /// CLR_NONE, value; in which case, images are drawn transparently using the mask.
        /// </param>
        /// <returns>Returns the previous background color if successful, or CLR_NONE otherwise.</returns>
        ColorRef SetBkColor( const ColorRef& newBackgroundColor ) const
        {
            return ImageList_SetBkColor( Value( ), newBackgroundColor );
        }

        /*
        int SetColorTable( int start, int len, RGBQUAD* prgb )
        {
            return ImageList_SetColorTable( Value( ), start, len, prgb );
        }
        */

    };

    // --------------------------------------------------------------------
    // ButtonBase
    // --------------------------------------------------------------------
    class ButtonBase : public Control
    {
        bool autoEllipsis_;
    public:
        using Base=Control;

        HW_EXPORT ButtonBase( );
    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    public:


        HW_EXPORT bool AutoEllipsis( ) const;
        HW_EXPORT ButtonBase& SetAutoEllipsis( bool theValue );



        HW_EXPORT ButtonBase& Click( );
        HW_EXPORT const ButtonBase& GetTextMargin( RECT& margin ) const;
        HW_EXPORT RECT GetTextMargin( ) const;
        HW_EXPORT ButtonBase& SetTextMargin( const RECT& margin );

        HW_EXPORT const ButtonBase& GetIdealSize( SIZE& preferredSize ) const;
        HW_EXPORT SIZE GetIdealSize( ) const;

        boost::signals2::signal<void( Control* sender )> OnClick;

    protected:
        HW_EXPORT virtual void DoOnSetEnabled( bool theValue );

        HW_EXPORT virtual void DoOnClick( );
        HW_EXPORT virtual void DoOnCommand( Message& message );


    };

    // --------------------------------------------------------------------
    // PushButtonBase
    // --------------------------------------------------------------------
    class PushButtonBase : public ButtonBase
    {
        bool isDefault_;
    public:
        using Base=ButtonBase;

        HW_EXPORT PushButtonBase( );

        HW_EXPORT bool IsDefault( ) const;
        HW_EXPORT PushButtonBase& SetDefault( bool theValue );

        boost::signals2::signal<void( Control* sender, bool theValue )> OnDefaultChanged;
    protected:
        HW_EXPORT virtual void DoOnSetDefault( bool theValue );
        HW_EXPORT virtual void DoOnDefaultChanged( bool theValue );

    };


    // --------------------------------------------------------------------
    // Button
    // --------------------------------------------------------------------
    class Button : public PushButtonBase
    {
    public:
        using Base=PushButtonBase;
        HW_EXPORT Button( );
        HW_EXPORT virtual DWORD GetStyle( ) const;
    protected:
        HW_EXPORT virtual void DoOnSetDefault( bool theValue );
    };


    // --------------------------------------------------------------------
    // DropDownButton
    // --------------------------------------------------------------------
    class DropDownButton : public PushButtonBase
    {
        std::unique_ptr<PopupMenu> popupMenu_;
    public:
        using Base=PushButtonBase;
        HW_EXPORT DropDownButton( );
        HW_EXPORT virtual DWORD GetStyle( ) const;

        HW_EXPORT PopupMenu* Menu( ) const;
    protected:
        HW_EXPORT virtual void DoOnInitialize( );
        HW_EXPORT virtual void DoOnSetDefault( bool theValue );

        HW_EXPORT virtual void DoOnNotify( Message& message );
    };

    // --------------------------------------------------------------------
    // CommandButton
    // --------------------------------------------------------------------
    class CommandButton : public PushButtonBase
    {
    public:
        using Base=PushButtonBase;
        HW_EXPORT CommandButton( );
        HW_EXPORT virtual DWORD GetStyle( ) const;
    protected:
        HW_EXPORT virtual void DoOnSetDefault( bool theValue );
    };


    // --------------------------------------------------------------------
    // StateButton
    // --------------------------------------------------------------------
    class StateButton : public ButtonBase
    {
        CheckState checkState_;
        bool allowGrayed_;
    public:
        using Base=ButtonBase;
        HW_EXPORT StateButton( );

        HW_EXPORT StateButton& SetCheckState( Windows::CheckState theCheckState );
        HW_EXPORT Windows::CheckState CheckState( ) const;

        HW_EXPORT bool AllowGrayed( ) const;
        HW_EXPORT StateButton& SetAllowGrayed( bool theValue = true );

        HW_EXPORT bool Checked( ) const;
        HW_EXPORT StateButton& SetChecked( bool theValue );
        HW_EXPORT StateButton& Toggle( );

        HW_EXPORT virtual void HandleMessage( Message& message );
        boost::signals2::signal<void( Control* sender, Windows::CheckState theCheckState )> OnCheckStateChanged;
    protected:
        HW_EXPORT virtual void DoOnHandleCreated( );
        HW_EXPORT virtual void DoOnCheckStateChanged( Windows::CheckState theCheckState );
        HW_EXPORT virtual void DoOnClick( );
    };

    // --------------------------------------------------------------------
    // CheckBox
    // --------------------------------------------------------------------
    class CheckBox : public StateButton
    {

    public:
        using Base=StateButton;
        HW_EXPORT CheckBox( );
    protected:
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };

    // --------------------------------------------------------------------
    // RadioButton
    // --------------------------------------------------------------------
    class RadioButton : public StateButton
    {
    public:
        using Base=StateButton;
        HW_EXPORT RadioButton( );
    protected:
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // DateTimePicker
    // --------------------------------------------------------------------
    class DateTimePicker : public Control
    {
    public:
        using Base=Control;

        HW_EXPORT DateTimePicker( );
    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;

        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // GroupBox
    // --------------------------------------------------------------------
    class GroupBox : public Control
    {
    public:
        using Base=Control;

        HW_EXPORT GroupBox( );
    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;

        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // Label
    // --------------------------------------------------------------------
    class Label : public Control
    {
    public:
        using Base=Control;
        HW_EXPORT Label( );
    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // LinkLabel
    // --------------------------------------------------------------------
    class LinkLabel : public Label
    {
    public:
        using Base=Label;
        HW_EXPORT LinkLabel( );


        boost::signals2::signal<void( LinkLabel* sender, NMLINK* pNMLINK )> OnClick;
    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;

        HW_EXPORT virtual void DoOnClick( NMLINK* pNMLINK );
        HW_EXPORT virtual void DoOnNotify( Message& message );
    };

    // --------------------------------------------------------------------
    // ListControl
    // --------------------------------------------------------------------
    class ListControl : public Control
    {
    public:
        using Base=Control;
        HW_EXPORT ListControl( );
    };

    // --------------------------------------------------------------------
    // ComboBox
    // --------------------------------------------------------------------
    class ComboBox : public ListControl
    {
    public:
        using Base=ListControl;
        HW_EXPORT ComboBox( );

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // ListBox
    // --------------------------------------------------------------------
    class ListBox : public ListControl
    {
    public:
        using Base=ListControl;
        HW_EXPORT ListBox( );

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // CheckedListBox
    // --------------------------------------------------------------------
    class CheckedListBox : public ListBox
    {
    public:
        using Base=ListBox;
        HW_EXPORT CheckedListBox( );
    protected:
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    enum class HeaderControlItemMask : UINT
    {
        None = 0,
        Width = 0x0001,
        Height = 0x0001,
        Text = 0x0002,
        Format = 0x0004,
        LParam = 0x0008,
        Bitmap = 0x0010,
        Image = 0x0020,
        DiSetItem = 0x0040,
        Order = 0x0080,
        Filter = 0x0100,
        State = 0x0200
    };
    DEFINE_ENUM_FLAG_OPERATORS( HeaderControlItemMask )



    enum class HeaderControlItemFormat : int
    {
        Default = 0,
        Left = 0x0000,
        Right = 0x0001,
        Center = 0x0002,
        AlignmentMask = 0x0003,
        RTLReading = 0x0004,
        Bitmap = 0x2000,
        String = 0x4000,
        OwnerDraw = 0x8000,
        Image = 0x0800,
        BitmapOnRight = 0x1000,
        SortUp = 0x0400,
        SortDown = 0x0200,
        CheckBox = 0x0040,
        Checked = 0x0080,
        FixedWidth = 0x0100,
        SplitButton = 0x1000000
    };
    DEFINE_ENUM_FLAG_OPERATORS( HeaderControlItemFormat )

    enum class HeaderControlItemFilterType
    {
        String = HDFT_ISSTRING,
        Number = HDFT_ISNUMBER,
        DateTime = HDFT_ISDATE,
        None = HDFT_HASNOVALUE
    };

    class HeaderControl;
    class HeaderControlItems;
    // --------------------------------------------------------------------
    // HeaderControlItem
    // --------------------------------------------------------------------
    class HeaderControlItem
    {
        friend class HeaderControl;
        friend class HeaderControlItems;
        HeaderControlItems* items_;

        HeaderControlItemMask mask_;
        int dimension_;
        WideString text_;
        BitmapHandle bitmap_;
        HeaderControlItemFormat format_;
        int     imageIndex_;
        int     order_;
        HeaderControlItemFilterType filterType_;
        WideString  textFilter_;
        int intFilter_;
        SYSTEMTIME timeFilter_;

        bool IsHandleCreated( ) const;
        HWND GetControlHandle( ) const;
        HeaderControl* GetControl( ) const;

    public:
        

        HW_EXPORT HeaderControlItem( HeaderControlItems* theHeaderControlItems );
        HW_EXPORT HeaderControlItem( HeaderControlItems* theHeaderControlItems, const WideString& theText );

        const HeaderControlItems* Items( ) const { return items_; }
        HeaderControlItems* Items( ) { return items_; }

        HW_EXPORT WideString Text( ) const;
        HW_EXPORT HeaderControlItem& SetText( const WideString& theText );

        HW_EXPORT HeaderControlItem& Assign( const HDITEMW& item );
        HW_EXPORT const HeaderControlItem& AssignTo( HDITEMW& item ) const;

        HW_EXPORT size_t IndexOf( ) const;

        HW_EXPORT HeaderControlItem& ClearFilter( );

    protected:
        HW_EXPORT virtual void DoOnBeginDrag( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnBeginFilterEdit( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnBeginTrack( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnDividerDoubleClick( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnDropDown( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnEndDrag( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnEndFilterEdit( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnEndTrack( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnFilterButtonClicked( NMHDFILTERBTNCLICK* pNMHDFILTERBTNCLICK );
        HW_EXPORT virtual void DoOnFilterChange( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnGetDispInfo( NMHDDISPINFO* pNMHDDISPINFO );
        HW_EXPORT virtual void DoOnItemChanged( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnItemChanging( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnItemClicked( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnItemDoubleClicked( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnItemKeyDown( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnItemStateIconClicked( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnItemOverflowButtonClicked( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnTrack( NMHEADER* pNMHEADER );
        HW_EXPORT virtual void DoOnCustomDraw( NMCUSTOMDRAW* pNMCUSTOMDRAW );
        HW_EXPORT virtual void DoOnRightClicked( const Point& mousePosition );

    private:
        HW_EXPORT void InsertHDITEM( );
        HW_EXPORT void UpdateHDITEM( );
        HW_EXPORT void DeleteHDITEM( );
    };

    // --------------------------------------------------------------------
    // HeaderControlItems
    // --------------------------------------------------------------------
    class HeaderControlItems
    {
    public:
        typedef size_t size_type;
        typedef HeaderControlItem* value_type;
        typedef std::vector<std::unique_ptr< HeaderControlItem >> vector;
        typedef vector::const_iterator const_iterator;
        typedef vector::iterator iterator;

        static const size_type npos = SIZE_T_MAX; //UINT64_MAX;
    private:
        friend class HeaderControlItem;
        friend class HeaderControl;
        HeaderControl* headerControl_;
        vector items_;
        size_type focusedIndex_;

        void DoOnHandleCreated( );
    public:
        HW_EXPORT HeaderControlItems( HeaderControl* theHeaderControl );

        iterator begin( ) { return items_.begin( ); }
        iterator end( ) { return items_.end( ); }

        const_iterator begin( ) const { return items_.begin( ); }
        const_iterator end( ) const { return items_.end( ); }

        const_iterator cbegin( ) const { return items_.cbegin( ); }
        const_iterator cend( ) const { return items_.cend( ); }

        HeaderControlItem* at( size_type index ) { return items_.at( index ).get(); }
        const HeaderControlItem* at( size_type index ) const { return items_.at( index ).get(); }

        HeaderControlItem* operator[]( size_type index ) { return items_[index].get(); }
        const HeaderControlItem* operator[]( size_type index ) const { return items_[index].get( ); }

        HW_EXPORT size_type Count( ) const;
        HW_EXPORT size_type count( ) const { return Count( ); }
        HW_EXPORT size_type size( ) const { return Count( ); }

        HW_EXPORT size_type IndexOf( const HeaderControlItem* theItem ) const;
        HW_EXPORT size_type IndexOf( const HeaderControlItem& theItem ) const;

        HW_EXPORT const HeaderControlItem* FocusedItem( ) const;
        HW_EXPORT HeaderControlItem* FocusedItem( );

        HW_EXPORT size_type FocusedIndex( ) const;

        HW_EXPORT const HeaderControlItem* Add( const WideString& headerText );
        HW_EXPORT const HeaderControlItem* Add( const WideString& headerText, HorizontalAlignment alignment );
        HW_EXPORT HeaderControlItems& RemoveAt( size_type index );



    };

    // --------------------------------------------------------------------
    // HeaderControl
    // --------------------------------------------------------------------
    class HeaderControl : public Control
    {
        friend class HeaderControlItem;
        HeaderControlItems* items_;
        ImageList imageList_;
        ImageList stateImageList_;
        int bitmapMargin_;
    public:
        typedef Control Base;
        HW_EXPORT HeaderControl( );
        HW_EXPORT virtual ~HeaderControl( );


        HW_EXPORT const Windows::ImageList& ImageList( ) const;
        HW_EXPORT HeaderControl& SetImageList( const Windows::ImageList& theImageList );

        HW_EXPORT const Windows::ImageList& StateImageList( ) const;
        HW_EXPORT HeaderControl& SetStateImageList( const Windows::ImageList& theImageList );

        HW_EXPORT Rectangle GetItemRectangle( size_t theIndex ) const;
        HW_EXPORT Rectangle GetItemRectangle( const HeaderControlItem* theItem ) const;
        HW_EXPORT Rectangle GetItemRectangle( const HeaderControlItem& theItem ) const;

        HW_EXPORT static int DefaultBitmapMargin( );
        HW_EXPORT HeaderControl& SetBitmapMargin( int theMargin );


        const HeaderControlItems* Items( ) const { return items_; };
        HeaderControlItems* Items( ) { return items_; };

        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnBeginDrag;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnBeginFilterEdit;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnBeginTrack;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnDividerDoubleClick;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnDropDown;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnEndDrag;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnEndFilterEdit;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnEndTrack;
        boost::signals2::signal<void( HeaderControl* sender, NMHDFILTERBTNCLICK* pNMHDFILTERBTNCLICK, HeaderControlItem& item ) > OnFilterButtonClicked;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnFilterChange;
        boost::signals2::signal<void( HeaderControl* sender, NMHDDISPINFO* pNMHDDISPINFO, HeaderControlItem& item ) > OnGetDispInfo;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemChanged;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemChanging;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemClicked;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemDoubleClicked;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemKeyDown;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemStateIconClicked;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnItemOverflowButtonClicked;
        boost::signals2::signal<void( HeaderControl* sender, NMHEADER* pNMHEADER, HeaderControlItem& item ) > OnTrack;
        boost::signals2::signal<void( HeaderControl* sender, NMCUSTOMDRAW* pNMCUSTOMDRAW ) > OnCustomDraw;
        boost::signals2::signal<void( HeaderControl* sender, const Point& mousePosition ) > OnRightClicked;
        boost::signals2::signal<void( HeaderControl* sender, const Point& mousePosition ) > OnCaptureReleased;

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;

        HW_EXPORT virtual void DoOnHandleCreated( );
        HW_EXPORT virtual void DoOnWindowSubClassed( );

        HW_EXPORT virtual void DoOnBeginDrag( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnBeginFilterEdit( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnBeginTrack( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnDividerDoubleClick( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnDropDown( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnEndDrag( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnEndFilterEdit( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnEndTrack( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnFilterButtonClicked( NMHDFILTERBTNCLICK* pNMHDFILTERBTNCLICK, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnFilterChange( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnGetDispInfo( NMHDDISPINFO* pNMHDDISPINFO, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemChanged( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemChanging( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemClicked( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemDoubleClicked( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemKeyDown( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemStateIconClicked( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnItemOverflowButtonClicked( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnTrack( NMHEADER* pNMHEADER, HeaderControlItem& item );
        HW_EXPORT virtual void DoOnCustomDraw( NMCUSTOMDRAW* pNMCUSTOMDRAW );
        HW_EXPORT virtual void DoOnRightClicked( const Point& mousePosition );
        HW_EXPORT virtual void DoOnCaptureReleased( const Point& mousePosition );

        HW_EXPORT virtual void DoOnNotify( Message& message );
    };

    // --------------------------------------------------------------------
    // ListView
    // --------------------------------------------------------------------
    class ListView : public Control
    {
    public:
        using Base=Control;
        HW_EXPORT ListView( );

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // MonthCalendar
    // --------------------------------------------------------------------
    class MonthCalendar : public Control
    {
    public:
        using Base=Control;
        HW_EXPORT MonthCalendar( );

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // TreeEditBase
    // --------------------------------------------------------------------
    class TreeEditBase : public Control
    {
    public:
        using Base=Control ;
        HW_EXPORT TreeEditBase( );
    };


    // --------------------------------------------------------------------
    // EditBase
    // --------------------------------------------------------------------
    class EditBase : public Control
    {
    public:
        using Base=Control;

        HW_EXPORT EditBase( );
    };


    // --------------------------------------------------------------------
    // TextEditBase
    // --------------------------------------------------------------------
    class TextEditBase : public EditBase
    {
    public:
        using Base=EditBase;
        HW_EXPORT TextEditBase( );
    };

    enum class TextEditStyles : UInt32
    {
        AlignLeft = ES_LEFT,
        AlignCenter = ES_CENTER,
        AlignRight = ES_RIGHT,
        MultiLine = ES_MULTILINE,
        ConvertToUpperCase = ES_UPPERCASE,
        ConvertToLowerCase = ES_LOWERCASE,
        Password = ES_PASSWORD,
        AutomaticVerticalScroll = ES_AUTOVSCROLL,
        AutomaticHorizontalScroll = ES_AUTOHSCROLL,
        AlwaysShowSelection = ES_NOHIDESEL,
        OEMConvert = ES_OEMCONVERT,
        ReadOnly = ES_READONLY,
        WantReturn = ES_WANTRETURN,
        Numeric = ES_NUMBER
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TextEditStyles, UInt32 );

    // --------------------------------------------------------------------
    // TextEdit
    // --------------------------------------------------------------------
    class TextEdit : public TextEditBase
    {
        TextEditStyles editStyle_ = TextEditStyles::AlignLeft;
    public:
        using Base=TextEditBase;
        HW_EXPORT TextEdit( TextEditStyles editStyle = TextEditStyles::AlignLeft );



        HW_EXPORT bool CanUndo( ) const;
        HW_EXPORT TextEdit& Undo( );

        HW_EXPORT TextEdit& EmptyUndoBuffer( );
        HW_EXPORT TextEdit& FmtLines( bool addSoftLinebreaks );

        HW_EXPORT WideString CueBannerText( ) const;
        HW_EXPORT TextEdit& SetCueBannerText( const WideString& theText, bool displayWhileFocused = false );
        HW_EXPORT TextEdit& SetCueBannerText( const wchar_t* theText, bool displayWhileFocused = false );

        HW_EXPORT int GetFirstVisibleLine( ) const;
        HW_EXPORT UINT TextLimit( ) const;
        HW_EXPORT TextEdit& SetTextLimit( UINT theValue );


        HW_EXPORT int LineIndex( int theIndex ) const;
        HW_EXPORT int LineLength( int theIndex ) const;
        HW_EXPORT WideString Line( int theIndex ) const;
        HW_EXPORT int LineCount( ) const;
        HW_EXPORT bool IsModified( ) const;

        HW_EXPORT wchar_t PasswordChar( ) const;
        HW_EXPORT TextEdit& SetPasswordChar( wchar_t theValue );

        HW_EXPORT Range Selection( ) const;
        HW_EXPORT TextEdit& SetSelection( const Range& selectionRange );

        HW_EXPORT TextEdit& ReplaceSelection( const WideString& theText );
        HW_EXPORT TextEdit& ReplaceSelection( const wchar_t* theText );

        HW_EXPORT TextEdit& Append( const WideString& theText );
        HW_EXPORT TextEdit& Append( const wchar_t* theText );



    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;

        HW_EXPORT virtual void DoOnSetEnabled( bool theValue );

    };

    // --------------------------------------------------------------------
    // MemoEdit
    // --------------------------------------------------------------------
    class MemoEdit : public TextEdit
    {
    public:
        using Base=TextEdit;
        HW_EXPORT MemoEdit( );

        HW_EXPORT int FirstVisibleLine( ) const;
        HW_EXPORT MemoEdit& AppendLine( const WideString& theText );
        HW_EXPORT MemoEdit& AppendLine( const wchar_t* theText );
    protected:
        HW_EXPORT virtual DWORD GetStyle( ) const;
        /*
        HW_EXPORT virtual WideString Text() const;
        protected:
        HW_EXPORT HLOCAL GetHandle() const;
        */
    };


    // --------------------------------------------------------------------
    // HotKey
    // --------------------------------------------------------------------
    class HotKey : public TextEditBase
    {
    public:
        using Base=TextEditBase;
        HW_EXPORT HotKey( );

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };


    // --------------------------------------------------------------------
    // ScrollBar
    // --------------------------------------------------------------------
    class ScrollBar : public Control
    {
    public:
        using Base = Control;
        HW_EXPORT ScrollBar( );

    protected:
        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };

    // --------------------------------------------------------------------
    // HScrollBar
    // --------------------------------------------------------------------
    class HScrollBar : public ScrollBar
    {
    public:
        using Base=ScrollBar;
        HW_EXPORT HScrollBar( );
    protected:
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };

    // --------------------------------------------------------------------
    // VScrollBar
    // --------------------------------------------------------------------
    class VScrollBar : public ScrollBar
    {
    public:
        using Base=ScrollBar;
        HW_EXPORT VScrollBar( );
    protected:
        HW_EXPORT virtual DWORD GetStyle( ) const;
    };





    // --------------------------------------------------------------------
    // Timer
    // --------------------------------------------------------------------
    class Timer
    {
        TimeSpan interval_;
        bool enabled_;

        friend class TimerControl;
        class TimerControl : public Control
        {
            Timer& timer_;
            UINT_PTR timerId_;
            static UINT_PTR TimerID_;
            bool stoppingTimer_;
        public:
            using Base=Control;
            HW_EXPORT TimerControl( Timer& timer );

            HW_EXPORT virtual void HandleMessage( Message& message );

            HW_EXPORT void StopTimer( );
            HW_EXPORT void StartTimer( );
        protected:
            HW_EXPORT virtual DWORD GetStyle( ) const;
            HW_EXPORT virtual HWND CreateHandle( );
            HW_EXPORT virtual void DoBeforeHandleDestroy( );

        };

        std::unique_ptr<TimerControl> timerControl_;

    public:

        HW_EXPORT Timer( );

        HW_EXPORT TimeSpan Interval( ) const;
        HW_EXPORT Timer& SetInterval( const TimeSpan& interval );

        HW_EXPORT bool Enabled( ) const;
        HW_EXPORT Timer& SetEnabled( bool value = true );

        boost::signals2::signal<void( Timer* sender )> OnTick;
    protected:
        HW_EXPORT virtual void DoOnTick( );

    };

    enum class TreeViewStyles : unsigned short
    {
        HasButtons = TVS_HASBUTTONS,
        HasLines = TVS_HASLINES,
        LinesAtRoot = TVS_LINESATROOT,
        EditLabels = TVS_EDITLABELS,
        DisableDragDrom = TVS_DISABLEDRAGDROP,
        ShowSelectAlways = TVS_SHOWSELALWAYS,
        RtlReading = TVS_RTLREADING,
        NoToolTips = TVS_NOTOOLTIPS,
        CheckBoxes = TVS_CHECKBOXES,
        TrackSelect = TVS_TRACKSELECT,
        SingleExpand = TVS_SINGLEEXPAND,
        InfoTip = TVS_INFOTIP,
        FullRowSelect = TVS_FULLROWSELECT,
        NoScroll = TVS_NOSCROLL,
        NonEvenHeight = TVS_NONEVENHEIGHT,
        NoHorizontalScroll = TVS_NOHSCROLL
    };
    HCC_DEFINE_ENUM_FLAG_OPERATORS( TreeViewStyles, unsigned short );

    class TreeViewItem;
    // --------------------------------------------------------------------
    // TreeView
    // --------------------------------------------------------------------
    class TreeView : public TreeEditBase
    {
        
        friend class TreeViewItem;
    public:

        using Base=TreeEditBase;

        HW_EXPORT TreeView( );
        HW_EXPORT ~TreeView( );

        HW_EXPORT virtual WindowClass* GetWindowClass( ) const;
        HW_EXPORT virtual DWORD GetStyle( ) const;

        HW_EXPORT TreeViewItem AddItem( const WideString& theText );
    };

    // --------------------------------------------------------------------
    // TreeViewItem
    // --------------------------------------------------------------------
    class TreeViewItem
    {
        friend class TreeView;

        HTREEITEM handle_;
        TreeView& treeView_;
        WideString text_;
    public:
        HW_EXPORT TreeViewItem( Windows::TreeView& treeView, const WideString& text );
    protected:
    protected:
        const Windows::TreeView& TreeView( ) const
        {
            return treeView_;
        }


    };

}

#endif
