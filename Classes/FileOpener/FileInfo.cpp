#include "FileInfo.h"

FileInfo::FileInfo(const vector<string>& _lines)
{
    if(_lines.size() > 2) return;
    for (const string& _line : _lines)
    {
        if(!ParseLine(_line))
            filePath = _line;
    }
}

string FileInfo::GetFilePath() const
{
    return filePath;
}

string FileInfo::GetLineToChange() const
{
    return lineToChange;
}

string FileInfo::GetValueToChange() const
{
    return valueToChange;
}

bool FileInfo::ParseLine(const string& _line)
{
    const int _index = _line.find('=');
    if( _index < 0) return false;

    lineToChange = _line.substr(0,_index);
    valueToChange = _line.substr(_index +1, _line.length()-1);
    return true;
}
