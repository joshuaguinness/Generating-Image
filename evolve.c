/*
	Programmed by: 
	Joshua Guinness
	November 29, 2018
	for the purpose of completing Assignment 4 for 2SO3
*/

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

/* Prototype for compare function */
int cmpfunc(const void *a, const void *b);

void ImagePrint(Individual *individual, int imageCounter);

/* Evolves the population */
PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate) {

	/* Variable Declaration and Initialization */
	int width = image->width;
	int height = image->height;
	int max_color = image->max_color;

	/* Checks to see if the Population Size is 0 */
	if (population_size == 0) {
		printf("Invalid Population Size. Must be > 0.\n");
		exit(EXIT_FAILURE);
	}

	/* Generates a random population of 
	population_size */
	Individual *individuals;
	individuals = generate_population(population_size, width, height, max_color);

	/* Compute the fitness of each individual */
	comp_fitness_population(image->data, individuals, population_size);

	/* Gets the first initial fitness and sets the image counter to 1000 */
	/*
	double currentFitness = individuals->fitness;
	int imageCounter = 1000;
	*/

	/* Sort the individuals in non-decreasing order 
	of fitness */
	qsort(individuals, population_size, sizeof(Individual), cmpfunc);

	/* Outputs the first image with file name 1 and 
	adds one to the image counter */
	/*
	ImagePrint(individuals, imageCounter);
	imageCounter++;
	*/

	/* Loop through generation number of times, each time
	crossing over, mutating, comparing the fitness, then
	sorting the population */
	for (int i = 0; i < num_generations; i++) {

		crossover(individuals, population_size);
		mutate_population(individuals, population_size, rate);
		comp_fitness_population(image->data, individuals, population_size);
		qsort(individuals, population_size, sizeof(Individual), cmpfunc);

		/* Higher rate, aka more mutated pixels earlier on then 
		decreased rate as the program runs making the fitness lower
		then if the rate was static */

		/* The following if statement was designed by Hassan Jasim
		and used with permission */
		if (rate >= 0.25e-2) {
			rate -= 0.000025;
		}
		
		// Code that will print out the image ever 100 fitness 
		/*
		if ((currentFitness - individuals->fitness) >= 100.0) {
			currentFitness = individuals->fitness;
			ImagePrint(individuals, imageCounter);
			imageCounter++;
		}
		*/
	}
	
	/* Allocates memory and creates a new PPM Image and then
	takes the Individual with the lowest fitness and 
	puts the PPM_IMAGE values into the new PPM Image */
	PPM_IMAGE *finalImage = malloc(sizeof(PPM_IMAGE));
	PIXEL *array = malloc(sizeof(PIXEL[width*height]));
	for (int i = 0; i < width*height; i++) {
		(array + i)->r = (individuals->image.data + i)->r;
		(array + i)->g = (individuals->image.data + i)->g;
		(array + i)->b = (individuals->image.data + i)->b;
	}
	finalImage->data = array;
	finalImage->width = individuals->image.width;
	finalImage->height = individuals->image.height;
	finalImage->max_color = individuals->image.max_color;
	
	/* Frees all the arrays of PIXELS */
	for (int i = 0; i < population_size; i++) {

		free((individuals + i)->image.data);
	}

	/* Frees the array of individuals */
	free(individuals);

	/* Returns the PPM_IMAGE with the smallest fitness */
	return finalImage;
}

void free_image(PPM_IMAGE *p) {
	free(p->data);
	free(p);
}

/* The following compare function for qsort
was built using the materials found at the site:
https://stackoverflow.com/questions/6105513/need-
help-using-qsort-with-an-array-of-structs?fbclid=
IwAR1OD6v_JROzVHsmOyBZDW4k8K242r1pbp9TnM_eMxLzC8qv
AEUAH15c3W8*/
int cmpfunc(const void *a, const void *b)
{

	Individual *elementA = (Individual *)a;
	Individual *elementB = (Individual *)b;

	return (elementA->fitness - elementB->fitness);
}

/* Prints the image */
/*
void ImagePrint(Individual *individual, int imageCounter) {

	/* Allocates memory and creates a new PPM Image and then
	takes the Individual with the lowest fitness and
	puts the PPM_IMAGE values into the new PPM Image
	PPM_IMAGE *finalImage = malloc(sizeof(PPM_IMAGE));
	PIXEL *array = malloc(sizeof(PIXEL[individual->image.width*individual->image.height]));
	for (int i = 0; i < (individual->image.width)*(individual->image.height); i++) {
		(array + i)->r = (individual->image.data + i)->r;
		(array + i)->g = (individual->image.data + i)->g;
		(array + i)->b = (individual->image.data + i)->b;
	}
	finalImage->data = array;
	finalImage->width = individual->image.width;
	finalImage->height = individual->image.height;
	finalImage->max_color = individual->image.max_color;

	// Converts the int image counter to a string
	char str[5];
	sprintf(str, "%d", imageCounter);

	write_ppm(str, finalImage);

	free_image(finalImage);
}
*/