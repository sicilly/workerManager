#include"workerManager.h"

WorkerManager::WorkerManager()
{
	// 1. �ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //���ļ�
	if (!ifs.is_open())
	{
		 cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2. �ļ����� ������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3. ���ļ����� ��������
	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	// ����һ�����飬����Ϊm_EmpNum
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	// ���ļ��е����ݴ浽������
	this->init_Emp();

	//// ����
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << this->m_EmpArray[i]->m_Id << " "
	//		<< this->m_EmpArray[i]->m_Name << " "
	//		<< this->m_EmpArray[i]->m_DeptId << endl;

	//}
	
}


// չʾ�˵���ʵ��
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

// ���ְ��
void WorkerManager::Add_Emp()
{
	cout << "���������ְ������" << endl;
	int addNum=0; // �����û����������
	cin >> addNum;
	if (addNum > 0)
	{
		// ���
		// ��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		// �����¿ռ�
		Worker** newSpace = new Worker* [newSize];

		// ��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) 
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		// �������������
		for (int i = 0; i < addNum; i++)
		{
			int id;  // ְ�����
			string name;  // ְ������
			int dSelect;  // ����ѡ��

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;

			cout << "�������" << i+1 <<"����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL; // ְ��ָ�� Ĭ��ָ���
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			// ��������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;

		}

		// �ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		// �����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		// �����µ�ְ������
		this->m_EmpNum = newSize;
		// �����ļ���Ϊ�յı�־��
		this->m_FileIsEmpty = false;
		// ��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum<< "����Ա����"<< endl;

		// �������ݵ��ļ���
		this->save();

	}
	else {
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");
}

// �����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); // д�ļ�
	for (int i = 0; i < this->m_EmpNum;i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << " "
			<< endl;
	}
	// �ر��ļ�
	ofs.close();
}

// ͳ���ļ��е�����
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); // ���ļ�
	int id;
	string name;
	int dId;

	int num = 0;

	// һ��һ�ж�
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ����������
		num++;
	}
	return num;
}

// ��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  // ���ļ�
	int id;
	string name;
	int dId;
	int index = 0;
	// һ��һ�ж�
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)  //��ͨԱ��
		{
			worker = new Employee(id,name,dId);
		}
		else if(dId==2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	// �ر��ļ�
	ifs.close();
}

// ��ʾԱ��
void WorkerManager::Show_Emp()
{
	// �ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

// ɾ��Ա��
void WorkerManager::Del_Emp() 
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		// ����ְ�����ɾ��
		cout << "��������Ҫɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)  // ְ�����ڲ���Ҫɾ����indexλ�õ�����
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--; // ���������м�¼��Ա����
			// ����ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "δ�ҵ���ְ�����޷�ɾ��" << endl;
		}
	}
	system("pause");
	system("cls");
}

// �ж�Ա���Ƿ���ڣ�������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id) 
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			// �ҵ�ְ��
			index = i;

			break;
		}
	}
	return index;
}

// �޸�Ա��
void WorkerManager::Mod_Emp() 
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		// ����ְ������޸�
		cout << "��������Ҫ�޸�ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)  // ְ������
		{
			// ���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��Ա������������ְ���ţ�" << endl;
			cin >> newId;
			cout << "��������������" << endl;
			cin >> newName;
			cout << "��ѡ���¸�λ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL; // ְ��ָ�� Ĭ��ָ���
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}
			// �������ݵ�������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << endl;

			//���浽�ļ���
			this->save();
		}
		else {
			cout << "δ�ҵ���ְ��,�޷��޸�" << endl;
		}
	}
	system("pause");
	system("cls");
}

// ����Ա��
void WorkerManager::Find_Emp() 
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)  // ����Ų�
		{
			cout << "��������ҵ�ְ����ţ�" << endl;
			int id = 0;
			cin >> id;

			int ret = this->IsExist(id);
			if (ret != -1)  // �ҵ�ְ��
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else {
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2) {  //��������
			cout << "��������ҵ�ְ��������" << endl;
			string name;
			cin >> name;

			// �����Ƿ���ҵ��ı�־ Ĭ��δ�ҵ�
			bool flag = false;

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					flag = true; // �ҵ��ı�־
					cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag==false) 
			{
				cout << "���޴���" << endl;
			}
		}
		else {
			cout << "����ѡ����������������" << endl;
		}
	}
	system("pause");
	system("cls");
}

// ���ձ������
void WorkerManager::Sort_Emp() 
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "��ѡ������ķ�ʽ��" << endl;
		cout << "1.��ְ���������" << endl;
		cout << "2.��ְ����Ž���" << endl;
		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;  // ��һ���϶���С����ֵ���±���0���ڶ����϶���С����ֵ�±���1...
			for (int j = i+1; j < this->m_EmpNum; j++) 
			{
				if (select == 1)   // ����
				{
					// �����Ƿ��и�С����
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) 
					{
						minOrMax = j;  // �����±�
					}
				}
				else  // ����
				{
					// �����Ƿ��и������
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;  // �����±�
					}
				}
			}

			//�ж�һ��ʼ�϶�����Сֵ�����ֵ �ǲ��� ��������Сֵ�����ֵ
			if (i != minOrMax) {
				// ����Ԫ��
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ���������Ϊ��" << endl;

		// ���浽�ļ�
		this->save();
		// ��ʾ���
		this->Show_Emp();
	}
}

// ����ļ�
void WorkerManager::Clean_File() 
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			// ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			// ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;

			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

// ��������
WorkerManager::~WorkerManager()
{
	//���������ֶ��ͷ�
	if (this->m_EmpArray != NULL)
	{
		// ÿһ��Ԫ���ÿ�
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		// �����ÿ�
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}