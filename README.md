*This activity has been created as part of the 42 curriculum by bkuntz*

## Description

This activity is about creating a scheduler for coders, they can either compile, debug or refactor.
To compile, a coder need two dongles. Each dongle is associated to a coder and a coder can only take the dongle on his left and rigth. 

Each action have a given duration, wich cannot be changed. Given that each coders have a burnout time, if a coder don't compile during a duration equal to the burnout time, the script should stop. The script will stop if every coders does compile a given numbers of time. 
## Instructions

To make things easier a Makefile was made:

| Command   | Utility                                                               |
| --------- | --------------------------------------------------------------------- |
| build     | will build the executable with all dependencies                       |
| all       | default command, will run the build command                           |
| run       | will build the executable and run the script                          |
| run_error | will build the executable and run and will triger an error            |
| debug     | will build the executable and lauch the executable inside debug mode  |
| norm      | will lauch the norminette on the folder                               |
| threads   | will build the executable and run valgrind to check for thread sanity |
## Ressources

No website were used however, AI was use in some cases: recherches, debugging and the README.


## Blocking Cases Handled

During the development of **Codexion**, several critical concurrency issues and edge cases were identified and successfully resolved to ensure the simulation remains stable, robust, and free of undefined behavior:

**Deadlocks (Mutual Exclusion Blocking):** 
Resolved cyclic dependency risks during resource acquisition (e.g., trying to lock multiple mutexes out of order) by enforcing a strict deterministic locking order. Fixed self-deadlocks where threads attempted to re-acquire mutexes they already held.
 
**Data Races:**
Eliminated race conditions detected by Helgrind by ensuring all shared data access (e.g., updating the queue via `move_to_last`, checking states, or updating compile times) is strictly protected by the central `thread_lock`.

**Phantom Logs (In-flight Execution):**
Fixed the issue where delayed threads would print state changes (like "is debugging") after another developer had already triggered a burnout. Implemented a centralized, thread-safe `print_status` function that evaluates the simulation state (`keep_running` flag) atomically before logging to `stdout`.

**Simultaneous Burnouts:**
Prevented the monitoring thread from flooding the terminal with multiple burnout logs during the same tick. The monitoring routine now atomically flags `keep_running` to `0` on the first detected burnout, instantly halting further evaluation and keeping the output clean.

**Memory Leaks:**
Ensured a clean shutdown process regardless of how the simulation ends (completion or burnout). `pthread_mutex_destroy` and `pthread_cond_destroy` are rigorously called for all dongles and central thread locks, and all heap-allocated structures are freed.


## Thread Synchronization Mechanism

To orchestrate the developers and ensure strict compliance with scheduling policies (FIFO/EDF), **Codexion** relies on a robust combination of POSIX threads and atomic operations:

**Central Thread Lock (`pthread_mutex_t`):**
A shared mutex protects the developer queue and individual state variables. Any modification to a developer's state (compiling, debugging, refactoring) or position in the scheduling queue is performed under this lock.

**Dongle Mutexes:**
Each developer has an individual dongle protected by its own mutex. To compile, a developer must acquire their neighbors' dongle. To prevent some deadlocks, locks are always acquired in numerical order based on developer IDs.

**Condition Variables (`pthread_cond_t`):**
Used to manage waiting developers efficiently. Instead of active polling (spinning), developers blocked from compiling wait on a condition variable. When dongles are released, `pthread_cond_signal` wakes the appropriate threads to re-evaluate their turn.

**Atomic Operations (`<stdatomic.h>`):**
The global simulation state (`keep_running`) is managed using `atomic_int`. This provides non-blocking, thread-safe state checks across all threads, guaranteeing immediate visibility when the monitoring thread halts the simulation due to a burnout or completion, without the overhead of acquiring the main mutex.

**Monitoring Thread:**
A dedicated overseer thread continuously polls the `last_compile_time` of all developers. If it detects a starvation period exceeding `time_to_burnout`, it atomically halts the simulation and triggers the end sequence.