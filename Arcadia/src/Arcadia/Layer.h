#pragma once

#include "Arcadia/Core.h"
#include "Arcadia/Events/Event.h"

namespace Arcadia
{
    class ARCADIA_API Layer
    {
    public:
        Layer(const std::string& _sLayerName = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate() {};
        virtual void OnEvent(Event& _e) {};

        inline const std::string& GetName() const { return m_sLayerName; }

    protected:
        std::string m_sLayerName;
    };
}