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
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../) 
```
Это что-то нужное, для красивой работы срипта (создает исполняемый файл в папке на уровень выше).

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
