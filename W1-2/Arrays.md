#1.
```cpp
int numbers[100];
```
By doing this I am making an array called numbers and it contains 100 integers.
#2.
```cpp
#include <iostream>
using namespace std;

int main(){
  int numbers[100]
  cout << "Size of one element:" << sizeof(numbers[0]) << "bytes" << endl;

  return 0;
} 
```
With this code it will give me the Total size of the array, since an "int" is 4 bytes typically that would be 100 *4 = 400 bytes.
#3.
Operation -> 
Steps -> reasoning
Reading -> 
1 o(1) -> The element is being accessed directly from the index
Searching for a value not contained within the array -> 
100 o(N) -> With this method every element has to be checked
Insertion at the beginning of the array ->
100 o(N) -> The existing elements be shifted to make room 
Insertion at the end of the array ->
1 o(1) -> No existing elements need to be 
Deletion at the beginning of the array ->
100 o(N) -> the remaining elements must be shifted left  
Deletion at the end of the array ->
1 o(1) -> No other elements need to be shifted
#4.
A program can not simply stop after find the first "apple" because there can be values of "apples" later in the array.
That being said, with an array with N elements it would take N steps o(N)
#5.
```cpp
#include <iostream>
using namespace std;

int main(){
  int numbers[100];
  cout << " First element adress:" << &numbers[0] << endl;
  return 0;
}
