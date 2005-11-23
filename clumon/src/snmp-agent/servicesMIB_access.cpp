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
/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.access_functions.conf,v 1.6.2.2 2004/06/21 10:12:28 dts12 Exp $
 */


#include "servicesMIB_access.h"
#include "servicesMIB_enums.h"

#include "ClusterMonitor.h"
#include "Cluster.h"
#include "clusterMonitorSnmp.h"

#include <list>

using namespace ClusterMonitoring;
using namespace std;


static unsigned int getStatusCode(counting_auto_ptr<Service>);
static string getStatusDescription(unsigned int code);



class LoopContext
{
public:
  LoopContext(counting_auto_ptr<Cluster> cluster) : 
    _cluster(cluster), 
    _services(cluster->services()),
    _curr(_services.begin()) {}
  virtual ~LoopContext() {}
  
  counting_auto_ptr<Service> curr()
  {
    if (_curr == _services.end())
      return counting_auto_ptr<Service>();
    else
      return *_curr;
  }
  counting_auto_ptr<Service> next()
  {
    if (curr().get() != NULL)
      _curr++;
    return curr();
  }
  
private:
  counting_auto_ptr<Cluster> _cluster;
  list<counting_auto_ptr<Service> > _services;
  list<counting_auto_ptr<Service> >::iterator _curr;
};

class DataContext
{
public:
  DataContext(LoopContext& loop) : 
    _service(loop.curr()) {}
  virtual ~DataContext() {}
  
  counting_auto_ptr<Service> getService()
  {
    return _service;
  }
  string str_holder;
  long long_holder;

private:
  counting_auto_ptr<Service> _service;
};



// ######################## INDEXES functions ##########################


/** returns the first data point within the rhcServicesTable table data.

    Set the my_loop_context variable to the first data point structure
    of your choice (from which you can find the next one).  This could
    be anything from the first node in a linked list, to an integer
    pointer containing the beginning of an array variable.

    Set the my_data_context variable to something to be returned to
    you later that will provide you with the data to return in a given
    row.  This could be the same pointer as what my_loop_context is
    set to, or something different.

    The put_index_data variable contains a list of snmp variable
    bindings, one for each index in your table.  Set the values of
    each appropriately according to the data matching the first row
    and return the put_index_data variable at the end of the function.
*/
netsnmp_variable_list *
rhcServicesTable_get_first_data_point(void** my_loop_context,
                                      void** my_data_context,
                                      netsnmp_variable_list* put_index_data,
                                      netsnmp_iterator_info* mydata)
{
  try {
    counting_auto_ptr<Cluster> cluster = monitor.get_cluster();
    if (cluster.get() == NULL)
      return NULL;
    
    LoopContext* loopctx = new LoopContext(cluster);
    *my_loop_context = loopctx;
    
    counting_auto_ptr<Service> service = loopctx->curr();
    if (service.get() == NULL)
      return NULL;
    
    const string& name = service->name();
    snmp_set_var_value(put_index_data, (u_char *) name.c_str(), name.size());
    return put_index_data;
  } catch ( ... ) {
    return NULL;
  }
}

/** functionally the same as rhcServicesTable_get_first_data_point, but
   my_loop_context has already been set to a previous value and should
   be updated to the next in the list.  For example, if it was a
   linked list, you might want to cast it to your local data type and
   then return my_loop_context->next.  The my_data_context pointer
   should be set to something you need later and the indexes in
   put_index_data updated again. */
netsnmp_variable_list *
rhcServicesTable_get_next_data_point(void** my_loop_context,
                                     void** my_data_context,
                                     netsnmp_variable_list* put_index_data,
                                     netsnmp_iterator_info* mydata)
{
  try {
    LoopContext* loopctx = (LoopContext*) *my_loop_context;
    if (loopctx == NULL)
      return NULL;
    
    counting_auto_ptr<Service> service = loopctx->next();
    if (service.get() == NULL)
      return NULL;
    
    const string& name = service->name();
    snmp_set_var_value(put_index_data, (u_char *) name.c_str(), name.size());
    return put_index_data;
  } catch ( ... ) {
    return NULL;
  }
}

void*
rhcServicesTable_context_convert_function(void* loop_context,
					  netsnmp_iterator_info *iinfo)
{
  try {
    LoopContext *loopctx = (LoopContext*) loop_context;
    return new DataContext(*loopctx);
  } catch ( ... ) {
    return NULL;
  }
}

void
rhcServicesTable_loop_free(void* loopctx, netsnmp_iterator_info* iinfo)
{
  delete (LoopContext*) loopctx;
}

void
rhcServicesTable_data_free(void* data, netsnmp_iterator_info* iinfo)
{
  delete (DataContext*) data;
}



// ######################## GET functions ##########################



