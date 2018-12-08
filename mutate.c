/*
	Programmed by:
	Joshua Guinness
	November 28, 2018
	for the purpose of completing Assignment 4 for 2SO3
*/

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

/* Function which mutates an image in an individual */
void mutate(Individual *individual, double rate) {

	/* Variable declaration and initialization */
	int sizeOfImage = individual->image.width * individual->image.height;
	int max_color = individual->image.max_color;

	/* Figures out the number of pixels to mutate */
	int toMutate = (int)(rate / 100 * sizeOfImage);

	/* Loops through ToMutate times and changes the r,g,b values of random
	pixels */
	for (int i = 0; i < toMutate; i++) {

		int pixelToMutate = rand() % sizeOfImage;
		//printf("Pixel to Mutate: %d\n", pixelToMutate);
		(individual->image.data + pixelToMutate)->r = rand() % (max_color+1);
		(individual->image.data + pixelToMutate)->g = rand() % (max_color+1);
		(individual->image.data + pixelToMutate)->b = rand() % (max_color+1);
	}
}

/* Mutates all individuals starting from index population_size/4 */
void mutate_population(Individual *individual, int population_size, double rate) {

	/* Variable declaration and initialization */
	int start = (int)(population_size / 4);

	/* Mutates all the individuals in a population 
	starting from start */
	for (int i = start; i < population_size; i++) {
		mutate((individual + i), rate);
	}
}