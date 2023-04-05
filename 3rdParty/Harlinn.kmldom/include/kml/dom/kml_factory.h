// Copyright 2008, Google Inc. All rights reserved.
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

#ifndef KML_DOM_KML_FACTORY_H__
#define KML_DOM_KML_FACTORY_H__

#include <string>
#include "kml/dom/kmldom.h"
#include "kml/base/util.h"

namespace kmldom {

// A singleton factory class.
class KmlFactory {
 public:
  KMLDOM_EXPORT static KmlFactory* GetFactory();

  // Factory functions used by the parser to create any KML element.
  KMLDOM_EXPORT ElementPtr CreateElementById(KmlDomType id) const;
  KMLDOM_EXPORT ElementPtr CreateElementFromName(const string& element_name) const;
  KMLDOM_EXPORT Field* CreateFieldById(KmlDomType type_id) const;

  // Factory functions to create all KML complex elements.
  KMLDOM_EXPORT Alias* CreateAlias() const;
  KMLDOM_EXPORT AtomAuthor* CreateAtomAuthor() const;
  KMLDOM_EXPORT AtomCategory* CreateAtomCategory() const;
  KMLDOM_EXPORT AtomContent* CreateAtomContent() const;
  KMLDOM_EXPORT AtomEntry* CreateAtomEntry() const;
  KMLDOM_EXPORT AtomFeed* CreateAtomFeed() const;
  KMLDOM_EXPORT AtomLink* CreateAtomLink() const;
  KMLDOM_EXPORT BalloonStyle* CreateBalloonStyle() const;
  KMLDOM_EXPORT Coordinates* CreateCoordinates() const;
  KMLDOM_EXPORT Camera* CreateCamera() const;
  KMLDOM_EXPORT Change* CreateChange() const;
  KMLDOM_EXPORT Create* CreateCreate() const;
  KMLDOM_EXPORT Data* CreateData() const;
  KMLDOM_EXPORT Delete* CreateDelete() const;
  KMLDOM_EXPORT Document* CreateDocument() const;
  KMLDOM_EXPORT ExtendedData* CreateExtendedData() const;
  KMLDOM_EXPORT Folder* CreateFolder() const;
  KMLDOM_EXPORT GroundOverlay* CreateGroundOverlay() const;
  KMLDOM_EXPORT HotSpot* CreateHotSpot() const;
  KMLDOM_EXPORT Icon* CreateIcon() const;
  KMLDOM_EXPORT IconStyle* CreateIconStyle() const;
  KMLDOM_EXPORT IconStyleIcon* CreateIconStyleIcon() const;
  KMLDOM_EXPORT ImagePyramid* CreateImagePyramid() const;
  KMLDOM_EXPORT InnerBoundaryIs* CreateInnerBoundaryIs() const;
  KMLDOM_EXPORT ItemIcon* CreateItemIcon() const;
  KMLDOM_EXPORT Kml* CreateKml() const;
  KMLDOM_EXPORT LabelStyle* CreateLabelStyle() const;
  KMLDOM_EXPORT LatLonBox* CreateLatLonBox() const;
  KMLDOM_EXPORT LatLonAltBox* CreateLatLonAltBox() const;
  KMLDOM_EXPORT LinearRing* CreateLinearRing() const;
  KMLDOM_EXPORT LineString* CreateLineString() const;
  KMLDOM_EXPORT LineStyle* CreateLineStyle() const;
  KMLDOM_EXPORT Link* CreateLink() const;
  KMLDOM_EXPORT LinkSnippet* CreateLinkSnippet() const;
  KMLDOM_EXPORT ListStyle* CreateListStyle() const;
  KMLDOM_EXPORT Location* CreateLocation() const;
  KMLDOM_EXPORT Lod* CreateLod() const;
  KMLDOM_EXPORT LookAt* CreateLookAt() const;
  KMLDOM_EXPORT Metadata* CreateMetadata() const;
  KMLDOM_EXPORT Model* CreateModel() const;
  KMLDOM_EXPORT MultiGeometry* CreateMultiGeometry() const;
  KMLDOM_EXPORT NetworkLink* CreateNetworkLink() const;
  KMLDOM_EXPORT Orientation* CreateOrientation() const;
  KMLDOM_EXPORT NetworkLinkControl* CreateNetworkLinkControl() const;
  KMLDOM_EXPORT OuterBoundaryIs* CreateOuterBoundaryIs() const;
  KMLDOM_EXPORT OverlayXY* CreateOverlayXY() const;
  KMLDOM_EXPORT Pair* CreatePair() const;
  KMLDOM_EXPORT PhotoOverlay* CreatePhotoOverlay() const;
  KMLDOM_EXPORT Placemark* CreatePlacemark() const;
  KMLDOM_EXPORT Polygon* CreatePolygon() const;
  KMLDOM_EXPORT Point* CreatePoint() const;
  KMLDOM_EXPORT PolyStyle* CreatePolyStyle() const;
  KMLDOM_EXPORT Region* CreateRegion() const;
  KMLDOM_EXPORT ResourceMap* CreateResourceMap() const;
  KMLDOM_EXPORT RotationXY* CreateRotationXY() const;
  KMLDOM_EXPORT Scale* CreateScale() const;
  KMLDOM_EXPORT Schema* CreateSchema() const;
  KMLDOM_EXPORT SchemaData* CreateSchemaData() const;
  KMLDOM_EXPORT ScreenOverlay* CreateScreenOverlay() const;
  KMLDOM_EXPORT ScreenXY* CreateScreenXY() const;
  KMLDOM_EXPORT Size* CreateSize() const;
  KMLDOM_EXPORT SimpleData* CreateSimpleData() const;
  KMLDOM_EXPORT SimpleField* CreateSimpleField() const;
  KMLDOM_EXPORT Snippet* CreateSnippet() const;
  KMLDOM_EXPORT Style* CreateStyle() const;
  KMLDOM_EXPORT StyleMap* CreateStyleMap() const;
  KMLDOM_EXPORT TimeSpan* CreateTimeSpan() const;
  KMLDOM_EXPORT TimeStamp* CreateTimeStamp() const;
  KMLDOM_EXPORT ViewVolume* CreateViewVolume() const;
  KMLDOM_EXPORT Update* CreateUpdate() const;
  KMLDOM_EXPORT Url* CreateUrl() const;
  KMLDOM_EXPORT XalAddressDetails* CreateXalAddressDetails() const;
  KMLDOM_EXPORT XalAdministrativeArea* CreateXalAdministrativeArea() const;
  KMLDOM_EXPORT XalCountry* CreateXalCountry() const;
  KMLDOM_EXPORT XalLocality* CreateXalLocality() const;
  KMLDOM_EXPORT XalPostalCode* CreateXalPostalCode() const;
  KMLDOM_EXPORT XalSubAdministrativeArea* CreateXalSubAdministrativeArea() const;
  KMLDOM_EXPORT XalThoroughfare* CreateXalThoroughfare() const;

