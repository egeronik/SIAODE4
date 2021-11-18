#include "BINWORK.h"


/// <summary>
/// Создание бинарного файла на базе текстового
/// </summary>
/// <param name="nametf">Имя текстового файла</param>
/// <param name="namebf">Имя бинарного файла который будет создан</param>
/// <returns></returns>
int CreateBinFile(string nametf, string namebf) {

	ifstream itf(nametf);
	if (itf) {
		fstream obf(namebf, ios::out | ios::binary | ios::trunc);
		record r;
		int len = sizeof(record);
		while (!itf.eof()) {
			itf >> r.key;
			itf.get();
			itf.getline(r.data, len, '\n');
			obf.write((char*)&r, sizeof(record));
		}
		itf.close();
		obf.close();
		return 0;
	}
	return 1;
}
/// <summary>
/// Парсинг бинарного файла
/// </summary>
/// <param name="namebf">Имя файла</param>
/// <returns>Вектор всей информации из бинарника</returns>
vector<record> outBinFile(string namebf) {
	vector<record> ans;
	fstream obf(namebf, ios::in | ios::binary);
	if (obf.is_open()) {
		record r;
		int len = sizeof(r);
		obf.read((char*)&r, sizeof(r));
		while (!obf.eof()) {
			ans.push_back(r);
			obf.read((char*)&r, sizeof(record));
		}
		obf.close();
		return ans;
	}
	return ans;
}

/// <summary>
/// Чтение одной записи из бинарника
/// </summary>
/// <param name="namebf">Имя файла</param>
/// <param name="pos">Номер строки начиная с 0</param>
/// <returns>Запись</returns>
record readRecordFromBin(string namebf, int pos) {
	fstream obf(namebf, ios::in | ios::binary);
	if (obf.is_open()) {
		record r;
		int len = sizeof(r);
		obf.seekg((int)len * pos, SEEK_SET);
		if (obf.eof()) {
			cout << "EOF!";
			return r;
		}
		obf.read((char*)&r, sizeof(r));
		obf.close();
		return r;
	}
}

/// <summary>
/// Удаление записи
/// </summary>
/// <param name="namebf">Имя файла</param>
/// <param name="pos">Позиция записи начиная с 0</param>
void deleteRecord(string namebf, int pos) {
	fstream obf(namebf, ios::in | ios::binary);
	vector<record> tmp;
	if (obf.is_open()) {
		record r;
		int len = sizeof(r);
		int i = 0;
		obf.read((char*)&r, sizeof(r));
		while (!obf.eof()) {
			if (i != pos) {
				tmp.push_back(r);

			}
			i++;
			obf.read((char*)&r, sizeof(r));
		}
		obf.close();
		obf.open(namebf, ios::trunc | ios::binary | ios::out);
		obf.seekg(0, SEEK_SET);
		for (int i = 0; i < tmp.size(); ++i) {
			obf.write((char*)&tmp[i], sizeof(record));
		}
		
	}

}

