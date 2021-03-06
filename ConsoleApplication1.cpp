// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include <vector>


int noOfProcesses = 3;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int rank;
	int vector[] = {3, 4, 6, 7, 8, 10, 6, 20};

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		int start = 0;
		int slice[10];
		for (int i = 0; i < noOfProcesses - 1; i ++) {
			
			int end = start + _countof(vector) / noOfProcesses ;
			int k = 0;
			for (int j = start; j < end ; j++) {
				slice[k] = vector[j];
				k++;
			}
			MPI_Send(vector, _countof(vector), MPI_INT, i, 0, MPI_COMM_WORLD);
			start += _countof(vector) / noOfProcesses ;
		}
		int k = 0;
		for (int j = start; j < _countof(vector); j++) {
			slice[k] = vector[j];
			k++;
		}
		MPI_Send(vector, _countof(vector), MPI_INT, noOfProcesses , 0, MPI_COMM_WORLD);
		int sum = 0;
		for (int i = 0; i < noOfProcesses i++) {
			MPI_Recv(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += sum;
		}
		printf("Sum =  %d \n", sum);
	}
	else 
	{
		char slice[10];
		MPI_Recv(slice, _countof(slice), MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = 0;
		for (int i = 0; i < _countof(slice); i++) {
			sum += slice[i];
		}
		MPI_Send(&sum, 1, MPI_INT, noOfProcesses , 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
    return 0;
}

