// AverageColorConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <boost/program_options.hpp>
#include <AverageColor.h>

namespace po = boost::program_options;

int _tmain(int argc, _TCHAR* argv[])
{

    po::options_description desc("Options");
    desc.add_options()
        ("help,h", "print help message")
        ("input,i", po::wvalue<std::wstring>(), "input filename")
        ;
    
    po::positional_options_description positionalOptions;     
    positionalOptions.add("input", 1);

    po::variables_map vm;

    po::store(po::wcommand_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);
    

    if (vm.count("help") || !vm.count("input")) {
        std::cout << "Find the average color of an image file." << std::endl << std::endl;
        std::cout << "Usage: AverageColor [-h] [[-i] filename]" << std::endl << std::endl;
        std::cout << desc << std::endl;
        return 1;
    }
    
    po::notify(vm);
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    DWORD averageColor;
    HRESULT hr = AverageColor(vm["input"].as< std::wstring>().c_str(), averageColor);

    if (SUCCEEDED(hr))
    {
        std::cout << "0x" << std::hex << std::setw(6) << std::setfill('0') << averageColor << std::endl;
    }
    else
    {
        std::cout << "Failed: 0x" << std::hex << hr << std::endl;
    }

    CoUninitialize();
    return 0;
}
