#include "DoublyLinkedList.h"
#include <fstream>
#include <iostream>
#include <string>

int main(void) {
	//�t�@�C���p�X����t�@�C�����J��
	std::string filePath = "Scores.txt";
	std::ifstream file(filePath.c_str());

	//�����������t�@�C�����J���Ȃ������ꍇ�Areturn
	if (!file.is_open()) {
		return 0;
	}

	doublyLinkedList<scoreData> list;
	std::string line = {};

	//��s����List�ɒǉ�
	while (std::getline(file, line)) {
		if (line.empty()) continue;  //�����󂾂����ꍇ�A���s

		//�ŏ��̃^�u�L�[���͂̈ʒu������
		std::size_t tab = line.find('\t');

		// tab���Ȃ��ꍇ�A�X�L�b�v
		if (tab == std::string::npos) continue;

		scoreData data = {};
		
		//�����������ꍇ�AinputScore�𐔎��ɕϊ�
		try {
			data.score = std::stoi(line.substr(0,tab));
		}
		// �����ł͂Ȃ��ꍇ�A�X�L�b�v
		catch (...) {
			continue;
		}
		data.userName = line.substr(tab + 1);

		// �����Ƀm�[�h��ǉ�
		list.insertData(list.cend(), data);
	}

	//�t�@�C�������
	file.close();

	
	//���X�g�̓��e���o��
	for (doublyLinkedList<scoreData>::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << (*it).score << '\t' << (*it).userName << std::endl;
	}

	return 0;
}