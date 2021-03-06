// RUN: %clang_analyze_cc1 -std=c++11 -analyzer-checker=core,cplusplus,alpha.cplusplus.InvalidatedIterator -analyzer-config aggressive-binary-operation-simplification=true -analyzer-config c++-container-inlining=false %s -verify
// RUN: %clang_analyze_cc1 -std=c++11 -analyzer-checker=core,cplusplus,alpha.cplusplus.InvalidatedIterator -analyzer-config aggressive-binary-operation-simplification=true -analyzer-config c++-container-inlining=true -DINLINE=1 %s -verify

#include "Inputs/system-header-simulator-cxx.h"

void clang_analyzer_warnIfReached();

void normal_dereference(std::vector<int> &V) {
  auto i = V.cbegin();
  *i; // no-warning
}

void invalidated_dereference(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  *i; // expected-warning{{Invalidated iterator accessed}}
}

void normal_prefix_increment(std::vector<int> &V) {
  auto i = V.cbegin();
  ++i; // no-warning
}

void invalidated_prefix_increment(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  ++i; // expected-warning{{Invalidated iterator accessed}}
}

void normal_prefix_decrement(std::vector<int> &V) {
  auto i = ++V.cbegin();
  --i; // no-warning
}

void invalidated_prefix_decrement(std::vector<int> &V) {
  auto i = ++V.cbegin();
  V.erase(i);
  --i; // expected-warning{{Invalidated iterator accessed}}
}

void normal_postfix_increment(std::vector<int> &V) {
  auto i = V.cbegin();
  i++; // no-warning
}

void invalidated_postfix_increment(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  i++; // expected-warning{{Invalidated iterator accessed}}
}

void normal_postfix_decrement(std::vector<int> &V) {
  auto i = ++V.cbegin();
  i--; // no-warning
}

void invalidated_postfix_decrement(std::vector<int> &V) {
  auto i = ++V.cbegin();
  V.erase(i);
  i--; // expected-warning{{Invalidated iterator accessed}}
}

void normal_increment_by_2(std::vector<int> &V) {
  auto i = V.cbegin();
  i += 2; // no-warning
}

void invalidated_increment_by_2(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  i += 2; // expected-warning{{Invalidated iterator accessed}}
}

void normal_increment_by_2_copy(std::vector<int> &V) {
  auto i = V.cbegin();
  auto j = i + 2; // no-warning
}

void invalidated_increment_by_2_copy(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  auto j = i + 2; // expected-warning{{Invalidated iterator accessed}}
}

void normal_decrement_by_2(std::vector<int> &V) {
  auto i = V.cbegin();
  i -= 2; // no-warning
}

void invalidated_decrement_by_2(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  i -= 2; // expected-warning{{Invalidated iterator accessed}}
}

void normal_decrement_by_2_copy(std::vector<int> &V) {
  auto i = V.cbegin();
  auto j = i - 2; // no-warning
}

void invalidated_decrement_by_2_copy(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  auto j = i - 2; // expected-warning{{Invalidated iterator accessed}}
}

void normal_subscript(std::vector<int> &V) {
  auto i = V.cbegin();
  i[1]; // no-warning
}

void invalidated_subscript(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  i[1]; // expected-warning{{Invalidated iterator accessed}}
}

void assignment(std::vector<int> &V) {
  auto i = V.cbegin();
  V.erase(i);
  auto j = V.cbegin(); // no-warning
}

