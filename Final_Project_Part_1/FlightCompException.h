#pragma once
#include <string>
#include <iostream>
using namespace std;

class CFlightCompException {
public:
    virtual ~CFlightCompException() {}
    virtual void Show() const = 0;
};

class CCompStringException : public CFlightCompException {
    string msg;
public:
    explicit CCompStringException(const string& m) : msg(m) {}
    void Show() const override 
    { 
        cout << "Error: " << msg << endl;
    }
};

class CCompLimitException : public CFlightCompException {
    int maxVal;
    string context;
public:
    explicit CCompLimitException(int maxValue, const string& ctx = "")
        : maxVal(maxValue), context(ctx) 
    {
    }
    void Show() const override 
    {
        cout << "Limit error";
        if (!context.empty())
        {
            cout << " (" << context << ")";
        }
        cout << ". Max allowed: " << maxVal << endl;
    }
};

class CCompFileException : public CFlightCompException {
    string file;
    string op;
public:
    CCompFileException(const string& filename, const string& operation)
        : file(filename), op(operation) 
    {
    }
    void Show() const override 
    {
        cout << "File error: " << op << " '" << file << "'" << endl;
    }
};
