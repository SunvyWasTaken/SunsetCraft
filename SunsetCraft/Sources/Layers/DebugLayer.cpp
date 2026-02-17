//
// Created by sunvy on 04/01/2026.
//

#include "DebugLayer.h"

#include "Network/INetworkTransport.h"
#include "Network/NetworkSystem.h"
#include "Network/TcpTransport.h"
#include "Utility/ThreadSafeQueue.h"

std::unique_ptr<SunsetEngine::NetworkSystem> network = nullptr;

DebugLayer::DebugLayer()
    : Layer()
{
    network = std::make_unique<SunsetEngine::NetworkSystem>();
    network->Connect("127.0.0.1", 12345);
}

DebugLayer::~DebugLayer()
{
    network.reset();
}

void DebugLayer::OnUpdate(float dt)
{
    network->Update();
}

void DebugLayer::OnDraw()
{
}

bool DebugLayer::OnEvent(SunsetEngine::Event::Type& event)
{
    return std::visit(overloads{
        [](SunsetEngine::Event::KeyEvent& event)
        {
            const std::string msg = std::format("{}", static_cast<char>(event.key));
            network->SendMessage(msg);
            return true;
        },
        [](SunsetEngine::Event::MouseEvent& event)
        {
            return true;
        }
    }, event);
}
