#include <CL/sycl.hpp>
SYCL_EXTERNAL void test1(sycl::id<1> i, sycl::accessor<float, 1, sycl::access::mode::read> A,sycl::accessor<float, 1, sycl::access::mode::read> B, sycl::accessor<float, 1, sycl::access::mode::write> C)
{
	C[i]=A[i]+B[i];
}