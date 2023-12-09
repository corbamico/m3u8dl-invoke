#include <iostream>
#include <windows.h>
#include <vector>

void change_directory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string exeDirectory = std::string(buffer);
    size_t pos = exeDirectory.find_last_of("\\/");
    exeDirectory = exeDirectory.substr(0, pos);
    SetCurrentDirectoryA(exeDirectory.c_str());
    //std::cout << "directory as :" << exeDirectory << std::endl;
}

int main(int argc, char *argv[])
{
    // SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
    if (argc != 2)
    {
        std::cout << "usage: m3u8dl-invoke.exe m3u8dl://......" << std::endl;
        return 1;
    }
    std::string encodedString = std::string(argv[1]).substr(9);

    if (encodedString.back() == '/')
    {
        encodedString.pop_back();
    }
    DWORD dwDecodedLength = 0;
    if (!CryptStringToBinaryA(encodedString.c_str(), encodedString.length(), CRYPT_STRING_BASE64, NULL, &dwDecodedLength, NULL, NULL))
    {
        std::cout << "Error code: " << GetLastError() << std::endl;
        return 1;
    }
    std::vector<BYTE> decodedBytes(dwDecodedLength);

    if (!CryptStringToBinaryA(encodedString.c_str(), 0, CRYPT_STRING_BASE64, &decodedBytes[0], &dwDecodedLength, NULL, NULL))
    {
        std::cout << "Error code: " << GetLastError() << std::endl;
        return 1;
    }
    // decodedString.resize(dwDecodedLength);
    std::string decodedString = std::string(reinterpret_cast<char *>(&decodedBytes[0]), dwDecodedLength);
    std::cout << "N_m3u8DL-re.exe " << decodedString << std::endl;

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Reuse stdin, stdout 
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    si.hStdError = GetStdHandle(STD_OUTPUT_HANDLE);
    // si.wShowWindow = SW_HIDE;

    decodedString = std::string("N_m3u8DL-re.exe ") + decodedString;
    change_directory();
    if (!CreateProcessA("N_m3u8DL-re.exe", (LPSTR)decodedString.c_str(), NULL, NULL, TRUE, 0 /*CREATE_NO_WINDOW*/, NULL, NULL, &si, &pi))
    {
        std::cout << "Error code: " << GetLastError() << std::endl;
        return 1;
    }
    return 0;
}
