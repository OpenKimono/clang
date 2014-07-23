// RUN: %clang_cc1 -verify -fopenmp=libiomp5 -ast-print %s | FileCheck %s
// RUN: %clang_cc1 -fopenmp=libiomp5 -x c++ -std=c++11 -emit-pch -o %t %s
// RUN: %clang_cc1 -fopenmp=libiomp5 -std=c++11 -include-pch %t -fsyntax-only -verify %s -ast-print | FileCheck %s
// expected-no-diagnostics

#ifndef HEADER
#define HEADER

template <class T>
T foo(T argc) {
  T a = T();
#pragma omp atomic
  a++;
#pragma omp atomic read
  a = argc;
#pragma omp atomic write
  a = argc + argc;
  return T();
}

// CHECK: int a = int();
// CHECK-NEXT: #pragma omp atomic
// CHECK-NEXT: a++;
// CHECK-NEXT: #pragma omp atomic read
// CHECK-NEXT: a = argc;
// CHECK-NEXT: #pragma omp atomic write
// CHECK-NEXT: a = argc + argc;
// CHECK: T a = T();
// CHECK-NEXT: #pragma omp atomic
// CHECK-NEXT: a++;
// CHECK-NEXT: #pragma omp atomic read
// CHECK-NEXT: a = argc;
// CHECK-NEXT: #pragma omp atomic write
// CHECK-NEXT: a = argc + argc;

int main(int argc, char **argv) {
  int a = 0;
// CHECK: int a = 0;
#pragma omp atomic
  a++;
#pragma omp atomic read
  a = argc;
#pragma omp atomic write
  a = argc + argc;
  // CHECK-NEXT: #pragma omp atomic
  // CHECK-NEXT: a++;
  // CHECK-NEXT: #pragma omp atomic read
  // CHECK-NEXT: a = argc;
  // CHECK-NEXT: #pragma omp atomic write
  // CHECK-NEXT: a = argc + argc;
  return foo(a);
}

#endif