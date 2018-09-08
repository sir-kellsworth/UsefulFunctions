/**********************************************************************
 *
 * Filename:    Waveform.h
 * 
 * Description: Defenitions of the Waveform functions
 *
 * Notes:
 *
 * 
 * Copyright (c) 2018 by Kelly Klein.  This software is placed into
 * the public domain and may be used for any purpose.  However, this
 * notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 **********************************************************************/

#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <vector>
#include <complex>

/*
	not ready yet. But eventually will have some sweet fast fourier transform and inverse transforms
*/

namespace useful{

const double PI = 3.141592653589793238460;

void fft(std::vector<std::complex<double>> &array, int samplingRate);
void ifft(std::vector<std::complex<double>> &array, int samplingRate);

};

#endif
