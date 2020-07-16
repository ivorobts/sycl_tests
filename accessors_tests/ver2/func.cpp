#include <CL/sycl.hpp>
SYCL_EXTERNAL void test1(sycl::id<1> i, const float *a, const float *b, float *c)
{
	c[i]=a[i]+b[i];
}