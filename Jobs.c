#include <errno.h>
#include <sys/wait.h>

#include "Jobs.h"
#include "deq.h"
#include "error.h"

extern Jobs newJobs() {
  return deq_new();
}

extern void addJobs(Jobs jobs, Pipeline pipeline) {
  deq_tail_put(jobs,pipeline);
}

extern int sizeJobs(Jobs jobs) {
  return deq_len(jobs);
}

extern void reapJobs(Jobs jobs) {
  (void)jobs;
  int result;
  do {
    result=waitpid(-1,0,WNOHANG);
  } while (result>0);
  if (result==-1 && errno != ECHILD && errno != EINTR)
    ERROR("waitpid() failed");
}

extern void waitJobs(Jobs jobs) {
  (void)jobs;
  while (waitpid(-1,0,0)==-1) {
    if (errno == EINTR)
      continue;
    if (errno == ECHILD)
      break;
    ERROR("waitpid() failed");
  }
}

extern void freeJobs(Jobs jobs) {
  deq_del(jobs,freePipeline);
}
