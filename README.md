# Nonogram

项目基于 [Qt](https://www.qt.io/) 框架制作。

关于 Nonogram 游戏的介绍参见 [Wikipedia](https://en.wikipedia.org/wiki/Nonogram) 。

## 说明

1. *build_inc.bat* 用于更新 build 号，应在编译步骤最开始执行，否则 build 号不会更新。该文件工作目录应为 `%{CurrentProject:Path}/tool` 。

2. *style* 目录下的 *styles* 文件夹需要放在编译后的 \*.exe 同级目录下，否则会出现样式错误。

3. 本程序采用 Qt 5.12.0 + MinGW 7.3.0 64bit 编译测试通过。由于文件编码问题，使用 MSVC 编译可能会出现中文不能正常显示的 BUG 。

4. 请在全英文无空格路径下编译，否则可能出错。

5. 如果游戏出现显示大小不正常（ DPI 显示问题），请右键单击应用程序->属性->兼容性，勾选“替代高 DPI 缩放行为”，再尝试运行。


## 已知 BUG

1. 某些情况下，在游戏界面点击返回，会出现主界面弹出但不能前置显示的问题（藏在其他窗口后面）。此时手动最小化窗口再最大化窗口即可解决问题。
