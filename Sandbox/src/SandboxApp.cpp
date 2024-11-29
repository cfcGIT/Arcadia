
#include "Arcadia.h"
#include "Arcadia/Events/Event.h"

class ExampleLayer : public Arcadia::Layer
{
public:
    ExampleLayer()
        : Layer("ExampleLayer") { }

    void OnUpdate() override
    {
        ARC_INFO("ExampleLayer update");
    }

    void OnEvent(Arcadia::Event& _event) override
    {
        ARC_TRACE("{0}", _event);
    }

    inline const std::string& GetName() const { return m_sLayerName; }
};


class Sandbox : public Arcadia::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Arcadia::Application* Arcadia::CreateApplication()
{
    return new Sandbox();
}
