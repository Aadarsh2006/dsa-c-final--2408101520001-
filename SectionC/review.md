## C1 Defect Report

| No | Line | Defect | Consequence |
|----|------|--------|-------------|
| 1 | 4 | `prev` is not initialized before it is assigned to `curr->next`. | Uses an uninitialized pointer, causing undefined behavior. |
| 2 | 6 | Loop condition is `while (curr->next != NULL)` instead of `while (curr != NULL)`. | The last node is never reversed, and if `head == NULL`, it dereferences a NULL pointer. |
| 3 | 12 | Returns `head` instead of `prev`. | Returns the original head instead of the new head of the reversed list. |

Corrected function: `SectionC/C1_reverse.c`

Complexity: **Time O(n), Space O(1)**

## C2 Optimization

### Current Time Complexity

- **Time Complexity:** **O(n²)**
- **Reason:** The function uses two nested loops to check every possible contiguous subarray. For `n = 1,000,000`, this results in about \(10^{12}\) operations, making it too slow.


```

Complexity: Time **O(n)**, Space **O(1)**

Condition: The sliding window approach is valid because **all array elements are positive integers**, so the window sum only increases when expanding and only decreases when shrinking. This ensures the left pointer never moves backward.