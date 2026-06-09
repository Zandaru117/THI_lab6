#include "Logic.h"
#include <iostream>

int main() {
    std::cout << "[==========] Running 2 tests from LineCounterTestSuite\n";
    std::cout << "[----------] Global test environment set-up.\n\n";

    CppCounterCreator creator;
    auto counter = creator.CreateCounter();


    //тест 1 проверка с решеткой

    std::cout << "[ RUN      ] LineCounterTest.IncludeDirectives\n";
    
    // Передаем путь к файлу из папки test
    AnalysisResult res1 = counter->Analyze("../test/include.cpp");
    
    if (res1.comments != 0) {
        std::cerr << "test/include.cpp: Failure\n";
        std::cerr << "Expected equality of these values:\n";
        std::cerr << "  res1.comments -> Which is: " << res1.comments << "\n";
        std::cerr << "  Expected      -> Which is: 0\n";
        std::cerr << "[  FAILED  ] LineCounterTest.IncludeDirectives\n\n";
    } else {
        std::cout << "[  PASSED  ] LineCounterTest.IncludeDirectives\n\n";
    }

    // =========================================================================
    // ТЕСТ №2: Проверка бага с 17-й пустой строкой
    // =========================================================================
    std::cout << "[ RUN      ] LineCounterTest.EmptyLinesCount\n";
    
    // Передаем путь ко второму файлу из папки test
    AnalysisResult res2 = counter->Analyze("../test/empty.cpp");
    
    if (res2.physical != 17) {
        std::cerr << "test/empty.cpp: Failure\n";
        std::cerr << "Expected equality of these values:\n";
        std::cerr << "  res2.physical -> Which is: " << res2.physical << "\n";
        std::cerr << "  Expected      -> Which is: 17\n";
        std::cerr << "[  FAILED  ] LineCounterTest.EmptyLinesCount\n\n";
    } else {
        std::cout << "[  PASSED  ] LineCounterTest.EmptyLinesCount\n\n";
    }

    std::cout << "[----------] Global test environment tear-down.\n";
    std::cout << "[==========] 2 tests ran. 0 passed. 2 failed.\n";
    
    return 0;
}