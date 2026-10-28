#include "lib.h"

void get_time(double *time_s, double *time_ns)
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	*time_s = (double)(time.tv_sec);
	*time_ns = (double)(time.tv_nsec);
}

int get_time_stamp(double start_time_s, double start_time_ns)
{
	double curr_time_s, curr_time_ns;
	double time_stamp = 0;
	
	get_time(&curr_time_s, &curr_time_ns);
	
	time_stamp = (curr_time_s - start_time_s);
	time_stamp *= 1e9; //Convert time stamp in ns
	
	time_stamp = time_stamp + (curr_time_ns - start_time_ns); //Add precision to time stamp
		
	return((int)time_stamp);
}