#include "ImageJobQueue.h"

void ImageJobQueue::WorkerThread()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this]()
                             { return !m_jobs.empty() || !m_running; });
            if (!m_running && m_jobs.empty())
                return;

            job = std::move(m_jobs.front());
            m_jobs.pop();
        }
        if (job)
            job();
    }
}

ImageJobQueue::ImageJobQueue() : m_running(true)
{
    m_worker = std::thread(&ImageJobQueue::WorkerThread, this);
}

ImageJobQueue::~ImageJobQueue()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_running = false;
    }
    m_condition.notify_one();
    if (m_worker.joinable())
    {
        m_worker.join();
    }
}

void ImageJobQueue::AddJob(std::function<void()> job)
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_jobs.push(std::move(job));
    }
    m_condition.notify_one();
}
