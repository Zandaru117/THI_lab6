#pragma once
#include <string>
#include <memory>


struct AnalysisResult {
    int physical = 0;
    int logical = 0;
    int comments = 0;
};


class LineCounter {
public:
    virtual ~LineCounter() = default;
    virtual AnalysisResult Analyze(const std::string& path) = 0; 
};


class CounterCreator {
public:
    virtual ~CounterCreator() = default;
    virtual std::unique_ptr<LineCounter> CreateCounter() const = 0;
};


class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void Log(std::string& message) = 0;
};


class LoggerFactory {
public:
    std::unique_ptr<ILogger> CreateLogger(int type) const;
};