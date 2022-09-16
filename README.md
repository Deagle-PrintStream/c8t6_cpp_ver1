# c8t6_cpp_ver1
c8t6 programme in cpp mode

## NOTICE

1.取消掉了argCount的传输，即从第二位开始就是参数列表，因为我们可以预先设定好每个指令的参数个数，argList的最大长度为4，目前看来是用不到的。 

2.receiveBuff[]={command,argList[0],argList[1],...}; 

3.部分指令有多余的参数，目前还没有对应实现，可以忽略 

## 通信设想

| command | 原始uint8_t  | argList[0]  | argList[1] |
|  ----  | ----  |  :----:  | :----:  |
| errorCmd  | 0 | 0 | 0 |
| moveCmd | 1 | 运动方向direction_t | 运动速度uint8_t |
|  rotateCmd | 2  |  旋转方向direction_t |  旋转速度uint8_t |
| trimCmd  |  3 | 旋转方向direction_t  | 旋转速度uint8_t  |
| stopCmd  |  4 |  0 |  0 |
| pushCurlingCmd  |  5 |  0 |  0 |
|  armRaiseCmd | 6  | 移动方向上或者下status_t  |  移动距离uint8_t |
| detectCodeCmd  |  7 |  0 |  0 |
| detectCodeAns  |  8 |  是否检测到条形码status_t |  0 |
| reservedCmd  |  9 |  0 |  0 |
| testCmd  |  10 |  测试用参数uint8_t |  0 |

## 文件结构

| file .cpp/.h  | description  |
| :----:  | :---- |
| common  | 初始化类对象，调试命令，杂项函数，宏定义函数  |
| sensor  | sensor_t类定义,完全服务于tracer_t，单个传感器 |
| tracer  | tracer_t类定义，被patrol_t引用，单方向上的巡线模块 |
| patrol  | selector_t类定义，patrol_t类定义，74ls153的逻辑实现,平凡节点检测 |
| path  | 最高级的路径函数，包括右转，无巡线直线前进，回到基点等 |
| callback  | 时钟和通信的中断回调函数  |
| connectivity  | 和zet6的通信相关函数，为过渡方案，后期可能考虑整合到一个芯片上 |



## TODO:

1.条件等待函数的非宏定义实现，即利用函数指针 

2.指令的接收，即uart1的接收功能正常工作 

3.最高层次的巡线指令实现完成 
