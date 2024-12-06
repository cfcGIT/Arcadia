#pragma once

#ifdef ARC_PLATFORM_WINDOWS

extern Arcadia::CApplication* Arcadia::CreateApplication();

int main(int argc, char** argv)
{
    Arcadia::CLog::Init();

    //ARC_CORE_FATAL("Esto es fatallll");
    ARC_CORE_WARN("Initialized Log!");
    int a = 5;
    ARC_INFO("Hello! Var={0}", a);

    Arcadia::CApplication* pApp = Arcadia::CreateApplication();
    pApp->Run();
    delete pApp;
}


#endif
