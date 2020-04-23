//compile with following options
//clang++ -fsycl -fsycl-targets=nvptx64-nvidia-cuda-sycldevice -std=c++17
#include <CL/sycl.hpp>
#define N 256

using namespace sycl;

int main()
  try
  {
    std::vector<float> B(N);
    buffer buff{ B };
    queue q;

    std::cout << "running via SYCL on " << q.get_device().get_info<info::device::name>()
       << ", driver version " << q.get_device().get_info<info::device::driver_version>()
       << std::endl;

    q.submit([&](handler &h) {
    auto acc = buff.get_access<access::mode::write>(h);
    h.parallel_for<class Test>(
      range(N),
      [=](id<1> id) {
        acc[id] = 1;
      });
  });


  return 0;
}
catch (exception const &exc) {
  std::cerr << exc.what() << "EOE at line " << __LINE__ << std::endl;
  std::exit(1);
}
