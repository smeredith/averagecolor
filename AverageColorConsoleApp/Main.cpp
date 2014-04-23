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

    // These are the options that need help descriptions printed.
    po::options_description normalOptions("Options");
    normalOptions.add_options()
        ("help,h", "print help message")
        ("version,v", "print version")
        ;

    // These are positional options that do not need help descriptions printed.
    po::options_description hiddenOptions("Options");
    hiddenOptions.add_options()
        ("input", po::wvalue<std::wstring>(), "input filename")
        ;

    po::positional_options_description positionalOptions;
    positionalOptions.add("input", 1);

    // The full list of options used for parsing the command line.
    po::options_description allOptions("Options");
    allOptions.add(normalOptions).add(hiddenOptions);

    po::variables_map vm;

    try
    {
        po::store(po::wcommand_line_parser(argc, argv).options(allOptions).positional(positionalOptions).run(), vm);
    }
    catch(po::error& e)
    {
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        std::cout << normalOptions << std::endl;
        return 1;
    }

    if (vm.count("version"))
    {
        std::cout << "averagecolor version 1.0" << std::endl;
        return 2;
    }

    if (vm.count("help") || !vm.count("input"))
    {
        std::cout << "Find the average color of an image file." << std::endl << std::endl;
        std::cout << "Usage: averagecolor [-hv] filename" << std::endl << std::endl;
        std::cout << normalOptions << std::endl;
        return 3;
    }
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    DWORD averageColor;
    HRESULT hr = AverageColor(vm["input"].as< std::wstring>().c_str(), averageColor);

    if (SUCCEEDED(hr))
    {
        std::cout << "0x" << std::hex << std::setw(6) << std::setfill('0') << averageColor << std::endl;
    }
    else
    {
        std::cout << "Error: 0x" << std::hex << hr << std::endl;
    }

    CoUninitialize();
    return 0;
}
