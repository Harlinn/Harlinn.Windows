// Copyright 2009, Google Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Google Inc. nor the names of its contributors may be
//     used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// WARNING: THE VISITOR API IMPLEMENTED IN THIS CLASS IS EXPERIMENTAL AND
// SUBJECT TO CHANGE WITHOUT WARNING.

#ifndef KML_DOM_VISITOR_H__
#define KML_DOM_VISITOR_H__

#include <vector>
#include "kml/base/util.h"
#include "kml/dom/kml_ptr.h"

#include "kmldomdef.h"

namespace kmldom {

// A base class implementing a visitor for elements in a kml dom hierarchy.
// This class should be extended to implement specific visitors by overriding
// the approriate VisitXxx() methods.
//
// The Visitor base class will ensure that the expected visit methods are
// invoked even if the element being visited is a sub-type of the element for
// which VisitXxx() was overridden. For example, if VisitContainer() is
// overridden by a subclass then it will be called for any Container elements
// visited, such as Document or Folder.
//
// If you wish to visit an element for several types (for example Container and
// Feature) using a single visitor, the sub-type visit methods should invoke
// their parent class method:
//
// void MyVisitor::VisitContainer(const ContainerPtr& container) {
//   // do stuff
//   Visitor::VisitContainer(container);  // calls VisitFeature()
// }
//
// A visitation over an element hierarchy is controlled by a VisitorDriver
// instance. The choice of driver can affect the order in which elements are
// visited and it is up to the user to select an appropriate driver for their
// needs. A visitor has no requirement to manage the visitation of its child
// elements as this is handled by the chosen driver, although a visitor is free
// to operate on its child elements directly if it so chooses.
//
// In typical usage processing an element hierarchy might look something like:
//
// const KmlPtr& root = GetRootElement();
// MyVisitor visitor();
// SimplePreorderDriver(visitor).Visit(root);
// ProcessResults(visitor.GetResults());
//
class Visitor {
 protected:
  KMLDOM_EXPORT Visitor();

 public:
  KMLDOM_EXPORT virtual ~Visitor();

  KMLDOM_EXPORT virtual void VisitElement(const ElementPtr& node);

  KMLDOM_EXPORT virtual void VisitAbstractLatLonBox(
      const AbstractLatLonBoxPtr& element);

  KMLDOM_EXPORT virtual void VisitAbstractLink(
      const AbstractLinkPtr& element);

  KMLDOM_EXPORT virtual void VisitAbstractView(
      const AbstractViewPtr& element);

  KMLDOM_EXPORT virtual void VisitAlias(
      const AliasPtr& element);

  KMLDOM_EXPORT virtual void VisitBalloonStyle(
      const BalloonStylePtr& element);

  KMLDOM_EXPORT virtual void VisitBasicLink(
      const BasicLinkPtr& element);

  KMLDOM_EXPORT virtual void VisitCamera(
      const CameraPtr& element);

  KMLDOM_EXPORT virtual void VisitChange(
      const ChangePtr& element);

  KMLDOM_EXPORT virtual void VisitColorStyle(
      const ColorStylePtr& element);

  KMLDOM_EXPORT virtual void VisitContainer(
      const ContainerPtr& element);

  KMLDOM_EXPORT virtual void VisitCoordinates(
      const CoordinatesPtr& element);

  KMLDOM_EXPORT virtual void VisitCreate(
      const CreatePtr& element);

  KMLDOM_EXPORT virtual void VisitData(
      const DataPtr& element);

  KMLDOM_EXPORT virtual void VisitDelete(
      const DeletePtr& element);

  KMLDOM_EXPORT virtual void VisitDocument(
      const DocumentPtr& element);

  KMLDOM_EXPORT virtual void VisitExtendedData(
      const ExtendedDataPtr& element);

  KMLDOM_EXPORT virtual void VisitFeature(
      const FeaturePtr& element);

  KMLDOM_EXPORT virtual void VisitField(
      const FieldPtr& element);

  KMLDOM_EXPORT virtual void VisitFolder(
      const FolderPtr& element);

  KMLDOM_EXPORT virtual void VisitGeometry(
      const GeometryPtr& element);

