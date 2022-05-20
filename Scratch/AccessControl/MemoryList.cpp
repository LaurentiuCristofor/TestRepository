////////////////////////////////////////////////////////////////////////////////////////////////////
/// (c) Laurentiu Cristofor
/// This file is made available under the MIT license.
/// Do not use it if you have not received an associated LICENSE file.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>

#include "Assert.hpp"
#include "MemoryList.hpp"

using namespace LaurentiuCristofor;

ListNode* CMemoryList::ReadRecord(size_t recordOffset) const
{
    ListNode* pRecord = reinterpret_cast<ListNode*>(recordOffset);

    return pRecord;
}

bool CMemoryList::TryToAdvanceCurrentRecord(IterationContext& context) const
{
    ASSERT(context.pPreviousRecord != nullptr, "Previous record cannot be null!");

    size_t currentRecordOffset = context.pPreviousRecord->next;

    if (currentRecordOffset == 0)
    {
        context.pCurrentRecord = nullptr;
        context.autoAccessCurrentRecord.ReleaseAccess();

        return true;
    }

    context.pCurrentRecord = ReadRecord(currentRecordOffset);
    context.autoAccessCurrentRecord.MarkAccess(&context.pCurrentRecord->accessControl);

    // Now that we marked our access, we need to check
    // whether pCurrentRecord still belongs in our list,
    // because another thread may have removed it
    // before we got to mark our access.
    if (context.pPreviousRecord->next == currentRecordOffset)
    {
        // All looks good, so we're done here.
        return true;
    }

    // We failed, so we should release the access that we marked.
    context.autoAccessCurrentRecord.ReleaseAccess();

    return false;
}

void CMemoryList::Start(ListNode* pListHead, IterationContext& context) const
{
    ASSERT(pListHead != nullptr, "Null list head was passed to CMemoryList::Start()!");

    context.pPreviousRecord = pListHead;
    context.autoAccessPreviousRecord.MarkAccess(&context.pPreviousRecord->accessControl);

    // Keep trying to advance current record until we succeed.
    while (!TryToAdvanceCurrentRecord(context))
    {
    }
}

bool CMemoryList::MoveNext(IterationContext& context) const
{
    ASSERT(context.pPreviousRecord != nullptr, "Previous record cannot be null!");
    ASSERT(context.autoAccessPreviousRecord.HasMarkedAccess(), "Access to previous record has not been marked yet!");

    if (context.pCurrentRecord == nullptr)
    {
        return false;
    }

    ASSERT(context.autoAccessCurrentRecord.HasMarkedAccess(), "Access to current record has not been marked yet!");

    // Advance previous reference first, so that we maintain the access mark on the current one.
    // This ensures (due to how record removal is implemented)
    // that the current record cannot be fully removed from the list,
    // so we can use its next link to continue the traversal.
    context.pPreviousRecord = context.pCurrentRecord;
    context.autoAccessPreviousRecord.MarkAccess(&context.pPreviousRecord->accessControl);

    // Keep trying to advance current record until we succeed.
    while (!TryToAdvanceCurrentRecord(context))
    {
    }

    // Return whether we have found one more record or the end of the list.
    return (context.pCurrentRecord != nullptr);
}

void CMemoryList::ResetCurrent(IterationContext& context) const
{
    ASSERT(context.pPreviousRecord != nullptr, "Previous record cannot be null!");
    ASSERT(context.autoAccessPreviousRecord.HasMarkedAccess(), "Access to previous record has not been marked yet!");
    ASSERT(context.autoAccessCurrentRecord.HasMarkedAccess(), "Access to current record has not been marked yet!");

    context.autoAccessCurrentRecord.ReleaseAccess();

    // Keep trying to advance current record until we succeed.
    while (!TryToAdvanceCurrentRecord(context))
    {
    }
}

