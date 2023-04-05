/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2021 Paul Ramsey <pramsey@cleverelephant.ca>
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/

#include <geos/geom/util/GeometryFixer.h>
#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/operation/overlayng/OverlayNG.h>
#include <geos/operation/overlayng/OverlayNGRobust.h>
#include <geos/operation/buffer/BufferOp.h>
#include <geos/operation/valid/RepeatedPointRemover.h>
#include <geos/util/UnsupportedOperationException.h>

using geos::operation::valid::RepeatedPointRemover;

namespace geos {
namespace geom { // geos.geom
namespace util { // geos.geom.util

/* public static */
std::unique_ptr<Geometry>
GeometryFixer::fix(const Geometry* p_geom)
{
    GeometryFixer fix(p_geom);
    return fix.getResult();
}

/* public */
void
GeometryFixer::setKeepCollapsed(bool p_isKeepCollapsed)
{
    isKeepCollapsed = p_isKeepCollapsed;
}

/* public */
std::unique_ptr<Geometry>
GeometryFixer::getResult() const
{
    /**
     *  Truly empty geometries are simply copied.
     *  Geometry collections with elements are evaluated on a per-element basis.
     */
    if (geom->getNumGeometries() == 0) {
        return geom->clone();
    }

    switch(geom->getGeometryTypeId()) {
        case GEOS_POINT:
            return fixPoint(static_cast<const Point*>(geom));
        case GEOS_LINEARRING:
            return fixLinearRing(static_cast<const LinearRing*>(geom));
        case GEOS_LINESTRING:
            return fixLineString(static_cast<const LineString*>(geom));
        case GEOS_POLYGON:
            return fixPolygon(static_cast<const Polygon*>(geom));
        case GEOS_MULTIPOINT:
            return fixMultiPoint(static_cast<const MultiPoint*>(geom));
        case GEOS_MULTILINESTRING:
            return fixMultiLineString(static_cast<const MultiLineString*>(geom));
        case GEOS_MULTIPOLYGON:
            return fixMultiPolygon(static_cast<const MultiPolygon*>(geom));
        case GEOS_GEOMETRYCOLLECTION:
            return fixCollection(static_cast<const GeometryCollection*>(geom));
        default:
            throw geos::util::UnsupportedOperationException("GeometryFixer::getResult called on unknown geometry type");
    }
}

/* private */
std::unique_ptr<Point>
GeometryFixer::fixPoint(const Point* p_geom) const
{
    std::unique_ptr<Point> pt = fixPointElement(p_geom);
    if (pt == nullptr)
        return factory->createPoint();
    else
        return pt;
}

/* private */
std::unique_ptr<Point>
GeometryFixer::fixPointElement(const Point* p_geom) const
{
    if (p_geom->isEmpty() || ! isValidPoint(p_geom)) {
        return nullptr;
    }
    return p_geom->clone();
}

/* private static */
bool
GeometryFixer::isValidPoint(const Point* pt) const
{
    const Coordinate* p = pt->getCoordinate();
    return p->isValid();
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixMultiPoint(const MultiPoint* p_geom) const
{
    std::vector<std::unique_ptr<Point>> pts;
    for (std::size_t i = 0; i < p_geom->getNumGeometries(); i++) {
        const Point* pt = p_geom->getGeometryN(i);
        if (pt->isEmpty()) continue;
        std::unique_ptr<Point> fixPt = fixPointElement(pt);
        if (fixPt != nullptr) {
            pts.emplace_back(fixPt.release());
        }
    }
    return factory->createMultiPoint(std::move(pts));
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixLinearRing(const LinearRing* p_geom) const
{
    std::unique_ptr<Geometry> fixedRing = fixLinearRingElement(p_geom);
    if (fixedRing == nullptr)
        return factory->createLinearRing();
    else
        return fixedRing;
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixLinearRingElement(const LinearRing* p_geom) const
{
    if (p_geom->isEmpty())
        return nullptr;

    auto ptsFix = RepeatedPointRemover::removeRepeatedAndInvalidPoints(p_geom->getCoordinatesRO());
    auto ptsFixSz = ptsFix->size();
    if (isKeepCollapsed) {
        if (ptsFixSz == 1) {
            const Coordinate& c = ptsFix->getAt(0);
            std::unique_ptr<Geometry> pt(factory->createPoint(c));
            return pt;
        }
        if (ptsFixSz > 1 && ptsFixSz <= 3) {
            return factory->createLineString(std::move(ptsFix));
        }
    }
    //--- too short to be a valid ring
    if (ptsFixSz <= LinearRing::MINIMUM_VALID_SIZE)
        return nullptr;

    std::unique_ptr<Geometry> ring = factory->createLinearRing(std::move(ptsFix));
    //--- convert invalid ring to LineString
    if (! ring->isValid())
        return factory->createLineString(ring->getCoordinates());
    else
        return ring;
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixLineString(const LineString* p_geom) const
{
    std::unique_ptr<Geometry> fixedLine = fixLineStringElement(p_geom);
    if (fixedLine == nullptr)
        return factory->createLineString();
    else
        return fixedLine;
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixLineStringElement(const LineString* p_geom) const
{
    if (p_geom->isEmpty())
        return nullptr;

    auto ptsFix = RepeatedPointRemover::removeRepeatedAndInvalidPoints(p_geom->getCoordinatesRO());
    auto ptsFixSz = ptsFix->size();
    if (isKeepCollapsed && ptsFixSz == 1) {
        const Coordinate& c = ptsFix->getAt(0);
        std::unique_ptr<Geometry> pt(factory->createPoint(c));
        return pt;
    }
    if (ptsFixSz <= 1)
        return nullptr;
    else
        return factory->createLineString(std::move(ptsFix));
}


/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixMultiLineString(const MultiLineString* p_geom) const
{
    std::vector<std::unique_ptr<Geometry>> fixed;
    bool isMixed = false;
    for (std::size_t i = 0; i < p_geom->getNumGeometries(); i++) {
        const LineString* line = p_geom->getGeometryN(i);
        if (line->isEmpty())
            continue;

        std::unique_ptr<Geometry> fixedMLine = fixLineStringElement(line);
        if (fixedMLine == nullptr)
            continue;

        if (fixedMLine->getGeometryTypeId() != GEOS_LINESTRING) {
            isMixed = true;
        }
        fixed.emplace_back(fixedMLine.release());
    }
    if (fixed.size() == 1) {
        std::unique_ptr<Geometry> g(fixed.at(0).release());
        return g;
    }
    if (isMixed)
        return factory->createGeometryCollection(std::move(fixed));
    else
        return factory->createMultiLineString(std::move(fixed));
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixPolygon(const Polygon* p_geom) const
{
    std::unique_ptr<Geometry> fixedPoly = fixPolygonElement(p_geom);
    if (fixedPoly == nullptr)
        return factory->createPolygon();
    else
        return fixedPoly;
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixPolygonElement(const Polygon* p_geom) const
{
    const LinearRing* shell = p_geom->getExteriorRing();
    std::unique_ptr<Geometry> fixShell = fixRing(shell);
    if (fixShell->isEmpty()) {
        if (isKeepCollapsed) {
            const CoordinateSequence* cs = shell->getCoordinatesRO();
            std::unique_ptr<LineString> line(factory->createLineString(*cs));
            return fixLineString(line.get());
        }
        //-- if not allowing collapses then return empty polygon
        return nullptr;
    }
    // if no holes then done
    if (p_geom->getNumInteriorRing() == 0) {
        return fixShell;
    }
    std::unique_ptr<Geometry> fixedHoles = fixHoles(p_geom);
    std::unique_ptr<Geometry> result = removeHoles(fixShell.get(), fixedHoles.get());
    return result;
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixHoles(const Polygon* p_geom) const
{
    std::vector<std::unique_ptr<Geometry>> holes;

    for (std::size_t i = 0; i < p_geom->getNumInteriorRing(); i++) {
        std::unique_ptr<Geometry> holeRep = fixRing(p_geom->getInteriorRingN(i));
        // Do not preserve null/empty holes
        if (holeRep != nullptr && !holeRep->isEmpty()) {
            holes.emplace_back(holeRep.release());
        }
    }
    if (holes.empty())
        return nullptr;

    if (holes.size() == 1) {
        std::unique_ptr<Geometry> h(holes.at(0).release());
        return h;
    }
    std::unique_ptr<GeometryCollection> holesGeom = (factory->createGeometryCollection(std::move(holes)));
    return operation::overlayng::OverlayNGRobust::Union(holesGeom.get());
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::removeHoles(const Geometry* shell, const Geometry* holes) const
{
    if (holes == nullptr || holes->isEmpty())
        return shell->clone();
    return operation::overlayng::OverlayNGRobust::Overlay(shell, holes,
        operation::overlayng::OverlayNG::DIFFERENCE);
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixRing(const LinearRing* ring) const
{
    //-- always execute fix, since it may remove repeated coords etc
    std::unique_ptr<LinearRing> lr = ring->clone();
    std::unique_ptr<Geometry> poly = factory->createPolygon(std::move(lr));
    // TODO: check if buffer removes invalid coordinates
    return operation::buffer::BufferOp::bufferByZero(poly.get(), true);
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixMultiPolygon(const MultiPolygon* p_geom) const
{
    std::vector<std::unique_ptr<Geometry>> polys;

    for (std::size_t i = 0; i < p_geom->getNumGeometries(); i++) {
        const Polygon* poly = p_geom->getGeometryN(i);
        std::unique_ptr<Geometry> polyFix = fixPolygonElement(poly);
        if (polyFix != nullptr && ! polyFix->isEmpty()) {
            polys.emplace_back(polyFix.release());
        }
    }
    if (polys.empty()) {
        return factory->createMultiPolygon();
    }
    std::unique_ptr<GeometryCollection> polysGeom = (factory->createGeometryCollection(std::move(polys)));
    return operation::overlayng::OverlayNGRobust::Union(polysGeom.get());
}

/* private */
std::unique_ptr<Geometry>
GeometryFixer::fixCollection(const GeometryCollection* p_geom) const
{
    std::vector<std::unique_ptr<Geometry>> geoms;
    for (std::size_t i = 0; i < p_geom->getNumGeometries(); i++) {
        std::unique_ptr<Geometry> fixed = fix(p_geom->getGeometryN(i));
        geoms.emplace_back(fixed.release());
    }
    return factory->createGeometryCollection(std::move(geoms));
}



} // namespace geos.geom.util
} // namespace geos.geom
} // namespace geos

