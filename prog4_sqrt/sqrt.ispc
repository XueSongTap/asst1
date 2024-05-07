// 定义一个阈值常量，用于确定迭代何时停止
static const float kThreshold = 0.00001f; 

// 定义一个导出函数，用于计算一个数组中每个值的平方根
export void sqrt_ispc(uniform int N, // 输入：要计算的元素数量
                      uniform float initialGuess, // 输入：牛顿法的初始猜测值
                      uniform float values[], // 输入：需要计算平方根的值数组
                      uniform float output[]) // 输出：计算得到的平方根结果数组
{
    // 遍历所有元素
    foreach (i = 0 ... N) {
        float x = values[i]; // 当前值
        float guess = initialGuess; // 初始猜测值

        // 计算预测误差
        float pred = abs(guess * guess * x - 1.f);

        // 当误差大于阈值时，继续迭代
        while (pred > kThreshold) {
            // 使用牛顿法更新猜测值
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            // 重新计算误差
            pred = abs(guess * guess * x - 1.f);
        }

        // 存储计算结果
        output[i] = x * guess;
    }
}

// 定义一个任务函数，用于并行计算平方根
task void sqrt_ispc_task(uniform int N, // 总元素数量
                         uniform int span, // 每个任务处理的元素数量
                         uniform float initialGuess, // 初始猜测值
                         uniform float values[], // 输入数组
                         uniform float output[]) // 输出数组
{
    // 计算当前任务处理的起始和结束索引
    uniform int indexStart = taskIndex * span;
    uniform int indexEnd = min(N, indexStart + span);

    // 遍历任务负责的元素
    foreach (i = indexStart ... indexEnd) {
        float x = values[i];
        float guess = initialGuess;

        float pred = abs(guess * guess * x - 1.f);

        while (pred > kThreshold) {
            guess = (3.f * guess - x * guess * guess * guess) * 0.5f;
            pred = abs(guess * guess * x - 1.f);
        }

        output[i] = x * guess;
    }
}

// 定义一个导出函数，使用任务并行化来加速计算
export void sqrt_ispc_withtasks(uniform int N, // 元素总数
                                uniform float initialGuess, // 初始猜测值
                                uniform float values[], // 输入数组
                                uniform float output[]) // 输出数组
{
    uniform int span = N / 64;  // 定义每个任务处理的元素数量，总共64个任务

    // 启动足够多的任务以覆盖所有元素
    launch[N/span] sqrt_ispc_task(N, span, initialGuess, values, output);
}
