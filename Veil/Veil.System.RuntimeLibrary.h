/*
 * PROJECT:   Veil
 * FILE:      Veil.h
 * PURPOSE:   Definition for the Windows Internal API from ntdll.dll,
 *            samlib.dll and winsta.dll
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: MiroKaku (50670906+MiroKaku@users.noreply.github.com)
 */

/*
 * PROJECT:   Mouri's Internal NT API Collections (MINT)
 * FILE:      MINT.h
 * PURPOSE:   Definition for the Windows Internal API from ntdll.dll,
 *            samlib.dll and winsta.dll
 *
 * LICENSE:   Relicensed under The MIT License from The CC BY 4.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

/*
 * This file is part of the Process Hacker project - https://processhacker.sf.io/
 *
 * You can redistribute this file and/or modify it under the terms of the
 * Attribution 4.0 International (CC BY 4.0) license.
 *
 * You must give appropriate credit, provide a link to the license, and
 * indicate if changes were made. You may do so in any reasonable manner, but
 * not in any way that suggests the licensor endorses you or your use.
 */

#pragma once

// Warnings which disabled for compiling
#if _MSC_VER >= 1200
#pragma warning(push)
// nonstandard extension used : nameless struct/union
#pragma warning(disable:4201)
// 'struct_name' : structure was padded due to __declspec(align())
#pragma warning(disable:4324)
// 'enumeration': a forward declaration of an unscoped enumeration must have an
// underlying type (int assumed)
#pragma warning(disable:4471)
#endif

VEIL_BEGIN()

//
// Helper
//

#ifndef _KERNEL_MODE

//++
//
// PCHAR
// RtlOffsetToPointer (
//     PVOID Base,
//     ULONG Offset
//     )
//
// Routine Description:
//
// This macro generates a pointer which points to the byte that is 'Offset'
// bytes beyond 'Base'. This is useful for referencing fields within
// self-relative data structures.
//
// Arguments:
//
//     Base - The address of the base of the structure.
//
//     Offset - An unsigned integer offset of the byte whose address is to
//         be generated.
//
// Return Value:
//
//     A PCHAR pointer to the byte that is 'Offset' bytes beyond 'Base'.
//
//
//--

#define RtlOffsetToPointer(B,O)  ((PCHAR)( ((PCHAR)(B)) + ((ULONG_PTR)(O))  ))


//++
//
// ULONG
// RtlPointerToOffset (
//     PVOID Base,
//     PVOID Pointer
//     )
//
// Routine Description:
//
// This macro calculates the offset from Base to Pointer.  This is useful
// for producing self-relative offsets for structures.
//
// Arguments:
//
//     Base - The address of the base of the structure.
//
//     Pointer - A pointer to a field, presumably within the structure
//         pointed to by Base.  This value must be larger than that specified
//         for Base.
//
// Return Value:
//
//     A ULONG offset from Base to Pointer.
//
//
//--

#define RtlPointerToOffset(B,P)  ((ULONG)( ((PCHAR)(P)) - ((PCHAR)(B))  ))

//++
//VOID
//RtlFailFast (
//    _In_ ULONG Code
//    );
//
// Routine Description:
//
//    This routine brings down the caller immediately in the event that
//    critical corruption has been detected.  No exception handlers are
//    invoked.
//
//    The routine may be used in libraries shared with user mode and
//    kernel mode.  In user mode, the process is terminated, whereas in
//    kernel mode, a KERNEL_SECURITY_CHECK_FAILURE bug check is raised.
//
// Arguments
//
//    Code - Supplies the reason code describing what type of corruption
//           was detected.
//
// Return Value:
//
//    None.  There is no return from this routine.
//
//--

DECLSPEC_NORETURN
FORCEINLINE
VOID
RtlFailFast(
    _In_ ULONG Code
)
{
    __fastfail(Code);
}

#endif // !_KERNEL_MODE

//
//  Doubly-linked list manipulation routines.
//

#ifndef _KERNEL_MODE

//
//  VOID
//  InitializeListHead32(
//      PLIST_ENTRY32 ListHead
//      );
//

#define InitializeListHead32(ListHead) (\
    (ListHead)->Flink = (ListHead)->Blink = PtrToUlong((ListHead)))

#define RTL_STATIC_LIST_HEAD(x) LIST_ENTRY x = { &x, &x }

FORCEINLINE
VOID
InitializeListHead(
    _Out_ PLIST_ENTRY ListHead
)
{
    ListHead->Flink = ListHead->Blink = ListHead;
    return;
}

_Must_inspect_result_
BOOLEAN
FORCEINLINE
IsListEmpty(
    _In_ const LIST_ENTRY* ListHead
)
{
    return (BOOLEAN)(ListHead->Flink == ListHead);
}

//++
//VOID
//FatalListEntryError (
//    _In_ PVOID p1,
//    _In_ PVOID p2,
//    _In_ PVOID p3
//    );
//
// Routine Description:
//
//    This routine reports a fatal list entry error.  It is implemented here as a
//    wrapper around RtlFailFast so that alternative reporting mechanisms (such
//    as simply logging and trying to continue) can be easily switched in.
//
// Arguments:
//
//    p1 - Supplies the first failure parameter.
//
//    p2 - Supplies the second failure parameter.
//
//    p3 - Supplies the third failure parameter.
//
//Return Value:
//
//    None.
//--

FORCEINLINE
VOID
FatalListEntryError(
    _In_ PVOID p1,
    _In_ PVOID p2,
    _In_ PVOID p3
)
{
    UNREFERENCED_PARAMETER(p1);
    UNREFERENCED_PARAMETER(p2);
    UNREFERENCED_PARAMETER(p3);

    RtlFailFast(FAST_FAIL_CORRUPT_LIST_ENTRY);
}

#if DBG

FORCEINLINE
VOID
RtlpCheckListEntry(
    _In_ PLIST_ENTRY Entry
)
{
    if ((((Entry->Flink)->Blink) != Entry) || (((Entry->Blink)->Flink) != Entry)) {
        FatalListEntryError((PVOID)(Entry),
            (PVOID)((Entry->Flink)->Blink),
            (PVOID)((Entry->Blink)->Flink));
    }
}

#else

#define RtlpCheckListEntry

#endif

FORCEINLINE
BOOLEAN
RemoveEntryList(
    _In_ PLIST_ENTRY Entry
)
{
    PLIST_ENTRY PrevEntry;
    PLIST_ENTRY NextEntry;

    NextEntry = Entry->Flink;
    PrevEntry = Entry->Blink;
    if ((NextEntry->Blink != Entry) || (PrevEntry->Flink != Entry)) {
        FatalListEntryError((PVOID)PrevEntry,
            (PVOID)Entry,
            (PVOID)NextEntry);
    }

    PrevEntry->Flink = NextEntry;
    NextEntry->Blink = PrevEntry;
    return (BOOLEAN)(PrevEntry == NextEntry);
}

FORCEINLINE
PLIST_ENTRY
RemoveHeadList(
    _Inout_ PLIST_ENTRY ListHead
)
{
    PLIST_ENTRY Entry;
    PLIST_ENTRY NextEntry;

    Entry = ListHead->Flink;

#if DBG

    RtlpCheckListEntry(ListHead);

#endif

    NextEntry = Entry->Flink;
    if ((Entry->Blink != ListHead) || (NextEntry->Blink != Entry)) {
        FatalListEntryError((PVOID)ListHead,
            (PVOID)Entry,
            (PVOID)NextEntry);
    }

    ListHead->Flink = NextEntry;
    NextEntry->Blink = ListHead;

    return Entry;
}

FORCEINLINE
PLIST_ENTRY
RemoveTailList(
    _Inout_ PLIST_ENTRY ListHead
)
{
    PLIST_ENTRY Entry;
    PLIST_ENTRY PrevEntry;

    Entry = ListHead->Blink;

#if DBG

    RtlpCheckListEntry(ListHead);

#endif

    PrevEntry = Entry->Blink;
    if ((Entry->Flink != ListHead) || (PrevEntry->Flink != Entry)) {
        FatalListEntryError((PVOID)PrevEntry,
            (PVOID)Entry,
            (PVOID)ListHead);
    }

    ListHead->Blink = PrevEntry;
    PrevEntry->Flink = ListHead;
    return Entry;
}


FORCEINLINE
VOID
InsertTailList(
    _Inout_ PLIST_ENTRY ListHead,
    _Out_ __drv_aliasesMem PLIST_ENTRY Entry
)
{
    PLIST_ENTRY PrevEntry;

#if DBG

    RtlpCheckListEntry(ListHead);

#endif

    PrevEntry = ListHead->Blink;
    if (PrevEntry->Flink != ListHead) {
        FatalListEntryError((PVOID)PrevEntry,
            (PVOID)ListHead,
            (PVOID)PrevEntry->Flink);
    }

    Entry->Flink = ListHead;
    Entry->Blink = PrevEntry;
    PrevEntry->Flink = Entry;
    ListHead->Blink = Entry;
    return;
}


FORCEINLINE
VOID
InsertHeadList(
    _Inout_ PLIST_ENTRY ListHead,
    _Out_ __drv_aliasesMem PLIST_ENTRY Entry
)
{
    PLIST_ENTRY NextEntry;

#if DBG

    RtlpCheckListEntry(ListHead);

#endif

    NextEntry = ListHead->Flink;
    if (NextEntry->Blink != ListHead) {
        FatalListEntryError((PVOID)ListHead,
            (PVOID)NextEntry,
            (PVOID)NextEntry->Blink);
    }

    Entry->Flink = NextEntry;
    Entry->Blink = ListHead;
    NextEntry->Blink = Entry;
    ListHead->Flink = Entry;
    return;
}

FORCEINLINE
VOID
AppendTailList(
    _Inout_ PLIST_ENTRY ListHead,
    _Inout_ PLIST_ENTRY ListToAppend
)
{
    PLIST_ENTRY ListEnd = ListHead->Blink;

    RtlpCheckListEntry(ListHead);
    RtlpCheckListEntry(ListToAppend);
    ListHead->Blink->Flink = ListToAppend;
    ListHead->Blink = ListToAppend->Blink;
    ListToAppend->Blink->Flink = ListHead;
    ListToAppend->Blink = ListEnd;
    return;
}

FORCEINLINE
PSINGLE_LIST_ENTRY
PopEntryList(
    _Inout_ PSINGLE_LIST_ENTRY ListHead
)
{
    PSINGLE_LIST_ENTRY FirstEntry;

    FirstEntry = ListHead->Next;
    if (FirstEntry != NULL) {
        ListHead->Next = FirstEntry->Next;
    }

    return FirstEntry;
}

FORCEINLINE
VOID
PushEntryList(
    _Inout_ PSINGLE_LIST_ENTRY ListHead,
    _Inout_ __drv_aliasesMem PSINGLE_LIST_ENTRY Entry
)
{
    Entry->Next = ListHead->Next;
    ListHead->Next = Entry;
    return;
}

#if !defined(MIDL_PASS)
__inline
void
ListEntry32To64(
    _In_ PLIST_ENTRY32 l32,
    _Out_ PLIST_ENTRY64 l64
)
{
    l64->Flink = (ULONGLONG)(ULONG)l32->Flink;
    l64->Blink = (ULONGLONG)(ULONG)l32->Blink;
}

__inline
void
ListEntry64To32(
    _In_ PLIST_ENTRY64 l64,
    _Out_ PLIST_ENTRY32 l32
)
{
    l32->Flink = (ULONG)l64->Flink;
    l32->Blink = (ULONG)l64->Blink;
}
#endif

#endif // !_KERNEL_MODE

//
// Run once
//

#ifndef _KERNEL_MODE

#ifndef _RTL_RUN_ONCE_DEF
#define _RTL_RUN_ONCE_DEF

//
// Run once
//

#define RTL_RUN_ONCE_INIT {0}   // Static initializer

//
// Run once flags
//

#define RTL_RUN_ONCE_CHECK_ONLY     0x00000001UL
#define RTL_RUN_ONCE_ASYNC          0x00000002UL
#define RTL_RUN_ONCE_INIT_FAILED    0x00000004UL

//
// The context stored in the run once structure must leave the following number
// of low order bits unused.
//

#define RTL_RUN_ONCE_CTX_RESERVED_BITS 2

typedef union _RTL_RUN_ONCE {
    PVOID Ptr;
} RTL_RUN_ONCE, * PRTL_RUN_ONCE;

#endif // _RTL_RUN_ONCE_DEF

typedef
_Function_class_(RTL_RUN_ONCE_INIT_FN)
_IRQL_requires_same_
ULONG /* LOGICAL */
NTAPI
RTL_RUN_ONCE_INIT_FN(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _Inout_opt_ PVOID Parameter,
    _Inout_opt_ PVOID* Context
);
typedef RTL_RUN_ONCE_INIT_FN* PRTL_RUN_ONCE_INIT_FN;

#if (NTDDI_VERSION >= NTDDI_LONGHORN)

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlRunOnceInitialize(
    _Out_ PRTL_RUN_ONCE RunOnce
);

_IRQL_requires_max_(APC_LEVEL)
_Maybe_raises_SEH_exception_
NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceExecuteOnce(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ __callback PRTL_RUN_ONCE_INIT_FN InitFn,
    _Inout_opt_ PVOID Parameter,
    _Outptr_opt_result_maybenull_ PVOID* Context
);

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceBeginInitialize(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ ULONG Flags,
    _Outptr_opt_result_maybenull_ PVOID* Context
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceComplete(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ ULONG Flags,
    _In_opt_ PVOID Context
);

#endif // NTDDI_VERSION >= NTDDI_LONGHORN

#endif // !_KERNEL_MODE

//
// AVL Trees
//

#ifndef _KERNEL_MODE

//
// This enumerated type is used as the function return value of the function
// that is used to search the tree for a key. FoundNode indicates that the
// function found the key. Insert as left indicates that the key was not found
// and the node should be inserted as the left child of the parent. Insert as
// right indicates that the key was not found and the node should be inserted
//  as the right child of the parent.
//
typedef enum _TABLE_SEARCH_RESULT {
    TableEmptyTree,
    TableFoundNode,
    TableInsertAsLeft,
    TableInsertAsRight
} TABLE_SEARCH_RESULT;

//
//  The results of a compare can be less than, equal, or greater than.
//

typedef enum _RTL_GENERIC_COMPARE_RESULTS {
    GenericLessThan,
    GenericGreaterThan,
    GenericEqual
} RTL_GENERIC_COMPARE_RESULTS;

//
//  Define the Avl version of the generic table package.  Note a generic table
//  should really be an opaque type.  We provide routines to manipulate the structure.
//
//  A generic table is package for inserting, deleting, and looking up elements
//  in a table (e.g., in a symbol table).  To use this package the user
//  defines the structure of the elements stored in the table, provides a
//  comparison function, a memory allocation function, and a memory
//  deallocation function.
//
//  Note: the user compare function must impose a complete ordering among
//  all of the elements, and the table does not allow for duplicate entries.
//

//
// Add an empty typedef so that functions can reference the
// a pointer to the generic table struct before it is declared.
//

struct _RTL_AVL_TABLE;

//
//  The comparison function takes as input pointers to elements containing
//  user defined structures and returns the results of comparing the two
//  elements.
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_COMPARE_ROUTINE)
RTL_GENERIC_COMPARE_RESULTS
NTAPI
RTL_AVL_COMPARE_ROUTINE(
    _In_ struct _RTL_AVL_TABLE* Table,
    _In_ PVOID FirstStruct,
    _In_ PVOID SecondStruct
);
typedef RTL_AVL_COMPARE_ROUTINE* PRTL_AVL_COMPARE_ROUTINE;

//
//  The allocation function is called by the generic table package whenever
//  it needs to allocate memory for the table.
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_ALLOCATE_ROUTINE)
__drv_allocatesMem(Mem)
PVOID
NTAPI
RTL_AVL_ALLOCATE_ROUTINE(
    _In_ struct _RTL_AVL_TABLE* Table,
    _In_ ULONG ByteSize
);
typedef RTL_AVL_ALLOCATE_ROUTINE* PRTL_AVL_ALLOCATE_ROUTINE;

//
//  The deallocation function is called by the generic table package whenever
//  it needs to deallocate memory from the table that was allocated by calling
//  the user supplied allocation function.
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_FREE_ROUTINE)
VOID
NTAPI
RTL_AVL_FREE_ROUTINE(
    _In_ struct _RTL_AVL_TABLE* Table,
    _In_ __drv_freesMem(Mem) _Post_invalid_ PVOID Buffer
);
typedef RTL_AVL_FREE_ROUTINE* PRTL_AVL_FREE_ROUTINE;

//
//  The match function takes as input the user data to be matched and a pointer
//  to some match data, which was passed along with the function pointer.  It
//  returns TRUE for a match and FALSE for no match.
//
//  RTL_AVL_MATCH_FUNCTION returns
//      STATUS_SUCCESS if the IndexRow matches
//      STATUS_NO_MATCH if the IndexRow does not match, but the enumeration should
//          continue
//      STATUS_NO_MORE_MATCHES if the IndexRow does not match, and the enumeration
//          should terminate
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_AVL_MATCH_FUNCTION)
NTSTATUS
NTAPI
RTL_AVL_MATCH_FUNCTION(
    _In_ struct _RTL_AVL_TABLE* Table,
    _In_ PVOID UserData,
    _In_ PVOID MatchData
);
typedef RTL_AVL_MATCH_FUNCTION* PRTL_AVL_MATCH_FUNCTION;

//
//  Define the balanced tree links and Balance field.  (No Rank field
//  defined at this time.)
//
//  Callers should treat this structure as opaque!
//
//  The root of a balanced binary tree is not a real node in the tree
//  but rather points to a real node which is the root.  It is always
//  in the table below, and its fields are used as follows:
//
//      Parent      Pointer to self, to allow for detection of the root.
//      LeftChild   NULL
//      RightChild  Pointer to real root
//      Balance     Undefined, however it is set to a convenient value
//                  (depending on the algorithm) prior to rebalancing
//                  in insert and delete routines.
//

typedef struct _RTL_BALANCED_LINKS {
    struct _RTL_BALANCED_LINKS* Parent;
    struct _RTL_BALANCED_LINKS* LeftChild;
    struct _RTL_BALANCED_LINKS* RightChild;
    CHAR Balance;
    UCHAR Reserved[3];
} RTL_BALANCED_LINKS;
typedef RTL_BALANCED_LINKS* PRTL_BALANCED_LINKS;

//
//  To use the generic table package the user declares a variable of type
//  GENERIC_TABLE and then uses the routines described below to initialize
//  the table and to manipulate the table.  Note that the generic table
//  should really be an opaque type.
//

typedef struct _RTL_AVL_TABLE {
    RTL_BALANCED_LINKS BalancedRoot;
    PVOID OrderedPointer;
    ULONG WhichOrderedElement;
    ULONG NumberGenericTableElements;
    ULONG DepthOfTree;
    PRTL_BALANCED_LINKS RestartKey;
    ULONG DeleteCount;
    PRTL_AVL_COMPARE_ROUTINE CompareRoutine;
    PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine;
    PRTL_AVL_FREE_ROUTINE FreeRoutine;
    PVOID TableContext;
} RTL_AVL_TABLE;
typedef RTL_AVL_TABLE* PRTL_AVL_TABLE;

//
//  The procedure InitializeGenericTable takes as input an uninitialized
//  generic table variable and pointers to the three user supplied routines.
//  This must be called for every individual generic table variable before
//  it can be used.
//

NTSYSAPI
VOID
NTAPI
RtlInitializeGenericTableAvl(
    _Out_ PRTL_AVL_TABLE Table,
    _In_ PRTL_AVL_COMPARE_ROUTINE CompareRoutine,
    _In_ PRTL_AVL_ALLOCATE_ROUTINE AllocateRoutine,
    _In_ PRTL_AVL_FREE_ROUTINE FreeRoutine,
    _In_opt_ PVOID TableContext
);

//
//  The function InsertElementGenericTable will insert a new element
//  in a table.  It does this by allocating space for the new element
//  (this includes AVL links), inserting the element in the table, and
//  then returning to the user a pointer to the new element.  If an element
//  with the same key already exists in the table the return value is a pointer
//  to the old element.  The optional output parameter NewElement is used
//  to indicate if the element previously existed in the table.  Note: the user
//  supplied Buffer is only used for searching the table, upon insertion its
//  contents are copied to the newly created element.  This means that
//  pointer to the input buffer will not point to the new element.
//

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement
);

//
//  The function InsertElementGenericTableFull will insert a new element
//  in a table.  It does this by allocating space for the new element
//  (this includes AVL links), inserting the element in the table, and
//  then returning to the user a pointer to the new element.  If an element
//  with the same key already exists in the table the return value is a pointer
//  to the old element.  The optional output parameter NewElement is used
//  to indicate if the element previously existed in the table.  Note: the user
//  supplied Buffer is only used for searching the table, upon insertion its
//  contents are copied to the newly created element.  This means that
//  pointer to the input buffer will not point to the new element.
//  This routine is passed the NodeOrParent and SearchResult from a
//  previous RtlLookupElementGenericTableFull.
//

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTableFullAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement,
    _In_ PVOID NodeOrParent,
    _In_ TABLE_SEARCH_RESULT SearchResult
);

//
//  The function DeleteElementGenericTable will find and delete an element
//  from a generic table.  If the element is located and deleted the return
//  value is TRUE, otherwise if the element is not located the return value
//  is FALSE.  The user supplied input buffer is only used as a key in
//  locating the element in the table.
//

NTSYSAPI
BOOLEAN
NTAPI
RtlDeleteElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer
);

//
//  The function DeleteElementGenericTableAvxEx deletes the element specified
//  by the NodeOrParent pointer. This element user data pointer must have first
//  been obtained with RtlLookupElementGenericTableFull.
//

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
VOID
NTAPI
RtlDeleteElementGenericTableAvlEx(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID NodeOrParent
);
#endif // NTDDI_VERSION >= NTDDI_WIN8

//
//  The function LookupElementGenericTable will find an element in a generic
//  table.  If the element is located the return value is a pointer to
//  the user defined structure associated with the element, otherwise if
//  the element is not located the return value is NULL.  The user supplied
//  input buffer is only used as a key in locating the element in the table.
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer
);

//
//  The function LookupElementGenericTableFull will find an element in a generic
//  table.  If the element is located the return value is a pointer to
//  the user defined structure associated with the element.  If the element is not
//  located then a pointer to the parent for the insert location is returned.  The
//  user must look at the SearchResult value to determine which is being returned.
//  The user can use the SearchResult and parent for a subsequent FullInsertElement
//  call to optimize the insert.
//

NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTableFullAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID* NodeOrParent,
    _Out_ TABLE_SEARCH_RESULT* SearchResult
);

//
//  The function EnumerateGenericTable will return to the caller one-by-one
//  the elements of of a table.  The return value is a pointer to the user
//  defined structure associated with the element.  The input parameter
//  Restart indicates if the enumeration should start from the beginning
//  or should return the next element.  If the are no more new elements to
//  return the return value is NULL.  As an example of its use, to enumerate
//  all of the elements in a table the user would write:
//
//      for (ptr = EnumerateGenericTable(Table, TRUE);
//           ptr != NULL;
//           ptr = EnumerateGenericTable(Table, FALSE)) {
//              :
//      }
//
//  NOTE:   This routine does not modify the structure of the tree, but saves
//          the last node returned in the generic table itself, and for this
//          reason requires exclusive access to the table for the duration of
//          the enumeration.
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ BOOLEAN Restart
);

//
//  The function EnumerateGenericTableWithoutSplaying will return to the
//  caller one-by-one the elements of of a table.  The return value is a
//  pointer to the user defined structure associated with the element.
//  The input parameter RestartKey indicates if the enumeration should
//  start from the beginning or should return the next element.  If the
//  are no more new elements to return the return value is NULL.  As an
//  example of its use, to enumerate all of the elements in a table the
//  user would write:
//
//      RestartKey = NULL;
//      for (ptr = EnumerateGenericTableWithoutSplaying(Table, &RestartKey);
//           ptr != NULL;
//           ptr = EnumerateGenericTableWithoutSplaying(Table, &RestartKey)) {
//              :
//      }
//
//  If RestartKey is NULL, the package will start from the least entry in the
//  table, otherwise it will start from the last entry returned.
//
//  NOTE:   This routine does not modify either the structure of the tree
//          or the generic table itself, but must insure that no deletes
//          occur for the duration of the enumeration, typically by having
//          at least shared access to the table for the duration.
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableWithoutSplayingAvl(
    _In_ PRTL_AVL_TABLE Table,
    _Inout_ PVOID* RestartKey
);

//
//  RtlLookupFirstMatchingElementGenericTableAvl will return the left-most
//  element in the tree matching the data in Buffer.  If, for example, the tree
//  contains filenames there may exist several that differ only in case. A case-
//  blind searcher can use this routine to position himself in the tree at the
//  first match, and use an enumeration routine (such as RtlEnumerateGenericTableWithoutSplayingAvl
//  to return each subsequent match.
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlLookupFirstMatchingElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID* RestartKey
);

//
//  The function EnumerateGenericTableLikeADirectory will return to the
//  caller one-by-one the elements of of a table.  The return value is a
//  pointer to the user defined structure associated with the element.
//  The input parameter RestartKey indicates if the enumeration should
//  start from the beginning or should return the next element.  If the
//  are no more new elements to return the return value is NULL.  As an
//  example of its use, to enumerate all of the elements in a table the
//  user would write:
//
//      RestartKey = NULL;
//      for (ptr = EnumerateGenericTableLikeADirectory(Table, &RestartKey, ...);
//           ptr != NULL;
//           ptr = EnumerateGenericTableLikeADirectory(Table, &RestartKey, ...)) {
//              :
//      }
//
//  If RestartKey is NULL, the package will start from the least entry in the
//  table, otherwise it will start from the last entry returned.
//
//  NOTE:   This routine does not modify either the structure of the tree
//          or the generic table itself.  The table must only be acquired
//          shared for the duration of this call, and all synchronization
//          may optionally be dropped between calls.  Enumeration is always
//          correctly resumed in the most efficient manner possible via the
//          IN OUT parameters provided.
//
//  ******  Explain NextFlag.  Directory enumeration resumes from a key
//          requires more thought.  Also need the match pattern and IgnoreCase.
//          Should some structure be introduced to carry it all?
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableLikeADirectory(
    _In_ PRTL_AVL_TABLE Table,
    _In_opt_ PRTL_AVL_MATCH_FUNCTION MatchFunction,
    _In_opt_ PVOID MatchData,
    _In_ ULONG NextFlag,
    _Inout_ PVOID* RestartKey,
    _Inout_ PULONG DeleteCount,
    _In_ PVOID Buffer
);

//
// The function GetElementGenericTable will return the i'th element
// inserted in the generic table.  I = 0 implies the first element,
// I = (RtlNumberGenericTableElements(Table)-1) will return the last element
// inserted into the generic table.  The type of I is ULONG.  Values
// of I > than (NumberGenericTableElements(Table)-1) will return NULL.  If
// an arbitrary element is deleted from the generic table it will cause
// all elements inserted after the deleted element to "move up".

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlGetElementGenericTableAvl(
    _In_ PRTL_AVL_TABLE Table,
    _In_ ULONG I
);

//
// The function NumberGenericTableElements returns a ULONG value
// which is the number of generic table elements currently inserted
// in the generic table.

NTSYSAPI
ULONG
NTAPI
RtlNumberGenericTableElementsAvl(
    _In_ PRTL_AVL_TABLE Table
);

//
//  The function IsGenericTableEmpty will return to the caller TRUE if
//  the input table is empty (i.e., does not contain any elements) and
//  FALSE otherwise.
//

//
// Generic extensions for using generic structures with the avl libraries.
//
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsGenericTableEmptyAvl(
    _In_ PRTL_AVL_TABLE Table
);

#endif // !_KERNEL_MODE

//
// SPlay linked
//

#ifndef _KERNEL_MODE

//
//  Define the splay links and the associated manipuliation macros and
//  routines.  Note that the splay_links should be an opaque type.
//  Routine are provided to traverse and manipulate the structure.
//

typedef struct _RTL_SPLAY_LINKS {
    struct _RTL_SPLAY_LINKS* Parent;
    struct _RTL_SPLAY_LINKS* LeftChild;
    struct _RTL_SPLAY_LINKS* RightChild;
} RTL_SPLAY_LINKS;
typedef RTL_SPLAY_LINKS* PRTL_SPLAY_LINKS;

#if !defined(MIDL_PASS) && !defined(SORTPP_PASS)

FORCEINLINE
VOID
RtlInitializeSplayLinks(
    _Out_ PRTL_SPLAY_LINKS Links
)
//++
//
//  The procedure InitializeSplayLinks takes as input a pointer to
//  splay link and initializes its substructure.  All splay link nodes must
//  be initialized before they are used in the different splay routines and
//  macros.
//
//--
{
    Links->Parent = Links;
    Links->LeftChild = NULL;
    Links->RightChild = NULL;
}

#endif // !defined(MIDL_PASS) && !defined(SORTPP_PASS)

//
//  The macro function Parent takes as input a pointer to a splay link in a
//  tree and returns a pointer to the splay link of the parent of the input
//  node.  If the input node is the root of the tree the return value is
//  equal to the input value.
//
//  PRTL_SPLAY_LINKS
//  RtlParent (
//      PRTL_SPLAY_LINKS Links
//      );
//

#define RtlParent(Links) (           \
    (PRTL_SPLAY_LINKS)(Links)->Parent \
    )

//
//  The macro function LeftChild takes as input a pointer to a splay link in
//  a tree and returns a pointer to the splay link of the left child of the
//  input node.  If the left child does not exist, the return value is NULL.
//
//  PRTL_SPLAY_LINKS
//  RtlLeftChild (
//      PRTL_SPLAY_LINKS Links
//      );
//

#define RtlLeftChild(Links) (           \
    (PRTL_SPLAY_LINKS)(Links)->LeftChild \
    )

//
//  The macro function RightChild takes as input a pointer to a splay link
//  in a tree and returns a pointer to the splay link of the right child of
//  the input node.  If the right child does not exist, the return value is
//  NULL.
//
//  PRTL_SPLAY_LINKS
//  RtlRightChild (
//      PRTL_SPLAY_LINKS Links
//      );
//

#define RtlRightChild(Links) (           \
    (PRTL_SPLAY_LINKS)(Links)->RightChild \
    )

//
//  The macro function IsRoot takes as input a pointer to a splay link
//  in a tree and returns TRUE if the input node is the root of the tree,
//  otherwise it returns FALSE.
//
//  BOOLEAN
//  RtlIsRoot (
//      PRTL_SPLAY_LINKS Links
//      );
//

#define RtlIsRoot(Links) (                          \
    (RtlParent(Links) == (PRTL_SPLAY_LINKS)(Links)) \
    )

//
//  The macro function IsLeftChild takes as input a pointer to a splay link
//  in a tree and returns TRUE if the input node is the left child of its
//  parent, otherwise it returns FALSE.
//
//  BOOLEAN
//  RtlIsLeftChild (
//      PRTL_SPLAY_LINKS Links
//      );
//

#define RtlIsLeftChild(Links) (                                   \
    (RtlLeftChild(RtlParent(Links)) == (PRTL_SPLAY_LINKS)(Links)) \
    )

//
//  The macro function IsRightChild takes as input a pointer to a splay link
//  in a tree and returns TRUE if the input node is the right child of its
//  parent, otherwise it returns FALSE.
//
//  BOOLEAN
//  RtlIsRightChild (
//      PRTL_SPLAY_LINKS Links
//      );
//

#define RtlIsRightChild(Links) (                                   \
    (RtlRightChild(RtlParent(Links)) == (PRTL_SPLAY_LINKS)(Links)) \
    )


#if !defined(MIDL_PASS) && !defined(SORTPP_PASS)

FORCEINLINE
VOID
RtlInsertAsLeftChild(
    _Inout_ PRTL_SPLAY_LINKS ParentLinks,
    _Inout_ PRTL_SPLAY_LINKS ChildLinks
)
//++
//
//  The procedure InsertAsLeftChild takes as input a pointer to a splay
//  link in a tree and a pointer to a node not in a tree.  It inserts the
//  second node as the left child of the first node.  The first node must not
//  already have a left child, and the second node must not already have a
//  parent.
//
//--
{
    ParentLinks->LeftChild = ChildLinks;
    ChildLinks->Parent = ParentLinks;
}

FORCEINLINE
VOID
RtlInsertAsRightChild(
    _Inout_ PRTL_SPLAY_LINKS ParentLinks,
    _Inout_ PRTL_SPLAY_LINKS ChildLinks
)
//++
//
//  The procedure InsertAsRightChild takes as input a pointer to a splay
//  link in a tree and a pointer to a node not in a tree.  It inserts the
//  second node as the right child of the first node.  The first node must not
//  already have a right child, and the second node must not already have a
//  parent.
//
//--
{
    ParentLinks->RightChild = ChildLinks;
    ChildLinks->Parent = ParentLinks;
}

#endif // !defined(MIDL_PASS) && !defined(SORTPP_PASS)

//
//  The Splay function takes as input a pointer to a splay link in a tree
//  and splays the tree.  Its function return value is a pointer to the
//  root of the splayed tree.
//

NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlSplay(
    _Inout_ PRTL_SPLAY_LINKS Links
);

//
//  The Delete function takes as input a pointer to a splay link in a tree
//  and deletes that node from the tree.  Its function return value is a
//  pointer to the root of the tree.  If the tree is now empty, the return
//  value is NULL.
//

NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlDelete(
    _In_ PRTL_SPLAY_LINKS Links
);

//
//  The DeleteNoSplay function takes as input a pointer to a splay link in a tree,
//  the caller's pointer to the root of the tree and deletes that node from the
//  tree.  Upon return the caller's pointer to the root node will correctly point
//  at the root of the tree.
//
//  It operationally differs from RtlDelete only in that it will not splay the tree.
//

NTSYSAPI
VOID
NTAPI
RtlDeleteNoSplay(
    _In_ PRTL_SPLAY_LINKS Links,
    _Inout_ PRTL_SPLAY_LINKS* Root
);

//
//  The SubtreeSuccessor function takes as input a pointer to a splay link
//  in a tree and returns a pointer to the successor of the input node of
//  the substree rooted at the input node.  If there is not a successor, the
//  return value is NULL.
//

_Must_inspect_result_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlSubtreeSuccessor(
    _In_ PRTL_SPLAY_LINKS Links
);

//
//  The SubtreePredecessor function takes as input a pointer to a splay link
//  in a tree and returns a pointer to the predecessor of the input node of
//  the substree rooted at the input node.  If there is not a predecessor,
//  the return value is NULL.
//

_Must_inspect_result_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlSubtreePredecessor(
    _In_ PRTL_SPLAY_LINKS Links
);

//
//  The RealSuccessor function takes as input a pointer to a splay link
//  in a tree and returns a pointer to the successor of the input node within
//  the entire tree.  If there is not a successor, the return value is NULL.
//

_Must_inspect_result_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlRealSuccessor(
    _In_ PRTL_SPLAY_LINKS Links
);

//
//  The RealPredecessor function takes as input a pointer to a splay link
//  in a tree and returns a pointer to the predecessor of the input node
//  within the entire tree.  If there is not a predecessor, the return value
//  is NULL.
//

_Must_inspect_result_
NTSYSAPI
PRTL_SPLAY_LINKS
NTAPI
RtlRealPredecessor(
    _In_ PRTL_SPLAY_LINKS Links
);

#endif // !_KERNEL_MODE

//
// Generic table
//

#ifndef _KERNEL_MODE

//
//  Define the generic table package.  Note a generic table should really
//  be an opaque type.  We provide routines to manipulate the structure.
//
//  A generic table is package for inserting, deleting, and looking up elements
//  in a table (e.g., in a symbol table).  To use this package the user
//  defines the structure of the elements stored in the table, provides a
//  comparison function, a memory allocation function, and a memory
//  deallocation function.
//
//  Note: the user compare function must impose a complete ordering among
//  all of the elements, and the table does not allow for duplicate entries.
//

//
//  Do not do the following defines if using Avl
//

#ifndef RTL_USE_AVL_TABLES

//
// Add an empty typedef so that functions can reference the
// a pointer to the generic table struct before it is declared.
//

struct _RTL_GENERIC_TABLE;

