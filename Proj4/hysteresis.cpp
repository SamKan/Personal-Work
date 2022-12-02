// hysteresis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// hysteresis.c : 

#include <stdio.h>
#include <stdlib.h>

const int MAX_DATA = 269450 + 1;  // Number of data points in input data file

// project #4 


int hysteresis(int in)
{
	const int low_limit  =  5;
	const int high_limit = 25;
	const int out_high   = 40;
	const int out_low    =  0;

	static int old_out = out_low; // initialize old_out to out_low = 0
	static int out     = out_low; // initialize     out to out_low = 0

	
	if ((in >= high_limit) && (old_out == out_low))
		out = out_high;
	if ((in <= low_limit) && (old_out == out_high))
		out = out_low;

	old_out = out;

	return out;
}




int main(void)
{
	FILE* fp_in;  // pointer to input file pointer
	FILE* fp_out; // output file pointer

	int in = 0;   // input value
	int out = 0;  // output result
	int dpn = 0;  // data point number

	// use data_per_sec with count down timer
	int data_per_sec = 16000;   // There are 16,000 data points per second
	// there are 269,450 data points

	// errno_t is a Microsoft specific file command
	// If you are using another environment, please check file open/close/error operations

	// please update file path names for you computer
	errno_t err_in = fopen_s(&fp_in,   "C:/Users/cello/OneDrive/Desktop/CMSC 411/Proj4/input.txt.txt", "r");   // may need to change file path
	errno_t err_out = fopen_s(&fp_out, "C:/Users/cello/OneDrive/Desktop/CMSC 411/Proj4/hyst.txt", "w"); // may need to change file path

	if (err_in)
		printf("In.txt File Open Error.  File was not opened. \n");

	if (err_out)
		printf("Out.txt File Open Error.  File was not opened. \n");

	else
	{
		while (!feof(fp_in) && dpn < MAX_DATA)
		{
			fscanf_s(fp_in, "%d", &in);

			out = hysteresis(in); // call hysteresis function 

			dpn = dpn + 1;

			fprintf_s(fp_out, "%d \t %d \n", in, out);  // you may write more fields to the output file

		}

	}

	fclose(fp_in);
	fclose(fp_out);
	printf("Done. \n");
}