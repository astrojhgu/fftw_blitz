#ifndef FFTW_BLITZ
#define FFTW_BLITZ
#include <cassert>
#include <complex>
#include <blitz/array.h>
#include <fftw3.h>
#include <iostream>
#include <cstdlib>
#ifndef NFFTW_THREADS
//#define NFFTW_THREADS 8
#endif

namespace fftw_blitz
{

  template <typename T>
  class fftw_blitz_trait
  {
  public:
    static void test()
    {
      std::cerr<<"Error, this type has not been implemented"<<std::endl;
      assert(0);
    }

  };

  template <>
  class fftw_blitz_trait<double>
  {
  public:
    static void test()
    {
    }
    static fftw_plan fft_plan_c2c(int, const int*,
				  fftw_complex*, fftw_complex*,
				  int, unsigned int);
    static fftw_plan fft_plan_r2c(int, const int*,
				  double*, fftw_complex*,
				  unsigned int);
    static fftw_plan fft_plan_c2r(int, const int*,
				  fftw_complex*, double*,
				  unsigned int);
  };
  
  template <>
  class fftw_blitz_trait<float>
  {
  public:
    static void test()
    {
    }
    static fftwf_plan fft_plan_c2c(int, const int*,
				  fftwf_complex*, fftwf_complex*,
				  int, unsigned int);
    static fftwf_plan fft_plan_r2c(int, const int*,
				  float*, fftwf_complex*,
				  unsigned int);
    static fftwf_plan fft_plan_c2r(int, const int*,
				  fftwf_complex*, float*,
				  unsigned int);
  };
  


  template <typename T,int N>
  blitz::Array<std::complex<T>,N> fft_c2c(blitz::Array<std::complex<T>,N> in, int sign=FFTW_FORWARD, int flags=FFTW_ESTIMATE)
  {
    fftw_blitz_trait<T>::test();
    blitz::Array<std::complex<T>,N> out(in.shape());
    fftw_plan p;
    blitz::TinyVector<int, N> ranks=in.shape();
#ifdef NFFTW_THREADS
    fftw_init_threads();
    fftw_plan_with_nthreads(NFFTW_THREADS);
#endif
    p = fftw_blitz_trait<T>::fft_plan_c2c(N, ranks.data(),reinterpret_cast<fftw_complex*>(in.data()), 
		      reinterpret_cast<fftw_complex*>(out.data()), sign, flags);
    fftw_execute(p);
    fftw_destroy_plan(p);
#ifdef NFFTW_THREADS 
    fftw_cleanup_threads();
#endif
    return out;
  }

  
  template <typename T,int N>
  blitz::Array<std::complex<T>,N> fft_r2c(blitz::Array<T,N> in,int flags=FFTW_ESTIMATE)
  {
    fftw_blitz_trait<T>::test();
    blitz::Array<std::complex<T>,N> out(in.shape());
    fftw_plan p;
    blitz::TinyVector<int, N> ranks=in.shape();
#ifdef NFFTW_THREADS
    fftw_init_threads();
    fftw_plan_with_nthreads(NFFTW_THREADS);
#endif
    p = fftw_blitz_trait<T>::fft_plan_r2c(N, ranks.data(),in.data(), 
					  reinterpret_cast<fftw_complex*>(out.data()),flags);
    fftw_execute(p);
    fftw_destroy_plan(p);
#ifdef NFFTW_THREADS
    fftw_cleanup_threads();
#endif
    return out;
  }

  
  template <typename T,int N>
  blitz::Array<T,N> fft_c2r(blitz::Array<std::complex<T>,N> in,int flags=FFTW_ESTIMATE)
  {
    fftw_blitz_trait<T>::test();
    blitz::Array<T,N> out(in.shape());
    fftw_plan p;
    blitz::TinyVector<int, N> ranks=in.shape();
#ifdef NFFTW_THREADS
    fftw_init_threads();
    fftw_plan_with_nthreads(NFFTW_THREADS);
#endif
    p = fftw_blitz_trait<T>::fft_plan_c2r(N, ranks.data(), reinterpret_cast<fftw_complex*>(in.data()), 
					  out.data(),flags);
    fftw_execute(p);
    fftw_destroy_plan(p);
#ifdef NFFTW_THREADS
    fftw_cleanup_threads();
#endif
    return out;
  }
  
  /*
    template <typename T,int N>
    void fft_shift(blitz::Array<T,N>& mx)
  {
  blitz::TinyVector<T,N> idx1,idx2;
  for(int cnt=0;cnt<N;++cnt)
  {
  for(typename blitz::Array<T,N>::iterator i=mx.begin();
  i!=mx.end();++i)
  {
  if(i.position()[cnt]<mx.extent(cnt)/2)
  {
  blitz::TinyVector<int,N> idx=i.position();
  idx(cnt)+=mx.extent(cnt)/2;
  T temp=mx(idx);
  mx(idx)=*i;
  *i=temp;
  }
  }
  }
  }
  */
  template <typename T,int N>
  void swap_by_dim(blitz::Array<T,N>& mx,int dim)
  {
    for(typename blitz::Array<T,N>::iterator i=mx.begin();i!=mx.end();++i)
      {
	if(i.position()(dim)*2>=mx.extent(dim))
	  {
	    continue;
	  }
	blitz::TinyVector<int,N> source_idx=i.position();
	blitz::TinyVector<int,N> target_idx=i.position();
	target_idx(dim)+=mx.extent(dim)/2;
	T temp=mx(source_idx);
	mx(source_idx)=mx(target_idx);
	mx(target_idx)=temp;
      }
  }

  template <typename T,int N>
  void fft_shift(blitz::Array<T,N>& mx)
  {
    for(int i=0;i<N;++i)
      {
	swap_by_dim(mx,i);
      }
  }
  
};


#endif

