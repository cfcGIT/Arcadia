
#include "Arcadia.h"

class Sandbox : public Arcadia::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }

    
};

Arcadia::Application* Arcadia::CreateApplication()
{
    return new Sandbox();
}


