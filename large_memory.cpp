#include <iostream>
#include <Windows.h>
#include <Commctrl.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;
HHOOK _hook;
HMENU menu;
void terminate_process(int pid);

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // get list of processes
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return 0;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return 0;
    }
    do
    {
        HANDLE hProcess;
        PROCESS_MEMORY_COUNTERS pmc;
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
        if (hProcess == NULL)
        {
            cout << pe32.szExeFile << " could not be opened" << endl;
            continue;
        }
        if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
        {
            cout << pe32.szExeFile << " has " << pmc.WorkingSetSize / 1024 << " KB of memory" << endl;
        }
        int memory_kbs = (int)(pmc.WorkingSetSize / 1024);
        // if memory is greater than 250000 MB, kill the process
        if (memory_kbs > 250000)
        {
            cout << endl << "Killing " << pe32.szExeFile << endl;
            //DWORD to INT
            int pid = pe32.th32ProcessID;
            terminate_process(pid);
        }

        CloseHandle(hProcess);
    } while (Process32Next(hProcessSnap, &pe32));
    CloseHandle(hProcessSnap);
    return 1;
}



void terminate_process(int pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL)
    {
        cout << "Could not open process" << endl;
        return;
    }
    if (!TerminateProcess(hProcess, 0))
    {
        cout << "Could not terminate process" << endl;
        return;
    }
    CloseHandle(hProcess);
}