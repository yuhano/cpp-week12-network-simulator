#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <iostream>
#include <ctime>
#include <vector>

class Simulator;

class Schedule
{
private:
  double time_;
  std::function<void()> function_;
  std::string objectStr_;

public:
  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}
};

class Simulator
{
private:
  static double time_;
  static clock_t start;
  static clock_t end;

  static std::function<bool(Schedule &, Schedule &)> cmp;
  static std::priority_queue<Schedule, std::vector<Schedule>, decltype(cmp)> scheduleQueue;

public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function)
  {
    // 스케줄 큐에 스케줄을 추가한다.
    scheduleQueue.push(Schedule(now() + time, function));
    // 동일한 함수
    // scheduleQueue.emplace(time ,function);
  }

  static void run()
  {
    // 모든 스케줄을 실행한다.
    while (!scheduleQueue.empty())
    {
      Schedule &topSchedule = const_cast<Schedule &>(scheduleQueue.top());

      if (topSchedule.time() <= now())
      {
        topSchedule.call();
        scheduleQueue.pop();
      }
      else
      {
        time_ += 0.001;
      }
    }
  }
};

#endif