  // These methods create the elements in the Google extensions to KML 2.2.
  KMLDOM_EXPORT GxAnimatedUpdate* CreateGxAnimatedUpdate() const;
  KMLDOM_EXPORT GxFlyTo* CreateGxFlyTo() const;
  KMLDOM_EXPORT GxLatLonQuad* CreateGxLatLonQuad() const;
  KMLDOM_EXPORT GxMultiTrack* CreateGxMultiTrack() const;
  KMLDOM_EXPORT GxPlaylist* CreateGxPlaylist() const;
  KMLDOM_EXPORT GxSimpleArrayData* CreateGxSimpleArrayData() const;
  KMLDOM_EXPORT GxSimpleArrayField* CreateGxSimpleArrayField() const;
  KMLDOM_EXPORT GxSoundCue* CreateGxSoundCue() const;
  KMLDOM_EXPORT GxTimeSpan* CreateGxTimeSpan() const;
  KMLDOM_EXPORT GxTimeStamp* CreateGxTimeStamp() const;
  KMLDOM_EXPORT GxTour* CreateGxTour() const;
  KMLDOM_EXPORT GxTourControl* CreateGxTourControl() const;
  KMLDOM_EXPORT GxTrack* CreateGxTrack() const;
  KMLDOM_EXPORT GxWait* CreateGxWait() const;

 private:
  KmlFactory() {};  // Singleton class, use GetFactory().
  static KmlFactory* factory_;
  LIBKML_DISALLOW_EVIL_CONSTRUCTORS(KmlFactory);
};

}  // namespace kmldom

#endif  // KML_DOM_KML_FACTORY_H__
