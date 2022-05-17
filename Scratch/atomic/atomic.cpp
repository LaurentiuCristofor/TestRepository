////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <sys/mman.h>

#include <chrono>
#include <climits>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void PrintDuration(
    pid_t pid,
    const time_point<steady_clock> startTime)
{
    cout
        << "Process " << pid << "'s operation lasted for "
        << fixed << setprecision(2)
        << duration<double, micro>(steady_clock::now() - startTime).count()
        << " μsec." << endl;
}

void IncrementWithFetchAndAdd(size_t* pValueToIncrement, size_t incrementValue)
{
    __sync_fetch_and_add(pValueToIncrement, incrementValue);
}

int IncrementWithCompareAndSwap(size_t* pValueToIncrement, size_t incrementValue)
{
    size_t valueToIncrement = *pValueToIncrement;
    size_t countRetries = 0;

    while (!__sync_bool_compare_and_swap(
        pValueToIncrement,
        valueToIncrement,
        valueToIncrement + incrementValue))
    {
        valueToIncrement = *pValueToIncrement;
        countRetries++;
    }

    return countRetries;
}

int main(int argc, char**argv)
{
    if (argc != 5)
    {
        cout << "Arguments:\n  <operation_type> <target_count> <increment_value> <process_count>" << endl;
        cout << "where <operation_type> can be either 'faa' or 'cas'." << endl;
        return 0;
    }

    string operationType = argv[1];
    size_t targetCount = strtoul(argv[2], nullptr, 10);
    size_t incrementValue = strtoul(argv[3], nullptr, 10);
    size_t processCount = strtoul(argv[4], nullptr, 10);

    if ((operationType != "faa" && operationType != "cas")
        || targetCount == 0 || targetCount == ULONG_MAX
        || incrementValue == 0 || incrementValue == ULONG_MAX
        || processCount == 0 || processCount == ULONG_MAX)
    {
        cout << "Invalid argument value!" << endl;
        return 1;
    }

    static size_t *pValueToIncrement;
    pValueToIncrement = reinterpret_cast<size_t*>(
        mmap(NULL, sizeof(size_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    // We now create processCount - 1 processes.
    pid_t pid;
    for (size_t i = 1; i < processCount; i++)
    {
        if ((pid = fork()) == 0)
        {
            break;
        }

        cout << "Forked process " << pid << "..." << endl;
    }

    pid = getpid();

    cout << "Process " << pid << " starts execution! valueToIncrement = " << *pValueToIncrement << " pValueToIncrement = " << pValueToIncrement << endl;

    size_t countOperations = 0;

    if (operationType == "faa")
    {
        time_point<steady_clock> startTime = steady_clock::now();

        while (*pValueToIncrement < targetCount)
        {
            IncrementWithFetchAndAdd(pValueToIncrement, incrementValue);
            countOperations++;
        }

        PrintDuration(pid, startTime);
    }
    else if (operationType == "cas")
    {
        size_t countRetries = 0;

        time_point<steady_clock> startTime = steady_clock::now();

        while (*pValueToIncrement < targetCount)
        {
            countRetries += IncrementWithCompareAndSwap(pValueToIncrement, incrementValue);
            countOperations++;
        }

        PrintDuration(pid, startTime);

        cout << "Process " << pid << " performed " << countRetries << " retries!" << endl;
    }

    cout << "Process " << pid << " performed " << countOperations << " operations and completed execution with valueToIncrement set at " << *pValueToIncrement << "." << endl;

    return 0;
}
