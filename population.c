/*
	Programmed by:
	Joshua Guinness
	November 28, 2018
	for the purpose of completing Assignment 4 for 2SO3
*/

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Function which generates a random image */
PIXEL *generate_random_image(int width, int height, int max_color) {

	/* Creating and allocating space for a width * height 
	sized array */
	PIXEL *a;
	a = malloc(sizeof(PIXEL[width*height]));

	/* Loops through width * height times and each time 
	puts random values in the r,g,b spots */
	for (int i = 0; i < width*height; i++) {
		(a + i)->r = rand() % (max_color + 1);
		(a + i)->g = rand() % (max_color + 1);
		(a + i)->b = rand() % (max_color + 1);
	}
	
	/* Returns a pointer to the array */
	return a;
}

/* Function which generates a population */
Individual *generate_population(int population_size, int width, int height, int max_color) {

	/* Creating and allocating space for a population_size 
	array of Individuals */
	Individual *a;
	a = malloc(sizeof(Individual[population_size]));

	/* Loops through population_size times and each time assigns a
	width, height, max_color, and array of PIXELS to the image at each
	point in the array */
	for (int i = 0; i < population_size; i++) {
		
		((a + i)->image).width = width;
		((a + i)->image).height = height;
		((a + i)->image).max_color = max_color;
		((a + i)->image).data = generate_random_image(width, height, max_color);
		
	}
	
	return a;
}
