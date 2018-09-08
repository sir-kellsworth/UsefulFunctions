/**********************************************************************
 *
 * Filename:    Waveform.cpp
 * 
 * Description: Implementations of Waveform methods
 *
 * Notes:
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#include "Waveform.h"

void fft(std::vector<std::complex<double>> &array, int samplingRate){
	//I think the fft is the sum of signal multiplied by the complex congugate...
	for(int i = 0; i < array.size(); i++){
		double abs = std::abs(array[i]);
		array[i].imag = std::arg(array[i]);
		array[i].real = abs;
	}

	for(int i = 0; i < array.size(); i++){
		array[i] *= samplingRate;
	}
}

void ifft(std::vector<std::complex<double>> &array, int samplingRate){
	
}
