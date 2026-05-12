# operaring systems II assignment 1

This is an assignment to BCT-222 Y1 S2 students given in [Multimedia University of Kenya](https://mmu.ac.ke)

> Make a program in your desired language illustrating shotest job first preemptive. Work in groups


## The implementation plan

We are going to use the C programming language.
We are going to use arrays of pointers to store retrieve and execute a job.
We are going to use the `time.h` library to track time.
We are going to quatify time in seconds.
We are going to use user input as our set.
We are going to represent user input in the format below.
```
$ > 9  "Execution of write file syscall"  0
    ^          ^                          ^
    |          |                          |
    |          |                          This is the exitcode of the thread
    |          This is what to print after a job has been executed
    This is the burst time if the job in seconds
```
We are going to use regex as our regular expression matching algoritm.

The maximmum number of jobs we can have in a specific time will be 255.
The maximum wait time is going to be 4 minutes 15 seconds.
We will use `uint8_t` from `stdint.h` a one byte integer.

our job structure will be.

```c
struct Job {
    uint8_t wait;
    uint8_t e_code;
    char* e_msg;
};
```

We will use the GNU readline library to get user input.