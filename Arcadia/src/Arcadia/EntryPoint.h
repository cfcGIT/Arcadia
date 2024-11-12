#pragma once

#ifdef ARC_PLATFORM_WINDOWS

extern Arcadia::Application* Arcadia::CreateApplication();

int main(int argc, char** argv)
{
    printf("Arcadia Engine\n");
    auto app = Arcadia::CreateApplication();
    app->Run();
    delete app;
}


#endif
