
#include "./code/EuclidianArithmetic.hpp"
#include <algorithm>
#include <climits>
#include <iterator>



void swap(coordinate *a, coordinate *b) {
  coordinate temp = *b;
  *b = *a;
  *a = temp;
}
void donothing(void) {}
// in progress
// vector forms the rows of the two-dimensional euclidian plane
// coordinate ** represents a single line in the euclidian plane from left to
// right to look up or down, observe the respective row of nums and compare to
// MIN()

void copyvecL(vector<coordinate *> src, vector<coordinate *> &dest) {
  std::vector<coordinate *>::iterator p = src.begin();
  std::vector<coordinate *>::iterator x = dest.begin();
  while (x != dest.end()) {
    *x = (*p);
    x++;
    p++;
  }
  return;
}
void copyvecR(vector<coordinate *> src, vector<coordinate *> &dest) {
  std::vector<coordinate *>::iterator p = src.begin() + (src.size() / 2) + 1;
  std::vector<coordinate *>::iterator x = dest.begin();
  while (x != dest.end()) {
    *x = (*p);
    x++;
    p++;
  }

  return;
}
// Assignment 1
// 1 1.40118
// 2 1.00469
// 3 2.68663
// 4 12.334
// 5 2.0259
// 6 5.82228
// 7 24.0436
// 8 12.2882
// 9 0.07
// 10 0

void recur(vector<coordinate *> nums1, vector<coordinate *> nums2,
           long double &ans1, long double &ans2) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  double minimum = INT_MAX;
  double ans = INT_MAX;
  coordinate *p = 0x0;
  coordinate *R = 0x0;
  coordinate *L = 0x0;
  coordinate *p2 = 0x0;
  coordinate *R2 = 0x0;
  coordinate *L2 = 0x0;
  // split the array along our line at p, and then break array into left and
  // right sets to recursively solve
  int size = std::min(nums1.size(), nums2.size());
  for (unsigned x = 1; x + 1 < size; x++) {
    p = nums1[x];
    R = nums1[x + 1];
    L = nums1[x - 1];
    p2 = nums2[x];
    R2 = nums2[x];
    L2 = nums2[x];
    p->distance(R) < minimum ? minimum = p->distance(R) : minimum = minimum;
    p->distance(L) < minimum ? minimum = p->distance(L) : minimum = minimum;
    p2->distance(R2) < ans ? ans = p2->distance(R2) : ans = ans;
    p2->distance(L2) < ans ? ans = p2->distance(L2) : ans = ans;
  }
  ans1 = minimum;
  ans2 = ans;
}

vector<coordinate *> *closest_candiates(vector<coordinate *> nums) {
  // take distance between all pairs using described algorithm splitting list
  // into left and right after origin sort furthest distance should be between
  // points on opposite end of splitted array
  vector<coordinate *> *R = new vector<coordinate *>(nums.size() / 2);
  vector<coordinate *> *L = new vector<coordinate *>(nums.size() / 2);
  coordinate *p = nums[nums.size() / 2];
  copyvecL(nums, *L);
  copyvecR(nums, *R);
  long double minL, minR;
  recur(*L, *R, minL, minR);
  long double distance = std::min(minL, minR);
  // split the array along our line at p, and then break array into left and
  // right sets to recursively solve might not work for all cases because we
  // have converted 2d coordinates to 1d. will need to fix this

  vector<coordinate *>::iterator r_itr = R->begin();
  vector<coordinate *>::iterator l_itr = L->begin();
  vector<coordinate *> *candidate = new vector<coordinate *>();
  // array of iterators which contain our points of interest
  for (unsigned x = 0; x < nums.size() / 2 - 1; x++) {
    long double leftdist = p->distance(*l_itr);
    if (leftdist < distance) {
      candidate->push_back(*l_itr);
    }
    long double rightdist = p->distance(*r_itr);
    if (rightdist < distance) {
      candidate->push_back(*r_itr);
    }
    r_itr++;
    l_itr++;
  }
  return candidate;
}

// temp used for nearest pair of points
// return the pair as nums
// sort nums
// should now be sorted in terms of euclidian plane
// split nums into left and right halves using algorithm

bool less(coordinate *a, coordinate *b) {
  return a->x0() < b->x0() || (a->x0() == b->x0() && a->x1() < b->x1());
}
void printplane(vector<coordinate *> R) {
  for (int i = 0; i < R.size(); i++) {
    R[i]->printcoords();
  }
}
class Compare {
public:
  // a is less than b operator, used for sort in R^2
  bool operator()(coordinate *a, coordinate *b) {
    return a->x0() < b->x0() || (a->x0() == b->x0() && a->x1() < b->x1());
  }
};
class Comparey {
public:
  // a is less than b operator, used for sort in R^2
  bool operator()(coordinate *a, coordinate *b) { return a->x1() < b->x1(); }
};

long double smallestdist(vector<coordinate *> strip) {
  // currently working
  long double minimum=INT_MAX;
  for (int i = 0; i < strip.size()/2; i ++) {
    // pick all points one by one, and check that their distance between points
    // is lower than minimum distance d
    if (strip[i]->distance(strip[i + 1]) < minimum) {
      minimum = strip[i]->distance(strip[i + 1]);
    }
  }
  return minimum;
}
int main(int argc, char **argv) {
  PlaneArithmetic *inst = new PlaneArithmetic();
  char **t = argv;
  if (t[1] != nullptr) {
    vector<coordinate *> *array = inst->filein(t[1]);
    if (array->empty()) {
      cout << "EMPTY" << endl;
      return -1;
    } else {
      // split array into two equal subsets;
      std::sort(array->begin(), array->end(), Compare());
      printplane(*array);
      vector<coordinate *> *strip = closest_candiates(*array);
      std::sort(strip->begin(), strip->end(), Comparey());
      cout << smallestdist(*strip) << " is shortest distance" << endl;
      cout << "=END=" << endl;
      return 1;
    }
  } else {
    cout << "INVALID FILENAME" << endl;
    return -1;
  }
  //  array set to array of points, now design sort below
  //  fix below
  /*
    printplane(array);
  coordinate *ans = closestpair(array);
  */

  // array of numbers is now set, now for sorting and
  // good parse
}
