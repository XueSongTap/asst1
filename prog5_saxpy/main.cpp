#include <stdio.h>
#include <algorithm>

#include "CycleTimer.h"
#include "saxpy_ispc.h"

extern void saxpySerial(int N, float a, float* X, float* Y, float* result);


// return GB/s
static float
toBW(int bytes, float sec) {
    return static_cast<float>(bytes) / (1024. * 1024. * 1024.) / sec;
}

static float
toGFLOPS(int ops, float sec) {
    return static_cast<float>(ops) / 1e9 / sec;
}

static void verifyResult(int N, float* result, float* gold) {
    for (int i=0; i<N; i++) {
        if (result[i] != gold[i]) {
            printf("Error: [%d] Got %f expected %f\n", i, result[i], gold[i]);
        }
    }
}

using namespace ispc;


int main() {

    const unsigned int N = 20 * 1000 * 1000; // 20 M element vectors (~80 MB)
    const unsigned int TOTAL_BYTES = 8 * N * sizeof(float);
    /*
    在`saxpy`函数的计算中，`TOTAL_BYTES = 4 * N * sizeof(float)`这一计算考虑了每个元素在内存中的读写操作。尽管在每次操作中`saxpy`只显式地从`X`和`Y`数组各加载一个元素，并向`result`数组写入一个元素，看似每次迭代涉及3个`float`的内存访问，但实际的内存带宽计算中乘以4是合理的。这主要是因为以下几个原因：
1. **读取和写入操作的内存访问**：
   - 对于每个元素，`X`和`Y`各被读取一次，`result`被写入一次。在许多处理器架构中，写操作通常涉及一个读操作和一个写操作，因为处理器需要先从内存中读取整个内存块（包含要写入的位置），修改后再写回整个内存块。

2. **内存系统的写回策略**：
   - 现代计算机系统中，CPU与内存之间的交互通常涉及缓存。大多数系统采用写回（Write-Back）缓存策略，意味着写入操作不会立即传递到主内存，而是首先写入缓存。当缓存行被替换出去时，修改后的数据才被写回到主内存。这个过程实际上涉及到额外的内存读取（加载旧的缓存行）和写入（保存新的缓存行）操作。

3. **缓存一致性和内存对齐**：
   - 在多核处理器系统中，维持缓存一致性通常需要额外的内存操作，这可能导致对相同数据的多次内存访问。此外，内存对齐问题也可能导致实际的内存访问量大于理论计算值。

4. **总线效应和内存预取**：
   - 处理器为了优化性能，往往会预取更多的数据到缓存中。这种预取行为可能导致实际的内存带宽使用高于单纯基于每次操作所需数据量的计算。

因此，尽管每次操作直接涉及三个浮点数的内存访问，但实际的内存带宽消耗可能更高，因为每次写入`result`可能涉及额外的读取和写入操作，以及缓存和内存系统的其他效应。因此，在性能分析中将每个迭代的内存操作计数为4次是合理的，更准确地反映了底层内存系统的实际负载。
    */
    const unsigned int TOTAL_FLOPS = 2 * N;

    float scale = 2.f;

    float* arrayX = new float[N];
    float* arrayY = new float[N];
    float* resultSerial = new float[N];
    float* resultISPC = new float[N];
    float* resultTasks = new float[N];

    // initialize array values
    for (unsigned int i=0; i<N; i++)
    {
        arrayX[i] = i;
        arrayY[i] = i;
        resultSerial[i] = 0.f;
        resultISPC[i] = 0.f;
        resultTasks[i] = 0.f;
    }

    //
    // Run the serial implementation. Repeat three times for robust
    // timing.
    //
    double minSerial = 1e30;
    for (int i = 0; i < 3; ++i) {
        double startTime =CycleTimer::currentSeconds();
        saxpySerial(N, scale, arrayX, arrayY, resultSerial);
        double endTime = CycleTimer::currentSeconds();
        minSerial = std::min(minSerial, endTime - startTime);
    }

    printf("[saxpy serial]:\t\t[%.3f] ms\t[%.3f] GB/s\t[%.3f] GFLOPS\n",
            minSerial * 1000,
            toBW(TOTAL_BYTES, minSerial),
            toGFLOPS(TOTAL_FLOPS, minSerial));

    //
    // Run the ISPC (single core) implementation
    //
    double minISPC = 1e30;
    for (int i = 0; i < 3; ++i) {
        double startTime = CycleTimer::currentSeconds();
        saxpy_ispc(N, scale, arrayX, arrayY, resultISPC);
        double endTime = CycleTimer::currentSeconds();
        minISPC = std::min(minISPC, endTime - startTime);
    }

    verifyResult(N, resultISPC, resultSerial);

    printf("[saxpy ispc]:\t\t[%.3f] ms\t[%.3f] GB/s\t[%.3f] GFLOPS\n",
           minISPC * 1000,
           toBW(TOTAL_BYTES, minISPC),
           toGFLOPS(TOTAL_FLOPS, minISPC));

    //
    // Run the ISPC (multi-core) implementation
    //
    double minTaskISPC = 1e30;
    for (int i = 0; i < 3; ++i) {
        double startTime = CycleTimer::currentSeconds();
        saxpy_ispc_withtasks(N, scale, arrayX, arrayY, resultTasks);
        double endTime = CycleTimer::currentSeconds();
        minTaskISPC = std::min(minTaskISPC, endTime - startTime);
    }

    verifyResult(N, resultTasks, resultSerial);

    printf("[saxpy task ispc]:\t[%.3f] ms\t[%.3f] GB/s\t[%.3f] GFLOPS\n",
           minTaskISPC * 1000,
           toBW(TOTAL_BYTES, minTaskISPC),
           toGFLOPS(TOTAL_FLOPS, minTaskISPC));

    printf("\t\t\t\t(%.2fx speedup from use of tasks)\n", minISPC/minTaskISPC);
    printf("\t\t\t\t(%.2fx speedup from ISPC)\n", minSerial/minISPC);
    printf("\t\t\t\t(%.2fx speedup from task ISPC)\n", minSerial/minTaskISPC);

    delete[] arrayX;
    delete[] arrayY;
    delete[] resultSerial;
    delete[] resultISPC;
    delete[] resultTasks;

    return 0;
}
