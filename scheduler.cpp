#include "scheduler.h"

TaskScheduler::TaskScheduler(size_t num_threads) : stop_flag_(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        threads_.emplace_back(&TaskScheduler::worker_thread, this);
    }
}

TaskScheduler::~TaskScheduler() {
    stop();
}

void TaskScheduler::schedule(const std::function<void()>& task, std::chrono::milliseconds delay) {
    std::unique_lock<std::mutex> lock(tasks_mutex_);
    tasks_.emplace(std::chrono::steady_clock::now() + delay, task);
    task_condition_.notify_one();
}

void TaskScheduler::stop() {
    {
        std::unique_lock<std::mutex> lock(tasks_mutex_);
        stop_flag_ = true;
    }
    task_condition_.notify_all();
    for (std::thread &thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void TaskScheduler::worker_thread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(tasks_mutex_);

            if (tasks_.empty() && !stop_flag_) {
                task_condition_.wait(lock);
            }

            if (stop_flag_ && tasks_.empty()) {
                break;
            }

            auto now = std::chrono::steady_clock::now();
            if (!tasks_.empty() && tasks_.top().first <= now) {
                task = tasks_.top().second;
                tasks_.pop();
            } else {
                task_condition_.wait_until(lock, tasks_.top().first);
            }
        }

        if (task) {
            task();  // Execute the task
        }
    }
}
