# Lab 10
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/amaurilopez90/Operating-System-Work/master/LICENSE)

# Task Description:
You must write a program that implements the following disk-scheduling alorithms:
1. First-Come-First-Served (FCFS)
2. Shortest-Seek-Time-First (SSTF)
3. SCAN
4. C-SCAN
5. LOOK
6. C-LOOK 

Your program needs to read input.txt in the same directory and write output.txt, also in the same directory. The format of an example input.txt file can be seen below:

  ![input](https://github.com/amaurilopez90/Operating-System-Work/blob/master/Scheduling/Mass Storage/OSlab10.JPG)
  
Following this example means that you will service a disk with 5,000 cylinders numbered from 0 to 4,900. Your program will get a series of 1,000 cylinder requests listed starting from the third line of the file. The last line is the initial position of the disk head. 

# Goal:
Report the total amount of head movements required by each algorithm. It shoud report in this order, line-by-line: **FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK 


