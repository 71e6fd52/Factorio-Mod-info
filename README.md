# Factorio-Mod-info
## 简介
Factorio-Mod-info 是一个可以获取 Factorio Mod 信息的库。
## 安装
### Arch Linux
在 Arch Linux 的 aur 中有 [Factorio-Mod-info-git](https://aur.archlinux.org/packages/Factorio-Mod-info-git/)
### 其他 Linux
安装你需要 [xmake](https://github.com/tboox/xmake)，[Boost](http://www.boost.org/) 和 [avhttp](https://avplayer.org/avhttp.html)，因为 [mods.factorio.com](https://mods.factorio.com) 需要 https，所以还需要 openssl。

安装完依赖后只需要
```bash
xmake i
```
## 例子
获取 Pushbutton 最新版的下载地址。
```c++
#include <mod-info.hpp>
#include <iostream>

int main()
try
{
	factorio::mod::info a("pushbutton");
	std::cout << a.download_url() << std::endl;
}
DA_MAIN_CATCH_EXCEPTION
```
或者分离开来
```c++
#include <mod-info.hpp>
#include <iostream>

int main()
try
{
	factorio::mod::info a;
	a.read_name("pushbutton");
	std::cout << a.download_url() << std::endl;
}
DA_MAIN_CATCH_EXCEPTION
```
还可以指定 Factorio 版本：
```c++
#include <mod-info.hpp>
#include <iostream>

int main()
try
{
	factorio::mod::info a("pushbutton");
	std::cout << a.download_url("0.14") << std::endl;
}
DA_MAIN_CATCH_EXCEPTION
```
## 接口
### 载入
| 函数 | 简介 |
| ---- | ---- |
| info() | 默认构造函数 |
| info(std::string name) | 构造时载入 Mod 信息，name 为 Mod 名 |
| void read_name(std::string name) | 以 Mod 名读取信息（如：rso-mod） |
| void read_full_name(std::string name) | 以 Mod 完整名（"作者名/Mod 名"）读取（如：orzelek/rso-mod） |
| void read_url(std::string url) | 从 URL 读取 Mod 信息（不一定为 mods.factorio.com，只要在 html.body.script 中存着 json 数据） |
### 读取信息
| 函数 | 读取内容 |
| ---- | -------- |
| int id() | id（如 rso-mod 为 87644） |
| std::string name() | Mod 名（如 Resource Spawner Overhaul 为 rso-mod ） |
| std::string title() | 标题（如 rso-mod 为 Resource Spawner Overhaul ） |
| std::string homepage() | 主页 |
| std::string github_path() | 源码 |
| std::string summary() | 简介 |
| std::string description() | 完整介绍 |
| std::string owner() | 作者 |
| std::string license_name() | 许可证名 |
| std::string license_url() | 许可证地址 |
| std::unordered_set&lt;int> id_list() | 所有发布 的 ID |
### 发布相关
这些函数都有三个版本，`type fun()`,`type fun(int id)`,`type fun(std::string factorio_version)`。

分别读取最新的发布、指定 ID 的发布、指定 Factorio 版本的发布。

| 函数名 | 读取内容 |
| ------ | -------- |
| download_url | 下载地址 |
| version | Mod 版本 |
| factorio_version | 支持的 Factorio 版本 |

