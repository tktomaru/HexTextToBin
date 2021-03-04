// HexTextToBin.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "tchar.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <atlstr.h>
#include <wchar.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int c;
	int x;
	int outBin;
	FILE* fin = NULL;
	FILE* fout = NULL;
	TCHAR fullPathName[MAX_PATH];
	char table[] = "0123456789ABCDEF";

	if (1 >= argc) {
		std::wcout << L"引数エラー";
		return -1;
	}

	_TCHAR* argfile = argv[1];
	CString filename = CString(argfile);
	errno_t error;

	std::wcout.imbue(std::locale(""));
	std::wcout << L"ファイル：" << filename.GetString() << std::endl;

	DWORD sz;
	LPCTSTR getFullFileName = filename.GetString();
	sz = GetFullPathName(getFullFileName, sizeof(fullPathName) / sizeof(TCHAR), fullPathName, NULL);

	if (sizeof(fullPathName) / sizeof(TCHAR) < sz) {
		std::wcout << L"バッファの文字数が足りません" << std::endl;
		return -1;
	}
	else {
		std::wcout << L"フルパス" << fullPathName << std::endl;
	}

	error = _tfopen_s(&fin, fullPathName, _T("r"));

	if (error != 0) {
		std::wcout << L"ファイルを開けませんでした" << fullPathName << std::endl;
		return -1;
	}
	std::wstring  s1 = fullPathName;
	std::wstring  s2 = _T(".dat");
	std::wstring  buf = s1 + s2;
	error = _tfopen_s(&fout, buf.c_str(), _T("wb"));
	
	if (error != 0) {
		std::wcout << L"ファイルを開けませんでした" << buf.c_str() << std::endl;
		return -1;
	}
	else {
		while (EOF != (c = fgetc(fin))) {
			switch (c) {
			case '.':
				break;
			case '\n':
				break;
			default:
				// 上位
				x = strchr(table, toupper(c)) - table;
				x = x * 16;
				// 下位
				c = fgetc(fin);
				if (c == EOF) {
					break;
				}
				c = strchr(table, toupper(c)) - table;
				outBin = x + c;
				fputc(outBin, fout);
				break;
			}
			if (c == EOF) {
				break;
			}
		}
	}
	_fcloseall();
	return 0;
}
