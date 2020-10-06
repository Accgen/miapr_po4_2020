
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	system("color f0");
	int a = 1,
		b = 9,
		en = 4, //���������� ������ ���
		n = 30, //���������� ��������, �� ������� ������������ ��������
		predict = 15; //���������� ��������, �� ������� ������������ ���������������

	double d = 0.5,
		Em = 0.01, //����������� ������������������ ������ ����
		E, //��������� ������������������ ������
		T = 1; //����� ��������� ����

	double* W = new double[en]; //������� ������������
	for (int i = 0; i < en; i++) { //������ ��������� ������� ������� ������������
		W[i] = static_cast <double> (rand()) / (static_cast <double>(RAND_MAX / 2));
	}

	double* etalon = new double[n + predict]; //��������� �������� y
	for (int i = 0; i < n + predict; i++) { //��������� ��������� ��������
		double step = 0.1, //���
			x = step * i;
		etalon[i] = a * sin(b * x) + d;
	}

	do {
		double y1, //�������� �������� ��������� ����
			A = 0.005; //�������� ��������
		E = 0;

		for (int i = 0; i < n - en; i++) {
			y1 = 0;

			for (int j = 0; j < en; j++) { //������� �������� ���������� ����
				y1 += W[j] * etalon[i + j];
			}
			y1 -= T;

			for (int j = 0; j < en; j++) { //��������� ������� �������������
				W[j] -= A * (y1 - etalon[i + en]) * etalon[i + j];
			}

			T += A * (y1 - etalon[i + en]); //��������� ������ ��������� ����
			E += 0.5 * pow(y1 - etalon[i + en], 2); //������ ��������� ������������������ ������

		}
	} while (E > Em);

	cout << "���������� ��������" << endl;
	cout << setw(27) << left << "��������� ��������" << setw(23) << left << "���������� ��������" << "����������" << endl;
	double* predicated_values = new double[n + predict];

	for (int i = 0; i < n; i++) {
		predicated_values[i] = 0;
		for (int j = 0; j < en; j++) {
			predicated_values[i] += W[j] * etalon[j + i ]; //���������� �������� � ���������� ��������
		}
		predicated_values[i] -= T;

		cout << "y[" << i << "] = " << setw(20) << left << etalon[i] << setw(23) << left;
		cout << predicated_values[i] << etalon[i] - predicated_values[i] << endl;
	}

	cout << endl << "���������� ���������������" << endl;
	cout << setw(28) << left << "��������� ��������" << setw(23) << left << "���������� ��������" << "����������" << endl;

	for (int i = 0; i < predict; i++) {
		predicated_values[i + n] = 0;
		for (int j = 0; j < en; j++) {
			//�������������� ��������
			predicated_values[i + n] += W[j] * etalon[n - en + j + i];
		}
		predicated_values[i + n] += T;

		cout << "y[" << n + i << "] = " << setw(20) << left << etalon[i + n] << setw(23) << left;
		cout << predicated_values[i + n] << etalon[i + n] - predicated_values[i + n] << endl;
	}

	delete[]etalon;
	delete[]predicated_values;
	delete[]W;
	return 0;
}
