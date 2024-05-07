## Program 5: BLAS `saxpy` (10 points) ##

Program 5 is an implementation of the saxpy routine in the BLAS (Basic Linear
Algebra Subproblems) library that is widely used (and heavily optimized) on 
many systems. `saxpy` computes the simple operation `result = scale*X+Y`, where `X`, `Y`, 
and `result` are vectors of `N` elements (in Program 5, `N` = 20 million) and `scale` is a scalar. Note that 
`saxpy` performs two math operations (one multiply, one add) for every three 
elements used. `saxpy` is a *trivially parallelizable computation* and features predictable, regular data access and predictable execution cost.

**What you need to do:**

1.  Compile and run `saxpy`. The program will report the performance of
  ISPC (without tasks) and ISPC (with tasks) implementations of saxpy. What 
  speedup from using ISPC with tasks do you observe? Explain the performance of this program.
  Do you think it can be substantially improved? (For example, could you rewrite the code to achieve near linear speedup? Yes or No? Please justify your answer.)
2. __Extra Credit:__ (1 point) Note that the total memory bandwidth consumed computation in `main.cpp` is `TOTAL_BYTES = 4 * N * sizeof(float);`.  Even though `saxpy` loads one element from X, one element from Y, and writes one element to `result` the multiplier by 4 is correct.  Why is this the case? (Hint, think about how CPU caches work.)
3. __Extra Credit:__ (points handled on a case-by-case basis) Improve the performance of `saxpy`.
  We're looking for a significant speedup here, not just a few percentage 
  points. If successful, describe how you did it and what a best-possible implementation on these systems might achieve. Also, if successful, come tell the staff, we'll be interested. ;-)

Notes: Some students have gotten hung up on this question (thinking too hard) in the past. We expect a simple answer, but the results from running this problem might trigger more questions in your head.  Feel encouraged to come talk to the staff.




## 程序5：BLAS `saxpy`（10分）##

程序5是在BLAS库中`saxpy`例程的一个实现，用于计算简单的运算`result = scale*X+Y`，其中`X`、`Y`和`result`是`N`个元素的向量（在程序5中，`N` = 2000万），而`scale`是一个标量。注意`saxpy`在每三个使用的元素中执行两个数学运算（一次乘法，一次加法）。`saxpy`是一个*轻松并行化的计算*，具有可预测的、规则的数据访问和可预测的执行成本。

**你需要做的事情：**

1. 编译并运行`saxpy`。程序将报告ISPC（不带任务）和ISPC（带任务）实现的`saxpy`的性能。你观察到使用ISPC带任务时的加速比是多少？解释这个程序的性能。
你认为它可以被大幅改进吗？（例如，你能重写代码以实现近乎线性的加速吗？是或否？请证明你的答案。）
2. __额外加分：__（1分）注意，在`main.cpp`中计算消耗的总内存带宽是`TOTAL_BYTES = 4 * N * sizeof(float);`。尽管`saxpy`从X中加载一个元素，从Y中加载一个元素，并向`result`中写入一个元素，但乘以4是正确的。这是为什么？（提示，思考CPU缓存是如何工作的。）

3. __额外加分：__（按情况给分）改进`saxpy`的性能。
   我们在这里寻求显著的加速，而不仅仅是几个百分点。如果成功，请描述你是如何做到的以及在这些系统上可能实现的最佳实现可能达到什么。此外，如果成功，请告诉工作人员，我们会感兴趣。;-)

备注：一些学生在过去对这个问题纠结过（想得太多）。我们期待一个简单的答案，但运行这个问题的结果可能会在你的脑海中引发更多问题。鼓励你来和工作人员交流。


```bash
yxc@yxc-System-Product-Name:~/code/asst1/prog5_saxpy$ ./saxpy 
[saxpy serial]:         [30.852] ms     [19.320] GB/s   [1.297] GFLOPS
[saxpy ispc]:           [28.762] ms     [20.723] GB/s   [1.391] GFLOPS
[saxpy task ispc]:      [28.155] ms     [21.170] GB/s   [1.421] GFLOPS
                                (1.02x speedup from use of tasks)
                                (1.07x speedup from ISPC)
                                (1.10x speedup from task ISPC)
```