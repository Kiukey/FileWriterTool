
#include <iostream>
#include <crtdbg.h>
#include "Classes/FileOpener/CFileOpener.h"
#include "Classes/FileOpener/FileInfo.h"

int main(int argc, char* argv[])
{
    //test
    CFileOpener* _opener = new CFileOpener();
    std::string _file;
    _opener->OpenFile("Config.ini");
    _opener->ReadFile(_file);
    FileInfo _infos = FileInfo(_opener->GetAllLines(_file));
    _opener->CloseFile();

    _opener->OpenFile(_infos.GetFilePath());
    _opener->ReadFile(_file);
    _opener->ReplaceLineValue(_file,_infos.GetLineToChange(),_infos.GetValueToChange(),true);
    _opener->CloseFile();
    
    delete _opener;

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();
    return 0;
}
