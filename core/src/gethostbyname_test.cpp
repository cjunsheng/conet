/*
 * =====================================================================================
 *
 *       Filename:  gethostbyname_test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年12月15日 03时44分59秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include <stdlib.h>
#include "conet_all.h"
#include "gflags/gflags.h"
#include "glog/logging.h"

#include <netdb.h>

using namespace conet;

DEFINE_int32(task_num, 10, "query time");
DEFINE_int32(num, 100, "query time");
DEFINE_string(name, "www.baidu.com", "resolve host name");

coroutine_t  *g_co = NULL;

int g_finish_cnt = 0;
int t(void *arg)
{
    for (int i=0; i< FLAGS_num; ++i) 
    {
        hostent * host = gethostbyname(FLAGS_name.c_str());
        if (host) {
            LOG(INFO)<<host->h_name;
        }
        else {
            LOG(ERROR)<<"parse "<<FLAGS_name<<" failed!";
        }
    }
    ++g_finish_cnt;
    return 0;
}



int main(int argc, char * argv[])
{
  gflags::ParseCommandLineFlags(&argc, &argv, false); 
  google::InitGoogleLogging(argv[0]);

  for (int i= 0; i< (int) FLAGS_task_num; ++i)
  {
      conet::coroutine_t *co = conet::alloc_coroutine(&t,  NULL);
      conet::set_auto_delete(co);
      resume(co, NULL);
  }

  while (g_finish_cnt < FLAGS_task_num) {
      conet::dispatch();
  }
  //t(NULL);
  return 0;
}

