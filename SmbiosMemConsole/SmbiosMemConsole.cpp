// SmbiosMemConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <winioctl.h>

#include "IOCTLValue.h"

#define AAEON_DEVICE L"\\\\.\\Aaeon_WdfLink"

using namespace std;

int main()
{
    cout << "HelloWorld\n";

    return 0;
}
