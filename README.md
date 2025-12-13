## Project Structure

The project uses Git Branches to isolate different scheduler implementations. You must switch branches to test each algorithm. (main is the defualt RR scheduler I did nothing in it)

```bash
git branch
  fcfs
* main
  priority
  sfj
```

## Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/shabbann/xv7-riscv.git
cd xv7-riscv

```

### 2. Switch to a SchedulerTo test a specific algorithm, checkout its branch:

```bash
# Example: Switch to SJF
git checkout sjf

```

### 3. Build and RunAlways clean the build before running to ensure the new scheduler logic is compiled.

```bash
make clean
make qemu CPUS=1

```

**Note:** We use CPUS=1 to ensure easy visualization of the scheduling order without multi-core race conditions.

## testing

| Scheduler | Command | Expected Output |
| --- | --- | --- |
| FCFS | `spin` | parent will finish before child |
| Priority | `priority_test` | High Priority (Odd PID) interrupts and finishes before Low Priority (Even PID). |
| SJF | `vis` | Short jobs cut in line ahead of Long jobs, even if Long arrived first. |

**runing checkers:** Inside the xv6 shell ($), type the command:

```bash
$ vis

```

### Performance


1. The kernel will print statistics for each process upon exit:
```text
PID 6 | Algo: SJF | Burst: 12 | TAT: 15 Wait: 3

```

2. tou could also try runing benchmark to get some kind of a feeling of how multiple proc works
```bash
$ benchmark

```

### Kernel Modifications details* **struct proc (proc.h):** Added fields for `ctime` (creation time), `rtime` (run time), `tick_start` (burst start), and `avg_burst` (SJF prediction).
* **trap.c:** Modified `usertrap` and `kerneltrap` to track CPU usage (`rtime++`) and handle preemption (yield) selectively.
* **proc.c**:
    * `allocproc`: Initializes priority and burst history.
    * `scheduler`: Implements the specific selection loop (Min CTime, Min AvgBurst, or Max Priority).
    * `sched`: Calculates the exponential average for SJF prediction after every run

disclamier: while this project isn't vibe coded, LLMs have helped me in understanding and writing some codes in the process. especially the vis.c in sjf, where I had to find a way to communicate the processes together to build a viable test for the algorithm
