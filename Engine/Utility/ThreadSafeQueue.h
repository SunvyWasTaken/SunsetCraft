//
// Created by sunvy on 17/02/2026.
//

#ifndef SUNSETCRAFT_THREADSAFEQUEUE_H
#define SUNSETCRAFT_THREADSAFEQUEUE_H
#include <mutex>
#include <optional>
#include <queue>

namespace SunsetEngine
{
    template <typename T>
    class ThreadSafeQueue
    {
    public:
        void Push(T item)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(item);
        }

        std::optional<T> Pop()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_queue.empty())
                return std::nullopt;

            T item = std::move(m_queue.front());
            m_queue.pop();
            return item;
        }
    private:
        std::mutex m_mutex;
        std::queue<T> m_queue;
    };
}

#endif //SUNSETCRAFT_THREADSAFEQUEUE_H