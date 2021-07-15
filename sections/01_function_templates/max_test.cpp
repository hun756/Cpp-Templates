#include "max.hpp"
#include <vector>
#include <string>
#include <iostream>


/**
 *  @brief 
 *      Assertions....! 
 */
template <typename T>
bool assertEqual(const T& val1, const T& val2) {
    return (val1 == val2);
}


template <typename T>
bool assertNotEqual(const T& val1, const T& val2) {
    return (val1 != val2);
}


inline bool assertTrue(bool conditionResult) {
    return conditionResult;
}


namespace Test {
    bool testCase001_testInteger() {
        int testVal = 42;

        return assertEqual(myTemplates::max(7, 42), 42);
    }


    bool testCase002_testDouble() {
        double testVal1 = 3.7, testVal2 = -6.5;

        return assertNotEqual(myTemplates::max(testVal1, testVal2), -6.5);
    }


    bool testCase003_testString() {
        std::string testVal1 = "mathemathics", testVal2 = "maths";

        return assertTrue(myTemplates::max(testVal1, testVal2) == testVal2);
    }


    bool testCase004_testDifferenType() {
        int testVal1 = 4;
        double testVal2 = 5.2;

        return assertTrue(myTemplates::max(testVal1, testVal2) == testVal2);
    }


    namespace Colorize {
        static std::string True(std::string str) {
            return "\x1B[32m" + str + "\033[0m";
        }


        static std::string False(std::string str) {
            return "\x1B[31m" + str + "\033[0m";
        }
    }
    

    void runAllTests() {
        int passingTest = 0;

        struct testInfo {
            short testNo {};
            std::string testName {};
            bool testState {};

            testInfo(short testNo, std::string testName, bool testState) 
                : testNo(testNo), testName(testName), testState(testState) {} 
        };

        std::vector<testInfo> testVec;

        if (testCase001_testInteger()) {
            testVec.emplace_back(1, "testInteger", true);
        } else {
            testVec.emplace_back(1, "testInteger", false);
        }

        if (testCase002_testDouble()) {
            testVec.emplace_back(2, "testDouble", true);
        } else {
            testVec.emplace_back(2, "testDouble", false);

        } if (testCase003_testString()) {
            testVec.emplace_back(3, "testString", true);
        } else {
            testVec.emplace_back(3, "testString", false);
        }

        if(testCase004_testDifferenType()) {
            testVec.emplace_back(4, "testDifferenType", true);
        } else {
            testVec.emplace_back(4, "testDifferenType", false);
        }


        for(const auto& var : testVec) {
            if (var.testState) {
                std::cout << "\x1B[32m" << "[OK]\t" << "\033[0m";
                ++passingTest;
            } else {
                 std::cout << "\x1B[31m" << "[ERR]\t" << "\033[0m";
            }

            std::cout <<  "testNo[" << var.testNo << ']' << "\t-->\t" << var.testName << '\n';
        }

        std::cout << '\n' << "Test Runned [" << passingTest << '/' << testVec.size() << ']' << '\n';
        if (passingTest == testVec.size()) {
            // std::cout << "\x1B[32m" << "All tests passed successfully" << "\033[0m" << '\n';
            std::cout << Colorize::True("All tests passed successfully") << std::endl;
        } else {
            // std::cout << "\x1B[31m" << "Some test cases failed." << "\033[0m" << '\n';
            std::cout << Colorize::False("Some test cases failed.") << std::endl;
        }
    }

};


namespace App {
    static void run(std::vector<std::string> args) {
        Test::runAllTests();
    }
}


/**
 *  @brief 
 *      Application Startpoint 
 */
int main(int argc, const char* argv[]) {
    App::run({argv + 1, argv + argc});
}