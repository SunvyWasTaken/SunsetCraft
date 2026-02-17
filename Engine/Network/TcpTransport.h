//
// Created by sunvy on 17/02/2026.
//

#ifndef SUNSETCRAFT_TCPTRANSPORT_H
#define SUNSETCRAFT_TCPTRANSPORT_H

#include "INetworkTransport.h"
#include "Utility/ThreadSafeQueue.h"

namespace SunsetEngine
{
    class TcpTransport : public INetworkTransport
    {
    public:
        explicit TcpTransport(SunsetEngine::ThreadSafeQueue<NetworkEvent>& queue);
        ~TcpTransport() override;

        void Connect(const std::string_view& host, uint16_t port) override;

        void Send(const std::vector<uint8_t>& data) override;

        void Poll() override;

        void Disconnect();

    private:

        void ReceiveLoop();

        int m_Socket;
        std::atomic<bool> m_Connected;
        std::thread m_Thread;
        ThreadSafeQueue<NetworkEvent>& m_Queue;
    };
}

#endif //SUNSETCRAFT_TCPTRANSPORT_H