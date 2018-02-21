# Lab 3

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/amaurilopez90/Operating-System-Work/master/LICENSE)

**Part 1:** Write a multithreaded program that calculates various statistical values for a list of numbers. This program will be passed a series of numbers on the command line and will then create three separate worker threads. One thread will determine the minimum value, the second will determine the maximum value, the third will determine the average value, the fourth will compute the standard deviation, and the fifth will compute the median value. 

For example, suppose your program is passed the integers: 94 80 65 95 20 70 9 

The program will report:
 
- Min = 9 
- Max = 95
- Average = 61.857143
- Standard Deviation = 31.809383
- Median = 70.000000

**Part 2:** An interesting way of calculating pi is to use a technique known as Monte Carlo, which involves randomization.

Write a multi-threaded version of this algorithm that creates a separate thread to generate a number of random points. The thread will count the number of points that occur within the circle and store that result in a global variable. When this thread has exited, the parent thread will calculate and output the estimated value of pi.

# How to Run

#### Linux:

1. Clone the source: `https://github.com/amaurilopez90/Operating-System-Work.git`
2. Go into the directory: `cd Operating-System-Work/Multithreading/Lab3`
3. Compile: `make`
4. Run: `./lab03_ex<num>` 
