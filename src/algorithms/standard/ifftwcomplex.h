/*
 * Copyright (C) 2006-2016  Music Technology Group - Universitat Pompeu Fabra
 *
 * This file is part of Essentia
 *
 * Essentia is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation (FSF), either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the Affero GNU General Public License
 * version 3 along with this program.  If not, see http://www.gnu.org/licenses/
 */

#ifndef ESSENTIA_IFFTWCOMPLEX_H
#define ESSENTIA_IFFTWCOMPLEX_H

#include "algorithm.h"
#include "threading.h"
#include <complex>
#include <fftw3.h>

namespace essentia {
namespace standard {

class IFFTWComplex : public Algorithm {

 protected:
  Input<std::vector<std::complex<Real> > > _fft;
  Output<std::vector<std::complex<Real> > > _signal;

 public:

  IFFTWComplex() : _fftPlan(0), _input(0), _output(0) {
    declareInput(_fft, "fft", "the input frame");
    declareOutput(_signal, "frame", "the complex IFFT of the input frame");
  }

  ~IFFTWComplex();

  void declareParameters() {
    declareParameter("size", "the expected size of the input frame. This is purely optional and only targeted at optimizing the creation time of the FFT object", "[1,inf)", 1024);
  }


  void compute();
  void configure();

  static const char* name;
  static const char* category;
  static const char* description;

 protected:
  fftwf_plan _fftPlan;
  int _fftPlanSize;
  std::complex<Real>* _input;
  std::complex<Real>* _output;

  void createFFTObject(int size);
};

} // namespace standard
} // namespace essentia

#include "streamingalgorithmwrapper.h"

namespace essentia {
namespace streaming {

class IFFTWComplex : public StreamingAlgorithmWrapper {

 protected:
  Sink<std::vector<std::complex<Real> > > _fft;
  Source<std::vector<std::complex<Real> > > _signal;

 public:
  IFFTWComplex() {
    declareAlgorithm("IFFTC");
    declareInput(_fft, TOKEN, "fft");
    declareOutput(_signal, TOKEN, "frame");
  }
};

} // namespace streaming
} // namespace essentia

#endif // ESSENTIA_IFFTWCOMPLEX_H
