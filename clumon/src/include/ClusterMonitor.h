/*
  Copyright Red Hat, Inc. 2005

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2, or (at your option) any
  later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; see the file COPYING.  If not, write to the
  Free Software Foundation, Inc.,  675 Mass Ave, Cambridge,
  MA 02139, USA.
*/
/*
 * Author: Stanko Kupcevic <kupcevic@redhat.com>
 */


#ifndef ClusterMonitor_h
#define ClusterMonitor_h

#include "Cluster.h"
#include "counting_auto_ptr.h"
#include "clumond_globals.h"

#include <string>


namespace ClusterMonitoring
{


class ClusterMonitor
{
 public:
  ClusterMonitor(const std::string& socket_path=MONITORING_CLIENT_SOCKET);
  virtual ~ClusterMonitor();
  
  counting_auto_ptr<Cluster> get_cluster();
  
 private:
  std::string _sock_path;
  unsigned int time();
  
  ClusterMonitor(const ClusterMonitor&);
  ClusterMonitor& operator= (const ClusterMonitor&);
  
};  // class ClusterMonitor


};  // namespace ClusterMonitoring


#endif
