//
// Created by sunvy on 17/02/2026.
//

#ifndef SUNSETCRAFT_NETWORKSYSTEM_H
#define SUNSETCRAFT_NETWORKSYSTEM_H
#include "Utility/ThreadSafeQueue.h"

struct NetworkEvent;
struct INetworkTransport;

namespace SunsetEngine
{
    class NetworkSystem
    {
    public:
        NetworkSystem();

        ~NetworkSystem();

        void Connect(const std::string_view& host, uint16_t port);

        void Update();

        void SendMessage(const std::string_view& message);

    private:

        ThreadSafeQueue<NetworkEvent> m_eventQueue;
        std::unique_ptr<INetworkTransport> m_transport;
    };
}

#endif //SUNSETCRAFT_NETWORKSYSTEM_H