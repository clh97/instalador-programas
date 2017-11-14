#include "programa.h"

// instala o programa inicializando a função createProcess
bool programa::instalar()
{
	if (Nome.length() <= 0 || Diretorio.length() <= 0 || Argumentos.length() <= 0)
		return false;

	cout << "> Iniciando instalação do " << Nome.c_str() << "..." << endl;

	createProcess(Diretorio, Argumentos);
	return true;
}

// inicia o processo e espera ele fechar, retornando e printando um exitCode
PROCESS_INFORMATION programa::createProcess(string pszPath, string pszArguments)
{
	string pszCommand;
	pszCommand.append(pszPath);
	pszCommand.append(" ");
	pszCommand.append(pszArguments);

	STARTUPINFO StartInfo;
	PROCESS_INFORMATION ProcessInfo;
	DWORD exitCode = { 0 };
	int lErrorCode = 0;

	memset(&StartInfo, 0, sizeof(StartInfo));

	StartInfo.cb = sizeof(StartInfo);

	StartInfo.wShowWindow = SW_HIDE;
	StartInfo.dwFlags |= STARTF_USESHOWWINDOW;

	//ERRO ESTÁ AQUI!!!! CONVERTER PSZCOMMAND PARA LPWSTR SEM DAR ERRO :(
	//wstring stemp = wstring(pszCommand.begin(), pszCommand.end());
	//LPCWSTR sw = stemp.c_str();
	BOOL proc = CreateProcess(0, (char *)pszCommand.c_str(), 0, 0, TRUE, CREATE_NEW_PROCESS_GROUP | CREATE_NO_WINDOW, 0, 0, &StartInfo, &ProcessInfo);
	//cout << "CONVERSAO: " << CA2T(pszCommand.c_str()) << endl;

	if (proc)
	{
		lErrorCode = 0;
	}
	else
	{
		lErrorCode = GetLastError();
		cout << lErrorCode;
	}

	if (WaitForSingleObject(ProcessInfo.hProcess, INFINITE) == WAIT_FAILED)
		cout << "> WaitForSingleObject() falhou! Erro: " << lErrorCode <<  endl;

	proc = GetExitCodeProcess(ProcessInfo.hProcess, &exitCode);

	CloseHandle(ProcessInfo.hProcess);
	CloseHandle(ProcessInfo.hThread);

	if (!proc)
		cout << "> Executou o comando, mas falhou ao retornar o exitcode." << endl;
	else
		cout << "> Processo executado com sucesso. ExitCode: " << exitCode << endl;

	return ProcessInfo;
}

string programa::ReplaceAll(string str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

wstring programa::widen(const string& str)
{
	wostringstream wstm;
	const ctype<wchar_t>& ctfacet =
		use_facet< ctype<wchar_t> >(wstm.getloc());
	for (size_t i = 0; i<str.size(); ++i)
		wstm << ctfacet.widen(str[i]);
	return wstm.str();
}

wstring programa::s2ws(const string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}