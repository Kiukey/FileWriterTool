#pragma once
#include <vector>
#include <string>

using namespace std;

class CFileOpener
{
private:
    FILE* file = nullptr;
    string filePath;
public:
    CFileOpener();
    ~CFileOpener();
    bool OpenFile(const string& _path);
    bool ReadFile(string& _ret) const;
    bool CloseFile();
    int GetFileSize() const;
    std::vector<string> GetAllLines(string _fileContent) const;
    void ReplaceLine(const string& _file, const string& _toReplace, const string& _toReplaceWith, bool _flushFileContent = false);
    void ReplaceLineValue(const string& _file, const string& _toReplace, const string& _newValue, bool _flushFileContent = false);
private:
    int SearchLine(const string& _toSearch,std::vector<string> _lines) const;
    void WriteLine(int _charToStart, const string& _toWrite, bool _flushFileContent = false);
    string ChangeValue(const string& _line, const string& _valueToChange);
};



