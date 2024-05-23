https://compscicenter.ru/courses/python/2015-autumn/classes/1364/

### Начало
https://youtu.be/5V7XG1mGiHc?si=lhs_CPlJ2myioRc-
Кто, когда и зачем придумал язык Python. Интерпретаторы языка. Синтаксис языка с высоты птичьего полёта. Интерактивная оболочка IPython.

### Всё, что вы хотели знать о функциях в Python
https://youtu.be/3fE_08eXyE4?si=o_j2mdEWg-AFCQfG
Синтаксис объявления функций. Упаковка и распаковка аргументов. Ключевые аргументы и аргументы по умолчанию. Распаковка и оператор присваивания. Области видимости, правило LEGB, операторы global и nonlocal. Функциональное программирование, анонимные функции. Функции map, filter и zip. Генераторы списков, множеств и словарей. Немного о PEP 8.

### Декораторы и модуль functools
https://youtu.be/h_B3O5jWMi4?si=VfNQsAAayisrbHCG
Синтаксис декораторов. Декораторы с аргументами, без аргументов. Примеры использования декораторов. Модуль functools.


## Строки, байты, файлы и ввод/вывод
https://youtu.be/7YIgaaaGpyA?si=T2SxJRXNy5-hOOX8
Строковые литералы и "сырые" строки. Строки и Юникод. Основные методы работы со строками. Модуль string. Байты. Кодировки. Файлы и файловые объекты. Методы работы с файлами. Модуль io.


## Встроенные коллекции и модуль collections
https://youtu.be/vne1p3huhew?si=yNzVL_EbKtfBn_7p
И снова встроенные коллекции: кортеж, список, множество, словарь -- обход в глубину, обзор методов, примеры. Почти всё про модуль collections: именованные кортежи, счётчики, defaultdict, OrderedDict.


## Классы 1
https://youtu.be/SJ8z-TF07s4?si=cAedOjTm6vq6J4Ao
Синтаксис объявления классов. Атрибуты, связанные и несвязанные методы, __dict__, __slots__. Статические методы и методы класса. Свойства, декоратор @property. Наследование, перегрузка методов и функция super. Декораторы классов. Магические методы.

## Исключения и менеджеры контекста
https://youtu.be/_vxcRfjyfgk?si=GodjsLWjZmDVnlok
Исключения, зачем они нужны и как их обрабатывать. Встроенные исключения и базовые классы BaseException и Exception. Операторы try...except..else..finally. Менеджеры контекста и модуль contextlib.

## Итераторы, генераторы и модуль itertools
https://youtu.be/snJhrhD9Sg8?si=JsfKnELhfcefSjFR
Два протокола итераторов: _next_ + _iter_ и __getitem__. Итераторы и цикл for, а также операторы in и not in. Генераторы, оператор-выражение yield. Генераторы как: итераторы, сопрограммы, менеджеры контекста. Модуль itertools.

## Модули, пакеты и система импорта
https://youtu.be/SuRVWRRjb_U?si=eyv3vQcvhlc7a_oc
Модули. Операторы import и from ... import. Пакеты. Относительный и абсолютный импорт. __init__-фасад. И снова оператор import --- обход в глубину.


## Классы 2
https://youtu.be/mTp2pLEoDaI?si=fQ9uZaMw5D6MzWPS
Дескрипторы: что-как-зачем. Конструктор __new__, класс type и метаклассы. Наследование встроенных типов. Модули abc и collections.abc.

## Тестирование
https://youtu.be/y78VXTI8PRQ?si=RKpxT4R9ehDf-rdj
Зачем тестировать? Тестирование в интерпретаторе и доктесты. Модуль unittest. Пакет py.test --- на порядок лучше. Тестирование свойств и пакет hypothesis.


## Быстрее, Python, ещё быстрее
https://youtu.be/-lMiAKKyLFI?si=Ny5r0fKCXs_kAF4a
Измерение времени работы кода на Python с помощью модулей timeit, cProfile и line_profiler. Немного о NumPy. JIT и AOT компиляция кода на Python на примере Numba и Cython.


## Многопоточность и GIL
https://youtu.be/nR8WhdcRJwM?si=KAajsdn6wawmF07r
Модули threading, queue и concurrent.futures. Использование потоков для параллельных вычислений на Python. GIL. Параллельность и конкурентность. Модуль asyncio. Модуль multiprocessing.

