# Project 2

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/amaurilopez90/Operating-System-Work/master/LICENSE)

# Task Description:
Your program should be implemented in C language, run on Linux machines, and should use pthread (POSIX) library. 
Given 84 data files in CSV format (comma seperate data; each line contains a record in the dataset and a record contains multiple attributes
of the recrod seperate by comma), your tasks are the following:

1. Find the total number of unique words among all non-numeric string literals in each file
2. Find maximum, minimum, average, and variance of lengths of alphanumeric strings in each file, exclude pure numbers (either integer or floating-point values)
3. Count ratio of missing or zero values in each file. Also, find maximum, minimum, and average of the number of rows and columns of all files

# Important to Note:
The work loads are not the same for Task1, 2 and 3. **Each task should be handled by a seperate thread.** The overall goal is
be able to develop your application so that it can complete these tasks as balanced as possible. You can assume that you have hardware capable of doing mulitple tasks in parallel. 

# Requirements:
1. Program should be able to offer a command line option such as **./main single 1** that runs the application in single-thread mode, and performs the first task. This way, you can show that the implementation of each task is correct, regardless of multi-threading. 
2. Yield the same result in multo-threaded mode ran as **./main multi** all tasks will run.
3. Support different scheduling algorthims for the worker threads. Pthread library supports two options: **FIFO** and **RR**. Provide a command line option to demonstrate this such as: **./main multi sched RR** or **./main multi sched FIFO**
4. Your program must provide a measure (e.g., total elasped time) at the end to see the difference between schedulers. It is possible that there will be no significant differences. 
5. Support a priority setting for your program. The user should be able to set  the priority of one task higher or lower than the other. For example, provide a command line argument as follows: **./main multi priority 1 low** will set the priority of task 1 lower than the others, and because of this, the user might see that taks 1 completed after the other three were finished - **high** option for other case. 

# Acknowledgement of Data:
analcatdata - A collection of data sets used in the book "Analyzing Categorical Data," by Jeffrey S. Simonoff, Springer-Verlag, New York, 2003. The submission consists of a zip file containing two version of each of 84 datasets. Each file is given in comma-delimited ASCII (.csv) form, and Microsoft Excel (.xls) form. Further details concerning the book, including information on statistical software are available at the website: http://www.stern.nyu.edu/~jsimonof/AnalCatData

# How to Run

#### Linux:

1. Clone the source: `https://github.com/amaurilopez90/Operating-System-Work.git`
2. Go into the directory: `cd Operating-System-Work/Multithreading/project2`
3. Compile: `make`
4. Run: `see above examples of runnable commands` 
