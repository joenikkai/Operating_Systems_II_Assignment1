# operaring systems II assignment 1

This is an assignment to BCT-222 Y1 S2 students given in [Multimedia University of Kenya](https://mmu.ac.ke)

> [Make a program in your desired language illustrating shotest job first preemptive. Work in groups](./docs/pdf/Group%20Assignment.pdf)


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
The maximum burst time is going to be 4 minutes 15 seconds.
We will use `uint8_t` from `stdint.h` a one byte integer.

our job structure will be.

```c
struct Job {
    uint8_t burst;
    uint8_t e_code;
    char* e_msg;
};
```

We will use the GNU readline library to get user input.

## REPL

This is how our loop looks like

![REPL demonstration Image](./docs/media/picture.png)

## data flow diagram

```mermaid
flowchart
    alpha([Start])
    alpha --> step1[/Dummy booting sequence/] --> step2
    step2[\user input\] --> exit_check{\ has quit? \}
    exit_check -..->|True|omega
    exit_check -->|False|job_space_check{\Enough Job Space Left?\} -.If true.-> proccess
    job_space_check -.Throw error if false.->step2
    proccess -->step2
    omega([End])
```


## Proccess illustration 

```mermaid
flowchart 
    ProcessBegin --> check_exec

    check_exec --True--> In_Bucket
    check_exec --False--> cpu_exec

    cpu_exec --> get_shortest

    In_Bucket --> get_shortest
    Suspended_Bucket --> take_unfinished_jobs 

    take_unfinished_jobs --> get_shortest

    get_shortest --> check_shortest

    check_shortest -.if The current job is not the shortest job.-> Suspended_Bucket
    check_shortest -.if The current job is the shortest job.-> check_return

    check_return --If the process can still be executed--> cpu_exec
    check_return --If the process has returned--> register

    register --> ProcessReturn

    %% --- %%
    ProcessBegin([From enough job space left check])

    %% Buckets
    In_Bucket[RAM BUCKET] 
    %% This bucket is for incoming jobs
    Suspended_Bucket[CACHE BUCKET] 
    %% this is for waiting jobs
    register[record job burst time and exit time] 
    %% this is for completed jobs
    cpu_exec[execute for given time quanta] 
    %% This is basically a wait clock but we will call it a cpu for illustration

    check_exec{check if there is a currently executing process}
    %% @deprecated check_new{ Check if there is a new process that has arrived}
    check_return{ Has the current job returned? (zero burst time)}
    
    get_shortest[Get the shortest]

    check_shortest{Is the shortest Job the current job?}

    take_unfinished_jobs[\Take in the unfinished jobs\] 
    ProcessReturn([to User input or generate report])

```
