/* 
	Programmed by: 
	Joshua Guinness
	November 24/25, 2018
	for the purpose of completing Assignment 4 for 2SO3
*/

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

/* Prototype for fopen */
FILE *fopen(const char * restrict file_name, const char * restrict mode);

/* Function to open a PPM file and read it */
PPM_IMAGE *read_ppm(const char *file_name) {

	/* Creates a pointer to a PPM_IMAGE struct then allocates
	memory for it*/
	PPM_IMAGE *p;
	p = malloc(sizeof(PPM_IMAGE));

	FILE *file = fopen(file_name, "r"); /* Opens the file */

	/* Checks to see if the could not open the file */
	if (file == NULL) {
		printf("Can't open\n" );
		exit(EXIT_FAILURE);
	}

	/* Reads in the width, height, and max color which are
	located at the top of the file, ignoring the P3.
	Stores the three values  */

	/* The following 6 lines of code are based off of code found
	at https://www.geeksforgeeks.org/scanf-and-fscanf-in-c-simple-yet-poweful/ and
	http://support.sas.com/documentation/onlinedoc/sasc/doc700/html/lr1/z2055208.htm */
	
	int width, height, max;
	while (fscanf(file, "P3 %d %d %d", &width, &height, &max) == 3) {
		p->width = width;
		p->height = height;
		p->max_color = max;
	}

	/* Create a PIXEL array with size width x height */
	PIXEL *a;
	a = malloc(sizeof(PIXEL[width*height]));

	/* Scans all the rgb values and places them within an array
	of PIXEL structures */
	int l, m, n;
	int i = 0;
	while (fscanf(file, "%d %d %d", &l, &m, &n) == 3) {
		//printf("Ith value %d: %d %d %d\n", i+1, l, m, n);
		(a + i)->r = l;
		(a + i)->g = m;
		(a + i)->b = n;
		i = i + 1;
	}

	/* Assigns the data pointer to be the array */
	p->data = a;

	/* Closes the file */
	fclose(file);

	/* Returns the pointer to the structure */
	return p;
}

/* Function which outputs to a textfile */
void write_ppm(const char *file_name, const PPM_IMAGE *image) {
	
	//PIXEL array = image->data;
	/* Get the width and height of the image */
	int width = image->width;
	int height = image->height;
	int max = image->max_color;

	/* Open the file, add the P3 and the width, height 
	at max color at the top */
	FILE *file = fopen(file_name, "w");
	fprintf(file, "P3\n");
	fprintf(file, "%d %d\n", width, height);
	fprintf(file, "%d\n", max);
	
	/* Iterates through each member of the array outputting it to 
	the text file with a new line after each row as determined
	by the width */
	for (int i = 1; i < width*height +1; i++) {
		fprintf(file, "%d %d %d ", (image->data + i - 1)->r, (image->data + i - 1)->g, (image->data + i - 1)->b);

		if (width % i == 0) {
			fprintf(file, "\n");
		}
	}
	
	/* Closes the file */
	fclose(file);
}
