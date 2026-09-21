## Task 1: Average-Case Analysis of Insertion Sort

### How Insertion Sort Divides the Array
Insertion sort works like sorting a hand of playing cards. It splits the array into two invisible sections:
1. **Sorted Portion:** On the left side. It starts with just the very first element (since one single number is always sorted by default).
2. **Unsorted Portion:** On the right side. These are the numbers waiting to be picked up and sorted.

```
Example Mid-Sort Diagram:
[ 2,  5,  8 |  4,  1 ]
 <--Sorted->  <-Unsorted->
            (4 is the key)
```

### How Elements are Compared and Shifted
In every step, the algorithm takes the first item from the unsorted side—called the **key**—and looks backward through the sorted side from right to left. 
* It compares the key to each sorted number.
* If a sorted number is bigger than the key, it slides (shifts) that number one slot to the right to make room.
* As soon as it hits a number smaller than or equal to the key (or reaches the beginning of the array), it drops the key into the open slot.

### Mathematical Explanation of Average-Case Work
In a completely random array (the average case), any new key we pick up will likely be smaller than some sorted numbers and bigger than others. On average, the key belongs right in the **middle** of the sorted side. 

* For the 1st unsorted item (at index 1), the sorted side has 1 element. We expect to check/shift about 1/2 of it.
* For the 2nd unsorted item (at index 2), the sorted side has 2 elements. We expect to check/shift about 2/2 = 1 element.
* For the i-th unsorted item, we expect to check/shift about i/2 elements.

To find the total work for an array of N elements, we add up the work done in every step:
Total Work = 1/2 + 2/2 + 3/2 + ... + (N-1)/2
Total Work = 1/2 * [1 + 2 + 3 + ... + (N-1)]

Using the standard math trick for adding a sequence of numbers from 1 to N-1, this simplifies to:
Total Work = 1/2 * [(N-1)(N) / 2] = (N^2 - N) / 4

When looking at Big-O notation, we ignore the constant fraction (1/4) and the smaller term (-N). We only care about the fastest-growing part, which is N^2. Therefore, the average-case time complexity is **O(N^2)**.

---

## Task 2: Changing the Starting Position of Insertion Sort

We are tracing a worst-case array of size N=5 initially in descending order: `[5, 4, 3, 2, 1]`.

### Part A — Start at i = 1
* **Iteration 1 (i=1):** Array is `[5, 4, 3, 2, 1]`. Key = `4`.
  * Compare: 5 > 4 (Yes) -> Shift 5 to the right. Array becomes `[5, 5, 3, 2, 1]`.
  * Loop ends. Insert key 4 at index 0. Array: `[4, 5, 3, 2, 1]`.
  * *Stats: 1 Comparison, 1 Shift*
* **Iteration 2 (i=2):** Array is `[4, 5, 3, 2, 1]`. Key = `3`.
  * Compare: 5 > 3 (Yes) -> Shift 5. Array: `[4, 5, 5, 2, 1]`.
  * Compare: 4 > 3 (Yes) -> Shift 4. Array: `[4, 4, 5, 2, 1]`.
  * Insert key 3 at index 0. Array: `[3, 4, 5, 2, 1]`.
  * *Stats: 2 Comparisons, 2 Shifts*
* **Iteration 3 (i=3):** Array is `[3, 4, 5, 2, 1]`. Key = `2`.
  * Compare: 5 > 2 (Yes) -> Shift 5.
  * Compare: 4 > 2 (Yes) -> Shift 4.
  * Compare: 3 > 2 (Yes) -> Shift 3.
  * Insert key 2 at index 0. Array: `[2, 3, 4, 5, 1]`.
  * *Stats: 3 Comparisons, 3 Shifts*
* **Iteration 4 (i=4):** Array is `[2, 3, 4, 5, 1]`. Key = `1`.
  * Compare: 5 > 1 (Yes) -> Shift 5.
  * Compare: 4 > 1 (Yes) -> Shift 4.
  * Compare: 3 > 1 (Yes) -> Shift 3.
  * Compare: 2 > 1 (Yes) -> Shift 2.
  * Insert key 1 at index 0. Array: `[1, 2, 3, 4, 5]`.
  * *Stats: 4 Comparisons, 4 Shifts*

**Total Operations for Part A:** 10 Comparisons, 10 Shifts = **20 total operations**. The array is successfully sorted.

### Part B — Start at i = 2
We reset to the original descending array: `[5, 4, 3, 2, 1]`. We skip i=1 and start directly at i=2.
* **Iteration 1 (i=2):** Array is `[5, 4, 3, 2, 1]`. Key = `3`.
  * Compare: 4 > 3 (Yes) -> Shift 4. Array: `[5, 4, 4, 2, 1]`.
  * Compare: 5 > 3 (Yes) -> Shift 5. Array: `[5, 5, 4, 2, 1]`.
  * Insert key 3 at index 0. Array: `[3, 5, 4, 2, 1]`.
  * *Stats: 2 Comparisons, 2 Shifts*
* **Iteration 2 (i=3):** Array is `[3, 5, 4, 2, 1]`. Key = `2`.
  * Compare: 4 > 2 (Yes) -> Shift 4.
  * Compare: 5 > 2 (Yes) -> Shift 5.
  * Compare: 3 > 2 (Yes) -> Shift 3.
  * Insert key 2 at index 0. Array: `[2, 3, 5, 4, 1]`.
  * *Stats: 3 Comparisons, 3 Shifts*
