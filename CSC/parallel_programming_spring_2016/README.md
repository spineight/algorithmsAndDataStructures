https://compscicenter.ru/courses/hp-course/2016-spring/classes/1719/


### Лекция 1. Введение (курс «Параллельное программирование»)
https://youtu.be/kbERSWTGtKw?si=dxDjNtrXRHIh1fQX
Тенденции развития вычислительных систем
Классификация параллельных систем: SIMD, MISD…, SMP, MPP
Современные высокопроизводительные системы: начиная от расширений SSE, через многоядерность к узлам кластеров
Понятия ускорения, эффективности
План курса

Лекция №1  в курсе "Параллельное программирование", весна 2016
Преподаватель курса: Евгений Леонидович Калишенко


### Лекция 2. Корректная работа с потоками
https://youtu.be/qA5XLTxmsP0?si=HpW3CBv_EFpX-zUJ

– Механизм запуска потока
– Корректное завершение потоков:
cancellation points (примеры кода в glibc)
interrupted exception
– Сравнение различных потоков (POSIX, boost/С++11, java)
– Проброс исключений между потоками

### Лекция 3. Примитивы синхронизации
https://youtu.be/kNWSciQtHEc?si=8kBgn_IDugUnQ0Th
Необходимость синхронизации: простые гонки данных
Реализация примитивов синхронизации: алгоритм булочника
Виды мьютексов:
рекурсивные/нерекурсивные
read/write
spin
futex
CAS-операции и атомики

### Лекция 4. Condition variables. Алгоритмы синхронизации
https://youtu.be/79d5WI5RTp8?si=UMpUe2ppQYGetxnY
Condition variables:
Пример на POSIX
Пример на Java
Алгоритмы синхронизации:
Грубая
Тонкая


### Лекция 5. Алгоритмы синхронизации
https://youtu.be/7aabRlVERPc?si=qUJOkiYduTyEfNgA

Алгоритмы синхронизации:
– Оптимистичная
– Ленивая
– Неблокирующая
Классы алгоритмов:
– lock-free
– wait-free
– lock-free алгоритм снятия снэпшота атомарных регистров

### Лекция 6. Ошибки || программирования
https://youtu.be/2A3Q0dA6Tlc?si=xBPgPL4AtDTG-5wV
Основные ошибки многопоточного программирования:
– Гонки данных (Data Race)
– Взаимная блокировка (Deadlock)
– Потерянный сигнал
Специфические ошибки:
– Реакция потока на сигнал
– Блокировки при fork многопоточных программ
– Проблема ABA
– Инверсия приоритетов

### Лекция 7. Атомарные снимки регистров
https://youtu.be/oq6krtEvCLA?si=x7k258JWbRp1_88F

Wait-free атомарный снимок регистров
Решение проблемы ABA на tagged pointers

### Лекция 8. Java.util.concurrent
https://youtu.be/zMj1Qi_N9Qc?si=t1PP-MjImHGMOFyi

Пример CAS и ORM
Пулы потоков
Контроль задач через Future
Потокобезопасные контейнеры

### Лекция 9. OpenMP и Intel TBB
https://youtu.be/_MKbLk6K_Tk?si=DZ9GtFZmobTZ0MMg
Обзор OpenMP:
параллельные секции
области видимости переменных
ограничения
Обзор Intel TBB:
алгоритмы
аллокаторы
деревья задач
особенности планирования (work stealing…)
flow graphs (параллель с BPEL)

### Лекция 10. Профилирование многопоточных приложений
https://youtu.be/d_3kCXSONWQ?si=K5Le95QvwuBVlO9W

Средства анализа производительности
Утилита time
Intel Parallel Studio
Valgrind (модули callgrind, cachegrind)
Пример поиска узких мест

### Лекция 11. Проблема видимости переменных. Устройство процессора
https://youtu.be/VcesAbhnGKU?si=uQ6o6UwzwzsAYtZK
Устройство процессора ** Store buffer ** Invalidate queue
Пример на протоколе MESI проблемы поздней видимости операций


### Лекция 12. Барьеры памяти. Модели памяти
https://youtu.be/kg0ZVbBdsMM?si=veZbHE1ygZCcjkJp
Барьеры памяти (store/load)
Acquire/release семантика
Модели памяти: Sequential consistency...
Перечисление барьеров памяти в C++ atomic
Необходимость volatile для Java
Пример ошибки в ядре ОС из-за отсутствия одного из барьеров
Случаи неявного применения барьеров памяти

https://habr.com/ru/articles/196548/

### Лекция 13. Шаблоны || программирования. Консенсус
https://youtu.be/C_v800s4Axs?si=gmz_W0MyhYKQM145

Структурные шаблоны:
Декомпозиция по задачам
Геометрическая декомпозиция
Recursive Data
Pipeline
Разное:
Double check
Local Serializer
Консенсус:
Консенсусное число RMW-регистров
Универсальность CAS-операций

### Лекция 14. Транзакционная память
https://youtu.be/HgRGGKqeod8?si=9qACfO37vAQtmsAj
Идея transactional memory:
Software transactional memory
Hardware transactional memory:
Преимущества и круг задач
Верификация || программ:
Model Checking

### Лекция 15. Асинхронный ввод/вывод
https://youtu.be/CBM2K0qdmOg?si=XKzlUTIgXU74684P
Блокирующий/неблокирующий
Синхронный (реактор)/асинхронный (проактор)
Преимущества асинхронной работы и реализация со стороны операционной системы
