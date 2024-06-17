#include "bm/MainLoop.hpp"

int main(int argc, char** argv)
{
    bm::Window::Ptr Window = std::make_shared<bm::Window>();

    if (!Window->Create("BulletManager"))
    {
        return -1;
    }

    bm::MainLoop::Ptr Loop = std::make_shared<bm::MainLoop>();
    if (!Loop->Initialize(Window)) {
        return -1;
    }

    Loop->Start();

    Loop->Deinitialize();

    return 0;
}