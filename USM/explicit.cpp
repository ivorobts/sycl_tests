#include <CL/sycl.hpp>

int main()
{
  using namespace sycl;
  queue q;
  int hostArray[42];
  int *deviceArray = (int*) malloc_device(42 * sizeof(int), q);
  for (int i = 0; i < 42; i++) hostArray[i] = 42;  
 
  // copy hostArray to deviceArray
  q.memcpy(deviceArray, &hostArray[0], 42 * sizeof(int));
  q.wait(); // needed for now (we learn how to ditch soon)

  q.submit([&](handler& h) {
    h.parallel_for(range<1>{42}, [=](id<1> ID) {
      deviceArray[ID]++;
      }); 
  });
  q.wait(); // needed for now (we learn how to ditch soon)
  
  // copy deviceArray back to hostArray
  q.memcpy(&hostArray[0], deviceArray, 42 * sizeof(int));

  q.wait(); // needed for now (we learn how to ditch soon)
  free(deviceArray, q);
}
