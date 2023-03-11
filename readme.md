## 植物大战僵尸小游戏

- 此项目写于2021年3月23日-2021年6月8日。

- 该项目分为两部分：

  - 第一次和第二次课设（project1&2）为C++控制台界面，第二次在第一次基础上补充完善。
    - ![image-20230311191130285](C:\Users\zxy\AppData\Roaming\Typora\typora-user-images\image-20230311191130285.png)
    - 游戏主界面如图，主要部分是5*9的草坪，左侧为房屋的边界线。
    - 商店：此为游戏的默认状态，光标（此处光标不是控制台光标，而是指当前选择的草块，植物，铲子等相对位置）可以在植物栏中移动，可以翻页，空格键确认后若满足购买条件则进入种植模式。
    - 种植：光标可以在草坪间移动，种植成功则返回商店模式。购买状态下，选择的植物栏位置自动变为“取消种植”按钮，若想取消，则只需按↓键将光标移动到此按钮上，确认即可。
    - 铲除：与种植类似。特别地，在植物栏最右一列按→键可选中铲子，确认即可进入铲除状态。
    - 暂停：按esc键使游戏暂停，直到按下空格键才开始正常循环。注：只有在商店状态下才能暂停，也就是必须归还铲子或者种植完毕后按esc键才会起效。
    - 注：因为操作比原游戏要麻烦一点，所以植物的选择与种植可能会花费一点时间。如果打不过就在shopping模式下按回车键，按一次阳光+1000，不超过100000。
  - 第三次课设（project3）为图形化界面，使用QT制作。
    - ![image-20230311191555568](C:\Users\zxy\AppData\Roaming\Typora\typora-user-images\image-20230311191555568.png)
    - ![image-20230311191625959](C:\Users\zxy\AppData\Roaming\Typora\typora-user-images\image-20230311191625959.png)
    - ![image-20230311191643060](C:\Users\zxy\AppData\Roaming\Typora\typora-user-images\image-20230311191643060.png)
  - 控制台和图形界面两部分可各自独立运行互不相关，具体介绍在各自文件夹下的report.pdf。

- 注意事项

  - 游戏界面初始化尺寸为1600*1200，是按照2160\*1440的分辨率设定的。
  - 因为计算量较大，可能出现卡顿现象，因电脑而异。
  
  
  
  ![C:\Users\zxy\AppData\Roaming\Typora\typora-user-images\image-20230311191130285.png](C:\Users\zxy\Desktop\tb3335976836\1反.png)
  
  