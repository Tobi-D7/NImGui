#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
#include <iostream>
#include <string>

namespace NImGui {

class Timer {
public:
  Timer() { Reset(); }

  void Reset() { m_Start = std::chrono::high_resolution_clock::now(); }

  float Get() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::high_resolution_clock::now() - m_Start)
               .count() *
           0.001f * 0.001f * 0.001f;
  }

  float GetAsMs() { return Get() * 1000.0f; }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
};
} // namespace NImGui

#endif // __TIMER_H__