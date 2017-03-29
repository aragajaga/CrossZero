//---------------------------------------------------------------------------------------
// Created by GbaLog
// Link on github.com: https://github.com/GbaLog/
//---------------------------------------------------------------------------------------
#ifndef TIMER_HPP
#define TIMER_HPP
//---------------------------------------------------------------------------------------
#include <chrono>
//---------------------------------------------------------------------------------------
namespace tools
{
//---------------------------------------------------------------------------------------
    using nanoseconds   = std::chrono::nanoseconds;
    using microseconds  = std::chrono::microseconds;
    using milliseconds  = std::chrono::milliseconds;
    using seconds       = std::chrono::seconds;
    using minutes       = std::chrono::minutes;
    using hours         = std::chrono::hours;
//---------------------------------------------------------------------------------------
class Timer
{
public:
  using clock      = std::chrono::system_clock;
  using time_point = clock::time_point;

  Timer()
      :
      start_time{ clock::now() }
  {}

  template<typename Time>
  bool gone( Time&& time )
  {
      return (clock::now() - start_time) >= time;
  }

  template<typename Time>
  bool restart( Time&& time )
  {
      auto tmp_start = start_time;
      start_time = clock::now();
      return (start_time - tmp_start) >= time;
  }

  time_point restart()
  {
      auto tmp_start = start_time;
      start_time = clock::now();
      return tmp_start;
  }

  template<typename Duration>
  inline typename Duration::rep get_elapsed_time() const
  {
      return std::chrono::duration_cast<Duration>(clock::now() - start_time).count();
  }

private:
  time_point start_time;

};
//---------------------------------------------------------------------------------------
} //tools
//---------------------------------------------------------------------------------------
#endif //TIMER_HPP
//---------------------------------------------------------------------------------------
