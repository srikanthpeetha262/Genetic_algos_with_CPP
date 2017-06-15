/*
######################################################################

Author: Srikanth Peetha
About: Implementating Genetic algorithm & Roulette wheel algorithms

######################################################################
*/

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>

using namespace std;

//float getGene(float input, float fitness, float out);

	
int pop_count = 10;
int elements = 3;

float input[20][3]; // 20-> pop_count, 3 -> elements
float newGen[20][3]; // 20-> pop_count, 3 -> elements
int i,j,KE;


float * getGene(float input[][3], float fit_probb[], float out[], float fit_sum)
{
	
	//cout << "Working" << endl;
	float randNum_1;

	randNum_1 = (((float) (rand()% 100))/48)/3;
	//cout << randNum_1 << "\n";

	static float gene_1[3]; // 3 is the no.of elements
	float probb_sum = 0.0;

	for (i=0; i<pop_count; i++)
	{
		probb_sum += fit_probb[i];

		if(randNum_1 < probb_sum)
		{
			for(j=0; j<elements; j++)
			{
				gene_1[j] = input[i][j];
			}
			break;
		}
	}



	static float gene_2[3];
	float randNum_2;
	randNum_2 = (((float) (rand()% 100))/48)/3;
	//cout << randNum_2 << "\n";


	probb_sum = 0.0;

	for (i=0; i<pop_count; i++)
	{
		probb_sum += fit_probb[i];

		if(randNum_2 < probb_sum)
		{
			for(j=0; j<elements; j++)
			{
				gene_2[j] = input[i][j];
			}
			break;
		}
	}

	
	static float cross[3];

	for (i=0; i<elements; i++)
	{
		cross[i] = gene_1[i];
	}

	int temp1, temp2;
	temp1 = (rand()% 15 ) / 5;
	temp2 = (rand()% 15 ) / 5;

	cross[temp1] = gene_2[temp1];
	cross[temp2] = gene_2[temp2];

	int chance;
	chance = rand()%100;

	int index;
	float increment;

	if(chance < 15)
	{
		index = (rand()% 15 ) / 5;
		increment = (((float)(rand()%101))/50-1)/8;

		cross[index] = cross[index] + increment;
	}

	return cross;
}


int main()
{
	srand (time(NULL));

	//~~~ Begin: Input generation
	for (i=0; i<pop_count; i++)
	{
		for (j=0; j<elements; j++)
		{
			KE = (((float) (rand()% 100))/48)/3;
			input[i][j] = ((float) (rand()% 100))/48 + KE;
			//input [i][j] = (( (float) (rand()%100) )/50+0.1);
		}

	}
	//~~~ End: Input generation


	//~~~ Begin: output and fitness calculation

	float out [pop_count];
	float fitness [pop_count];
	float fit_probb [pop_count];
	float fit_sum = 0.0;
	float *new_1;

	int iterations = 500;
	int count = 0;


//~~~ Begin: While Loop for iteration

	while(count < iterations)
	{
		for (i=0; i<pop_count; i++)
		{
			out[i] = pow((input[i][0] - 1),2) + pow((input[i][1] - 2),2) + pow((input[i][2] - 3),2);

			fitness[i] = exp(-out[i]);
			fit_sum += fitness[i];
		}

		for (i=0; i<pop_count; i++)
		{
			fit_probb[i] = fitness[i] / fit_sum;
		}


		//~~~ End: output and fitness calculation


		//~~~ Begin: Algorithm

		int k = 0;
		for (k=0; k<pop_count; k++)
		{
			new_1 = getGene(input, fit_probb, out, fit_sum);

			for (j=0; j<elements; j++)
			{
				newGen[k][j] = new_1[j];
			}

		}

		//~~~ Replace input with new generation
		i = 0;
		j = 0;
		for (i=0; i<pop_count; i++)
		{
			for (j=0; j<elements; j++)
			{
				input[i][j] = newGen[i][j];
			}

		}


	count += 1;
	}

//~~~ End: While Loop for iteration




	//~~~ Begin: Printing output
	cout << "\n";
	int k = 0;
	int min;
	j = 0;
	for (k=0; k<(pop_count-1); k++)
	{
		if(out[k] < out[k+1])
			min = k;

		else
			min = k+1;
	}


	i = 0;

	for (j=0; j<elements; j++)
	{
		cout << input[min][j] << ", ";
	}


	cout << "\n" << "end" << "\n";
	//~~~ End: Printing output

	return 0;
}





