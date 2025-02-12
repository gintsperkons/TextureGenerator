#pragma once
#include <queue>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <string>
#include <memory>

class ImageJobQueue
{
  struct JobEntry
  {
    std::function<void(std::shared_ptr<std::atomic<bool>>)> jobFunction;
    std::shared_ptr<std::atomic<bool>> cancelFlag;
  };

  std::unordered_map<std::string, JobEntry> m_jobs; // Stores latest job per source
  std::queue<std::string> m_jobQueue;               // Tracks execution order
  std::mutex m_mutex;
  std::condition_variable m_condition;
  std::atomic<bool> m_running;
  std::thread m_worker;
  std::string m_currentJob; // Track currently running job
  std::shared_ptr<std::atomic<bool>> m_currentCancelFlag;

  void WorkerThread();

public:
  ImageJobQueue();
  ~ImageJobQueue();

  void AddJob(const std::string &source, std::function<void(std::shared_ptr<std::atomic<bool>>)> job);

};
