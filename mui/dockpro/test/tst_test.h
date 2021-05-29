#ifndef TST_TEST_H
#define TST_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

namespace mkgo {

    class TestThread : public ::testing::Test
    {

    protected:

      virtual void SetUp();
      virtual void TearDown();

    };

}


#endif // TST_TEST_H
