#pragma once

#include <cstdint>
#include "../objects/IBaseObject.h"

namespace alt
{
    class IWebView : public virtual IBaseObject
    {
    public:
        virtual ~IWebView() = default;
        virtual void Trigger(alt::StringView eventname, const alt::MValueArgs &args) = 0;
        virtual void Focus() = 0;
        virtual void Unfocus() = 0;
        virtual bool IsFocused() const = 0;
        virtual alt::StringView GetUrl() const = 0;
        virtual void SetUrl(alt::StringView url) = 0;
        virtual bool IsVisible() const = 0;
        virtual void SetVisible(bool visible) = 0;
        virtual bool IsOverlay() const = 0;
        virtual bool IsLoaded() const = 0;
        virtual bool IsReady() const = 0;
        virtual void SetExtraHeader(alt::StringView name, alt::StringView value) = 0;
        virtual void SetZoomLevel(double value) = 0;
        virtual Vector2i GetSize() const = 0;
        virtual void SetSize(Vector2i size) = 0;
        virtual Vector2i GetPosition() const = 0;
        virtual void SetPosition(Vector2i pos) = 0;
        
        const std::type_info& GetTypeInfo() const override { return typeid(this); }
    };
} // namespace alt
