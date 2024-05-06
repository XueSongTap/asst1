## Program 2: Vectorizing Code Using SIMD Intrinsics (20 points) ##

Take a look at the function `clampedExpSerial` in `prog2_vecintrin/main.cpp` of the
Assignment 1 code base.  The `clampedExp()` function raises `values[i]` to the power given by `exponents[i]` for all elements of the input array and clamps the resulting values at 9.999999.  In program 2, your job is to vectorize this piece of code so it can be run on a machine with SIMD vector instructions.

However, rather than craft an implementation using SSE or AVX2 vector intrinsics that map to real SIMD vector instructions on modern CPUs, to make things a little easier, we're asking you to implement your version using CS149's "fake vector intrinsics" defined in `CS149intrin.h`.   The `CS149intrin.h` library provides you with a set of vector instructions that operate
on vector values and/or vector masks. (These functions don't translate to real CPU vector instructions, instead we simulate these operations for you in our library, and provide feedback that makes for easier debugging.)  As an example of using the CS149 intrinsics, a vectorized version of the `abs()` function is given in `main.cpp`. This example contains some basic vector loads and stores and manipulates mask registers.  Note that the `abs()` example is only a simple example, and in fact the code does not correctly handle all inputs! (We will let you figure out why!) You may wish to read through all the comments and function definitions in `CS149intrin.h` to know what operations are available to you. 

Here are few hints to help you in your implementation:

-  Every vector instruction is subject to an optional mask parameter.  The mask parameter defines which lanes whose output is "masked" for this operation. A 0 in the mask indicates a lane is masked, and so its value will not be overwritten by the results of the vector operation. If no mask is specified in the operation, no lanes are masked. (Note this equivalent to providing a mask of all ones.) 
   *Hint:* Your solution will need to use multiple mask registers and various mask operations provided in the library.
-  *Hint:* Use `_cs149_cntbits` function helpful in this problem.
-  Consider what might happen if the total number of loop iterations is not a multiple of SIMD vector width. We suggest you test 
your code with `./myexp -s 3`. *Hint:* You might find `_cs149_init_ones` helpful.
-  *Hint:* Use `./myexp -l` to print a log of executed vector instruction at the end. 
Use function `addUserLog()` to add customized debug information in log. Feel free to add additional 
`CS149Logger.printLog()` to help you debug.

The output of the program will tell you if your implementation generates correct output. If there
are incorrect results, the program will print the first one it finds and print out a table of
function inputs and outputs. Your function's output is after "output = ", which should match with 
the results after "gold = ". The program also prints out a list of statistics describing utilization of the CS149 fake vector
units. You should consider the performance of your implementation to be the value "Total Vector 
Instructions". (You can assume every CS149 fake vector instruction takes one cycle on the CS149 fake SIMD CPU.) "Vector Utilization" 
shows the percentage of vector lanes that are enabled. 

**What you need to do:**

1.  Implement a vectorized version of `clampedExpSerial` in `clampedExpVector` . Your implementation 
should work with any combination of input array size (`N`) and vector width (`VECTOR_WIDTH`). 
2.  Run `./myexp -s 10000` and sweep the vector width from 2, 4, 8, to 16. Record the resulting vector 
utilization. You can do this by changing the `#define VECTOR_WIDTH` value in `CS149intrin.h`. 
Does the vector utilization increase, decrease or stay the same as `VECTOR_WIDTH` changes? Why?
3.  _Extra credit: (1 point)_ Implement a vectorized version of `arraySumSerial` in `arraySumVector`. Your implementation may assume that `VECTOR_WIDTH` is a factor of the input array size `N`. Whereas the serial implementation runs in `O(N)` time, your implementation should aim for runtime of `(N / VECTOR_WIDTH + VECTOR_WIDTH)` or even `(N / VECTOR_WIDTH + log2(VECTOR_WIDTH))`  You may find the `hadd` and `interleave` operations useful.


## 程序2：使用SIMD内在指令向量化代码（20分）

请查看作业1代码库中`prog2_vecintrin/main.cpp`文件的`clampedExpSerial`函数。该函数的`clampedExp()`功能是对输入数组的所有元素中的`values[i]`按`exponents[i]`的幂进行运算，并将结果限制在9.999999。在程序2中，你的任务是将这段代码向量化，使其可以在具有SIMD向量指令的机器上运行。

然而，我们不要求你使用映射到现代CPU上真实SIMD向量指令的SSE或AVX2向量内在指令来实现，为了简化问题，我们希望你使用CS149的“假向量内在指令”来实现你的版本，这些内在指令定义在`CS149intrin.h`中。`CS149intrin.h`库为你提供了一组操作向量值和/或向量掩码的向量指令。（这些函数并不转换为真实的CPU向量指令，相反，我们在库中为你模拟这些操作，并提供便于调试的反馈。）作为使用CS149内在指令的一个例子，`main.cpp`中给出了`abs()`函数的向量化版本。这个例子包含了一些基本的向量加载和存储操作，并操纵掩码寄存器。注意，`abs()`示例只是一个简单的示例，事实上代码并没有正确处理所有输入！（我们将让你自己找出原因！）你可能希望阅读`CS149intrin.h`中的所有注释和函数定义，以了解你可以使用的操作。

以下是一些帮助你实现的提示：

- 每个向量指令都可以选择一个可选的掩码参数。掩码参数定义了哪些通道的输出为这个操作“掩蔽”。掩码中的0表示一个通道被掩蔽，因此其值不会被向量操作的结果覆盖。如果操作中没有指定掩码，那么没有通道被掩蔽。（这等同于提供一个全1的掩码。）
   *提示：* 你的解决方案需要使用多个掩码寄存器和库中提供的各种掩码操作。
- *提示：* `_cs149_cntbits`函数在这个问题中很有帮助。
- 考虑如果循环迭代的总数不是SIMD向量宽度的倍数会发生什么。我们建议你使用`./myexp -s 3`测试你的代码。*提示：* `_cs149_init_ones`可能有帮助。
- *提示：* 使用`./myexp -l`在最后打印执行的向量指令日志。使用`addUserLog()`函数添加自定义的调试信息。随意添加额外的`CS149Logger.printLog()`来帮助你调试。

程序的输出将告诉你你的实现是否产生了正确的输出。如果有不正确的结果，程序将打印出它找到的第一个，并打印出函数输入和输出的表格。你函数的输出在“output = ”之后，应该与“gold = ”后的结果匹配。程序还会打印一系列描述CS149假向量单元利用情况的统计数据。你应该考虑你的实现的性能为“总向量指令”的值。（你可以假设CS149假SIMD CPU上的每个CS149假向量指令需要一个周期。）“向量利用率”显示启用的向量通道的百分比。

**你需要做的事情：**

1. 在`clamped

ExpVector`中实现`clampedExpSerial`的向量化版本。你的实现应该适用于任何组合的输入数组大小（`N`）和向量宽度（`VECTOR_WIDTH`）。
2. 运行`./myexp -s 10000`并将向量宽度从2, 4, 8, 到16进行变换。记录结果的向量利用率。你可以通过改变`CS149intrin.h`中的`#define VECTOR_WIDTH`值来做到这一点。向量利用率是随着`VECTOR_WIDTH`的变化而增加、减少还是保持不变？为什么？
3. _额外学分：（1分）_ 在`arraySumVector`中实现`arraySumSerial`的向量化版本。你的实现可以假设`VECTOR_WIDTH`是输入数组大小`N`的因数。而串行实现的运行时间为`O(N)`，你的实现应该目标是`(N / VECTOR_WIDTH + VECTOR_WIDTH)`甚至`(N / VECTOR_WIDTH + log2(VECTOR_WIDTH))`的运行时间。你可能会发现`hadd`和`interleave`操作有用。s