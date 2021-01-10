// Timer.hh --- Break Timer
//
// Copyright (C) 2001 - 2010, 2012, 2013 Rob Caelers <robc@krandor.nl>
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef TIMER_HH
#define TIMER_HH

#include <memory>

#ifdef TIME_WITH_SYS_TIME
#  include <sys/time.h>
#  include <time.h>
#else
#  ifdef HAVE_SYS_TIME_H
#    include <sys/time.h>
#  else
#    include <time.h>
#  endif
#endif

#include <string>

class DayTimePred;

enum TimerState
{
  STATE_INVALID,
  STATE_RUNNING,
  STATE_STOPPED
};

//! Event generated by the timer.
enum TimerEvent
{
  //! No event occurred.
  TIMER_EVENT_NONE,

  //! The timer was reset back to 0 after the limit was reached.
  TIMER_EVENT_RESET,

  //! The timer was reset back to 0 before the limit was reached.
  TIMER_EVENT_NATURAL_RESET,

  //! The timer reached its limit.
  TIMER_EVENT_LIMIT_REACHED,
};

//! The Timer class.
/*!
 *  The Timer receives 'active' and 'idle' events from an activity monitor.
 *  Based on these events, the timer will start or stop the clock.
 *
 */
class Timer
{
public:
  using Ptr = std::shared_ptr<Timer>;

public:
  // Construction/Destruction.
  explicit Timer(std::string id);
  virtual ~Timer();

  // Control
  void enable();
  void disable();

  void snooze_timer();
  void inhibit_snooze();

  void start_timer();
  void stop_timer();
  void reset_timer();

  void freeze_timer(bool f);

  // Timer processing.
  TimerEvent process(bool user_is_active);

  // State inquiry
  int64_t get_elapsed_time() const;
  int64_t get_elapsed_idle_time() const;
  bool is_running() const;
  bool is_enabled() const;

  // Auto-resetting.
  void set_auto_reset(int t);
  void set_auto_reset_enabled(bool b);
  void set_daily_reset(DayTimePred *daily_reset);
  bool is_auto_reset_enabled() const;
  int64_t get_auto_reset() const;
  int64_t get_next_reset_time() const;

  // Limiting.
  void set_limit(int t);
  void set_limit_enabled(bool b);
  bool is_limit_enabled() const;
  int64_t get_limit() const;
  int64_t get_next_limit_time() const;

  // Snoozing.
  void set_snooze(int64_t time);
  int64_t get_snooze() const;

  // Timer ID
  std::string get_id() const;

  // State serialization.
  std::string serialize_state() const;
  bool deserialize_state(const std::string &state, int version);
  // void set_state(int elapsed, int idle, int overdue = -1);

  int64_t get_total_overdue_time() const;
  void daily_reset();

private:
  void compute_next_limit_time();
  void compute_next_reset_time();
  void compute_next_daily_reset_time();

private:
  //! Is this timer enabled ?
  bool timer_enabled;

  //! Is the timer frozen? A frozen timer only counts idle time.
  bool timer_frozen;

  //! State of the timer.
  TimerState timer_state;

  //! Default snooze time
  int64_t snooze_interval;

  //! Don't snooze til next reset or changes.
  bool snooze_inhibited;

  //! Is the timer limit enabled?
  bool limit_enabled;

  //! Timer limit interval.
  int64_t limit_interval;

  //! Is the timer auto reset enabled?
  bool auto_reset_enabled;

  //! Automatic reset time interval.
  int64_t auto_reset_interval;

  //! Daily auto reset checker (NULL if not used)
  DayTimePred *daily_auto_reset;

  //! Elapsed time.
  int64_t elapsed_timespan;

  //! The total elapsed time the last time the limit was reached.
  int64_t elapsed_timespan_at_last_limit;

  //! Elapsed Idle time.
  int64_t elapsed_idle_timespan;

  //! Total overdue time.
  int64_t total_overdue_timespan;

  //! Time when the timer was last started.
  int64_t last_start_time;

  //! Time when the timer was last stopped.
  int64_t last_stop_time;

  //! Time when the timer was last reset.
  int64_t last_reset_time;

  //! Time when the timer was last reset because of a daily reset.
  int64_t last_daily_reset_time;

  //! Next automatic reset time.
  int64_t next_reset_time;

  //! Next daily reset time.
  int64_t next_daily_reset_time;

  //! Next limit time.
  int64_t next_limit_time;

  //! Id of the timer.
  std::string timer_id;
};

#endif // TIMER_HH
