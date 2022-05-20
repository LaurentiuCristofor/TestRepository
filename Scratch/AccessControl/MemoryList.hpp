////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MemoryStructures.hpp"

namespace LaurentiuCristofor
{

class CMemoryList
{
public:

    // Get the record data corresponding to an offset.
    ListNode* ReadRecord(size_t recordOffset) const;

    // Sets up two references for traversing the given list.
    // If list is empty, pCurrentRecord will be set to nullptr,
    // otherwise it will be set to the list's first node.
    void Start(ListNode* pListHead, IterationContext& context) const;

    // Basic iteration method over a ListNode list, using two references.
    // It ensures a safe traversal of the list in a multi-threaded context
    // in which other threads may insert or remove nodes from the list.
    //
    // Returns true if a next node was found and false if we reached the end of the list.
    bool MoveNext(IterationContext& context) const;

    // In some situations, we need to reset the current node
    // and advance it again from the previous node.
    void ResetCurrent(IterationContext& context) const;

    // Attempts to lock the wanted access on the previous record.
    //
    // If access is locked but the link between the previous record and the next is broken,
    // the lock will be reverted and we'll fail the call.
    //
    // An access mark (a read mark) on a node just ensures that whatever its 'next' link points to
    // is still part of our list, but does not prevent that link from changing.
    // An access lock ensures that the 'next' link cannot be changed by another thread.
    //
    // For Insert/Update, we only need to acquire a lock on pPreviousRecord, to "freeze its next link".
    // For Delete, we need to acquire locks on both pPreviousRecord and pCurrentRecord,
    // because the operation impacts two links.
    //
    // Returns true if access was acquired and false otherwise.
    bool TryToLockAccess(IterationContext& context, EAccessLockType wantedAccess, EAccessLockType& existingAccess) const;

    bool TryToLockAccess(IterationContext& context, EAccessLockType wantedAccess) const;

    // Removes the current record from the list.
    // Assumes that both records have already had their access locked.
    // This method will avoid ABA issues by delaying its completion
    // until all readers have moved past the current record.
    // This and the held locks ensure that the next link of the current node
    // is safe to pursue and still points to a node in our list.
    void Remove(IterationContext& context) const;

    // Inserts a record after the previous record specified in the context.
    // Safety of this operation also relies on the calling party
    // locking access to the record after which we insert.
    void Insert(IterationContext& context, ListNode*& pRecord) const;

    // Inserts a memory record in order.
    void InsertListNode(ListNode* pListHead, ListNode* pRecord) const;

protected:

    // Helper function that attempts to advance the current record past the previous one.
    //
    // Returns true if it succeeds and false otherwise.
    bool TryToAdvanceCurrentRecord(IterationContext& context) const;

    void SearchUpdateExample();
    void RemovalExample();
    void InsertionExample();
};

} // LaurentiuCristofor
