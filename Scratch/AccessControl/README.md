# AccessControl

This code was written to help manage lists stores in shared memory that could be accessed (and updated) by multiple processes.

As this problem requires synchronization across processes, standard mutexes could not be used.

`AccessControl` introduces a simple structure that can be used to synchronize operations.

`MemoryList` and `MemoryStructures` show how the structure can be used to help operate on lists and provide an API for list operations.

`Assert` and `AssertionFailure` are general-purpose asserting functions.

The MemoryList code has only been lightly tested and has no unit tests so it might have significant bugs in it. As in many situations, the requirements changed and I no longer needed to support concurrent multi-process access to data structures, so this code got abandoned. However, it does attempt to address a difficult problem and I might reuse it at some point if I'll ever need to attempt to solve such a problem again. At that point, I'll probably add more extensive documentation as well.

## Design Notes

The nodes of the lists are supposed to never get deleted. Removed nodes are meant to be inserted into lists from which they can be extracted again when needed, instead of allocating new ones. This simplifies synchronization because now we only need to be concerned about whether the nodes have been moved around lists or if their data was updated.

Lists also have a "dummy" head node that doesn't contain any data and is immutable for each list. That provides stability for starting a list iteration.

List iteration is performed using an iteration context that basically marks both the previous and current nodes as being read, to prevent concurrent processes from moving them into different lists (so that you'd start iterating in a list and end up in another). As the iteration moves forward, read access is released from the previous node and marked on the next one, while always keeping at least one node marked at any time. List updates require locks to be taken that state the update intent - the intent is used by other processes to understand the nature of the update. Updaters that remove a node from a list will wait for all readers to move away from the node before inserting it into another list.

At some point, I would rewrite this code to use std::atomic variables.

The original code computed memory addresses from offsets and a base memory address - the base memory address has been dropped out from this code, but it would need to be added back for practical use, because different processes would see the same region of memory mapped at different addresses.
