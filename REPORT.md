## Обзор проекта

Становой Александр, Б05-822, консольный аналог [tileman.io](http://tileman.io/).

### Общая информация

Игра, которая будет написана, абсолитно аналогична [tileman.io](http://tileman.io/), но играться будет в консоли. Правила очень просты:

* Игра происходит на клетчатом поле `NxM`.
* Изначально игрок появляется в случайной незанятой точке.
* Необходимо захватить как можно большу территорию.
* Если вы выходите в свободную зону, то за вами образуется "след".
* Если вы наступите на свой след или на след противника, то вы проиграете.
* Если вы замкнули след обратно на свою территорию, то вся очерченая фигура становится захваченной.

Для лучшего понимания [лучше поиграть](http://tileman.io/).

### Обзор технологических решений

* Я решил использовать не систему сборки `Make` или `CMake`, а `Meson`. Причины:
  * Современная система сборки, учитывающая существующие недостатки у других систем. Пример: встроенный в `Cmake` `CTest` не умеет корректно передавать опции `qemu`, что я выяснил, пока делал репозиторий для задачи `advanced-1` в прошлом семестре по АКОС.
  * Хорошая нативная поддержка кросс-компиляции и кросс-тестирования.
  * Читабельный код системы.
  * В основе самого сборщика лежит `Ninja` - очень быстрая система сборки.
  * Я уже множество раз создавал и настраивал сборки на `CMake`, и хотелось попробовать нечто новое.
* `Doxygen`, хорошо подходящий для генерации документации C-кода.
* `Clang-Tidy` и `Clang-Format` для поддержки качества кода, в т.ч среди разных контрибьютеров в проекте (рассмотрел такой вариант в дальнейшем).

### Почему репозиторий называется GUDP?

Этот репозиторий предназначен **только** для Netcode, самой игры тут не будет по объективным причинам. Чуть позже я создам репозиторий для игры согласно плану проекта, а данный репозиторий станет third-party dependence.

### Почему для Netcode нужен отдельный репозиторий?

Нетворкинг в играх - задача невероятно трудная и нетривиальная, а с ростом числа именно онлайн игр даже рождаются проекты и [стартапы](https://www.networknext.com), призванные улучшать мультиплеерный опыт игроков в игре от производителя.

### Как это будет работать?

Я напишу об этом подробную документацию. Пока что небольшая часть есть в документации файла `packet.h` - это документация о том, какие именно пакеты будут посылаться. Описание, как они обрабатываются, еще будет.

Вообще говоря, сам мой Netcode основан на идеях [Глена Фидлера](https://gafferongames.com/post/reliable_ordered_messages/), если хочется узнать об этом заранее - прочтите цикл статей. Как эталонную имплементацию я рассматриваю [GameNetworkingSockets от Valve](https://github.com/ValveSoftware/GameNetworkingSockets).

### Какой минимум будет реализован к концу семестра и какие улучшения могут появится чуть позже?

Все эти хитрости не нужны для того, чтобы моя игра просто начала работать. Поэтому создание Reliable UDP for game networking - лишнее, но я напишу. Минимум - игра, в которой вы будете подключатся, запуская ее из командной строки с нужным `ip` и портом в качестве параметров, либо хостить игру, запуская клиент так же, но как сервер:

```
$ ./game create "121.0.0.1" "24535"
$ ./game connect "121.0.0.1" "24535"
```

Процесс игры представляется так (сделал на коленке, будет с цветом):

```
+--------------------+
|                    |
|      0...          |
|         .          |
|        ###         |
|        ###         |
|        ###         |
|                    |
|                    |
|                    |
+--------------------+
```

Возможные улучшения:

* Поддержка IPv6 (на уровне системы сборки).
* Поддержка Windows.
* O(1) на запрос клиента (требует реализации дополнительных структур данных).
* Сжатие: Хаффман, дельта-кодирование...
* OpenSSL с публичным шифрованием пакетов.
* Расширение возможностей библиотеки: гарантированные сообщения (их посылку нужно повторять), чат (такие сообщения являются очень длинными).

### План

* 1 неделя: написание сокетов для Linux, описание пакетов.
* 2 неделя: имплементация коммуникации клиент-сервер.
* 3 неделя: написание кода для тестирования основных функций библиотеки.
* 4 неделя: создание репозитория игры. Создание ее архитектуры.
* 5 неделя: написание функционала игры для однопользовательской игры.
* 6 неделя: работоспособная игра.
* 7-8 неделя: третья контрольная точка, добавление улучшающего функционала.

### Дополнительная информация

Репозиторий приватный, следовательно, средств CI и GitHub Pages не будет на все время работы. Придется клонировать репозиторий и, следуя инструкциям из `BUILDING.md`, создавать документацию (точка входа - `docs/index.html`) и тестировать.

# Информация для дальнейшей поддержки библиотеки

### Используемые паттерны проектирования

- Dependency injection - структуры `Address`, `Socket`, `Data`, `Packet`...

### Правила написания библиотеки

- Все функции, описанные в интерфейсе, возвращают `RETCODE`, если исполнение вариантивно (может случится ошибка или успех может быть различным).
- Следует сокращать код. Например, используйте макрос `THROW_OR_CONTINUE` чтобы вернуть код возврата или продолжить исполнение.
- Все значения, передаваемые функции по ссылке, либо не меняются (ошибка выполнения), либо изменяются на валидные (корректное исполнение).
