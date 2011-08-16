#define NFFTW_THREADS 1
#include "fftw_blitz.hpp"
#include "fio.h"
#include <cstdlib>
using namespace std;
using namespace blitz;
using namespace fftw_blitz;

const double pi=3.14159265358979323846;
int main(int argc,char* argv[])
{
  if(argc!=2)
    {
      return -1;
    }
  cfitsfile ff;
  Array<double,2> mx;
  ff.open(argv[1]);

  ff>>mx;

  //////   - average /////////

  
  double aver=sum(mx)/mx.size();






  ///////////////////////////





  //  return 0;
  Array<complex<double>,2> mxc(mx.extent(0)*2,mx.extent(1)*2);
  mxc=0;
    for(int i=0;i<mx.extent(0);++i)
    {
      for(int j=0;j<mx.extent(1);++j)
	{
	  mxc(i,j)=mx(i,j)-aver;
	}
    }
  
  Array<complex<double>,2> fft_mx=fft_c2c(mxc);
  
  //  Array<complex<double>,2> mxd(fft_mx.shape());
  for(int i=0;i<fft_mx.extent(0);++i)
    {
      for(int j=0;j<fft_mx.extent(1);++j)
	{
	  fft_mx(i,j)=(fft_mx(i,j).real()*fft_mx(i,j).real()+fft_mx(i,j).imag()*fft_mx(i,j).imag());
	  //fft_mx(i,j).real();
	}
    }

  //ff.close();
  mxc=fft_c2c(fft_mx,FFTW_BACKWARD);
  //  Array<complex<double>,2> mxc(mx.shape());
  for(int i=0;i<mx.extent(0);++i)
    {
      for(int j=0;j<mx.extent(1);++j)
	{
	  mx(i,j)=mxc(i,j).real();
	}
    }
  cfitsfile ff1;
  ff1.create("a.fits");
  ff1<<mx;

  Array<double,1> corrfun(min(mx.extent(1),mx.extent(0)));
  corrfun=0;

  for(int i=0;i<mx.extent(0);++i)
    {
      for(int j=0;j<mx.extent(1);++j)
	{
	  if(i*i+j*j<(corrfun.extent(0)-1)*(corrfun.extent(0)-1))
	    {
	      assert(!isnan(mx(i,j)));
	      corrfun((int)sqrt((double)i*i+j*j))+=mx(i,j);
	    }
	}
    }

  for(int i=1;i<corrfun.extent(0);++i)
    {
      cout<<i<<"\t"<<corrfun(i)/((double)i)<<endl;
    }

}
