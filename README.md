# ConvertZH 

#### NotePad++ for x64版本插件，工作中常用简繁体互转，但目前官方无，32位很少用直接64位。

#### 功能为简单的简繁互转。参考官网提供demo，使用c++。

## 安装方法：

#### ./ConvertZH/x64/Debug/ConvertZH.dll  复制到目录/plugins下(新建ConvertZH目录)，如下图

![内嵌图片](D:\3.Code\c++\ConvertZH\images\内嵌图片.png)

## 使用方法：

#### 1.快捷键：选择待转的文字,alt+t或alt+s

#### 2.插件->简繁体转换

## 编译方法--**推荐方法2**

### 方法1：使用批处理脚本
```bash
build_with_encoding.bat
```

### 方法2：使用Visual Studio
1. 打开 `ConvertZH.sln`
2. 选择 Debug x64 配置
3. 右键生成解决方案

### 方法3：命令行编译
```bash
# 设置UTF-8编码
set _CL_=/utf-8
set _CXX_=/utf-8

# 编译
msbuild ConvertZH.vcxproj /p:Configuration=Debug /p:Platform=x64 /p:CharacterSet=Unicode
```

## 文件说明

- `ConvertZH.vcxproj` - Visual Studio项目文件
- `ConvertZH.sln` - Visual Studio解决方案文件
- `ConvertZH.def` - DLL导出函数定义
- `build_with_encoding.bat` - 自动编译脚本

