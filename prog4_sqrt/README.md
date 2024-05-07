
## Program 4: Iterative `sqrt` (15 points) ##

Program 4 is an ISPC program that computes the square root of 20 million
random numbers between 0 and 3. It uses a fast, iterative implementation of
square root that uses Newton's method to solve the equation ${\frac{1}{x^2}} - S = 0$.
The value 1.0 is used as the initial guess in this implementation. The graph below shows the 
number of iterations required for `sqrt` to converge to an accurate solution 
for values in the (0-3) range. (The implementation does not converge for 
inputs outside this range). Notice that the speed of convergence depends on the 
accuracy of the initial guess.

Note: This problem is a review to double-check your understanding, as it covers similar concepts as programs 2 and 3.

![Convergence of sqrt](handout-images/sqrt_graph.jpg "Convergence of sqrt on the range 0-3 with starting guess 1.0. Note that iterations until convergence is immediate for an input value of 1 and increases as the input value goes toward 0 or 3 (highest value is for input of 3).")

**What you need to do:**

1.  Build and run `sqrt`. Report the ISPC implementation speedup for 
  single CPU core (no tasks) and when using all cores (with tasks). What 
  is the speedup due to SIMD parallelization? What is the speedup due to 
  multi-core parallelization?
2.  Modify the contents of the array values to improve the relative speedup 
  of the ISPC implementations. Construct a specifc input that __maximizes speedup over the sequential version of the code__ and report the resulting speedup achieved (for both the with- and without-tasks ISPC implementations). Does your modification improve SIMD speedup?
  Does it improve multi-core speedup (i.e., the benefit of moving from ISPC without-tasks to ISPC with tasks)? Please explain why.
3.  Construct a specific input for `sqrt` that __minimizes speedup for ISPC (without-tasks) over the sequential version of the code__. Describe this input, describe why you chose it, and report the resulting relative performance of the ISPC implementations. What is the reason for the loss in efficiency? 
    __(keep in mind we are using the `--target=avx2` option for ISPC, which generates 8-wide SIMD instructions)__. 
4.  _Extra Credit: (up to 2 points)_ Write your own version of the `sqrt` 
 function manually using AVX2 intrinsics. To get credit your 
    implementation should be nearly as fast (or faster) than the binary 
    produced using ISPC. You may find the [Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide/) 
    very helpful.

这是一个计算程序的任务说明，涉及使用ISPC编程语言来计算随机数的平方根。

## 程序4：迭代平方根计算（15分）##

程序4是一个ISPC程序，它计算2000万个介于0到3之间的随机数的平方根。它使用了一种快速迭代的平方根实现方法，采用牛顿法解方程 ${\frac{1}{x^2}} - S = 0$。这个实现中初始猜测值使用1.0。下面的图表显示了对于(0-3)范围内的值，`sqrt`收敛到精确解所需的迭代次数（程序在此范围之外的输入值上不会收敛）。请注意，收敛速度取决于初始猜测的准确性。

注意：这个问题是为了复查你的理解，因为它涵盖了与程序2和3相似的概念。

（这里有一张关于0-3范围内的平方根收敛的图，初始猜测为1.0。请注意，对于输入值为1时，收敛是立即的，并且随着输入值向0或3（输入为3时值最高）靠近，需要的迭代次数增加。）

**你需要做的事情：**

1. 构建并运行`sqrt`。报告ISPC实现在单核CPU（无任务）以及使用所有核心（带任务）时的加速比。SIMD并行化带来的加速比是多少？多核并行化带来的加速比是多少？
2. 修改数组值的内容，以提高ISPC实现的相对加速比。构造一个特定的输入，**最大化与顺序代码版本的加速比**，并报告达到的加速比（对于带任务和不带任务的ISPC实现都要报告）。你的修改是否提高了SIMD加速比？是否提高了多核加速比（即，从ISPC无任务移至ISPC带任务的好处）？请解释原因。
3. 为`sqrt`构造一个特定的输入，**最小化ISPC（无任务）与顺序版本代码的加速比**。描述这个输入，解释你为什么选择它，并报告ISPC实现的相对性能。导致效率降低的原因是什么？（**请记住，我们使用的是`--target=avx2`选项，这会生成8宽的SIMD指令**）。
4. _额外加分：（最多2分）_ 手动使用AVX2内在函数编写你自己的`sqrt`函数版本。为了得到学分，你的实现应该与使用ISPC生成的二进制文件一样快（或更快）。你可能会发现[Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide/)非常有用。
 


在ISPC (Intel SPMD Program Compiler) 中调用并行化计算的方式与传统的单线程C/C++编程有所不同。ISPC利用了单指令多数据（SIMD）的并行性来加速计算。在你提供的代码中，有几个关键的点需要理解以明白如何进行调用：

### ISPC的并行任务启动

在ISPC中，使用`launch`关键字来启动并行任务。这是ISPC特有的构造，它允许程序以SPMD（单程序多数据）的方式启动多个任务。在你的代码中，`launch`关键字用于从`sqrt_ispc_withtasks`函数中启动多个`sqrt_ispc_task`任务。

```c
uniform int span = N / 64;  // 定义每个任务处理的元素数量，总共64个任务
launch[N/span] sqrt_ispc_task(N, span, initialGuess, values, output);
```

这里，`launch[N/span]`表明将要启动的任务数量，它根据总数据量`N`和每个任务的数据跨度`span`计算得出。`sqrt_ispc_task`是任务函数名，后面跟着的是传递给每个任务的参数。

### 如何理解`uniform`和`foreach`

- **uniform**：这个关键字用于标记一个变量在所有并行执行的程序中都是相同的。在ISPC中，`uniform`意味着每个处理器核心（或线程）看到的该变量值都是一样的，这对于任务分割和同步很关键。

- **foreach**：`foreach`是ISPC中实现循环的方式，用于自动并行处理数组或集合中的每个元素。`foreach (i = 0 ... N)`类似于C++中的`for (int i = 0; i < N; i++)`，但是ISPC会尝试自动在多个核心上并行执行这个循环。

### 函数导出

- **export**：`export`关键字用于标记函数，使得它可以被ISPC生成的库的外部C/C++代码调用。这意味着在ISPC编译后的程序可以被一个常规的C/C++程序作为库来调用。



```bash
yxc@yxc-System-Product-Name:~/code/asst1/prog4_sqrt$ ./sqrt
[sqrt serial]:          [2002.253] ms
[sqrt ispc]:            [413.499] ms
[sqrt task ispc]:       [27.606] ms
                                (4.84x speedup from ISPC)
                                (72.53x speedup from task ISPC)
```