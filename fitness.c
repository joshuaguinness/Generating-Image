/*
	Programmed by:
	Joshua Guinness
	November 28, 2018
	for the purpose of completing Assignment 4 for 2SO3
*/

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Function which generates total distance between two images */
double comp_distance(const PIXEL *A, const PIXEL *B, int image_size) {

	/* Variable declaration */
	double distance;
	double d = 0;

	/* Loops through image_size times and sums
	the distance, storing it in d */
	for (int i = 0; i < image_size; i++) {
		int a = (A + i)->r - (B + i)->r;
		int b = (A + i)->g - (B + i)->g;
		int c = (A + i)->b - (B + i)->b;

		d += a * a + b * b + c * c;
	}
	
	/*
	for (int i = 0; i < image_size; i+2) {
		int a = (A + i)->r - (B + i)->r;
		int b = (A + i)->g - (B + i)->g;
		int c = (A + i)->b - (B + i)->b;

		int e = (A + i+1)->r - (B + i+1)->r;
		int f = (A + i+1)->g - (B + i+1)->g;
		int g = (A + i+1)->b - (B + i+1)->b;

		d += a * a + b * b + c * c + e * e + f * f + g * g;
	}
	*/

	/* Finishes the function by sqrt */
	distance = sqrt(d);

	/* Return value */
	return distance;
}

/* Computes the fitness of each individual in the population */
void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size) {

	/* Gets the image size */
	int image_size = (individual)->image.width * (individual)->image.height;

	/* Loops through image_size times and computes the fitness between the 
	original image and each one in the population, storing it in the individual
	structure */
	for (int i = 0; i < population_size; i++) {
		double fitness = comp_distance(image, (individual + i)->image.data, image_size);
		(individual + i)->fitness = fitness;
	}
}