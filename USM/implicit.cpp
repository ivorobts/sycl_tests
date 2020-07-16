#include <CL/sycl.hpp>

int main()
{
  using namespace sycl;
  queue q;
  int *hostArray = (int*) malloc_host(42 * sizeof(int), q);
  int *sharedArray = (int*) malloc_shared(42 * sizeof(int), q);

  for (int i = 0; i < 42; i++) hostArray[i] = 1234;
  q.submit([&](handler& h){
    h.parallel_for(range<1>{42}, [=](id<1> ID) {
      int i = ID[0];
      // access sharedArray and hostArray on device
      sharedArray[i] = hostArray[i] + 1;
    });
  });
  q.wait();
  for (int i = 0; i < 42; i++) hostArray[i] = sharedArray[i];
  free(sharedArray, q);
  free(hostArray, q);
}
