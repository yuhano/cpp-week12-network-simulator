#include "simulator.h"
#include "object.h"

double Simulator::time_ = 0.0;

clock_t Simulator::start = clock();

std::function<bool(Schedule &, Schedule &)> Simulator::cmp = [](Schedule &a, Schedule &b)
{
  return a.time() > b.time();
};

std::priority_queue<Schedule, std::vector<Schedule>, decltype(Simulator::cmp)> Simulator::scheduleQueue(Simulator::cmp);

void Simulator::run()
{
  Object::initializeAll();

  // 모든 스케줄을 실행한다.
  // TODO: 구현

  // 모든 스케줄을 실행한다.
  while (!scheduleQueue.empty())
  {
    time_ = double((clock() - start) / (double)CLOCKS_PER_SEC);
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

  Object::cleanup();
  std::cout << "result!!!";
}