#include "stack.hpp"
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


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


/**
 *  @brief 
 *      Defining macro for excepting error.
 * 
 *  @see
 *      https://stackoverflow.com/questions/39578934#39578934
 */
#define ASSERT_EXCEPTION( TRY_BLOCK, EXCEPTION_TYPE, MESSAGE, HASEXCEPT)            \
try                                                                                 \
{                                                                                   \
    TRY_BLOCK                                                                       \
    std::cerr << "exception '" << MESSAGE << "' not thrown at all!\n";              \
}                                                                                   \
catch( const EXCEPTION_TYPE& e )                                                    \
{                                                                                   \
    if(assertEqual( MESSAGE, std::string(e.what()) ))                               \
    {                                                                               \
        std::cerr << "\x1B[33mExpect Thrown succesfully --> EXPECTED : \n\t" <<     \
        "[ " << MESSAGE << " ]\n";                                                  \
        HASEXCEPT = true;                                                           \
    } else                                                                          \
    {                                                                               \
        std::cerr << " exception message is incorrect. Expected the following" <<   \
        "message\n\n";                                                              \
    }                                                                               \
}                                                                                   \
catch( ... )                                                                        \
{                                                                                   \
    std::cerr << "exception '" << MESSAGE                                           \
           << "' not thrown with expected type '" << #EXCEPTION_TYPE                \
           << "'!";                                                                 \
}


namespace Test {
    bool testCase001_testEmptyStack() {
        myTemplate::Stack<int> myStack;

        return assertEqual(myStack.isEmpty(), true);
    }

    
    bool testCase002_testEmptyStackPop() {
        bool exceptcheck = false;
        myTemplate::Stack<int> myStack;
        // myStack.push(1);

        std::cout << "\x1B[34m==\tTestCase03\t==" << std::endl;
        ASSERT_EXCEPTION({
            myStack.pop();
        }, std::domain_error, std::string("Error..! Stack is empty"), exceptcheck);

        std::cout << "\n\n";
        
        return exceptcheck;
    }


    bool testCase003_testEmptyStackTop() {
        bool exceptcheck = false;
        myTemplate::Stack<int> myStack;

        std::cout << "\x1B[34m==\tTestCase03\t==" << std::endl;
        ASSERT_EXCEPTION({
            myStack.top();
        }, std::domain_error, std::string("Error..! Stack is empty"), exceptcheck);

        std::cout << "\n\n";
        return exceptcheck;
    }


    bool testCase004_testStackWithPrimitiveTypes() {
        myTemplate::Stack<int> myStack;
        std::vector<int>  myTestVec {5, 8, 7, 23, 43, 654, 42, 43};

        for (const auto& var : myTestVec) {
            myStack.push(var);
            myTestVec.pop_back();
        }

        while (!myStack.isEmpty()) {
            myTestVec.push_back(myStack.top());
            myStack.pop();
        }
        return assertEqual(myTestVec, std::vector<int>({43, 42, 654, 43, 23, 7, 8, 5}));
    }


    bool testCase005_testStackWithUserDefinesTypes() {
        /**
         *  @brief 
         *      Internal Class
         */
        class MyTestClass {
        public:
            MyTestClass() : nv(" "), val(0) {
            }

            MyTestClass(std::string nv, short val) : nv(nv), val(val) {
            }


            bool isEquals(const MyTestClass& rhs) const {
                return (this->nv == rhs.nv && this->val == rhs.val) ? true : false;
            }
            

        private:
            std::string nv;
            short val;
        };

        
        bool check = true;
        std::vector<MyTestClass> myTestVec;
        myTemplate::Stack<MyTestClass> myStack;

        myTestVec.emplace_back("apple",     1);
        myTestVec.emplace_back("banana",    5);
        myTestVec.emplace_back("melon",     8);
        myTestVec.emplace_back("orange",    7);
        myTestVec.emplace_back("cherry",    8);
        myTestVec.emplace_back("peach",     6);


        for (const auto& var : myTestVec) {
            myStack.push(var);
        }


        int i = myTestVec.size() - 1;
        while(!myStack.isEmpty()) {
            if (!assertTrue(myStack.top().isEquals(myTestVec[i--]))) {
                check = false;
                break;
            }

            myStack.pop();
        }

        return check;
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

        if (testCase001_testEmptyStack()) {
            testVec.emplace_back(1, "testEmptyStack", true);
        } else {
            testVec.emplace_back(1, "testEmptyStack", false);
        }

        if (testCase002_testEmptyStackPop()) {
            testVec.emplace_back(2, "testEmptyStackPop", true);
        } else {
            testVec.emplace_back(2, "testEmptyStackPop", false);
        }

        if (testCase003_testEmptyStackTop()) {
            testVec.emplace_back(3, "testEmptyStackPop", true);
        } else {
            testVec.emplace_back(3, "testEmptyStackPop", false);
        }


        if (testCase004_testStackWithPrimitiveTypes()) {
            testVec.emplace_back(4, "testStackWithPrimitiveTypes", true);
        } else {
            testVec.emplace_back(4, "testStackWithPrimitiveTypes", false);
        }

        if (testCase005_testStackWithUserDefinesTypes()) {
            testVec.emplace_back(5, "testStackWithUserDefinesTypes", true);
        } else {
            testVec.emplace_back(5, "testStackWithUserDefinesTypes", false);
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
    static void Run(std::vector<std::string> args) {
        Test::runAllTests();
    }
}


int main(int argc, const char* argv[]) {
    App::Run({argv + 1, argv + argc});
}