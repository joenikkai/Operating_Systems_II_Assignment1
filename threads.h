#if !defined(THREADS_H)
#define THREADS_H

/**
 * constantly update window size.
 * manage the 3 buckets
 * - programs that have already run
 * - program that have been suspended
 * - programs that are incoming
 * The program that is currently running does not need a bucket because it is already in the VM's CPU
*/

#endif // THREADS_H