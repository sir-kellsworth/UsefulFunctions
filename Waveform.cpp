/**********************************************************************
 *
 * Filename:    Waveform.cpp
 * 
 * Description: Implementations of Waveform methods
 *
 * Notes: these arent by any means origional. I just created these
 *	functions from descriptions from wikipidia.
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include "Waveform.h"

//just transforms it into the frequency domain. you need to call 
//get frequencies to get a list of frequencies
void useful::fft(std::vector<std::complex<double>> &array){
	int N = array.size();
	if(N <= 1)
		return;

	//separate the array to even and odd parts
	std::vector<std::complex<double>> even(N/2,0);
	std::vector<std::complex<double>> odd(N/2,0);
	for(int i = 0; i < N/2; i++){
		even[i] = array[i*2];
		odd[i] = array[i*2 + 1];
	}

	fft(even);
	fft(odd);

	//combine
	for(int i = 0; i < N/2; i++){
		std::complex<double> t = std::polar(1.0, -2.0 * PI * i / N) * odd[i];
		array[i] = even[i] + t;
		array[i + N/2] = even[i] - t;
	}
}

void useful::ifft(std::vector<std::complex<double>> &array, int samplingRate){
	for(int i = 0; i < array.size(); i++){
		array[i] *= std::conj(array[i]);
	}

	fft(array);

	for(int i = 0; i < array.size(); i++){
		array[i] *= std::conj(array[i]);
		array[i] /= array.size();
	}
}

std::vector<double> useful::getFrequencies(std::vector<std::complex<double>> &sineSamples,double Fs,int N,double accuracy){
	std::vector<double> frequencies(N/2,0);
	std::vector<double> y(N/2,0);
	for(int i = 0; i < y.size(); i++){
		frequencies[i] = ((Fs / N) * i);
		y[i] = std::abs(sineSamples[i]) / Fs;
		
	}

	std::vector<double> foundFrequencies;
	for(int i = 0; i < y.size(); i++){
		if(y[i] > 0.4){
			bool farEnough = true;
			for(double frequency : foundFrequencies){
				if(fabs(frequency - frequencies[i]) < accuracy){
					farEnough = false;
				}
			}
			if(farEnough){
				foundFrequencies.push_back(frequencies[i]);
			}
		}
	}

	return foundFrequencies;
}
