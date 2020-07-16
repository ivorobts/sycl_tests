#include <CL/sycl.hpp>
int main()
{	
using namespace sycl;
queue q; 
int* d = (int*)malloc_shared(2 * sizeof(int), q); 

d[0] = 10; d[1] = 10; 

  q.submit([&] (handler &h){ 
    h.parallel_for(range<1>(2), [=](item<1> item){ 
      size_t index = item.get_linear_id(); 
      d[index] += 1; 
    }); 
  }); 
q.wait();

std::cout << "Output : " << d[0] << ", " << d[1] << std::endl; 

}
