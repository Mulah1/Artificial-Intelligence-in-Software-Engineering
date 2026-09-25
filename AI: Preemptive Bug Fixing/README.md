# AI: Preemptive Bug Fixing

## Objective
Use a structured, role-based AI prompt to review a vulnerable C linked-list function for correctness, memory safety, and error handling, then apply the proposed fix.

## Files
- [`initial_add_node_end.c`](./initial_add_node_end.c): The vulnerable implementation supplied in the task.
- [`refactored_add_node_end.c`](./refactored_add_node_end.c): The corrected implementation.
- [`ai_code_review_response.md`](./ai_code_review_response.md): The structured prompt and the resulting review content, including the identified flaws and corrected function.

## Structured AI Prompt

> Act as a Senior C Developer conducting a rigorous code review. Review the following function, which should add a new node to the end of a singly linked list. Assume `list_t` is defined as `struct list_s { int n; struct list_s *next; };`.
>
> ```c
> list_t *add_node_end(list_t *head, const int n) {
>     list_t *new_node = malloc(sizeof(list_t));
>     list_t *current = head;
>     if (!head)
>         return (new_node);
>     while (current)
>         current = current->next;
>     current = new_node;
>     new_node->n = n;
>     new_node->next = NULL;
>     return (head);
> }
> ```
>
> Review it for: (1) correctness and logical errors when adding to a non-empty list, especially whether traversal actually links the new node; (2) memory safety and error handling, including whether `malloc` can return `NULL` before `new_node` is dereferenced; and (3) leaks or ownership problems, explaining when an allocated node becomes unreachable. Explain every flaw in detail, then provide a complete corrected C function. The corrected function must handle an empty list, append to a non-empty list, check allocation failure, initialize the node safely, and return the appropriate list pointer.

## Review Findings

1. **Logical linking error:** `while (current)` traverses until `current` becomes `NULL`. The statement `current = new_node;` only changes the local traversal variable; it does not update the previous node's `next` member. Consequently, the new node is unreachable from `head`.
2. **Allocation failure:** `malloc` may return `NULL`. The original function dereferences `new_node` through `new_node->n` and `new_node->next`, which can cause a segmentation fault.
3. **Unreachable allocation / leak:** For a non-empty list, because the new node is never linked, the allocated block has no remaining pointer after the function returns. That is a memory leak. Once the node is correctly linked, the list owns it and it is no longer leaked by this function.
4. **Initialization order:** The corrected version initializes the node only after verifying that allocation succeeded.

## Analysis of the Logical Fix

The original `while (current)` loop advances `current` past the last node until it becomes `NULL`, which is the termination condition for traversal. The following `current = new_node` only assigns the new address to the local variable `current`; it does not write to the last node's `next` field, so the new node is not connected to the list. The fix stops at the last node with `while (current->next != NULL)` and assigns `current->next = new_node`.

## Analysis of the Memory Fix

`malloc` can fail and return `NULL`, especially when the allocation cannot be satisfied. Dereferencing `new_node` without checking it can therefore cause a segmentation fault. The corrected function checks `new_node == NULL` before using it and returns `NULL` to report failure; it also ensures that a successfully allocated node is linked into the list so it does not become unreachable.

## Screenshot / Google Doc Deliverable

The assignment requires a screenshot of the AI response and a Google Doc named **Mulah_AI: Preemptive Bug Fixing**. A screenshot and Google Doc cannot be created or attached through the available GitHub repository tools. The complete prompt, review findings, and corrected function are preserved in `ai_code_review_response.md` so they can be pasted into the document alongside the screenshot captured from the AI tool.

## Repository Link

[Task folder](https://github.com/Mulah1/Artificial-Intelligence-in-Software-Engineering/tree/main/AI%3A%20Preemptive%20Bug%20Fixing)