/*
 * User-defined data access functions (per column) for data in table rhcServicesTable 
 */
/*
 * NOTE:
 * - these get_ routines MUST return data that will not be freed (ie,
 *   use static variables or persistent data).  It will be copied, if
 *   needed, immediately after the get_ routine has been called.
 */


char*
get_rhcServiceName(void* data_context, size_t* ret_len)
{
  try {
    DataContext* datactx = (DataContext*) data_context;
    if (datactx == NULL)
      return NULL;
    counting_auto_ptr<Service> service = datactx->getService();
    if (service.get() == NULL)
      return NULL;
  
    datactx->str_holder = service->name();
    *ret_len = datactx->str_holder.size();
    return (char*) datactx->str_holder.c_str();
  } catch ( ... ) {
    return NULL;
  }
}

char*
get_rhcServiceStartMode(void* data_context, size_t* ret_len)
{
  try {
    DataContext* datactx = (DataContext*) data_context;
    if (datactx == NULL)
      return NULL;
    counting_auto_ptr<Service> service = datactx->getService();
    if (service.get() == NULL)
      return NULL;
    
    if (service->autostart())
      datactx->str_holder = "Automatic";
    else
      datactx->str_holder = "Manual";
    *ret_len = datactx->str_holder.size();
    return (char*) datactx->str_holder.c_str();
  } catch ( ... ) {
    return NULL;
  }
}

char*
get_rhcServiceRunningOnNode(void* data_context, size_t* ret_len)
{
  try {
    DataContext* datactx = (DataContext*) data_context;
    if (datactx == NULL)
      return NULL;
    counting_auto_ptr<Service> service = datactx->getService();
    if (service.get() == NULL)
      return NULL;
    
    if (!service->running())
      return NULL;
    
    datactx->str_holder = service->nodename();
    *ret_len = datactx->str_holder.size();
    return (char*) datactx->str_holder.c_str();
  } catch ( ... ) {
    return NULL;
  }
}

// ## status ##

unsigned int 
getStatusCode(counting_auto_ptr<Service> service)
{
  if (service->failed())
    // failed
    return 2;
  
  if (service->running())
    // running
    return 0;
  else
    // stopped
    return 1;
}
string 
getStatusDescription(unsigned int code)
{
  switch(code) {
  case 0:
    return "Service running";
  case 1:
    return "Service stopped";
  case 2:
    return "Service failed";
  default:
    return "Unknown";
  }
}

long*
get_rhcServiceStatusCode(void* data_context, size_t* ret_len)
{
  try {
    DataContext* datactx = (DataContext*) data_context;
    if (datactx == NULL)
      return NULL;
    counting_auto_ptr<Service> service = datactx->getService();
    if (service.get() == NULL)
      return NULL;
    
    datactx->long_holder = getStatusCode(service);
    *ret_len = sizeof(datactx->long_holder);
    return &datactx->long_holder;
  } catch ( ... ) {
    return NULL;
  }
}

char*
get_rhcServiceStatusString(void* data_context, size_t* ret_len)
{
  try {
    DataContext* datactx = (DataContext*) data_context;
    if (datactx == NULL)
      return NULL;
    counting_auto_ptr<Service> service = datactx->getService();
    if (service.get() == NULL)
      return NULL;
    
    unsigned int code = getStatusCode(service);
    datactx->str_holder = getStatusDescription(code);
    *ret_len = datactx->str_holder.size();
    return (char*) datactx->str_holder.c_str();
  } catch ( ... ) {
    return NULL;
  }
}




// ######################### SET functions #######################



/** Create a data_context for non-existent rows that SETs are performed on.
 *  return a void * pointer which will be passed to subsequent get_XXX
 *  and set_XXX functions for data retrival and modification during
 *  this SET request.
 *
 *  The indexs are encoded (in order) into the index_data pointer if it
 *  would be helpful to use that information.
 */
void           *
rhcServicesTable_create_data_context(netsnmp_variable_list * index_data)
{
    return NULL;                /* XXX: you likely want to return a real pointer */
}

/** If the implemented set_* functions don't operate directly on the
   real-live data (which is actually recommended), then this function
   can be used to take a given my_data_context pointer and "commit" it
   to whereever the modified data needs to be put back to.  For
   example, if this was a routing table you could publish the modified
   routes back into the kernel at this point.

   new_or_del will be set to 1 if new, or -1 if it should be deleted
   or 0 if it is just a modification of an existing row.

   If you free the data yourself, make sure to *my_data_context = NULL */
int
rhcServicesTable_commit_row(void **my_data_context, int new_or_del)
{
    /** Add any necessary commit code here */
    /*
     */

    /*
     * return no errors.  And there shouldn't be any!!!  Ever!!!  You
     * should have checked the values long before this. 
     */
    return SNMP_ERR_NOERROR;
}
