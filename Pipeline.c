#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#include "Pipeline.h"
#include "deq.h"
#include "error.h"

typedef struct {
  Deq processes;
  int fg;			// not "&"
} *PipelineRep;

extern Pipeline newPipeline(int fg) {
  PipelineRep r=(PipelineRep)malloc(sizeof(*r));
  if (!r)
    ERROR("malloc() failed");
  r->processes=deq_new();
  r->fg=fg;
  return r;
}

extern void addPipeline(Pipeline pipeline, Command command) {
  PipelineRep r=(PipelineRep)pipeline;
  deq_tail_put(r->processes,command);
}

extern int sizePipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  return deq_len(r->processes);
}

extern int foregroundPipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  return r->fg;
}

static void execute(Pipeline pipeline, Jobs jobs, int *jobbed, int *eof) {
  PipelineRep r=(PipelineRep)pipeline;
  int input_fd=STDIN_FILENO;
  int count=sizePipeline(r);
  pid_t pids[count];

  for (int i=0; i<count && !*eof; i++) {
    int pipe_fds[2]={-1,-1};
    int output_fd=STDOUT_FILENO;
    if (i+1<count && pipe(pipe_fds)==-1)
      ERROR("pipe() failed");
    if (i+1<count)
      output_fd=pipe_fds[1];
    execCommand(deq_head_ith(r->processes,i),pipeline,jobs,jobbed,eof,
                r->fg,input_fd,output_fd,r->fg,&pids[i]);
    if (input_fd!=STDIN_FILENO)
      close(input_fd);
    if (output_fd!=STDOUT_FILENO)
      close(output_fd);
    input_fd=i+1<count ? pipe_fds[0] : STDIN_FILENO;
  }
  if (input_fd!=STDIN_FILENO)
    close(input_fd);
  if (r->fg) {
    for (int i=0; i<count; i++)
      while (waitpid(pids[i],0,0)==-1 && errno==EINTR);
  }
}

extern void execPipeline(Pipeline pipeline, Jobs jobs, int *eof) {
  int jobbed=0;
  execute(pipeline,jobs,&jobbed,eof);
  if (!jobbed)
    freePipeline(pipeline);	// for fg builtins, and such
}

extern void freePipeline(Pipeline pipeline) {
  PipelineRep r=(PipelineRep)pipeline;
  deq_del(r->processes,freeCommand);
  free(r);
}
