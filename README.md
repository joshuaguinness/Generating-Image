# Generating-Image

This was the final assignment for my 2SO3 - Principles of Programming class. In this class we focused on programming in C, as well as basic data structure and algorithms.

In this assignment, we had to use a genetic algorithm to produce an image that is the closest fit to a goal image. The way the algorithm works is that it creates a population of images where the pixels are randomized. It then calculates the fitness for each individual in the population and sorts them from lowest to higher (lowest in this case being the best). It then mutates the bottom 75% of images by randomizing a certain number of pixels. It then re-sorts them according the fitness and the process continues. 

After a certain number of generations, the image with the lowest fitness is the one outputed to a new .ppm file.

The algorithm I used, specifically seen in the evolve.c file, starts with a higher rate, which then decreases as the number of generations increases. This makes it so that more pixels are mutated at the beginning, but less later on. This is done so that a lower fitness is reached quicker at the beginning, and after many generations, only a few pixels are mutated so that there is a higher chance of improving.

The images produced by the genetic algorithm, and the goal images are seen below.  

![testing](https://github.com/joshuaguinness/Generating-Image/blob/master/me2.jpg)

## What I Learned

## To Run

To run with the bird photo, type "make escher." To run with the McMaster logo type "make mcmaster."

To clean type "make clean"
