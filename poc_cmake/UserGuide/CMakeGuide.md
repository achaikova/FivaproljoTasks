# CMake guide
```
cmake_minimum_required(VERSION 3.15) 
```
Этой версии вроде бы хватает, поэтому условимся использовать хотя бы ее.

```
project(hw_02) 
```
Название проекта, у нас всегда будет `fivaproljo`.

``` 
include_directories(include) 
```
Здесь указываются папки с заголовочными файлами, по умолчанию называем ее `include`.

``` 
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
```
Флаги для компиляции, по дефолты там установлены флаги `"-Wall -Wextra -Werror"` (устанавливаемые флаги пишутся в кавычках). 

```
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
endif()

if(LINUX)
   set(CMAKE_PREFIX_PATH "/home/daniel/Qt5.14.1/5.14.1/gcc_64") # for Daniel only
elseif(MACOSX)
   set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.14.1") # Any macOS
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
```
Кусок для `qt`, возможно, придется менять путь до файла...

``` 
SET(CMAKE_EXE_LINKE_FLAGS "-lncurses") 
```
Флаги для линковки.

** Сборка исполняемого файла. Синтакси следующий:
```
add_executable( OutputExecutableFileName
        srcFile1
	srcFile2
	srcFile3
	)
```
* `srcFile1` - относительный путь до файла из нынешней директории.
* Заголовочные файлы подключаются автоматически.
* Именно 4 пробела.
