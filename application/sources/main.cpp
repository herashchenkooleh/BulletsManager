#include "bm/MainLoop.hpp"
#include "bm/Configs.hpp"
#include "bm/Logger.hpp"

int main(int argc, char** argv) {
    bm::Window::Ptr Window = std::make_shared<bm::Window>();

    if (!Window->Create(bm::Configs::GetInstance().Get<std::string>(bm::Configs::sGlobalWindowTitle))) {
        bm::Logger::GetInstance().Fatal("Failed initialize window");
        return -1;
    }

    bm::MainLoop::Ptr Loop = std::make_shared<bm::MainLoop>();
    if (!Loop->Initialize(Window)) {
        bm::Logger::GetInstance().Fatal("Failed initialize main loop");
        return -1;
    }

    Loop->Start();

    Loop->Deinitialize();

    return 0;
}