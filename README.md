# MapReduce Framework with Thread Pool Architecture

A good-performance, thread-safe MapReduce framework implementation in C featuring a custom thread pool architecture, dynamic memory management, and efficient data partitioning. This implementation demonstrates advanced systems programming concepts including parallel processing, synchronization primitives, and scalable data processing patterns.

## Table of Contents

- [MapReduce Framework with Thread Pool Architecture](#mapreduce-framework-with-thread-pool-architecture)
  - [Table of Contents](#table-of-contents)
  - [Key Features](#key-features)
    - [Core Architecture](#core-architecture)
    - [Advanced Capabilities](#advanced-capabilities)
  - [Project Architecture](#project-architecture)
  - [Technical Implementation](#technical-implementation)
    - [Thread Pool Architecture](#thread-pool-architecture)
    - [Data Partitioning System](#data-partitioning-system)
    - [Hash-Based Partitioning](#hash-based-partitioning)
  - [Prerequisites](#prerequisites)
  - [Installation \& Build](#installation--build)
    - [Clone and Build](#clone-and-build)
  - [MapReduce Operations](#mapreduce-operations)
    - [1. Word Count (`wordcount`)](#1-word-count-wordcount)
    - [2. Department Maximum (`departmax`)](#2-department-maximum-departmax)
    - [3. Number Sum (`numbersum`)](#3-number-sum-numbersum)
    - [4. Average Calculation (`average`)](#4-average-calculation-average)
  - [Performance Characteristics](#performance-characteristics)
    - [Scalability Features](#scalability-features)
    - [Threading Configuration](#threading-configuration)
    - [Thread Safety Guarantees](#thread-safety-guarantees)
  - [System Architecture](#system-architecture)
    - [Data Flow Pipeline](#data-flow-pipeline)
    - [Execution Phases](#execution-phases)
    - [Memory Management Strategy](#memory-management-strategy)
  - [Contributing](#contributing)
    - [Development Guidelines](#development-guidelines)
    - [Adding New Operations](#adding-new-operations)
  - [Technical References](#technical-references)

## Key Features

### Core Architecture
- **Custom Thread Pool Implementation**: Efficient worker thread management with condition variables and mutex synchronization
- **Thread-Safe Data Structures**: Concurrent access to partitions and task queues with proper locking mechanisms  
- **Dynamic Memory Management**: Automatic partition resizing and proper memory cleanup
- **Hash-Based Partitioning**: Efficient data distribution using djb2 hash algorithm for load balancing

### Advanced Capabilities
- **Multiple MapReduce Operations**: Word counting, numerical aggregation, maximum finding, and statistical analysis
- **Configurable Parallelism**: Separate thread pools for map and reduce phases with customizable thread counts
- **Scalable Data Processing**: Dynamic partition growth to handle large datasets

## Project Architecture

```
Map-Reduce/
├── include/                    # Header files
│   ├── mr_sys.h               # Core MapReduce system interface
│   ├── thread_pool.h          # Thread pool management
│   ├── partition.h            # Data partitioning with thread safety
│   ├── pair.h                 # Key-value pair operations
│   ├── mappers.h              # Mapper function declarations
│   └── reducers.h             # Reducer function declarations
├── src/                       # Implementation files
│   ├── mr_sys.c               # Core MapReduce orchestration
│   ├── thread_pool.c          # Thread pool with worker management
│   ├── partition.c            # Thread-safe partition operations
│   ├── pair.c                 # Key-value pair management
│   ├── mappers.c              # Map phase implementations
│   └── reducers.c             # Reduce phase implementations
├── samples/                   # Test datasets
│   ├── word_count_*.txt       # Word frequency analysis data
│   ├── department_max_*.txt   # Department performance data
│   ├── numbers_sum.txt        # Numerical aggregation data
│   └── averages.txt           # Statistical analysis data
├── main.c                     # Application entry point
├── test_all_operations.sh     # Automated testing suite
└── CMakeLists.txt            # Build configuration
```

## Technical Implementation

### Thread Pool Architecture

The framework implements a sophisticated thread pool system:

```c
struct threads_pool {
    int num_threads;           // Configurable thread count
    int shutdown;              // Graceful shutdown flag
    pthread_t *threads;        // Worker thread array
    struct task_queue task_queue;  // Thread-safe task queue
    pthread_mutex_t lock;      // Pool synchronization
    pthread_cond_t not_empty;  // Task availability signal
};
```

**Key Features:**
- **Worker Thread Management**: Pre-allocated threads with condition variable synchronization
- **Task Queue**: Thread-safe FIFO queue with mutex protection
- **Graceful Shutdown**: Proper thread joining and resource cleanup
- **Dynamic Task Distribution**: Automatic load balancing across worker threads

### Data Partitioning System

Thread-safe partitions with dynamic resizing:

```c
struct partition {
    pthread_mutex_t lock;      // Partition-level synchronization
    int next;                  // Iterator for reduce phase
    int size;                  // Current number of pairs
    int capacity;              // Current allocated capacity
    struct pair *pairs;        // Dynamic key-value array
};
```

**Advanced Features:**
- **Dynamic Growth**: Automatic capacity doubling when needed
- **Thread Safety**: Per-partition mutex for concurrent access
- **Efficient Sorting**: Insertion sort for reduce phase preparation
- **Memory Management**: Proper allocation and deallocation

### Hash-Based Partitioning

Uses the djb2 hash algorithm for optimal data distribution:

```c
int MR_DefaultHashPartition(char *key, int num_partitions) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++) != '\0') {
        hash = hash * 33 + c;
    }
    return hash % num_partitions;
}
```

## Prerequisites

- **CMake** (≥ 3.10)
- **GCC** with C99 support
- **POSIX threads** (pthread)
- **Linux/Unix** environment

## Installation & Build

### Clone and Build

```bash
git clone https://github.com/Islam-Imad/Map-Reduce.git
cd Map-Reduce
mkdir build && cd build
cmake ..
make
```

This generates the `MapReduce` executable with full thread pool support.

## MapReduce Operations

### 1. Word Count (`wordcount`)
**Purpose**: Parallel word frequency analysis across multiple files

**Algorithm**:
- **Map Phase**: Tokenize input files and emit (word, 1) pairs
- **Partition Phase**: Distribute words across partitions using hash function
- **Reduce Phase**: Aggregate counts for each unique word

**Usage**:
```bash
./MapReduce wordcount samples/word_count_1.txt samples/word_count_2.txt samples/word_count_3.txt
```

### 2. Department Maximum (`departmax`)
**Purpose**: Find maximum performance values per department

**Algorithm**:
- **Map Phase**: Parse department-value pairs from input files
- **Partition Phase**: Group values by department name
- **Reduce Phase**: Find maximum value for each department

**Usage**:
```bash
./MapReduce departmax samples/department_max_1.txt samples/department_max_2.txt samples/department_max_3.txt
```

### 3. Number Sum (`numbersum`)
**Purpose**: Parallel summation of all numeric values

**Usage**:
```bash
./MapReduce numbersum samples/numbers_sum.txt
```

### 4. Average Calculation (`average`)
**Purpose**: Statistical analysis with mean and count calculation

**Usage**:
```bash
./MapReduce average samples/averages.txt
```

## Performance Characteristics

### Scalability Features
- **Parallel Map Phase**: Multiple files processed concurrently
- **Parallel Reduce Phase**: Partitions processed in parallel
- **Configurable Threads**: Tune mapper/reducer thread counts for optimal performance
- **Memory Efficiency**: Dynamic allocation prevents memory waste

### Threading Configuration
```c
// Example: 4 partitions, 2 mapper threads, 3 reducer threads
init_MapReduceSystem(&mr_sys, mapper_func, reducer_func, 
                     MR_DefaultHashPartition, 4, 2, 3);
```

### Thread Safety Guarantees
- **Partition Access**: Per-partition mutexes prevent race conditions
- **Task Queue**: Thread-safe enqueue/dequeue operations
- **Memory Management**: Proper synchronization during dynamic resizing
- **Resource Cleanup**: Deadlock-free shutdown procedures

## System Architecture

### Data Flow Pipeline
```
Input Files → Thread Pool (Mappers) → Hash Partitioner → Thread Pool (Reducers) → Results
     ↓              ↓                        ↓                    ↓              ↓
  File I/O    Parallel Parsing        Load Balancing      Parallel Aggregation  Output
```

### Execution Phases

1. **Initialization Phase**
   - Create and configure MapReduce system
   - Initialize thread pools for map and reduce phases
   - Allocate partitions with initial capacity

2. **Map Phase**
   - Distribute input files across mapper threads
   - Each mapper processes assigned files independently
   - Key-value pairs distributed to partitions via hash function

3. **Synchronization Point**
   - Wait for all mapper threads to complete
   - Shutdown mapper thread pool

4. **Reduce Phase**
   - Sort each partition by key for efficient processing
   - Distribute partitions across reducer threads
   - Each reducer processes assigned partitions independently

5. **Cleanup Phase**
   - Wait for all reducer threads to complete
   - Clean up all allocated resources

### Memory Management Strategy
- **Dynamic Partitions**: Start with small capacity, grow as needed
- **String Duplication**: Safe copying of keys and values
- **Proper Cleanup**: Comprehensive deallocation in destroy functions
- **Thread-Safe Operations**: Mutex protection during memory operations

## Contributing

### Development Guidelines
1. **Thread Safety**: All new data structures must be thread-safe
2. **Memory Management**: Implement proper allocation/deallocation pairs
3. **Error Handling**: Add appropriate error checking and cleanup
4. **Testing**: Include test cases for new functionality

### Adding New Operations
1. **Implement Mapper**: Add function to `src/mappers.c`
2. **Implement Reducer**: Add function to `src/reducers.c`
3. **Update Headers**: Declare functions in respective header files
4. **Extend Main**: Add operation case to `main.c`
5. **Create Test Data**: Add sample files and update test script

## Technical References

- **MapReduce Paper**: [Dean & Ghemawat, OSDI 2004](https://research.google.com/archive/mapreduce.html)
- **POSIX Threads**: [IEEE Std 1003.1-2017](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)
- **djb2 Hash Algorithm**: [Daniel J. Bernstein](http://www.cse.yorku.ca/~oz/hash.html)
- **Thread Pool Pattern**: [Schmidt et al., Pattern-Oriented Software Architecture](https://www.dre.vanderbilt.edu/~schmidt/POSA/)

---

*This implementation showcases advanced C programming techniques including thread management, synchronization primitives, dynamic memory allocation, and scalable system design. Perfect for educational purposes and real-world data processing applications.*