  KMLDOM_EXPORT virtual void VisitGroundOverlay(
      const GroundOverlayPtr& element);

  KMLDOM_EXPORT virtual void VisitGxAnimatedUpdate(
      const GxAnimatedUpdatePtr& element);

  KMLDOM_EXPORT virtual void VisitGxFlyTo(
      const GxFlyToPtr& element);

  KMLDOM_EXPORT virtual void VisitGxLatLonQuad(
      const GxLatLonQuadPtr& element);

  KMLDOM_EXPORT virtual void VisitGxMultiTrack(
      const GxMultiTrackPtr& element);

  KMLDOM_EXPORT virtual void VisitGxPlaylist(
      const GxPlaylistPtr& element);

  KMLDOM_EXPORT virtual void VisitGxSimpleArrayData(
      const GxSimpleArrayDataPtr& element);

  KMLDOM_EXPORT virtual void VisitGxSimpleArrayField(
      const GxSimpleArrayFieldPtr& element);

  KMLDOM_EXPORT virtual void VisitGxSoundCue(
      const GxSoundCuePtr& element);

  KMLDOM_EXPORT virtual void VisitGxTimeSpan(
      const GxTimeSpanPtr& element);

  KMLDOM_EXPORT virtual void VisitGxTimeStamp(
      const GxTimeStampPtr& element);

  KMLDOM_EXPORT virtual void VisitGxTour(
      const GxTourPtr& element);

  KMLDOM_EXPORT virtual void VisitGxTourControl(
      const GxTourControlPtr& element);

  KMLDOM_EXPORT virtual void VisitGxTourPrimitive(
      const GxTourPrimitivePtr& element);

  KMLDOM_EXPORT virtual void VisitGxTrack(
      const GxTrackPtr& element);

  KMLDOM_EXPORT virtual void VisitGxWait(
      const GxWaitPtr& element);

  KMLDOM_EXPORT virtual void VisitHotSpot(
      const HotSpotPtr& element);

  KMLDOM_EXPORT virtual void VisitIcon(
      const IconPtr& element);

  KMLDOM_EXPORT virtual void VisitIconStyle(
      const IconStylePtr& element);

  KMLDOM_EXPORT virtual void VisitIconStyleIcon(
      const IconStyleIconPtr& element);

  KMLDOM_EXPORT virtual void VisitImagePyramid(
      const ImagePyramidPtr& element);

  KMLDOM_EXPORT virtual void VisitInnerBoundaryIs(
      const InnerBoundaryIsPtr& element);

  KMLDOM_EXPORT virtual void VisitItemIcon(
      const ItemIconPtr& element);

  KMLDOM_EXPORT virtual void VisitKml(
      const KmlPtr& element);

  KMLDOM_EXPORT virtual void VisitLabelStyle(
      const LabelStylePtr& element);

  KMLDOM_EXPORT virtual void VisitLatLonAltBox(
      const LatLonAltBoxPtr& element);

  KMLDOM_EXPORT virtual void VisitLatLonBox(
      const LatLonBoxPtr& element);

  KMLDOM_EXPORT virtual void VisitLineString(
      const LineStringPtr& element);

  KMLDOM_EXPORT virtual void VisitLineStyle(
      const LineStylePtr& element);

  KMLDOM_EXPORT virtual void VisitLinearRing(
      const LinearRingPtr& element);

  KMLDOM_EXPORT virtual void VisitLink(
      const LinkPtr& element);

  KMLDOM_EXPORT virtual void VisitLinkSnippet(
      const LinkSnippetPtr& element);

  KMLDOM_EXPORT virtual void VisitListStyle(
      const ListStylePtr& element);

  KMLDOM_EXPORT virtual void VisitLocation(
      const LocationPtr& element);

  KMLDOM_EXPORT virtual void VisitLod(
      const LodPtr& element);

  KMLDOM_EXPORT virtual void VisitLookAt(
      const LookAtPtr& element);

  KMLDOM_EXPORT virtual void VisitMetadata(
      const MetadataPtr& element);