* **Iteration 3 (i=4):** Array is `[2, 3, 5, 4, 1]`. Key = `1`.
  * Compare: 4 > 1 (Yes) -> Shift 4.
  * Compare: 5 > 1 (Yes) -> Shift 5.
  * Compare: 3 > 1 (Yes) -> Shift 3.
  * Compare: 2 > 1 (Yes) -> Shift 2.
  * Insert key 1 at index 0. Array: `[1, 2, 3, 5, 4]`.
  * *Stats: 4 Comparisons, 4 Shifts*

**Total Operations for Part B:** 9 Comparisons, 9 Shifts = **18 total operations**. Notice that the final array is `[1, 2, 3, 5, 4]`, which is **not fully sorted** because 5 and 4 are out of order.

### Part C — Start at i = 3
We reset to the original descending array: `[5, 4, 3, 2, 1]`. We skip i=1 and i=2 and start at i=3.
* **Iteration 1 (i=3):** Array is `[5, 4, 3, 2, 1]`. Key = `2`.
  * Compare: 3 > 2 (Yes) -> Shift 3.
  * Compare: 4 > 2 (Yes) -> Shift 4.
  * Compare: 5 > 2 (Yes) -> Shift 5.
  * Insert key 2 at index 0. Array: `[2, 5, 4, 3, 1]`.
  * *Stats: 3 Comparisons, 3 Shifts*
* **Iteration 2 (i=4):** Array is `[2, 5, 4, 3, 1]`. Key = `1`.
  * Compare: 3 > 1 (Yes) -> Shift 3.
  * Compare: 4 > 1 (Yes) -> Shift 4.
  * Compare: 5 > 1 (Yes) -> Shift 5.
  * Compare: 2 > 1 (Yes) -> Shift 2.
  * Insert key 1 at index 0. Array: `[1, 2, 5, 4, 3]`.
  * *Stats: 4 Comparisons, 4 Shifts*

**Total Operations for Part C:** 7 Comparisons, 7 Shifts = **14 total operations**. The final array is `[1, 2, 5, 4, 3]`, which is **completely incorrect**.

### Part D — Correctness Analysis
1. **Why it normally starts at i = 1:** Insertion sort requires the left portion of the array to be completely sorted before handling the next element. By starting at index 1, the "sorted portion" is just index 0, which is always sorted by default.
2. **The core assumption:** The algorithm assumes that every single element *before* index i has already been processed and is in perfect relative order.
3. **Does starting at i = 2 work?** No. It leaves the elements at index 0 and 1 completely unchecked against each other. In Part B, 5 and 4 were never compared, so they stayed out of order at the end.
4. **Does starting at i = 3 work?** No. It skips checking the first three items against one another, leaving 5, 4, and 3 broken and unsorted.
5. **Why less iterations doesn't mean it's right:** Skipping loops reduces the total code operation count, but it breaks the algorithm. If you skip initial iterations, the fundamental assumption of insertion sort is ruined, leaving old elements completely ignored and unsorted.

---

## Task 3: Improving a Search Algorithm

### Part A — Complexity Analysis of the Original Code
The original JavaScript function uses a basic `for` loop that checks every single character in the string one by one from left to right. 

* **If "X" is the first character:** The code notes that it found "X", but the loop keeps spinning and checks all the remaining letters anyway.
* **If "X" occurs in the middle or end:** It finds it, but still checks everything until the very last index.
* **If "X" does not occur:** It checks everything and returns false.
* **Why it keeps going:** The loop condition is strictly tied to `i < string.length`. There is no `break` statement or early return inside the `if` block to stop the engine.

**Big-O Performance Runtimes:**
* Best-Case: **O(N)** (Even if "X" is item #1, it performs N steps).
* Average-Case: **O(N)** (Performs N steps).
* Worst-Case: **O(N)** (Performs N steps).

### Part B — Improve the Algorithm
We can rewrite the function to stop immediately using a `return true` statement as soon as an "X" is encountered:

```javascript
function containsX(string) {
    for (let i = 0; i < string.length; i++) {
        if (string[i] === "X") {
            return true; // Stops the loop immediately and exits the function
        }
    }
    return false; // Only reached if the loop finished without finding an "X"
}
```

### Part C — Analyze the Improved Version
* Best-Case Time Complexity: **O(1)** (Constant time). If "X" is the very first character, the function instantly exits after exactly 1 comparison.
* Average-Case Time Complexity: **O(N)** (Linear time). On average, "X" might be found in the middle of the string (N/2 steps), which scales linearly as strings get longer.
* Worst-Case Time Complexity: **O(N)** (Linear time). If "X" is at the very end or completely missing, the loop must look at all N characters.

**Comparison:**
While the formal worst-case Big-O notation is still O(N) for both versions, the improved version is vastly superior in real-world scenarios. In the best and average cases, an early exit cuts out thousands of wasted iterations on large strings, freeing up system performance.

---

## Task 4: Analysis and Reflection

1. **Why Insertion Sort is Quadratic (O(N^2)):** It uses a loop inside a loop. For messy or backward inputs, every time the outer loop moves forward by one, the inner loop has to scan back across all processed elements, causing the work to double quadratically as the list expands.
2. **Importance of i = 1:** Starting at index 1 ensures that the algorithm builds on a valid, guaranteed foundation where the starting left-hand block (a single element) is perfectly sorted. Skipping this steps leaves initial values stranded and unsorted.
3. **Operations vs. Big-O Complexity:** Reducing operations means making minor code tweaks to skip basic steps (like changing a starting index to i=2). Reducing Big-O complexity requires changing the fundamental behavior of the algorithm so that its work scales better mathematically as inputs scale toward infinity.
4. **Why same Big-O algorithms perform differently:** Big-O only looks at structural growth behavior at a massive scale. In reality, one algorithm might perform fewer memory writes or benefit from early exit conditions (like our improved search loop) making it noticeably faster on everyday hardware.
