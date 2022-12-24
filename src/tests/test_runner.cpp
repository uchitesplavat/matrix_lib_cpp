#include "gtest/gtest.h"

int main() {
    testing::InitGoogleTest();
    if (RUN_ALL_TESTS()) {
        std::cout << "Some tests have failed :(\n"
                  << "Get back to work!" << "\n";
    } else {
        std::cout << "Great work!" << "\n";
    }
}