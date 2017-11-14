#include "config.h"

// lê int do arquivo .ini e transforma em BOOL
BOOL config::get_info(string name)
{
	return (GetPrivateProfileInt((LPCSTR)"CONFIGURATIONS", (LPCSTR)name.c_str(), INSTALL, (LPCSTR)base_path.c_str()) == 1);
}

// lê quais programas vao ser instalados e retorna em forma de struct
config::configurations config::configure()
{
	config cfg;
	config::configurations configurations;

	configurations.chrome = cfg.get_info("chrome");
	configurations.firefox = cfg.get_info("firefox");
	configurations.skype = cfg.get_info("skype");
	configurations.reader = cfg.get_info("reader");
	configurations.vlc = cfg.get_info("vlc");
	configurations.mse = cfg.get_info("mse");
	configurations.copy_tv = cfg.get_info("teamviewer");
	configurations.drivereasy = cfg.get_info("drivereasy");
	configurations.winrar = cfg.get_info("winrar");
	configurations.java = cfg.get_info("java");
	memset(&cfg, NULL, 0);

	return configurations;
}

// pega o diretório do executável
string config::getexepath()
{
	//char* cwd = _getcwd(0, 0); // **** microsoft specific ****
	//std::string working_directory(cwd);
	//std::free(cwd);
	//return working_directory;

	/*char buffer[MAX_PATH];
	GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);*/

	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
BOOL config::is64()
{
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			cout << "> Erro na hora de definir se e x64 ou x86. x86 foi definido como padrao." << endl;
		}
	}
	return bIsWow64;
}

string config::getdesktop()
{
	/*wchar_t path[MAX_PATH];
	if (SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_DESKTOPDIRECTORY, FALSE))
		return CW2A(path);
	else
		return string("ERROR");*/

	ULONG ulDataType;
	HKEY hKey;
	DWORD dwToRead = 100;
	static char strPath[100];
	char strKey[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders";
 
	RegOpenKeyEx(HKEY_CURRENT_USER,strKey,0,KEY_READ,&hKey);
	RegQueryValueEx(hKey,"Desktop",NULL,&ulDataType,(LPBYTE)strPath,&dwToRead);
	strPath[dwToRead] = '\0';
	RegCloseKey(hKey);
	return (string)strPath;
}