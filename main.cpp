#include <stdio.h>
#include <iostream>
#include <ctime>
#include <fstream>
/*#include <stdlib.h>
#include <iomanip>*/

//������ �� 104 �������...

using namespace std;

int NUM_VERTICES;           // ����� ������ � �����
const int INF = 10000; // �������� �����, ������������ �������������

int** f;  // f[i][j] - �����, ������� �� ������� i � j
int** c;  // c[i][j] - ������������ �������� ������, ��������� ���� �� ����� (i,j)

									// ����� ��������������� ����������, ������������ �������� FindPath - ������ � ������
int* Flow;  // Flow - �������� ������ ����� ������ ������� �� ������ ���� ������
int* Link;  // Link[i] ������ ����� ���������� ������ �� ���� i -> �����
int* Queue; // �������
int QP, QC;              // QP - ��������� ������ ������� � QC - ����� ��-��� � �������

// ����� ����, �� �������� �������� ������� ����� ���������� ������ ����� � ������
// ������� ���� ���� �� ������ � ����, �� �������� ��� ����� ������� �����,
// ������ ����������� ������ (i,j) ������ c[i][j] - f[i][j]

int FindPath(int source, int target) // source - �����, target - ����
{
	QP = 0; QC = 1; Queue[0] = source;
	Link[target] = -1;
	int CurVertex;
	for (int i = 0; i < NUM_VERTICES; ++i)
		Flow[i] = 0;
	Flow[source] = INF;
	while (Link[target] == -1 && QP < QC)
	{
		CurVertex = Queue[QP];
		for (int i = 0; i < NUM_VERTICES; i++)
			if ((c[CurVertex][i] - f[CurVertex][i]) > 0 && Flow[i] == 0)
			{
				Queue[QC] = i;
				QC++;
				Link[i] = CurVertex;
				if (c[CurVertex][i] - f[CurVertex][i] < Flow[CurVertex])
					Flow[i] = c[CurVertex][i];
				else
					Flow[i] = Flow[CurVertex];
			}
		QP++;

	}

	if (Link[target] == -1) return 0;
	CurVertex = target;
	while (CurVertex != source)
	{
		f[Link[CurVertex]][CurVertex] += Flow[target];
		CurVertex = Link[CurVertex];
	}
	return Flow[target];
}

// �������� ������� ������ ������������� ������
int MaxFlow(int source, int target) // source - �����, target - ����
{
	for (int i = 0; i < NUM_VERTICES; ++i)
	{
		for (int j = 0; j < NUM_VERTICES; ++j)
		{
			f[i][j] = 0;
		}
	}
	int MaxFlow = 0;
	int AddFlow;
	do
	{
		AddFlow = FindPath(source, target);
		MaxFlow += AddFlow;
	} while (AddFlow > 0);
	return MaxFlow;
}

int main()
{
	int source, target, e;
	cout << "Enter NUM_VERTICES - ";
	cin >> NUM_VERTICES;

	cout << "source - ";
	cin >> source;
	cout << "target - ";
	cin >> target;
    cout << "if you want to use text file enter 0, if you want to enter items manually enter 1" << endl;
    cin >> e;

	f = new int*[NUM_VERTICES];
	c = new int*[NUM_VERTICES];
	for (int i = 0; i < NUM_VERTICES; ++i)
	{
		f[i] = new int[NUM_VERTICES];
		c[i] = new int[NUM_VERTICES];
	}

if(e==0){
    ifstream A; //������ �������� ����!
    A.open(C:\Users\������\Documents\������\���������\C++\������ � �������); //����� ���������� ����� ������ �� ��������� ���� �� ���������� (D:\\sites\\accounts.txt)
  if(A){
    for (int i = 0; i < NUM_VERTICES; ++i){
		for (int j = 0; j < NUM_VERTICES; ++j){
    while(!A.eof()){
        A >> c[i][j];
        }
        A.close();
            }
    }
  }
    else{
        coot << "Text file doesn't exist" << endl;
        }
}
    else{
	for (int i = 0; i < NUM_VERTICES; ++i)
		for (int j = 0; j < NUM_VERTICES; ++j)
			c[i][j]=0;

			int numb, i,j;
			cout << endl << "Enter the elements in the following order:'i'->'j'->'numb'(c[i][j]=numb)." << endl << "When will you finish, enter '0->0->0'." << endl;
			cin >> i >> j;
			cout << "c[" << i << "][" << j << "]=";
            cin >> numb;

			while(numb!=0){
              c[i][j]=numb;
                cin >> i >> j;
                cout << "c[" << i << "][" << j << "]=";
                cin >> numb;

			}
}


	Flow = new int[NUM_VERTICES];
	Link = new int[NUM_VERTICES];
	Queue = new int[NUM_VERTICES];

	unsigned int start_time=clock();

	int maxflow=MaxFlow(source, target);

	unsigned int end_time=clock();


	cout << "MaxFlow = " << maxflow << "; time = " << end_time-start_time << endl;

	delete[] f;
	delete[] c;
	delete[] Flow;
	delete[] Link;
	delete[] Queue;
	return 0;
}
