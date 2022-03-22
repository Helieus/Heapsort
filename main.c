/*
 * C Program to sort an array based on heap sort algorithm(MAX heap)
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCHAR 10

void printArray(int* theArray, int noOfElementsInArray, char* title, FILE* outputFile)
{
//screen
    printf("%s array\'s %d elements are:\t", title, noOfElementsInArray);
	
    for (int i = 0; i < noOfElementsInArray; i++)
        printf("%d\t ", theArray[i]);
	
	printf("\r\n");
	
//output file
    fprintf(outputFile, "%s array\'s %d elements are:\t", title, noOfElementsInArray);
	
    for (int i = 0; i < noOfElementsInArray; i++)
        fprintf(outputFile, "%d\t ", theArray[i]);
	
	fprintf(outputFile, "\r\n");
}

FILE* openOutputFile(char* filename)
{	
    FILE *fp;
    char str[MAXCHAR];
 
    fp = fopen(filename, "w");
    if (fp == NULL){
        printf("Could not open file %s. Is the directory where the executable exists writable?\r\n",filename);
        exit(-1);
    }

	return fp;
}

int readData(char* filename, int** data, int* noOfElementsInData)
{	
    FILE *fp;
    char str[MAXCHAR];
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s. Please place the input files in the same directory with the executable!\r\n",filename);
        return -1;
    }
	
	*noOfElementsInData = -1;
    while (fgets(str, MAXCHAR, fp) != NULL)
	{
		if (*noOfElementsInData == -1)
		{
			*data = (int *) malloc(atoi(str) * sizeof(int));
			*noOfElementsInData = *noOfElementsInData + 1;
		}
		else
		{
			(*data)[*noOfElementsInData] = atoi(str);
			*noOfElementsInData = *noOfElementsInData + 1;
		}
	}
	fclose(fp);
	
	return 1;
}

void heapsort(char* filename, FILE* outputFile)
{
    int i, j, c, root, temp;	
	int* heap;
	int noOfElementsInData = 0;
	
	if (readData(filename, &heap, &noOfElementsInData) != -1)
	{
		printf("File %s\r\n", filename);
		printArray(heap, noOfElementsInData, "Input data", outputFile);
			   
		for (i = 1; i < noOfElementsInData; i++)
		{
			c = i;
			do
			{
				root = (c - 1) / 2;
				if (heap[root] < heap[c])   /* to create MAX heap array */
				{
					temp = heap[root];
					heap[root] = heap[c];
					heap[c] = temp;
				}
				c = root;
			} while (c != 0);
		}
		
		printArray(heap, noOfElementsInData, "Heap", outputFile);
		
		int currStep = 1;
		char stepTitle[15];
		
		for (j = noOfElementsInData - 1; j >= 0; j--)
		{
			temp = heap[0];
			heap[0] = heap[j];    /* swap max element with rightmost leaf element */
			heap[j] = temp;
			root = 0;
			do
			{
				c = 2 * root + 1;    /* left node of root element */
				if ((heap[c] < heap[c + 1]) && c < j-1)
					c++;
				if (heap[root]<heap[c] && c<j)    /* again rearrange to max heap array */
				{
					temp = heap[root];
					heap[root] = heap[c];
					heap[c] = temp;
				}
				
				root = c;
				
				sprintf(stepTitle, "Step %d heap", currStep);
				printArray(heap, noOfElementsInData, stepTitle, outputFile);
				currStep++;
				
			} while (c < j);
		}
		
		printArray(heap, noOfElementsInData, "The sorted", outputFile);
		printf("\r\n\r\n");
		
		fclose(outputFile);
	}	
}

void main()
{
	char filename[15];
	char filename_output[15];
	char temp[3];
	
	for (int i=1; i<5; i++)
	{
		strcpy(filename, "data_");
		sprintf(temp,"%d",i);
		strcat(filename, temp);
		
		strcpy(filename_output, filename);
		strcat(filename_output, "_output");
		
		strcat(filename, ".txt");
		strcat(filename_output, ".txt");
		
		FILE* oututFile = openOutputFile(filename_output);
		heapsort(filename, oututFile);
	}
}
