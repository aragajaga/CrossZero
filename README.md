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

Если CMake не удалось найти установленный SFML, задайте его вручную: ```-SFML_INCLUDE_DIR=<путь_к_заголовкам> -SFML_LIBRARIES=<путь_к_библиотекам>```

## Лицензия
Код распространяется по лицензии GNU GPLv3. Текст лицензии Вы можете прочитать в файле LICENSE.