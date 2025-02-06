
#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ImageJobQueue
{
        std::queue<std::function<void()>> m_jobs;
        std::mutex m_mutex;
        std::condition_variable m_condition;
        std::atomic<bool> m_running;
        std::thread m_worker;

        void WorkerThread();
    public:
        ImageJobQueue();
        ~ImageJobQueue();
        void AddJob(std::function<void()> job);
};