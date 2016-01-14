#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <e-hal.h>  // Epiphany Hardware Abstraction Layer
                    // functionality for communicating with epiphany chip when
                    // the application runs on a host, typically the ARM µp

#define MAIN_ITERATION 10000 // Default number of main iterations
#define SUB_ITERATION  1000  // Default number of sub iterations

static unsigned main_iteration = MAIN_ITERATION;
static unsigned sub_iteration  = SUB_ITERATION;

float f(unsigned x);
float second();

/*
 * Main entry
 */
int main(int argc, char * argv[]) {

  // Arguments handling
  switch(argc) {
    case 3: sub_iteration  = atoi(argv[2]);
    case 2: main_iteration = atoi(argv[1]);
    case 1: break;
    default:
      printf("Wrong number of args\nUsage: ./main.elf [main iterations] [sub iteration]\n");
      return 0;
  }

  float start_t = second();

  // >>>>> Begin benchamrk
  unsigned i;
  float res = 0;

  for(i = 0; i < main_iteration; i++) {
    res = res + f(i);
  }
  res *= 4;
  // <<<<< End benchmark

  float end_t   = second();
  float spent_t = end_t - start_t;
  #ifdef STAT
    printf("(%i,%i,%f)\n", main_iteration, sub_iteration, spent_t);
  #else
    printf("PI = %f\ttime spent %fs\n", res, spent_t);
  #endif
  return 0;
}

/*
 * Compute part of PI sum
 */
float f(unsigned x) {
  float res = 0;
  unsigned a = x * sub_iteration;
  unsigned b = a + sub_iteration;
  for(; a < b; a++) {
    res += pow(-1,a) / (2*a + 1);
  }
  return res;
}

/*
 * Get seconds spent from the beginning
 */
float second() {
	#include <sys/time.h>
	#include <sys/resource.h>

	struct rusage ru;
	float t;
	getrusage(RUSAGE_SELF,&ru) ;
  // user CPU time used in second + system CPU time used in second
  // + the same but in microseconds
	t = (float) (ru.ru_utime.tv_sec+ru.ru_stime.tv_sec) +
	    ((float) (ru.ru_utime.tv_usec+ru.ru_stime.tv_usec))/1.0e6 ;
	 return t ;
}
