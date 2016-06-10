#include"test_common.h"
#include"hip_runtime.h"
#include"hip_runtime_api.h"

#define N 512
#define SIZE N*sizeof(float)

__global__ void test_sincosf(hipLaunchParm lp, float* a, float* b, float *c){
    int tid = hipThreadIdx_x;
    sincosf(a[tid], b+tid, c+tid);
}

__global__ void test_sincospif(hipLaunchParm lp, float* a, float* b, float *c){
    int tid = hipThreadIdx_x;
    sincospif(a[tid], b+tid, c+tid);
}

__global__ void test_fdividef(hipLaunchParm lp, float *a, float* b, float *c){
    int tid = hipThreadIdx_x;
    c[tid] = fdividef(a[tid], b[tid]);
}

__global__ void test_llrintf(hipLaunchParm lp, float *a, long long int *b){
    int tid = hipThreadIdx_x;
    b[tid] = llrintf(a[tid]);
}

__global__ void test_lrintf(hipLaunchParm lp, float *a, long int *b){
    int tid = hipThreadIdx_x;
    b[tid] = lrintf(a[tid]);
}

__global__ void test_rintf(hipLaunchParm lp, float *a, float *b){
    int tid = hipThreadIdx_x;
    b[tid] = rintf(a[tid]);
}

__global__ void test_llroundf(hipLaunchParm lp, float *a, long long int *b){
    int tid = hipThreadIdx_x;
    b[tid] = llroundf(a[tid]);
}

__global__ void test_lroundf(hipLaunchParm lp, float *a, long int *b){
    int tid = hipThreadIdx_x;
    b[tid] = lroundf(a[tid]);
}

__global__ void test_rhypotf(hipLaunchParm lp, float *a, float* b, float *c){
    int tid = hipThreadIdx_x;
    c[tid] = rhypotf(a[tid], b[tid]);
}

__global__ void test_norm3df(hipLaunchParm lp, float *a, float* b, float *c, float *d){
    int tid = hipThreadIdx_x;
    d[tid] = norm3df(a[tid], b[tid], c[tid]);
}

__global__ void test_norm4df(hipLaunchParm lp, float *a, float* b, float *c, float *d, float *e){
    int tid = hipThreadIdx_x;
    e[tid] = norm4df(a[tid], b[tid], c[tid], d[tid]);
}

__global__ void test_normf(hipLaunchParm lp, float *a, float *b){
    int tid = hipThreadIdx_x;
    b[tid] = normf(N, a);
}

__global__ void test_rnorm3df(hipLaunchParm lp, float *a, float* b, float *c, float *d){
    int tid = hipThreadIdx_x;
    d[tid] = rnorm3df(a[tid], b[tid], c[tid]);
}

__global__ void test_rnorm4df(hipLaunchParm lp, float *a, float* b, float *c, float *d, float *e){
    int tid = hipThreadIdx_x;
    e[tid] = rnorm4df(a[tid], b[tid], c[tid], d[tid]);
}

__global__ void test_rnormf(hipLaunchParm lp, float *a, float *b){
    int tid = hipThreadIdx_x;
    b[tid] = rnormf(N, a);
}



