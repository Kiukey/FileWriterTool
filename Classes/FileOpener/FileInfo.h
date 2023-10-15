#pragma once
#include <string>
#include <vector>

using namespace  std;

struct FileInfo
{
private:
    string filePath;
    string lineToChange;
    string valueToChange;
public:
    FileInfo() : filePath(""),lineToChange(""),valueToChange(""){}
    FileInfo(const vector<string>& _lines);

    string GetFilePath() const;
    string GetLineToChange() const;
    string GetValueToChange() const;
private:
    bool ParseLine(const string& _line);
};
