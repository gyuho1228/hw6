#include<iostream>
#include<fstream>

using namespace std;

float getLength(int eumpyo) {
	float T = 0;
	if (eumpyo == 4) T = 1.0 / 2;
	else if (eumpyo == 8) T = 0.5 / 2; // 8분음표는 0.5초
	else if (eumpyo == 16) T = 0.25 / 2; // 16분음표는 0.25초
	return T;
}
float getfrequency(int eumpyo) {
	float f = 0;
	if (eumpyo == 'C') f = 261;
	else if (eumpyo == 'D') f = 294; // D
	else if (eumpyo == 'E') f = 330; // E
	else if (eumpyo == 'F') f = 349; // F
	else if (eumpyo == 'G') f = 392; // G
	else if (eumpyo == 'A') f = 440; // A
	else if (eumpyo == 'B') f = 494; // B
	else  f = 523; // C
	return f;
}
float getAmplitude(int eumpyo) {
	float a = 0;
	a = eumpyo * 1000;
	return a;
}


int main() {
	ifstream xx("my.wav", ios::binary | ios::in);
	if (!xx) return 999;  // if the file is not found
	char header[44];
	// Sprint 1
	xx.read(header, 44);
	int* sampleRate = (int*)(header + 24);
	cout << "   sampleRate = " << *sampleRate << endl;
	short* n;   n = (short*)(header + 22);  cout << *n << endl; // numChannels
	int* fs;   fs = (int*)(header + 24);  cout << *fs << endl; // sampleRate
	int* b;   b = (int*)(header + 28);  cout << *b << endl;  //  byteRate



	// Sprint 3
	int N = fs[0] * 20; // samples for 10 seconds
	short* data;
	data = new short[N*2]; // allocate memory for 10 seconds mono
	*n = 2;  // serteo 
	const float pi = 3.141592;
	float dt = 1. / fs[0];

	//데이터 읽기
	ifstream zz("piece.txt");
	ifstream zz1("piece1.txt");
	int gaesu, eu, ss;
	char hh;
	float f, a, T;
	float f1, a1, T1;
	zz >> gaesu; // 음표가 몇 개인지 읽기
	int j = 0;
	for (int i = 0; i < gaesu; i++) {
		zz >> eu >> hh >> ss;  // eu ss는 int이고, hh는 char
		f = getfrequency(hh);    // 주파수가 return 되는 함수
		a = getAmplitude(ss);    // 진폭이 return되는 함수
		T = getLength(eu);       // 시간이 return되는 함수
		// 해당 시간만큼 a * sin(2*pi*f*t)를 샘플수(fs[0]*T)만큼 계산하여 data에 넣고,
		// 나의 wave file에 만들어진 sample 개수만큼 write한다.

		for (float t = 0.0; t < T; t += dt, j++) {
			data[2 * j] = (short)(a * sin(2.0 * pi * f * t));   // a 진폭, f 주파수, N 샘플수(1초는 fs[0] samples, 44100 또는 8000)
		}
	}
	zz1 >> gaesu; // 음표가 몇 개인지 읽기
	int k = 0;
	for (int i = 0; i < gaesu; i++) {
		//반주부분
		zz1 >> eu >> hh >> ss;  // eu ss는 int이고, hh는 char
		f1 = getfrequency(hh);    // 주파수가 return 되는 함수
		a1 = getAmplitude(ss);    // 진폭이 return되는 함수
		T1 = getLength(eu);

		for (float t = 0.0; t < T1; t += dt, k++) {
			data[2 * k + 1] = (short)(a1 * sin(2.0 * pi * f1 * t));   // a 진폭, f 주파수, N 샘플수(1초는 fs[0] samples, 44100 또는 8000)
		}
	}

	// 나의 wave file 닫기



	ofstream yy("my6.wav", ios::binary | ios::out);
	if (!yy) return 666;  // 만일 파일이 열리지 않으면 프로그램을 끝낸다. 
	yy.write(header, 44 * sizeof(char)); // 헤더를 쓴다. 
	yy.write((char*)data, N * sizeof(short));    // 헤더에 이어서 10초 분량 쓴다.
	yy.close();
	return 1;
}