bool run_sincosf(){
float *A, *Ad, *B, *C, *Bd, *Cd;
A = new float[N];
B = new float[N];
C = new float[N];
for(int i=0;i<N;i++){
A[i] = 1.0f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_sincosf, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd);
hipMemcpy(B, Bd, SIZE, hipMemcpyDeviceToHost);
hipMemcpy(C, Cd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(B[i] == sinf(1.0f)){
        passed = 1;
    }
}
passed = 0;
for(int i=0;i<512;i++){
    if(C[i] == cosf(1.0f)){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_sincospif(){
float *A, *Ad, *B, *C, *Bd, *Cd;
A = new float[N];
B = new float[N];
C = new float[N];
for(int i=0;i<N;i++){
A[i] = 1.0f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_sincospif, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd);
hipMemcpy(B, Bd, SIZE, hipMemcpyDeviceToHost);
hipMemcpy(C, Cd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(B[i] - sinpif(1.0f) < 0.1){
        passed = 1;
    }
}
passed = 0;
for(int i=0;i<512;i++){
    if(C[i] - cospif(1.0f) < 0.1){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_fdividef(){
float *A, *Ad, *B, *C, *Bd, *Cd;
A = new float[N];
B = new float[N];
C = new float[N];
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 2.0f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Bd, B, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_fdividef, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd);
hipMemcpy(C, Cd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(C[i] == A[i]/B[i]){
        passed = 1;
    }
}

free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_llrintf(){
float *A, *Ad;
long long int *B, *Bd;
A = new float[N];
B = new long long int[N];
for(int i=0;i<N;i++){
A[i] = 1.345f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, N*sizeof(long long int));
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_llrintf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, N*sizeof(long long int), hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    int x = roundf(A[i]);
    long long int y = x;
    if(B[i] == x){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_lrintf(){
float *A, *Ad;
long int *B, *Bd;
A = new float[N];
B = new long int[N];
for(int i=0;i<N;i++){
A[i] = 1.345f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, N*sizeof(long int));
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_lrintf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, N*sizeof(long int), hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    int x = roundf(A[i]);
    long int y = x;
    if(B[i] == x){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_rintf(){
float *A, *Ad;
float *B, *Bd;
A = new float[N];
B = new float[N];
for(int i=0;i<N;i++){
A[i] = 1.345f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_rintf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    float x = roundf(A[i]);
    if(B[i] == x){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}


bool run_llroundf(){
float *A, *Ad;
long long int *B, *Bd;
A = new float[N];
B = new long long int[N];
for(int i=0;i<N;i++){
A[i] = 1.345f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, N*sizeof(long long int));
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_llroundf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, N*sizeof(long long int), hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    int x = roundf(A[i]);
    long long int y = x;
    if(B[i] == x){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_lroundf(){
float *A, *Ad;
long int *B, *Bd;
A = new float[N];
B = new long int[N];
for(int i=0;i<N;i++){
A[i] = 1.345f;
}
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, N*sizeof(long int));
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_lroundf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, N*sizeof(long int), hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    int x = roundf(A[i]);
    long int y = x;
    if(B[i] == x){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}


bool run_norm3df(){
float *A, *Ad, *B, *Bd, *C, *Cd, *D, *Dd;
A = new float[N];
B = new float[N];
C = new float[N];
D = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 2.0f;
C[i] = 3.0f;
}
val = sqrtf(1.0f + 4.0f + 9.0f);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMalloc((void**)&Dd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Bd, B, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Cd, C, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_norm3df, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd, Dd);
hipMemcpy(D, Dd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(D[i] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_norm4df(){
float *A, *Ad, *B, *Bd, *C, *Cd, *D, *Dd, *E, *Ed;
A = new float[N];
B = new float[N];
C = new float[N];
D = new float[N];
E = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 2.0f;
C[i] = 3.0f;
D[i] = 4.0f;
}
val = sqrtf(1.0f + 4.0f + 9.0f + 16.0f);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMalloc((void**)&Dd, SIZE);
hipMalloc((void**)&Ed, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Bd, B, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Cd, C, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Dd, D, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_norm4df, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd, Dd, Ed);
hipMemcpy(E, Ed, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(E[i] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_normf(){
float *A, *Ad, *B, *Bd;
A = new float[N];
B = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 0.0f;
val += 1.0f;
}
val = sqrtf(val);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_normf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(B[0] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_rhypotf(){
float *A, *Ad, *B, *Bd, *C, *Cd;
A = new float[N];
B = new float[N];
C = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 2.0f;
}
val = 1/sqrtf(1.0f + 4.0f);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Bd, B, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_rhypotf, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd);
hipMemcpy(C, Cd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(C[i] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_rnorm3df(){
float *A, *Ad, *B, *Bd, *C, *Cd, *D, *Dd;
A = new float[N];
B = new float[N];
C = new float[N];
D = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 2.0f;
C[i] = 3.0f;
}
val = 1/sqrtf(1.0f + 4.0f + 9.0f);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMalloc((void**)&Dd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Bd, B, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Cd, C, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_rnorm3df, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd, Dd);
hipMemcpy(D, Dd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(D[i] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_rnorm4df(){
float *A, *Ad, *B, *Bd, *C, *Cd, *D, *Dd, *E, *Ed;
A = new float[N];
B = new float[N];
C = new float[N];
D = new float[N];
E = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 2.0f;
C[i] = 3.0f;
D[i] = 4.0f;
}
val = 1/sqrtf(1.0f + 4.0f + 9.0f + 16.0f);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMalloc((void**)&Cd, SIZE);
hipMalloc((void**)&Dd, SIZE);
hipMalloc((void**)&Ed, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Bd, B, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Cd, C, SIZE, hipMemcpyHostToDevice);
hipMemcpy(Dd, D, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_rnorm4df, dim3(1), dim3(N), 0, 0, Ad, Bd, Cd, Dd, Ed);
hipMemcpy(E, Ed, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(E[i] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}

bool run_rnormf(){
float *A, *Ad, *B, *Bd;
A = new float[N];
B = new float[N];
float val = 0.0f;
for(int i=0;i<N;i++){
A[i] = 1.0f;
B[i] = 0.0f;
val += 1.0f;
}
val = 1/sqrtf(val);
hipMalloc((void**)&Ad, SIZE);
hipMalloc((void**)&Bd, SIZE);
hipMemcpy(Ad, A, SIZE, hipMemcpyHostToDevice);
hipLaunchKernel(test_rnormf, dim3(1), dim3(N), 0, 0, Ad, Bd);
hipMemcpy(B, Bd, SIZE, hipMemcpyDeviceToHost);
int passed = 0;
for(int i=0;i<512;i++){
    if(B[0] - val < 0.000001){
        passed = 1;
    }
}
free(A);
if(passed == 1){
    return true;
}
assert(passed == 1);
return false;
}


int main(){
if(run_sincosf() && run_sincospif() && run_fdividef() && 
   run_llrintf() && run_norm3df() && run_norm4df() &&
   run_normf() && run_rnorm3df() && run_rnorm4df() &&
   run_rnormf() && run_lroundf() && run_llroundf() &&
   run_rintf() && run_rhypotf()
){
passed();
}
}
