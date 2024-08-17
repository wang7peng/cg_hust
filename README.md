图形编程内容：

1. 不使用引擎，直接基于 openGL 标准开发
2. 使用 glsl 语言


## 结构

- demo1  环境检查和显示界面
- demo2  显示图形
- demo3
- demo4


## 使用

**第 1 步** 先安装好 glfw

``` sh
git clone --depth 1 https://github.com/wang7peng/bash_scripts.git
cd bash_scripts
bash glfw3*

pkg-config --modversion glfw
```

cmake 使用了 pkg-config 工具来查找 `glfw` 库的位置，
在编译前需要配置 `$PKG_CONFIG_PATH` 安装好。
脚本里用 `--prefix` 修改了安装的位置，不是默认的 `/usr/local` 

> 不推荐用 `apt` 直接安装 `libglfw3-dev` ，版本不新

**第 2 步** GLAD 位置平路径配置。
将 `include` 里的两个目录（glad + KHR）放到公共位置。

``` sh
sudo cp -r include /usr/local/include
```

**第 3 步** 编译 cmake 运行程序

``` sh
cd demo2
cmake -B build .
cmake --build build # make

cd build
./xxx
```

进入到具体 demo 中, 在当前位置新建了一个 `build` 目录，编译产生的所有内容都在里面。

