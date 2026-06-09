#pragma once
#include "Domain.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

class CppLineCounter : public LineCounter {
public:
    AnalysisResult Analyze(const std::string& path) override {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Файл не найден");
        }
        
        AnalysisResult res;
        bool multiLine = false;

        while (true) {
            std::string line;
            if (!std::getline(file, line)) {
                break;
            }

            res.physical++;

            if (line.find(';') != std::string::npos || 
                line.find('{') != std::string::npos || 
                line.find('}') != std::string::npos) {
                res.logical++;
            }
            size_t firstNonSpace = line.find_first_not_of(" \t");
            bool isPreprocessor = (firstNonSpace != std::string::npos && line[firstNonSpace] == '#');

            if (!isPreprocessor && line.find("//") != std::string::npos) {
                res.comments++;
            
                if (file.eof()) break;
                continue; 
            }
            if (!isPreprocessor && line.find("/*") != std::string::npos) {
                multiLine = true;
            }

            if (multiLine) {
                res.comments++;
                if (line.find("*/") != std::string::npos) {
                    multiLine = false;
                }
            }

            if (file.eof()) {
                break;
            }
        }
        return res;
    }
}; 


class CppCounterCreator : public CounterCreator {
public:
    std::unique_ptr<LineCounter> CreateCounter() const override {
        std::make_unique<CppLineCounter>();
    }
};


class ConsoleLogger : public ILogger {
public:
    void Log(std::string& message) override {
        std::cout << "[Console LOG]: " << message << std::endl;
    }
};


class FileLogger : public ILogger {
public:
    void Log(std::string& message) override {
        std::ofstream out("log.txt", std::ios::app);
        if (out.is_open()) {
            out << "[File LOG]: " << message << std::endl;
        }
    }
};


inline std::unique_ptr<ILogger> LoggerFactory::CreateLogger(int type) const {
    switch (type) {
        case 1:
            return std::make_unique<ConsoleLogger>();
        case 2:
            return std::make_unique<FileLogger>();
        default:
            return std::make_unique<ConsoleLogger>();
    }
}