  KMLDOM_EXPORT virtual void VisitModel(
      const ModelPtr& element);

  KMLDOM_EXPORT virtual void VisitMultiGeometry(
      const MultiGeometryPtr& element);

  KMLDOM_EXPORT virtual void VisitNetworkLink(
      const NetworkLinkPtr& element);

  KMLDOM_EXPORT virtual void VisitNetworkLinkControl(
      const NetworkLinkControlPtr& element);

  KMLDOM_EXPORT virtual void VisitObject(
      const ObjectPtr& element);

  KMLDOM_EXPORT virtual void VisitOrientation(
      const OrientationPtr& element);

  KMLDOM_EXPORT virtual void VisitOuterBoundaryIs(
      const OuterBoundaryIsPtr& element);

  KMLDOM_EXPORT virtual void VisitOverlay(
      const OverlayPtr& element);

  KMLDOM_EXPORT virtual void VisitOverlayXY(
      const OverlayXYPtr& element);

  KMLDOM_EXPORT virtual void VisitPair(
      const PairPtr& element);

  KMLDOM_EXPORT virtual void VisitPhotoOverlay(
      const PhotoOverlayPtr& element);

  KMLDOM_EXPORT virtual void VisitPlacemark(
      const PlacemarkPtr& element);

  KMLDOM_EXPORT virtual void VisitPoint(
      const PointPtr& element);

  KMLDOM_EXPORT virtual void VisitPolyStyle(
      const PolyStylePtr& element);

  KMLDOM_EXPORT virtual void VisitPolygon(
      const PolygonPtr& element);

  KMLDOM_EXPORT virtual void VisitRegion(
      const RegionPtr& element);

  KMLDOM_EXPORT virtual void VisitResourceMap(
      const ResourceMapPtr& element);

  KMLDOM_EXPORT virtual void VisitRotationXY(
      const RotationXYPtr& element);

  KMLDOM_EXPORT virtual void VisitScale(
      const ScalePtr& element);

  KMLDOM_EXPORT virtual void VisitSchema(
      const SchemaPtr& element);

  KMLDOM_EXPORT virtual void VisitSchemaData(
      const SchemaDataPtr& element);

  KMLDOM_EXPORT virtual void VisitScreenOverlay(
      const ScreenOverlayPtr& element);

  KMLDOM_EXPORT virtual void VisitScreenXY(
      const ScreenXYPtr& element);

  KMLDOM_EXPORT virtual void VisitSimpleData(
      const SimpleDataPtr& element);

  KMLDOM_EXPORT virtual void VisitSimpleField(
      const SimpleFieldPtr& element);

  KMLDOM_EXPORT virtual void VisitSize(
      const SizePtr& element);

  KMLDOM_EXPORT virtual void VisitSnippet(
      const SnippetPtr& element);

  KMLDOM_EXPORT virtual void VisitStyle(
      const StylePtr& element);

  KMLDOM_EXPORT virtual void VisitStyleMap(
      const StyleMapPtr& element);

  KMLDOM_EXPORT virtual void VisitStyleSelector(
      const StyleSelectorPtr& element);

  KMLDOM_EXPORT virtual void VisitSubStyle(
      const SubStylePtr& element);

  KMLDOM_EXPORT virtual void VisitTimePrimitive(
      const TimePrimitivePtr& element);

  KMLDOM_EXPORT virtual void VisitTimeSpan(
      const TimeSpanPtr& element);

  KMLDOM_EXPORT virtual void VisitTimeStamp(
      const TimeStampPtr& element);

  KMLDOM_EXPORT virtual void VisitUpdate(
      const UpdatePtr& element);

  KMLDOM_EXPORT virtual void VisitUpdateOperation(
      const UpdateOperationPtr& element);

  KMLDOM_EXPORT virtual void VisitUrl(
      const UrlPtr& element);

  KMLDOM_EXPORT virtual void VisitVec2(
      const Vec2Ptr& element);

  KMLDOM_EXPORT virtual void VisitViewVolume(
      const ViewVolumePtr& element);

  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(Visitor);
};

}  // end namespace kmldom

#endif  // KML_DOM_VISITOR_H__
