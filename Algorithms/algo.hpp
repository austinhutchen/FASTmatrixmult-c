#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iterator>
#pragma ONCE
#include "algo.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class Solution {
public:
  Solution() {}

  vector<int> abs(vector<int> &nums) {
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] < 0) {
        ans.push_back(~nums[i] + 1);
      } else {
        continue;
      }
    }
    return ans;
  }

  void msort_itr(vector<char> &unsorted, unsigned a, unsigned p, unsigned q) {
    // works so long as a<=p<q
    size_t n1 = p - a + 1;
    size_t n2 = q - p;
    size_t i = 0;
    size_t j = 0;
    vector<int> *L = new vector<int>(n1 + 1);
    vector<int> *R = new vector<int>(n2 + 1);
    std::vector<int>::iterator L_ptr = L->begin();
    std::vector<int>::iterator R_ptr = R->begin();
    *L->end() = INT_MAX;
    *R->end() = INT_MAX;
    for (; L_ptr != L->end() && R_ptr != R->end(); i++ && j++) {
      *L_ptr = (unsorted[i + a]);
      *R_ptr = (unsorted[j + p + 1]);
      L_ptr++;
      R_ptr++;
    }
    i = j = 0;
    L_ptr = L->begin();
    R_ptr = R->begin();
    auto Rend = R->end();
    auto Lend = L->end();
    for (unsigned k = a; k < q && L_ptr != Lend && R_ptr != Rend; k++) {
      if (*L_ptr <= *R_ptr) {
        unsorted[k] = *L_ptr;
        L_ptr++;
      } else {
        unsorted[k] = *R_ptr;
        R_ptr++;
      }
    }
  }

  void msort(vector<int> &unsorted, unsigned a, unsigned p, unsigned q) {
    // works so long as a<=p<q
    size_t n1 = p - a + 1;
    size_t n2 = q - p;
    unsigned i = 0;
    unsigned j = 0;
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    for (; i < n1; i++) {
      L[i] = (unsorted[i + a]);
    }
    for (; j < n2; j++) {
      R[j] = (unsorted[j + p]);
    }
    R[n1] = INT_MAX;
    L[n2] = INT_MAX;
    i = j = 0;
    for (unsigned k = a; k < q && i < n1 && j < n2; k++) {
      if (L[i] <= R[j]) {
        unsorted[k] = L[i];
        i++;
      } else {
        unsorted[k] = R[j];
        j++;
      }
    }
  }

  int findClosestNumber(vector<int> &nums) {
    // find closest number to 0 within an array of integers nums
    switch (nums.size()) {
    case 0: {
      return 0;
      break;
    }
    case 1: {
      return nums[0];
      break;
    }
    default: {
      vector<int> absolute = abs(nums);
      msort(absolute, 0, (nums.size() - 1) / 2, nums.size() - 1);
      msort(nums, 0, (nums.size() - 1) / 2, nums.size() - 1);
      if (absolute[0] != nums[0]) {
        // closest number to 0 is negative
        return nums[0];
      } else {
        return absolute[0];
      }
    }
    }
  }

  int fib(int n) {
    if (n == 0 || n == 1) {
      return n;
    } else {
      n = fib(n - 1) + fib(n - 2);
    }
    return n;
  }

  bool strPal(string check) {
    std::stack<char> ans;
    int i = 0;
    for (; i < check.size(); i++) {
      ans.push(check[i]);
    }
    i = 0;
    while (!ans.empty()) {
      if (ans.top() == check[i]) {
        i++;
        ans.pop();
        continue;
      } else {
        return false;
      }
    }
    return true;
  }

  bool isPalindrome(ListNode *head) {
    if (head == NULL) {
      return true;
    }
    string result;
    ListNode *temp = head;
    while (temp != NULL) {
      result.push_back(char(temp->val));
      temp = temp->next;
    }
    return strPal(result);
  }

  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    // merge sorted array
    std::vector<int>::iterator L_ptr = nums1.begin();
    std::vector<int>::iterator R_ptr = nums2.begin();
    if (L_ptr == nums1.end() || R_ptr == nums2.end()) {
      return;
    }
    auto Lend = nums2.end();
    size_t size = nums1.size();
    unsigned i = m;
    for (unsigned k = 0; k < size && L_ptr != Lend && i < size; k++) {
      if (nums1[k] <= *L_ptr) {
        nums1[k] = *L_ptr;
        L_ptr++;
      }
      if (nums1[i] <= *R_ptr) {
        nums1[i] = *R_ptr;
        R_ptr++;
        i++;
      }
    }
    bubble(nums1);
  }

  void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
  }

  void bubble(vector<int> &unsorted) {
    for (int i = 0; i < unsorted.size(); i++) {
      for (int j = i + 1; j < unsorted.size(); j++) {
        if (unsorted[i] > unsorted[j]) {
          this->swap(&unsorted[i], &unsorted[j]);
        }
      }
    }
  }

  void lowercase(char &start) {
    // convert all characters in c string to lowercasew with pointers;
    char *p = &start;
    while (*p != '\0') {
      if (*p >= 97 && *p <= 122) {
        *p = tolower(*p);
      }
      p++;
    }
  }

  bool isomorphic(std::stack<char> stck, std::string string) {
    uint i = 0;
    while (!stck.empty()) {
      if (string[i] == stck.top()) {
        i++;
        stck.pop();
      } else {
        return false;
      }
    }
    return true;
  }

  void alphastr(string &check) {
    // does check have all alphanumeric characters?
    // alphanumeric characters lie in the ASCII value range of [65, 90] for
    // uppercase alphabets, [97, 122] for lowercase alphabets, and [48, 57] for
    // digits
    char *c = &check[0];
    for (; *c != '\0'; c++) {
      if (*c >= 65 && *c <= 90 || *c >= 97 && *c <= 122 ||
          *c >= 48 && *c <= 57) {
        // alphanumeric
        continue;
      } else {
        // will need to be changed to45t3y fully remove the nonalphanumeric
        // indices
        *c = ' ';
      }
    }
    return;
  }

  bool isPalindrome(string s) {
    // determine if string is a palindrome after removing non alphanumeric
    // characters from str
    if (s.size() == 0) {
      return false;
    }
    alphastr(s);
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    lowercase(s[0]);
    std::stack<char> nums;
    for (int i = 0; i < s.size(); i++) {
      nums.push(s[i]);
    }
    return isomorphic(nums, s);
  }

  int majorityElement(vector<int> &nums) {
    uint sz = nums.size();
    if (sz == 1) {
      return nums[0];
    }
    for (vector<int>::iterator p = nums.begin(); p != nums.end(); p++) {
      uint counter = 1;
      for (vector<int>::iterator i = nums.begin(); i != nums.end(); i++) {
        if (*i == *p && p != i) {
          counter++;
        }
      }
      if (counter > sz / 2) {
        return *p;
      }
    }
    return 0x0;
  }

  void moveZeroes(vector<int> &nums) {
    std::queue<int> ordered;
    for (vector<int>::iterator i = nums.begin(); i != nums.end(); i++) {
      if (*i == 0) {
        continue;
      } else {
        ordered.push(*i);
      }
    }
    uint sz = ordered.size();
    uint i = 0;
    while (!ordered.empty()) {
      nums[i] = ordered.front();
      ordered.pop();
      i++;
    }
    for (; i < nums.size(); i++) {
      nums[i] = 0;
    }
    return;
  }

  bool isSubsequence(string s, string t) {
    if (s.size() == 0) {
      return true;
    }
    if (t.size() == 0) {
      return false;
    }
    if (s.size() > t.size()) {
      return false;
    }
    std::stack<char> stck;
    for (int i = s.size() - 1; i >= 0; i--) {
      stck.push(s[i]);
    }
    for (int i = 0; i < t.size(); i++) {
      while (!stck.empty() && stck.top() == t[i]) {
        stck.pop();
      }
      if (stck.empty()) {
        return true;
      }
    }
    return false;
  }

  vector<int> removeDuplicates(vector<int> &nums) {
    // use queue and loop through entire array??
    std::queue<int> q;
    vector<int> ans;
    int fix = 0;
    while (fix < nums.size()) {
      bool flag = false;
      q.push(nums[fix]);
      for (int i = fix + 1; i < nums.size(); i++) {
        if (q.front() == nums[i]) {
          // duplicate, needs to be removed from vector
          flag = true;
          break;
        }
      }
      if (flag != true) {
        // is NOT a duplicate
        // take out of queue
        q.pop();
        ans.push_back(nums[fix]);
        fix++;
      } else {
        // IS a duplicate, dont add to ans, leave in queue
        continue;
      }
    }
    return ans;
  }

  int removeDuplicatesconstant(vector<int> &nums) {
    // bubble sort method
    int index = 1;
    // sorts using a fixed in-place variable index that iterates up to store
    // non-duplicates
    for (int y = 1; y < nums.size(); y++) {
      if (nums[y] != nums[y - 1]) {
        nums[index] = nums[y];
        index++;
      }
    }
    return index;
  }

  int removeElement(vector<int> &nums, int val) {
    // bubble up unique integers in numsß using fixed index iterator
    int k = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == val) {
        // start point for search on rest of elements in array
        nums.erase(nums.begin() + i);
      } else {
        k++;
      }
    }
    return k;
  }

  void deletenode(ListNode *head, int val) {
    if (head == 0x0) {
      return;
    }
    ListNode *temp = head;
    ListNode *prev = temp;
    while (prev != 0x0 && temp->val != val) {
      prev = temp;
      temp = temp->next;
    }

    prev->next = temp->next;
    delete temp;
    temp = 0x0;
    return;
  }

  void populate(ListNode *head, std::vector<int> &vals) {
    ListNode *temp = head;
    while (temp->next != 0x0) {
      vals.push_back(temp->val);
      temp = temp->next;
    }
    return;
  }

  ListNode *deleteDuplicates(ListNode *head) {
    if (head == 0x0) {
      return 0x0;
    }
    std::vector<int> vals;
    populate(head, vals);
    int src = removeDuplicatesconstant(vals);
    for (int k = 0; k < vals.size(); k++) {
      // duplicates to remove in LL
      deletenode(head, vals[k - 1]);
    }
    return head;
  }

  string restoreString(string s, vector<int> &indices) {
    string ans(s.size(), '.');
    for (int i = 0; i < s.size(); i++) {
      ans[indices[i]] = s[i];
    }
    return ans;
  }

  void removeclosestoccurences(char in) {
    // use pointer to a to increment and decrement for nearest occurences near
    // index in str of a assume input is a char* with "I am unwell\" \"We need
    // to go..." rewrite string with pointers
    char *src, *dest;
    src = dest = &in; // both pointers point to the first char of input
    while (*src != '\0' && src) // exit loop when null terminator reached
    {
      if (in != *src) // if source is not a " char
      {
        *dest = *src; // copy the char at source to destination
        dest++;       // increment destination pointer
      } else {
        dest++;
      }
      src++; // increment source pointer
    }
    *dest = '\0'; // terminate string with null terminator

    // input now contains "I am unwell We need to go..."
  }

  int minimizedStringLength(string s) {
    int size = s.size();
    for (int i = 0; i < size; i++) {
      removeclosestoccurences(s[i]);
    }
    return s.size();
  }

  string makeGood(string s) {
    std::stack<int> ans;
    string final(s.size(), ' '); // initialize string ans with size = s.size()
    short int prev;
    for (int i = 0; i < s.size(); i++) {
      ans.push(s[i]);
    }
    while (ans.top()) {
      if (ans.top() == prev + 32 || ans.top() == prev - 32) {
        // dont add these to new string;
        continue;
      } else {
        final.push_back(ans.top());
      }
      prev = ans.top();
      ans.pop();
    }
    return final;
  }

  void bubsort(string &unsorted) {
    for (int i = 0; i < unsorted.size(); i++) {
      for (int j = i + 1; j < unsorted.size(); j++) {
        if (unsorted[i] > unsorted[j]) {
          char t = unsorted[j];
          unsorted[j] = unsorted[i];
          unsorted[i] = t;
        }
      }
    }
  }
};
