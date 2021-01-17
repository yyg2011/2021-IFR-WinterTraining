# 2021-IFR-WinterTraining
#### 简介

2021年IFR实验室寒假集训进度

#### 进度

**1.6**  完善单个电机的控制代码 ，新增模式切换（速度环、位置环）以及看门狗。

**1.7**  封装以前写的电机数据转换函数、引用robo-base.c中控制底盘电机的函数实现对底盘4个电机的驱动。初步了解麦克纳姆轮控制原理，正在编写对应单个电机的转速控制代码以实现遥控器对底盘运动的控制。

**1.8**  初步完成麦克纳姆轮的控制代码，正在进行测试。

**1.9**  重写了CAN发送的代码，删除代码冗余部分，解决了一部分历史遗留问题，修复麦轮运动分析算法的错误。

**1.10**  测试通过。修复电机编号被强制设定的bug，修复未接遥控器时电机疯转的bug，新增限速函数。

**1.11**  增加底盘旋转功能。整理思路，重新绘制底盘控制程序流程图。学习链表使用方法，阅读了RM规则。

**1.12**  熟悉链表用法，写了双向链表的程序，实现链表数据的排序、删除以及合并。

**1.13**  熟悉RM规则，绘制了工程采矿比赛的程序流程图。

**1.14**  Simulink编程 **开 幕 雷 击** ，研究了一整天环境配置以及控GPIO的办法，可算是把代码写出来了。

**1.15**  使用Simulink写了定时器中断的代码，CAN通信环回模式程序正在编写中。

**1.16**  查阅相关资料，试图解决CAN_IT模块无法识别配置的情况。

**1.17**  参照Sinulink的STM32库中的Demo写出了CAN通信环回模式的代码，代码可以生成，但是Simulink在编译时会报错。