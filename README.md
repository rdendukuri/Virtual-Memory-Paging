# Virtual-Memory-Paging

See the sample output for usage

We will simulate the decisions made in page replacement using the 
"First-In-First-Out" (FIFO) and "Least-Recently-Used" (LRU) algorithms. 
The premise is that we have an operating system that uses virtual memory. 
We will assume that the process (code and data) is made up of N pages, and that the system has available K pages, where N > K > 0.
As not all pages can be in memory at one time, there may be times we need to replace a page.  The question is which page to replace.

Input File
data6.txt

The data in the input file is in pairs of lines.  The first line 
contains a letter X, followed by two small positive integers N and K.  
The second line contains a sequence of integers in the range 0 to 
N-1.

Here:
   X = 'F' for "FIFO" or 'L' for "LRU"
   N = the number of pages belonging to a process 
   K = the number of frames available for use

The numbers on the second line are page numbers for the pages the process needs as it executes.  When you find the value -1, the process terminates.

You may assume the letter is always either 'F' or 'L'.

You may assume N is never more than 12 and K is between 2 and 8.

You may assume the second line contains 20 values, ending with a succession of -1s.

The file ends with two lines marked '?', 0s and -1s.  These are present as a delimiter.  
