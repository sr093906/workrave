// Copyright (C) 2001, 2002, 2003, 2007, 2008, 2011, 2013 Rob Caelers & Raymond Penners
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

#ifndef W32GRABHARPOON_HH
#define W32GRABHARPOON_HH

#include <gtk/gtk.h>

#include <windows.h>

#undef __out
#undef __in

#if defined(interface)
#undef interface
#endif

#include "Grab.hh"

class W32GrabHarpoon : public Grab
{
public:
  bool can_grab();
  void grab(GdkWindow *window);
  void ungrab();
};

#endif // W32GRABHARPOON_HH
