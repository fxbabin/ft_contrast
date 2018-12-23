/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contrast_th.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbabin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:51:23 by fbabin            #+#    #+#             */
/*   Updated: 2018/12/23 12:51:30 by fbabin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tpool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*   
The following structure contains the necessary information  
to allow the function "dotprod" to access its input data and 
place its output into the structure.  This structure is 
unchanged from the sequential version.
*/

typedef struct 
 {
   double      *a;
   double      *b;
   double     sum; 
   int     veclen; 
 } DOTDATA;

/* Define globally accessible variables and a mutex */

#define NUMTHRDS 4
#define VECLEN 100000
   DOTDATA dotstr; 
   pthread_t callThd[NUMTHRDS];
   pthread_mutex_t mutexsum;

/*
The function dotprod is activated when the thread is created.
As before, all input to this routine is obtained from a structure 
of type DOTDATA and all output from this function is written into
this structure. The benefit of this approach is apparent for the 
multi-threaded program: when a thread is created we pass a single
argument to the activated function - typically this argument
is a thread number. All  the other information required by the 
function is accessed from the globally accessible structure. 
*/

void *dotprod(void *arg)
{

/* Define and use local variables for convenience */

   int i, start, end, len ;
   long offset;
   double mysum, *x, *y;
   offset = (long)arg;
     
   len = dotstr.veclen;
   start = offset*len;
   end   = start + len;
   x = dotstr.a;
   y = dotstr.b;

/*
Perform the dot product and assign result
to the appropriate variable in the structure. 
*/
   mysum = 0;
   for (i=start; i<end ; i++) 
    {
      mysum += (x[i] * y[i]);
    }

/*
Lock a mutex prior to updating the value in the shared
structure, and unlock it upon updating.
*/
   pthread_mutex_lock (&mutexsum);
   dotstr.sum += mysum;
   printf("Thread %ld did %d to %d:  mysum=%f global sum=%f\n",offset,start,end,mysum,dotstr.sum);
   pthread_mutex_unlock (&mutexsum);

   pthread_exit((void*) 0);
}

/* 
The main program creates threads which do all the work and then 
print out result upon completion. Before creating the threads,
The input data is created. Since all threads update a shared structure, we
need a mutex for mutual exclusion. The main thread needs to wait for
all threads to complete, it waits for each one of the threads. We specify
a thread attribute value that allow the main thread to join with the
threads it creates. Note also that we free up handles  when they are
no longer needed.
*/

int main (int argc, char *argv[])
{
long i;
double *a, *b;
void *status;
pthread_attr_t attr;

/* Assign storage and initialize values */

a = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
b = (double*) malloc (NUMTHRDS*VECLEN*sizeof(double));
  
for (i=0; i<VECLEN*NUMTHRDS; i++) {
  a[i]=1;
  b[i]=a[i];
  }

dotstr.veclen = VECLEN; 
dotstr.a = a; 
dotstr.b = b; 
dotstr.sum=0;

pthread_mutex_init(&mutexsum, NULL);
         
/* Create threads to perform the dotproduct  */
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

for(i=0;i<NUMTHRDS;i++)
  {
  /* Each thread works on a different set of data.
   * The offset is specified by 'i'. The size of
   * the data for each thread is indicated by VECLEN.
   */
   pthread_create(&callThd[i], &attr, dotprod, (void *)i); 
   }

pthread_attr_destroy(&attr);
/* Wait on the other threads */

for(i=0;i<NUMTHRDS;i++) {
  pthread_join(callThd[i], &status);
  }
/* After joining, print out the results and cleanup */

printf ("Sum =  %f \n", dotstr.sum);
free (a);
free (b);
pthread_mutex_destroy(&mutexsum);
pthread_exit(NULL);
}   

#define NB_THREADS 4

void	process_queue(t_env *env, t_queue **queue)
{
	char	*tmp;
    int     i;

    i = 0;
	while ((tmp = ft_dequeue(queue)))
	{
        pthread_create(&callThd[i], &attr, contrast_chunk, tmp); 
		if (i == NB_THREADS)
        {
            //join
            i = 0;
        }
        //contrast_chunk(env, tmp);
	}
    if (i > 0)
        //join
}

void	process_file(t_env *env)
{
	char		buff[BUF_SIZE + 1];
	t_queue		*chunk_queue;
	char		*chunk;
	int			ret;

	ret = 0;
	chunk = NULL;
	chunk_queue = NULL;
	process_header(env);
	ft_bzero((char*)&buff, BUF_SIZE);
	while ((ret = read(env->input_fd, buff, BUF_SIZE)) > 0)
	{
		chunk = read_chunk(env, (char*)&buff, ret);
		//chunk = contrast_chunk(env, chunk);
		ft_enqueue(&chunk_queue, chunk);
	}
	process_queue(env, &chunk_queue);
	ft_qdel(&chunk_queue);
}

int		main(int argc, char **argv)
{
	t_env	env;
    
    pthread_t callThd[NUMTHRDS];
    pthread_mutex_t mutexsum;
    pthread_attr_t attr;
	env.contrast = -1;
	env.input_fd = -1;
	env.output_fd = -1;
	env.max_contrast = -1;
	env.line_len = 0;
    env.mutex
    env.attr
	env.queue = NULL;

    pthread_mutex_init(&mutexsum, NULL);
         
    /* Create threads to perform the dotproduct  */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	if (argc != 7)
		ft_usage();
	if (!check_arguments(argc, argv, &env))
		ft_usage();
	
    process_file(&env);
    
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
	
    close(env.input_fd);
	ft_qdel(&(env.queue));
	return (0);
}
