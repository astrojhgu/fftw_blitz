#include "fftw_blitz.hpp"


namespace fftw_blitz{
  fftw_plan fftw_blitz_trait<double>::fft_plan_c2c(int rank, const int* n,
					      fftw_complex* in, 
					      fftw_complex* out,
					      int sign, unsigned int flags)
  {
    return fftw_plan_dft(rank,n,in,out,sign,flags);
  }

  fftw_plan fftw_blitz_trait<double>::fft_plan_r2c(int rank, const int* n,
				double* in, 
				fftw_complex* out,
				unsigned int flags)
  {
    return fftw_plan_dft_r2c(rank,n,in,out,flags);
  }


  fftw_plan fftw_blitz_trait<double>::fft_plan_c2r(int rank, const int* n,
				fftw_complex* in, 
				double* out,
				unsigned int flags)
  {
    return fftw_plan_dft_c2r(rank,n,in,out,flags);
  }

  fftwf_plan fftw_blitz_trait<float>::fft_plan_c2c(int rank, const int* n,
						  fftwf_complex* in, 
						  fftwf_complex* out,
						  int sign, unsigned int flags)
  {
    return fftwf_plan_dft(rank,n,in,out,sign,flags);
  }

  fftwf_plan fftw_blitz_trait<float>::fft_plan_r2c(int rank, const int* n,
						  float* in, 
						  fftwf_complex* out,
						  unsigned int flags)
  {
    return fftwf_plan_dft_r2c(rank,n,in,out,flags);
  }


  fftwf_plan fftw_blitz_trait<float>::fft_plan_c2r(int rank, const int* n,
						    fftwf_complex* in, 
						    float* out,
						    unsigned int flags)
  {
    return fftwf_plan_dft_c2r(rank,n,in,out,flags);
  }

}
