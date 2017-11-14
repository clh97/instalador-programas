#pragma once
#include <iostream>
#include <Windows.h>
#include <sstream>

using namespace std;

class programa
{
public:
	string Nome;
	string Diretorio;
	string Argumentos;
	string Versao;
	bool instalar();

private:
	PROCESS_INFORMATION createProcess(string pszPath, string pszArguments);
	string ReplaceAll(string str, const string& from, const string& to);
	wstring widen(const string& str);
	wstring s2ws(const string& s);
	
};

