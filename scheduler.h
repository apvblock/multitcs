#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

class TaskScheduler {
public:
    TaskScheduler(size_t num_threads);
    ~TaskScheduler();

    // Schedule a task to run after a delay
    void schedule(const std::function<void()>& task, std::chrono::milliseconds delay);

    // Stop the scheduler
    void stop();

private:
    std::vector<std::thread> threads_;
    std::priority_queue<std::pair<std::chrono::steady_clock::time_point, std::function<void()>>> tasks_;
    std::mutex tasks_mutex_;
    std::condition_variable task_condition_;
    bool stop_flag_;

    // Worker thread function
    void worker_thread();
};

#endif
