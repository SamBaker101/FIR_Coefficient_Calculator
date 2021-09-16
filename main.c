//Sam Baker
//09/2021
//Calculator to determine coefficients for FIR filter design

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define PI 3.14159265

struct attributes {
	int sample_freq;
	int taps;
	int Band;
};


void get_attributes(struct attributes*);
double* low_pass(struct attributes*, double*);


int main() {
	struct attributes instance;
	printf("Welcome \n\n");

	get_attributes(&instance);

	printf("\nSample Rate: %d, Taps: %d \n", 
		instance.sample_freq, instance.taps);

	double* impulse_resp = (double*)malloc((instance.taps+1)*sizeof(double));
	impulse_resp = low_pass(&instance, impulse_resp);
}


//Takes user input to define system variables
void get_attributes(struct attributes* instance){
	printf("Please Enter Sample Frequency \n");
	fflush(stdout);
	scanf("%d", &(instance->sample_freq));

	printf("Please Enter Number of Taps \n");
	fflush(stdout);
	scanf("%d", &(instance->taps));
}

double* low_pass(struct attributes* instance, double* h){
	int cutoff;
	double temp;
	double sum = 0;

	printf("Please Enter Cutoff Freq \n");
	fflush(stdout);
	scanf("%d", &(cutoff)); 

	for (int i = 1; i < (instance->taps/2)+1; i++){
		temp = sin((PI*i*cutoff)/instance->sample_freq)/((PI*i*cutoff)/instance->sample_freq);
		sum += 2*temp;
		h[instance->taps/2+(i-1)] = temp;
		h[instance->taps/2-(i-1)] = temp;
		printf("%d   %1.20f \n",i, h[instance->taps/2+(i-1)]);
	}

	printf("\n %1.10f \n\n", sum);


	
	for (int i = 0; i < instance->taps; i++){
		h[i] = h[i]/sum;
		printf("%d   %1.20f \n",i, h[i]);
	}
	


	return h;
}