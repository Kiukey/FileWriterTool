#include "CFileOpener.h"
#include <iostream>

CFileOpener::CFileOpener()
{
}

bool CFileOpener::OpenFile(const string& _path)
{
    filePath = _path;
    const errno_t _error = fopen_s(&file,_path.c_str(),"r+");
    return _error == 0;
}

bool CFileOpener::ReadFile(string& _ret) const
{
    const int _fileSize = GetFileSize();
    char* _buffer = new char[_fileSize+1]{'\0'};
    const size_t _red = fread_s(_buffer,_fileSize,1,_fileSize,file);
    _buffer[_fileSize] = '\0';
    rewind(file);
    _ret = _buffer;
    delete[] _buffer;
    return _red > 0;
}

bool CFileOpener::CloseFile()
{
    const int _closeState = fclose(file);
    filePath = "";
    return _closeState == 0;
}

int CFileOpener::GetFileSize() const
{
    const int _error = fseek(file,0,SEEK_END);
    if(_error != 0) return 0;
    const int _toRet = ftell(file);
    rewind(file);
    return _toRet;
}

std::vector<string> CFileOpener::GetAllLines(string _fileContent) const
{
    string _toUse;
    std::vector<string> _lines = std::vector<string>();
    for (int _i = 0; _i <= _fileContent.length(); _i++)
    {
        if(_fileContent[_i] == '\n' || _fileContent[_i] == '\0')
        {
            _lines.insert(_lines.end(),_toUse);
            _toUse = "";
        }
        else
            _toUse += _fileContent[_i];
    }
    return _lines;
}

int CFileOpener::SearchLine(const string& _toSearch,std::vector<string> _lines) const
{
    for (int i = 0; i < _lines.size(); i++)
    {
        const int _found = _lines[i].find(_toSearch);
        if(_found >= 0)
            return i;
    }
    return -1;
}

void CFileOpener::ReplaceLine(const string& _file, const string& _toReplace, const string& _toReplaceWith,bool _flushFileContent)
{
    std::vector<string> _lines = GetAllLines(_file);
    const int _index = SearchLine(_toReplace, _lines);
    if(_index < 0) return;
    _lines[_index] = _toReplaceWith;
    string _toWrite;
    for(string _line : _lines)
        _toWrite += _line + "\n";
    WriteLine(0, _toWrite, _flushFileContent);
}

void CFileOpener::ReplaceLineValue(const string& _file, const string& _toReplace, const string& _newValue,bool _flushFileContent)
{
    ReplaceLine(_file,_toReplace,ChangeValue(_toReplace,_newValue),_flushFileContent);
}

void CFileOpener::WriteLine(int _charToStart, const string& _toWrite, bool _flushFileContent)
{
    if(_flushFileContent)
        freopen_s(&file,filePath.c_str(),"w+",file);
    int _error = fseek(file,_charToStart,0);
    if(_error != 0) return;
    fwrite(_toWrite.c_str(),1,_toWrite.length(),file);
}

string CFileOpener::ChangeValue(const string& _line, const string& _valueToChange)
{
    string _toRet = _line;
    const string _toAdd = "="+_valueToChange;
    const int _index = _line.find_first_of("=");
    if(_index >= 0)
        _toRet.erase(_index,_toRet.length());
    _toRet += _toAdd;
    return _toRet;
}

CFileOpener::~CFileOpener()
{
    delete file;
}