//
//  The comparison function takes as input pointers to elements containing
//  user defined structures and returns the results of comparing the two
//  elements.
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_GENERIC_COMPARE_ROUTINE)
RTL_GENERIC_COMPARE_RESULTS
NTAPI
RTL_GENERIC_COMPARE_ROUTINE(
    _In_ struct _RTL_GENERIC_TABLE* Table,
    _In_ PVOID FirstStruct,
    _In_ PVOID SecondStruct
);
typedef RTL_GENERIC_COMPARE_ROUTINE* PRTL_GENERIC_COMPARE_ROUTINE;

//
//  The allocation function is called by the generic table package whenever
//  it needs to allocate memory for the table.
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_GENERIC_ALLOCATE_ROUTINE)
__drv_allocatesMem(Mem)
PVOID
NTAPI
RTL_GENERIC_ALLOCATE_ROUTINE(
    _In_ struct _RTL_GENERIC_TABLE* Table,
    _In_ ULONG ByteSize
);
typedef RTL_GENERIC_ALLOCATE_ROUTINE* PRTL_GENERIC_ALLOCATE_ROUTINE;

//
//  The deallocation function is called by the generic table package whenever
//  it needs to deallocate memory from the table that was allocated by calling
//  the user supplied allocation function.
//

typedef
_IRQL_requires_same_
_Function_class_(RTL_GENERIC_FREE_ROUTINE)
VOID
NTAPI
RTL_GENERIC_FREE_ROUTINE(
    _In_ struct _RTL_GENERIC_TABLE* Table,
    _In_ __drv_freesMem(Mem) _Post_invalid_ PVOID Buffer
);
typedef RTL_GENERIC_FREE_ROUTINE* PRTL_GENERIC_FREE_ROUTINE;

//
//  To use the generic table package the user declares a variable of type
//  GENERIC_TABLE and then uses the routines described below to initialize
//  the table and to manipulate the table.  Note that the generic table
//  should really be an opaque type.
//

typedef struct _RTL_GENERIC_TABLE {
    PRTL_SPLAY_LINKS TableRoot;
    LIST_ENTRY InsertOrderList;
    PLIST_ENTRY OrderedPointer;
    ULONG WhichOrderedElement;
    ULONG NumberGenericTableElements;
    PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine;
    PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine;
    PRTL_GENERIC_FREE_ROUTINE FreeRoutine;
    PVOID TableContext;
} RTL_GENERIC_TABLE;
typedef RTL_GENERIC_TABLE* PRTL_GENERIC_TABLE;

//
//  The procedure InitializeGenericTable takes as input an uninitialized
//  generic table variable and pointers to the three user supplied routines.
//  This must be called for every individual generic table variable before
//  it can be used.
//

NTSYSAPI
VOID
NTAPI
RtlInitializeGenericTable(
    _Out_ PRTL_GENERIC_TABLE Table,
    _In_ PRTL_GENERIC_COMPARE_ROUTINE CompareRoutine,
    _In_ PRTL_GENERIC_ALLOCATE_ROUTINE AllocateRoutine,
    _In_ PRTL_GENERIC_FREE_ROUTINE FreeRoutine,
    _In_opt_ PVOID TableContext
);

//
//  The function InsertElementGenericTable will insert a new element
//  in a table.  It does this by allocating space for the new element
//  (this includes splay links), inserting the element in the table, and
//  then returning to the user a pointer to the new element.  If an element
//  with the same key already exists in the table the return value is a pointer
//  to the old element.  The optional output parameter NewElement is used
//  to indicate if the element previously existed in the table.  Note: the user
//  supplied Buffer is only used for searching the table, upon insertion its
//  contents are copied to the newly created element.  This means that
//  pointer to the input buffer will not point to the new element.
//

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement
);

//
//  The function InsertElementGenericTableFull will insert a new element
//  in a table.  It does this by allocating space for the new element
//  (this includes splay links), inserting the element in the table, and
//  then returning to the user a pointer to the new element.  If an element
//  with the same key already exists in the table the return value is a pointer
//  to the old element.  The optional output parameter NewElement is used
//  to indicate if the element previously existed in the table.  Note: the user
//  supplied Buffer is only used for searching the table, upon insertion its
//  contents are copied to the newly created element.  This means that
//  pointer to the input buffer will not point to the new element.
//  This routine is passed the NodeOrParent and SearchResult from a
//  previous RtlLookupElementGenericTableFull.
//

NTSYSAPI
PVOID
NTAPI
RtlInsertElementGenericTableFull(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_reads_bytes_(BufferSize) PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PBOOLEAN NewElement,
    _In_ PVOID NodeOrParent,
    _In_ TABLE_SEARCH_RESULT SearchResult
);

//
//  The function DeleteElementGenericTable will find and delete an element
//  from a generic table.  If the element is located and deleted the return
//  value is TRUE, otherwise if the element is not located the return value
//  is FALSE.  The user supplied input buffer is only used as a key in
//  locating the element in the table.
//

NTSYSAPI
BOOLEAN
NTAPI
RtlDeleteElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer
);

//
//  The function LookupElementGenericTable will find an element in a generic
//  table.  If the element is located the return value is a pointer to
//  the user defined structure associated with the element, otherwise if
//  the element is not located the return value is NULL.  The user supplied
//  input buffer is only used as a key in locating the element in the table.
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer
);

//
//  The function LookupElementGenericTableFull will find an element in a generic
//  table.  If the element is located the return value is a pointer to
//  the user defined structure associated with the element.  If the element is not
//  located then a pointer to the parent for the insert location is returned.  The
//  user must look at the SearchResult value to determine which is being returned.
//  The user can use the SearchResult and parent for a subsequent FullInsertElement
//  call to optimize the insert.
//

NTSYSAPI
PVOID
NTAPI
RtlLookupElementGenericTableFull(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ PVOID Buffer,
    _Out_ PVOID* NodeOrParent,
    _Out_ TABLE_SEARCH_RESULT* SearchResult
);

//
//  The function EnumerateGenericTable will return to the caller one-by-one
//  the elements of of a table.  The return value is a pointer to the user
//  defined structure associated with the element.  The input parameter
//  Restart indicates if the enumeration should start from the beginning
//  or should return the next element.  If the are no more new elements to
//  return the return value is NULL.  As an example of its use, to enumerate
//  all of the elements in a table the user would write:
//
//      for (ptr = EnumerateGenericTable(Table, TRUE);
//           ptr != NULL;
//           ptr = EnumerateGenericTable(Table, FALSE)) {
//              :
//      }
//
//
//  PLEASE NOTE:
//
//      If you enumerate a GenericTable using RtlEnumerateGenericTable, you
//      will flatten the table, turning it into a sorted linked list.
//      To enumerate the table without perturbing the splay links, use
//      RtlEnumerateGenericTableWithoutSplaying

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ BOOLEAN Restart
);

//
//  The function EnumerateGenericTableWithoutSplaying will return to the
//  caller one-by-one the elements of of a table.  The return value is a
//  pointer to the user defined structure associated with the element.
//  The input parameter RestartKey indicates if the enumeration should
//  start from the beginning or should return the next element.  If the
//  are no more new elements to return the return value is NULL.  As an
//  example of its use, to enumerate all of the elements in a table the
//  user would write:
//
//      RestartKey = NULL;
//      for (ptr = EnumerateGenericTableWithoutSplaying(Table, &RestartKey);
//           ptr != NULL;
//           ptr = EnumerateGenericTableWithoutSplaying(Table, &RestartKey)) {
//              :
//      }
//
//  If RestartKey is NULL, the package will start from the least entry in the
//  table, otherwise it will start from the last entry returned.
//
//
//  Note that unlike RtlEnumerateGenericTable, this routine will NOT perturb
//  the splay order of the tree.
//

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlEnumerateGenericTableWithoutSplaying(
    _In_ PRTL_GENERIC_TABLE Table,
    _Inout_ PVOID* RestartKey
);

//
// The function GetElementGenericTable will return the i'th element
// inserted in the generic table.  I = 0 implies the first element,
// I = (RtlNumberGenericTableElements(Table)-1) will return the last element
// inserted into the generic table.  The type of I is ULONG.  Values
// of I > than (NumberGenericTableElements(Table)-1) will return NULL.  If
// an arbitrary element is deleted from the generic table it will cause
// all elements inserted after the deleted element to "move up".

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlGetElementGenericTable(
    _In_ PRTL_GENERIC_TABLE Table,
    _In_ ULONG I
);

//
// The function NumberGenericTableElements returns a ULONG value
// which is the number of generic table elements currently inserted
// in the generic table.

NTSYSAPI
ULONG
NTAPI
RtlNumberGenericTableElements(
    _In_ PRTL_GENERIC_TABLE Table
);

//
//  The function IsGenericTableEmpty will return to the caller TRUE if
//  the input table is empty (i.e., does not contain any elements) and
//  FALSE otherwise.
//

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsGenericTableEmpty(
    _In_ PRTL_GENERIC_TABLE Table
);

#endif // RTL_USE_AVL_TABLES

#endif // !_KERNEL_MODE

//
// Hash Table
//

#ifndef _KERNEL_MODE

//
// The hash table header structure can either be allocated
// by the caller, or by the hash table creation function itself.
// This flag indicates what was done at creation time.
//
#define RTL_HASH_ALLOCATED_HEADER            0x00000001

//
// The RTL_HASH_RESERVED_SIGNATURE is the signature used internally for
// enumerators. A caller can never assign this signature to
// valid entries.
//
#define RTL_HASH_RESERVED_SIGNATURE 0


typedef struct _RTL_DYNAMIC_HASH_TABLE_ENTRY {
    LIST_ENTRY Linkage;
    ULONG_PTR Signature;
} RTL_DYNAMIC_HASH_TABLE_ENTRY, * PRTL_DYNAMIC_HASH_TABLE_ENTRY;

//
// Some components want to see the actual signature and can use
// this macro to encapsulate that operation.
//
#define HASH_ENTRY_KEY(x)    ((x)->Signature)

//
// Brief background on each of the parameters and their
// justification:
// 1. ChainHead stores the pointer to a bucket. This is needed since
//    our hash chains are doubly-linked circular lists, and there is
//    is no way to determine whether we've reached the end of the
//    chain unless we store the pointer to the bucket itself. This
//    is particularly used in walking the sub-list of entries returned
//    by a lookup. We need to know when the sub-list has been
//    completely returned.
// 2. PrevLinkage stores a pointer to the entry before the entry
//    under consideration. The reason for storing the previous entry
//    instead of the entry itself is for cases where a lookup fails
//    and PrevLinkage actually stores the entry that would have been
//    the previous entry, had the looked up entry existed. This can
//    then be used to actually insert the entry at that place.
// 3. Signature is used primarily as a safety check in insertion.
//    This field must match the Signature of the entry being inserted.
//

typedef struct _RTL_DYNAMIC_HASH_TABLE_CONTEXT {
    PLIST_ENTRY ChainHead;
    PLIST_ENTRY PrevLinkage;
    ULONG_PTR Signature;
} RTL_DYNAMIC_HASH_TABLE_CONTEXT, * PRTL_DYNAMIC_HASH_TABLE_CONTEXT;

typedef struct _RTL_DYNAMIC_HASH_TABLE_ENUMERATOR {
    union {
        RTL_DYNAMIC_HASH_TABLE_ENTRY HashEntry;
        PLIST_ENTRY CurEntry;
    };
    PLIST_ENTRY ChainHead;
    ULONG BucketIndex;
} RTL_DYNAMIC_HASH_TABLE_ENUMERATOR, * PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR;

typedef struct _RTL_DYNAMIC_HASH_TABLE {

    // Entries initialized at creation
    ULONG Flags;
    ULONG Shift;

    // Entries used in bucket computation.
    ULONG TableSize;
    ULONG Pivot;
    ULONG DivisorMask;

    // Counters
    ULONG NumEntries;
    ULONG NonEmptyBuckets;
    ULONG NumEnumerators;

    // The directory. This field is for internal use only.
    PVOID Directory;

} RTL_DYNAMIC_HASH_TABLE, * PRTL_DYNAMIC_HASH_TABLE;

