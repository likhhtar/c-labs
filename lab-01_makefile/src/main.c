#include "algorithm.h"
#include "util.h"
#include "io.h"
// #include "io.c"
// Ошибкa «повторное определение»

//int mian(){
// Ошибкa «неопределённая ссылка»
int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  // Max(a, b);
  // Ошибкa «неопределённая ссылка»
  logDebug('!');
}
