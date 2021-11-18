#pragma once
#ifndef BINWORK
#define BINWORK
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


struct record {
	int key = 0;
	char data[50] = "";
};

int CreateBinFile(string nametf, string namebf);
vector<record> outBinFile(string namebf);
record readRecordFromBin(string namebf, int pos);
void deleteRecord(string namebf, int pos);
#endif // !BINWORK
