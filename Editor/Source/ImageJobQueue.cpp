#include "ImageJobQueue.h"
#include "Core/Logger/Logger.h"

void ImageJobQueue::WorkerThread()
{
  while (m_running)
  {
    std::string jobSource;
    std::function<void(std::shared_ptr<std::atomic<bool>>)> job;
    std::shared_ptr<std::atomic<bool>> cancelFlag;

    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_condition.wait(lock, [this]
                       { return !m_jobQueue.empty() || !m_running; });

      if (!m_running)
        return;

      // Get the next job in FIFO order
      jobSource = m_jobQueue.front();
      m_jobQueue.pop();

      // Fetch job from the map
      job = std::move(m_jobs[jobSource].jobFunction);
      cancelFlag = m_jobs[jobSource].cancelFlag;
      m_currentJob = jobSource;
      m_currentCancelFlag = cancelFlag;
      m_jobs.erase(jobSource);
    }

    // Execute job with cancelFlag
    if (job)
    {
      try
      {
        job(cancelFlag);
      }
      catch (const std::exception &e)
      {
        LOG_ERROR("Error executing job %s %s\n", jobSource.c_str(), e.what());
      }
    }

    // Clear current job
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_currentJob.clear();
    }
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

void ImageJobQueue::AddJob(const std::string &source, std::function<void(std::shared_ptr<std::atomic<bool>>)> job)
{
  {
    std::lock_guard<std::mutex> lock(m_mutex);

    // Cancel currently running job if it's the same source
    LOG_DEBUG("Adding job %s\n", source.c_str());
    LOG_DEBUG("Current job %s\n", m_currentJob.c_str());
    LOG_DEBUG("Map size %d\n", m_jobs.size());
    LOG_DEBUG("Queue size %d\n", m_jobQueue.size());

    // Check if the job we are adding is already the current job in process
    if (source == m_currentJob  )
    {
      *(m_currentCancelFlag) = true; // Cancel the current job
    }

    // Create a new cancel flag for the new job
    auto cancelFlag = std::make_shared<std::atomic<bool>>(false);

    // Insert or replace job in map with its cancel flag
    m_jobs[source] = {std::move(job), cancelFlag};

    // Remove previous entry from queue if it exists
    std::queue<std::string> tempQueue;
    while (!m_jobQueue.empty())
    {
      if (m_jobQueue.front() != source) // Don't remove the new job from the queue
      {
        tempQueue.push(m_jobQueue.front());
      }
      m_jobQueue.pop();
    }
    std::swap(m_jobQueue, tempQueue);

    // Add the new job at the end of the queue
    m_jobQueue.push(source);
  }
  m_condition.notify_one();
}
