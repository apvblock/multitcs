#include "scheduler.h"

void print_message(const std::string& message) {
    std::cout << "Task executed: " << message << "\n";
}

int main() {
    TaskScheduler scheduler(4);

    // Schedule tasks
    scheduler.schedule(std::bind(print_message, "Hello, World!"), std::chrono::milliseconds(1000));
    scheduler.schedule(std::bind(print_message, "Task 2"), std::chrono::milliseconds(2000));
    scheduler.schedule(std::bind(print_message, "Task 3"), std::chrono::milliseconds(3000));

    // Let the tasks run for a while
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    scheduler.stop();  // Gracefully stop the scheduler
    return 0;
}