bool CMemoryList::TryToLockAccess(IterationContext& context, EAccessLockType wantedAccess, EAccessLockType& existingAccess) const
{
    ASSERT(wantedAccess != alt_Remove, "A Remove lock should never be taken on previous record - use UpdateRemove instead!");
    ASSERT(context.pPreviousRecord != nullptr, "Previous record cannot be null!");
    ASSERT(context.autoAccessPreviousRecord.HasMarkedAccess(), "Access to previous record has not been marked yet!");
    ASSERT(!context.autoAccessPreviousRecord.HasLockedAccess(), "Access to previous record has been locked already!");

    if (!context.autoAccessPreviousRecord.TryToLockAccess(wantedAccess, existingAccess))
    {
        return false;
    }

    // Operations other than Insert need to work with the current record,
    // so we need to check if the link between the two records still holds.
    // If the link is broken, there is no point in maintaining the lock further,
    // but we'll leave the access mark because that is managed by our caller.
    if (wantedAccess != alt_Insert
        && context.pCurrentRecord != ReadRecord(context.pPreviousRecord->next))
    {
        context.autoAccessPreviousRecord.ReleaseAccessLock();
        return false;
    }

    return true;
}

bool CMemoryList::TryToLockAccess(IterationContext& context, EAccessLockType wantedAccess) const
{
    EAccessLockType existingAccess;

    return TryToLockAccess(context, wantedAccess, existingAccess);
}

void CMemoryList::Remove(IterationContext& context) const
{
    ASSERT(context.pPreviousRecord != nullptr, "Previous record cannot be null!");
    ASSERT(context.pCurrentRecord != nullptr, "Current record cannot be null!");
    ASSERT(context.autoAccessPreviousRecord.HasLockedAccess(), "Access to previous record has not been locked yet!");
    ASSERT(context.autoAccessCurrentRecord.HasLockedAccess(), "Access to current record has not been locked yet!");
    ASSERT(
        context.pCurrentRecord == ReadRecord(context.pPreviousRecord->next),
        "Previous record pointer does not precede the current record pointer!");

    // Remove the current record from the list.
    context.pPreviousRecord->next = context.pCurrentRecord->next;

    // Wait for all other readers of the current record to move away from it.
    // No new readers can appear, because we removed the record from the list.
    // This wait, coupled with the lock maintained on the previous record,
    // guarantees that pCurrentRecord->next can be safely followed by any suspended readers.
    while (context.pCurrentRecord->accessControl.readersCount > 1)
    {
        // Give other threads a chance to release read marks.
        usleep(1);
    }

    // We can now suppress the outgoing link.
    context.pCurrentRecord->next = 0;

    // We're done! Release all access immediately.
    context.autoAccessPreviousRecord.ReleaseAccess();
    context.autoAccessCurrentRecord.ReleaseAccess();
}

void CMemoryList::Insert(IterationContext& context, ListNode*& pRecord) const
{
    ASSERT(context.pPreviousRecord != nullptr, "Record cannot be null!");
    ASSERT(context.autoAccessPreviousRecord.HasLockedAccess(), "Access to previous record has not been locked yet!");

    pRecord->next = context.pPreviousRecord->next;

    uint8_t* pRecordAddress = reinterpret_cast<uint8_t*>(pRecord);
    size_t recordOffset = reinterpret_cast<size_t>(pRecordAddress);

    context.pPreviousRecord->next = recordOffset;

    // We're done! Release all access immediately.
    context.autoAccessPreviousRecord.ReleaseAccess();
}

