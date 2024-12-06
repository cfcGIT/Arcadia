#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    class ARCADIA_API CLayer
    {
    public:
        CLayer(const std::string& _sLayerName = "Layer");
        virtual ~CLayer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(CEvent& _oEvent) {};

        inline const std::string& GetName() const { return m_sLayerName; }

    protected:
        std::string m_sLayerName;
    };
}