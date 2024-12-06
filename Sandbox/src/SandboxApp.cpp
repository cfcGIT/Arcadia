
#include "Arcadia.h"
#include "Arcadia/Events/Event.h"

class CExampleLayer : public Arcadia::CLayer
{
public:
    CExampleLayer()
        : CLayer("ExampleLayer") { }

    void OnUpdate() override
    {
        ARC_INFO("ExampleLayer update");
    }

    void OnEvent(Arcadia::CEvent& _oEvent) override
    {
        ARC_TRACE("{0}", _oEvent);
    }

    inline const std::string& GetName() const { return m_sLayerName; }
};


class CSandbox : public Arcadia::CApplication
{
public:
    CSandbox()
    {
        PushLayer(new CExampleLayer());
    }

    ~CSandbox()
    {

    }
};

Arcadia::CApplication* Arcadia::CreateApplication()
{
    return new CSandbox();
}