//
// Inline functions first.
//
#if !defined(MIDL_PASS) && !defined(SORTPP_PASS)

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
VOID
RtlInitHashTableContext(
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
)
{
    Context->ChainHead = NULL;
    Context->PrevLinkage = NULL;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
VOID
RtlInitHashTableContextFromEnumerator(
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context,
    _In_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
)
{
    Context->ChainHead = Enumerator->ChainHead;
    Context->PrevLinkage = Enumerator->HashEntry.Linkage.Blink;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
void
RtlReleaseHashTableContext(
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
)
{
    UNREFERENCED_PARAMETER(Context);
    return;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
ULONG
RtlTotalBucketsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
)
{
    return HashTable->TableSize;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
ULONG
RtlNonEmptyBucketsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
)
{
    return HashTable->NonEmptyBuckets;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
ULONG
RtlEmptyBucketsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
)
{
    return HashTable->TableSize - HashTable->NonEmptyBuckets;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
ULONG
RtlTotalEntriesHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
)
{
    return HashTable->NumEntries;
}
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
FORCEINLINE
ULONG
RtlActiveEnumeratorsHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
)
{
    return HashTable->NumEnumerators;
}
#endif

#endif // !defined(MIDL_PASS) && !defined(SORTPP_PASS)

//
// Almost all the hash functions take in a Context.
// If a valid context is passed in, it will be used
// in executing the operation if possible. If a
// blank context is passed in, it will be initialized
// appropriately.
//

#if (NTDDI_VERSION >= NTDDI_WIN7)
_Must_inspect_result_
_Success_(return != 0)
NTSYSAPI
BOOLEAN
NTAPI
RtlCreateHashTable(
    _Inout_ _When_(NULL == *HashTable, _At_(*HashTable, __drv_allocatesMem(Mem)))
    PRTL_DYNAMIC_HASH_TABLE * HashTable,
    _In_ ULONG Shift,
    _Reserved_ ULONG Flags
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Must_inspect_result_
_Success_(return != 0)
NTSYSAPI
BOOLEAN
NTAPI
RtlCreateHashTableEx(
    _Inout_ _When_(NULL == *HashTable, _At_(*HashTable, __drv_allocatesMem(Mem)))
    PRTL_DYNAMIC_HASH_TABLE * HashTable,
    _In_ ULONG InitialSize,
    _In_ ULONG Shift,
    _Reserved_ ULONG Flags
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
VOID
NTAPI
RtlDeleteHashTable(
    _In_ _When_((HashTable->Flags & RTL_HASH_ALLOCATED_HEADER), __drv_freesMem(Mem) _Post_invalid_)
    PRTL_DYNAMIC_HASH_TABLE HashTable
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
BOOLEAN
NTAPI
RtlInsertEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ __drv_aliasesMem PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
    _In_ ULONG_PTR Signature,
    _Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
BOOLEAN
NTAPI
RtlRemoveEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_ENTRY Entry,
    _Inout_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlLookupEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ ULONG_PTR Signature,
    _Out_opt_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlGetNextEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _In_ PRTL_DYNAMIC_HASH_TABLE_CONTEXT Context
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
BOOLEAN
NTAPI
RtlInitEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlEnumerateEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
VOID
NTAPI
RtlEndEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
BOOLEAN
NTAPI
RtlInitWeakEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlWeaklyEnumerateEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
VOID
NTAPI
RtlEndWeakEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
NTSYSAPI
BOOLEAN
NTAPI
RtlInitStrongEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Out_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_Must_inspect_result_
NTSYSAPI
PRTL_DYNAMIC_HASH_TABLE_ENTRY
NTAPI
RtlStronglyEnumerateEntryHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
NTSYSAPI
VOID
NTAPI
RtlEndStrongEnumerationHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable,
    _Inout_ PRTL_DYNAMIC_HASH_TABLE_ENUMERATOR Enumerator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
BOOLEAN
NTAPI
RtlExpandHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
BOOLEAN
NTAPI
RtlContractHashTable(
    _In_ PRTL_DYNAMIC_HASH_TABLE HashTable
);
#endif

#endif // !_KERNEL_MODE

//
// RB Trees
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
VOID
NTAPI
RtlRbInsertNodeEx(
    _In_ PRTL_RB_TREE Tree,
    _In_opt_ PRTL_BALANCED_NODE Parent,
    _In_ BOOLEAN Right,
    _Out_ PRTL_BALANCED_NODE Node
);

NTSYSAPI
VOID
NTAPI
RtlRbRemoveNode(
    _In_ PRTL_RB_TREE Tree,
    _In_ PRTL_BALANCED_NODE Node
);
#endif

#endif // !_KERNEL_MODE

//
// Critical sections
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeCriticalSection(
    _Out_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeCriticalSectionAndSpinCount(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_ ULONG SpinCount
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
NTSTATUS
NTAPI
RtlEnterCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
NTSTATUS
NTAPI
RtlLeaveCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
LOGICAL
NTAPI
RtlTryEnterCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
LOGICAL
NTAPI
RtlIsCriticalSectionLocked(
    _In_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
LOGICAL
NTAPI
RtlIsCriticalSectionLockedByThread(
    _In_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
ULONG
NTAPI
RtlGetCriticalSectionRecursionCount(
    _In_ PRTL_CRITICAL_SECTION CriticalSection
);

NTSYSAPI
ULONG
NTAPI
RtlSetCriticalSectionSpinCount(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_ ULONG SpinCount
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
HANDLE
NTAPI
RtlQueryCriticalSectionOwner(
    _In_ HANDLE EventHandle
);
#endif

NTSYSAPI
VOID
NTAPI
RtlCheckForOrphanedCriticalSections(
    _In_ HANDLE ThreadHandle
);

#endif // !_KERNEL_MODE

//
// Resources
//

#ifndef _KERNEL_MODE

typedef struct _RTL_RESOURCE
{
    RTL_CRITICAL_SECTION CriticalSection;

    HANDLE SharedSemaphore;
    volatile ULONG NumberOfWaitingShared;
    HANDLE ExclusiveSemaphore;
    volatile ULONG NumberOfWaitingExclusive;

    volatile LONG NumberOfActive; // negative: exclusive acquire; zero: not acquired; positive: shared acquire(s)
    HANDLE ExclusiveOwnerThread;

    ULONG Flags; // RTL_RESOURCE_FLAG_*

    PRTL_RESOURCE_DEBUG DebugInfo;
} RTL_RESOURCE, * PRTL_RESOURCE;

#define RTL_RESOURCE_FLAG_LONG_TERM ((ULONG)0x00000001)

NTSYSAPI
VOID
NTAPI
RtlInitializeResource(
    _Out_ PRTL_RESOURCE Resource
);

NTSYSAPI
VOID
NTAPI
RtlDeleteResource(
    _Inout_ PRTL_RESOURCE Resource
);

NTSYSAPI
BOOLEAN
NTAPI
RtlAcquireResourceShared(
    _Inout_ PRTL_RESOURCE Resource,
    _In_ BOOLEAN Wait
);

NTSYSAPI
BOOLEAN
NTAPI
RtlAcquireResourceExclusive(
    _Inout_ PRTL_RESOURCE Resource,
    _In_ BOOLEAN Wait
);

NTSYSAPI
VOID
NTAPI
RtlReleaseResource(
    _Inout_ PRTL_RESOURCE Resource
);

NTSYSAPI
VOID
NTAPI
RtlConvertSharedToExclusive(
    _Inout_ PRTL_RESOURCE Resource
);

NTSYSAPI
VOID
NTAPI
RtlConvertExclusiveToShared(
    _Inout_ PRTL_RESOURCE Resource
);

#endif // !_KERNEL_MODE

//
// Slim reader-writer locks, condition variables, and barriers
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// winbase:InitializeSRWLock
NTSYSAPI
VOID
NTAPI
RtlInitializeSRWLock(
    _Out_ PRTL_SRWLOCK SRWLock
);

// winbase:AcquireSRWLockExclusive
NTSYSAPI
VOID
NTAPI
RtlAcquireSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:AcquireSRWLockShared
NTSYSAPI
VOID
NTAPI
RtlAcquireSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:ReleaseSRWLockExclusive
NTSYSAPI
VOID
NTAPI
RtlReleaseSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:ReleaseSRWLockShared
NTSYSAPI
VOID
NTAPI
RtlReleaseSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:TryAcquireSRWLockExclusive
NTSYSAPI
BOOLEAN
NTAPI
RtlTryAcquireSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
);

// winbase:TryAcquireSRWLockShared
NTSYSAPI
BOOLEAN
NTAPI
RtlTryAcquireSRWLockShared(
    _Inout_ PRTL_SRWLOCK SRWLock
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
VOID
NTAPI
RtlAcquireReleaseSRWLockExclusive(
    _Inout_ PRTL_SRWLOCK SRWLock
);
#endif //(NTDDI_VERSION >= NTDDI_WIN7)

#endif //(NTDDI_VERSION >= NTDDI_VISTA)

#if (NTDDI_VERSION >= NTDDI_VISTA)
// winbase:InitializeConditionVariable
NTSYSAPI
VOID
NTAPI
RtlInitializeConditionVariable(
    _Out_ PRTL_CONDITION_VARIABLE ConditionVariable
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSleepConditionVariableCS(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable,
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_opt_ PLARGE_INTEGER Timeout
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSleepConditionVariableSRW(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable,
    _Inout_ PRTL_SRWLOCK SRWLock,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ ULONG Flags
);

// winbase:WakeConditionVariable
NTSYSAPI
VOID
NTAPI
RtlWakeConditionVariable(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable
);

// winbase:WakeAllConditionVariable
NTSYSAPI
VOID
NTAPI
RtlWakeAllConditionVariable(
    _Inout_ PRTL_CONDITION_VARIABLE ConditionVariable
);
#endif //(NTDDI_VERSION >= NTDDI_VISTA)

// begin_rev
#define RTL_BARRIER_FLAGS_SPIN_ONLY  0x00000001 // never block on event - always spin
#define RTL_BARRIER_FLAGS_BLOCK_ONLY 0x00000002 // always block on event - never spin
#define RTL_BARRIER_FLAGS_NO_DELETE  0x00000004 // use if barrier will never be deleted
// end_rev

// begin_private

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitBarrier(
    _Out_ PRTL_BARRIER Barrier,
    _In_ ULONG TotalThreads,
    _In_ ULONG SpinCount
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteBarrier(
    _In_ PRTL_BARRIER Barrier
);

NTSYSAPI
BOOLEAN
NTAPI
RtlBarrier(
    _Inout_ PRTL_BARRIER Barrier,
    _In_ ULONG Flags
);

NTSYSAPI
BOOLEAN
NTAPI
RtlBarrierForDelete(
    _Inout_ PRTL_BARRIER Barrier,
    _In_ ULONG Flags
);
#endif //(NTDDI_VERSION >= NTDDI_VISTA)

#endif // !_KERNEL_MODE

//
// Wait on address
//

#ifndef _KERNEL_MODE

// begin_rev
#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
NTSTATUS
NTAPI
RtlWaitOnAddress(
    _In_ volatile VOID* Address,
    _In_ PVOID CompareAddress,
    _In_ SIZE_T AddressSize,
    _In_opt_ PLARGE_INTEGER Timeout
);

NTSYSAPI
VOID
NTAPI
RtlWakeAddressAll(
    _In_ PVOID Address
);

NTSYSAPI
VOID
NTAPI
RtlWakeAddressSingle(
    _In_ PVOID Address
);
#endif
// end_rev

#endif // !_KERNEL_MODE


//
// Strings
//

#ifndef ANSI_STRING_MAX_BYTES
#define ANSI_STRING_MAX_BYTES ((USHORT)65535)
#endif // ANSI_STRING_MAX_BYTES

#ifndef ANSI_STRING_MAX_CHARS
#define ANSI_STRING_MAX_CHARS ANSI_STRING_MAX_BYTES
#endif

#include <strsafe.h>

#ifdef _KERNEL_MODE
#include <ntstrsafe.h>
#endif

#ifndef _KERNEL_MODE

_At_(AnsiString->Buffer, _Post_equal_to_(Buffer))
_At_(AnsiString->Length, _Post_equal_to_(0))
_At_(AnsiString->MaximumLength, _Post_equal_to_(BufferSize))
FORCEINLINE
VOID
RtlInitEmptyAnsiString(
    _Out_ PANSI_STRING AnsiString,
    _Pre_maybenull_ _Pre_readable_size_(BufferSize) __drv_aliasesMem PCHAR Buffer,
    _In_ USHORT BufferSize
)
{
    AnsiString->MaximumLength = BufferSize;
    AnsiString->Buffer = Buffer;
    AnsiString->Length = 0;
}

#endif // !_KERNEL_MODE

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlInitString(
    _Out_ PSTRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitStringEx(
    _Out_ PSTRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);
#endif

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlInitAnsiString(
    _Out_ PANSI_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitAnsiStringEx(
    _Out_ PANSI_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlFreeAnsiString(
    _Inout_ _At_(AnsiString->Buffer, _Frees_ptr_opt_)
    PANSI_STRING AnsiString
);

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlInitUTF8String(
    _Out_ PUTF8_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);

_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitUTF8StringEx(
    _Out_ PUTF8_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCSZ SourceString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlFreeUTF8String(
    _Inout_ _At_(utf8String->Buffer, _Frees_ptr_opt_)
    PUTF8_STRING utf8String
);
#endif

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlFreeOemString(
    _Inout_ _At_(OemString->Buffer, _Frees_ptr_opt_)
    POEM_STRING OemString
);

NTSYSAPI
VOID
NTAPI
RtlCopyString(
    _Out_ PSTRING DestinationString,
    _In_opt_ const STRING* SourceString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
CHAR
NTAPI
RtlUpperChar(
    _In_ CHAR Character
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareString(
    _In_ const STRING* String1,
    _In_ const STRING* String2,
    _In_ BOOLEAN CaseInSensitive
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualString(
    _In_ const STRING* String1,
    _In_ const STRING* String2,
    _In_ BOOLEAN CaseInSensitive
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlPrefixString(
    _In_ const STRING* String1,
    _In_ const STRING* String2,
    _In_ BOOLEAN CaseInSensitive
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAppendStringToString(
    _Inout_ PSTRING Destination,
    _In_ const STRING* Source
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAppendAsciizToString(
    _In_ PSTRING Destination,
    _In_opt_ PCSTR Source
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlUpperString(
    _Inout_ PSTRING DestinationString,
    _In_ const STRING* SourceString
);

FORCEINLINE
BOOLEAN
RtlIsNullOrEmptyUnicodeString(
    _In_opt_ PUNICODE_STRING String
)
{
    return !String || String->Length == 0;
}

#ifndef _KERNEL_MODE

_At_(UnicodeString->Buffer, _Post_equal_to_(Buffer))
_At_(UnicodeString->Length, _Post_equal_to_(0))
_At_(UnicodeString->MaximumLength, _Post_equal_to_(BufferSize))
FORCEINLINE
VOID
RtlInitEmptyUnicodeString(
    _Out_ PUNICODE_STRING UnicodeString,
    _Writable_bytes_(BufferSize)
    _When_(BufferSize != 0, _Notnull_)
    __drv_aliasesMem PWCHAR Buffer,
    _In_ USHORT BufferSize
)
{
    UnicodeString->Buffer = Buffer;
    UnicodeString->MaximumLength = BufferSize;
    UnicodeString->Length = 0;
}

#endif // !_KERNEL_MODE

_IRQL_requires_max_(DISPATCH_LEVEL)
_At_(DestinationString->Buffer, _Post_equal_to_(SourceString))
_At_(DestinationString->Length, _Post_equal_to_(_String_length_(SourceString) * sizeof(WCHAR)))
_At_(DestinationString->MaximumLength, _Post_equal_to_((_String_length_(SourceString) + 1) * sizeof(WCHAR)))
NTSYSAPI
VOID
NTAPI
RtlInitUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCWSTR SourceString
);

#ifndef RtlInitUnicodeStringEx
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitUnicodeStringEx(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ __drv_aliasesMem PCWSTR SourceString
);
#endif

_IRQL_requires_max_(APC_LEVEL)
_Success_(return != 0)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlCreateUnicodeString(
    _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem))
    PUNICODE_STRING DestinationString,
    _In_z_ PCWSTR SourceString
);

NTSYSAPI
BOOLEAN
NTAPI
RtlCreateUnicodeStringFromAsciiz(
    _Out_ PUNICODE_STRING DestinationString,
    _In_ PCSTR SourceString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlFreeUnicodeString(
    _Inout_ _At_(UnicodeString->Buffer, _Frees_ptr_opt_)
    PUNICODE_STRING UnicodeString
);

#ifndef _KERNEL_MODE
#define RTL_DUPLICATE_UNICODE_STRING_NULL_TERMINATE         (0x00000001)
#define RTL_DUPLICATE_UNICODE_STRING_ALLOCATE_NULL_STRING   (0x00000002)
#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlDuplicateUnicodeString(
    _In_ ULONG Flags,
    _In_ PCUNICODE_STRING StringIn,
    _Out_ _At_(StringOut->Buffer, __drv_allocatesMem(Mem))
    PUNICODE_STRING StringOut
);

_Unchanged_(DestinationString->Buffer)
_Unchanged_(DestinationString->MaximumLength)
_At_(DestinationString->Length,
    _When_(SourceString->Length > DestinationString->MaximumLength,
        _Post_equal_to_(DestinationString->MaximumLength))
    _When_(SourceString->Length <= DestinationString->MaximumLength,
        _Post_equal_to_(SourceString->Length)))
    NTSYSAPI
    VOID
    NTAPI
    RtlCopyUnicodeString(
        _Inout_ PUNICODE_STRING DestinationString,
        _In_opt_ PCUNICODE_STRING SourceString
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
WCHAR
NTAPI
RtlUpcaseUnicodeChar(
    _In_ WCHAR SourceCharacter
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
WCHAR
NTAPI
RtlDowncaseUnicodeChar(
    _In_ WCHAR SourceCharacter
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeString(
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeStrings(
    _In_reads_(String1Length) PCWCH String1,
    _In_ SIZE_T String1Length,
    _In_reads_(String2Length) PCWCH String2,
    _In_ SIZE_T String2Length,
    _In_ BOOLEAN CaseInSensitive
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualUnicodeString(
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
);

#ifndef _KERNEL_MODE
#define HASH_STRING_ALGORITHM_DEFAULT   (0)
#define HASH_STRING_ALGORITHM_X65599    (1)
#define HASH_STRING_ALGORITHM_INVALID   (0xffffffff)
#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlHashUnicodeString(
    _In_ PCUNICODE_STRING String,
    _In_ BOOLEAN CaseInSensitive,
    _In_ ULONG HashAlgorithm,
    _Out_ PULONG HashValue
);

_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlValidateUnicodeString(
    _Reserved_ ULONG Flags,
    _In_ PCUNICODE_STRING String
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlPrefixUnicodeString(
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
);

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlSuffixUnicodeString(
    _In_ PCUNICODE_STRING String1,
    _In_ PCUNICODE_STRING String2,
    _In_ BOOLEAN CaseInSensitive
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
_Must_inspect_result_
NTSYSAPI
PWCHAR
NTAPI
RtlFindUnicodeSubstring(
    _In_ PUNICODE_STRING FullString,
    _In_ PUNICODE_STRING SearchString,
    _In_ BOOLEAN CaseInSensitive
);
#endif

#define RTL_FIND_CHAR_IN_UNICODE_STRING_START_AT_END        0x00000001
#define RTL_FIND_CHAR_IN_UNICODE_STRING_COMPLEMENT_CHAR_SET 0x00000002
#define RTL_FIND_CHAR_IN_UNICODE_STRING_CASE_INSENSITIVE    0x00000004

_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlFindCharInUnicodeString(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING StringToSearch,
    _In_ PUNICODE_STRING CharSet,
    _Out_ PUSHORT NonInclusivePrefixLength
);

_Success_(1)
_Unchanged_(Destination->MaximumLength)
_Unchanged_(Destination->Buffer)
_When_(_Old_(Destination->Length) + Source->Length <= Destination->MaximumLength,
    _At_(Destination->Length,
        _Post_equal_to_(_Old_(Destination->Length) + Source->Length))
    _At_(return, _Out_range_(== , 0)))
    _When_(_Old_(Destination->Length) + Source->Length > Destination->MaximumLength,
        _Unchanged_(Destination->Length)
        _At_(return, _Out_range_(< , 0)))
    NTSYSAPI
    NTSTATUS
    NTAPI
    RtlAppendUnicodeStringToString(
        _Inout_ PUNICODE_STRING Destination,
        _In_ PCUNICODE_STRING Source
    );

_Success_(1)
_Unchanged_(Destination->MaximumLength)
_Unchanged_(Destination->Buffer)
_When_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(WCHAR) <= Destination->MaximumLength,
    _At_(Destination->Length,
        _Post_equal_to_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(WCHAR)))
    _At_(return, _Out_range_(== , 0)))
    _When_(_Old_(Destination->Length) + _String_length_(Source) * sizeof(WCHAR) > Destination->MaximumLength,
        _Unchanged_(Destination->Length)
        _At_(return, _Out_range_(< , 0)))
    NTSYSAPI
    NTSTATUS
    NTAPI
    RtlAppendUnicodeToString(
        _Inout_ PUNICODE_STRING Destination,
        _In_opt_z_ PCWSTR Source
    );

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSYSAPI
NTSTATUS
NTAPI
RtlDowncaseUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

NTSYSAPI
VOID
NTAPI
RtlEraseUnicodeString(
    _Inout_ PUNICODE_STRING String
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlAnsiStringToUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PCANSI_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_When_(AllocateDestinationString,
    _At_(DestinationString->MaximumLength,
        _Out_range_(<= , (SourceString->MaximumLength / sizeof(WCHAR)))))
    _When_(!AllocateDestinationString,
        _At_(DestinationString->Buffer, _Const_)
        _At_(DestinationString->MaximumLength, _Const_))
    _IRQL_requires_max_(PASSIVE_LEVEL)
    _When_(AllocateDestinationString, _Must_inspect_result_)
    NTSYSAPI
    NTSTATUS
    NTAPI
    RtlUnicodeStringToAnsiString(
        _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
        _When_(!AllocateDestinationString, _Inout_)
        PANSI_STRING DestinationString,
        _In_ PCUNICODE_STRING SourceString,
        _In_ BOOLEAN AllocateDestinationString
    );

#if (NTDDI_VERSION >= NTDDI_WIN7)
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlUTF8ToUnicodeN(
    _Out_writes_bytes_to_(UnicodeStringMaxByteCount, *UnicodeStringActualByteCount) PWSTR UnicodeStringDestination,
    _In_ ULONG UnicodeStringMaxByteCount,
    _Out_ PULONG UnicodeStringActualByteCount,
    _In_reads_bytes_(UTF8StringByteCount) PCCH UTF8StringSource,
    _In_ ULONG UTF8StringByteCount
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToUTF8N(
    _Out_writes_bytes_to_(UTF8StringMaxByteCount, *UTF8StringActualByteCount) PCHAR UTF8StringDestination,
    _In_ ULONG UTF8StringMaxByteCount,
    _Out_ PULONG UTF8StringActualByteCount,
    _In_reads_bytes_(UnicodeStringByteCount) PCWCH UnicodeStringSource,
    _In_ ULONG UnicodeStringByteCount
);

_When_(AllocateDestinationString,
    _At_(DestinationString->MaximumLength, _Out_range_(<= , (SourceString->MaximumLength / sizeof(WCHAR)))))
_When_(!AllocateDestinationString,
    _At_(DestinationString->Buffer, _Const_)
    _At_(DestinationString->MaximumLength, _Const_))
_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToUTF8String(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUTF8_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlUTF8StringToUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PUTF8_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

#if (NTDDI_VERSION < NTDDI_WIN10_VB)
_When_(AllocateDestinationString,
_At_(DestinationString->MaximumLength, _Out_range_(<= , (SourceString->MaximumLength / sizeof(WCHAR)))))
_When_(!AllocateDestinationString,
    _At_(DestinationString->Buffer, _Const_)
    _At_(DestinationString->MaximumLength, _Const_))
_IRQL_requires_max_(PASSIVE_LEVEL)
_When_(AllocateDestinationString, _Must_inspect_result_)
inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlUnicodeStringToUTF8String(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUTF8_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
)
{
    NTSTATUS Status = STATUS_SUCCESS;

    do
    {
        ULONG ActualByteCount = 0ul;

        Status = RtlUnicodeToUTF8N(NULL, 0, &ActualByteCount, SourceString->Buffer, SourceString->Length);
        if (ActualByteCount == 0ul)
        {
            break;
        }

        ActualByteCount += sizeof ANSI_NULL;

        if (ActualByteCount >= ANSI_STRING_MAX_BYTES)
        {
            return STATUS_INVALID_PARAMETER_2;
        }

        if (AllocateDestinationString)
        {
#ifdef _KERNEL_MODE
#pragma warning(suppress: 4996)
            DestinationString->Buffer = (PSTR)ExAllocatePool(PagedPool, ActualByteCount);
#else
            DestinationString->Buffer = (PSTR)LocalAlloc(LPTR, ActualByteCount);
#endif
            if (DestinationString->Buffer == NULL)
            {
                Status = STATUS_NO_MEMORY;
                break;
            }
            DestinationString->MaximumLength = (USHORT)ActualByteCount;

            RtlSecureZeroMemory(DestinationString->Buffer, ActualByteCount);
        }
        else
        {
            if (DestinationString->MaximumLength < ActualByteCount)
            {
                Status = STATUS_BUFFER_OVERFLOW;
                break;
            }
        }

        Status = RtlUnicodeToUTF8N(DestinationString->Buffer, DestinationString->MaximumLength, &ActualByteCount, SourceString->Buffer, SourceString->Length);
        if (!NT_SUCCESS(Status))
        {
            if (AllocateDestinationString)
            {
                RtlFreeAnsiString(DestinationString);
            }
            break;
        }

        if (ActualByteCount > DestinationString->MaximumLength)
        {
            Status = STATUS_BUFFER_OVERFLOW;
            break;
        }

        DestinationString->Length = (USHORT)ActualByteCount;
        DestinationString->Buffer[ActualByteCount / sizeof ANSI_NULL] = ANSI_NULL;

    } while (false);

    return Status;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlUTF8StringToUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PUTF8_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
)
{
    NTSTATUS Status = STATUS_SUCCESS;

    do
    {
        ULONG ActualByteCount = 0ul;

        Status = RtlUTF8ToUnicodeN(NULL, 0, &ActualByteCount, SourceString->Buffer, SourceString->Length);
        if (ActualByteCount == 0ul)
        {
            break;
        }

        ActualByteCount += sizeof UNICODE_NULL;

        if (ActualByteCount >= UNICODE_STRING_MAX_BYTES)
        {
            return STATUS_INVALID_PARAMETER_2;
        }

        if (AllocateDestinationString)
        {
#ifdef _KERNEL_MODE
#pragma warning(suppress: 4996)
            DestinationString->Buffer = (PWCH)ExAllocatePool(PagedPool, ActualByteCount);
#else
            DestinationString->Buffer = (PWCH)LocalAlloc(LPTR, ActualByteCount);
#endif
            if (DestinationString->Buffer == NULL)
            {
                Status = STATUS_NO_MEMORY;
                break;
            }
            DestinationString->MaximumLength = (USHORT)ActualByteCount;

            RtlSecureZeroMemory(DestinationString->Buffer, ActualByteCount);
        }
        else
        {
            if (DestinationString->MaximumLength < ActualByteCount)
            {
                Status = STATUS_BUFFER_OVERFLOW;
                break;
            }
        }

        Status = RtlUTF8ToUnicodeN(DestinationString->Buffer, DestinationString->MaximumLength, &ActualByteCount, SourceString->Buffer, SourceString->Length);
        if (!NT_SUCCESS(Status))
        {
            if (AllocateDestinationString)
            {
                RtlFreeUnicodeString(DestinationString);
            }
            break;
        }

        if (ActualByteCount > DestinationString->MaximumLength)
        {
            Status = STATUS_BUFFER_OVERFLOW;
            break;
        }

        DestinationString->Length = (USHORT)ActualByteCount;
        DestinationString->Buffer[ActualByteCount / sizeof UNICODE_NULL] = UNICODE_NULL;

    } while (false);

    return Status;
}

#if defined _M_IX86

_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlUnicodeStringToUTF8String@12, _VEIL_IMPL_RtlUnicodeStringToUTF8String);
_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlUTF8StringToUnicodeString@12, _VEIL_IMPL_RtlUTF8StringToUnicodeString);

#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64

_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlUnicodeStringToUTF8String, _VEIL_IMPL_RtlUnicodeStringToUTF8String);
_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlUTF8StringToUnicodeString, _VEIL_IMPL_RtlUTF8StringToUnicodeString);

#endif
#endif // if (NTDDI_VERSION < NTDDI_WIN10_VB)
#endif // if (NTDDI_VERSION >= NTDDI_WIN7)

NTSYSAPI
WCHAR
NTAPI
RtlAnsiCharToUnicodeChar(
    _Inout_ PUCHAR * SourceCharacter
);

NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToAnsiString(
    _Inout_ PANSI_STRING DestinationString,
    _In_ PUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlOemStringToUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PCOEM_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
_When_(AllocateDestinationString, _At_(DestinationString->Buffer, _Post_notnull_ __drv_allocatesMem(Mem)))
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToOemString(
    _When_(AllocateDestinationString, _Out_)
    _When_(!AllocateDestinationString, _Inout_)
    POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToOemString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlOemStringToCountedUnicodeString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    PUNICODE_STRING DestinationString,
    _In_ PCOEM_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToCountedOemString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeStringToCountedOemString(
    _When_(AllocateDestinationString, _Out_ _At_(DestinationString->Buffer, __drv_allocatesMem(Mem)))
    _When_(!AllocateDestinationString, _Inout_)
    POEM_STRING DestinationString,
    _In_ PCUNICODE_STRING SourceString,
    _In_ BOOLEAN AllocateDestinationString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlMultiByteToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) PCSTR MultiByteString,
    _In_ ULONG BytesInMultiByteString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlMultiByteToUnicodeSize(
    _Out_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) PCSTR MultiByteString,
    _In_ ULONG BytesInMultiByteString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToMultiByteN(
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToMultiByteSize(
    _Out_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeToMultiByteN(
    _Out_writes_bytes_to_(MaxBytesInMultiByteString, *BytesInMultiByteString) PCHAR MultiByteString,
    _In_ ULONG MaxBytesInMultiByteString,
    _Out_opt_ PULONG BytesInMultiByteString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlOemToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWSTR UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInOemString) PCCH OemString,
    _In_ ULONG BytesInOemString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToOemN(
    _Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
    _In_ ULONG MaxBytesInOemString,
    _Out_opt_ PULONG BytesInOemString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeToOemN(
    _Out_writes_bytes_to_(MaxBytesInOemString, *BytesInOemString) PCHAR OemString,
    _In_ ULONG MaxBytesInOemString,
    _Out_opt_ PULONG BytesInOemString,
    _In_reads_bytes_(BytesInUnicodeString) PCWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

NTSYSAPI
NTSTATUS
NTAPI
RtlConsoleMultiByteToUnicodeN(
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInMultiByteString) PCCH MultiByteString,
    _In_ ULONG BytesInMultiByteString,
    _Out_ PULONG pdwSpecialChar
);

//
//  String manipulation routines
//

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCustomCPToUnicodeN(
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInUnicodeString, *BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG MaxBytesInUnicodeString,
    _Out_opt_ PULONG BytesInUnicodeString,
    _In_reads_bytes_(BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG BytesInCustomCPString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeToCustomCPN(
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG MaxBytesInCustomCPString,
    _Out_opt_ PULONG BytesInCustomCPString,
    _In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUpcaseUnicodeToCustomCPN(
    _In_ PCPTABLEINFO CustomCP,
    _Out_writes_bytes_to_(MaxBytesInCustomCPString, *BytesInCustomCPString) PCH CustomCPString,
    _In_ ULONG MaxBytesInCustomCPString,
    _Out_opt_ PULONG BytesInCustomCPString,
    _In_reads_bytes_(BytesInUnicodeString) PWCH UnicodeString,
    _In_ ULONG BytesInUnicodeString
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlInitCodePageTable(
    _In_reads_opt_(2) PUSHORT TableBase,
    _Inout_ PCPTABLEINFO CodePageTable
);

#ifndef _KERNEL_MODE

NTSYSAPI
VOID
NTAPI
RtlInitNlsTables(
    _In_ PUSHORT AnsiNlsBase,
    _In_ PUSHORT OemNlsBase,
    _In_ PUSHORT LanguageNlsBase,
    _Out_ PNLSTABLEINFO TableInfo // PCPTABLEINFO?
);

NTSYSAPI
VOID
NTAPI
RtlResetRtlTranslations(
    _In_ PNLSTABLEINFO TableInfo
);

NTSYSAPI
BOOLEAN
NTAPI
RtlIsTextUnicode(
    _In_ PVOID Buffer,
    _In_ ULONG Size,
    _Inout_opt_ PULONG Result
);

#endif // !_KERNEL_MODE

typedef enum _RTL_NORM_FORM
{
    NormOther   = 0x0,
    NormC       = 0x1,
    NormD       = 0x2,
    NormKC      = 0x5,
    NormKD      = 0x6,
    NormIdna    = 0xd,
    DisallowUnassigned          = 0x100,
    NormCDisallowUnassigned     = 0x101,
    NormDDisallowUnassigned     = 0x102,
    NormKCDisallowUnassigned    = 0x105,
    NormKDDisallowUnassigned    = 0x106,
    NormIdnaDisallowUnassigned  = 0x10d
} RTL_NORM_FORM;

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlNormalizeString(
    _In_ ULONG NormForm, // RTL_NORM_FORM
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlIsNormalizedString(
    _In_ ULONG NormForm, // RTL_NORM_FORM
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_ PBOOLEAN Normalized
);
#endif

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN7)
// ntifs:FsRtlIsNameInExpression
NTSYSAPI
BOOLEAN
NTAPI
RtlIsNameInExpression(
    _In_ PUNICODE_STRING Expression,
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN IgnoreCase,
    _In_opt_ PWCH UpcaseTable
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
// ntifs:FsRtlIsNameInUnUpcasedExpression
NTSYSAPI
BOOLEAN
NTAPI
RtlIsNameInUnUpcasedExpression(
    _In_ PUNICODE_STRING Expression,
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN IgnoreCase,
    _In_opt_ PWCH UpcaseTable
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_19H1)
// ntifs:FsRtlDoesNameContainWildCards
NTSYSAPI
BOOLEAN
NTAPI
RtlDoesNameContainWildCards(
    _In_ PUNICODE_STRING Name
);
#endif

NTSYSAPI
BOOLEAN
NTAPI
RtlEqualDomainName(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2
);

NTSYSAPI
BOOLEAN
NTAPI
RtlEqualComputerName(
    _In_ PUNICODE_STRING String1,
    _In_ PUNICODE_STRING String2
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDnsHostNameToComputerName(
    _Out_ PUNICODE_STRING ComputerNameString,
    _In_ PUNICODE_STRING DnsHostNameString,
    _In_ BOOLEAN AllocateComputerNameString
);

#endif // !_KERNEL_MODE

#ifndef _KERNEL_MODE
#define RTL_GUID_STRING_SIZE 38
#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlStringFromGUID(
    _In_ REFGUID Guid,
    _Out_ _At_(GuidString->Buffer, __drv_allocatesMem(Mem))
    PUNICODE_STRING GuidString
);

#if (NTDDI_VERSION >= NTDDI_WINBLUE)

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlStringFromGUIDEx(
    _In_ PGUID Guid,
    _Inout_ PUNICODE_STRING GuidString,
    _In_ BOOLEAN AllocateGuidString
);

#endif

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlGUIDFromString(
    _In_ PCUNICODE_STRING GuidString,
    _Out_ GUID* Guid
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
LONG
NTAPI
RtlCompareAltitudes(
    _In_ PCUNICODE_STRING Altitude1,
    _In_ PCUNICODE_STRING Altitude2
);

NTSYSAPI
NTSTATUS
NTAPI
RtlIdnToAscii(
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlIdnToUnicode(
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlIdnToNameprepUnicode(
    _In_ ULONG Flags,
    _In_ PCWSTR SourceString,
    _In_ LONG SourceStringLength,
    _Out_writes_to_(*DestinationStringLength, *DestinationStringLength) PWSTR DestinationString,
    _Inout_ PLONG DestinationStringLength
);
#endif // NTDDI_VERSION >= NTDDI_VISTA

//
// Prefix
//

#ifndef _KERNEL_MODE

//
//  Prefix package types and procedures.
//
//  Note that the following two record structures should really be opaque
//  to the user of this package.  The only information about the two
//  structures available for the user should be the size and alignment
//  of the structures.
//

typedef struct _PREFIX_TABLE_ENTRY {
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct _PREFIX_TABLE_ENTRY* NextPrefixTree;
    RTL_SPLAY_LINKS Links;
    PSTRING Prefix;
} PREFIX_TABLE_ENTRY;
typedef PREFIX_TABLE_ENTRY* PPREFIX_TABLE_ENTRY;

typedef struct _PREFIX_TABLE {
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    PPREFIX_TABLE_ENTRY NextPrefixTree;
} PREFIX_TABLE;
typedef PREFIX_TABLE* PPREFIX_TABLE;

#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
PfxInitialize(
    _Out_ PPREFIX_TABLE PrefixTable
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
BOOLEAN
NTAPI
PfxInsertPrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ __drv_aliasesMem PSTRING Prefix,
    _Out_ PPREFIX_TABLE_ENTRY PrefixTableEntry
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
PfxRemovePrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PPREFIX_TABLE_ENTRY PrefixTableEntry
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
PPREFIX_TABLE_ENTRY
NTAPI
PfxFindPrefix(
    _In_ PPREFIX_TABLE PrefixTable,
    _In_ PSTRING FullName
);

#ifndef _KERNEL_MODE

//
//  The following definitions are for the unicode version of the prefix
//  package.
//

typedef struct _UNICODE_PREFIX_TABLE_ENTRY {
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    struct _UNICODE_PREFIX_TABLE_ENTRY* NextPrefixTree;
    struct _UNICODE_PREFIX_TABLE_ENTRY* CaseMatch;
    RTL_SPLAY_LINKS Links;
    PUNICODE_STRING Prefix;
} UNICODE_PREFIX_TABLE_ENTRY;
typedef UNICODE_PREFIX_TABLE_ENTRY* PUNICODE_PREFIX_TABLE_ENTRY;

typedef struct _UNICODE_PREFIX_TABLE {
    CSHORT NodeTypeCode;
    CSHORT NameLength;
    PUNICODE_PREFIX_TABLE_ENTRY NextPrefixTree;
    PUNICODE_PREFIX_TABLE_ENTRY LastNextEntry;
} UNICODE_PREFIX_TABLE;
typedef UNICODE_PREFIX_TABLE* PUNICODE_PREFIX_TABLE;

#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlInitializeUnicodePrefix(
    _Out_ PUNICODE_PREFIX_TABLE PrefixTable
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
BOOLEAN
NTAPI
RtlInsertUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ __drv_aliasesMem PUNICODE_STRING Prefix,
    _Out_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
VOID
NTAPI
RtlRemoveUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PUNICODE_PREFIX_TABLE_ENTRY PrefixTableEntry
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
PUNICODE_PREFIX_TABLE_ENTRY
NTAPI
RtlFindUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ PCUNICODE_STRING FullName,
    _In_ ULONG CaseInsensitiveIndex
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
PUNICODE_PREFIX_TABLE_ENTRY
NTAPI
RtlNextUnicodePrefix(
    _In_ PUNICODE_PREFIX_TABLE PrefixTable,
    _In_ BOOLEAN Restart
);

//
// Compression
//

#ifndef _KERNEL_MODE

//
//  Compression package types and procedures.
//

#define COMPRESSION_FORMAT_NONE          (0x0000)   // winnt
#define COMPRESSION_FORMAT_DEFAULT       (0x0001)   // winnt
#define COMPRESSION_FORMAT_LZNT1         (0x0002)   // winnt
#define COMPRESSION_FORMAT_XPRESS        (0x0003)   // winnt
#define COMPRESSION_FORMAT_XPRESS_HUFF   (0x0004)   // winnt
#define COMPRESSION_FORMAT_XP10          (0x0005)   // winnt
#define COMPRESSION_FORMAT_MAX           (0x0005)

#define COMPRESSION_ENGINE_STANDARD      (0x0000)   // winnt
#define COMPRESSION_ENGINE_MAXIMUM       (0x0100)   // winnt
#define COMPRESSION_ENGINE_HIBER         (0x0200)   // winnt
#define COMPRESSION_ENGINE_MAX           (0x0200)

#define COMPRESSION_FORMAT_MASK          (0x00FF)
#define COMPRESSION_ENGINE_MASK          (0xFF00)
#define COMPRESSION_FORMAT_ENGINE_MASK   (COMPRESSION_FORMAT_MASK |         \
                                          COMPRESSION_ENGINE_MASK)

//
//  Compressed Data Information structure.  This structure is
//  used to describe the state of a compressed data buffer,
//  whose uncompressed size is known.  All compressed chunks
//  described by this structure must be compressed with the
//  same format.  On compressed reads, this entire structure
//  is an output, and on compressed writes the entire structure
//  is an input.
//

typedef struct _COMPRESSED_DATA_INFO {

    //
    //  Code for the compression format (and engine) as
    //  defined in ntrtl.h.  Note that COMPRESSION_FORMAT_NONE
    //  and COMPRESSION_FORMAT_DEFAULT are invalid if
    //  any of the described chunks are compressed.
    //

    USHORT CompressionFormatAndEngine;

    //
    //  Since chunks and compression units are expected to be
    //  powers of 2 in size, we express then log2.  So, for
    //  example (1 << ChunkShift) == ChunkSizeInBytes.  The
    //  ClusterShift indicates how much space must be saved
    //  to successfully compress a compression unit - each
    //  successfully compressed compression unit must occupy
    //  at least one cluster less in bytes than an uncompressed
    //  compression unit.
    //

    UCHAR CompressionUnitShift;
    UCHAR ChunkShift;
    UCHAR ClusterShift;
    UCHAR Reserved;

    //
    //  This is the number of entries in the CompressedChunkSizes
    //  array.
    //

    USHORT NumberOfChunks;

    //
    //  This is an array of the sizes of all chunks resident
    //  in the compressed data buffer.  There must be one entry
    //  in this array for each chunk possible in the uncompressed
    //  buffer size.  A size of FSRTL_CHUNK_SIZE indicates the
    //  corresponding chunk is uncompressed and occupies exactly
    //  that size.  A size of 0 indicates that the corresponding
    //  chunk contains nothing but binary 0's, and occupies no
    //  space in the compressed data.  All other sizes must be
    //  less than FSRTL_CHUNK_SIZE, and indicate the exact size
    //  of the compressed data in bytes.
    //

    ULONG CompressedChunkSizes[ANYSIZE_ARRAY];

} COMPRESSED_DATA_INFO;
typedef COMPRESSED_DATA_INFO* PCOMPRESSED_DATA_INFO;

#endif // !_KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlGetCompressionWorkSpaceSize(
    _In_ USHORT CompressionFormatAndEngine,
    _Out_ PULONG CompressBufferWorkSpaceSize,
    _Out_ PULONG CompressFragmentWorkSpaceSize
);

NTSYSAPI
NTSTATUS
NTAPI
RtlCompressBuffer(
    _In_ USHORT CompressionFormatAndEngine,
    _In_reads_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _Out_writes_bytes_to_(CompressedBufferSize, *FinalCompressedSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_ ULONG UncompressedChunkSize,
    _Out_ PULONG FinalCompressedSize,
    _In_ PVOID WorkSpace
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressBuffer(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _Out_ PULONG FinalUncompressedSize
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressBufferEx(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _Out_ PULONG FinalUncompressedSize,
    _In_opt_ PVOID WorkSpace
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressBufferEx2(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedBufferSize, *FinalUncompressedSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_ ULONG UncompressedChunkSize,
    _Out_ PULONG FinalUncompressedSize,
    _In_opt_ PVOID WorkSpace
);
#endif

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressFragment(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedFragmentSize, *FinalUncompressedSize) PUCHAR UncompressedFragment,
    _In_ ULONG UncompressedFragmentSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_range_(< , CompressedBufferSize) ULONG FragmentOffset,
    _Out_ PULONG FinalUncompressedSize,
    _In_ PVOID WorkSpace
);

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressFragmentEx(
    _In_ USHORT CompressionFormat,
    _Out_writes_bytes_to_(UncompressedFragmentSize, *FinalUncompressedSize) PUCHAR UncompressedFragment,
    _In_ ULONG UncompressedFragmentSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_range_(< , CompressedBufferSize) ULONG FragmentOffset,
    _In_ ULONG UncompressedChunkSize,
    _Out_ PULONG FinalUncompressedSize,
    _In_ PVOID WorkSpace
);
#endif

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDescribeChunk(
    _In_ USHORT CompressionFormat,
    _Inout_ PUCHAR* CompressedBuffer,
    _In_ PUCHAR EndOfCompressedBufferPlus1,
    _Out_ PUCHAR* ChunkBuffer,
    _Out_ PULONG ChunkSize
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlReserveChunk(
    _In_ USHORT CompressionFormat,
    _Inout_ PUCHAR* CompressedBuffer,
    _In_ PUCHAR EndOfCompressedBufferPlus1,
    _Out_ PUCHAR* ChunkBuffer,
    _In_ ULONG ChunkSize
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDecompressChunks(
    _Out_writes_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _In_reads_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_ ULONG CompressedBufferSize,
    _In_reads_bytes_(CompressedTailSize) PUCHAR CompressedTail,
    _In_ ULONG CompressedTailSize,
    _In_ PCOMPRESSED_DATA_INFO CompressedDataInfo
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCompressChunks(
    _In_reads_bytes_(UncompressedBufferSize) PUCHAR UncompressedBuffer,
    _In_ ULONG UncompressedBufferSize,
    _Out_writes_bytes_(CompressedBufferSize) PUCHAR CompressedBuffer,
    _In_range_(>= , (UncompressedBufferSize - (UncompressedBufferSize / 16))) ULONG CompressedBufferSize,
    _Inout_updates_bytes_(CompressedDataInfoLength) PCOMPRESSED_DATA_INFO CompressedDataInfo,
    _In_range_(> , sizeof(COMPRESSED_DATA_INFO)) ULONG CompressedDataInfoLength,
    _In_ PVOID WorkSpace
);

//
// Locale
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlConvertLCIDToString(
    _In_ LCID LcidValue,
    _In_ ULONG Base,
    _In_ ULONG Padding, // string is padded to this width
    _Out_writes_(Size) PWSTR pResultBuf,
    _In_ ULONG Size
);

// private
NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidLocaleName(
    _In_ PCWSTR LocaleName,
    _In_ ULONG Flags
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlGetParentLocaleName(
    _In_ PCWSTR LocaleName,
    _Inout_ PUNICODE_STRING ParentLocaleName,
    _In_ ULONG Flags,
    _In_ BOOLEAN AllocateDestinationString
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLcidToLocaleName(
    _In_ LCID lcid, // sic
    _Inout_ PUNICODE_STRING LocaleName,
    _In_ ULONG Flags,
    _In_ BOOLEAN AllocateDestinationString
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLocaleNameToLcid(
    _In_ PCWSTR LocaleName,
    _Out_ PLCID lcid,
    _In_ ULONG Flags
);

// private
NTSYSAPI
BOOLEAN
NTAPI
RtlLCIDToCultureName(
    _In_ LCID Lcid,
    _Inout_ PUNICODE_STRING String
);

// private
NTSYSAPI
BOOLEAN
NTAPI
RtlCultureNameToLCID(
    _In_ PUNICODE_STRING String,
    _Out_ PLCID Lcid
);

// private
NTSYSAPI
VOID
NTAPI
RtlCleanUpTEBLangLists(
    VOID
);

#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetLocaleFileMappingAddress(
    _Out_ PVOID* BaseAddress,
    _Out_ PLCID DefaultLocaleId,
    _Out_ PLARGE_INTEGER DefaultCasingTableSize
);
#endif

#endif // !_KERNEL_MODE

//
// PEB
//

#ifndef _KERNEL_MODE

NTSYSAPI
PPEB
NTAPI
RtlGetCurrentPeb(
    VOID
);

NTSYSAPI
VOID
NTAPI
RtlAcquirePebLock(
    VOID
);

NTSYSAPI
VOID
NTAPI
RtlReleasePebLock(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
LOGICAL
NTAPI
RtlTryAcquirePebLock(
    VOID
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateFromPeb(
    _In_ ULONG Size,
    _Out_ PVOID* Block
);

NTSYSAPI
NTSTATUS
NTAPI
RtlFreeToPeb(
    _In_ PVOID Block,
    _In_ ULONG Size
);

#endif // !_KERNEL_MODE

//
// Processes
//

#define DOS_MAX_COMPONENT_LENGTH 255
#define DOS_MAX_PATH_LENGTH (DOS_MAX_COMPONENT_LENGTH + 5)

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, * PCURDIR;

#define RTL_USER_PROC_CURDIR_CLOSE      0x00000002
#define RTL_USER_PROC_CURDIR_INHERIT    0x00000003

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

#define RTL_MAX_DRIVE_LETTERS 32
#define RTL_DRIVE_LETTER_VALID (USHORT)0x0001

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;

    ULONG Flags;
    ULONG DebugFlags;

    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;

    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    PVOID Environment;

    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;

    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

    ULONG_PTR EnvironmentSize;
    ULONG_PTR EnvironmentVersion;

    PVOID PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;

    UNICODE_STRING RedirectionDllName; // REDSTONE4
    UNICODE_STRING HeapPartitionName; // 19H1
    ULONG_PTR DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

#define RTL_USER_PROC_PARAMS_NORMALIZED     0x00000001
#define RTL_USER_PROC_PROFILE_USER          0x00000002
#define RTL_USER_PROC_PROFILE_KERNEL        0x00000004
#define RTL_USER_PROC_PROFILE_SERVER        0x00000008
#define RTL_USER_PROC_RESERVE_1MB           0x00000020
#define RTL_USER_PROC_RESERVE_16MB          0x00000040
#define RTL_USER_PROC_CASE_SENSITIVE        0x00000080
#define RTL_USER_PROC_DISABLE_HEAP_DECOMMIT 0x00000100
#define RTL_USER_PROC_DLL_REDIRECTION_LOCAL 0x00001000
#define RTL_USER_PROC_APP_MANIFEST_PRESENT  0x00002000
#define RTL_USER_PROC_IMAGE_KEY_MISSING     0x00004000
#define RTL_USER_PROC_OPTIN_PROCESS         0x00020000

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateProcessParameters(
    _Out_ PRTL_USER_PROCESS_PARAMETERS* pProcessParameters,
    _In_ PUNICODE_STRING ImagePathName,
    _In_opt_ PUNICODE_STRING DllPath,
    _In_opt_ PUNICODE_STRING CurrentDirectory,
    _In_opt_ PUNICODE_STRING CommandLine,
    _In_opt_ PVOID Environment,
    _In_opt_ PUNICODE_STRING WindowTitle,
    _In_opt_ PUNICODE_STRING DesktopInfo,
    _In_opt_ PUNICODE_STRING ShellInfo,
    _In_opt_ PUNICODE_STRING RuntimeData
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateProcessParametersEx(
    _Out_ PRTL_USER_PROCESS_PARAMETERS* pProcessParameters,
    _In_ PUNICODE_STRING ImagePathName,
    _In_opt_ PUNICODE_STRING DllPath,
    _In_opt_ PUNICODE_STRING CurrentDirectory,
    _In_opt_ PUNICODE_STRING CommandLine,
    _In_opt_ PVOID Environment,
    _In_opt_ PUNICODE_STRING WindowTitle,
    _In_opt_ PUNICODE_STRING DesktopInfo,
    _In_opt_ PUNICODE_STRING ShellInfo,
    _In_opt_ PUNICODE_STRING RuntimeData,
    _In_ ULONG Flags // pass RTL_USER_PROC_PARAMS_NORMALIZED to keep parameters normalized
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyProcessParameters(
    _In_ _Post_invalid_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
);

NTSYSAPI
PRTL_USER_PROCESS_PARAMETERS
NTAPI
RtlNormalizeProcessParams(
    _Inout_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
);

NTSYSAPI
PRTL_USER_PROCESS_PARAMETERS
NTAPI
RtlDeNormalizeProcessParams(
    _Inout_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters
);

typedef struct _RTL_USER_PROCESS_INFORMATION
{
    ULONG Length;
    HANDLE ProcessHandle;
    HANDLE ThreadHandle;
    CLIENT_ID ClientId;
    struct _SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, * PRTL_USER_PROCESS_INFORMATION;

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserProcess(
    _In_ PUNICODE_STRING NtImagePathName,
    _In_ ULONG AttributesDeprecated,
    _In_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    _In_opt_ PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_opt_ HANDLE ParentProcess,
    _In_ BOOLEAN InheritHandles,
    _In_opt_ HANDLE DebugPort,
    _In_opt_ HANDLE TokenHandle, // used to be ExceptionPort
    _Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
);

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
#define RTL_USER_PROCESS_EXTENDED_PARAMETERS_VERSION 1

// private
typedef struct _RTL_USER_PROCESS_EXTENDED_PARAMETERS
{
    USHORT Version;
    USHORT NodeNumber;
    PSECURITY_DESCRIPTOR ProcessSecurityDescriptor;
    PSECURITY_DESCRIPTOR ThreadSecurityDescriptor;
    HANDLE ParentProcess;
    HANDLE DebugPort;
    HANDLE TokenHandle;
    HANDLE JobHandle;
} RTL_USER_PROCESS_EXTENDED_PARAMETERS, * PRTL_USER_PROCESS_EXTENDED_PARAMETERS;

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserProcessEx(
    _In_ PUNICODE_STRING NtImagePathName,
    _In_ PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    _In_ BOOLEAN InheritHandles,
    _In_opt_ PRTL_USER_PROCESS_EXTENDED_PARAMETERS ProcessExtendedParameters,
    _Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
DECLSPEC_NORETURN
NTSYSAPI
VOID
NTAPI
RtlExitUserProcess(
    _In_ NTSTATUS ExitStatus
);
#else
#define RtlExitUserProcess RtlExitUserProcess_R

DECLSPEC_NORETURN
FORCEINLINE VOID RtlExitUserProcess_R(
    _In_ NTSTATUS ExitStatus
)
{
    ExitProcess(ExitStatus);
}
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// begin_rev
#define RTL_CLONE_PROCESS_FLAGS_CREATE_SUSPENDED    0x00000001
#define RTL_CLONE_PROCESS_FLAGS_INHERIT_HANDLES     0x00000002
#define RTL_CLONE_PROCESS_FLAGS_NO_SYNCHRONIZE      0x00000004 // don't update synchronization objects
// end_rev

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCloneUserProcess(
    _In_ ULONG ProcessFlags,
    _In_opt_ PSECURITY_DESCRIPTOR ProcessSecurityDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_opt_ HANDLE DebugPort,
    _Out_ PRTL_USER_PROCESS_INFORMATION ProcessInformation
);

// private
NTSYSAPI
VOID
NTAPI
RtlUpdateClonedCriticalSection(
    _Inout_ PRTL_CRITICAL_SECTION CriticalSection
);

// private
NTSYSAPI
VOID
NTAPI
RtlUpdateClonedSRWLock(
    _Inout_ PRTL_SRWLOCK SRWLock,
    _In_ LOGICAL Shared // TRUE to set to shared acquire
);
#endif

// rev
#define RTL_PROCESS_REFLECTION_FLAGS_INHERIT_HANDLES    0x2
#define RTL_PROCESS_REFLECTION_FLAGS_NO_SUSPEND         0x4
#define RTL_PROCESS_REFLECTION_FLAGS_NO_SYNCHRONIZE     0x8
#define RTL_PROCESS_REFLECTION_FLAGS_NO_CLOSE_EVENT     0x10

// private
typedef struct _RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION
{
    HANDLE ReflectionProcessHandle;
    HANDLE ReflectionThreadHandle;
    CLIENT_ID ReflectionClientId;
} RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION, * PRTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION;

typedef RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION PROCESS_REFLECTION_INFORMATION, * PPROCESS_REFLECTION_INFORMATION;

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateProcessReflection(
    _In_ HANDLE ProcessHandle,
    _In_ ULONG Flags, // RTL_PROCESS_REFLECTION_FLAGS_*
    _In_opt_ PVOID StartRoutine,
    _In_opt_ PVOID StartContext,
    _In_opt_ HANDLE EventHandle,
    _Out_opt_ PRTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION ReflectionInformation
);
#endif

NTSYSAPI
NTSTATUS
STDAPIVCALLTYPE
RtlSetProcessIsCritical(
    _In_ BOOLEAN NewValue,
    _Out_opt_ PBOOLEAN OldValue,
    _In_ BOOLEAN CheckFlag
);

NTSYSAPI
NTSTATUS
STDAPIVCALLTYPE
RtlSetThreadIsCritical(
    _In_ BOOLEAN NewValue,
    _Out_opt_ PBOOLEAN OldValue,
    _In_ BOOLEAN CheckFlag
);

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlValidProcessProtection(
    _In_ struct _PS_PROTECTION ProcessProtection
);

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlTestProtectedAccess(
    _In_ struct _PS_PROTECTION Source,
    _In_ struct _PS_PROTECTION Target
);

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCurrentProcess( // NtCompareObjects(NtCurrentProcess(), ProcessHandle)
    _In_ HANDLE ProcessHandle
);

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCurrentThread( // NtCompareObjects(NtCurrentThread(), ThreadHandle)
    _In_ HANDLE ThreadHandle
);
#endif

// KernelBase.dll
NTSYSAPI
BOOL
WINAPI
CreateProcessInternalA(
    _In_opt_ HANDLE hUserToken,
    _In_opt_ LPWSTR lpApplicationName,
    _Inout_opt_ LPSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOA lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation,
    _Out_opt_ PHANDLE hNewToken
);

NTSYSAPI
BOOL
WINAPI
CreateProcessInternalW(
    _In_opt_ HANDLE hUserToken,
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation,
    _Out_opt_ PHANDLE hNewToken
);

#endif // !_KERNEL_MODE

//
// Threads
//

#ifndef _KERNEL_MODE

typedef NTSTATUS(NTAPI* PUSER_THREAD_START_ROUTINE)(
    _In_ PVOID ThreadParameter
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserThread(
    _In_ HANDLE Process,
    _In_opt_ PSECURITY_DESCRIPTOR ThreadSecurityDescriptor,
    _In_ BOOLEAN CreateSuspended,
    _In_opt_ ULONG ZeroBits,
    _In_opt_ SIZE_T MaximumStackSize,
    _In_opt_ SIZE_T CommittedStackSize,
    _In_ PUSER_THREAD_START_ROUTINE StartAddress,
    _In_opt_ PVOID Parameter,
    _Out_opt_ PHANDLE Thread,
    _Out_opt_ PCLIENT_ID ClientId
);

#if (NTDDI_VERSION >= NTDDI_VISTA) // should be NTDDI_WINXP, but is NTDDI_VISTA for consistency with RtlExitUserProcess
DECLSPEC_NORETURN
NTSYSAPI
VOID
NTAPI
RtlExitUserThread(
    _In_ NTSTATUS ExitStatus
);
#else
#define RtlExitUserThread RtlExitUserThread_R

DECLSPEC_NORETURN
FORCEINLINE VOID RtlExitUserThread_R(
    _In_ NTSTATUS ExitStatus
)
{
    ExitThread(ExitStatus);
}
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCurrentThreadAttachExempt(
    VOID
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserStack(
    _In_opt_ SIZE_T CommittedStackSize,
    _In_opt_ SIZE_T MaximumStackSize,
    _In_opt_ ULONG_PTR ZeroBits,
    _In_ SIZE_T PageSize,
    _In_ ULONG_PTR ReserveAlignment,
    _Out_ struct _INITIAL_TEB* InitialTeb
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlFreeUserStack(
    _In_ PVOID AllocationBase
);
#endif

#endif // !_KERNEL_MODE

//
// Extended thread context
//

#ifndef _KERNEL_MODE

typedef struct _CONTEXT_CHUNK
{
    LONG Offset; // Offset may be negative.
    ULONG Length;
} CONTEXT_CHUNK, * PCONTEXT_CHUNK;

typedef struct _CONTEXT_EX
{
    CONTEXT_CHUNK All;
    CONTEXT_CHUNK Legacy;
    CONTEXT_CHUNK XState;
} CONTEXT_EX, * PCONTEXT_EX;

#define CONTEXT_EX_LENGTH ALIGN_UP_BY(sizeof(CONTEXT_EX), PAGE_SIZE)
#define RTL_CONTEXT_EX_OFFSET(ContextEx, Chunk) ((ContextEx)->Chunk.Offset)
#define RTL_CONTEXT_EX_LENGTH(ContextEx, Chunk) ((ContextEx)->Chunk.Length)
#define RTL_CONTEXT_EX_CHUNK(Base, Layout, Chunk) ((PVOID)((PCHAR)(Base) + RTL_CONTEXT_EX_OFFSET(Layout, Chunk)))
#define RTL_CONTEXT_OFFSET(Context, Chunk) RTL_CONTEXT_EX_OFFSET((PCONTEXT_EX)(Context + 1), Chunk)
#define RTL_CONTEXT_LENGTH(Context, Chunk) RTL_CONTEXT_EX_LENGTH((PCONTEXT_EX)(Context + 1), Chunk)
#define RTL_CONTEXT_CHUNK(Context, Chunk) RTL_CONTEXT_EX_CHUNK((PCONTEXT_EX)(Context + 1), (PCONTEXT_EX)(Context + 1), Chunk)

NTSYSAPI
VOID
NTAPI
RtlInitializeContext(
    _In_ HANDLE Process,
    _Out_ PCONTEXT Context,
    _In_opt_ PVOID Parameter,
    _In_opt_ PVOID InitialPc,
    _In_opt_ PVOID InitialSp
);

NTSYSAPI
NTSTATUS
NTAPI
RtlCopyContext(
    _Inout_ PCONTEXT Context,
    _In_ ULONG ContextFlags,
    _Out_ PCONTEXT Source
);

NTSYSAPI
ULONG
NTAPI
RtlInitializeExtendedContext(
    _Out_ PCONTEXT Context,
    _In_ ULONG ContextFlags,
    _Out_ PCONTEXT_EX* ContextEx
);

NTSYSAPI
ULONG
NTAPI
RtlCopyExtendedContext(
    _Out_ PCONTEXT_EX Destination,
    _In_ ULONG ContextFlags,
    _In_ PCONTEXT_EX Source
);

NTSYSAPI
ULONG
NTAPI
RtlGetExtendedContextLength(
    _In_ ULONG ContextFlags,
    _Out_ PULONG ContextLength
);

NTSYSAPI
ULONG64
NTAPI
RtlGetExtendedFeaturesMask(
    _In_ PCONTEXT_EX ContextEx
);

NTSYSAPI
PVOID
NTAPI
RtlLocateExtendedFeature(
    _In_ PCONTEXT_EX ContextEx,
    _In_ ULONG FeatureId,
    _Out_opt_ PULONG Length
);

NTSYSAPI
PCONTEXT
NTAPI
RtlLocateLegacyContext(
    _In_ PCONTEXT_EX ContextEx,
    _Out_opt_ PULONG Length
);

NTSYSAPI
VOID
NTAPI
RtlSetExtendedFeaturesMask(
    _In_ PCONTEXT_EX ContextEx,
    _In_ ULONG64 FeatureMask
);

#ifdef _WIN64
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlWow64GetThreadContext(
    _In_ HANDLE ThreadHandle,
    _Inout_ PWOW64_CONTEXT ThreadContext
);
#endif

#ifdef _WIN64
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlWow64SetThreadContext(
    _In_ HANDLE ThreadHandle,
    _In_ PWOW64_CONTEXT ThreadContext
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlRemoteCall(
    _In_ HANDLE Process,
    _In_ HANDLE Thread,
    _In_ PVOID CallSite,
    _In_ ULONG ArgumentCount,
    _In_opt_ PULONG_PTR Arguments,
    _In_ BOOLEAN PassContext,
    _In_ BOOLEAN AlreadySuspended
);

#endif // !_KERNEL_MODE

//
// Vectored exception handlers
//

#ifndef _KERNEL_MODE

NTSYSAPI
PVOID
NTAPI
RtlAddVectoredExceptionHandler(
    _In_ ULONG First,
    _In_ PVECTORED_EXCEPTION_HANDLER Handler
);

NTSYSAPI
ULONG
NTAPI
RtlRemoveVectoredExceptionHandler(
    _In_ PVOID Handle
);

NTSYSAPI
PVOID
NTAPI
RtlAddVectoredContinueHandler(
    _In_ ULONG First,
    _In_ PVECTORED_EXCEPTION_HANDLER Handler
);

NTSYSAPI
ULONG
NTAPI
RtlRemoveVectoredContinueHandler(
    _In_ PVOID Handle
);

#endif // !_KERNEL_MODE

//
// Runtime exception handling
//

#if defined(_ARM_)
typedef struct _IMAGE_ARM_RUNTIME_FUNCTION_ENTRY RUNTIME_FUNCTION, * PRUNTIME_FUNCTION;
#elif defined(_ARM64_)
typedef struct _IMAGE_ARM64_RUNTIME_FUNCTION_ENTRY RUNTIME_FUNCTION, * PRUNTIME_FUNCTION;
#elif defined(_AMD64_)
typedef struct _IMAGE_RUNTIME_FUNCTION_ENTRY RUNTIME_FUNCTION, * PRUNTIME_FUNCTION;
#endif

#ifndef _KERNEL_MODE

typedef ULONG(NTAPI* PRTLP_UNHANDLED_EXCEPTION_FILTER)(
    _In_ PEXCEPTION_POINTERS ExceptionInfo
    );

NTSYSAPI
VOID
NTAPI
RtlSetUnhandledExceptionFilter(
    _In_ PRTLP_UNHANDLED_EXCEPTION_FILTER UnhandledExceptionFilter
);

// rev
NTSYSAPI
LONG
NTAPI
RtlUnhandledExceptionFilter(
    _In_ PEXCEPTION_POINTERS ExceptionPointers
);

// rev
NTSYSAPI
LONG
NTAPI
RtlUnhandledExceptionFilter2(
    _In_ PEXCEPTION_POINTERS ExceptionPointers,
    _In_ ULONG Flags
);

// rev
NTSYSAPI
LONG
NTAPI
RtlKnownExceptionFilter(
    _In_ PEXCEPTION_POINTERS ExceptionPointers
);

NTSYSAPI
BOOLEAN
NTAPI
RtlDispatchException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord
);

NTSYSAPI
DECLSPEC_NORETURN
VOID
NTAPI
RtlRaiseStatus(
    _In_ NTSTATUS Status
);

NTSYSAPI
__analysis_noreturn
VOID
NTAPI
RtlAssert(
    _In_ PVOID VoidFailedAssertion,
    _In_ PVOID VoidFileName,
    _In_ ULONG LineNumber,
    _In_opt_ PSTR MutableMessage
);

#if DBG

#define ASSERT( exp ) \
    ((!(exp)) ? \
        (RtlAssert( (PVOID)#exp, (PVOID)__FILE__, __LINE__, NULL ),FALSE) : \
        TRUE)

#define ASSERTMSG( msg, exp ) \
    ((!(exp)) ? \
        (RtlAssert( (PVOID)#exp, (PVOID)__FILE__, __LINE__, msg ),FALSE) : \
        TRUE)

#define RTL_SOFT_ASSERT(_exp) \
    ((!(_exp)) ? \
        (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n", __FILE__, __LINE__, #_exp),FALSE) : \
        TRUE)

#define RTL_SOFT_ASSERTMSG(_msg, _exp) \
    ((!(_exp)) ? \
        (DbgPrint("%s(%d): Soft assertion failed\n   Expression: %s\n   Message: %s\n", __FILE__, __LINE__, #_exp, (_msg)),FALSE) : \
        TRUE)

#define RTL_VERIFY         ASSERT
#define RTL_VERIFYMSG      ASSERTMSG

#define RTL_SOFT_VERIFY    RTL_SOFT_ASSERT
#define RTL_SOFT_VERIFYMSG RTL_SOFT_ASSERTMSG

#else
#define ASSERT( exp )         ((void) 0)
#define ASSERTMSG( msg, exp ) ((void) 0)

#define RTL_SOFT_ASSERT(_exp)          ((void) 0)
#define RTL_SOFT_ASSERTMSG(_msg, _exp) ((void) 0)

#define RTL_VERIFY( exp )         ((exp) ? TRUE : FALSE)
#define RTL_VERIFYMSG( msg, exp ) ((exp) ? TRUE : FALSE)

#define RTL_SOFT_VERIFY(_exp)         ((_exp) ? TRUE : FALSE)
#define RTL_SOFT_VERIFYMSG(msg, _exp) ((_exp) ? TRUE : FALSE)

#endif // DBG

#ifdef _WIN64
// private
typedef enum _FUNCTION_TABLE_TYPE
{
    RF_SORTED,
    RF_UNSORTED,
    RF_CALLBACK,
    RF_KERNEL_DYNAMIC
} FUNCTION_TABLE_TYPE;

// private
typedef struct _DYNAMIC_FUNCTION_TABLE
{
    LIST_ENTRY ListEntry;
    PRUNTIME_FUNCTION FunctionTable;
    LARGE_INTEGER TimeStamp;
    ULONG64 MinimumAddress;
    ULONG64 MaximumAddress;
    ULONG64 BaseAddress;
    PGET_RUNTIME_FUNCTION_CALLBACK Callback;
    PVOID Context;
    PWSTR OutOfProcessCallbackDll;
    FUNCTION_TABLE_TYPE Type;
    ULONG EntryCount;
    RTL_BALANCED_NODE TreeNodeMin;
    RTL_BALANCED_NODE TreeNodeMax;
} DYNAMIC_FUNCTION_TABLE, * PDYNAMIC_FUNCTION_TABLE;

// rev
NTSYSAPI
PLIST_ENTRY
NTAPI
RtlGetFunctionTableListHead(
    VOID
);
#endif // _WIN64

// Activation Contexts

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetActiveActivationContext(
    _Out_ HANDLE ActCtx
);

// rev
NTSYSAPI
VOID
NTAPI
RtlAddRefActivationContext(
    _In_ HANDLE ActCtx
);

// rev
NTSYSAPI
VOID
NTAPI
RtlReleaseActivationContext(
    _In_ HANDLE ActCtx
);

// kernel32!FindActCtxSectionString
NTSYSAPI
NTSTATUS
NTAPI
RtlFindActivationContextSectionString(
    _In_ ULONG Flags,
    _In_ const GUID* ExtensionGuid,
    _In_ ULONG SectionId,
    _In_ const UNICODE_STRING* StringToFind,
    _Out_ PACTCTX_SECTION_KEYED_DATA ReturnedData
);

#endif // !_KERNEL_MODE

//
// Images
//

NTSYSAPI
PIMAGE_NT_HEADERS
NTAPI
RtlImageNtHeader(
    _In_ PVOID BaseOfImage
);

#define RTL_IMAGE_NT_HEADER_EX_FLAG_NO_RANGE_CHECK 0x00000001

NTSYSAPI
NTSTATUS
NTAPI
RtlImageNtHeaderEx(
    _In_ ULONG Flags,
    _In_ PVOID BaseOfImage,
    _In_ ULONG64 Size,
    _Out_ PIMAGE_NT_HEADERS* OutHeaders
);

#ifndef _KERNEL_MODE

NTSYSAPI
PVOID
NTAPI
RtlAddressInSectionTable(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG VirtualAddress
);

NTSYSAPI
PIMAGE_SECTION_HEADER
NTAPI
RtlSectionTableFromVirtualAddress(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG VirtualAddress
);

#endif // !_KERNEL_MODE

NTSYSAPI
PVOID
NTAPI
RtlImageDirectoryEntryToData(
    _In_ PVOID BaseOfImage,
    _In_ BOOLEAN MappedAsImage,
    _In_ USHORT DirectoryEntry,
    _Out_ PULONG Size
);

NTSYSAPI
PIMAGE_SECTION_HEADER
NTAPI
RtlImageRvaToSection(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG Rva
);

NTSYSAPI
PVOID
NTAPI
RtlImageRvaToVa(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG Rva,
    _Inout_opt_ PIMAGE_SECTION_HEADER* LastRvaSection
);

#ifdef _KERNEL_MODE
inline
PIMAGE_SECTION_HEADER
NTAPI
_VEIL_IMPL_RtlImageRvaToSection(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG Rva
)
{
    ULONG i = 0ul;
    PIMAGE_SECTION_HEADER NtSection = NULL;

    UNREFERENCED_PARAMETER(BaseOfImage);

    NtSection = IMAGE_FIRST_SECTION(NtHeaders);
    for (i = 0; i < NtHeaders->FileHeader.NumberOfSections; i++) {
        if (Rva >= NtSection->VirtualAddress &&
            Rva < NtSection->VirtualAddress + NtSection->SizeOfRawData
            ) {
            return NtSection;
        }
        ++NtSection;
    }

    return NULL;
}

inline
PVOID
NTAPI
_VEIL_IMPL_RtlImageRvaToVa(
    _In_ PIMAGE_NT_HEADERS NtHeaders,
    _In_ PVOID BaseOfImage,
    _In_ ULONG Rva,
    _Inout_opt_ PIMAGE_SECTION_HEADER* LastRvaSection
)
{
    PIMAGE_SECTION_HEADER NtSection = NULL;

    if (LastRvaSection != NULL)
    {
        NtSection = *LastRvaSection;
    }

    if ((NtSection == NULL) ||
        (Rva < NtSection->VirtualAddress) ||
        (Rva >= NtSection->VirtualAddress + NtSection->SizeOfRawData))
    {
        NtSection = RtlImageRvaToSection(NtHeaders, BaseOfImage, Rva);
        if (NtSection == NULL)
        {
            return NULL;
        }

        if (LastRvaSection != NULL)
        {
            *LastRvaSection = NtSection;
        }
    }

    return (PVOID)((ULONG_PTR)BaseOfImage
        + Rva
        + NtSection->PointerToRawData
        - NtSection->VirtualAddress);
}

#if defined _M_IX86

_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlImageRvaToSection@12, _VEIL_IMPL_RtlImageRvaToSection);
_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlImageRvaToVa@16, _VEIL_IMPL_RtlImageRvaToVa);

#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64

_VEIL_DEFINE_IAT_SYMBOL(RtlImageRvaToSection, _VEIL_IMPL_RtlImageRvaToSection);
_VEIL_DEFINE_IAT_SYMBOL(RtlImageRvaToVa, _VEIL_IMPL_RtlImageRvaToVa);

#endif

#endif // if _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
PVOID
NTAPI
RtlFindExportedRoutineByName(
    _In_ PVOID BaseOfImage,
    _In_ PCSTR RoutineName
);
#endif

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGuardCheckLongJumpTarget(
    _In_ PVOID PcValue,
    _In_ BOOL IsFastFail,
    _Out_ PBOOL IsLongJumpTarget
);
#endif

#endif // !_KERNEL_MODE

#ifdef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlPcToFileName(
    _In_ PVOID PcValue,
    _Out_ PUNICODE_STRING FileName
);

NTSYSAPI
NTSTATUS
NTAPI
RtlPcToFilePath(
    _In_ PVOID PcValue,
    _Out_ PUNICODE_STRING FilePath
);

NTSYSAPI
PVOID
NTAPI
RtlPcToFileHeader(
    _In_ PVOID PcValue,
    _Out_ PVOID* BaseOfImage
);

NTSYSAPI
VOID
NTAPI
RtlRaiseException(
    _In_ PEXCEPTION_RECORD ExceptionRecord
);

NTSYSAPI
VOID
NTAPI
RtlUnwind(
    _In_opt_ PVOID TargetFrame,
    _In_opt_ PVOID TargetIp,
    _In_opt_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PVOID ReturnValue
);

#if defined(_M_ARM)

//
// Define unwind information flags.
//

#define UNW_FLAG_NHANDLER               0x0             /* any handler */
#define UNW_FLAG_EHANDLER               0x1             /* filter handler */
#define UNW_FLAG_UHANDLER               0x2             /* unwind handler */

//
// Define unwind history table structure.
//

#define UNWIND_HISTORY_TABLE_SIZE 12

typedef struct _UNWIND_HISTORY_TABLE_ENTRY {
    DWORD ImageBase;
    PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry;
} UNWIND_HISTORY_TABLE_ENTRY, * PUNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE {
    DWORD Count;
    BYTE  LocalHint;
    BYTE  GlobalHint;
    BYTE  Search;
    BYTE  Once;
    DWORD LowAddress;
    DWORD HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[UNWIND_HISTORY_TABLE_SIZE];
} UNWIND_HISTORY_TABLE, * PUNWIND_HISTORY_TABLE;

//
// Define exception dispatch context structure.
//

typedef struct _DISPATCHER_CONTEXT {
    DWORD ControlPc;
    DWORD ImageBase;
    PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry;
    DWORD EstablisherFrame;
    DWORD TargetPc;
    PCONTEXT ContextRecord;
    PEXCEPTION_ROUTINE LanguageHandler;
    PVOID HandlerData;
    PUNWIND_HISTORY_TABLE HistoryTable;
    DWORD ScopeIndex;
    BOOLEAN ControlPcIsUnwound;
    PBYTE  NonVolatileRegisters;
    DWORD Reserved;
} DISPATCHER_CONTEXT, * PDISPATCHER_CONTEXT;

//
// Define exception filter and termination handler function types.
// N.B. These functions use a custom calling convention.
//

struct _EXCEPTION_POINTERS;
typedef
LONG
(*PEXCEPTION_FILTER) (
    struct _EXCEPTION_POINTERS* ExceptionPointers,
    DWORD EstablisherFrame
    );

typedef
VOID
(*PTERMINATION_HANDLER) (
    BOOLEAN AbnormalTermination,
    DWORD EstablisherFrame
    );

//
// Define dynamic function table entry.
//

typedef
_Function_class_(GET_RUNTIME_FUNCTION_CALLBACK)
PIMAGE_RUNTIME_FUNCTION_ENTRY
GET_RUNTIME_FUNCTION_CALLBACK(
    _In_ DWORD ControlPc,
    _In_opt_ PVOID Context
);
typedef GET_RUNTIME_FUNCTION_CALLBACK* PGET_RUNTIME_FUNCTION_CALLBACK;

typedef
_Function_class_(OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK)
DWORD
OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK(
    _In_ HANDLE Process,
    _In_ PVOID TableAddress,
    _Out_ PDWORD Entries,
    _Out_ PIMAGE_RUNTIME_FUNCTION_ENTRY* Functions
);
typedef OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK* POUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK;

#define OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK_EXPORT_NAME \
    "OutOfProcessFunctionTableCallback"

//
// Nonvolatile context pointer record.
//

typedef struct _KNONVOLATILE_CONTEXT_POINTERS {

    PDWORD R4;
    PDWORD R5;
    PDWORD R6;
    PDWORD R7;
    PDWORD R8;
    PDWORD R9;
    PDWORD R10;
    PDWORD R11;
    PDWORD Lr;

    PULONGLONG D8;
    PULONGLONG D9;
    PULONGLONG D10;
    PULONGLONG D11;
    PULONGLONG D12;
    PULONGLONG D13;
    PULONGLONG D14;
    PULONGLONG D15;

} KNONVOLATILE_CONTEXT_POINTERS, * PKNONVOLATILE_CONTEXT_POINTERS;

#elif defined(_M_X64)

#define RUNTIME_FUNCTION_INDIRECT 0x1

//
// Define unwind information flags.
//

#define UNW_FLAG_NHANDLER       0x0
#define UNW_FLAG_EHANDLER       0x1
#define UNW_FLAG_UHANDLER       0x2
#define UNW_FLAG_CHAININFO      0x4

#define UNW_FLAG_NO_EPILOGUE    0x80000000UL    // Software only flag

#define UNWIND_CHAIN_LIMIT      32

//
// Define unwind history table structure.
//

#define UNWIND_HISTORY_TABLE_SIZE 12

typedef struct _UNWIND_HISTORY_TABLE_ENTRY
{
    ULONG_PTR ImageBase;
    PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry;

} UNWIND_HISTORY_TABLE_ENTRY, * PUNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE
{
    UINT32 Count;
    UINT8  LocalHint;
    UINT8  GlobalHint;
    UINT8  Search;
    UINT8  Once;
    ULONG_PTR LowAddress;
    ULONG_PTR HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[UNWIND_HISTORY_TABLE_SIZE];

} UNWIND_HISTORY_TABLE, * PUNWIND_HISTORY_TABLE;


//
// Define dynamic function table entry.
//

typedef
_Function_class_(GET_RUNTIME_FUNCTION_CALLBACK)
PIMAGE_RUNTIME_FUNCTION_ENTRY
GET_RUNTIME_FUNCTION_CALLBACK(
    _In_ DWORD64 ControlPc,
    _In_opt_ PVOID Context
);
typedef GET_RUNTIME_FUNCTION_CALLBACK* PGET_RUNTIME_FUNCTION_CALLBACK;

typedef
_Function_class_(OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK)
DWORD
OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK(
    _In_ HANDLE Process,
    _In_ PVOID TableAddress,
    _Out_ PDWORD Entries,
    _Out_ PIMAGE_RUNTIME_FUNCTION_ENTRY* Functions
);
typedef OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK* POUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK;

#define OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK_EXPORT_NAME \
    "OutOfProcessFunctionTableCallback"

//
// Define exception dispatch context structure.
//

typedef struct _DISPATCHER_CONTEXT {
    DWORD64 ControlPc;
    DWORD64 ImageBase;
    PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry;
    DWORD64 EstablisherFrame;
    DWORD64 TargetIp;
    PCONTEXT ContextRecord;
    PEXCEPTION_ROUTINE LanguageHandler;
    PVOID HandlerData;
    PUNWIND_HISTORY_TABLE HistoryTable;
    DWORD ScopeIndex;
    DWORD Fill0;
} DISPATCHER_CONTEXT, * PDISPATCHER_CONTEXT;

//
// Define exception filter and termination handler function types.
//

struct _EXCEPTION_POINTERS;
typedef
LONG
(*PEXCEPTION_FILTER) (
    struct _EXCEPTION_POINTERS* ExceptionPointers,
    PVOID EstablisherFrame
    );

typedef
VOID
(*PTERMINATION_HANDLER) (
    BOOLEAN AbnormalTermination,
    PVOID EstablisherFrame
    );

//
// Nonvolatile context pointer record.
//

#pragma warning(push)
#pragma warning(disable: 4201) // nonstandard extension used: nameless struct/union
typedef struct _KNONVOLATILE_CONTEXT_POINTERS {
    union {
        PM128A FloatingContext[16];
        struct {
            PM128A Xmm0;
            PM128A Xmm1;
            PM128A Xmm2;
            PM128A Xmm3;
            PM128A Xmm4;
            PM128A Xmm5;
            PM128A Xmm6;
            PM128A Xmm7;
            PM128A Xmm8;
            PM128A Xmm9;
            PM128A Xmm10;
            PM128A Xmm11;
            PM128A Xmm12;
            PM128A Xmm13;
            PM128A Xmm14;
            PM128A Xmm15;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

    union {
        PDWORD64 IntegerContext[16];
        struct {
            PDWORD64 Rax;
            PDWORD64 Rcx;
            PDWORD64 Rdx;
            PDWORD64 Rbx;
            PDWORD64 Rsp;
            PDWORD64 Rbp;
            PDWORD64 Rsi;
            PDWORD64 Rdi;
            PDWORD64 R8;
            PDWORD64 R9;
            PDWORD64 R10;
            PDWORD64 R11;
            PDWORD64 R12;
            PDWORD64 R13;
            PDWORD64 R14;
            PDWORD64 R15;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME2;

} KNONVOLATILE_CONTEXT_POINTERS, * PKNONVOLATILE_CONTEXT_POINTERS;
#pragma warning(pop)

#elif defined(_M_ARM64) || defined(_CHPE_X86_ARM64_EH_)

//
// Define unwind information flags.
//

#define UNW_FLAG_NHANDLER               0x0             /* any handler */
#define UNW_FLAG_EHANDLER               0x1             /* filter handler */
#define UNW_FLAG_UHANDLER               0x2             /* unwind handler */

//
// Define unwind history table structure.
//

#define UNWIND_HISTORY_TABLE_SIZE 12

typedef struct _UNWIND_HISTORY_TABLE_ENTRY {
    DWORD64 ImageBase;
    PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry;
} UNWIND_HISTORY_TABLE_ENTRY, * PUNWIND_HISTORY_TABLE_ENTRY;

typedef struct _UNWIND_HISTORY_TABLE {
    DWORD Count;
    BYTE  LocalHint;
    BYTE  GlobalHint;
    BYTE  Search;
    BYTE  Once;
    DWORD64 LowAddress;
    DWORD64 HighAddress;
    UNWIND_HISTORY_TABLE_ENTRY Entry[UNWIND_HISTORY_TABLE_SIZE];
} UNWIND_HISTORY_TABLE, * PUNWIND_HISTORY_TABLE;

#pragma push_macro("_DISPATCHER_CONTEXT_ARM64")
#undef _DISPATCHER_CONTEXT_ARM64
#define _DISPATCHER_CONTEXT_ARM64 _DISPATCHER_CONTEXT

//
// Define exception dispatch context structure.
//

typedef struct _DISPATCHER_CONTEXT_ARM64 {
    ULONG_PTR ControlPc;
    ULONG_PTR ImageBase;
    PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry;
    ULONG_PTR EstablisherFrame;
    ULONG_PTR TargetPc;
    PARM64_NT_CONTEXT ContextRecord;
    PEXCEPTION_ROUTINE LanguageHandler;
    PVOID HandlerData;
    PUNWIND_HISTORY_TABLE HistoryTable;
    DWORD ScopeIndex;
    BOOLEAN ControlPcIsUnwound;
    PBYTE  NonVolatileRegisters;
} DISPATCHER_CONTEXT_ARM64, * PDISPATCHER_CONTEXT_ARM64;

#undef _DISPATCHER_CONTEXT_ARM64
#pragma pop_macro("_DISPATCHER_CONTEXT_ARM64")

typedef DISPATCHER_CONTEXT_ARM64 DISPATCHER_CONTEXT, * PDISPATCHER_CONTEXT;

//
// Define exception filter and termination handler function types.
// N.B. These functions use a custom calling convention.
//

struct _EXCEPTION_POINTERS;
typedef
LONG
(*PEXCEPTION_FILTER) (
    struct _EXCEPTION_POINTERS* ExceptionPointers,
    DWORD64 EstablisherFrame
    );

typedef
VOID
(*PTERMINATION_HANDLER) (
    BOOLEAN AbnormalTermination,
    DWORD64 EstablisherFrame
    );

//
// Define dynamic function table entry.
//

typedef
_Function_class_(GET_RUNTIME_FUNCTION_CALLBACK)
PIMAGE_RUNTIME_FUNCTION_ENTRY
GET_RUNTIME_FUNCTION_CALLBACK(
    _In_ DWORD64 ControlPc,
    _In_opt_ PVOID Context
);
typedef GET_RUNTIME_FUNCTION_CALLBACK* PGET_RUNTIME_FUNCTION_CALLBACK;

typedef
_Function_class_(OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK)
DWORD
OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK(
    _In_ HANDLE Process,
    _In_ PVOID TableAddress,
    _Out_ PDWORD Entries,
    _Out_ PIMAGE_RUNTIME_FUNCTION_ENTRY* Functions
);
typedef OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK* POUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK;

#define OUT_OF_PROCESS_FUNCTION_TABLE_CALLBACK_EXPORT_NAME \
    "OutOfProcessFunctionTableCallback"

//
// Nonvolatile context pointer record.
//

typedef struct _KNONVOLATILE_CONTEXT_POINTERS_ARM64 {

    PDWORD64 X19;
    PDWORD64 X20;
    PDWORD64 X21;
    PDWORD64 X22;
    PDWORD64 X23;
    PDWORD64 X24;
    PDWORD64 X25;
    PDWORD64 X26;
    PDWORD64 X27;
    PDWORD64 X28;
    PDWORD64 Fp;
    PDWORD64 Lr;

    PDWORD64 D8;
    PDWORD64 D9;
    PDWORD64 D10;
    PDWORD64 D11;
    PDWORD64 D12;
    PDWORD64 D13;
    PDWORD64 D14;
    PDWORD64 D15;

} KNONVOLATILE_CONTEXT_POINTERS_ARM64, * PKNONVOLATILE_CONTEXT_POINTERS_ARM64;

typedef KNONVOLATILE_CONTEXT_POINTERS_ARM64 KNONVOLATILE_CONTEXT_POINTERS, * PKNONVOLATILE_CONTEXT_POINTERS;

#endif // _M_ARM64 | _CHPE_X86_ARM64_EH_

#if defined(_M_AMD64) || defined(_M_ARM64) || defined(_M_ARM)

NTSYSAPI
PIMAGE_RUNTIME_FUNCTION_ENTRY
NTAPI
RtlLookupFunctionEntry(
    _In_ ULONG_PTR ControlPc,
    _Out_ PULONG_PTR ImageBase,
    _Inout_opt_ PUNWIND_HISTORY_TABLE HistoryTable
);

NTSYSAPI
VOID
__cdecl
RtlRestoreContext(
    _In_ PCONTEXT ContextRecord,
    _In_opt_ PEXCEPTION_RECORD ExceptionRecord
);

NTSYSAPI
VOID
NTAPI
RtlUnwindEx(
    _In_opt_ PVOID TargetFrame,
    _In_opt_ PVOID TargetIp,
    _In_opt_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PVOID ReturnValue,
    _In_ PCONTEXT ContextRecord,
    _In_opt_ PUNWIND_HISTORY_TABLE HistoryTable
);

NTSYSAPI
PEXCEPTION_ROUTINE
NTAPI
RtlVirtualUnwind(
    _In_ UINT32 HandlerType,
    _In_ SIZE_T ImageBase,
    _In_ SIZE_T ControlPc,
    _In_ PIMAGE_RUNTIME_FUNCTION_ENTRY FunctionEntry,
    _Inout_ PCONTEXT ContextRecord,
    _Out_ PVOID* HandlerData,
    _Out_ PSIZE_T EstablisherFrame,
    _Inout_opt_ PKNONVOLATILE_CONTEXT_POINTERS ContextPointers
);

#endif // _M_AMD64 | _M_ARM64 | _M_ARM

#endif // _KERNEL_MODE

typedef struct _RTL_MODULE_BASIC_INFO {
    PVOID ImageBase;
} RTL_MODULE_BASIC_INFO, * PRTL_MODULE_BASIC_INFO;

typedef struct _RTL_MODULE_EXTENDED_INFO {
    RTL_MODULE_BASIC_INFO BasicInfo;
    ULONG ImageSize;
    USHORT FileNameOffset;
    UCHAR FullPathName[256];
} RTL_MODULE_EXTENDED_INFO, * PRTL_MODULE_EXTENDED_INFO;

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryModuleInformation(      // ZwQuerySystemInformation(SystemModuleInformation)
    _Out_ PULONG ReturnLength,
    _In_ ULONG BufferSize,      // sizeof RTL_MODULE_EXTENDED_INFO or RTL_MODULE_BASIC_INFO
    _In_ PVOID Buffer           // PRTL_MODULE_EXTENDED_INFO or PRTL_MODULE_BASIC_INFO
);

//
// Memory
//

_Must_inspect_result_
NTSYSAPI
SIZE_T
NTAPI
RtlCompareMemoryUlong(
    _In_reads_bytes_(Length) PVOID Source,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern
);

#ifndef _KERNEL_MODE

#if defined(_M_AMD64)
FORCEINLINE
VOID
RtlFillMemoryUlong(
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern
)
{
    PULONG Address = (PULONG)Destination;

    //
    // If the number of DWORDs is not zero, then fill the specified buffer
    // with the specified pattern.
    //

    if ((Length /= 4) != 0) {

        //
        // If the destination is not quadword aligned (ignoring low bits),
        // then align the destination by storing one DWORD.
        //

        if (((ULONG64)Address & 4) != 0) {
            *Address = Pattern;
            if ((Length -= 1) == 0) {
                return;
            }

            Address += 1;
        }

        //
        // If the number of QWORDs is not zero, then fill the destination
        // buffer a QWORD at a time.
        //

        __stosq((PULONG64)(Address),
            Pattern | ((ULONG64)Pattern << 32),
            Length / 2);

        if ((Length & 1) != 0) {
            Address[Length - 1] = Pattern;
        }
    }

    return;
}
#else
NTSYSAPI
VOID
NTAPI
RtlFillMemoryUlong(
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONG Pattern
);
#endif

#if defined(_M_AMD64)
#define RtlFillMemoryUlonglong(Destination, Length, Pattern) \
    __stosq((PULONG64)(Destination), Pattern, (Length) / 8)
#else
NTSYSAPI
VOID
NTAPI
RtlFillMemoryUlonglong(
    _Out_writes_bytes_all_(Length) PVOID Destination,
    _In_ SIZE_T Length,
    _In_ ULONGLONG Pattern
);
#endif

#endif // !_KERNEL_MODE

//
// Environment
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateEnvironment(
    _In_ BOOLEAN CloneCurrentEnvironment,
    _Out_ PVOID* Environment
);

// begin_rev
#define RTL_CREATE_ENVIRONMENT_TRANSLATE 0x1 // translate from multi-byte to Unicode
#define RTL_CREATE_ENVIRONMENT_TRANSLATE_FROM_OEM 0x2 // translate from OEM to Unicode (Translate flag must also be set)
#define RTL_CREATE_ENVIRONMENT_EMPTY 0x4 // create empty environment block
// end_rev

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateEnvironmentEx(
    _In_ PVOID SourceEnv,
    _Out_ PVOID* Environment,
    _In_ ULONG Flags
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyEnvironment(
    _In_ PVOID Environment
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetCurrentEnvironment(
    _In_ PVOID Environment,
    _Out_opt_ PVOID* PreviousEnvironment
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentVar(
    _Inout_opt_ PVOID* Environment,
    _In_reads_(NameLength) PCWSTR Name,
    _In_ SIZE_T NameLength,
    _In_reads_(ValueLength) PCWSTR Value,
    _In_ SIZE_T ValueLength
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentVariable(
    _Inout_opt_ PVOID* Environment,
    _In_ PUNICODE_STRING Name,
    _In_opt_ PUNICODE_STRING Value
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryEnvironmentVariable(
    _In_opt_ PVOID Environment,
    _In_reads_(NameLength) PCWSTR Name,
    _In_ SIZE_T NameLength,
    _Out_writes_(ValueLength) PWSTR Value,
    _In_ SIZE_T ValueLength,
    _Out_ PSIZE_T ReturnLength
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryEnvironmentVariable_U(
    _In_opt_ PVOID Environment,
    _In_ PUNICODE_STRING Name,
    _Inout_ PUNICODE_STRING Value
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlExpandEnvironmentStrings(
    _In_opt_ PVOID Environment,
    _In_reads_(SrcLength) PCWSTR Src,
    _In_ SIZE_T SrcLength,
    _Out_writes_(DstLength) PWSTR Dst,
    _In_ SIZE_T DstLength,
    _Out_opt_ PSIZE_T ReturnLength
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlExpandEnvironmentStrings_U(
    _In_opt_ PVOID Environment,
    _In_ PUNICODE_STRING Source,
    _Inout_ PUNICODE_STRING Destination,
    _Out_opt_ PULONG ReturnedLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetEnvironmentStrings(
    _In_ PCWCHAR NewEnvironment,
    _In_ SIZE_T NewEnvironmentSize
);

#endif // !_KERNEL_MODE

//
// Directory and path support
//

#ifndef _KERNEL_MODE

typedef struct _RTLP_CURDIR_REF
{
    LONG ReferenceCount;
    HANDLE DirectoryHandle;
} RTLP_CURDIR_REF, * PRTLP_CURDIR_REF;

typedef struct _RTL_RELATIVE_NAME_U
{
    UNICODE_STRING RelativeName;
    HANDLE ContainingDirectory;
    PRTLP_CURDIR_REF CurDirRef;
} RTL_RELATIVE_NAME_U, * PRTL_RELATIVE_NAME_U;

typedef enum _RTL_PATH_TYPE
{
    RtlPathTypeUnknown,
    RtlPathTypeUncAbsolute,
    RtlPathTypeDriveAbsolute,
    RtlPathTypeDriveRelative,
    RtlPathTypeRooted,
    RtlPathTypeRelative,
    RtlPathTypeLocalDevice,
    RtlPathTypeRootLocalDevice
} RTL_PATH_TYPE;

// Data exports (ntdll.lib/ntdllp.lib)

NTSYSAPI PWSTR RtlNtdllName;
NTSYSAPI UNICODE_STRING RtlDosPathSeperatorsString;
NTSYSAPI UNICODE_STRING RtlAlternateDosPathSeperatorString;
NTSYSAPI UNICODE_STRING RtlNtPathSeperatorString;

// Path functions

NTSYSAPI
RTL_PATH_TYPE
NTAPI
RtlDetermineDosPathNameType_U(
    _In_ PCWSTR DosFileName
);

NTSYSAPI
ULONG
NTAPI
RtlIsDosDeviceName_U(
    _In_ PCWSTR DosFileName
);

NTSYSAPI
ULONG
NTAPI
RtlGetFullPathName_U(
    _In_ PCWSTR FileName,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _Out_opt_ PWSTR* FilePart
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetFullPathName_UEx(
    _In_ PCWSTR FileName,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ ULONG* BytesRequired
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlGetFullPathName_UstrEx(
    _In_ PUNICODE_STRING FileName,
    _Inout_ PUNICODE_STRING StaticString,
    _Out_opt_ PUNICODE_STRING DynamicString,
    _Out_opt_ PUNICODE_STRING* StringUsed,
    _Out_opt_ SIZE_T* FilePartPrefixCch,
    _Out_opt_ PBOOLEAN NameInvalid,
    _Out_ RTL_PATH_TYPE* InputPathType,
    _Out_opt_ SIZE_T* BytesRequired
);
#endif

NTSYSAPI
ULONG
NTAPI
RtlGetCurrentDirectory_U(
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetCurrentDirectory_U(
    _In_ PUNICODE_STRING PathName
);

NTSYSAPI
ULONG
NTAPI
RtlGetLongestNtPathLength(
    VOID
);

NTSYSAPI
BOOLEAN
NTAPI
RtlDosPathNameToNtPathName_U(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlDosPathNameToNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDosLongPathNameToNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
BOOLEAN
NTAPI
RtlDosPathNameToRelativeNtPathName_U(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
NTSTATUS
NTAPI
RtlDosPathNameToRelativeNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDosLongPathNameToRelativeNtPathName_U_WithStatus(
    _In_ PCWSTR DosFileName,
    _Out_ PUNICODE_STRING NtFileName,
    _Out_opt_ PWSTR* FilePart,
    _Out_opt_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

#if (NTDDI_VERSION >= NTDDI_WS03)
NTSYSAPI
VOID
NTAPI
RtlReleaseRelativeName(
    _Inout_ PRTL_RELATIVE_NAME_U RelativeName
);
#endif

NTSYSAPI
ULONG
NTAPI
RtlDosSearchPath_U(
    _In_ PCWSTR Path,
    _In_ PCWSTR FileName,
    _In_opt_ PCWSTR Extension,
    _In_ ULONG BufferLength,
    _Out_writes_bytes_(BufferLength) PWSTR Buffer,
    _Out_opt_ PWSTR* FilePart
);

#define RTL_DOS_SEARCH_PATH_FLAG_APPLY_ISOLATION_REDIRECTION 0x00000001
#define RTL_DOS_SEARCH_PATH_FLAG_DISALLOW_DOT_RELATIVE_PATH_SEARCH 0x00000002
#define RTL_DOS_SEARCH_PATH_FLAG_APPLY_DEFAULT_EXTENSION_WHEN_NOT_RELATIVE_PATH_EVEN_IF_FILE_HAS_EXTENSION 0x00000004

NTSYSAPI
NTSTATUS
NTAPI
RtlDosSearchPath_Ustr(
    _In_ ULONG Flags,
    _In_ PUNICODE_STRING Path,
    _In_ PUNICODE_STRING FileName,
    _In_opt_ PUNICODE_STRING DefaultExtension,
    _Out_opt_ PUNICODE_STRING StaticString,
    _Out_opt_ PUNICODE_STRING DynamicString,
    _Out_opt_ PCUNICODE_STRING* FullFileNameOut,
    _Out_opt_ SIZE_T* FilePartPrefixCch,
    _Out_opt_ SIZE_T* BytesRequired
);

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlDosApplyFileIsolationRedirection_Ustr(
    _In_ ULONG                  Flags,
    _In_ PUNICODE_STRING        OriginalName,
    _In_ PUNICODE_STRING        Extension,
    _In_opt_ PUNICODE_STRING    StaticString,
    _In_opt_ PUNICODE_STRING    DynamicString,
    _In_opt_ PUNICODE_STRING*   NewName,
    _In_ PULONG                 NewFlags,
    _In_ PSIZE_T                FileNameSize,
    _In_ PSIZE_T                RequiredLength
);

NTSYSAPI
BOOLEAN
NTAPI
RtlDoesFileExists_U(
    _In_ PCWSTR FileName
);

NTSYSAPI
NTSTATUS
NTAPI
RtlGetLengthWithoutLastFullDosOrNtPathElement(
    _Reserved_ ULONG Flags,
    _In_ PUNICODE_STRING PathString,
    _Out_ PULONG Length
);

NTSYSAPI
NTSTATUS
NTAPI
RtlGetLengthWithoutTrailingPathSeperators(
    _Reserved_ ULONG Flags,
    _In_ PUNICODE_STRING PathString,
    _Out_ PULONG Length
);

typedef struct _GENERATE_NAME_CONTEXT
{
    USHORT Checksum;
    BOOLEAN CheckSumInserted;
    UCHAR NameLength;
    WCHAR NameBuffer[8];
    ULONG ExtensionLength;
    WCHAR ExtensionBuffer[4];
    ULONG LastIndexValue;
} GENERATE_NAME_CONTEXT, * PGENERATE_NAME_CONTEXT;

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlGenerate8dot3Name(
    _In_ PUNICODE_STRING Name,
    _In_ BOOLEAN AllowExtendedCharacters,
    _Inout_ PGENERATE_NAME_CONTEXT Context,
    _Inout_ PUNICODE_STRING Name8dot3
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlComputePrivatizedDllName_U(
    _In_ PUNICODE_STRING DllName,
    _Out_ PUNICODE_STRING RealName,
    _Out_ PUNICODE_STRING LocalName
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetSearchPath(
    _Out_ PWSTR* SearchPath
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetSearchPathMode(
    _In_ ULONG Flags
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetExePath(
    _In_ PCWSTR DosPathName,
    _Out_ PWSTR* SearchPath
);

// rev
NTSYSAPI
VOID
NTAPI
RtlReleasePath(
    _In_ PWSTR Path
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
NTSYSAPI
ULONG
NTAPI
RtlReplaceSystemDirectoryInPath(
    _Inout_ PUNICODE_STRING Destination,
    _In_ ULONG Machine, // IMAGE_FILE_MACHINE_I386
    _In_ ULONG TargetMachine, // IMAGE_FILE_MACHINE_TARGET_HOST
    _In_ BOOLEAN IncludePathSeperator
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_CO)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlWow64GetProcessMachines(
    _In_ HANDLE ProcessHandle,
    _Out_ PUSHORT ProcessMachine,
    _Out_ PUSHORT NativeMachine
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
PCWSTR
NTAPI
RtlGetNtSystemRoot(
    VOID
);

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlAreLongPathsEnabled(
    VOID
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS2

NTSYSAPI
BOOLEAN
NTAPI
RtlIsThreadWithinLoaderCallout(
    VOID
);

NTSYSAPI
BOOLEAN
NTAPI
RtlDllShutdownInProgress(
    VOID
);

#endif // !_KERNEL_MODE

//
// Heaps
//

#ifndef _KERNEL_MODE

typedef struct _RTL_HEAP_ENTRY
{
    SIZE_T Size;
    USHORT Flags;
    USHORT AllocatorBackTraceIndex;
    union
    {
        struct
        {
            SIZE_T Settable;
            ULONG Tag;
        } s1;
        struct
        {
            SIZE_T CommittedSize;
            PVOID FirstBlock;
        } s2;
    } u;
} RTL_HEAP_ENTRY, * PRTL_HEAP_ENTRY;

#define RTL_HEAP_BUSY           (USHORT)0x0001
#define RTL_HEAP_SEGMENT        (USHORT)0x0002
#define RTL_HEAP_SETTABLE_VALUE (USHORT)0x0010
#define RTL_HEAP_SETTABLE_FLAG1 (USHORT)0x0020
#define RTL_HEAP_SETTABLE_FLAG2 (USHORT)0x0040
#define RTL_HEAP_SETTABLE_FLAG3 (USHORT)0x0080
#define RTL_HEAP_SETTABLE_FLAGS (USHORT)0x00e0
#define RTL_HEAP_UNCOMMITTED_RANGE (USHORT)0x0100
#define RTL_HEAP_PROTECTED_ENTRY (USHORT)0x0200

typedef struct _RTL_HEAP_TAG
{
    ULONG NumberOfAllocations;
    ULONG NumberOfFrees;
    SIZE_T BytesAllocated;
    USHORT TagIndex;
    USHORT CreatorBackTraceIndex;
    WCHAR TagName[24];
} RTL_HEAP_TAG, * PRTL_HEAP_TAG;

// Windows 7/8/10
typedef struct _RTL_HEAP_INFORMATION
{
    PVOID BaseAddress;
    ULONG Flags;
    USHORT EntryOverhead;
    USHORT CreatorBackTraceIndex;
    SIZE_T BytesAllocated;
    SIZE_T BytesCommitted;
    ULONG NumberOfTags;
    ULONG NumberOfEntries;
    ULONG NumberOfPseudoTags;
    ULONG PseudoTagGranularity;
    ULONG Reserved[5];
    PRTL_HEAP_TAG Tags;
    PRTL_HEAP_ENTRY Entries;
    ULONG64 HeapTag; // Windows 11 > 22000
} RTL_HEAP_INFORMATION, * PRTL_HEAP_INFORMATION;

#define RTL_HEAP_SIGNATURE          0xFFEEFFEEUL
#define RTL_HEAP_SEGMENT_SIGNATURE  0xDDEEDDEEUL

typedef struct _RTL_PROCESS_HEAPS
{
    ULONG NumberOfHeaps;
    RTL_HEAP_INFORMATION Heaps[1];
} RTL_PROCESS_HEAPS, * PRTL_PROCESS_HEAPS;

typedef
_Function_class_(RTL_HEAP_COMMIT_ROUTINE)
_IRQL_requires_same_
NTSTATUS
NTAPI
RTL_HEAP_COMMIT_ROUTINE(
    _In_ PVOID Base,
    _Inout_ PVOID* CommitAddress,
    _Inout_ PSIZE_T CommitSize
);
typedef RTL_HEAP_COMMIT_ROUTINE* PRTL_HEAP_COMMIT_ROUTINE;

typedef struct _RTL_HEAP_PARAMETERS
{
    ULONG Length;
    SIZE_T SegmentReserve;
    SIZE_T SegmentCommit;
    SIZE_T DeCommitFreeBlockThreshold;
    SIZE_T DeCommitTotalFreeThreshold;
    SIZE_T MaximumAllocationSize;
    SIZE_T VirtualMemoryThreshold;
    SIZE_T InitialCommit;
    SIZE_T InitialReserve;
    PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
    SIZE_T Reserved[2];
} RTL_HEAP_PARAMETERS, * PRTL_HEAP_PARAMETERS;

#define HEAP_SETTABLE_USER_VALUE 0x00000100
#define HEAP_SETTABLE_USER_FLAG1 0x00000200
#define HEAP_SETTABLE_USER_FLAG2 0x00000400
#define HEAP_SETTABLE_USER_FLAG3 0x00000800
#define HEAP_SETTABLE_USER_FLAGS 0x00000e00

#define HEAP_CLASS_0 0x00000000 // Process heap
#define HEAP_CLASS_1 0x00001000 // Private heap
#define HEAP_CLASS_2 0x00002000 // Kernel heap
#define HEAP_CLASS_3 0x00003000 // GDI heap
#define HEAP_CLASS_4 0x00004000 // User heap
#define HEAP_CLASS_5 0x00005000 // Console heap
#define HEAP_CLASS_6 0x00006000 // User desktop heap
#define HEAP_CLASS_7 0x00007000 // CSR shared heap
#define HEAP_CLASS_8 0x00008000 // CSR port heap
#define HEAP_CLASS_MASK 0x0000f000

_Must_inspect_result_
NTSYSAPI
PVOID
NTAPI
RtlCreateHeap(
    _In_ ULONG Flags,
    _In_opt_ PVOID HeapBase,
    _In_opt_ SIZE_T ReserveSize,
    _In_opt_ SIZE_T CommitSize,
    _In_opt_ PVOID Lock,
    _In_opt_ PRTL_HEAP_PARAMETERS Parameters
);

NTSYSAPI
PVOID
NTAPI
RtlDestroyHeap(
    _In_ _Post_invalid_ PVOID HeapHandle
);

_Must_inspect_result_
_Ret_maybenull_
_Post_writable_byte_size_(Size)
NTSYSAPI
PVOID
NTAPI
RtlAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _In_ SIZE_T Size
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Success_(return != 0)
NTSYSAPI
LOGICAL
NTAPI
RtlFreeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress
);
#else
_Success_(return)
NTSYSAPI
BOOLEAN
NTAPI
RtlFreeHeap(
    _In_ PVOID HeapHandle,
    _In_opt_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress
);
#endif

#endif // !_KERNEL_MODE

NTSYSAPI
SIZE_T
NTAPI
RtlSizeHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress
);

NTSYSAPI
NTSTATUS
NTAPI
RtlZeroHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags
);

#ifndef _KERNEL_MODE

NTSYSAPI
VOID
NTAPI
RtlProtectHeap(
    _In_ PVOID HeapHandle,
    _In_ BOOLEAN MakeReadOnly
);

#endif // !_KERNEL_MODE

#define RtlProcessHeap() (NtCurrentPeb()->ProcessHeap)

#ifndef _KERNEL_MODE

NTSYSAPI
BOOLEAN
NTAPI
RtlLockHeap(
    _In_ PVOID HeapHandle
);

NTSYSAPI
BOOLEAN
NTAPI
RtlUnlockHeap(
    _In_ PVOID HeapHandle
);

NTSYSAPI
PVOID
NTAPI
RtlReAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _Frees_ptr_opt_ PVOID BaseAddress,
    _In_ SIZE_T Size
);

NTSYSAPI
BOOLEAN
NTAPI
RtlGetUserInfoHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _Out_opt_ PVOID * UserValue,
    _Out_opt_ PULONG UserFlags
);

NTSYSAPI
BOOLEAN
NTAPI
RtlSetUserValueHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ PVOID UserValue
);

NTSYSAPI
BOOLEAN
NTAPI
RtlSetUserFlagsHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress,
    _In_ ULONG UserFlagsReset,
    _In_ ULONG UserFlagsSet
);

typedef struct _RTL_HEAP_TAG_INFO
{
    ULONG NumberOfAllocations;
    ULONG NumberOfFrees;
    SIZE_T BytesAllocated;
} RTL_HEAP_TAG_INFO, * PRTL_HEAP_TAG_INFO;

#define RTL_HEAP_MAKE_TAG HEAP_MAKE_TAG_FLAGS

NTSYSAPI
ULONG
NTAPI
RtlCreateTagHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_opt_ PWSTR TagPrefix,
    _In_ PWSTR TagNames
);

NTSYSAPI
PWSTR
NTAPI
RtlQueryTagHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ USHORT TagIndex,
    _In_ BOOLEAN ResetCounters,
    _Out_opt_ PRTL_HEAP_TAG_INFO TagInfo
);

NTSYSAPI
NTSTATUS
NTAPI
RtlExtendHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID Base,
    _In_ SIZE_T Size
);

NTSYSAPI
SIZE_T
NTAPI
RtlCompactHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags
);

NTSYSAPI
BOOLEAN
NTAPI
RtlValidateHeap(
    _In_opt_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress
);

NTSYSAPI
BOOLEAN
NTAPI
RtlValidateProcessHeaps(
    VOID
);

NTSYSAPI
ULONG
NTAPI
RtlGetProcessHeaps(
    _In_ ULONG NumberOfHeaps,
    _Out_ PVOID * ProcessHeaps
);

typedef NTSTATUS(NTAPI* PRTL_ENUM_HEAPS_ROUTINE)(
    _In_ PVOID HeapHandle,
    _In_ PVOID Parameter
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlEnumProcessHeaps(
    _In_ PRTL_ENUM_HEAPS_ROUTINE EnumRoutine,
    _In_ PVOID Parameter
);

typedef struct _RTL_HEAP_USAGE_ENTRY
{
    struct _RTL_HEAP_USAGE_ENTRY* Next;
    PVOID Address;
    SIZE_T Size;
    USHORT AllocatorBackTraceIndex;
    USHORT TagIndex;
} RTL_HEAP_USAGE_ENTRY, * PRTL_HEAP_USAGE_ENTRY;

typedef struct _RTL_HEAP_USAGE
{
    ULONG Length;
    SIZE_T BytesAllocated;
    SIZE_T BytesCommitted;
    SIZE_T BytesReserved;
    SIZE_T BytesReservedMaximum;
    PRTL_HEAP_USAGE_ENTRY Entries;
    PRTL_HEAP_USAGE_ENTRY AddedEntries;
    PRTL_HEAP_USAGE_ENTRY RemovedEntries;
    ULONG_PTR Reserved[8];
} RTL_HEAP_USAGE, * PRTL_HEAP_USAGE;

#define HEAP_USAGE_ALLOCATED_BLOCKS HEAP_REALLOC_IN_PLACE_ONLY
#define HEAP_USAGE_FREE_BUFFER HEAP_ZERO_MEMORY

NTSYSAPI
NTSTATUS
NTAPI
RtlUsageHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _Inout_ PRTL_HEAP_USAGE Usage
);

typedef struct _RTL_HEAP_WALK_ENTRY
{
    PVOID DataAddress;
    SIZE_T DataSize;
    UCHAR OverheadBytes;
    UCHAR SegmentIndex;
    USHORT Flags;
    union
    {
        struct
        {
            SIZE_T Settable;
            USHORT TagIndex;
            USHORT AllocatorBackTraceIndex;
            ULONG Reserved[2];
        } Block;
        struct
        {
            ULONG CommittedSize;
            ULONG UnCommittedSize;
            PVOID FirstEntry;
            PVOID LastEntry;
        } Segment;
    };
} RTL_HEAP_WALK_ENTRY, * PRTL_HEAP_WALK_ENTRY;

NTSYSAPI
NTSTATUS
NTAPI
RtlWalkHeap(
    _In_ PVOID HeapHandle,
    _Inout_ PRTL_HEAP_WALK_ENTRY Entry
);

// HEAP_INFORMATION_CLASS
#define HeapCompatibilityInformation        ((HEAP_INFORMATION_CLASS)0x0       ) // q; s: ULONG
#define HeapEnableTerminationOnCorruption   ((HEAP_INFORMATION_CLASS)0x1       ) // q; s: NULL
#define HeapExtendedInformation             ((HEAP_INFORMATION_CLASS)0x2       ) // q; s: HEAP_EXTENDED_INFORMATION
#define HeapOptimizeResources               ((HEAP_INFORMATION_CLASS)0x3       ) // q; s: HEAP_OPTIMIZE_RESOURCES_INFORMATION
#define HeapTaggingInformation              ((HEAP_INFORMATION_CLASS)0x4       )
#define HeapStackDatabase                   ((HEAP_INFORMATION_CLASS)0x5       ) // q: RTL_HEAP_STACK_QUERY; s: RTL_HEAP_STACK_CONTROL
#define HeapMemoryLimit                     ((HEAP_INFORMATION_CLASS)0x6       ) // since 19H2
#define HeapTag                             ((HEAP_INFORMATION_CLASS)0x6       ) // since 20H1
#define HeapDetailedFailureInformation      ((HEAP_INFORMATION_CLASS)0x80000001)
#define HeapSetDebuggingInformation         ((HEAP_INFORMATION_CLASS)0x80000002) // q; s: HEAP_DEBUGGING_INFORMATION

typedef enum _HEAP_COMPATIBILITY_MODE
{
    HEAP_COMPATIBILITY_STANDARD = 0UL,
    HEAP_COMPATIBILITY_LAL = 1UL,
    HEAP_COMPATIBILITY_LFH = 2UL,
} HEAP_COMPATIBILITY_MODE;

typedef struct _RTLP_TAG_INFO
{
    GUID Id;
    ULONG_PTR CurrentAllocatedBytes;
} RTLP_TAG_INFO, * PRTLP_TAG_INFO;

typedef struct _RTLP_HEAP_TAGGING_INFO
{
    USHORT Version;
    USHORT Flags;
    PVOID ProcessHandle;
    ULONG_PTR EntriesCount;
    RTLP_TAG_INFO Entries[1];
} RTLP_HEAP_TAGGING_INFO, * PRTLP_HEAP_TAGGING_INFO;

typedef struct _PROCESS_HEAP_INFORMATION
{
    SIZE_T ReserveSize;
    SIZE_T CommitSize;
    ULONG NumberOfHeaps;
    ULONG_PTR FirstHeapInformationOffset;
} PROCESS_HEAP_INFORMATION, * PPROCESS_HEAP_INFORMATION;

typedef struct _HEAP_REGION_INFORMATION
{
    PVOID Address;
    SIZE_T ReserveSize;
    SIZE_T CommitSize;
    ULONG_PTR FirstRangeInformationOffset;
    ULONG_PTR NextRegionInformationOffset;
} HEAP_REGION_INFORMATION, * PHEAP_REGION_INFORMATION;

typedef struct _HEAP_RANGE_INFORMATION
{
    PVOID Address;
    SIZE_T Size;
    ULONG Type;
    ULONG Protection;
    ULONG_PTR FirstBlockInformationOffset;
    ULONG_PTR NextRangeInformationOffset;
} HEAP_RANGE_INFORMATION, * PHEAP_RANGE_INFORMATION;

typedef struct _HEAP_BLOCK_INFORMATION
{
    PVOID Address;
    ULONG Flags;
    SIZE_T DataSize;
    ULONG_PTR OverheadSize;
    ULONG_PTR NextBlockInformationOffset;
} HEAP_BLOCK_INFORMATION, * PHEAP_BLOCK_INFORMATION;

typedef struct _HEAP_INFORMATION
{
    PVOID Address;
    ULONG Mode;
    SIZE_T ReserveSize;
    SIZE_T CommitSize;
    ULONG_PTR FirstRegionInformationOffset;
    ULONG_PTR NextHeapInformationOffset;
} HEAP_INFORMATION, * PHEAP_INFORMATION;

typedef struct _SEGMENT_HEAP_PERFORMANCE_COUNTER_INFORMATION
{
    SIZE_T SegmentReserveSize;
    SIZE_T SegmentCommitSize;
    ULONG_PTR SegmentCount;
    SIZE_T AllocatedSize;
    SIZE_T LargeAllocReserveSize;
    SIZE_T LargeAllocCommitSize;
} SEGMENT_HEAP_PERFORMANCE_COUNTER_INFORMATION, * PSEGMENT_HEAP_PERFORMANCE_COUNTER_INFORMATION;

#define HeapPerformanceCountersInformationStandardHeapVersion 0x1
#define HeapPerformanceCountersInformationSegmentHeapVersion 0x2

typedef struct _HEAP_PERFORMANCE_COUNTERS_INFORMATION
{
    ULONG Size;
    ULONG Version;
    ULONG HeapIndex;
    ULONG LastHeapIndex;
    PVOID BaseAddress;
    SIZE_T ReserveSize;
    SIZE_T CommitSize;
    ULONG SegmentCount;
    SIZE_T LargeUCRMemory;
    ULONG UCRLength;
    SIZE_T AllocatedSpace;
    SIZE_T FreeSpace;
    ULONG FreeListLength;
    ULONG Contention;
    ULONG VirtualBlocks;
    ULONG CommitRate;
    ULONG DecommitRate;
    SEGMENT_HEAP_PERFORMANCE_COUNTER_INFORMATION SegmentHeapPerfInformation; // since WIN8
} HEAP_PERFORMANCE_COUNTERS_INFORMATION, * PHEAP_PERFORMANCE_COUNTERS_INFORMATION;

typedef struct _HEAP_INFORMATION_ITEM
{
    ULONG Level;
    SIZE_T Size;
    union
    {
        PROCESS_HEAP_INFORMATION ProcessHeapInformation;
        HEAP_INFORMATION HeapInformation;
        HEAP_REGION_INFORMATION HeapRegionInformation;
        HEAP_RANGE_INFORMATION HeapRangeInformation;
        HEAP_BLOCK_INFORMATION HeapBlockInformation;
        HEAP_PERFORMANCE_COUNTERS_INFORMATION HeapPerfInformation;
        ULONG_PTR DynamicStart;
    };
} HEAP_INFORMATION_ITEM, * PHEAP_INFORMATION_ITEM;

typedef NTSTATUS(NTAPI* PRTL_HEAP_EXTENDED_ENUMERATION_ROUTINE)(
    _In_ PHEAP_INFORMATION_ITEM Information,
    _In_ PVOID Context
    );

// HEAP_EXTENDED_INFORMATION Level
#define HeapExtendedProcessHeapInformationLevel 0x1
#define HeapExtendedHeapInformationLevel        0x2
#define HeapExtendedHeapRegionInformationLevel  0x3
#define HeapExtendedHeapRangeInformationLevel   0x4
#define HeapExtendedHeapBlockInformationLevel   0x5
#define HeapExtendedHeapHeapPerfInformationLevel 0x80000000

typedef struct _HEAP_EXTENDED_INFORMATION
{
    HANDLE ProcessHandle;
    PVOID HeapHandle;
    ULONG Level;
    PRTL_HEAP_EXTENDED_ENUMERATION_ROUTINE CallbackRoutine;
    PVOID CallbackContext;
    union
    {
        PROCESS_HEAP_INFORMATION ProcessHeapInformation;
        HEAP_INFORMATION HeapInformation;
    };
} HEAP_EXTENDED_INFORMATION, * PHEAP_EXTENDED_INFORMATION;

// rev
typedef NTSTATUS(NTAPI* RTL_HEAP_STACK_WRITE_ROUTINE)(
    _In_ PVOID Information, // TODO: 3 missing structures (dmex)
    _In_ ULONG Size,
    _In_ PVOID Context
    );

// rev
typedef struct _RTLP_HEAP_STACK_TRACE_SERIALIZATION_INIT
{
    ULONG Count;
    ULONG Total;
    ULONG Flags;
} RTLP_HEAP_STACK_TRACE_SERIALIZATION_INIT, * PRTLP_HEAP_STACK_TRACE_SERIALIZATION_INIT;

// rev
typedef struct _RTLP_HEAP_STACK_TRACE_SERIALIZATION_HEADER
{
    USHORT Version;
    USHORT PointerSize;
    PVOID Heap;
    SIZE_T TotalCommit;
    SIZE_T TotalReserve;
} RTLP_HEAP_STACK_TRACE_SERIALIZATION_HEADER, * PRTLP_HEAP_STACK_TRACE_SERIALIZATION_HEADER;

// rev
typedef struct _RTLP_HEAP_STACK_TRACE_SERIALIZATION_ALLOCATION
{
    PVOID Address;
    ULONG Flags;
    SIZE_T DataSize;
} RTLP_HEAP_STACK_TRACE_SERIALIZATION_ALLOCATION, * PRTLP_HEAP_STACK_TRACE_SERIALIZATION_ALLOCATION;

// rev
typedef struct _RTLP_HEAP_STACK_TRACE_SERIALIZATION_STACKFRAME
{
    PVOID StackFrame[8];
} RTLP_HEAP_STACK_TRACE_SERIALIZATION_STACKFRAME, * PRTLP_HEAP_STACK_TRACE_SERIALIZATION_STACKFRAME;

#define HEAP_STACK_QUERY_VERSION 0x2

typedef struct _RTL_HEAP_STACK_QUERY
{
    ULONG Version;
    HANDLE ProcessHandle;
    RTL_HEAP_STACK_WRITE_ROUTINE WriteRoutine;
    PVOID SerializationContext;
    UCHAR QueryLevel;
    UCHAR Flags;
} RTL_HEAP_STACK_QUERY, * PRTL_HEAP_STACK_QUERY;

#define HEAP_STACK_CONTROL_VERSION 0x1
#define HEAP_STACK_CONTROL_FLAGS_STACKTRACE_ENABLE 0x1
#define HEAP_STACK_CONTROL_FLAGS_STACKTRACE_DISABLE 0x2

typedef struct _RTL_HEAP_STACK_CONTROL
{
    USHORT Version;
    USHORT Flags;
    HANDLE ProcessHandle;
} RTL_HEAP_STACK_CONTROL, * PRTL_HEAP_STACK_CONTROL;

// rev
typedef NTSTATUS(NTAPI* PRTL_HEAP_DEBUGGING_INTERCEPTOR_ROUTINE)(
    _In_ PVOID HeapHandle,
    _In_ ULONG Action,
    _In_ ULONG StackFramesToCapture,
    _In_ PVOID* StackTrace
    );

// rev
typedef NTSTATUS(NTAPI* PRTL_HEAP_LEAK_ENUMERATION_ROUTINE)(
    _In_ LONG Reserved,
    _In_ PVOID HeapHandle,
    _In_ PVOID BaseAddress,
    _In_ SIZE_T BlockSize,
    _In_ ULONG StackTraceDepth,
    _In_ PVOID* StackTrace
    );

// symbols
typedef struct _HEAP_DEBUGGING_INFORMATION
{
    PRTL_HEAP_DEBUGGING_INTERCEPTOR_ROUTINE InterceptorFunction;
    USHORT InterceptorValue;
    ULONG ExtendedOptions;
    ULONG StackTraceDepth;
    SIZE_T MinTotalBlockSize;
    SIZE_T MaxTotalBlockSize;
    PRTL_HEAP_LEAK_ENUMERATION_ROUTINE HeapLeakEnumerationRoutine;
} HEAP_DEBUGGING_INFORMATION, * PHEAP_DEBUGGING_INFORMATION;

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryHeapInformation(
    _In_opt_ PVOID HeapHandle,
    _In_ HEAP_INFORMATION_CLASS HeapInformationClass,
    _Out_opt_ PVOID HeapInformation,
    _In_opt_ SIZE_T HeapInformationLength,
    _Out_opt_ PSIZE_T ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetHeapInformation(
    _In_ PVOID HeapHandle,
    _In_ HEAP_INFORMATION_CLASS HeapInformationClass,
    _In_opt_ PVOID HeapInformation,
    _In_opt_ SIZE_T HeapInformationLength
);

NTSYSAPI
ULONG
NTAPI
RtlMultipleAllocateHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ SIZE_T Size,
    _In_ ULONG Count,
    _Out_ PVOID * Array
);

NTSYSAPI
ULONG
NTAPI
RtlMultipleFreeHeap(
    _In_ PVOID HeapHandle,
    _In_ ULONG Flags,
    _In_ ULONG Count,
    _In_ PVOID * Array
);

#if (NTDDI_VERSION >= NTDDI_WIN7)
NTSYSAPI
VOID
NTAPI
RtlDetectHeapLeaks(
    VOID
);
#endif

NTSYSAPI
VOID
NTAPI
RtlFlushHeaps(
    VOID
);

#endif // !_KERNEL_MODE

//
// Memory zones
//

#ifndef _KERNEL_MODE

// begin_private
typedef struct _RTL_MEMORY_ZONE_SEGMENT
{
    struct _RTL_MEMORY_ZONE_SEGMENT* NextSegment;
    SIZE_T Size;
    PVOID Next;
    PVOID Limit;
} RTL_MEMORY_ZONE_SEGMENT, * PRTL_MEMORY_ZONE_SEGMENT;

typedef struct _RTL_MEMORY_ZONE
{
    RTL_MEMORY_ZONE_SEGMENT Segment;
    RTL_SRWLOCK Lock;
    ULONG LockCount;
    PRTL_MEMORY_ZONE_SEGMENT FirstSegment;
} RTL_MEMORY_ZONE, * PRTL_MEMORY_ZONE;

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateMemoryZone(
    _Out_ PVOID* MemoryZone,
    _In_ SIZE_T InitialSize,
    _Reserved_ ULONG Flags
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyMemoryZone(
    _In_ _Post_invalid_ PVOID MemoryZone
);

NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateMemoryZone(
    _In_ PVOID MemoryZone,
    _In_ SIZE_T BlockSize,
    _Out_ PVOID* Block
);

NTSYSAPI
NTSTATUS
NTAPI
RtlResetMemoryZone(
    _In_ PVOID MemoryZone
);

NTSYSAPI
NTSTATUS
NTAPI
RtlLockMemoryZone(
    _In_ PVOID MemoryZone
);

NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockMemoryZone(
    _In_ PVOID MemoryZone
);
#endif
// end_private

#endif // !_KERNEL_MODE

//
// Memory block lookaside lists
//

#ifndef _KERNEL_MODE

// begin_private
#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateMemoryBlockLookaside(
    _Out_ PVOID* MemoryBlockLookaside,
    _Reserved_ ULONG Flags,
    _In_ ULONG InitialSize,
    _In_ ULONG MinimumBlockSize,
    _In_ ULONG MaximumBlockSize
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
);

NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside,
    _In_ ULONG BlockSize,
    _Out_ PVOID* Block
);

NTSYSAPI
NTSTATUS
NTAPI
RtlFreeMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside,
    _In_ PVOID Block
);

NTSYSAPI
NTSTATUS
NTAPI
RtlExtendMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside,
    _In_ ULONG Increment
);

NTSYSAPI
NTSTATUS
NTAPI
RtlResetMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
);

NTSYSAPI
NTSTATUS
NTAPI
RtlLockMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
);

NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockMemoryBlockLookaside(
    _In_ PVOID MemoryBlockLookaside
);
#endif
// end_private

#endif // !_KERNEL_MODE

//
// Transactions
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
HANDLE
NTAPI
RtlGetCurrentTransaction(
    VOID
);

// private
NTSYSAPI
LOGICAL
NTAPI
RtlSetCurrentTransaction(
    _In_opt_ HANDLE TransactionHandle
);
#endif

#endif // _KERNEL_MODE

//
// LUIDs
//

#ifndef _KERNEL_MODE

FORCEINLINE BOOLEAN RtlIsEqualLuid( // RtlEqualLuid
    _In_ PLUID L1,
    _In_ PLUID L2
)
{
    return L1->LowPart == L2->LowPart &&
        L1->HighPart == L2->HighPart;
}

#define RtlEqualLuid RtlIsEqualLuid

FORCEINLINE BOOLEAN RtlIsZeroLuid(
    _In_ PLUID L1
)
{
    return (L1->LowPart | L1->HighPart) == 0;
}

FORCEINLINE LUID RtlConvertLongToLuid(
    _In_ LONG Long
)
{
    LUID tempLuid;
    LARGE_INTEGER tempLi;

    tempLi.QuadPart = Long;
    tempLuid.LowPart = tempLi.LowPart;
    tempLuid.HighPart = tempLi.HighPart;

    return tempLuid;
}

FORCEINLINE LUID RtlConvertUlongToLuid(
    _In_ ULONG Ulong
)
{
    LUID tempLuid;

    tempLuid.LowPart = Ulong;
    tempLuid.HighPart = 0;

    return tempLuid;
}

NTSYSAPI
VOID
NTAPI
RtlCopyLuid(
    _Out_ PLUID DestinationLuid,
    _In_ PLUID SourceLuid
);

#endif // !_KERNEL_MODE

// ros
NTSYSAPI
VOID
NTAPI
RtlCopyLuidAndAttributesArray(
    _In_ ULONG Count,
    _In_ PLUID_AND_ATTRIBUTES Src,
    _In_ PLUID_AND_ATTRIBUTES Dest
);

//
// Byte swap routines.
//

#ifndef _KERNEL_MODE

//
// Byte swap routines.  These are used to convert from little-endian to
// big-endian and vice-versa.
//

#if (defined(_M_IX86) && (_MSC_FULL_VER > 13009037)) || ((defined(_M_AMD64) || defined(_M_IA64)) && (_MSC_FULL_VER > 13009175)) || defined(_M_ARM) || defined(_M_ARM64)

#ifdef __cplusplus
extern "C" {
#endif
    _Check_return_ unsigned short __cdecl _byteswap_ushort(_In_ unsigned short);
    _Check_return_ unsigned long  __cdecl _byteswap_ulong(_In_ unsigned long);
    _Check_return_ unsigned __int64 __cdecl _byteswap_uint64(_In_ unsigned __int64);
#ifdef __cplusplus
}
#endif
#pragma intrinsic(_byteswap_ushort)
#pragma intrinsic(_byteswap_ulong)
#pragma intrinsic(_byteswap_uint64)

#define RtlUshortByteSwap(_x)    _byteswap_ushort((USHORT)(_x))
#define RtlUlongByteSwap(_x)     _byteswap_ulong((_x))
#define RtlUlonglongByteSwap(_x) _byteswap_uint64((_x))

#else

NTSYSAPI
USHORT
FASTCALL
RtlUshortByteSwap(
    _In_ USHORT Source
);

NTSYSAPI
ULONG
FASTCALL
RtlUlongByteSwap(
    _In_ ULONG Source
);

NTSYSAPI
ULONGLONG
FASTCALL
RtlUlonglongByteSwap(
    _In_ ULONGLONG Source
);
#endif

#endif // !_KERNEL_MODE

//
// Debugging
//

#ifndef _KERNEL_MODE

// private
typedef struct _RTL_PROCESS_VERIFIER_OPTIONS
{
    ULONG SizeStruct;
    ULONG Option;
    UCHAR OptionData[1];
} RTL_PROCESS_VERIFIER_OPTIONS, * PRTL_PROCESS_VERIFIER_OPTIONS;

// private
typedef struct _RTL_DEBUG_INFORMATION
{
    HANDLE SectionHandleClient;
    PVOID ViewBaseClient;
    PVOID ViewBaseTarget;
    ULONG_PTR ViewBaseDelta;
    HANDLE EventPairClient;
    HANDLE EventPairTarget;
    HANDLE TargetProcessId;
    HANDLE TargetThreadHandle;
    ULONG Flags;
    SIZE_T OffsetFree;
    SIZE_T CommitSize;
    SIZE_T ViewSize;
    union
    {
        struct _RTL_PROCESS_MODULES* Modules;
        struct _RTL_PROCESS_MODULE_INFORMATION_EX* ModulesEx;
    };
    struct _RTL_PROCESS_BACKTRACES* BackTraces;
    PVOID Heaps;
    struct _RTL_PROCESS_LOCKS* Locks;
    PVOID SpecificHeap;
    HANDLE TargetProcessHandle;
    PRTL_PROCESS_VERIFIER_OPTIONS VerifierOptions;
    PVOID ProcessHeap;
    HANDLE CriticalSectionHandle;
    HANDLE CriticalSectionOwnerThread;
    PVOID Reserved[4];
} RTL_DEBUG_INFORMATION, * PRTL_DEBUG_INFORMATION;

NTSYSAPI
PRTL_DEBUG_INFORMATION
NTAPI
RtlCreateQueryDebugBuffer(
    _In_opt_ ULONG MaximumCommit,
    _In_ BOOLEAN UseEventPair
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyQueryDebugBuffer(
    _In_ PRTL_DEBUG_INFORMATION Buffer
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
PVOID
NTAPI
RtlCommitDebugInfo(
    _Inout_ PRTL_DEBUG_INFORMATION Buffer,
    _In_ SIZE_T Size
);

// private
NTSYSAPI
VOID
NTAPI
RtlDeCommitDebugInfo(
    _Inout_ PRTL_DEBUG_INFORMATION Buffer,
    _In_ PVOID p,
    _In_ SIZE_T Size
);
#endif

#define RTL_QUERY_PROCESS_MODULES 0x00000001
#define RTL_QUERY_PROCESS_BACKTRACES 0x00000002
#define RTL_QUERY_PROCESS_HEAP_SUMMARY 0x00000004
#define RTL_QUERY_PROCESS_HEAP_TAGS 0x00000008
#define RTL_QUERY_PROCESS_HEAP_ENTRIES 0x00000010
#define RTL_QUERY_PROCESS_LOCKS 0x00000020
#define RTL_QUERY_PROCESS_MODULES32 0x00000040
#define RTL_QUERY_PROCESS_VERIFIER_OPTIONS 0x00000080 // rev
#define RTL_QUERY_PROCESS_MODULESEX 0x00000100 // rev
#define RTL_QUERY_PROCESS_HEAP_SEGMENTS 0x00000200
#define RTL_QUERY_PROCESS_CS_OWNER 0x00000400 // rev
#define RTL_QUERY_PROCESS_NONINVASIVE 0x80000000

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryProcessDebugInformation(
    _In_ HANDLE UniqueProcessId,
    _In_ ULONG Flags,
    _Inout_ PRTL_DEBUG_INFORMATION Buffer
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetProcessDebugInformation(
    _In_ HANDLE UniqueProcessId,
    _In_ ULONG Flags,
    _Inout_ PRTL_DEBUG_INFORMATION Buffer
);

#endif // !_KERNEL_MODE

//
// Messages
//

#ifdef _KERNEL_MODE

typedef struct _MESSAGE_RESOURCE_ENTRY {
    USHORT   Length;
    USHORT   Flags;
    UINT8    Text[1];
} MESSAGE_RESOURCE_ENTRY, * PMESSAGE_RESOURCE_ENTRY;

#define MESSAGE_RESOURCE_UNICODE    0x0001
#define MESSAGE_RESOURCE_UTF8       0x0002

typedef struct _MESSAGE_RESOURCE_BLOCK {
    UINT32 LowId;
    UINT32 HighId;
    UINT32 OffsetToEntries;
} MESSAGE_RESOURCE_BLOCK, * PMESSAGE_RESOURCE_BLOCK;

typedef struct _MESSAGE_RESOURCE_DATA {
    UINT32 NumberOfBlocks;
    MESSAGE_RESOURCE_BLOCK Blocks[1];
} MESSAGE_RESOURCE_DATA, * PMESSAGE_RESOURCE_DATA;

#endif // _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlFindMessage(
    _In_ PVOID DllHandle,
    _In_ ULONG MessageTableId,
    _In_ ULONG MessageLanguageId,
    _In_ ULONG MessageId,
    _Out_ PMESSAGE_RESOURCE_ENTRY* MessageEntry
);

#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
#define FORMAT_MESSAGE_FROM_STRING     0x00000400
#define FORMAT_MESSAGE_FROM_HMODULE    0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM     0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000
#define FORMAT_MESSAGE_ARGUMENT_ANSI   0x00004000
#define FORMAT_MESSAGE_MAX_WIDTH_MASK  0x000000FF

NTSYSAPI
NTSTATUS
NTAPI
RtlFormatMessage(
    _In_ PWSTR MessageFormat,
    _In_ ULONG MaximumWidth,
    _In_ BOOLEAN IgnoreInserts,
    _In_ BOOLEAN ArgumentsAreAnsi,
    _In_ BOOLEAN ArgumentsAreAnArray,
    _In_ va_list* Arguments,
    _Out_writes_bytes_to_(Length, *ReturnLength) PWSTR Buffer,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength
);

typedef struct _PARSE_MESSAGE_CONTEXT
{
    ULONG fFlags;
    ULONG cwSavColumn;
    SIZE_T iwSrc;
    SIZE_T iwDst;
    SIZE_T iwDstSpace;
    va_list lpvArgStart;
} PARSE_MESSAGE_CONTEXT, * PPARSE_MESSAGE_CONTEXT;

#define INIT_PARSE_MESSAGE_CONTEXT(ctx)             { (ctx)->fFlags = 0; }
#define TEST_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag)  ((ctx)->fFlags & (flag))
#define SET_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag)   ((ctx)->fFlags |= (flag))
#define CLEAR_PARSE_MESSAGE_CONTEXT_FLAG(ctx, flag) ((ctx)->fFlags &= ~(flag))

NTSYSAPI
NTSTATUS
NTAPI
RtlFormatMessageEx(
    _In_ PWSTR MessageFormat,
    _In_ ULONG MaximumWidth,
    _In_ BOOLEAN IgnoreInserts,
    _In_ BOOLEAN ArgumentsAreAnsi,
    _In_ BOOLEAN ArgumentsAreAnArray,
    _In_ va_list* Arguments,
    _Out_writes_bytes_to_(Length, *ReturnLength) PWSTR Buffer,
    _In_ ULONG Length,
    _Out_opt_ PULONG ReturnLength,
    _Out_opt_ PPARSE_MESSAGE_CONTEXT ParseContext
);

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlGetFileMUIPath(
    _In_ ULONG Flags,
    _In_ PCWSTR FilePath,
    _Inout_opt_ PWSTR Language,
    _Inout_ PULONG LanguageLength,
    _Out_opt_ PWSTR FileMUIPath,
    _Inout_ PULONG FileMUIPathLength,
    _Inout_ PULONGLONG Enumerator
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLoadString(
    _In_ PVOID DllHandle,
    _In_ ULONG StringId,
    _In_opt_ PCWSTR StringLanguage,
    _In_ ULONG Flags,
    _Out_ PCWSTR* ReturnString,
    _Out_opt_ PUSHORT ReturnStringLen,
    _Out_writes_(ReturnLanguageLen) PWSTR ReturnLanguageName,
    _Inout_opt_ PULONG ReturnLanguageLen
);
#endif // !_KERNEL_MODE

//
// RC Resource
//

#ifdef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlLoadLibraryAsDataFile(
    _In_  PCUNICODE_STRING FileName,
    _Out_ PVOID* ModBase,
    _Out_ SIZE_T* ModSize
);

NTSYSAPI
NTSTATUS
NTAPI
RtlFreeLibraryAsDataFile(
    _In_ PVOID ModBase
);

inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlLoadLibraryAsDataFile(
    _In_  PCUNICODE_STRING FileName,
    _Out_ PVOID* ModBase,
    _Out_ SIZE_T* ModSize
)
{
    return LdrLoadDataFile(FileName, ModBase, ModSize);
}

inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlFreeLibraryAsDataFile(
    _In_ PVOID ModBase
)
{
    return LdrUnloadDataFile(ModBase);
}

#if defined _M_IX86

_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlLoadLibraryAsDataFile@12, _VEIL_IMPL_RtlLoadLibraryAsDataFile);
_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlFreeLibraryAsDataFile@4, _VEIL_IMPL_RtlFreeLibraryAsDataFile);

#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64

_VEIL_DEFINE_IAT_SYMBOL(RtlLoadLibraryAsDataFile, _VEIL_IMPL_RtlLoadLibraryAsDataFile);
_VEIL_DEFINE_IAT_SYMBOL(RtlFreeLibraryAsDataFile, _VEIL_IMPL_RtlFreeLibraryAsDataFile);

#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlMapResourceId(
    _Out_ ULONG_PTR* To,
    _In_  LPCWSTR    From
);

NTSYSAPI
VOID
NTAPI
RtlUnmapResourceId(
    _In_ ULONG_PTR Id
);

inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlMapResourceId(
    _Out_ ULONG_PTR* To,
    _In_  LPCWSTR    From
)
{
    NTSTATUS Status = STATUS_SUCCESS;

    do
    {
        __try
        {
            *To = (ULONG_PTR)-1;

            if ((ULONG_PTR)From >= LDR_RESOURCE_ID_NAME_MINVAL)
            {
                if (*From == L'#')
                {
                    UNICODE_STRING UnicodeString = { 0 };
                    RtlInitUnicodeString(&UnicodeString, From + 1);

                    ULONG Integer = 0ul;
                    Status = RtlUnicodeStringToInteger(&UnicodeString, 10, &Integer);
                    if (!NT_SUCCESS(Status) || Integer > LDR_RESOURCE_ID_NAME_MASK)
                    {
                        if (NT_SUCCESS(Status))
                        {
                            Status = STATUS_INVALID_PARAMETER;
                        }
                    }
                    else
                    {
                        *To = Integer;
                    }
                }
                else
                {
#pragma warning(suppress: 4996)
                    PWSTR String = (PWSTR)ExAllocatePool(PagedPool, (wcslen(From) + 1) * sizeof(WCHAR));
                    if (String == NULL)
                    {
                        Status = STATUS_INSUFFICIENT_RESOURCES;
                    }
                    else
                    {
                        *To = (ULONG_PTR)String;

                        while (*From != UNICODE_NULL)
                        {
                            *String++ = RtlUpcaseUnicodeChar(*From++);
                        }

                        *String = UNICODE_NULL;
                    }
                }
            }
            else
            {
                *To = (ULONG_PTR)From;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            *To = (ULONG_PTR)-1;
        }

    } while (FALSE);

    return Status;
}

inline
VOID
NTAPI
_VEIL_IMPL_RtlUnmapResourceId(
    _In_ ULONG_PTR Id
)
{
    if (Id >= LDR_RESOURCE_ID_NAME_MINVAL && Id != -1)
    {
        ExFreePool((PVOID)Id);
    }
}

#if defined _M_IX86

_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlMapResourceId@8, _VEIL_IMPL_RtlMapResourceId);
_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlUnmapResourceId@4, _VEIL_IMPL_RtlUnmapResourceId);

#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64

_VEIL_DEFINE_IAT_SYMBOL(RtlMapResourceId, _VEIL_IMPL_RtlMapResourceId);
_VEIL_DEFINE_IAT_SYMBOL(RtlUnmapResourceId, _VEIL_IMPL_RtlUnmapResourceId);

#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlFindResource(
    _Out_ HRSRC* ResBase,
    _In_  PVOID   ModBase,
    _In_  LPCWSTR Name,
    _In_  LPCWSTR Type,
    _In_  UINT16  Language
);

NTSYSAPI
NTSTATUS
NTAPI
RtlLoadResource(
    _Out_ PVOID* ResBuff,
    _Out_ ULONG* ResSize,
    _In_  HRSRC  ResBase,
    _In_  PVOID  ModBase
);

inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlFindResource(
    _Out_ HRSRC* ResBase,
    _In_  PVOID   ModBase,
    _In_  LPCWSTR Name,
    _In_  LPCWSTR Type,
    _In_  UINT16  Language
)
{
    NTSTATUS Status = STATUS_SUCCESS;
    LDR_RESOURCE_INFO IdPath = { 0 };

    do
    {
        __try
        {
            Status = RtlMapResourceId(&IdPath.Type, Type);
            if (!NT_SUCCESS(Status))
            {
                break;
            }

            Status = RtlMapResourceId(&IdPath.Name, Name);
            if (!NT_SUCCESS(Status))
            {
                break;
            }

            IdPath.Language = Language;

            Status = LdrFindResource_U(ModBase, &IdPath, LDR_RESOURCE_LEVEL_DATA, (PIMAGE_RESOURCE_DATA_ENTRY*)ResBase);
            if (!NT_SUCCESS(Status))
            {
                break;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Status = GetExceptionCode();
        }

    } while (FALSE);

    RtlUnmapResourceId(IdPath.Type);
    RtlUnmapResourceId(IdPath.Name);

    return Status;
}

inline
NTSTATUS
NTAPI
_VEIL_IMPL_RtlLoadResource(
    _Out_ PVOID* ResBuff,
    _Out_ ULONG* ResSize,
    _In_  HRSRC  ResBase,
    _In_  PVOID  ModBase
)
{
    NTSTATUS Status = STATUS_SUCCESS;

    do
    {
        __try
        {
            Status = LdrAccessResource(ModBase,
                (PIMAGE_RESOURCE_DATA_ENTRY)ResBase, ResBuff, ResSize);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            Status = GetExceptionCode();
        }

    } while (FALSE);

    return Status;
}

#if defined _M_IX86

_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlFindResource@20, _VEIL_IMPL_RtlFindResource);
_VEIL_DEFINE_IAT_RAW_SYMBOL(RtlLoadResource@16, _VEIL_IMPL_RtlLoadResource);

#elif defined _M_X64 || defined _M_ARM || defined _M_ARM64

_VEIL_DEFINE_IAT_SYMBOL(RtlFindResource, _VEIL_IMPL_RtlFindResource);
_VEIL_DEFINE_IAT_SYMBOL(RtlLoadResource, _VEIL_IMPL_RtlLoadResource);

#endif

#endif // if _KERNEL_MODE

//
// Errors
//

_IRQL_requires_max_(APC_LEVEL)
_When_(Status < 0, _Out_range_(> , 0))
_When_(Status >= 0, _Out_range_(== , 0))
NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosError(
    _In_ NTSTATUS Status
);

_When_(Status < 0, _Out_range_(> , 0))
_When_(Status >= 0, _Out_range_(== , 0))
NTSYSAPI
ULONG
NTAPI
RtlNtStatusToDosErrorNoTeb(
    _In_ NTSTATUS Status
);

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlGetLastNtStatus(
    VOID
);

NTSYSAPI
LONG
NTAPI
RtlGetLastWin32Error(
    VOID
);

NTSYSAPI
VOID
NTAPI
RtlSetLastWin32ErrorAndNtStatusFromNtStatus(
    _In_ NTSTATUS Status
);

NTSYSAPI
VOID
NTAPI
RtlSetLastWin32Error(
    _In_ LONG Win32Error
);

NTSYSAPI
VOID
NTAPI
RtlRestoreLastWin32Error(
    _In_ LONG Win32Error
);

#define RTL_ERRORMODE_FAILCRITICALERRORS 0x0010
#define RTL_ERRORMODE_NOGPFAULTERRORBOX  0x0020
#define RTL_ERRORMODE_NOOPENFILEERRORBOX 0x0040

NTSYSAPI
ULONG
NTAPI
RtlGetThreadErrorMode(
    VOID
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetThreadErrorMode(
    _In_ ULONG NewMode,
    _Out_opt_ PULONG OldMode
);

#endif // !_KERNEL_MODE

//
// Windows Error Reporting
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlReportException(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ ULONG Flags
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlReportExceptionEx(
    _In_ PEXCEPTION_RECORD ExceptionRecord,
    _In_ PCONTEXT ContextRecord,
    _In_ ULONG Flags,
    _In_ PLARGE_INTEGER Timeout
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlWerpReportException(
    _In_ ULONG ProcessId,
    _In_ HANDLE CrashReportSharedMem,
    _In_ ULONG Flags,
    _Out_ PHANDLE CrashVerticalProcessHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlReportSilentProcessExit(
    _In_ HANDLE ProcessHandle,
    _In_ NTSTATUS ExitStatus
);
#endif

#endif // !_KERNEL_MODE

//
// Random
//

_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<= , MAXLONG)
NTSYSAPI
ULONG
NTAPI
RtlRandom(
    _Inout_ PULONG Seed
);

_IRQL_requires_max_(APC_LEVEL)
_Ret_range_(<= , MAXLONG)
NTSYSAPI
ULONG
NTAPI
RtlRandomEx(
    _Inout_ PULONG Seed
);

#ifndef _KERNEL_MODE

NTSYSAPI
ULONG
NTAPI
RtlUniform(
    _Inout_ PULONG Seed
);

#define RTL_IMPORT_TABLE_HASH_REVISION 1

NTSYSAPI
NTSTATUS
NTAPI
RtlComputeImportTableHash(
    _In_ HANDLE FileHandle,
    _Out_writes_bytes_(16) PCHAR Hash,
    _In_ ULONG ImportTableHashRevision // must be 1
);

#endif // !_KERNEL_MODE

//
// Integer conversion
//

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlIntegerToChar(
    _In_ ULONG Value,
    _In_opt_ ULONG Base,
    _In_ LONG OutputLength, // negative to pad to width
    _Out_ PSTR String
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCharToInteger(
    _In_z_ PCSZ String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlLargeIntegerToChar(
    _In_ PLARGE_INTEGER Value,
    _In_opt_ ULONG Base,
    _In_ LONG OutputLength,
    _Out_ PSTR String
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_At_(String->MaximumLength, _Const_)
NTSYSAPI
NTSTATUS
NTAPI
RtlIntegerToUnicodeString(
    _In_ ULONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_At_(String->MaximumLength, _Const_)
NTSYSAPI
NTSTATUS
NTAPI
RtlInt64ToUnicodeString(
    _In_ ULONGLONG Value,
    _In_opt_ ULONG Base,
    _Inout_ PUNICODE_STRING String
);

#ifndef _KERNEL_MODE

#ifdef _WIN64
#define RtlIntPtrToUnicodeString(Value, Base, String) RtlInt64ToUnicodeString(Value, Base, String)
#else
#define RtlIntPtrToUnicodeString(Value, Base, String) RtlIntegerToUnicodeString(Value, Base, String)
#endif

#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlUnicodeStringToInteger(
    _In_ PCUNICODE_STRING String,
    _In_opt_ ULONG Base,
    _Out_ PULONG Value
);

NTSTATUS
RtlUnicodeStringToInt64(
    _In_ PCUNICODE_STRING String,
    _In_opt_ ULONG Base,
    _Out_ PLONG64 Number,
    _Out_opt_ PWSTR* EndPointer
);

//
// IPv4/6 conversion
//
#include <ip2string.h>

//
// Time
//

#ifndef _KERNEL_MODE

typedef struct _TIME_FIELDS
{
    CSHORT Year;            // 1601...
    CSHORT Month;           // 1..12
    CSHORT Day;             // 1..31
    CSHORT Hour;            // 0..23
    CSHORT Minute;          // 0..59
    CSHORT Second;          // 0..59
    CSHORT Milliseconds;    // 0..999
    CSHORT Weekday;         // 0..6 = Sunday..Saturday
} TIME_FIELDS, * PTIME_FIELDS;

NTSYSAPI
BOOLEAN
NTAPI
RtlCutoverTimeToSystemTime(
    _In_ PTIME_FIELDS CutoverTime,
    _Out_ PLARGE_INTEGER SystemTime,
    _In_ PLARGE_INTEGER CurrentSystemTime,
    _In_ BOOLEAN ThisYear
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSystemTimeToLocalTime(
    _In_ PLARGE_INTEGER SystemTime,
    _Out_ PLARGE_INTEGER LocalTime
);

NTSYSAPI
NTSTATUS
NTAPI
RtlLocalTimeToSystemTime(
    _In_ PLARGE_INTEGER LocalTime,
    _Out_ PLARGE_INTEGER SystemTime
);

NTSYSAPI
VOID
NTAPI
RtlTimeToElapsedTimeFields(
    _In_ PLARGE_INTEGER Time,
    _Out_ PTIME_FIELDS TimeFields
);

NTSYSAPI
VOID
NTAPI
RtlTimeToTimeFields(
    _In_ PLARGE_INTEGER Time,
    _Out_ PTIME_FIELDS TimeFields
);

NTSYSAPI
BOOLEAN
NTAPI
RtlTimeFieldsToTime(
    _In_ PTIME_FIELDS TimeFields, // Weekday is ignored
    _Out_ PLARGE_INTEGER Time
);

NTSYSAPI
BOOLEAN
NTAPI
RtlTimeToSecondsSince1980(
    _In_ PLARGE_INTEGER Time,
    _Out_ PULONG ElapsedSeconds
);

NTSYSAPI
VOID
NTAPI
RtlSecondsSince1980ToTime(
    _In_ ULONG ElapsedSeconds,
    _Out_ PLARGE_INTEGER Time
);

NTSYSAPI
BOOLEAN
NTAPI
RtlTimeToSecondsSince1970(
    _In_ PLARGE_INTEGER Time,
    _Out_ PULONG ElapsedSeconds
);

NTSYSAPI
VOID
NTAPI
RtlSecondsSince1970ToTime(
    _In_ ULONG ElapsedSeconds,
    _Out_ PLARGE_INTEGER Time
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
ULONGLONG
NTAPI
RtlGetSystemTimePrecise(
    VOID
);

NTSYSAPI
BOOLEAN
NTAPI
RtlQueryUnbiasedInterruptTime(
    _Out_ PLARGE_INTEGER InterruptTime
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN11_CO)
NTSYSAPI
KSYSTEM_TIME
NTAPI
RtlGetSystemTimeAndBias(
    _Out_ KSYSTEM_TIME TimeZoneBias,
    _Out_opt_ PLARGE_INTEGER TimeZoneBiasEffectiveStart,
    _Out_opt_ PLARGE_INTEGER TimeZoneBiasEffectiveEnd
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI
LARGE_INTEGER
NTAPI
RtlGetInterruptTimePrecise(
    _Out_ PLARGE_INTEGER PerformanceCounter
);
#endif

#endif // !_KERNEL_MODE

//
// Time zones
//

// fix: WPP error: type redefinition
typedef struct _RTL_TIME_ZONE_INFORMATION_V
{
    LONG Bias;
    WCHAR StandardName[32];
    TIME_FIELDS StandardStart;
    LONG StandardBias;
    WCHAR DaylightName[32];
    TIME_FIELDS DaylightStart;
    LONG DaylightBias;
} RTL_TIME_ZONE_INFORMATION_V, * PRTL_TIME_ZONE_INFORMATION_V;

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryTimeZoneInformation(
    _Out_ PRTL_TIME_ZONE_INFORMATION_V TimeZoneInformation
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetTimeZoneInformation(
    _In_ PRTL_TIME_ZONE_INFORMATION_V TimeZoneInformation
);

//
// Bitmaps
//

//
//  BitMap routines.  The following structure, routines, and macros are
//  for manipulating bitmaps.  The user is responsible for allocating a bitmap
//  structure (which is really a header) and a buffer (which must be longword
//  aligned and multiple longwords in size).
//

#ifndef _KERNEL_MODE

typedef struct _RTL_BITMAP {
    ULONG SizeOfBitMap;                     // Number of bits in bit map
    PULONG Buffer;                          // Pointer to the bit map itself
} RTL_BITMAP;
typedef RTL_BITMAP* PRTL_BITMAP;

#endif // !_KERNEL_MODE

NTSYSAPI
VOID
NTAPI
RtlInitializeBitMap(
    _Out_ PRTL_BITMAP BitMapHeader,
    _In_opt_ __drv_aliasesMem PULONG BitMapBuffer,
    _In_opt_ ULONG SizeOfBitMap
);

NTSYSAPI
VOID
NTAPI
RtlClearBit(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(< , BitMapHeader->SizeOfBitMap) ULONG BitNumber
);

NTSYSAPI
VOID
NTAPI
RtlSetBit(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(< , BitMapHeader->SizeOfBitMap) ULONG BitNumber
);

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlTestBit(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(< , BitMapHeader->SizeOfBitMap) ULONG BitNumber
);

NTSYSAPI
VOID
NTAPI
RtlClearAllBits(
    _In_ PRTL_BITMAP BitMapHeader
);

NTSYSAPI
VOID
NTAPI
RtlSetAllBits(
    _In_ PRTL_BITMAP BitMapHeader
);

//
//  The following two routines locate a contiguous region of either
//  clear or set bits within the bitmap.  The region will be at least
//  as large as the number specified, and the search of the bitmap will
//  begin at the specified hint index (which is a bit index within the
//  bitmap, zero based).  The return value is the bit index of the located
//  region (zero based) or -1 (i.e., 0xffffffff) if such a region cannot
//  be located
//

_Success_(return != -1)
_Ret_range_(<= , BitMapHeader->SizeOfBitMap - NumberToFind)
_Must_inspect_result_
NTSYSAPI
ULONG
NTAPI
RtlFindClearBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
);

_Success_(return != -1)
_Ret_range_(<= , BitMapHeader->SizeOfBitMap - NumberToFind)
_Must_inspect_result_
NTSYSAPI
ULONG
NTAPI
RtlFindSetBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
);

//
//  The following two routines locate a contiguous region of either
//  clear or set bits within the bitmap and either set or clear the bits
//  within the located region.  The region will be as large as the number
//  specified, and the search for the region will begin at the specified
//  hint index (which is a bit index within the bitmap, zero based).  The
//  return value is the bit index of the located region (zero based) or
//  -1 (i.e., 0xffffffff) if such a region cannot be located.  If a region
//  cannot be located then the setting/clearing of the bitmap is not performed.
//

_Success_(return != -1)
_Ret_range_(<= , BitMapHeader->SizeOfBitMap - NumberToFind)
NTSYSAPI
ULONG
NTAPI
RtlFindClearBitsAndSet(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
);

_Success_(return != -1)
_Ret_range_(<= , BitMapHeader->SizeOfBitMap - NumberToFind)
NTSYSAPI
ULONG
NTAPI
RtlFindSetBitsAndClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG NumberToFind,
    _In_ ULONG HintIndex
);

NTSYSAPI
VOID
NTAPI
RtlClearBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear
);

NTSYSAPI
VOID
NTAPI
RtlSetBits(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet
);

//
//  The following routine locates a set of contiguous regions of clear
//  bits within the bitmap.  The caller specifies whether to return the
//  longest runs or just the first found lcoated.  The following structure is
//  used to denote a contiguous run of bits.  The two routines return an array
//  of this structure, one for each run located.
//

#ifndef _KERNEL_MODE

typedef struct _RTL_BITMAP_RUN {

    ULONG StartingIndex;
    ULONG NumberOfBits;

} RTL_BITMAP_RUN;
typedef RTL_BITMAP_RUN* PRTL_BITMAP_RUN;

#endif // !_KERNEL_MODE

NTSYSAPI
ULONG
NTAPI
RtlFindClearRuns(
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_writes_to_(SizeOfRunArray, return) PRTL_BITMAP_RUN RunArray,
    _In_range_(> , 0) ULONG SizeOfRunArray,
    _In_ BOOLEAN LocateLongestRuns
);

NTSYSAPI
ULONG
NTAPI
RtlFindLongestRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex
);

NTSYSAPI
ULONG
NTAPI
RtlFindFirstRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _Out_ PULONG StartingIndex
);

#ifndef _KERNEL_MODE

_Must_inspect_result_
FORCEINLINE
BOOLEAN
RtlCheckBit(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(< , BitMapHeader->SizeOfBitMap) ULONG BitPosition
)
{
#ifdef _WIN64
    return BitTest64((LONG64 const*)BitMapHeader->Buffer, (LONG64)BitPosition);
#else
    return (((PLONG)BitMapHeader->Buffer)[BitPosition / 32] >> (BitPosition % 32)) & 0x1;
#endif
}

#endif // !_KERNEL_MODE


#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
ULONG
NTAPI
RtlNumberOfClearBitsInRange(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
);

NTSYSAPI
ULONG
NTAPI
RtlNumberOfSetBitsInRange(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
);
#endif

NTSYSAPI
ULONG
NTAPI
RtlNumberOfClearBits(
    _In_ PRTL_BITMAP BitMapHeader
);

NTSYSAPI
ULONG
NTAPI
RtlNumberOfSetBits(
    _In_ PRTL_BITMAP BitMapHeader
);

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlAreBitsClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
);

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlAreBitsSet(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG StartingIndex,
    _In_ ULONG Length
);

NTSYSAPI
ULONG
NTAPI
RtlFindNextForwardRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex
);

NTSYSAPI
ULONG
NTAPI
RtlFindLastBackwardRunClear(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_ ULONG FromIndex,
    _Out_ PULONG StartingRunIndex
);

_Success_(return != -1)
_Must_inspect_result_
NTSYSAPI
CCHAR
NTAPI
RtlFindLeastSignificantBit(
    _In_ ULONGLONG Set
);

_Success_(return != -1)
_Must_inspect_result_
NTSYSAPI
CCHAR
NTAPI
RtlFindMostSignificantBit(
    _In_ ULONGLONG Set
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
ULONG
NTAPI
RtlNumberOfSetBitsUlongPtr(
    _In_ ULONG_PTR Target
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
NTSYSAPI
VOID
NTAPI
RtlCopyBitMap(
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Destination->SizeOfBitMap - 1) ULONG TargetBit
);

NTSYSAPI
VOID
NTAPI
RtlExtractBitMap(
    _In_ PRTL_BITMAP Source,
    _In_ PRTL_BITMAP Destination,
    _In_range_(0, Source->SizeOfBitMap - 1) ULONG TargetBit,
    _In_range_(0, Source->SizeOfBitMap) ULONG NumberOfBits
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
VOID
NTAPI
RtlInterlockedClearBitRun(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToClear) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToClear
);

// rev
NTSYSAPI
VOID
NTAPI
RtlInterlockedSetBitRun(
    _In_ PRTL_BITMAP BitMapHeader,
    _In_range_(0, BitMapHeader->SizeOfBitMap - NumberToSet) ULONG StartingIndex,
    _In_range_(0, BitMapHeader->SizeOfBitMap - StartingIndex) ULONG NumberToSet
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
// private
typedef struct _RTL_BITMAP_EX
{
    ULONG64 SizeOfBitMap;
    PULONG64 Buffer;
} RTL_BITMAP_EX, * PRTL_BITMAP_EX;

// rev
NTSYSAPI
VOID
NTAPI
RtlInitializeBitMapEx(
    _Out_ PRTL_BITMAP_EX BitMapHeader,
    _In_ PULONG64 BitMapBuffer,
    _In_ ULONG64 SizeOfBitMap
);

// rev
_Check_return_
NTSYSAPI
BOOLEAN
NTAPI
RtlTestBitEx(
    _In_ PRTL_BITMAP_EX BitMapHeader,
    _In_range_(< , BitMapHeader->SizeOfBitMap) ULONG64 BitNumber
);
#endif

//
// Handle tables
//

#ifndef _KERNEL_MODE

typedef struct _RTL_HANDLE_TABLE_ENTRY
{
    union
    {
        ULONG Flags; // allocated entries have the low bit set
        struct _RTL_HANDLE_TABLE_ENTRY* NextFree;
    };
} RTL_HANDLE_TABLE_ENTRY, * PRTL_HANDLE_TABLE_ENTRY;

#define RTL_HANDLE_ALLOCATED (USHORT)0x0001

typedef struct _RTL_HANDLE_TABLE
{
    ULONG MaximumNumberOfHandles;
    ULONG SizeOfHandleTableEntry;
    ULONG Reserved[2];
    PRTL_HANDLE_TABLE_ENTRY FreeHandles;
    PRTL_HANDLE_TABLE_ENTRY CommittedHandles;
    PRTL_HANDLE_TABLE_ENTRY UnCommittedHandles;
    PRTL_HANDLE_TABLE_ENTRY MaxReservedHandles;
} RTL_HANDLE_TABLE, * PRTL_HANDLE_TABLE;

NTSYSAPI
VOID
NTAPI
RtlInitializeHandleTable(
    _In_ ULONG MaximumNumberOfHandles,
    _In_ ULONG SizeOfHandleTableEntry,
    _Out_ PRTL_HANDLE_TABLE HandleTable
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyHandleTable(
    _Inout_ PRTL_HANDLE_TABLE HandleTable
);

NTSYSAPI
PRTL_HANDLE_TABLE_ENTRY
NTAPI
RtlAllocateHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _Out_opt_ PULONG HandleIndex
);

NTSYSAPI
BOOLEAN
NTAPI
RtlFreeHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _In_ PRTL_HANDLE_TABLE_ENTRY Handle
);

NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _In_ PRTL_HANDLE_TABLE_ENTRY Handle
);

NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidIndexHandle(
    _In_ PRTL_HANDLE_TABLE HandleTable,
    _In_ ULONG HandleIndex,
    _Out_ PRTL_HANDLE_TABLE_ENTRY* Handle
);

#endif // !_KERNEL_MODE

//
// Atom tables
//

#define RTL_ATOM_MAXIMUM_INTEGER_ATOM               (RTL_ATOM)0xC000
#define RTL_ATOM_INVALID_ATOM                       (RTL_ATOM)0x0000
#define RTL_ATOM_TABLE_DEFAULT_NUMBER_OF_BUCKETS    37
#define RTL_ATOM_MAXIMUM_NAME_LENGTH                255
#define RTL_ATOM_PINNED                             0x01

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateAtomTable(
    _In_ ULONG NumberOfBuckets,
    _Out_ PVOID* AtomTableHandle
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDestroyAtomTable(
    _In_ _Post_invalid_ PVOID AtomTableHandle
);

NTSYSAPI
NTSTATUS
NTAPI
RtlEmptyAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ BOOLEAN IncludePinnedAtoms
);

NTSYSAPI
NTSTATUS
NTAPI
RtlAddAtomToAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ PWSTR AtomName,
    _Inout_opt_ PRTL_ATOM Atom
);

NTSYSAPI
NTSTATUS
NTAPI
RtlLookupAtomInAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ PWSTR AtomName,
    _Out_opt_ PRTL_ATOM Atom
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteAtomFromAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ RTL_ATOM Atom
);

NTSYSAPI
NTSTATUS
NTAPI
RtlPinAtomInAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ RTL_ATOM Atom
);

NTSYSAPI
NTSTATUS
NTAPI
RtlQueryAtomInAtomTable(
    _In_ PVOID AtomTableHandle,
    _In_ RTL_ATOM Atom,
    _Out_opt_ PULONG AtomUsage,
    _Out_opt_ PULONG AtomFlags,
    _Inout_updates_bytes_to_opt_(*AtomNameLength, *AtomNameLength) PWSTR AtomName,
    _Inout_opt_ PULONG AtomNameLength
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlGetIntegerAtom(
    _In_ PWSTR AtomName,
    _Out_opt_ PUSHORT IntegerAtom
);
#endif

//
// SIDs
//

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlValidSid(
    _In_ PSID Sid
);

_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualSid(
    _In_ PSID Sid1,
    _In_ PSID Sid2
);

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlEqualPrefixSid(
    _In_ PSID Sid1,
    _In_ PSID Sid2
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
ULONG
NTAPI
RtlLengthRequiredSid(
    _In_ ULONG SubAuthorityCount
);

NTSYSAPI
PVOID
NTAPI
RtlFreeSid(
    _In_ _Post_invalid_ PSID Sid
);

_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateAndInitializeSid(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_ ULONG SubAuthority0,
    _In_ ULONG SubAuthority1,
    _In_ ULONG SubAuthority2,
    _In_ ULONG SubAuthority3,
    _In_ ULONG SubAuthority4,
    _In_ ULONG SubAuthority5,
    _In_ ULONG SubAuthority6,
    _In_ ULONG SubAuthority7,
    _Outptr_ PSID* Sid
);

#if (NTDDI_VERSION >= NTDDI_WIN8)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlAllocateAndInitializeSidEx(
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    _In_reads_(SubAuthorityCount) PULONG SubAuthorities,
    _Outptr_ PSID* Sid
);
#endif // NTDDI_VERSION >= NTDDI_WIN8

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeSid(
    _Out_ PSID Sid,
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount
);

#if (NTDDI_VERSION >= NTDDI_WINTHRESHOLD)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlInitializeSidEx(
    _Out_writes_bytes_(SECURITY_SID_SIZE(SubAuthorityCount)) PSID Sid,
    _In_ PSID_IDENTIFIER_AUTHORITY IdentifierAuthority,
    _In_ UCHAR SubAuthorityCount,
    ...
);
#endif

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
PSID_IDENTIFIER_AUTHORITY
NTAPI
RtlIdentifierAuthoritySid(
    _In_ PSID Sid
);

NTSYSAPI
PULONG
NTAPI
RtlSubAuthoritySid(
    _In_ PSID Sid,
    _In_ ULONG SubAuthority
);

NTSYSAPI
PUCHAR
NTAPI
RtlSubAuthorityCountSid(
    _In_ PSID Sid
);

NTSYSAPI
_Post_satisfies_(return >= 8 && return <= SECURITY_MAX_SID_SIZE)
ULONG
NTAPI
RtlLengthSid(
    _In_ PSID Sid
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCopySid(
    _In_ ULONG DestinationSidLength,
    _Out_writes_bytes_(DestinationSidLength) PSID DestinationSid,
    _In_ PSID SourceSid
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateServiceSid(
    _In_ PUNICODE_STRING ServiceName,
    _Out_writes_bytes_opt_(*ServiceSidLength) PSID ServiceSid,
    _Inout_ PULONG ServiceSidLength
);
#endif

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlCopySidAndAttributesArray(
    _In_ ULONG Count,
    _In_ PSID_AND_ATTRIBUTES Src,
    _In_ ULONG SidAreaSize,
    _In_ PSID_AND_ATTRIBUTES Dest,
    _In_ PSID SidArea,
    _Out_ PSID* RemainingSidArea,
    _Out_ PULONG RemainingSidAreaSize
);

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidDominates(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN Dominates
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSidDominatesForTrust(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN DominatesTrust // TokenProcessTrustLevel
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidEqualLevel(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN EqualLevel
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidIsHigherLevel(
    _In_ PSID Sid1,
    _In_ PSID Sid2,
    _Out_ PBOOLEAN HigherLevel
);
#endif

#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN7)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlReplaceSidInSd(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ PSID OldSid,
    _In_ PSID NewSid,
    _Out_ ULONG * NumChanges
);

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateVirtualAccountSid(
    _In_ PCUNICODE_STRING Name,
    _In_ ULONG BaseSubAuthority,
    _Out_writes_bytes_(*SidLength) PSID Sid,
    _Inout_ PULONG SidLength
);
#endif

//
// MAX_UNICODE_STACK_BUFFER_LENGTH is the maximum stack buffer
// that RtlConvertSidToUnicodeString can fill if the caller
// specifies AllocateDestinationString = FALSE.
//

#ifndef _KERNEL_MODE
#define MAX_UNICODE_STACK_BUFFER_LENGTH 256
#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlConvertSidToUnicodeString(
    _Inout_ PUNICODE_STRING UnicodeString,
    _In_ PSID Sid,
    _In_ BOOLEAN AllocateDestinationString
);

#ifndef _KERNEL_MODE
NTSYSAPI
NTSTATUS
NTAPI
RtlLengthSidAsUnicodeString(
    _In_ PSID Sid,
    _Out_ PULONG StringLength
);
#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSidHashInitialize(
    _In_reads_(SidCount) PSID_AND_ATTRIBUTES SidAttr,
    _In_ ULONG SidCount,
    _Out_ PSID_AND_ATTRIBUTES_HASH SidAttrHash
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
PSID_AND_ATTRIBUTES
NTAPI
RtlSidHashLookup(
    _In_ PSID_AND_ATTRIBUTES_HASH SidAttrHash,
    _In_ PSID Sid
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsElevatedRid(
    _In_ PSID_AND_ATTRIBUTES SidAttr
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDeriveCapabilitySidsFromName(
    _Inout_ PUNICODE_STRING UnicodeString,
    _Out_ PSID CapabilityGroupSid,
    _Out_ PSID CapabilitySid
);
#endif

//
// Security Descriptors
//

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateSecurityDescriptor(
    _Out_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ ULONG Revision
);

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlValidSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
ULONG
NTAPI
RtlLengthSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
);

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlValidRelativeSecurityDescriptor(
    _In_reads_bytes_(SecurityDescriptorLength) PSECURITY_DESCRIPTOR SecurityDescriptorInput,
    _In_ ULONG SecurityDescriptorLength,
    _In_ SECURITY_INFORMATION RequiredInformation
);

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlGetControlSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR_CONTROL Control,
    _Out_ PULONG Revision
);

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlSetControlSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsOfInterest,
    _In_ SECURITY_DESCRIPTOR_CONTROL ControlBitsToSet
);

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlSetAttributesSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ SECURITY_DESCRIPTOR_CONTROL Control,
    _Out_ PULONG Revision
);

NTSYSAPI
BOOLEAN
NTAPI
RtlGetSecurityDescriptorRMControl(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PUCHAR RMControl
);

NTSYSAPI
VOID
NTAPI
RtlSetSecurityDescriptorRMControl(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PUCHAR RMControl
);

#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlSetDaclSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN DaclPresent,
    _In_opt_ PACL Dacl,
    _In_ BOOLEAN DaclDefaulted
);

NTSYSAPI
NTSTATUS
NTAPI
RtlGetDaclSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PBOOLEAN DaclPresent,
    _Outptr_result_maybenull_ PACL* Dacl,
    _Pre_ _Writable_elements_(1)
    _When_(!(*DaclPresent), _Post_invalid_)
    _When_((*DaclPresent), _Post_valid_)
    PBOOLEAN DaclDefaulted
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlSetSaclSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_ BOOLEAN SaclPresent,
    _In_opt_ PACL Sacl,
    _In_ BOOLEAN SaclDefaulted
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlGetSaclSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Out_ PBOOLEAN SaclPresent,
    _Out_ PACL* Sacl,
    _Out_ PBOOLEAN SaclDefaulted
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlSetOwnerSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID Owner,
    _In_ BOOLEAN OwnerDefaulted
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlGetOwnerSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_result_maybenull_ PSID* Owner,
    _When_(*Owner == NULL, _Post_invalid_)
    _When_(*Owner != NULL, _Post_valid_)
    _Pre_ _Notnull_ _Pre_ _Writable_elements_(1) PBOOLEAN OwnerDefaulted
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlSetGroupSecurityDescriptor(
    _Inout_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _In_opt_ PSID Group,
    _In_ BOOLEAN GroupDefaulted
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlGetGroupSecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR SecurityDescriptor,
    _Outptr_result_maybenull_ PSID* Group,
    _Pre_ _Notnull_ _Pre_ _Writable_elements_(1)
    _When_(*Group == NULL, _Post_invalid_)
    _When_(*Group != NULL, _Post_valid_)
    PBOOLEAN GroupDefaulted
);

#ifndef _KERNEL_MODE
NTSYSAPI
NTSTATUS
NTAPI
RtlMakeSelfRelativeSD(
    _In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Out_writes_bytes_(*BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Inout_ PULONG BufferLength
);
#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAbsoluteToSelfRelativeSD(
    _In_ PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Out_writes_bytes_to_opt_(*BufferLength, *BufferLength) PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Inout_ PULONG BufferLength
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlSelfRelativeToAbsoluteSD(
    _In_ PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Out_writes_bytes_to_opt_(*AbsoluteSecurityDescriptorSize, *AbsoluteSecurityDescriptorSize) PSECURITY_DESCRIPTOR AbsoluteSecurityDescriptor,
    _Inout_ PULONG AbsoluteSecurityDescriptorSize,
    _Out_writes_bytes_to_opt_(*DaclSize, *DaclSize) PACL Dacl,
    _Inout_ PULONG DaclSize,
    _Out_writes_bytes_to_opt_(*SaclSize, *SaclSize) PACL Sacl,
    _Inout_ PULONG SaclSize,
    _Out_writes_bytes_to_opt_(*OwnerSize, *OwnerSize) PSID Owner,
    _Inout_ PULONG OwnerSize,
    _Out_writes_bytes_to_opt_(*PrimaryGroupSize, *PrimaryGroupSize) PSID PrimaryGroup,
    _Inout_ PULONG PrimaryGroupSize
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlSelfRelativeToAbsoluteSD2(
    _Inout_ PSECURITY_DESCRIPTOR SelfRelativeSecurityDescriptor,
    _Inout_ PULONG BufferSize
);

//
// Access masks
//

NTSYSAPI
BOOLEAN
NTAPI
RtlAreAllAccessesGranted(
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ACCESS_MASK DesiredAccess
);
//{
//    return (~GrantedAccess & DesiredAccess) == 0;
//}

NTSYSAPI
BOOLEAN
NTAPI
RtlAreAnyAccessesGranted(
    _In_ ACCESS_MASK GrantedAccess,
    _In_ ACCESS_MASK DesiredAccess
);
//{
//    return (GrantedAccess & DesiredAccess) != 0;
//}

//
// ACLs
//

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateAcl(
    _Out_writes_bytes_(AclLength) PACL Acl,
    _In_ ULONG AclLength,
    _In_ ULONG AclRevision
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG StartingAceIndex,
    _In_reads_bytes_(AceListLength) PVOID AceList,
    _In_ ULONG AceListLength
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceIndex
);

NTSYSAPI
NTSTATUS
NTAPI
RtlGetAce(
    _In_ PACL Acl,
    _In_ ULONG AceIndex,
    _Outptr_ PVOID* Ace
);

NTSYSAPI
BOOLEAN
NTAPI
RtlValidAcl(
    _In_ PACL Acl
);

#ifdef _KERNEL_MODE

//
// Currently define Flags for "OBJECT" ACE types.
//

#define ACE_OBJECT_TYPE_PRESENT           0x1
#define ACE_INHERITED_OBJECT_TYPE_PRESENT 0x2


//
//  The following declarations are used for setting and querying information
//  about and ACL.  First are the various information classes available to
//  the user.
//

typedef enum _ACL_INFORMATION_CLASS {
    AclRevisionInformation = 1,
    AclSizeInformation
} ACL_INFORMATION_CLASS;

//
//  This record is returned/sent if the user is requesting/setting the
//  AclRevisionInformation
//

typedef struct _ACL_REVISION_INFORMATION {
    UINT32 AclRevision;
} ACL_REVISION_INFORMATION;
typedef ACL_REVISION_INFORMATION* PACL_REVISION_INFORMATION;

//
//  This record is returned if the user is requesting AclSizeInformation
//

typedef struct _ACL_SIZE_INFORMATION {
    UINT32 AceCount;
    UINT32 AclBytesInUse;
    UINT32 AclBytesFree;
} ACL_SIZE_INFORMATION;
typedef ACL_SIZE_INFORMATION* PACL_SIZE_INFORMATION;

#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryInformationAcl(
    _In_ PACL Acl,
    _Out_writes_bytes_(AclInformationLength) PVOID AclInformation,
    _In_ ULONG AclInformationLength,
    _In_ ACL_INFORMATION_CLASS AclInformationClass
);

#ifndef _KERNEL_MODE
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlSetInformationAcl(
    _Inout_ PACL Acl,
    _In_reads_bytes_(AclInformationLength) PVOID AclInformation,
    _In_ ULONG AclInformationLength,
    _In_ ACL_INFORMATION_CLASS AclInformationClass
);
#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
BOOLEAN
NTAPI
RtlFirstFreeAce(
    _In_ PACL Acl,
    _Out_ PVOID* FirstFree
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
PVOID
NTAPI
RtlFindAceByType(
    _In_ PACL Acl,
    _In_ UCHAR AceType,
    _Out_opt_ PULONG Index
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
BOOLEAN
NTAPI
RtlOwnerAcesPresent(
    _In_ PACL pAcl
);
#endif

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedAceEx(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
);

#ifndef _KERNEL_MODE
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessDeniedAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
);
#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessDeniedAceEx(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid
);

#ifndef _KERNEL_MODE
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAuditAccessAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid,
    _In_ BOOLEAN AuditSuccess,
    _In_ BOOLEAN AuditFailure
);
#endif // !_KERNEL_MODE

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAuditAccessAceEx(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID Sid,
    _In_ BOOLEAN AuditSuccess,
    _In_ BOOLEAN AuditFailure
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessAllowedObjectAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_opt_ PGUID ObjectTypeGuid,
    _In_opt_ PGUID InheritedObjectTypeGuid,
    _In_ PSID Sid
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAccessDeniedObjectAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_opt_ PGUID ObjectTypeGuid,
    _In_opt_ PGUID InheritedObjectTypeGuid,
    _In_ PSID Sid
);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddAuditAccessObjectAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ACCESS_MASK AccessMask,
    _In_opt_ PGUID ObjectTypeGuid,
    _In_opt_ PGUID InheritedObjectTypeGuid,
    _In_ PSID Sid,
    _In_ BOOLEAN AuditSuccess,
    _In_ BOOLEAN AuditFailure
);

#ifndef _KERNEL_MODE
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddCompoundAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ UCHAR AceType,
    _In_ ACCESS_MASK AccessMask,
    _In_ PSID ServerSid,
    _In_ PSID ClientSid
);
#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddMandatoryAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ PSID Sid,
    _In_ UCHAR AceType,
    _In_ ACCESS_MASK AccessMask
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddResourceAttributeAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ULONG AccessMask,
    _In_ PSID Sid,
    _In_ PCLAIM_SECURITY_ATTRIBUTES_INFORMATION AttributeInfo,
    _Out_ PULONG ReturnLength
);
#endif //NTDDI_VERSION >= NTDDI_WIN8

#ifndef _KERNEL_MODE
#if (NTDDI_VERSION >= NTDDI_WIN8)
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlAddScopedPolicyIDAce(
    _Inout_ PACL Acl,
    _In_ ULONG AceRevision,
    _In_ ULONG AceFlags,
    _In_ ULONG AccessMask,
    _In_ PSID Sid
);
#endif //NTDDI_VERSION >= NTDDI_WIN8

// Named pipes

NTSYSAPI
NTSTATUS
NTAPI
RtlDefaultNpAcl(
    _Out_ PACL* Acl
);
#endif // !_KERNEL_MODE

//
// Security objects
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlNewSecurityObject(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR* NewDescriptor,
    _In_ BOOLEAN IsDirectoryObject,
    _In_opt_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI
NTSTATUS
NTAPI
RtlNewSecurityObjectEx(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR* NewDescriptor,
    _In_opt_ GUID* ObjectType,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ ULONG AutoInheritFlags, // SEF_*
    _In_opt_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI
NTSTATUS
NTAPI
RtlNewSecurityObjectWithMultipleInheritance(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR* NewDescriptor,
    _In_opt_ GUID** ObjectType,
    _In_ ULONG GuidCount,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ ULONG AutoInheritFlags, // SEF_*
    _In_opt_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteSecurityObject(
    _Inout_ PSECURITY_DESCRIPTOR* ObjectDescriptor
);

NTSYSAPI
NTSTATUS
NTAPI
RtlQuerySecurityObject(
    _In_ PSECURITY_DESCRIPTOR ObjectDescriptor,
    _In_ SECURITY_INFORMATION SecurityInformation,
    _Out_opt_ PSECURITY_DESCRIPTOR ResultantDescriptor,
    _In_ ULONG DescriptorLength,
    _Out_ PULONG ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetSecurityObject(
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR* ObjectsSecurityDescriptor,
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_opt_ HANDLE Token
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetSecurityObjectEx(
    _In_ SECURITY_INFORMATION SecurityInformation,
    _In_ PSECURITY_DESCRIPTOR ModificationDescriptor,
    _Inout_ PSECURITY_DESCRIPTOR* ObjectsSecurityDescriptor,
    _In_ ULONG AutoInheritFlags, // SEF_*
    _In_ PGENERIC_MAPPING GenericMapping,
    _In_opt_ HANDLE Token
);

NTSYSAPI
NTSTATUS
NTAPI
RtlConvertToAutoInheritSecurityObject(
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_ PSECURITY_DESCRIPTOR CurrentSecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR* NewSecurityDescriptor,
    _In_opt_ GUID* ObjectType,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI
NTSTATUS
NTAPI
RtlNewInstanceSecurityObject(
    _In_ BOOLEAN ParentDescriptorChanged,
    _In_ BOOLEAN CreatorDescriptorChanged,
    _In_ PLUID OldClientTokenModifiedId,
    _Out_ PLUID NewClientTokenModifiedId,
    _In_opt_ PSECURITY_DESCRIPTOR ParentDescriptor,
    _In_opt_ PSECURITY_DESCRIPTOR CreatorDescriptor,
    _Out_ PSECURITY_DESCRIPTOR* NewDescriptor,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ HANDLE Token,
    _In_ PGENERIC_MAPPING GenericMapping
);

NTSYSAPI
NTSTATUS
NTAPI
RtlCopySecurityDescriptor(
    _In_ PSECURITY_DESCRIPTOR InputSecurityDescriptor,
    _Out_ PSECURITY_DESCRIPTOR* OutputSecurityDescriptor
);

// private
typedef struct _RTL_ACE_DATA
{
    UCHAR AceType;
    UCHAR InheritFlags;
    UCHAR AceFlags;
    ACCESS_MASK AccessMask;
    PSID* Sid;
} RTL_ACE_DATA, * PRTL_ACE_DATA;

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateUserSecurityObject(
    _In_ PRTL_ACE_DATA AceData,
    _In_ ULONG AceCount,
    _In_ PSID OwnerSid,
    _In_ PSID GroupSid,
    _In_ BOOLEAN IsDirectoryObject,
    _In_ PGENERIC_MAPPING GenericMapping,
    _Out_ PSECURITY_DESCRIPTOR* NewSecurityDescriptor
);

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateAndSetSD(
    _In_ PRTL_ACE_DATA AceData,
    _In_ ULONG AceCount,
    _In_opt_ PSID OwnerSid,
    _In_opt_ PSID GroupSid,
    _Out_ PSECURITY_DESCRIPTOR* NewSecurityDescriptor
);

#endif // !_KERNEL_MODE

//
// Misc. security
//

#ifndef _KERNEL_MODE

NTSYSAPI
VOID
NTAPI
RtlRunEncodeUnicodeString(
    _Inout_ PUCHAR Seed,
    _Inout_ PUNICODE_STRING String
);

NTSYSAPI
VOID
NTAPI
RtlRunDecodeUnicodeString(
    _In_ UCHAR Seed,
    _Inout_ PUNICODE_STRING String
);

NTSYSAPI
NTSTATUS
NTAPI
RtlImpersonateSelf(
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlImpersonateSelfEx(
    _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
    _In_opt_ ACCESS_MASK AdditionalAccess,
    _Out_opt_ PHANDLE ThreadToken
);
#endif

NTSYSAPI
NTSTATUS
NTAPI
RtlAdjustPrivilege(
    _In_ ULONG Privilege,
    _In_ BOOLEAN Enable,
    _In_ BOOLEAN Client,
    _Out_ PBOOLEAN WasEnabled
);

#define RTL_ACQUIRE_PRIVILEGE_REVERT 0x00000001
#define RTL_ACQUIRE_PRIVILEGE_PROCESS 0x00000002

NTSYSAPI
NTSTATUS
NTAPI
RtlAcquirePrivilege(
    _In_ PULONG Privilege,
    _In_ ULONG NumPriv,
    _In_ ULONG Flags,
    _Out_ PVOID* ReturnedState
);

NTSYSAPI
VOID
NTAPI
RtlReleasePrivilege(
    _In_ PVOID StatePointer
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlRemovePrivileges(
    _In_ HANDLE TokenHandle,
    _In_ PULONG PrivilegesToKeep,
    _In_ ULONG PrivilegeCount
);
#endif

#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN8)

NTSYSAPI
NTSTATUS
NTAPI
RtlIsUntrustedObject(
    _In_opt_ HANDLE Handle,
    _In_opt_ PVOID Object,
    _Out_ PBOOLEAN UntrustedObject
);

NTSYSAPI
ULONG
NTAPI
RtlQueryValidationRunlevel(
    _In_opt_ PCUNICODE_STRING ComponentName
);
#endif

//
// Private namespaces
//

#ifndef _KERNEL_MODE

// begin_private
#if (NTDDI_VERSION >= NTDDI_VISTA)

// rev
#define BOUNDARY_DESCRIPTOR_ADD_APPCONTAINER_SID 0x0001

NTSYSAPI
POBJECT_BOUNDARY_DESCRIPTOR
NTAPI
RtlCreateBoundaryDescriptor(
    _In_ PUNICODE_STRING Name,
    _In_ ULONG Flags
);

NTSYSAPI
VOID
NTAPI
RtlDeleteBoundaryDescriptor(
    _In_ _Post_invalid_ POBJECT_BOUNDARY_DESCRIPTOR BoundaryDescriptor
);

NTSYSAPI
NTSTATUS
NTAPI
RtlAddSIDToBoundaryDescriptor(
    _Inout_ POBJECT_BOUNDARY_DESCRIPTOR* BoundaryDescriptor,
    _In_ PSID RequiredSid
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlAddIntegrityLabelToBoundaryDescriptor(
    _Inout_ POBJECT_BOUNDARY_DESCRIPTOR* BoundaryDescriptor,
    _In_ PSID IntegrityLabel
);
#endif
// end_private

#endif // !_KERNEL_MODE

//
// Version
//

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlGetVersion(
    _Out_
    _At_(lpVersionInformation->dwOSVersionInfoSize, _Pre_ _Valid_)
    _When_(lpVersionInformation->dwOSVersionInfoSize == sizeof(RTL_OSVERSIONINFOEXW),
        _At_((PRTL_OSVERSIONINFOEXW)lpVersionInformation, _Out_))
    PRTL_OSVERSIONINFOW lpVersionInformation
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlVerifyVersionInfo(
    _In_ PRTL_OSVERSIONINFOEXW VersionInfo,
    _In_ ULONG TypeMask,
    _In_ ULONGLONG  ConditionMask
);

#ifndef _KERNEL_MODE
// rev
NTSYSAPI
VOID
NTAPI
RtlGetNtVersionNumbers(
    _Out_opt_ PULONG NtMajorVersion,
    _Out_opt_ PULONG NtMinorVersion,
    _Out_opt_ PULONG NtBuildNumber
);
#endif // !_KERNEL_MODE

//
// System information
//

// rev
NTSYSAPI
ULONG
NTAPI
RtlGetNtGlobalFlags(
    VOID
);

NTSYSAPI
BOOLEAN
NTAPI
RtlGetNtProductType(
    _Out_ PNT_PRODUCT_TYPE NtProductType
);

#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
NTSYSAPI
ULONG
NTAPI
RtlGetSuiteMask(
    VOID
);
#endif

//
// Thread pool (old)
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterWait(
    _Out_ PHANDLE WaitHandle,
    _In_ HANDLE Handle,
    _In_ WAITORTIMERCALLBACKFUNC Function,
    _In_ PVOID Context,
    _In_ ULONG Milliseconds,
    _In_ ULONG Flags
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeregisterWait(
    _In_ HANDLE WaitHandle
);

#define RTL_WAITER_DEREGISTER_WAIT_FOR_COMPLETION ((HANDLE)(LONG_PTR)-1)

NTSYSAPI
NTSTATUS
NTAPI
RtlDeregisterWaitEx(
    _In_ HANDLE WaitHandle,
    _In_opt_ HANDLE Event // optional: RTL_WAITER_DEREGISTER_WAIT_FOR_COMPLETION
);

NTSYSAPI
NTSTATUS
NTAPI
RtlQueueWorkItem(
    _In_ WORKERCALLBACKFUNC Function,
    _In_ PVOID Context,
    _In_ ULONG Flags
);

NTSYSAPI
NTSTATUS
NTAPI
RtlSetIoCompletionCallback(
    _In_ HANDLE FileHandle,
    _In_ APC_CALLBACK_FUNCTION CompletionProc,
    _In_ ULONG Flags
);

typedef NTSTATUS(NTAPI* PRTL_START_POOL_THREAD)(
    _In_ PTHREAD_START_ROUTINE Function,
    _In_ PVOID Parameter,
    _Out_ PHANDLE ThreadHandle
    );

typedef NTSTATUS(NTAPI* PRTL_EXIT_POOL_THREAD)(
    _In_ NTSTATUS ExitStatus
    );

NTSYSAPI
NTSTATUS
NTAPI
RtlSetThreadPoolStartFunc(
    _In_ PRTL_START_POOL_THREAD StartPoolThread,
    _In_ PRTL_EXIT_POOL_THREAD ExitPoolThread
);

NTSYSAPI
VOID
NTAPI
RtlUserThreadStart(
    _In_ PTHREAD_START_ROUTINE Function,
    _In_ PVOID Parameter
);

// Thread execution

NTSYSCALLAPI
NTSTATUS
NTAPI
RtlDelayExecution(
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER DelayInterval
);

#endif // !_KERNEL_MODE

//
// Timer support
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateTimerQueue(
    _Out_ PHANDLE TimerQueueHandle
);

NTSYSAPI
NTSTATUS
NTAPI
RtlCreateTimer(
    _In_ HANDLE TimerQueueHandle,
    _Out_ PHANDLE Handle,
    _In_ WAITORTIMERCALLBACKFUNC Function,
    _In_opt_ PVOID Context,
    _In_ ULONG DueTime,
    _In_ ULONG Period,
    _In_ ULONG Flags
);

NTSYSAPI
NTSTATUS
NTAPI
RtlUpdateTimer(
    _In_ HANDLE TimerQueueHandle,
    _In_ HANDLE TimerHandle,
    _In_ ULONG DueTime,
    _In_ ULONG Period
);

#define RTL_TIMER_DELETE_WAIT_FOR_COMPLETION ((HANDLE)(LONG_PTR)-1)

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteTimer(
    _In_ HANDLE TimerQueueHandle,
    _In_ HANDLE TimerToCancel,
    _In_opt_ HANDLE Event // optional: RTL_TIMER_DELETE_WAIT_FOR_COMPLETION
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteTimerQueue(
    _In_ HANDLE TimerQueueHandle
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteTimerQueueEx(
    _In_ HANDLE TimerQueueHandle,
    _In_opt_ HANDLE Event
);

#endif // !_KERNEL_MODE

//
// Registry access
//

NTSYSAPI
NTSTATUS
NTAPI
RtlFormatCurrentUserKeyPath(
    _Out_ PUNICODE_STRING CurrentUserKeyPath
);

NTSYSAPI
NTSTATUS
NTAPI
RtlOpenCurrentUser(
    _In_ ACCESS_MASK DesiredAccess,
    _Out_ PHANDLE CurrentUserKey
);

#ifndef _KERNEL_MODE

//
// The following values for the RelativeTo parameter determine what the
// Path parameter to RtlQueryRegistryValues is relative to.
//

#define RTL_REGISTRY_ABSOLUTE     0   // Path is a full path
#define RTL_REGISTRY_SERVICES     1   // \Registry\Machine\System\CurrentControlSet\Services
#define RTL_REGISTRY_CONTROL      2   // \Registry\Machine\System\CurrentControlSet\Control
#define RTL_REGISTRY_WINDOWS_NT   3   // \Registry\Machine\Software\Microsoft\Windows NT\CurrentVersion
#define RTL_REGISTRY_DEVICEMAP    4   // \Registry\Machine\Hardware\DeviceMap
#define RTL_REGISTRY_USER         5   // \Registry\User\CurrentUser
#define RTL_REGISTRY_MAXIMUM      6
#define RTL_REGISTRY_HANDLE       0x40000000    // Low order bits are registry handle
#define RTL_REGISTRY_OPTIONAL     0x80000000    // Indicates the key node is optional

#endif // !_KERNEL_MODE

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateRegistryKey(
    _In_ ULONG RelativeTo,
    _In_ PWSTR Path
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckRegistryKey(
    _In_ ULONG RelativeTo,
    _In_ PWSTR Path
);

#ifndef _KERNEL_MODE

typedef
_Function_class_(RTL_QUERY_REGISTRY_ROUTINE)
_IRQL_requires_max_(PASSIVE_LEVEL)
_IRQL_requires_same_
NTSTATUS
NTAPI
RTL_QUERY_REGISTRY_ROUTINE(
    _In_z_ PWSTR ValueName,
    _In_ ULONG ValueType,
    _In_reads_bytes_opt_(ValueLength) PVOID ValueData,
    _In_ ULONG ValueLength,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID EntryContext
);
typedef RTL_QUERY_REGISTRY_ROUTINE* PRTL_QUERY_REGISTRY_ROUTINE;

typedef struct _RTL_QUERY_REGISTRY_TABLE
{
    PRTL_QUERY_REGISTRY_ROUTINE QueryRoutine;
    ULONG Flags;
    PWSTR Name;
    PVOID EntryContext;
    ULONG DefaultType;
    PVOID DefaultData;
    ULONG DefaultLength;
} RTL_QUERY_REGISTRY_TABLE, * PRTL_QUERY_REGISTRY_TABLE;

//
// The following flags specify how the Name field of a RTL_QUERY_REGISTRY_TABLE
// entry is interpreted.  A NULL name indicates the end of the table.
//

#define RTL_QUERY_REGISTRY_SUBKEY   0x00000001  // Name is a subkey and remainder of
                                                // table or until next subkey are value
                                                // names for that subkey to look at.

#define RTL_QUERY_REGISTRY_TOPKEY   0x00000002  // Reset current key to original key for
                                                // this and all following table entries.

#define RTL_QUERY_REGISTRY_REQUIRED 0x00000004  // Fail if no match found for this table
                                                // entry.

#define RTL_QUERY_REGISTRY_NOVALUE  0x00000008  // Used to mark a table entry that has no
                                                // value name, just wants a call out, not
                                                // an enumeration of all values.

#define RTL_QUERY_REGISTRY_NOEXPAND 0x00000010  // Used to suppress the expansion of
                                                // REG_MULTI_SZ into multiple callouts or
                                                // to prevent the expansion of environment
                                                // variable values in REG_EXPAND_SZ

#define RTL_QUERY_REGISTRY_DIRECT   0x00000020  // QueryRoutine field ignored.  EntryContext
                                                // field points to location to store value.
                                                // For null terminated strings, EntryContext
                                                // points to UNICODE_STRING structure that
                                                // that describes maximum size of buffer.
                                                // If .Buffer field is NULL then a buffer is
                                                // allocated.
                                                //

#define RTL_QUERY_REGISTRY_DELETE   0x00000040  // Used to delete value keys after they
                                                // are queried.

#define RTL_QUERY_REGISTRY_NOSTRING 0x00000080  // THIS IS DEPRECATED - use RTL_QUERY_REGISTRY_TYPECHECK
                                                //
                                                // Used with RTL_QUERY_REGISTRY_DIRECT in
                                                // cases where the caller expects a
                                                // non-string value.  Otherwise, the
                                                // assumption that EntryContext points to
                                                // a UNICODE_STRING structure can overrun
                                                // the caller's buffer.
                                                //

#define RTL_QUERY_REGISTRY_TYPECHECK 0x00000100 // Used with RTL_QUERY_REGISTRY_DIRECT to
                                                // validate the registry value type
                                                // expected by caller with actual type thats
                                                // read from the registry.


//
// Use the most significant byte of DefaultType from QueryTable, as the
// caller's expected REG_TYPE
//
#define RTL_QUERY_REGISTRY_TYPECHECK_SHIFT      24
#define RTL_QUERY_REGISTRY_TYPECHECK_MASK       (0xff << RTL_QUERY_REGISTRY_TYPECHECK_SHIFT)

#endif // !_KERNEL_MODE

#ifndef RtlQueryRegistryValues
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryRegistryValues(
    _In_     ULONG RelativeTo,
    _In_     PCWSTR Path,
    _Inout_ _At_(*(*QueryTable).EntryContext, _Pre_unknown_)
    PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_opt_ PVOID Context,
    _In_opt_ PVOID Environment
);
#endif

// rev
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryRegistryValuesEx(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_ PRTL_QUERY_REGISTRY_TABLE QueryTable,
    _In_ PVOID Context,
    _In_opt_ PVOID Environment
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlWriteRegistryValue(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_z_ PCWSTR ValueName,
    _In_ ULONG ValueType,
    _In_reads_bytes_opt_(ValueLength) PVOID ValueData,
    _In_ ULONG ValueLength
);

_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlDeleteRegistryValue(
    _In_ ULONG RelativeTo,
    _In_ PCWSTR Path,
    _In_z_ PCWSTR ValueName
);

//
// Thread profiling
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlEnableThreadProfiling(
    _In_ HANDLE ThreadHandle,
    _In_ ULONG Flags,
    _In_ ULONG64 HardwareCounters,
    _Out_ PVOID* PerformanceDataHandle
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDisableThreadProfiling(
    _In_ PVOID PerformanceDataHandle
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryThreadProfiling(
    _In_ HANDLE ThreadHandle,
    _Out_ PBOOLEAN Enabled
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlReadThreadProfilingData(
    _In_ HANDLE PerformanceDataHandle,
    _In_ ULONG Flags,
    _Out_ PPERFORMANCE_DATA PerformanceData
);
#endif

#endif // !_KERNEL_MODE

//
// WOW64
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlGetNativeSystemInformation(
    _In_ ULONG SystemInformationClass,
    _In_ PVOID NativeSystemInformation,
    _In_ ULONG InformationLength,
    _Out_opt_ PULONG ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI
RtlQueueApcWow64Thread(
    _In_ HANDLE ThreadHandle,
    _In_ PPS_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcArgument1,
    _In_opt_ PVOID ApcArgument2,
    _In_opt_ PVOID ApcArgument3
);

NTSYSAPI
NTSTATUS
NTAPI
RtlWow64EnableFsRedirection(
    _In_ BOOLEAN Wow64FsEnableRedirection
);

NTSYSAPI
NTSTATUS
NTAPI
RtlWow64EnableFsRedirectionEx(
    _In_ PVOID Wow64FsEnableRedirection,
    _Out_ PVOID* OldFsRedirectionLevel
);

#endif // !_KERNEL_MODE

//
// Misc
//

NTSYSAPI
ULONG32
NTAPI
RtlComputeCrc32(
    _In_ ULONG32 PartialCrc,
    _In_ PVOID Buffer,
    _In_ ULONG Length
);

#ifndef _KERNEL_MODE

NTSYSAPI
PVOID
NTAPI
RtlEncodePointer(
    _In_ PVOID Ptr
);

NTSYSAPI
PVOID
NTAPI
RtlDecodePointer(
    _In_ PVOID Ptr
);

NTSYSAPI
PVOID
NTAPI
RtlEncodeSystemPointer(
    _In_ PVOID Ptr
);

NTSYSAPI
PVOID
NTAPI
RtlDecodeSystemPointer(
    _In_ PVOID Ptr
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlEncodeRemotePointer(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID Pointer,
    _Out_ PVOID* EncodedPointer
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlDecodeRemotePointer(
    _In_ HANDLE ProcessHandle,
    _In_ PVOID Pointer,
    _Out_ PVOID* DecodedPointer
);
#endif

#endif // !_KERNEL_MODE

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsProcessorFeaturePresent(
    _In_ ULONG ProcessorFeature
);

#ifndef _KERNEL_MODE

// rev
NTSYSAPI
ULONG
NTAPI
RtlGetCurrentProcessorNumber(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
VOID
NTAPI
RtlGetCurrentProcessorNumberEx(
    _Out_ PPROCESSOR_NUMBER ProcessorNumber
);
#endif

#endif // !_KERNEL_MODE

//
// Stack support
//

#ifndef _KERNEL_MODE

NTSYSAPI
VOID
NTAPI
RtlPushFrame(
    _In_ struct _TEB_ACTIVE_FRAME* Frame
);

NTSYSAPI
VOID
NTAPI
RtlPopFrame(
    _In_ struct _TEB_ACTIVE_FRAME* Frame
);

NTSYSAPI
struct _TEB_ACTIVE_FRAME*
NTAPI
RtlGetFrame(
    VOID
);

#endif // !_KERNEL_MODE

#define RTL_WALK_USER_MODE_STACK    0x00000001
#define RTL_WALK_VALID_FLAGS        0x00000001

#ifndef _KERNEL_MODE
#define RTL_STACK_WALKING_MODE_FRAMES_TO_SKIP_SHIFT 0x00000008
#endif  // !_KERNEL_MODE

// private
NTSYSAPI
ULONG
NTAPI
RtlWalkFrameChain(
    _Out_writes_(Count - (Flags >> RTL_STACK_WALKING_MODE_FRAMES_TO_SKIP_SHIFT)) PVOID* Callers,
    _In_ ULONG Count,
    _In_ ULONG Flags
);

#ifndef _KERNEL_MODE
#if (defined(_M_AMD64) || defined(_M_IA64)) && !defined(_REALLY_GET_CALLERS_CALLER_)

#define RtlGetCallersAddress(CallersAddress, CallersCaller) \
    *CallersAddress = (PVOID)_ReturnAddress(); \
    *CallersCaller = NULL;

#else

NTSYSAPI
VOID
NTAPI
RtlGetCallersAddress(
    _Out_ PVOID* CallersAddress,
    _Out_ PVOID* CallersCaller
);

#endif
#endif  // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN7)
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
ULONG64
NTAPI
RtlGetEnabledExtendedFeatures(
    _In_ ULONG64 FeatureMask
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
// msdn
_IRQL_requires_max_(PASSIVE_LEVEL)
NTSYSAPI
ULONG64
NTAPI
RtlGetEnabledExtendedAndSupervisorFeatures(
    _In_ ULONG64 FeatureMask
);

// msdn
_Ret_maybenull_
_Success_(return != NULL)
NTSYSAPI
PVOID
NTAPI
RtlLocateSupervisorFeature(
    _In_ PXSAVE_AREA_HEADER XStateHeader,
    _In_range_(XSTATE_AVX, MAXIMUM_XSTATE_FEATURES - 1) ULONG FeatureId,
    _Out_opt_ PULONG Length
);
#endif

// private
typedef union _RTL_ELEVATION_FLAGS
{
    ULONG Flags;
    struct
    {
        ULONG ElevationEnabled : 1;
        ULONG VirtualizationEnabled : 1;
        ULONG InstallerDetectEnabled : 1;
        ULONG ReservedBits : 29;
    };
} RTL_ELEVATION_FLAGS, * PRTL_ELEVATION_FLAGS;

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryElevationFlags(
    _Out_ PRTL_ELEVATION_FLAGS Flags
);
#endif

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_VISTA)
// private
NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterThreadWithCsrss(
    VOID
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLockCurrentThread(
    VOID
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockCurrentThread(
    VOID
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlLockModuleSection(
    _In_ PVOID Address
);

// private
NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockModuleSection(
    _In_ PVOID Address
);
#endif

#endif // !_KERNEL_MODE


//
// Event Trace
//

#ifndef _KERNEL_MODE

// begin_msdn:"Winternl"
#define RTL_UNLOAD_EVENT_TRACE_NUMBER 64

// private
typedef struct _RTL_UNLOAD_EVENT_TRACE
{
    PVOID BaseAddress;
    SIZE_T SizeOfImage;
    ULONG Sequence;
    ULONG TimeDateStamp;
    ULONG CheckSum;
    WCHAR ImageName[32];
    ULONG Version[2];
} RTL_UNLOAD_EVENT_TRACE, * PRTL_UNLOAD_EVENT_TRACE;

typedef struct _RTL_UNLOAD_EVENT_TRACE32
{
    ULONG BaseAddress;
    ULONG SizeOfImage;
    ULONG Sequence;
    ULONG TimeDateStamp;
    ULONG CheckSum;
    WCHAR ImageName[32];
    ULONG Version[2];
} RTL_UNLOAD_EVENT_TRACE32, * PRTL_UNLOAD_EVENT_TRACE32;

NTSYSAPI
PRTL_UNLOAD_EVENT_TRACE
NTAPI
RtlGetUnloadEventTrace(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
VOID
NTAPI
RtlGetUnloadEventTraceEx(
    _Out_ PULONG * ElementSize,
    _Out_ PULONG * ElementCount,
    _Out_ PVOID * EventTrace // works across all processes
);
#endif
// end_msdn

#endif // !_KERNEL_MODE

//
// Performance Counter
//

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN7)
// rev
NTSYSAPI
LOGICAL
NTAPI
RtlQueryPerformanceCounter(
    _Out_ PLARGE_INTEGER PerformanceCounter
);

// rev
NTSYSAPI
LOGICAL
NTAPI
RtlQueryPerformanceFrequency(
    _Out_ PLARGE_INTEGER PerformanceFrequency
);
#endif

#endif // !_KERNEL_MODE

//
// Image Mitigation
//

#ifndef _KERNEL_MODE

// rev
typedef enum _IMAGE_MITIGATION_POLICY
{
    ImageDepPolicy,                     // RTL_IMAGE_MITIGATION_DEP_POLICY
    ImageAslrPolicy,                    // RTL_IMAGE_MITIGATION_ASLR_POLICY
    ImageDynamicCodePolicy,             // RTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY
    ImageStrictHandleCheckPolicy,       // RTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY
    ImageSystemCallDisablePolicy,       // RTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY
    ImageMitigationOptionsMask,
    ImageExtensionPointDisablePolicy,   // RTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY
    ImageControlFlowGuardPolicy,        // RTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY
    ImageSignaturePolicy,               // RTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY
    ImageFontDisablePolicy,             // RTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY
    ImageImageLoadPolicy,               // RTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY
    ImagePayloadRestrictionPolicy,      // RTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY
    ImageChildProcessPolicy,            // RTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY
    ImageSehopPolicy,                   // RTL_IMAGE_MITIGATION_SEHOP_POLICY
    ImageHeapPolicy,                    // RTL_IMAGE_MITIGATION_HEAP_POLICY
    ImageUserShadowStackPolicy,         // RTL_IMAGE_MITIGATION_USER_SHADOW_STACK_POLICY
    MaxImageMitigationPolicy
} IMAGE_MITIGATION_POLICY;

// rev
typedef union _RTL_IMAGE_MITIGATION_POLICY
{
    struct
    {
        ULONG64 AuditState : 2;
        ULONG64 AuditFlag : 1;
        ULONG64 EnableAdditionalAuditingOption : 1;
        ULONG64 Reserved : 60;
    };
    struct
    {
        ULONG64 PolicyState : 2;
        ULONG64 AlwaysInherit : 1;
        ULONG64 EnableAdditionalPolicyOption : 1;
        ULONG64 AuditReserved : 60;
    };
} RTL_IMAGE_MITIGATION_POLICY, * PRTL_IMAGE_MITIGATION_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_DEP_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY Dep;
} RTL_IMAGE_MITIGATION_DEP_POLICY, * PRTL_IMAGE_MITIGATION_DEP_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_ASLR_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY ForceRelocateImages;
    RTL_IMAGE_MITIGATION_POLICY BottomUpRandomization;
    RTL_IMAGE_MITIGATION_POLICY HighEntropyRandomization;
} RTL_IMAGE_MITIGATION_ASLR_POLICY, * PRTL_IMAGE_MITIGATION_ASLR_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockDynamicCode;
} RTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY, * PRTL_IMAGE_MITIGATION_DYNAMIC_CODE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY StrictHandleChecks;
} RTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY, * PRTL_IMAGE_MITIGATION_STRICT_HANDLE_CHECK_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockWin32kSystemCalls;
} RTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY, * PRTL_IMAGE_MITIGATION_SYSTEM_CALL_DISABLE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY DisableExtensionPoints;
} RTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY, * PRTL_IMAGE_MITIGATION_EXTENSION_POINT_DISABLE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY ControlFlowGuard;
    RTL_IMAGE_MITIGATION_POLICY StrictControlFlowGuard;
} RTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY, * PRTL_IMAGE_MITIGATION_CONTROL_FLOW_GUARD_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockNonMicrosoftSignedBinaries;
    RTL_IMAGE_MITIGATION_POLICY EnforceSigningOnModuleDependencies;
} RTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY, * PRTL_IMAGE_MITIGATION_BINARY_SIGNATURE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY DisableNonSystemFonts;
} RTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY, * PRTL_IMAGE_MITIGATION_FONT_DISABLE_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY BlockRemoteImageLoads;
    RTL_IMAGE_MITIGATION_POLICY BlockLowLabelImageLoads;
    RTL_IMAGE_MITIGATION_POLICY PreferSystem32;
} RTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY, * PRTL_IMAGE_MITIGATION_IMAGE_LOAD_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY EnableExportAddressFilter;
    RTL_IMAGE_MITIGATION_POLICY EnableExportAddressFilterPlus;
    RTL_IMAGE_MITIGATION_POLICY EnableImportAddressFilter;
    RTL_IMAGE_MITIGATION_POLICY EnableRopStackPivot;
    RTL_IMAGE_MITIGATION_POLICY EnableRopCallerCheck;
    RTL_IMAGE_MITIGATION_POLICY EnableRopSimExec;
    WCHAR EafPlusModuleList[512]; // 19H1
} RTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY, * PRTL_IMAGE_MITIGATION_PAYLOAD_RESTRICTION_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY DisallowChildProcessCreation;
} RTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY, * PRTL_IMAGE_MITIGATION_CHILD_PROCESS_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_SEHOP_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY Sehop;
} RTL_IMAGE_MITIGATION_SEHOP_POLICY, * PRTL_IMAGE_MITIGATION_SEHOP_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_HEAP_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY TerminateOnHeapErrors;
} RTL_IMAGE_MITIGATION_HEAP_POLICY, * PRTL_IMAGE_MITIGATION_HEAP_POLICY;

// rev
typedef struct _RTL_IMAGE_MITIGATION_USER_SHADOW_STACK_POLICY
{
    RTL_IMAGE_MITIGATION_POLICY UserShadowStack;
    RTL_IMAGE_MITIGATION_POLICY SetContextIpValidation;
    RTL_IMAGE_MITIGATION_POLICY BlockNonCetBinaries;
} RTL_IMAGE_MITIGATION_USER_SHADOW_STACK_POLICY, * PRTL_IMAGE_MITIGATION_USER_SHADOW_STACK_POLICY;

typedef enum _RTL_IMAGE_MITIGATION_OPTION_STATE
{
    RtlMitigationOptionStateNotConfigured,
    RtlMitigationOptionStateOn,
    RtlMitigationOptionStateOff,
    RtlMitigationOptionStateForce,
    RtlMitigationOptionStateOption
} RTL_IMAGE_MITIGATION_OPTION_STATE;

#define RTL_IMAGE_MITIGATION_OPTION_STATEMASK  3UL
#define RTL_IMAGE_MITIGATION_OPTION_FORCEMASK  4UL
#define RTL_IMAGE_MITIGATION_OPTION_OPTIONMASK 8UL

// rev from PROCESS_MITIGATION_FLAGS
#define RTL_IMAGE_MITIGATION_FLAG_RESET     0x1
#define RTL_IMAGE_MITIGATION_FLAG_REMOVE    0x2
#define RTL_IMAGE_MITIGATION_FLAG_OSDEFAULT 0x4
#define RTL_IMAGE_MITIGATION_FLAG_AUDIT     0x8

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryImageMitigationPolicy(
    _In_opt_ PWSTR ImagePath, // NULL for system-wide defaults
    _In_ IMAGE_MITIGATION_POLICY Policy,
    _In_ ULONG Flags,
    _Inout_ PVOID Buffer,
    _In_ ULONG BufferSize
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetImageMitigationPolicy(
    _In_opt_ PWSTR ImagePath, // NULL for system-wide defaults
    _In_ IMAGE_MITIGATION_POLICY Policy,
    _In_ ULONG Flags,
    _Inout_ PVOID Buffer,
    _In_ ULONG BufferSize
);
#endif

#endif // !_KERNEL_MODE

//
// session 
//

// rev
NTSYSAPI
ULONG
NTAPI
RtlGetCurrentServiceSessionId(
    VOID
);

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI
ULONG
NTAPI
RtlGetActiveConsoleId(
    VOID
);

NTSYSAPI
ULONGLONG
NTAPI
RtlGetConsoleSessionForegroundProcessId(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsMultiSessionSku(
    VOID
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsMultiUsersInSessionSku(
    VOID
);
#else // NTDDI_VERSION >= NTDDI_WIN10_RS1
FORCEINLINE
ULONG
NTAPI
RtlGetActiveConsoleId(
    VOID
)
{
    return SharedUserData->ActiveConsoleId;
}

FORCEINLINE
ULONGLONG
NTAPI
RtlGetConsoleSessionForegroundProcessId(
    VOID
)
{
    return SharedUserData->ConsoleSessionForegroundProcessId;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
FORCEINLINE
BOOLEAN
NTAPI
RtlIsMultiSessionSku(
    VOID
)
{
    return SharedUserData->DbgMultiSessionSku;
}

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
FORCEINLINE
BOOLEAN
NTAPI
RtlIsMultiUsersInSessionSku(
    VOID
)
{
    return SharedUserData->DbgMultiUsersInSessionSku;
}
#endif // NTDDI_VERSION < NTDDI_WIN10_RS1

//
// Appcontainer
//

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetTokenNamedObjectPath(
    _In_ HANDLE Token,
    _In_opt_ PSID Sid,
    _Out_ PUNICODE_STRING ObjectPath // RtlFreeUnicodeString
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetAppContainerNamedObjectPath(
    _In_opt_ HANDLE Token,
    _In_opt_ PSID AppContainerSid,
    _In_ BOOLEAN RelativePath,
    _Out_ PUNICODE_STRING ObjectPath // RtlFreeUnicodeString
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetAppContainerParent(
    _In_ PSID AppContainerSid,
    _Out_ PSID* AppContainerSidParent // RtlFreeSid
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckSandboxedToken(
    _In_opt_ HANDLE TokenHandle,
    _Out_ PBOOLEAN IsSandboxed
);
#endif

#ifdef _KERNEL_MODE
NTSYSAPI
BOOLEAN
NTAPI
RtlIsSandboxedToken(
    _In_opt_ PSECURITY_SUBJECT_CONTEXT Context,
    _In_ KPROCESSOR_MODE PreviousMode
);
#endif // _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckTokenCapability(
    _In_opt_ HANDLE TokenHandle,
    _In_ PSID CapabilitySidToCheck,
    _Out_ PBOOLEAN HasCapability
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCapabilityCheck(
    _In_opt_ HANDLE TokenHandle,
    _In_ PUNICODE_STRING CapabilityName,
    _Out_ PBOOLEAN HasCapability
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckTokenMembership(
    _In_opt_ HANDLE TokenHandle,
    _In_ PSID SidToCheck,
    _Out_ PBOOLEAN IsMember
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckTokenMembershipEx(
    _In_opt_ HANDLE TokenHandle,
    _In_ PSID SidToCheck,
    _In_ ULONG Flags, // CTMF_VALID_FLAGS
    _Out_ PBOOLEAN IsMember
);
#endif

#ifndef _KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryTokenHostIdAsUlong64(
    _In_ HANDLE TokenHandle,
    _Out_ PULONG64 HostId // (WIN://PKGHOSTID)
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsParentOfChildAppContainer(
    _In_ PSID ParentAppContainerSid,
    _In_ PSID ChildAppContainerSid
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN11)
NTSYSAPI
NTSTATUS
NTAPI
RtlIsApiSetImplemented(
    _In_ PCSTR Namespace
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN8)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsCapabilitySid(
    _In_ PSID Sid
);

// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsPackageSid(
    _In_ PSID Sid
);
#endif

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
NTSYSAPI
BOOLEAN
NTAPI
RtlIsValidProcessTrustLabelSid(
    _In_ PSID Sid
);
#endif

#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)
_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
BOOLEAN
NTAPI
RtlIsStateSeparationEnabled(
    VOID
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS4

typedef enum _APPCONTAINER_SID_TYPE
{
    NotAppContainerSidType,
    ChildAppContainerSidType,
    ParentAppContainerSidType,
    InvalidAppContainerSidType,
    MaxAppContainerSidType
} APPCONTAINER_SID_TYPE, * PAPPCONTAINER_SID_TYPE;

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetAppContainerSidType(
    _In_ PSID AppContainerSid,
    _Out_ PAPPCONTAINER_SID_TYPE AppContainerSidType
);
#endif

//
// Fls
//

#ifndef _KERNEL_MODE

NTSYSAPI
NTSTATUS
NTAPI
RtlFlsAlloc(
    _In_ PFLS_CALLBACK_FUNCTION Callback,
    _Out_ PULONG FlsIndex
);

NTSYSAPI
NTSTATUS
NTAPI
RtlFlsFree(
    _In_ ULONG FlsIndex
);

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)
NTSYSAPI
NTSTATUS
WINAPI
RtlFlsGetValue(
    _In_ ULONG FlsIndex,
    _Out_ PVOID* FlsData
);

NTSYSAPI
NTSTATUS
WINAPI
RtlFlsSetValue(
    _In_ ULONG FlsIndex,
    _In_ PVOID FlsData
);
#endif

#endif // !_KERNEL_MODE

//
// File System
// 

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
#ifndef _KERNEL_MODE

typedef enum _STATE_LOCATION_TYPE
{
    LocationTypeRegistry = 0,
    LocationTypeFileSystem = 1,
    LocationTypeMaximum = 2
} STATE_LOCATION_TYPE;

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlGetPersistedStateLocation(
    _In_                        PCWSTR    SourceID,
    _In_opt_                    PCWSTR    CustomValue,
    _In_opt_                    PCWSTR    DefaultPath,
    _In_                        STATE_LOCATION_TYPE StateLocationType,
    _Out_writes_bytes_to_opt_(BufferLengthIn, *BufferLengthOut)
    PWCHAR   TargetPath,
    _In_                        ULONG    BufferLengthIn,
    _Out_opt_                   PULONG   BufferLengthOut
);

#endif // !_KERNEL_MODE
#endif // (NTDDI_VERSION >= NTDDI_WIN10_RS3)

//
// Placeholder file routines.
//

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)

NTSYSAPI
BOOLEAN
NTAPI
RtlIsCloudFilesPlaceholder(
    _In_ ULONG FileAttributes,
    _In_ ULONG ReparseTag
);

NTSYSAPI
BOOLEAN
NTAPI
RtlIsPartialPlaceholder(
    _In_ ULONG FileAttributes,
    _In_ ULONG ReparseTag
);

NTSYSAPI
NTSTATUS
NTAPI
RtlIsPartialPlaceholderFileHandle(
    _In_ HANDLE FileHandle,
    _Out_ PBOOLEAN IsPartialPlaceholder
);

NTSYSAPI
NTSTATUS
NTAPI
RtlIsPartialPlaceholderFileInfo(
    _In_ CONST VOID* InfoBuffer,
    _In_ FILE_INFORMATION_CLASS InfoClass,
    _Out_ PBOOLEAN IsPartialPlaceholder
);

#endif // NTDDI_VERSION >= NTDDI_WIN10_RS2

#if (NTDDI_VERSION >= NTDDI_WIN10_RS2)
NTSYSAPI
BOOLEAN
NTAPI
RtlIsNonEmptyDirectoryReparsePointAllowed(
    _In_ ULONG ReparseTag
);
#endif // NTDDI_VERSION >= NTDDI_WIN10_RS2

#if (NTDDI_VERSION >= NTDDI_WIN8)
#ifndef _KERNEL_MODE
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlAppxIsFileOwnedByTrustedInstaller(
    _In_ HANDLE FileHandle,
    _Out_ PBOOLEAN IsFileOwnedByTrustedInstaller
);
#endif // !_KERNEL_MODE
#endif // (NTDDI_VERSION >= NTDDI_WIN8)

// Windows Internals book
#define PSM_ACTIVATION_TOKEN_PACKAGED_APPLICATION   0x1
#define PSM_ACTIVATION_TOKEN_SHARED_ENTITY          0x2
#define PSM_ACTIVATION_TOKEN_FULL_TRUST             0x4
#define PSM_ACTIVATION_TOKEN_NATIVE_SERVICE         0x8
#define PSM_ACTIVATION_TOKEN_DEVELOPMENT_APP        0x10
#define BREAKAWAY_INHIBITED                         0x20

// private
typedef struct _PS_PKG_CLAIM
{
    ULONG Flags;  // PSM_ACTIVATION_TOKEN_*
    ULONG Origin; // PackageOrigin from appmodel.h
} PS_PKG_CLAIM, * PPS_PKG_CLAIM;

#if (NTDDI_VERSION >= NTDDI_WIN10)
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryPackageClaims(
    _In_ HANDLE TokenHandle,
    _Out_writes_bytes_to_opt_(*PackageSize, *PackageSize) PWSTR PackageFullName,
    _Inout_opt_ PSIZE_T PackageSize,
    _Out_writes_bytes_to_opt_(*AppIdSize, *AppIdSize) PWSTR AppId,
    _Inout_opt_ PSIZE_T AppIdSize,
    _Out_opt_ PGUID DynamicId,
    _Out_opt_ PPS_PKG_CLAIM PkgClaim,
    _Out_opt_ PULONG64 AttributesPresent
);
#endif

//
// Process & Thread Placeholder
//

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)

#ifndef _KERNEL_MODE
#undef PHCM_MAX
#define PHCM_APPLICATION_DEFAULT      ((CHAR)0)
#define PHCM_DISGUISE_PLACEHOLDERS    ((CHAR)1)
#define PHCM_EXPOSE_PLACEHOLDERS      ((CHAR)2)
#define PHCM_MAX                      ((CHAR)2)

#define PHCM_ERROR_INVALID_PARAMETER  ((CHAR)-1)
#define PHCM_ERROR_NO_TEB             ((CHAR)-2)
#endif // !_KERNEL_MODE

NTSYSAPI
CHAR
NTAPI
RtlQueryThreadPlaceholderCompatibilityMode(
    VOID
);

NTSYSAPI
CHAR
NTAPI
RtlSetThreadPlaceholderCompatibilityMode(
    _In_ CHAR Mode
);

#endif // NTDDI_VERSION >= NTDDI_WIN10_RS3

#if (NTDDI_VERSION >= NTDDI_WIN10_RS4)

#ifndef _KERNEL_MODE
#undef PHCM_MAX
#define PHCM_DISGUISE_FULL_PLACEHOLDERS  ((CHAR)3)
#define PHCM_MAX                         ((CHAR)3)
#define PHCM_ERROR_NO_PEB                ((CHAR)-3)
#endif // !_KERNEL_MODE

NTSYSAPI
CHAR
NTAPI
RtlQueryProcessPlaceholderCompatibilityMode(
    VOID
);

NTSYSAPI
CHAR
NTAPI
RtlSetProcessPlaceholderCompatibilityMode(
    _In_ CHAR Mode
);

#endif // NTDDI_VERSION >= NTDDI_WIN10_RS4

//
// Protected policies
//

#if (NTDDI_VERSION >= NTDDI_WINBLUE)
#ifndef _KERNEL_MODE

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryProtectedPolicy(
    _In_ PGUID PolicyGuid,
    _Out_ PULONG_PTR PolicyValue
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetProtectedPolicy(
    _In_ PGUID PolicyGuid,
    _In_ ULONG_PTR PolicyValue,
    _Out_ PULONG_PTR OldPolicyValue
);

#endif // !_KERNEL_MODE
#endif

//
// Boot Status Data
//

// private
typedef enum _RTL_BSD_ITEM_TYPE
{
    RtlBsdItemVersionNumber, // q; s: ULONG
    RtlBsdItemProductType, // q; s: NT_PRODUCT_TYPE (ULONG)
    RtlBsdItemAabEnabled, // q: s: BOOLEAN // AutoAdvancedBoot
    RtlBsdItemAabTimeout, // q: s: UCHAR // AdvancedBootMenuTimeout
    RtlBsdItemBootGood, // q: s: BOOLEAN // LastBootSucceeded
    RtlBsdItemBootShutdown, // q: s: BOOLEAN // LastBootShutdown
    RtlBsdSleepInProgress, // q: s: BOOLEAN // SleepInProgress
    RtlBsdPowerTransition, // q: s: RTL_BSD_DATA_POWER_TRANSITION
    RtlBsdItemBootAttemptCount, // q: s: UCHAR // BootAttemptCount
    RtlBsdItemBootCheckpoint, // q: s: UCHAR // LastBootCheckpoint
    RtlBsdItemBootId, // q; s: ULONG (USER_SHARED_DATA->BootId)
    RtlBsdItemShutdownBootId, // q; s: ULONG
    RtlBsdItemReportedAbnormalShutdownBootId, // q; s: ULONG
    RtlBsdItemErrorInfo, // RTL_BSD_DATA_ERROR_INFO
    RtlBsdItemPowerButtonPressInfo, // RTL_BSD_POWER_BUTTON_PRESS_INFO
    RtlBsdItemChecksum, // q: s: UCHAR
    RtlBsdPowerTransitionExtension,
    RtlBsdItemFeatureConfigurationState, // q; s: ULONG
    RtlBsdItemMax
} RTL_BSD_ITEM_TYPE;


// ros
typedef struct _RTL_BSD_DATA_POWER_TRANSITION
{
    LARGE_INTEGER PowerButtonTimestamp;
    struct
    {
        BOOLEAN SystemRunning : 1;
        BOOLEAN ConnectedStandbyInProgress : 1;
        BOOLEAN UserShutdownInProgress : 1;
        BOOLEAN SystemShutdownInProgress : 1;
        BOOLEAN SleepInProgress : 4;
    } Flags;
    UCHAR ConnectedStandbyScenarioInstanceId;
    UCHAR ConnectedStandbyEntryReason;
    UCHAR ConnectedStandbyExitReason;
    USHORT SystemSleepTransitionCount;
    LARGE_INTEGER LastReferenceTime;
    ULONG LastReferenceTimeChecksum;
    ULONG LastUpdateBootId;
} RTL_BSD_DATA_POWER_TRANSITION, * PRTL_BSD_DATA_POWER_TRANSITION;

// ros
typedef struct _RTL_BSD_DATA_ERROR_INFO
{
    ULONG BootId;
    ULONG RepeatCount;
    ULONG OtherErrorCount;
    ULONG Code;
    ULONG OtherErrorCount2;
} RTL_BSD_DATA_ERROR_INFO, * PRTL_BSD_DATA_ERROR_INFO;

// ros
typedef struct _RTL_BSD_POWER_BUTTON_PRESS_INFO
{
    LARGE_INTEGER LastPressTime;
    ULONG CumulativePressCount;
    USHORT LastPressBootId;
    UCHAR LastPowerWatchdogStage;
    struct
    {
        UCHAR WatchdogArmed : 1;
        UCHAR ShutdownInProgress : 1;
    } Flags;
    LARGE_INTEGER LastReleaseTime;
    ULONG CumulativeReleaseCount;
    USHORT LastReleaseBootId;
    USHORT ErrorCount;
    UCHAR CurrentConnectedStandbyPhase;
    ULONG TransitionLatestCheckpointId;
    ULONG TransitionLatestCheckpointType;
    ULONG TransitionLatestCheckpointSequenceNumber;
} RTL_BSD_POWER_BUTTON_PRESS_INFO, * PRTL_BSD_POWER_BUTTON_PRESS_INFO;

// private
typedef struct _RTL_BSD_ITEM
{
    RTL_BSD_ITEM_TYPE Type;
    PVOID DataBuffer;
    ULONG DataLength;
} RTL_BSD_ITEM, * PRTL_BSD_ITEM;

#ifndef _KERNEL_MODE
// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlCreateBootStatusDataFile(
    VOID
);
#endif // !_KERNEL_MODE

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlLockBootStatusData(
    _Out_ PHANDLE FileHandle
);

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlUnlockBootStatusData(
    _In_ HANDLE FileHandle
);

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlGetSetBootStatusData(
    _In_ HANDLE FileHandle,
    _In_ BOOLEAN Read,
    _In_ RTL_BSD_ITEM_TYPE DataClass,
    _In_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG ReturnLength
);

#ifndef _KERNEL_MODE
#if (NTDDI_VERSION >= NTDDI_WIN10_RS1)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckBootStatusIntegrity(
    _In_ HANDLE FileHandle,
    _Out_ PBOOLEAN Verified
);
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlRestoreBootStatusDefaults(
    _In_ HANDLE FileHandle
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlRestoreSystemBootStatusDefaults(
    VOID
);
#endif
#endif // !_KERNEL_MODE

#if (NTDDI_VERSION >= NTDDI_WIN10_RS3)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlGetSystemBootStatus(
    _In_ RTL_BSD_ITEM_TYPE BootStatusInformationClass,
    _Out_ PVOID DataBuffer,
    _In_ ULONG DataLength,
    _Out_opt_ PULONG ReturnLength
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetSystemBootStatus(
    _In_ RTL_BSD_ITEM_TYPE BootStatusInformationClass,
    _In_ PVOID DataBuffer,
    _In_ ULONG DataLength,
    _Out_opt_ PULONG ReturnLength
);
#endif

#if (NTDDI_VERSION >= NTDDI_WIN18)
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlCheckPortableOperatingSystem(
    _Out_ PBOOLEAN IsPortable // VOID
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetPortableOperatingSystem(
    _In_ BOOLEAN IsPortable
);
#endif

#if (NTDDI_VERSION >= NTDDI_VISTA)
NTSYSAPI
NTSTATUS
NTAPI
RtlFindClosestEncodableLength(
    _In_ ULONGLONG SourceLength,
    _Out_ PULONGLONG TargetLength
);
#endif

//
// Memory cache
//

#ifndef _KERNEL_MODE

typedef NTSTATUS(NTAPI* PRTL_SECURE_MEMORY_CACHE_CALLBACK)(
    _In_ PVOID Address,
    _In_ SIZE_T Length
    );

// ros
NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterSecureMemoryCacheCallback(
    _In_ PRTL_SECURE_MEMORY_CACHE_CALLBACK Callback
);

NTSYSAPI
NTSTATUS
NTAPI
RtlDeregisterSecureMemoryCacheCallback(
    _In_ PRTL_SECURE_MEMORY_CACHE_CALLBACK Callback
);

// ros
NTSYSAPI
BOOLEAN
NTAPI
RtlFlushSecureMemoryCache(
    _In_ PVOID MemoryCache,
    _In_opt_ SIZE_T MemoryLength
);

#endif // !_KERNEL_MODE

//
// Feature configuration
//

#if (NTDDI_VERSION >= NTDDI_WIN10_VB)

typedef struct _RTL_FEATURE_USAGE_REPORT
{
    ULONG FeatureId;
    USHORT ReportingKind;
    USHORT ReportingOptions;
} RTL_FEATURE_USAGE_REPORT, * PRTL_FEATURE_USAGE_REPORT;

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlNotifyFeatureUsage(
    _In_ PRTL_FEATURE_USAGE_REPORT FeatureUsageReport
);

typedef enum _RTL_FEATURE_CONFIGURATION_TYPE
{
    RtlFeatureConfigurationBoot,
    RtlFeatureConfigurationRuntime,
    RtlFeatureConfigurationCount
} RTL_FEATURE_CONFIGURATION_TYPE;

// rev
typedef struct _RTL_FEATURE_CONFIGURATION
{
    ULONG FeatureId;
    union
    {
        ULONG Flags;
        struct
        {
            ULONG Priority : 4;
            ULONG EnabledState : 2;
            ULONG IsWexpConfiguration : 1;
            ULONG HasSubscriptions : 1;
            ULONG Variant : 6;
            ULONG VariantPayloadKind : 2;
            ULONG Reserved : 16;
        };
    };
    ULONG VariantPayload;
} RTL_FEATURE_CONFIGURATION, * PRTL_FEATURE_CONFIGURATION;

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryFeatureConfiguration(
    _In_ ULONG FeatureId,
    _In_ RTL_FEATURE_CONFIGURATION_TYPE FeatureType,
    _Inout_ PULONGLONG ChangeStamp,
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration
);

#ifndef _KERNEL_MODE
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSetFeatureConfigurations(
    _Inout_ PULONGLONG ChangeStamp,
    _In_ RTL_FEATURE_CONFIGURATION_TYPE FeatureType,
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _In_ ULONG FeatureConfigurationCount
);
#endif // !_KERNEL_MODE

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryAllFeatureConfigurations(
    _In_ RTL_FEATURE_CONFIGURATION_TYPE FeatureType,
    _Inout_ PULONGLONG ChangeStamp,
    _Out_ PRTL_FEATURE_CONFIGURATION FeatureConfigurations,
    _Inout_ PULONG FeatureConfigurationCount
);

// rev
NTSYSAPI
ULONGLONG
NTAPI
RtlQueryFeatureConfigurationChangeStamp(
    VOID
);

#ifndef _KERNEL_MODE
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlQueryFeatureUsageNotificationSubscriptions(
    _Out_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _Inout_ PULONG FeatureConfigurationCount
);
#endif // !_KERNEL_MODE

typedef VOID(NTAPI* PRTL_FEATURE_CONFIGURATION_CHANGE_NOTIFICATION)(
    _In_opt_ PVOID Context
    );

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlRegisterFeatureConfigurationChangeNotification(
    _In_ PRTL_FEATURE_CONFIGURATION_CHANGE_NOTIFICATION Callback,
    _In_opt_ PVOID Context,
    _Inout_opt_ PULONGLONG ChangeStamp,
    _Out_ PHANDLE NotificationHandle
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlUnregisterFeatureConfigurationChangeNotification(
    _In_ HANDLE NotificationHandle
);

#ifndef _KERNEL_MODE
// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlSubscribeForFeatureUsageNotification(
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _In_ ULONG FeatureConfigurationCount
);

// rev
NTSYSAPI
NTSTATUS
NTAPI
RtlUnsubscribeFromFeatureUsageNotifications(
    _In_ PRTL_FEATURE_CONFIGURATION FeatureConfiguration,
    _In_ ULONG FeatureConfigurationCount
);
#endif // !_KERNEL_MODE

#endif // NTDDI_VERSION >= NTDDI_WIN10_RS3

//
// Only Kernel RTL
//

#ifdef _KERNEL_MODE

// FsRtl

FORCEINLINE
VOID
NTAPI
FsRtlSetTopLevelIrpForModWriter()
{
    IoSetTopLevelIrp((PIRP)FSRTL_MOD_WRITE_TOP_LEVEL_IRP);
}

_Must_inspect_result_
_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
FsRtlGetFileNameInformation(                // -> FltMgr!FsRtlGetFileNameInformation
    _In_ PFILE_OBJECT FileObject,
    _In_ ULONG NameOptions,                 // FLT_FILE_NAME_OPTIONS
    _Out_ PUNICODE_STRING FileName,
    _Outptr_ PVOID* FileNameInformation     // PFLT_FILE_NAME_INFORMATION
);

_IRQL_requires_max_(APC_LEVEL)
FORCEINLINE
NTSTATUS
NTAPI
FsRtlParseFileNameInformation(
    _Inout_ PFLT_FILE_NAME_INFORMATION FileNameInformation
)
{
    return FltParseFileNameInformation(FileNameInformation);
}

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
VOID
NTAPI
FsRtlReleaseFileNameInformation(
    _In_ PVOID FileNameInformation
);

#endif // _KERNEL_MODE

VEIL_END()

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif
