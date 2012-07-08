// ActivityMonitor.hh --- ActivityMonitor functionality
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006, 2007, 2010, 2012 Rob Caelers <robc@krandor.nl>
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

#ifndef ACTIVITYMONITOR_HH
#define ACTIVITYMONITOR_HH

#include "config/Config.hh"

#include "IActivityMonitor.hh"
#include "IActivityMonitorListener.hh"

#include "LocalActivityMonitor.hh"

using namespace workrave::config;

class ActivityMonitor :
  public IActivityMonitor
{
public:
  typedef boost::shared_ptr<ActivityMonitor> Ptr;

public:
  static Ptr create(IConfigurator::Ptr configurator);

  ActivityMonitor(IConfigurator::Ptr configurator);
  virtual ~ActivityMonitor();

  void init(const std::string &display_name);
  void terminate();
  void suspend();
  void resume();
  void force_idle();
  void shift_time(int delta);

  void heartbeat();
  void report_external_activity(std::string who, bool act);
  
  ActivityState get_current_state();

  void set_listener(IActivityMonitorListener::Ptr l);

private:
  //! The Configurator.
  IConfigurator::Ptr configurator;

  //! Activity listener.
  IActivityMonitorListener::Ptr listener;

  //! The activity monitor
  LocalActivityMonitor::Ptr local_monitor;

  //! External activity
  std::map<std::string, gint64> external_activity;

  //! Current overall monitor state.
  ActivityState monitor_state;
};

#endif // ACTIVITYMONITOR_HH
