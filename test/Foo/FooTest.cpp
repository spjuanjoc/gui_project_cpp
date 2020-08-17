//
// Created by juan.castellanos on 9/07/20.
//

#include "Foo/IFoo.hpp"
#include <cstdio>

struct TestFoo : IFoo
{
  void doSomething() override
  {
    puts("Test do something");
  }
};

void TestDoSomething()
{
  TestFoo tf;
  tf.doSomething();
}

int main()
{
  TestDoSomething();
  // \todo add gtest
  return 0;
}
