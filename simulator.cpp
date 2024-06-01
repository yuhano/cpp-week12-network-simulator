#include "simulator.h"

double Simulator::time_ = 0.0;

clock_t Simulator::start = clock();


std::function<bool(Schedule&, Schedule&)> Simulator::cmp = [](Schedule &a, Schedule &b) {
    return a.time() > b.time();
};

std::priority_queue<Schedule, std::vector<Schedule>, decltype(Simulator::cmp)> Simulator::scheduleQueue(Simulator::cmp);
