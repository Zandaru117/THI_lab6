#include <iostream>
#include "Logic.h"


class ConsoleUI {
private:
    std::unique_ptr<CounterCreator> creator;
    std::unique_ptr<ILogger> logger; 
public:
    ConsoleUI(std::unique_ptr<CounterCreator> c, std::unique_ptr<ILogger> l) 
        : creator(std::move(c)), logger(std::move(l)) {}
        void Start() {
        system("chcp 65001 > nul");
        
        std::string startMsg = "Начало работы программы.";
        logger->Log(startMsg);
        std::string path;
        std::cout << "Программа анализа строк кода" << std::endl;
        
        while (true) {
            std::cout << "Введите путь к файлу (или 'exit' для выхода): ";
            std::cin >> path;
            if (path == "exit") break;
            try {
                auto counter = creator->CreateCounter();
                AnalysisResult res = counter->Analyze(path);
                std::string successMsg = "Файл проанализирован: " + path;
                logger->Log(successMsg);
                std::cout << "\n=====================================" << std::endl;
                std::cout << " Физические строки: " << res.physical << std::endl;
                std::cout << " Логические строки: " << res.logical << std::endl;
                std::cout << " Строки с комментариями: " << res.comments << std::endl;
                std::cout << "=====================================\n" << std::endl;
                } catch (const std::exception& e) {
                std::string errorMsg = "Ошибка при работе с файлом: " + std::string(e.what());
                logger->Log(errorMsg);
                std::cout << "[ОШИБКА]: " << e.what() << std::endl;
            }
        }
        std::string endMsg = "Работа завершена.";
        logger->Log(endMsg);
    }
};


int main() {
    system("chcp 65001 > nul");
    
    int logType = 1;
    std::cout << "Выберите тип логирования (1 - Консоль, 2 - Файл log.txt): ";
    std::cin >> logType;
    LoggerFactory logFactory;
    auto logger = logFactory.CreateLogger(logType);
    auto counterFactory = std::make_unique<CppCounterCreator>();
    ConsoleUI ui(std::move(counterFactory), std::move(logger));
    ui.Start();

    return 0;
}
