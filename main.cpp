#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <deque>
#include <random>

// Quicksort:

// i. Partitioning
//  #1 Select the front as pivot and move it to the front.
//  Example:
//  unsorted: [9,2,1,6,8,5,3,4,11]
//             ^
//            pivot
//

// ii. Rearrange the container
//      - such that all left-hand-side elements of the pivot are lesser than the pivot
//      - and all right-hand-side elements of the pivot are larger than the pivot

//  Partitioning operation:
//  Step1: scan the container from left to right to look for an element l larger than pivot
//  unsorted: [9,2,1,6,8,5,3,4,11]
//             ^                ^
//            pivot             l
//
//  Step2: scan the container from right to left to look for an element r lesser than pivot
//  unsorted: [9,2,1,6,8,5,3,4,11]
//             ^             ^  ^
//            pivot          r  l
//
// Step3: if (l < r) swap element l  with element r and go back to step 1
//        otherwise swap pivot with element r (partitioning finished)
//  unsorted: [4,2,1,6,8,5,3,9, 11]
//             ^             ^  ^
//             r          pivot l
//
//  Such That [4,2,1,6,8,5,3] are all less than the pivot and [11] are all larger than pivot.

//  iii. Sorting the sub-containers recursively using the same method

/* Function to print the container */
template<typename T, template<typename ...> class container = std::vector>
void printResult(container<T> result) {
  for (auto const &r : result) {
    std::cout << r << " ";
  }
  std::cout << std::endl;
}

template<typename T, template<typename ...> class container = std::vector>
size_t partition(container<T> &unsorted, size_t begin, size_t end) {
  if (begin < end) {
    size_t l = begin + 1;
    size_t r = end;
    bool done = false;

    while (!done) {

      // Step1: scan the container from left to right to look for an element l larger than pivot
      while (l < r && unsorted[l] <= unsorted[begin])
        l++;

      // Step2: scan the container from right to left to look for an element r lesser than pivot
      while (unsorted[r] > unsorted[begin])
        r--;

      // Step3: if(i < j) swap element i  with element j and go back to step 1
      if (l < r) {
        std::swap(unsorted[l], unsorted[r]);
      }

        //otherwise swap pivot with element j (partitioning finished)
      else
        done = true;
    }
    std::swap(unsorted[begin], unsorted[r]);
    return r;
  }
}

template<typename T, template<typename ...> class container = std::vector>
void quickSort(container<T> &unsorted, size_t begin, size_t end) {
  if(unsorted.size() == 0)
    return;
  assert(begin >= 0);
  assert(end >= 0);

  if (begin < end) {
    int pivotIndex = partition(unsorted, begin, end);

    // Left
    if (pivotIndex != 0)
      quickSort(unsorted, begin, pivotIndex - 1);

    // Right
    if (pivotIndex != end)
      quickSort(unsorted, pivotIndex + 1, end);
  }
}

template<typename T, template<typename ...> class container = std::vector>
void test_case(container<T> && unsorted){
  container<T> q_res = unsorted;
  container<T> s_res = unsorted;
  std::cout << "unsorted container: ";
  if (unsorted.size() < 100)
    printResult(s_res);

  auto start = std::chrono::high_resolution_clock::now();
  quickSort(q_res, 0, std::size(q_res) - 1);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Container after quickSort(): ";
  std::cout << "Time taken by quickSort():: " << duration.count() << " microseconds" << std::endl;

  if (unsorted.size() < 100)
    if (unsorted.size() < 100)printResult(q_res);
  std::cout << "Container after std::sort(): ";
  start = std::chrono::high_resolution_clock::now();
  std::sort(begin(s_res), end(s_res));
  stop = std::chrono::high_resolution_clock::now();
  duration = duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Container after std::sort(): ";
  std::cout << "Time taken by std::sort: " << duration.count() << " microseconds" << std::endl;
  if (unsorted.size() < 100)
    printResult(s_res);
  std::cout << std::endl;
  assert(q_res == s_res);
}

int main() {
  test_case(std::move(std::vector<int>{}));
  test_case(std::move(std::vector<int> {11,2,1,6,8,5,3,4,9}));
  test_case(std::move(std::deque<std::string> {"zaaa", "zab", "c", "k"}));

  std::random_device crypto_random_generator;
  std::normal_distribution<double> distribution(0,999999);

  std::vector<double> actual_distribution;
  for(int i = 0; i < 9999999; i++) {
    actual_distribution.emplace_back(distribution(crypto_random_generator));
  }
  test_case(std::move(actual_distribution));

  return 0;
}
