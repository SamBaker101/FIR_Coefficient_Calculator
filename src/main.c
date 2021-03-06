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


//Utility functions
void get_attributes(struct attributes*);
double* normalize(struct attributes*, double*);
void print_coeffs(struct attributes*, double*);
void print_attr(struct attributes*);
void generate_impulse_file(struct attributes*, double*);
void generate_freq_file(struct attributes*, double*, double);


//Calculator Functions
double* low_pass(struct attributes*, double*);


int main() {
	printf("Welcome \n\n");

	struct attributes instance;
	get_attributes(&instance);
	double* impulse_resp = (double*)malloc((instance.taps+1)*sizeof(double));

	print_attr(&instance);
	
	impulse_resp = low_pass(&instance, impulse_resp);
	impulse_resp = normalize(&instance, impulse_resp);
	print_coeffs(&instance, impulse_resp);

	generate_impulse_file(&instance, impulse_resp);
	generate_freq_file(&instance, impulse_resp, (instance.sample_freq/2)/200);
	
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


//Calculates coefficients using SINC function and shifts impulse response
double* low_pass(struct attributes* instance, double* h){
	int cutoff;
	double temp;

	printf("Please Enter Cutoff Freq \n");
	fflush(stdout);
	scanf("%d", &(cutoff)); 


	for (int i = 1; i < (instance->taps/2)+1; i++){
		temp = sin((2*PI*cutoff*i)/instance->sample_freq)/(PI*i);

		h[instance->taps/2+(i-1)] = temp;
		h[instance->taps/2-(i)] = temp;
	}

	return h;
}


//Normalize Coefficient Values
double* normalize(struct attributes* instance, double* h){
	double sum = 0;

	for (int i = 0; i < instance->taps; i++){
		sum += 2*h[i];
	}

		
	for (int i = 0; i < instance->taps; i++){
		h[i] = h[i]/sum;
	}
	
	return h;
}


//Print Coefficients to Console
void print_coeffs(struct attributes* instance, double* h){
	printf("\n Coefficients: \n \n");
	for (int i = 0; i < instance->taps; i++){
		printf("%d   %1.20f \n",i, h[i]);
		fflush(stdout);
	}
	printf("\n");
}


//Print Attributes to Console
void print_attr(struct attributes* instance){
	printf("\nSample Rate: %d, Taps: %d \n\n", 
		instance->sample_freq, instance->taps);
}
	

//Generates a data file containing the impulse response of the system for plotting
void generate_impulse_file(struct attributes* instance, double* h){
	FILE* file_pointer;

	file_pointer = fopen("data/impulse.txt", "w");

	if(file_pointer == NULL){
		printf("Error generating impulse.dat");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < instance->taps; i++){
		fprintf(file_pointer, "%f\t %f\n", i*(1.0/instance->sample_freq), h[i]);
	}


	fclose(file_pointer);
	printf("File Generated \n");
	fflush(stdout);
}

void generate_freq_file(struct attributes* instance, double* h, double step){
	FILE* file_pointer;
	double test_freq = 0;
	double x, y, amp;

	file_pointer = fopen("data/freq.txt", "w");

	if(file_pointer == NULL){
		printf("Error generating impulse.dat");
		exit(EXIT_FAILURE);
		}

	while (test_freq <= instance->sample_freq/2){
		amp = 0;

		for (int i = 0; i < instance->taps; i++){
			amp += h[i]*cos((2*PI*i*test_freq)/(instance->sample_freq));
			}

		amp = pow(amp,2);
		fprintf(file_pointer, "%f\t %f\n", test_freq, amp);
		test_freq += step;
		}
	


	fclose(file_pointer);
	printf("File Generated \n");
	fflush(stdout);
}

