#include <iostream>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "programa.h"
#include "config.h"

#define NOME_PASTA		"Pacote"
#define DIRETORIO_BASE	cfg.getexepath()

void firefox_file();
string diretorio;

using namespace std;

int main(int argc, char **argv)
{
	// TODO: FAZER DOWNLOAD DOS ARQUIVOS DO SERVIDOR NA PASTA PACOTE

	config cfg;
	config::configurations configs = cfg.configure();
	BOOL arch64 = cfg.is64();
	string desktop = cfg.getdesktop();

	diretorio = cfg.getexepath() + "\\" + NOME_PASTA + "\\";
	cout << "> Diretorio Base:" << diretorio.c_str() << endl;
	if (arch64)
		cout << "> Arquitetura 64 bits detectada." << endl;
	else
		cout << "> Arquitetura 32 bits detectada." << endl;

	getchar();

	if (configs.chrome)
	{
		programa chrome;
		chrome.Nome = "Google Chrome";
		chrome.Diretorio = diretorio + "chrome.exe";
		chrome.Versao = "xxx";
		chrome.Argumentos = "/silent /install";
		chrome.instalar();
	}

	if (configs.firefox)
	{
		programa firefox;
		firefox.Nome = "Mozilla Firefox";
		firefox.Diretorio = diretorio + "firefox.exe";
		firefox.Versao = "xxx";
		firefox.Argumentos = "/INI="; firefox.Argumentos.append("\"" + DIRETORIO_BASE + "\\Pacote\\mozilla.ini" + "\"");
		firefox_file();
		firefox.instalar();
	}

	if (configs.winrar)
	{
		programa winrar;
		winrar.Nome = "Winrar";
		winrar.Diretorio = diretorio + "winrar.exe";
		winrar.Versao = "xxx";
		winrar.Argumentos = "/s /v";
		winrar.instalar();
	}

	if (configs.reader)
	{
		programa reader;
		reader.Nome = "Adobe Reader";
		reader.Diretorio = diretorio + "reader.exe";
		reader.Versao = "xxx";
		reader.Argumentos = "/sAll";
		reader.instalar();
	}

	if (configs.skype)
	{
		programa skype;
		skype.Nome = "Skype";
		skype.Diretorio = diretorio + "skype.msi";
		skype.Versao = "xxx";
		skype.Argumentos = "/i /quiet /n /norestart";
		//skype.Argumentos = "/VERYSILENT /SP- /NOCANCEL /NORESTART /SUPPRESSMSGBOXES /NOLAUNCH";
		//skype.instalar();
		string run;
		run+="msiexec.exe ";
		run+=skype.Argumentos;
		cout << run.c_str() << endl;
		//wcscpy_s(run, "msiexec.exe ");
		//wcscpy_s(run, skype.Argumentos.c_str());
		ShellExecute(NULL, NULL, run.c_str(), NULL, NULL, SW_HIDE);	
		int lErrorCode = GetLastError();
		cout << lErrorCode;
	}

	if (configs.java)
	{
		programa java;
		java.Nome = "Java";
		java.Diretorio = diretorio + "java.exe";
		java.Versao = "xxx";
		java.Argumentos = "/s";
		java.instalar();
	}

	if (configs.vlc)
	{
		programa vlc;
		vlc.Nome = "VLC Media Player";
		vlc.Diretorio = diretorio + "vlc_m_p.exe";
		vlc.Versao = "xxx";
		vlc.Argumentos = "/S";
		vlc.instalar();
	}

	if (configs.mse)
	{
		programa mse;
		mse.Nome = "Microsoft Security Essentials";
		if(arch64)
			mse.Diretorio = diretorio + "mse64.exe";
		else
			mse.Diretorio = diretorio + "mse32.exe";
		mse.Versao = "xxx";
		mse.Argumentos = "/s /q /o /runwgacheck";
		mse.instalar();
	}

	if (configs.copy_tv)
	{
		programa tv;
		tv.Nome = "TeamViewer";
		tv.Versao = "xxx";
		tv.Diretorio = diretorio + "teamviewer.exe";
		string diretorio_final = desktop + "/TeamViewer.exe";
		cout << "> Copiando TeamViewer para a Area de trabalho.." << endl;
		CopyFile((LPCSTR)tv.Diretorio.c_str(), (LPCSTR)diretorio_final.c_str(), TRUE);
	}
	
	if (configs.drivereasy)
	{
		programa drivereasy;
		drivereasy.Nome = "DriverEasy";
		drivereasy.Diretorio = diretorio + "drivereasy.exe";
		drivereasy.Versao = "2.0";
		drivereasy.Argumentos = "/silent";
		drivereasy.instalar();
	}

	getchar();
	return 0;
}

// cria arquivo especifico para instalação silenciosa do firefox
void firefox_file()
{
	config cfg;
	std::ofstream outfile(diretorio + "/mozilla.ini");
	outfile.close();
	memset(&cfg, 0, 0);
}