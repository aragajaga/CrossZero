# <img src="https://github.com/Philosoph228/CrossZero/blob/master/res/icon.png" width="48"> CrossZero
Сетевая игра крестики-нолики.

[![Build Status](https://travis-ci.org/Philosoph228/CrossZero.svg?branch=master)](https://travis-ci.org/Philosoph228/CrossZero)

## Сборка
Для сборки требуются:
* библиотека SFML
* cmake

```
cmake ./
make
```

Если CMake не удалось найти установленный SFML, добавьте путь к нему в `CMAKE_PREFIX_PATH`. Например: ```-DCMAKE_PREFIX_PATH="C:\\SFML-2.5.1\\"```
> С CMake версии >3.12 больше нелья использовать `-DSFML_ROOT` https://cmake.org/cmake/help/git-stage/policy/CMP0074.html

## Лицензия
Код распространяется по лицензии GNU GPLv3. Текст лицензии Вы можете прочитать в файле LICENSE.
