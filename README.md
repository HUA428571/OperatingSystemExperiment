# OperatingSystemExperiment
> NJUPT 2021操作系统A 实验

## 页面置换算法
### 题目要求：
通过实现页面置换的四种算法，理解虚拟存储器的概念、实现方法，页面分配的总体原则、进程运行时系统是怎样选择换出页面的，并分析四种不同的算法各自的优缺点是哪些。
以下算法都要实现：
1. 最佳置换算法(OPT)：将以后永不使用的或许是在最长(未来)时间内不再被访问的页面换出。
2. 先进先出算法(FIFO)：淘汰最先进入内存的页面，即选择在内存中驻留时间最久的页面予以淘汰。
3. 最近最久未使用算法(LRU)：淘汰最近最久未被使用的页面。
4. 最不经常使用算法(LFU)  
### 实验目的：
1. 用C语言编写OPT、FIFO、LRU，LFU四种置换算法。
2. 熟悉内存分页管理策略。
3. 了解页面置换的算法。
4. 掌握一般常用的调度算法。
5. 根据方案使算法得以模拟实现。
6. 锻炼知识的运用能力和实践能力。
### 设计要求
1. 编写算法，实现页面置换算法；
2. 针对内存地址引用串，运行页面置换算法进行页面置换；
3. 算法所需的各种参数由输入产生（手工输入或者随机数产生）；
4. 输出内存驻留的页面集合，缺页次数以及缺页率；

## 银行家算法
### 题目要求：
银行家算法是避免死锁的一种重要方法，本设计要求用C语言编写和调试一个简单的银行家算法程序。加深有关资源申请、避免死锁等概念，并讨论死锁和避免死锁的具体实施方法，以及银行家算法的原理。
### 设计要求
设计一n个并发进程共享m个系统资源的程序，实现银行家算法。
要求包括：
1. 简单的初始化界面；
2. 系统资源的占用和剩余情况；
3. 为进程分配资源，用银行家算法对其进行检测，分为以下三种情况：
    1. 所申请的资源大于其所需资源，提示分配不合理不予分配并返回；        
    2. 所申请的资源未大于其所需资源，但大于系统此时的可利用资源，提示分配不合理不予分配并返回；
    3. 所申请的资源未大于其所需资源，亦未大于系统此时的可利用资源，预分配并进行安全性检查：
4. 预分配后系统是安全的，将该进程所申请的资源予以实际分配并打印后返回；
5. 与分配后系统进入不安全状态，提示系统不安全并返回；
对输入进行检查，即若输入不符合条件，应当报错并返回重新输入；
撤销作业，释放资源。

## 时间片轮转进程调度算法
### 题目要求：
用C语言实现时间片轮转进程调度算法，加深对调度算法的理解，进一步讨论进程概念、进程状态的转变、进程调度的策略及对系统性能的评价方法。
### 设计要求
**问题描述：**  
设计程序模拟进程的时间片轮转RR调度过程。
假设有n个进程分别在T1, … ,Tn时刻到达系统，它们需要的服务时间分别为S1, … ,Sn。分别利用不同的时间片大小q，采用时间片轮转RR进程调度算法进行调度，计算每个进程的完成时间，周转时间和带权周转时间，并且统计n个进程的平均周转时间和平均带权周转时间。  
**程序要求如下：**
1. 进程个数n；每个进程的到达时间T1, … ,Tn和服务时间S1, … ,Sn；输入时间片大小q。
2. 要求时间片轮转法RR调度进程运行，计算每个进程的周转时间，带权周转时间，并且计算所有进程的平均周转时间，带权平均周转时间；
3. 输出：要求模拟整个调度过程，输出每个时刻的进程运行状态，如“时刻3：进程B开始运行”等等；
4. 输出：要求输出计算出来的每个进程的周转时间，带权周转时间，所有进程的平均周转时间，带权平均周转时间。

## 进程调度算法
### 实验内容
1. 设计可用于该实验的进程控制块，进程控制块至少包括进程号、状态和要求服务时间；
2. 动态或静态创建多个进程；
3. 模拟操作系统四种进程调度算法：先进先出、短作业优先、高优先级优先、高相应比优先中的任意两种。
4. 调度所创建的进程并显示调度结果。
### 实验目的
1. 加深进程概念的理解；
2. 掌握进程状态转变；
3. 掌握进程调度策略。
### 实验要求
1. 编写程序完成实验内容；
2. 在实验报告中画出程序流程图；
3. 撰写实验报告。