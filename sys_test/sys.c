/* test how system() and time.h works */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void logThing(int cpu, int burst)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	printf("Arrival time: %d:%d:%d\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	char command[128];
	snprintf(command, sizeof(command), "echo \'CPU#%d: burst_time: %d\nArrival time: %d:%d:%d\' >> simulation_log", cpu, burst, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	system(command);
}

int main()
{
	system("echo \'simulation_log\' >> simulation_log");

	logThing(1, 21);
	
//	fork();

//	sleep(2);
	logThing(2, 43);
	logThing(3, 52);

	return 0;
}
