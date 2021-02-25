#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

// ������ ͷ�ļ���ֻ��˵��
class WorkerManager
{
public:
	// ���캯��
	WorkerManager();

	// չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	// ��¼ְ������
	int m_EmpNum;

	// ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	// �ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;

	 // ͳ���ļ�������
	int get_EmpNum();

	// ��ʼ��Ա��
	void init_Emp();

	// ��ʾԱ��
	void Show_Emp();

	// ɾ��Ա��
	void Del_Emp();

	// �޸�Ա��
	void Mod_Emp();

	// ����Ա��
	void Find_Emp();

	// ���ձ������
	void Sort_Emp();

	// �ж�Ա���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int IsExist(int id);

	// ����ļ�
	void Clean_File();

	// ��������
	~WorkerManager();
};