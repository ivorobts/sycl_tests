#include <CL/sycl.hpp>
int main()
{	
using namespace sycl;
queue q; 
int d[2] = {10,10}; 
{
  buffer<int, 1> buf_d(d, range<1>(2)); 

  q.submit([&] (handler &h){ 
    auto acc = buf_d.get_access< access::mode::read_write >(h); 

    h.parallel_for(range<1>(2), [=](item<1> item){ 
      size_t index = item.get_linear_id(); 
      acc[index] += 1; 
    }); 
  }); 
}

std::cout << "Output : " << d[0] << ", " << d[1] << std::endl; 

}
