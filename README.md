## LB_LEXER

Simple C language lexical analyzer.

Switch debug mode:

```console
$ export LB_DEBUG=ON # on
$ export LB_DEBUG=OFF #off
```

### 伸手党警告

本人不卷保研，就算被算 0 分也没啥影响。但是**抄作业者死妈，见一个举报一个**。

## 开发环境准备

操作系统：以 Debian 11 为例，其它发行版同理。

> Windows 参考[此处](https://github.com/microsoft/vcpkg#quick-start-windows)。

### 安装系统依赖

```console
$ sudo apt install cmake
```

### 安装包管理器 vcpkg

```console
$ mkdir ~/app
$ cd ~/app
$ git clone https://github.com/microsoft/vcpkg
$ ./vcpkg/bootstrap-vcpkg.sh
$ sudo ln -s ./vcpkg/vcpkg /usr/bin/vcpkg
```

### 安装依赖

```console
vcpkg install spdlog
```

### 配置 VSCode 环境

VSCode 需要安装 C/C++、CMake、CMake Tools 插件。（推荐直接安装全套插件 C/C++ Extension Pack）

`.vscode/settings.json` 追加如下配置：

```jsonc
{
    "cmake.buildArgs": [  "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake"],
    "cmake.configureArgs": [  "-DCMAKE_TOOLCHAIN_FILE:FILEPATH=$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake"],
    "C_Cpp.default.includePath": [
        "$VCPKG_PATH/installed/x64-linux/include",
    ],
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    "cmake.configureOnOpen": true,
}
```

其中 `$VCPKG_PATH` 替换为你安装的 vcpkg 的绝对目录路径，如 `/home/pluveto/app/`.

## 编译和运行

### 执行 CMake Configure

打开 VSCode 命令面板（<kbd>F1</kbd>），执行 `CMake Configure`.

### 执行编译脚本

`mr` 是编写好的编译、运行脚本。使用 `./mr` 执行。

> 如果权限不足，请 `$ chmod +x mr`

程序将会完成编译并运行。