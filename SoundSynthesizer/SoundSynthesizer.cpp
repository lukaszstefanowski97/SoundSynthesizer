// SoundSynthesizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "olcNoiseMaker.h"
using namespace std;

atomic<double> dFrequencyOutput = 0.0;

double makeNoise(double dTime) {

	double dOutput = 1.0*sin(dFrequencyOutput * 2 * 3.14159 * dTime);

	if (dOutput > 0)
		return 0.3;
	else
		return -0.3;
}


int main()
{
	
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	for (auto d : devices) wcout << "Found output device: " << d << endl;

	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	sound.SetUserFunction(makeNoise);

	double dOctaveFrequency = 110.0;
	double d12thRootOf2 = pow(2.0, 1.0 / 12.0);

	while (1) {

		bool bKeyPressed = false;
		for (int k = 0; k < 15; k++) {
			if (GetAsyncKeyState((unsigned char)("ZSXDCVGBHNJM\xbcl\xbe"[k])) & 0x8000)
			{
				dFrequencyOutput = dOctaveFrequency * pow(d12thRootOf2, k);
				bKeyPressed = true;
			}
		}
		if (!bKeyPressed)
		{
			dFrequencyOutput = 0.0;
		}
	}

    return 0;
}