void CMemoryList::InsertListNode(ListNode* pListHead, ListNode* pListNode) const
{
    ASSERT(pListHead != nullptr, "Null list head was passed to InsertListNode()!");
    ASSERT(pListNode != nullptr, "InsertListNode() was called with a null parameter!");

    // We need an extra loop to restart the insertion from scratch in a special case.
    while (true)
    {
        IterationContext context;
        Start(pListHead, context);
        bool foundInsertionPlace = false;
        EAccessLockType existingAccess = alt_None;

        // Insert record in its proper place in the list,
        // based on any criteria around its payload value.
        // In this example, we just keep the list nodes ordered by their payload value.
        while (true)
        {
            // Check if this is the right place to insert our record.
            // If we reached the end of the list, then that is the right place.
            if (context.pCurrentRecord == nullptr
                || context.pCurrentRecord->payload > pListNode->payload)
            {
                foundInsertionPlace = true;

                if (TryToLockAccess(context, alt_Insert, existingAccess))
                {
                    Insert(context, pListNode);

                    // We're done!
                    return;
                }
                else if (existingAccess == alt_Remove)
                {
                    // We have to restart from the beginning of the list
                    // because our previous record is being deleted.
                    break;
                }
                else
                {
                    // Some other operation is taking place,
                    // so we'll have to re-examine if this is the right place to insert.
                    foundInsertionPlace = false;
                    usleep(1);
                    ResetCurrent(context);
                    continue;
                }
            }

            ASSERT(!foundInsertionPlace, "We should not reach this code if we already found the insertion place!");

            MoveNext(context);
        }
    }
}

void CMemoryList::SearchUpdateExample()
{
    constexpr size_t requestedPayload = 88;

    ListNode listHead;
    IterationContext context;
    Start(&listHead, context);

    // Iterate over a list and try to find a record from which to extract our requested payload.
    while (context.pCurrentRecord != nullptr)
    {
        if (context.pCurrentRecord->payload > requestedPayload)
        {
            // We have 2 situations: the record payload is exactly our required size or it is larger.
            //
            // In both situations, we need to check the size of the payload again after acquiring the locks,
            // because another thread may have managed to update it before we could lock it.
            if (context.pCurrentRecord->payload == requestedPayload)
            {
                if (TryToLockAccess(context, alt_UpdateRemove)
                    && context.autoAccessCurrentRecord.TryToLockAccess(alt_Remove)
                    && context.pCurrentRecord->payload == requestedPayload)
                {
                    ASSERT(
                        context.pCurrentRecord->payload == requestedPayload,
                        "Internal error - we are attempting to use a record whose payload is too small!");

                    // Jolly good! We've found a record of exactly the size that we were looking for.
                    // As it has our requested payload, it should be removed from the list.
                    Remove(context);

                    // context.pCurrentRecord is now referencing the removed node
                    // and that could now be inserted into another list.

                    break;
                }
            }
            else
            {
                if (TryToLockAccess(context, alt_Update)
                    && context.pCurrentRecord->payload > requestedPayload)
                {
                    ASSERT(
                        context.pCurrentRecord->payload > requestedPayload,
                        "Internal error - we are attempting to use a record whose payload is too small!");

                    // We have more payload than we needed, so update the record
                    // to track the remaining payload.
                    context.pCurrentRecord->payload -= requestedPayload;

                    break;
                }
            }
        }

        MoveNext(context);
    }
}

void CMemoryList::RemovalExample()
{
    ListNode listHead;
    IterationContext context;
    Start(&listHead, context);
    [[maybe_unused]] ListNode* pExtractedRecord = nullptr;

    // Iterate through a list of records and attempt to extract one.
    while (context.pCurrentRecord != nullptr)
    {
        // Retrieving a node from this list is going to be a small-effort initiative.
        // If we fail, we'll just allocate a new node, so eventually,
        // enough nodes will get inserted into this list that we'll succeed easily to remove one.
        //
        // We'll try to lock each node one after the other.
        if (TryToLockAccess(context, alt_UpdateRemove)
            && context.autoAccessCurrentRecord.TryToLockAccess(alt_Remove))
        {
            Remove(context);

            pExtractedRecord = context.pCurrentRecord;

            break;
        }

        MoveNext(context);
    }
}

void CMemoryList::InsertionExample()
{
    // Attempt to insert a node into a list.
    ListNode listHead;
    IterationContext context;
    Start(&listHead, context);
    ListNode* pRecord = nullptr;

    // We'll keep trying to insert at the beginning of the list.
    while (true)
    {
        if (TryToLockAccess(context, alt_Insert))
        {
            Insert(context, pRecord);

            return;
        }
    }
}
