#include <CL/sycl.hpp> 

using namespace sycl;

#define dpc_r access::mode::read 
#define dpc_w access::mode::write
#define dpc_rw access::mode::read_write

SYCL_EXTERNAL void test1(id<1> i, accessor<float, 1, access::mode::read> A, accessor<float, 1, access::mode::read> B, accessor<float, 1, access::mode::write> C);


int main(){
        const int N=1024;
        float A[N], B[N], C[N];

        //Initialization of data
        for(size_t i=0; i<N; i++){
                A[i] = i*1.0f;
                B[i] = i*1.0f;
                C[i] = 0.0f;
        }
 {
        buffer<float, 1> bufA { A, range<1> {N} };
        buffer<float, 1> bufB { B, range<1> {N} };
        buffer<float, 1> bufC { C, range<1> {N} };

		gpu_selector device;
		queue q(device);

        q.submit([&](handler& h) {
            auto A = bufA.get_access<dpc_r>(h);
            auto B = bufB.get_access<dpc_r>(h);
            auto C = bufC.get_access<dpc_w>(h);

            h.parallel_for(range<1> {N}, [=](id<1> i) {
                test1(i, A, B, C);
            });
        });
    }
	for (int i = 0; i < N; i++)
        	std::cout << "C[" << i << "] = " << C[i] << std::endl;

	return 0;
}
