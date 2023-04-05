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

#include "kml/dom/style.h"
#include "kml/base/attributes.h"
#include "kml/dom/kml22.h"
#include "kml/dom/kml_cast.h"
#include "kml/dom/serializer.h"

using kmlbase::Attributes;

namespace kmldom {

Style::Style() {}

Style::~Style() {}

void Style::AddElement(const ElementPtr& element) {
  if (!element) {
    return;
  }
  switch (element->Type()) {
    case Type_IconStyle:
      set_iconstyle(AsIconStyle(element));
      break;
    case Type_LabelStyle:
      set_labelstyle(AsLabelStyle(element));
      break;
    case Type_LineStyle:
      set_linestyle(AsLineStyle(element));
      break;
    case Type_PolyStyle:
      set_polystyle(AsPolyStyle(element));
      break;
    case Type_BalloonStyle:
      set_balloonstyle(AsBalloonStyle(element));
      break;
    case Type_ListStyle:
      set_liststyle(AsListStyle(element));
      break;
    default:
      StyleSelector::AddElement(element);
      break;
  }
}

void Style::Serialize(Serializer& serializer) const {
  ElementSerializer element_serializer(*this, serializer);
  StyleSelector::Serialize(serializer);
  if (has_iconstyle()) {
    serializer.SaveElement(get_iconstyle());
  }
  if (has_labelstyle()) {
    serializer.SaveElement(get_labelstyle());
  }
  if (has_linestyle()) {
    serializer.SaveElement(get_linestyle());
  }
  if (has_polystyle()) {
    serializer.SaveElement(get_polystyle());
  }
  if (has_balloonstyle()) {
    serializer.SaveElement(get_balloonstyle());
  }
  if (has_liststyle()) {
    serializer.SaveElement(get_liststyle());
  }
}

void Style::Accept(Visitor* visitor) {
  visitor->VisitStyle(StylePtr(this));
}

void Style::AcceptChildren(VisitorDriver* driver) {
  StyleSelector::AcceptChildren(driver);
  if (has_iconstyle()) {
    driver->Visit(get_iconstyle());
  }
  if (has_labelstyle()) {
    driver->Visit(get_labelstyle());
  }
  if (has_linestyle()) {
    driver->Visit(get_linestyle());
  }
  if (has_polystyle()) {
    driver->Visit(get_polystyle());
  }
  if (has_balloonstyle()) {
    driver->Visit(get_balloonstyle());
  }
  if (has_liststyle()) {
    driver->Visit(get_liststyle());
  }
}

}  // end namespace kmldom
