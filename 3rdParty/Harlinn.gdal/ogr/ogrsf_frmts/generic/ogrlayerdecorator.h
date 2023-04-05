/******************************************************************************
 * $Id$
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Defines OGRLayerDecorator class
 * Author:   Even Rouault, even dot rouault at spatialys.com
 *
 ******************************************************************************
 * Copyright (c) 2012-2013, Even Rouault <even dot rouault at spatialys.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#ifndef OGRLAYERDECORATOR_H_INCLUDED
#define OGRLAYERDECORATOR_H_INCLUDED

#ifndef DOXYGEN_SKIP

#include <ogr/ogrsf_frmts/ogrsf_frmts.h>

class OGRLayerDecorator : public OGRLayer
{
    CPL_DISALLOW_COPY_ASSIGN(OGRLayerDecorator)

  protected:
    OGRLayer *m_poDecoratedLayer;
    int       m_bHasOwnership;

  public:

    HGDAL_EXPORT                    OGRLayerDecorator(OGRLayer* poDecoratedLayer,
                                         int bTakeOwnership);
    HGDAL_EXPORT virtual           ~OGRLayerDecorator();

    HGDAL_EXPORT virtual OGRGeometry *GetSpatialFilter() override;
    HGDAL_EXPORT virtual void        SetSpatialFilter( OGRGeometry * ) override;
    HGDAL_EXPORT virtual void        SetSpatialFilterRect( double dfMinX, double dfMinY,
                                              double dfMaxX, double dfMaxY ) override;
    HGDAL_EXPORT virtual void        SetSpatialFilter( int iGeomField, OGRGeometry * ) override;
    HGDAL_EXPORT virtual void        SetSpatialFilterRect( int iGeomField, double dfMinX, double dfMinY,
                                              double dfMaxX, double dfMaxY ) override;

    HGDAL_EXPORT virtual OGRErr      SetAttributeFilter( const char * ) override;

    HGDAL_EXPORT virtual void        ResetReading() override;
    HGDAL_EXPORT virtual OGRFeature *GetNextFeature() override;
    HGDAL_EXPORT virtual OGRErr      SetNextByIndex( GIntBig nIndex ) override;
    HGDAL_EXPORT virtual OGRFeature *GetFeature( GIntBig nFID ) override;
    HGDAL_EXPORT virtual OGRErr      ISetFeature( OGRFeature *poFeature ) override;
    HGDAL_EXPORT virtual OGRErr      ICreateFeature( OGRFeature *poFeature ) override;
    HGDAL_EXPORT virtual OGRErr      DeleteFeature( GIntBig nFID ) override;

    HGDAL_EXPORT virtual const char *GetName() override;
    HGDAL_EXPORT virtual OGRwkbGeometryType GetGeomType() override;
    HGDAL_EXPORT virtual OGRFeatureDefn *GetLayerDefn() override;

    HGDAL_EXPORT virtual OGRSpatialReference *GetSpatialRef() override;

    HGDAL_EXPORT virtual GIntBig     GetFeatureCount( int bForce = TRUE ) override;
    HGDAL_EXPORT virtual OGRErr      GetExtent(int iGeomField, OGREnvelope *psExtent, int bForce = TRUE) override;
    HGDAL_EXPORT virtual OGRErr      GetExtent(OGREnvelope *psExtent, int bForce = TRUE) override;

    HGDAL_EXPORT virtual int         TestCapability( const char * ) override;

    HGDAL_EXPORT virtual OGRErr      CreateField( OGRFieldDefn *poField,
                                     int bApproxOK = TRUE ) override;
    HGDAL_EXPORT virtual OGRErr      DeleteField( int iField ) override;
    HGDAL_EXPORT virtual OGRErr      ReorderFields( int* panMap ) override;
    HGDAL_EXPORT virtual OGRErr      AlterFieldDefn( int iField, OGRFieldDefn* poNewFieldDefn, int nFlags ) override;

    HGDAL_EXPORT virtual OGRErr      CreateGeomField( OGRGeomFieldDefn *poField,
                                         int bApproxOK = TRUE ) override;

    HGDAL_EXPORT virtual OGRErr      SyncToDisk() override;

    HGDAL_EXPORT virtual OGRStyleTable *GetStyleTable() override;
    HGDAL_EXPORT virtual void        SetStyleTableDirectly( OGRStyleTable *poStyleTable ) override;

    HGDAL_EXPORT virtual void        SetStyleTable(OGRStyleTable *poStyleTable) override;

    HGDAL_EXPORT virtual OGRErr      StartTransaction() override;
    HGDAL_EXPORT virtual OGRErr      CommitTransaction() override;
    HGDAL_EXPORT virtual OGRErr      RollbackTransaction() override;

    HGDAL_EXPORT virtual const char *GetFIDColumn() override;
    HGDAL_EXPORT virtual const char *GetGeometryColumn() override;

    HGDAL_EXPORT virtual OGRErr      SetIgnoredFields( const char **papszFields ) override;

    HGDAL_EXPORT virtual char      **GetMetadata( const char * pszDomain = "" ) override;
    HGDAL_EXPORT virtual CPLErr      SetMetadata( char ** papszMetadata,
                                     const char * pszDomain = "" ) override;
    HGDAL_EXPORT virtual const char *GetMetadataItem( const char * pszName,
                                         const char * pszDomain = "" ) override;
    HGDAL_EXPORT virtual CPLErr      SetMetadataItem( const char * pszName,
                                         const char * pszValue,
                                         const char * pszDomain = "" ) override;

    OGRLayer* GetBaseLayer() const { return m_poDecoratedLayer; }
};

#endif /* #ifndef DOXYGEN_SKIP */

#endif // OGRLAYERDECORATOR_H_INCLUDED
