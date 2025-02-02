// NetworkLogDialog.hh --- Network Log Dialog
//
// Copyright (C) 2002, 2003, 2007 Raymond Penners <raymond@dotsphinx.com>
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

#ifndef NETWORKLOGDIALOG_HH
#define NETWORKLOGDIALOG_HH

#include <cstdio>

#include <string>

class TimeEntry;

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/dialog.h>
#include <gtkmm/textbuffer.h>

namespace Gtk
{
  class TextView;
}

#include "core/DistributionLogListener.hh"
#include "IApplication.hh"

class NetworkLogDialog
  : public Gtk::Dialog
  , public workrave::DistributionLogListener
{
public:
  NetworkLogDialog(std::shared_ptr<IApplication> app);
  ~NetworkLogDialog() override;

  int run();

private:
  void init();
  void distribution_log(std::string msg) override;
  void on_response(int response) override;

  std::shared_ptr<IApplication> app;
  Gtk::TextView *text_view{nullptr};
  Gtk::ScrolledWindow scrolled_window;
  Glib::RefPtr<Gtk::TextBuffer> text_buffer;
};

#endif // NETWORKLOGWINDOW_HH
