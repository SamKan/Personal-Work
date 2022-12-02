//  hpf.c : This file contains the 'main' function. Program execution begins and ends there.

#include <stdio.h>
#include <stdlib.h>

const int MAX_DATA = 269450 + 1;  // Number of data points in input data file

// insert function call for project 2.1
int lpf(int in)
{
	// low pass filter equations
	// w(n) = in(n) + 15/16 w(n – 1)
	// out(n) = 1/16[w(n) + w(n - 1)]

	static int w_old = 0;

	// v_old to calculate 15/16 w(n-1)

	int v_old = 16 * w_old - w_old;
	v_old = v_old / 16;

	int w = in + v_old;
	int out = w + w_old;

	out = out / 16;

	w_old = w;




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
	errno_t err_in = fopen_s(&fp_in, "C:/Users/cello/OneDrive/Desktop/CMSC 411/Proj3/Audio.txt", "r");
	errno_t err_out = fopen_s(&fp_out, "C:/Users/cello/OneDrive/Desktop/CMSC 411/Proj3/lpf.txt", "w");

	if (err_in)
	{
		printf("In.txt File Open Error.  File was not opened. \n");
		exit(1);
	}


	if (err_out)
	{
		printf("Out.txt File Open Error.  File was not opened. \n");
		exit(1);
	}


	else
	{
		while (!feof(fp_in) && dpn < MAX_DATA)
		{
			fscanf_s(fp_in, "%d", &in);

			out = lpf(in); // high pass filter.  

			dpn = dpn + 1;

			fprintf_s(fp_out, "%d \t %d \n", in, out);  // you may write more fields to the output file

		}

	}

	printf("Done. \n");
}