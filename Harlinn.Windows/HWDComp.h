#pragma once
#ifndef HARLINN_WINDOWS_HWDCOMP_H_
#define HARLINN_WINDOWS_HWDCOMP_H_

#include "HWDCompAnimation.h"

namespace Harlinn::Windows::Graphics
{
    class DCompositionDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionDevice, Unknown, IDCompositionDevice, IUnknown)
    public:
        // Commits all DirectComposition commands pending on this device.
        void Commit() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Commit();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Waits for the last Commit to be processed by the composition engine
        void WaitForCommitCompletion( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->WaitForCommitCompletion();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Gets timing information about the composition engine.
        void GetFrameStatistics(DCOMPOSITION_FRAME_STATISTICS* statistics ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFrameStatistics(statistics);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a composition target bound to a window represented by an HWND.
        void CreateTargetForHwnd(HWND hwnd, BOOL topmost, IDCompositionTarget** target ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTargetForHwnd(hwnd, topmost, target);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a new visual object.
        void CreateVisual(IDCompositionVisual** visual ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVisual(visual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a DirectComposition surface object
        void CreateSurface(UINT width, UINT height, DXGI_FORMAT pixelFormat, DXGI_ALPHA_MODE alphaMode, IDCompositionSurface** surface ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurface(width, height, pixelFormat, alphaMode, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a DirectComposition virtual surface object
        void CreateVirtualSurface( UINT initialWidth, UINT initialHeight, DXGI_FORMAT pixelFormat, DXGI_ALPHA_MODE alphaMode, IDCompositionVirtualSurface** virtualSurface ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVirtualSurface(initialWidth, initialHeight, pixelFormat, alphaMode, virtualSurface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a surface wrapper around a pre-existing surface that can be associated with one or more visuals for composition.
        void CreateSurfaceFromHandle( HANDLE handle, IUnknown** surface ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurfaceFromHandle(handle, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a wrapper object that represents the rasterization of a layered window and which can be associated with a visual for composition.
        void CreateSurfaceFromHwnd(HWND hwnd, IUnknown** surface ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurfaceFromHwnd(hwnd, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D translation transform object.
        void CreateTranslateTransform( IDCompositionTranslateTransform** translateTransform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTranslateTransform(translateTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D scale transform object.
        void CreateScaleTransform( IDCompositionScaleTransform** scaleTransform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateScaleTransform(scaleTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D rotation transform object.
        void CreateRotateTransform( IDCompositionRotateTransform** rotateTransform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRotateTransform(rotateTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D skew transform object.
        void CreateSkewTransform( IDCompositionSkewTransform** skewTransform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSkewTransform(skewTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D 3x2 matrix transform object.
        void CreateMatrixTransform(IDCompositionMatrixTransform** matrixTransform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateMatrixTransform(matrixTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D transform object that holds an array of 2D transform objects.
        void CreateTransformGroup(IDCompositionTransform** transforms, UINT numberOfTransforms, IDCompositionTransform** transformGroup ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTransformGroup(transforms, numberOfTransforms, transformGroup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D translation transform object.
        void CreateTranslateTransform3D(IDCompositionTranslateTransform3D** translateTransform3D ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTranslateTransform3D(translateTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D scale transform object.
        void CreateScaleTransform3D(IDCompositionScaleTransform3D** scaleTransform3D ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateScaleTransform3D(scaleTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D rotation transform object.
        void CreateRotateTransform3D(IDCompositionRotateTransform3D** rotateTransform3D ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRotateTransform3D(rotateTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D 4x4 matrix transform object.
        void CreateMatrixTransform3D(IDCompositionMatrixTransform3D** matrixTransform3D ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateMatrixTransform3D(matrixTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D transform object that holds an array of 3D transform objects.
        void CreateTransform3DGroup(IDCompositionTransform3D** transforms3D, UINT numberOftransforms3D, IDCompositionTransform3D** transform3DGroup ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTransform3DGroup(transforms3D, numberOftransforms3D, transform3DGroup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates an effect group
        void CreateEffectGroup(IDCompositionEffectGroup** effectGroup ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateEffectGroup(effectGroup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a clip object that can be used to clip the contents of a visual subtree.
        void CreateRectangleClip(IDCompositionRectangleClip** clip ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRectangleClip(clip);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates an animation object
        void CreateAnimation(IDCompositionAnimation** animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateAnimation(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Returns the states of the app's DX device and DWM's dx devices
        void CheckDeviceState(BOOL* valid ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CheckDeviceState(valid);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionTarget : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTarget, Unknown, IDCompositionTarget, IUnknown)
    public:
        void SetRoot(IDCompositionVisual* visual) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRoot(visual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionVisual : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionVisual, Unknown, IDCompositionVisual, IUnknown)
    public:
        // Changes the value of OffsetX property
        void SetOffsetX(float offsetX ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetX(offsetX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetX property.
        void SetOffsetX(IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of OffsetY property
        void SetOffsetY(float offsetY ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetY(offsetY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetY property.
        void SetOffsetY(IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the matrix that modifies the coordinate system of this visual.
        void SetTransform(const D2D_MATRIX_3X2_F& matrix ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransform(matrix);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the transformation object that modifies the coordinate system of this visual.
        void SetTransform(IDCompositionTransform* transform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransform(transform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the visual that should act as this visual's parent for the
        // purpose of establishing a base coordinate system.
        void SetTransformParent(IDCompositionVisual* visual ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransformParent(visual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the effect object that is applied during the rendering of this visual
        void SetEffect(IDCompositionEffect* effect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetEffect(effect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the mode to use when interpolating pixels from bitmaps drawn not
        // exactly at scale and axis-aligned.
        void SetBitmapInterpolationMode(DCOMPOSITION_BITMAP_INTERPOLATION_MODE interpolationMode ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBitmapInterpolationMode(interpolationMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the mode to use when drawing the edge of bitmaps that are not
        // exactly axis-aligned and at precise pixel boundaries.
        void SetBorderMode(DCOMPOSITION_BORDER_MODE borderMode ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBorderMode(borderMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the clip object that restricts the rendering of this visual to a D2D rectangle.
        void SetClip(const D2D_RECT_F& rect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetClip(rect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the clip object that restricts the rendering of this visual to a rectangle.
        void SetClip(IDCompositionClip* clip ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetClip(clip);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Associates a bitmap with a visual
        void SetContent(IUnknown* content ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetContent(content);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Adds a visual to the children list of another visual.
        void AddVisual(IDCompositionVisual* visual, BOOL insertAbove, IDCompositionVisual* referenceVisual ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddVisual(visual, insertAbove, referenceVisual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Removes a visual from the children list of another visual.
        void RemoveVisual(IDCompositionVisual* visual ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveVisual(visual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Removes all visuals from the children list of another visual.
        void RemoveAllVisuals( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveAllVisuals();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the mode to use when composing the bitmap against the render target.
        void SetCompositeMode(DCOMPOSITION_COMPOSITE_MODE compositeMode ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCompositeMode(compositeMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionEffect : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionEffect, Unknown, IDCompositionEffect, IUnknown)
    public:
    };

    class DCompositionTransform3D : public DCompositionEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTransform3D, DCompositionEffect, IDCompositionTransform3D, IDCompositionEffect)
    public:
    };

    class DCompositionTransform : public DCompositionTransform3D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTransform, DCompositionTransform3D, IDCompositionTransform, IDCompositionTransform3D)
    public:
    };

    class DCompositionTranslateTransform : public DCompositionTransform
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTranslateTransform, DCompositionTransform, IDCompositionTranslateTransform, IDCompositionTransform)
    public:
        // Changes the value of the OffsetX property.
        void SetOffsetX(float offsetX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetX(offsetX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetX property.
        void SetOffsetX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the OffsetY property.
        void SetOffsetY(float offsetY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetY(offsetY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetY property.
        void SetOffsetY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionScaleTransform : public DCompositionTransform
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionScaleTransform, DCompositionTransform, IDCompositionScaleTransform, IDCompositionTransform)
    public:
        // Changes the value of the ScaleX property.
        void SetScaleX(float scaleX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleX(scaleX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the ScaleX property.
        void SetScaleX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the ScaleY property.
        void SetScaleY(float scaleY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleY(scaleY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the ScaleY property.
        void SetScaleY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterX property.
        void SetCenterX(float centerX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(centerX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterX property.
        void SetCenterX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterY property.
        void SetCenterY(float centerY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(centerY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterY property.
        void SetCenterY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionRotateTransform : public DCompositionTransform
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionRotateTransform, DCompositionTransform, IDCompositionRotateTransform, IDCompositionTransform)
    public:
        // Changes the value of the Angle property.
        void SetAngle(float angle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngle(angle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Angle property.
        void SetAngle(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngle(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterX property.
        void SetCenterX(float centerX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(centerX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterX property.
        void SetCenterX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterY property.
        void SetCenterY(float centerY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(centerY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterY property.
        void SetCenterY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionSkewTransform : public DCompositionTransform
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionSkewTransform, DCompositionTransform, IDCompositionSkewTransform, IDCompositionTransform)
    public:
        // Changes the value of the AngleX property.
        void SetAngleX(float angleX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngleX(angleX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the AngleX property.
        void SetAngleX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngleX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the AngleY property.
        void SetAngleY(float angleY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngleY(angleY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the AngleY property.
        void SetAngleY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngleY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterX property.
        void SetCenterX(float centerX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(centerX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterX property.
        void SetCenterX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterY property.
        void SetCenterY(float centerY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(centerY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterY property.
        void SetCenterY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionMatrixTransform : public DCompositionTransform
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionMatrixTransform, DCompositionTransform, IDCompositionMatrixTransform, IDCompositionTransform)
    public:
        // Changes all values of the matrix of this transform.
        void SetMatrix(const D2D_MATRIX_3X2_F& matrix) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrix(matrix);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes a single element of the matrix of this transform.
        void SetMatrixElement( int row, int column, float value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrixElement(row, column, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates a single element of the matrix of this transform.
        void SetMatrixElement( int row, int column, IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrixElement(row, column, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionEffectGroup : public DCompositionEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionEffectGroup, DCompositionEffect, IDCompositionEffectGroup, IDCompositionEffect)
    public:
        // Changes the opacity property.
        void SetOpacity(float opacity) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOpacity(opacity);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the opacity property
        void SetOpacity(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOpacity(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the 3D transform
        void SetTransform3D(IDCompositionTransform3D* transform3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransform3D(transform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionTranslateTransform3D : public DCompositionTransform3D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTranslateTransform3D, DCompositionTransform3D, IDCompositionTranslateTransform3D, IDCompositionTransform3D)
    public:
        // Changes the value of the OffsetX property.
        void SetOffsetX(float offsetX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetX(offsetX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetX property.
        void SetOffsetX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the OffsetY property.
        void SetOffsetY(float offsetY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetY(offsetY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetY property.
        void SetOffsetY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the OffsetZ property.
        void SetOffsetZ(float offsetZ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetZ(offsetZ);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetZ property.
        void SetOffsetZ(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetZ(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionScaleTransform3D : public DCompositionTransform3D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionScaleTransform3D, DCompositionTransform3D, IDCompositionScaleTransform3D, IDCompositionTransform3D)
    public:
        // Changes the value of the ScaleX property.
        void SetScaleX(float scaleX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleX(scaleX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the ScaleX property.
        void SetScaleX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the ScaleY property.
        void SetScaleY(float scaleY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleY(scaleY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the ScaleY property.
        void SetScaleY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the ScaleZ property.
        void SetScaleZ(float scaleZ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleZ(scaleZ);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the ScaleZ property.
        void SetScaleZ(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetScaleZ(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterX property.
        void SetCenterX(float centerX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(centerX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterX property.
        void SetCenterX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterY property.
        void SetCenterY(float centerY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(centerY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterY property.
        void SetCenterY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterZ property.
        void SetCenterZ(float centerZ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterZ(centerZ);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterZ property.
        void SetCenterZ(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterZ(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);

        }
    };

    class DCompositionRotateTransform3D : public DCompositionTransform3D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionRotateTransform3D, DCompositionTransform3D, IDCompositionRotateTransform3D, IDCompositionTransform3D)
    public:
        // Changes the value of the Angle property.
        void SetAngle(float angle) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngle(angle);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Angle property.
        void SetAngle(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngle(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the AxisX property.
        void SetAxisX(float axisX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAxisX(axisX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the AxisX property.
        void SetAxisX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAxisX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the AxisY property.
        void SetAxisY(float axisY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAxisY(axisY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the AxisY property.
        void SetAxisY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAxisY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the AxisZ property.
        void SetAxisZ(float axisZ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAxisZ(axisZ);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the AxisZ property.
        void SetAxisZ(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAxisZ(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterX property.
        void SetCenterX(float centerX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(centerX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterX property.
        void SetCenterX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterY property.
        void SetCenterY(float centerY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(centerY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterY property.
        void SetCenterY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the CenterZ property.
        void SetCenterZ(float centerZ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterZ(centerZ);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the CenterZ property.
        void SetCenterZ(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCenterZ(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionMatrixTransform3D : public DCompositionTransform3D
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionMatrixTransform3D, DCompositionTransform3D, IDCompositionMatrixTransform3D, IDCompositionTransform3D)
    public:
        // Changes all values of the matrix of this transform.
        void SetMatrix(const D3DMATRIX& matrix) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrix(matrix);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes a single element of the matrix of this transform.
        void SetMatrixElement( int row, int column, float value) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrixElement(row, column, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates a single element of the matrix of this transform.
        void SetMatrixElement( int row, int column, IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrixElement(row, column, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionClip : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionClip, Unknown, IDCompositionClip, IUnknown)
    public:

    };

    class DCompositionRectangleClip : public DCompositionClip
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionRectangleClip, DCompositionClip, IDCompositionRectangleClip, IDCompositionClip)
    public:
        // Changes the value of the Left property.
        void SetLeft(float left) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetLeft(left);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Left property.
        void SetLeft(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetLeft(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the Top property.
        void SetTop(float top) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTop(top);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Top property.
        void SetTop(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTop(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the Right property.
        void SetRight(float right) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRight(right);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Right property.
        void SetRight(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRight(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the Bottom property.
        void SetBottom(float bottom) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottom(bottom);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Bottom property.
        void SetBottom(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottom(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the x radius of the ellipse that rounds the
        // top-left corner of the clip.
        void SetTopLeftRadiusX(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopLeftRadiusX(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the x radius of the ellipse that rounds the
        // top-left corner of the clip.
        void SetTopLeftRadiusX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopLeftRadiusX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the y radius of the ellipse that rounds the
        // top-left corner of the clip.
        void SetTopLeftRadiusY(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopLeftRadiusY(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the y radius of the ellipse that rounds the
        // top-left corner of the clip.
        void SetTopLeftRadiusY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopLeftRadiusY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the x radius of the ellipse that rounds the
        // top-right corner of the clip.
        void SetTopRightRadiusX(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopRightRadiusX(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the x radius of the ellipse that rounds the
        // top-right corner of the clip.
        void SetTopRightRadiusX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopRightRadiusX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the y radius of the ellipse that rounds the
        // top-right corner of the clip.
        void SetTopRightRadiusY(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopRightRadiusY(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the y radius of the ellipse that rounds the
        // top-right corner of the clip.
        void SetTopRightRadiusY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTopRightRadiusY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the x radius of the ellipse that rounds the
        // bottom-left corner of the clip.
        void SetBottomLeftRadiusX(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomLeftRadiusX(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the x radius of the ellipse that rounds the
        // bottom-left corner of the clip.
        void SetBottomLeftRadiusX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomLeftRadiusX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the y radius of the ellipse that rounds the
        // bottom-left corner of the clip.
        void SetBottomLeftRadiusY(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomLeftRadiusY(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the y radius of the ellipse that rounds the
        // bottom-left corner of the clip.
        void SetBottomLeftRadiusY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomLeftRadiusY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the x radius of the ellipse that rounds the
        // bottom-right corner of the clip.
        void SetBottomRightRadiusX(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomRightRadiusX(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the x radius of the ellipse that rounds the
        // bottom-right corner of the clip.
        void SetBottomRightRadiusX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomRightRadiusX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the y radius of the ellipse that rounds the
        // bottom-right corner of the clip.
        void SetBottomRightRadiusY(float radius) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomRightRadiusY(radius);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the y radius of the ellipse that rounds the
        // bottom-right corner of the clip.
        void SetBottomRightRadiusY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBottomRightRadiusY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

    };

    class DCompositionSurface : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionSurface, Unknown, IDCompositionSurface, IUnknown)
    public:
        void BeginDraw(const RECT* updateRect, const Guid& iid, void** updateObject, POINT* updateOffset) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->BeginDraw(updateRect, iid, updateObject, updateOffset);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void EndDraw( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EndDraw();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SuspendDraw( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SuspendDraw();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void ResumeDraw( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->ResumeDraw();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Scroll( const RECT* scrollRect, const RECT* clipRect, int offsetX, int offsetY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Scroll(scrollRect, clipRect, offsetX, offsetY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionVirtualSurface : public DCompositionSurface
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionVirtualSurface, DCompositionSurface, IDCompositionVirtualSurface, IDCompositionSurface)
    public:
        void Resize(UINT width, UINT height) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Resize(width, height);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void Trim(const RECT* rectangles, UINT count ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Trim(rectangles, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionDevice2 : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionDevice2, Unknown, IDCompositionDevice2, IUnknown)
    public:
        // Commits all DirectComposition commands pending on this device.
        void Commit() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->Commit();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Waits for the last Commit to be processed by the composition engine
        void WaitForCommitCompletion( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->WaitForCommitCompletion();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Gets timing information about the composition engine.
        void GetFrameStatistics(DCOMPOSITION_FRAME_STATISTICS* statistics) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->GetFrameStatistics(statistics);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a new visual object.
        void CreateVisual(IDCompositionVisual2** visual) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVisual(visual);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a factory for surface objects
        void CreateSurfaceFactory(IUnknown* renderingDevice, IDCompositionSurfaceFactory** surfaceFactory) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurfaceFactory(renderingDevice, surfaceFactory);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a DirectComposition surface object
        void CreateSurface(UINT width, UINT height, DXGI_FORMAT pixelFormat, DXGI_ALPHA_MODE alphaMode, IDCompositionSurface** surface) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurface(width, height, pixelFormat, alphaMode, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a DirectComposition virtual surface object
        void CreateVirtualSurface(UINT initialWidth, UINT initialHeight, DXGI_FORMAT pixelFormat, DXGI_ALPHA_MODE alphaMode, IDCompositionVirtualSurface** virtualSurface ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVirtualSurface(initialWidth, initialHeight, pixelFormat, alphaMode, virtualSurface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D translation transform object.
        void CreateTranslateTransform(IDCompositionTranslateTransform** translateTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTranslateTransform(translateTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D scale transform object.
        void CreateScaleTransform(IDCompositionScaleTransform** scaleTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateScaleTransform(scaleTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D rotation transform object.
        void CreateRotateTransform(IDCompositionRotateTransform** rotateTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRotateTransform(rotateTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D skew transform object.
        void CreateSkewTransform(IDCompositionSkewTransform** skewTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSkewTransform(skewTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D 3x2 matrix transform object.
        void CreateMatrixTransform(IDCompositionMatrixTransform** matrixTransform) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateMatrixTransform(matrixTransform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 2D transform object that holds an array of 2D transform objects.
        void CreateTransformGroup(IDCompositionTransform** transforms, UINT numberOfTransforms, IDCompositionTransform** transformGroup) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTransformGroup(transforms, numberOfTransforms, transformGroup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D translation transform object.
        void CreateTranslateTransform3D(IDCompositionTranslateTransform3D** translateTransform3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTranslateTransform3D(translateTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D scale transform object.
        void CreateScaleTransform3D(IDCompositionScaleTransform3D** scaleTransform3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateScaleTransform3D(scaleTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D rotation transform object.
        void CreateRotateTransform3D(IDCompositionRotateTransform3D** rotateTransform3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRotateTransform3D(rotateTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D 4x4 matrix transform object.
        void CreateMatrixTransform3D(IDCompositionMatrixTransform3D** matrixTransform3D) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateMatrixTransform3D(matrixTransform3D);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a 3D transform object that holds an array of 3D transform objects.
        void CreateTransform3DGroup(IDCompositionTransform3D** transforms3D, UINT numberOfTransforms3D,IDCompositionTransform3D** transform3DGroup) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTransform3DGroup(transforms3D, numberOfTransforms3D, transform3DGroup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates an effect group
        void CreateEffectGroup(IDCompositionEffectGroup** effectGroup) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateEffectGroup(effectGroup);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a clip object that can be used to clip the contents of a visual subtree.
        void CreateRectangleClip(IDCompositionRectangleClip** clip) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateRectangleClip(clip);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates an animation object
        void CreateAnimation(IDCompositionAnimation** animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateAnimation(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionDesktopDevice : public DCompositionDevice2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionDesktopDevice, DCompositionDevice2, IDCompositionDesktopDevice, IDCompositionDevice2)
    public:
        void CreateTargetForHwnd(HWND hwnd, BOOL topmost, IDCompositionTarget** target) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTargetForHwnd(hwnd, topmost, target);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a surface wrapper around a pre-existing surface that can be associated with one or more visuals for composition.
        void CreateSurfaceFromHandle(HANDLE handle, IUnknown** surface) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurfaceFromHandle(handle, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a wrapper object that represents the rasterization of a layered window and which can be associated with a visual for composition.
        void CreateSurfaceFromHwnd(HWND hwnd, IUnknown** surface) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurfaceFromHwnd(hwnd, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionDeviceDebug : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionDeviceDebug, Unknown, IDCompositionDeviceDebug, IUnknown)
    public:
        // Enables debug counters
        void EnableDebugCounters() const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnableDebugCounters();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Enables debug counters
        void DisableDebugCounters( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DisableDebugCounters();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionSurfaceFactory : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionSurfaceFactory, Unknown, IDCompositionSurfaceFactory, IUnknown)
    public:
        // Creates a DirectComposition surface object
        void CreateSurface(UINT width, UINT height, DXGI_FORMAT pixelFormat, DXGI_ALPHA_MODE alphaMode, IDCompositionSurface** surface) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSurface(width, height, pixelFormat, alphaMode, surface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Creates a DirectComposition virtual surface object
        void CreateVirtualSurface(UINT initialWidth, UINT initialHeight, DXGI_FORMAT pixelFormat, DXGI_ALPHA_MODE alphaMode, IDCompositionVirtualSurface** virtualSurface) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateVirtualSurface(initialWidth, initialHeight, pixelFormat, alphaMode, virtualSurface);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionVisual2 : public DCompositionVisual
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionVisual2, DCompositionVisual, IDCompositionVisual2, IDCompositionVisual)
    public:
        // Changes the interpretation of the opacity property of an effect group
    // associated with this visual
        void SetOpacityMode(DCOMPOSITION_OPACITY_MODE mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOpacityMode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets back face visibility
        void SetBackFaceVisibility(DCOMPOSITION_BACKFACE_VISIBILITY visibility) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBackFaceVisibility(visibility);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionVisualDebug : public DCompositionVisual2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionVisualDebug, DCompositionVisual2, IDCompositionVisualDebug, IDCompositionVisual2)
    public:
        // Enable heat map
        void EnableHeatMap(const D2D1_COLOR_F& color) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnableHeatMap(color);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Disable heat map
        void DisableHeatMap( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DisableHeatMap();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Enable redraw regions
        void EnableRedrawRegions( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->EnableRedrawRegions();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Disable redraw regions
        void DisableRedrawRegions( ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->DisableRedrawRegions();
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionVisual3 : public DCompositionVisualDebug
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionVisual3, DCompositionVisualDebug, IDCompositionVisual3, IDCompositionVisualDebug)
    public:
        // Sets depth mode property associated with this visual
        void SetDepthMode(DCOMPOSITION_DEPTH_MODE mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetDepthMode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of OffsetZ property.
        void SetOffsetZ( float offsetZ ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetZ(offsetZ);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the OffsetZ property.
        void SetOffsetZ( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffsetZ(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the Opacity property.
        void SetOpacity( float opacity ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOpacity(opacity);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates the value of the Opacity property.
        void SetOpacity( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOpacity(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the matrix that modifies the coordinate system of this visual.
        void SetTransform( const D2D_MATRIX_4X4_F& matrix ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransform(matrix);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the transformation object that modifies the coordinate system of this visual.
        void SetTransform( IDCompositionTransform3D* transform ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransform(transform);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of the Visible property
        void SetVisible( BOOL visible ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetVisible(visible);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionDevice3 : public DCompositionDevice2
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionDevice3, DCompositionDevice2, IDCompositionDevice3, IDCompositionDevice2)
    public:
        // Effect creation calls, each creates an interface around a D2D1Effect
        void CreateGaussianBlurEffect(IDCompositionGaussianBlurEffect** gaussianBlurEffect) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateGaussianBlurEffect(gaussianBlurEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateBrightnessEffect( IDCompositionBrightnessEffect** brightnessEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateBrightnessEffect(brightnessEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateColorMatrixEffect( IDCompositionColorMatrixEffect** colorMatrixEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateColorMatrixEffect(colorMatrixEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateShadowEffect( IDCompositionShadowEffect** shadowEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateShadowEffect(shadowEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateHueRotationEffect( IDCompositionHueRotationEffect** hueRotationEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateHueRotationEffect(hueRotationEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateSaturationEffect( IDCompositionSaturationEffect** saturationEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateSaturationEffect(saturationEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateTurbulenceEffect( IDCompositionTurbulenceEffect** turbulenceEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTurbulenceEffect(turbulenceEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateLinearTransferEffect( IDCompositionLinearTransferEffect** linearTransferEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateLinearTransferEffect(linearTransferEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateTableTransferEffect( IDCompositionTableTransferEffect** tableTransferEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateTableTransferEffect(tableTransferEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateCompositeEffect( IDCompositionCompositeEffect** compositeEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateCompositeEffect(compositeEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateBlendEffect( IDCompositionBlendEffect** blendEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateBlendEffect(blendEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateArithmeticCompositeEffect( IDCompositionArithmeticCompositeEffect** arithmeticCompositeEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateArithmeticCompositeEffect(arithmeticCompositeEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateAffineTransform2DEffect( IDCompositionAffineTransform2DEffect** affineTransform2dEffect ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateAffineTransform2DEffect(affineTransform2dEffect);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionFilterEffect : public DCompositionEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionFilterEffect, DCompositionEffect, IDCompositionFilterEffect, IDCompositionEffect)
    public:
        void SetInput(UINT index, IUnknown* input, UINT flags) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInput(index, input, flags);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionGaussianBlurEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionGaussianBlurEffect, DCompositionFilterEffect, IDCompositionGaussianBlurEffect, IDCompositionFilterEffect)
    public:
        // Changes the amount of blur to be applied.
        void SetStandardDeviation(float amount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStandardDeviation(amount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetStandardDeviation(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStandardDeviation(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes border mode (see D2D1_GAUSSIANBLUR)
        void SetBorderMode( D2D1_BORDER_MODE mode ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBorderMode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionBrightnessEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionBrightnessEffect, DCompositionFilterEffect, IDCompositionBrightnessEffect, IDCompositionFilterEffect)
    public:
        // Changes the value of white point property.
        void SetWhitePoint(const D2D1_VECTOR_2F& whitePoint) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWhitePoint(whitePoint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the value of black point property
        void SetBlackPoint(const D2D1_VECTOR_2F& blackPoint ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlackPoint(blackPoint);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the X value of the white point property.
        void SetWhitePointX(float whitePointX ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWhitePointX(whitePointX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetWhitePointX(IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWhitePointX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the Y value of the white point property.
        void SetWhitePointY(float whitePointY ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWhitePointY(whitePointY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetWhitePointY(IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetWhitePointY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the X value of the black point property.
        void SetBlackPointX(float blackPointX) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlackPointX(blackPointX);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlackPointX(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlackPointX(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the Y value of the black point property.
        void SetBlackPointY(float blackPointY) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlackPointY(blackPointY);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlackPointY(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlackPointY(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionColorMatrixEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionColorMatrixEffect, DCompositionFilterEffect, IDCompositionColorMatrixEffect, IDCompositionFilterEffect)
    public:
        // Changes all values of the matrix for a color transform
        void SetMatrix(const D2D1_MATRIX_5X4_F& matrix) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrix(matrix);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes a single element of the matrix of this color transform.
        void SetMatrixElement( int row, int column, float value ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrixElement(row, column, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Animates a single element of the matrix of this color transform.
        void SetMatrixElement( int row, int column, IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMatrixElement(row, column, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the alpha mode
        void SetAlphaMode( D2D1_COLORMATRIX_ALPHA_MODE mode ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaMode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the clamp output property
        void SetClampOutput(BOOL clamp ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetClampOutput(clamp);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionShadowEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionShadowEffect, DCompositionFilterEffect, IDCompositionShadowEffect, IDCompositionFilterEffect)
    public:
        // Changes the amount of blur to be applied.
        void SetStandardDeviation(float amount ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStandardDeviation(amount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetStandardDeviation(IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStandardDeviation(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes shadow color
        void SetColor(const D2D1_VECTOR_4F& color) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetColor(color);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRed(float amount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRed(amount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRed(IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRed(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreen( float amount ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreen(amount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreen( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreen(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlue( float amount ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlue(amount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlue(IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlue(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlpha(float amount) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlpha(amount);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlpha( IDCompositionAnimation* animation) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlpha(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionHueRotationEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionHueRotationEffect, DCompositionFilterEffect, IDCompositionHueRotationEffect, IDCompositionFilterEffect)
    public:
        // Changes the angle of rotation
        void SetAngle(float amountDegrees) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngle(amountDegrees);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAngle( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAngle(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionSaturationEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionSaturationEffect, DCompositionFilterEffect, IDCompositionSaturationEffect, IDCompositionFilterEffect)
    public:
        // Changes the amount of saturation to be applied.
        void SetSaturation(float ratio) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSaturation(ratio);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSaturation( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSaturation(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };


    class DCompositionTurbulenceEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTurbulenceEffect, DCompositionFilterEffect, IDCompositionTurbulenceEffect, IDCompositionFilterEffect)
    public:
        // Changes the starting offset of the turbulence
        void SetOffset(const D2D1_VECTOR_2F& offset) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetOffset(offset);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the base frequency of the turbulence
        void SetBaseFrequency(const D2D1_VECTOR_2F& frequency ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBaseFrequency(frequency);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Changes the output size of the turbulence
        void SetSize( const D2D1_VECTOR_2F& size ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSize(size);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Sets the number of octaves
        void SetNumOctaves( UINT numOctaves ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetNumOctaves(numOctaves);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Set the random number seed
        void SetSeed( UINT seed ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSeed(seed);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Set the noise mode
        void SetNoise( D2D1_TURBULENCE_NOISE noise ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetNoise(noise);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Set stitchable
        void SetStitchable( BOOL stitchable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetStitchable(stitchable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionLinearTransferEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionLinearTransferEffect, DCompositionFilterEffect, IDCompositionLinearTransferEffect, IDCompositionFilterEffect)
    public:
        void SetRedYIntercept(float redYIntercept) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedYIntercept(redYIntercept);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRedYIntercept( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedYIntercept(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRedSlope( float redSlope ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedSlope(redSlope);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRedSlope( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedSlope(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRedDisable( BOOL redDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedDisable(redDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenYIntercept( float greenYIntercept ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenYIntercept(greenYIntercept);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenYIntercept( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenYIntercept(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenSlope( float greenSlope ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenSlope(greenSlope);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenSlope( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenSlope(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenDisable( BOOL greenDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenDisable(greenDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueYIntercept( float blueYIntercept ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueYIntercept(blueYIntercept);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueYIntercept( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueYIntercept(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueSlope( float blueSlope ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueSlope(blueSlope);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueSlope( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueSlope(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueDisable( BOOL blueDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueDisable(blueDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaYIntercept( float alphaYIntercept ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaYIntercept(alphaYIntercept);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaYIntercept( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaYIntercept(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaSlope( float alphaSlope ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaSlope(alphaSlope);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaSlope( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaSlope(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaDisable( BOOL alphaDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaDisable(alphaDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetClampOutput( BOOL clampOutput ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetClampOutput(clampOutput);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionTableTransferEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionTableTransferEffect, DCompositionFilterEffect, IDCompositionTableTransferEffect, IDCompositionFilterEffect)
    public:
        void SetRedTable(const float* tableValues, UINT count) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedTable(tableValues, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenTable( const float* tableValues, UINT count ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenTable(tableValues, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueTable( const float* tableValues, UINT count ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueTable(tableValues, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaTable( const float* tableValues, UINT count ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaTable(tableValues, count);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRedDisable( BOOL redDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedDisable(redDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenDisable( BOOL greenDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenDisable(greenDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueDisable( BOOL blueDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueDisable(blueDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaDisable( BOOL alphaDisable ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaDisable(alphaDisable);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetClampOutput( BOOL clampOutput ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetClampOutput(clampOutput);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Note:  To set individual values, the table must have already been initialized
        //        with a buffer of values of the appropriate size, or these calls will fail
        void SetRedTableValue( UINT index, float value ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedTableValue(index, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetRedTableValue( UINT index, IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetRedTableValue(index, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenTableValue( UINT index, float value ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenTableValue(index, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetGreenTableValue( UINT index, IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetGreenTableValue(index, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueTableValue( UINT index, float value ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueTableValue(index, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBlueTableValue( UINT index, IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBlueTableValue(index, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaTableValue( UINT index, float value ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaTableValue(index, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetAlphaTableValue( UINT index, IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetAlphaTableValue(index, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionCompositeEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionCompositeEffect, DCompositionFilterEffect, IDCompositionCompositeEffect, IDCompositionFilterEffect)
    public:
        // Changes the composite mode.
        void SetMode(D2D1_COMPOSITE_MODE mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionBlendEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionBlendEffect, DCompositionFilterEffect, IDCompositionBlendEffect, IDCompositionFilterEffect)
    public:
        void SetMode(D2D1_BLEND_MODE mode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetMode(mode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionArithmeticCompositeEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionArithmeticCompositeEffect, DCompositionFilterEffect, IDCompositionArithmeticCompositeEffect, IDCompositionFilterEffect)
    public:
        void SetCoefficients(const D2D1_VECTOR_4F& coefficients) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficients(coefficients);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetClampOutput( BOOL clampoutput ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetClampOutput(clampoutput);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient1( float Coeffcient1 ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient1(Coeffcient1);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient1( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient1(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient2( float Coefficient2 ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient2(Coefficient2);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient2( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient2(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient3( float Coefficient3 ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient3(Coefficient3);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient3( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient3(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient4( float Coefficient4 ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient4(Coefficient4);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetCoefficient4( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetCoefficient4(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionAffineTransform2DEffect : public DCompositionFilterEffect
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionAffineTransform2DEffect, DCompositionFilterEffect, IDCompositionAffineTransform2DEffect, IDCompositionFilterEffect)
    public:
        void SetInterpolationMode(D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE interpolationMode) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetInterpolationMode(interpolationMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetBorderMode( D2D1_BORDER_MODE borderMode ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetBorderMode(borderMode);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetTransformMatrix( const D2D1_MATRIX_3X2_F& transformMatrix ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransformMatrix(transformMatrix);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetTransformMatrixElement( int row, int column, float value ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransformMatrixElement(row, column, value);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetTransformMatrixElement( int row, int column, IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetTransformMatrixElement(row, column, animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSharpness( float sharpness ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSharpness(sharpness);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void SetSharpness( IDCompositionAnimation* animation ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->SetSharpness(animation);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionDelegatedInkTrail : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionDelegatedInkTrail, Unknown, IDCompositionDelegatedInkTrail, IUnknown)
    public:
        void AddTrailPoints(const DCompositionInkTrailPoint* inkPoints, UINT inkPointsCount, UINT* generationId) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddTrailPoints(inkPoints, inkPointsCount, generationId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        // Returns a generation id to be used when removing points later
        void AddTrailPointsWithPrediction(const DCompositionInkTrailPoint* inkPoints, UINT inkPointsCount, const DCompositionInkTrailPoint* predictedInkPoints, UINT predictedInkPointsCount, UINT* generationId ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->AddTrailPointsWithPrediction(inkPoints, inkPointsCount, predictedInkPoints, predictedInkPointsCount, generationId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void RemoveTrailPoints( UINT generationId ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->RemoveTrailPoints(generationId);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void StartNewTrail(const D2D1_COLOR_F& color ) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->StartNewTrail(color);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };

    class DCompositionInkTrailDevice : public Unknown
    {
    public:
        HCC_COM_STANDARD_METHODS_IMPL(DCompositionInkTrailDevice, Unknown, IDCompositionInkTrailDevice, IUnknown)
    public:
        void CreateDelegatedInkTrail(IDCompositionDelegatedInkTrail** inkTrail) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDelegatedInkTrail(inkTrail);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }

        void CreateDelegatedInkTrailForSwapChain(IUnknown* swapChain, IDCompositionDelegatedInkTrail** inkTrail) const
        {
            InterfaceType* pInterface = GetInterface();
            HRESULT hr = pInterface->CreateDelegatedInkTrailForSwapChain(swapChain, inkTrail);
            HCC_COM_CHECK_HRESULT2(hr, pInterface);
        }
    };



}

#endif
