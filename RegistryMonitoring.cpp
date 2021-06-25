#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
    DWORD  dwFilter = REG_NOTIFY_CHANGE_NAME |
        REG_NOTIFY_CHANGE_ATTRIBUTES |
        REG_NOTIFY_CHANGE_LAST_SET |
        REG_NOTIFY_CHANGE_SECURITY;

    HKEY pHresult = 0;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Test\\Product\\NewOne", 0, KEY_NOTIFY | KEY_CREATE_SUB_KEY | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY, &pHresult) != ERROR_SUCCESS) {
        std::cout << "FAIL IN OPEN SOFTWARE" << std::endl;
    }
    std::cout << " OPENED SOFTWARE\\Test\\Product\\NewOne" << std::endl;

    while (1)
    {
        HANDLE hevent = CreateEvent(NULL, FALSE, TRUE, NULL);
        if (RegNotifyChangeKeyValue(pHresult, TRUE, dwFilter, hevent, TRUE) != ERROR_SUCCESS)
        {
            std::cout << "NOTIFICATION FAILED " << std::endl;
        }

        DWORD dwret = WaitForSingleObject(hevent, 2000);
        if (dwret == WAIT_TIMEOUT)
        {
            std::cout << " TIMEOUT " << std::endl;
        }
        else if (dwret == WAIT_FAILED)
        {
            //
        }
        else
        {
            std::cout << "Change Occured" << std::endl;
        }

        //Sleep(2000);
    }
    RegCloseKey(pHresult);
}