# Adaptive Sorting Strategy Lab Report

## Part A & Part B — Implementation (`adaptive_sort.cpp`)

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int SIZE = 50;
    vector<int> arr(SIZE);

    cout << "Enter 50 integers separated by spaces:\n";
    for (int i = 0; i < SIZE; ++i) {
        cin >> arr[i];
    }

    // Step 1: Count how many elements are out of order
    int outOfOrderCount = 0;
    for (int i = 0; i < SIZE - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            outOfOrderCount++;
        }
    }

    // Step 2: Classify the array based on our count
    string classification;
    if (outOfOrderCount <= 5) {
        classification = "Best/Nearly Sorted";
    } else if (outOfOrderCount >= 44) {
        classification = "Worst/Highly Reverse-Ordered";
    } else {
        classification = "Average/Partially Ordered";
    }

    cout << "\n--- Part B: Case Classification Without Sorting ---\n";
    cout << "Input classification: " << classification << "\n";

    cout << "\n--- Part A: Adaptive Sorting Selection ---\n";
    cout << "Original Array:\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // Step 3: Pick the algorithm and sort
    if (classification == "Best/Nearly Sorted") {
        cout << "\nSelected Algorithm: Insertion Sort\n";
        // Insertion Sort Code
        for (int i = 1; i < SIZE; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    } else {
        cout << "\nSelected Algorithm: Selection Sort\n";
        // Selection Sort Code
        for (int i = 0; i < SIZE - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < SIZE; ++j) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            // Swap numbers
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }

    cout << "\nSorted Array:\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    return 0;
}
```

---

## Part C — Complexity of the Classification

### How the check works
My program uses a single loop to look through the array from the very first item to the second-to-last item. 
* **Pairs checked:** For $N$ elements, it always checks exactly $N - 1$ adjacent pairs.
* **How it scales:** If the array size doubles, the number of checks also doubles. 

### Big-O notation
The time complexity for this check is **$O(N)$**. This is because it goes through the array exactly one time from left to right, making one comparison per pair.

### Does this slow down the main sorting?
No, adding this check **does not change** the overall Big-O of the program. 
1. If the list is nearly sorted, Insertion Sort runs in $O(N)$ time. Adding our check means $O(N) + $O(N)$, which is still just **$O(N)$**.
2. If the list is average or reversed, Selection Sort runs in $O(N^2)$ time. Because $N^2$ grows so much faster than $N$, the $O(N)$ check becomes negligible. The total complexity stays **$O(N^2)$**.

---

## Part D — Documentation and Analysis

### Threshold Definition
I decided to count how many adjacent numbers are in the wrong order. 
* **Best/Nearly Sorted:** 10% or less of the pairs are out of order (0 to 5 pairs). I chose this because if only a few items are misplaced, Insertion Sort can fix them very quickly.
* **Worst/Highly Reverse-Ordered:** 90% or more of the pairs are out of order (44 to 49 pairs). This means the list is almost completely backward.
* **Average/Partially Ordered:** Anywhere between 6 and 43 pairs out of order. This represents a normal, randomized list of numbers.

### Threshold Justification
I picked 10% for the "Nearly Sorted" boundary because it gives a safe buffer where Insertion Sort still stays extremely fast. If more than 10% of adjacent pairs are out of order, the hidden shuffling work inside Insertion Sort starts growing too quickly. I picked 90% for "Highly Reverse-Ordered" because it guarantees that almost every element needs to move backwards, meaning a complete breakdown for Insertion Sort's inner mechanisms.

### Algorithm Selection
* **Best/Nearly Sorted $
ightarrow$ Insertion Sort:** Insertion Sort is really smart when a list is already mostly sorted. It can just skim through the data and only move things when it absolutely has to, making it super fast.
* **Average or Worst $
ightarrow$ Selection Sort:** When a list is messy or completely backward, Insertion Sort has to do a massive amount of shifting, which slows it down. Selection Sort is preferred here because it always does the same predictable amount of work and doesn't get overwhelmed by a messy list.

### Time Complexity
* **Selection Sort:** It does not care about the initial order. It always uses two loops to scan the entire remaining list to find the smallest number, so it is always slow ($O(N^2)$).
* **Insertion Sort:** It checks numbers backward. If a number is already bigger than the one before it, it stops checking immediately. This is why it runs super fast ($O(N)$) on sorted data, but drops to slow ($O(N^2)$) on random or backward data where it has to slide numbers over repeatedly.
* **Same Big-O, different real-world speeds:** In the average case, both are labeled $O(N^2)$, but they behave differently. Selection Sort takes a lot of time comparing numbers but does very few swaps. Insertion Sort does fewer comparisons if parts of the list are neat, but it spends a lot of energy moving items around in memory.

### Analysis and Reflection
By looking at the array before sorting, we can easily see if it is already neat, completely backward, or just random. However, checking this takes $N-1$ steps of extra work.

An adaptive strategy is **not always better**. If you only have a small list of numbers (like 10 or 15 items), the time it takes to analyze the array might be longer than just sorting it right away. 

Also, Big-O notation doesn't tell the whole story. It only tells you how an algorithm handles massive scales as numbers grow toward infinity. It ignores small details, like how fast a computer can swap numbers versus comparing them in real life.
