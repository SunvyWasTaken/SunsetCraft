//
// Created by sunvy on 17/02/2026.
//

#include "NetworkSystem.h"

#include "INetworkTransport.h"
#include "TcpTransport.h"

namespace
{
    void HandleEvent(const NetworkEvent& ev)
    {
        switch (ev.type)
        {
        case NetworkEvent::Type::Connected:
            LOG("Engine", info, "[Network] Connected");
            break;
        case NetworkEvent::Type::Disconnected:
            LOG("Engine", info, "[Network] Disconnected");
            break;
        case NetworkEvent::Type::Message:
            LOG("Engine", info, "[Network] Message received: {}", std::string(ev.payload.begin(), ev.payload.end()));
            break;
        }
    }
}

namespace SunsetEngine
{
    NetworkSystem::NetworkSystem()
        : m_eventQueue()
        , m_transport(std::make_unique<TcpTransport>(m_eventQueue))
    {
    }

    // For the forward declaration.
    NetworkSystem::~NetworkSystem()
    {
    }

    void NetworkSystem::Connect(const std::string_view& host, uint16_t port)
    {
        m_transport->Connect(host, port);
    }

    void NetworkSystem::Update()
    {
        m_transport->Poll();
        while (auto ev = m_eventQueue.Pop())
        {
            HandleEvent(*ev);
        }
    }

    void NetworkSystem::SendMessage(const std::string_view& message)
    {
        std::vector<uint8_t> data(message.begin(), message.end());
        m_transport->Send(data);
    }
}
