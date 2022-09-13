# c8t6_cpp_ver1
c8t6 programme in cpp mode

取消掉了argCount的传输，即从第二位开始就是参数列表，因为我们可以预先设定好每个指令的参数个数，argList的最大长度为4，目前看来是用不到的。

receiveBuff[]={command,argList[0],argList[1],...};

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


