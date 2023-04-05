/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkottieUtils_DEFINED
#define SkottieUtils_DEFINED

#include <skia/skottie/ExternalLayer.h>
#include <skia/skottie/Skottie.h>
#include <skia/skottie/SkottieProperty.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace skottie_utils {

/**
 * CustomPropertyManager implements a property management scheme where color/opacity/transform
 * attributes are grouped and manipulated by name (one-to-many mapping).
 *
 *   - setters apply the value to all properties in a named group
 *
 *   - getters return all the managed property groups, and the first value within each of them
 *     (unchecked assumption: all properties within the same group have the same value)
 *
 * Attach to an Animation::Builder using the utility methods below to intercept properties and
 * markers at build time.
 */
class CustomPropertyManager final {
public:
    enum class Mode {
        kCollapseProperties,   // keys ignore the ancestor chain and are
                               // grouped based on the local node name
        kNamespacedProperties, // keys include the ancestor node names (no grouping)
    };

    SK_API explicit CustomPropertyManager(Mode = Mode::kNamespacedProperties,
                                   const char* prefix = nullptr);
    SK_API ~CustomPropertyManager();

    using PropKey = std::string;

    SK_API std::vector<PropKey> getColorProps() const;
    SK_API skottie::ColorPropertyValue getColor(const PropKey&) const;
    SK_API bool setColor(const PropKey&, const skottie::ColorPropertyValue&);

    SK_API std::vector<PropKey> getOpacityProps() const;
    SK_API skottie::OpacityPropertyValue getOpacity(const PropKey&) const;
    SK_API bool setOpacity(const PropKey&, const skottie::OpacityPropertyValue&);

    SK_API std::vector<PropKey> getTransformProps( ) const;
    SK_API skottie::TransformPropertyValue getTransform( const PropKey& ) const;
    SK_API bool setTransform(const PropKey&, const skottie::TransformPropertyValue&);

    SK_API std::vector<PropKey> getTextProps( ) const;
    SK_API skottie::TextPropertyValue getText( const PropKey& ) const;
    SK_API bool setText(const PropKey&, const skottie::TextPropertyValue&);

    struct MarkerInfo {
        std::string name;
        float       t0, t1;
    };
    SK_API const std::vector<MarkerInfo>& markers() const { return fMarkers; }

    // Returns a property observer to be attached to an animation builder.
    SK_API sk_sp<skottie::PropertyObserver> getPropertyObserver() const;

    // Returns a marker observer to be attached to an animation builder.
    SK_API sk_sp<skottie::MarkerObserver> getMarkerObserver() const;

private:
    class PropertyInterceptor;
    class MarkerInterceptor;

    SK_API std::string acceptKey(const char*, const char*) const;

    template <typename T>
    using PropGroup = std::vector<std::unique_ptr<T>>;

    template <typename T>
    using PropMap = std::unordered_map<PropKey, PropGroup<T>>;

    template <typename T>
    std::vector<PropKey> getProps(const PropMap<T>& container) const;

    template <typename V, typename T>
    V get(const PropKey&, const PropMap<T>& container) const;

    template <typename V, typename T>
    bool set(const PropKey&, const V&, const PropMap<T>& container);

    const Mode                                fMode;
    const SkString                            fPrefix;

    sk_sp<PropertyInterceptor>                fPropertyInterceptor;
    sk_sp<MarkerInterceptor>                  fMarkerInterceptor;

    PropMap<skottie::ColorPropertyHandle>     fColorMap;
    PropMap<skottie::OpacityPropertyHandle>   fOpacityMap;
    PropMap<skottie::TransformPropertyHandle> fTransformMap;
    PropMap<skottie::TextPropertyHandle>      fTextMap;
    std::vector<MarkerInfo>                   fMarkers;
    std::string                               fCurrentNode;
};

/**
 * A sample PrecompInterceptor implementation.
 *
 * Attempts to substitute all precomp layers matching the given pattern (name prefix)
 * with external Lottie animations.
 */
class ExternalAnimationPrecompInterceptor final : public skottie::PrecompInterceptor {
public:
    SK_API ExternalAnimationPrecompInterceptor(sk_sp<skresources::ResourceProvider>, const char prefix[]);
    SK_API ~ExternalAnimationPrecompInterceptor() override;

private:
    SK_API sk_sp<skottie::ExternalLayer> onLoadPrecomp(const char[], const char[], const SkSize&) override;

    const sk_sp<skresources::ResourceProvider> fResourceProvider;
    const SkString                             fPrefix;
};


} // namespace skottie_utils

#endif // SkottieUtils_DEFINED
