#pragma once

#include <bits/stdc++.h>

using namespace std;

// Сложение производим обычным столбиком (как мы это делаем вручную на бумажке)

namespace lec9 {

  template<int Base = 1000 * 1000 * 1000, int BaseLen = 9>
  struct BigInt {
    vector<int> lnum;

    BigInt() {
    }

    // ############################## ЧТЕНИЕ ЧИСЛА ################################################
    //
    // При чтении длинного числа нужно помнить, что цифры записываются в обратном порядке.
    // Но в случае системы исчисления большей 10, «десятичные цифры» внутри цифры большей системы исчисления идут в прямом порядке.
    // Например, число 12345678 в 100-ричной системе исчисления будет записано как: 78, 56, 34, 122.
    //
    // https://www.nextptr.com/tutorial/ta1217154594/cplusplus-stdstring_view-for-better-performance-an-example-use-case
    // https://www.modernescpp.com/index.php/c-17-avoid-copying-with-std-string-view
    BigInt(std::string_view sw) {
      // Считываем строку в string, и затем преобразовываем её в вектор:
      // 123456 -> |3456|12|
      // [start_pos, end_pos)
      for (int end_pos = static_cast<int>(sw.size()); end_pos > 0; end_pos -= BaseLen) {
        const size_t start_pos = (size_t)max(0, end_pos - BaseLen);
        const size_t n_of_chars = (size_t)end_pos - start_pos;
        const auto digit_str = sw.substr(start_pos, n_of_chars);
        int digit;
        // https://en.cppreference.com/w/cpp/utility/from_chars
        from_chars(begin(digit_str), end(digit_str), digit);
        lnum.push_back(digit);
      }
      // Если во входном числе уже могут быть лидирующие нули, то их после чтения можно удалить таким образом:
      while (!lnum.empty() && lnum.back() == 0) lnum.pop_back();
    }


    // ################################# СЛОЖЕНИЕ И ВЫЧИТАНИЕ ################################################
    // Сложение и вычитание работает за длину наибольшего числа.
    // Числа, которые встречаются в процессе вычислений, не превосходят по модулю 2 * base.
    // Значит в одной ячейке массива при использовании типа longint (int) можно хранить до 9 десятичных цифр
    // (то есть основание системы исчисления может быть до 10^9).


    // carry     111
    //         12345
    //       +   678
    //        --------
    //         13023    carry 1 carry 1 carry 1
    //
    //      50
    //    + 50
    //    -----
    //     100
    BigInt<Base, BaseLen> operator+(const BigInt<Base, BaseLen> &other) {
      BigInt<Base, BaseLen> result;
      /* carry - обозначает сколько у нас "в уме"
         при сложение младших цифр в уме у нас 0 */
      long long carry = 0;
      for (size_t i = 0; i < max(lnum.size(), other.lnum.size()) ||
                         carry; ++i) { // || carry - если после сложения остался еще перенос, то нужно добавить еще одну цифру
        if (i < lnum.size())
          carry += lnum[i];
        if (i < other.lnum.size())
          carry += other.lnum[i];
        result.lnum.push_back(carry % Base);
        carry = carry / Base;
      }

      return result;
    }


    //    1234
    //  -  165
    // ----------
    //      69          borrow 1 1
    // a-b, where a >= b
    BigInt<Base, BaseLen> operator-(const BigInt<Base, BaseLen> &other) {
      BigInt<Base, BaseLen> result;
      int borrow = 0;
      for (size_t i = 0; i < max(lnum.size(), other.lnum.size()); ++i) {
        // может получиться отрицательное число
        // Пример 1000 - 3000
        if (i < lnum.size())
          borrow += lnum[i];
        if (i < other.lnum.size())
          borrow -= other.lnum[i];
        // borrow = -2000
        // Как я понимаю нам нужно получить положительное число, которое мы запишем в ячейку ответа
        // И здесь мы используем трюк предложенный Станкевичем:
//        1. X mod Y to get answ in [0,Y) where Y > 0 x can be positive/negative
//        X mod Y in (-y,y)
//        ( (X mod Y) + Y ) mod Y in [0,Y)
        result.lnum.push_back((borrow + Base) % Base); // 8000;
        // Если при вычитании двух цифр результат получается отрицательным, то мы занимаем единицу из старшего разряда.
        borrow = (borrow + Base) / Base - 1; // 8000 / 10000 - 1 == -1 (мы взяли единичку из старшего разряда)
      }
      // В отличие от сложения количество цифр в разности может уменьшиться,
      // поэтому нужно будет пересчитать количество цифр.
      // Здесь мы после выполнения вычитания удаляем лидирующие нули,
      // чтобы поддерживать предикат о том, что таковые отсутствуют.
      while (result.lnum.size() > 1 && result.lnum.back() == 0)
        result.lnum.pop_back();
      return result;
    }

    // ################################### Сравнение чисел ############################################
    // Первое на что мы обратим внимание, когда будем сравнивать числа, будет количество цифр в них.
    // - Если количество цифр различно, то больше то из них, которое содержит  больше цифр.
    // - Если количество цифр одинаково, то нужно сравнивать, начиная со старшей цифры.
    //   При обнаружении первого различия (т. е. самая старшая цифра, в которой есть различие),
    //   можно определить какое из чисел больше.
    // - Если два числа не имеют различий, то они равны.

    bool operator<(const BigInt<Base, BaseLen> &other) const {
      if (lnum.size() != other.lnum.size()) return lnum.size() < other.lnum.size();

      for (int i = static_cast<int>(lnum.size())-1; i >= 0; --i) {
        if (lnum[i] != other.lnum[i]) return lnum[i] < other.lnum[i];
      }
      return false;
    }

    bool operator==(const BigInt<Base, BaseLen> &other) const {
      if(lnum.size() != other.lnum.size()) return false;
      for(int i = 0; i < lnum.size();++i)
        if(lnum[i] != other.lnum[i]) return false;
      return true;
    }

    // ############################ УМНОЖЕНИЕ ##################################
    // Умножение длинного на короткое
    // Умножает длинное a на короткое b (b < base)
    BigInt<Base, BaseLen> operator*(int num) {
      BigInt<Base, BaseLen> result;
      long long carry = 0; // long long - чтобы избежать переполнения
      for (int i = 0; i < lnum.size() ||
                      carry; ++i) { // || carry -  } /*Если после умножения остался еще перенос, то нужно добавить еще цифру.*/
        // (Примечание: способ дополнительной оптимизации.
        // Если скорость работы чрезвычайно важна, то можно попробовать заменить два деления одним:
        // посчитать только целую часть от деления (в коде это переменная carry),
        // а затем уже посчитать по ней остаток от деления (с помощью одной операции умножения).
        // Как правило, этот приём позволяет ускорить код, хотя и не очень значительно.)
        //
        // From: http://e-maxx.ru/algo/big_integer
        //        В примечании по производительности вы предлагали заменить два деления делением и умножением
        //        А можно ли просто использовать "div" или "ldiv" из "stdlib.h"? Они ищут одновременно и делимое, и остаток.
        //                Если я не ошибаюсь, это будет работать немного быстрее, чем предложенный вам вариант.
        if (i < lnum.size()) // !!!! we can ran out of digits in big_int but still have a carry!!!
          carry += lnum[i] * 1LL * num; // * 1LL - чтобы избежать переполнения, при умножении двух чисел типа int
        result.lnum.push_back(carry % Base);
        carry /= Base;
        // Можно использовать вместо
        // c[i+j] = int (cur % base);
        //carry = int (cur / base);
        //следующее:
        //carry = int (cur / base);
        //c[i+j] = int (cur - carry * base);
        //
        //У меня работает немного быстрее
        // Да, такой приём есть, он обычно действительно немного ускоряет.
        // Только в произведении carry и base надо не забыть умножить на 1LL, чтобы не произошло переполнения типа int.
      }
      // Здесь мы после выполнения деления удаляем лидирующие нули, чтобы поддерживать предикат о том, что таковые отсутствуют.
      // Мой вопрос: какие лидирующие нули здесь могут быть, ответ (http://e-maxx.ru/algo/big_integer):
      // Длинное число умножить на ноль, например.

      while (!result.lnum.empty() && result.lnum.back() == 0)
        result.lnum.pop_back();

      return result;
    }

    // Умножение двух длинных чисел
    //
    //         12345
    //       *   678
    //        --------
    //         98760
    //     +  86415
    //       74070
    //      -----------
    //       8369910
    // 1. Итоговое число имеет цифр = цифр в первом числе + цифр во втором
    //
    //
    BigInt<Base, BaseLen> operator*(const BigInt<Base, BaseLen> &other) {
      BigInt<Base, BaseLen> result;
      result.lnum.resize(lnum.size() + other.lnum.size());
      // a x b
      for (size_t i = 0; i < lnum.size(); ++i) { // b
        long long carry = 0;
        for (int j = 0; j < (int) other.lnum.size() || carry; ++j) {  // a
          long long current = result.lnum[i + j] + carry;
          if (j < other.lnum.size())
            current += lnum[i] * 1LL * other.lnum[j]; // * 1LL - to avoid overflow
          result.lnum[i + j] = current % Base;
          carry = current / Base;
        }
      }
      while (!result.lnum.empty() && result.lnum.back() == 0)
        result.lnum.pop_back();
      return result;
    }

    // ############################ ДЕЛЕНИЕ ######
    // Деление длинного на короткое
    //
    //    В младших классах в школе, все мы так же изучали деление столбиком.
    //    Мы будем рассматривать деление на короткое число b.
    //    При делении столбиком сначала выписывается старшая цифра, эту цифру делят на b.
    //    Частное дописывают к результату, а остаток пишут ниже.
    //    После этого к остатку приписывают следующую цифру, полученное значение делят на b.
    //    Аналогично, частное дописывают к ответу, а остаток пишут ниже. Процесс продолжается пока все цифры не будут использованы.
    //
    //    4531  | 7
    //    42     ------
    //    ----  | 647
    //    33
    //    28
    //    ----
    //    51
    //    49
    //    ---
    //    2
    //    Остаток, к которому уже нельзя приписать цифру, будет остатком от деления.
    BigInt<Base, BaseLen> operator/(int num) {
      BigInt<Base, BaseLen> result;
      int remainder = 0; // обозначает текущий остаток, к которому будет приписана очередная цифра
      /*цикл от старших цифр к младшим*/
      for (int i = (int) lnum.size() - 1; i >= 0; --i) {
        remainder = remainder * Base + lnum[i]; //приписывание очередной цифры
        result.lnum.push_back(remainder / num); // //запись частного в результат
        remainder = remainder % num; //пересчет остатка
      }
      // Так как мы идем от старших рязрядов к младьшим, а храним в обратном порядке - то нужно полученный массив развернуть
      reverse(result.lnum.begin(), result.lnum.end());
      /*Частное может содержать меньше цифр,
        поэтому нужно при необходимости уменьшить количество цифр*/
      while (!result.lnum.empty() && result.lnum.back() == 0) result.lnum.pop_back();
      return result;
    }

    /*функция делит число a на короткое число num и возвращает остаток от деления*/
    std::pair<BigInt<Base, BaseLen>, long long> operator%(int num) {
      long long remainder = 0;
      BigInt<Base, BaseLen> result;
      for (int i = (int) lnum.size() - 1; i >= 0; --i) { // идем от старших числе к младшим
        remainder = remainder * 1LL * Base + lnum[i]; //приписывание очередной цифры
        result.lnum.push_back(remainder / num); //запись частного в результат
        remainder %= num; // пересчет остатка
      }
      std::reverse(begin(result.lnum), end(result.lnum));
      return {result, remainder};
    }

    operator string() const {
      // Для того, чтобы вывести число, записанное в десятичной системе исчисления
      // достаточно последовательно вывести цифры последовательно, начиная со старшей.
      // Если число записано в системе исчисления 10K, то это не совсем верно.
      // Число 109 в 100-ричной системе исчисления состоит из двух цифр: 1 и 9.
      // Поэтому нужно быть внимательным при выводе цифр состоящих из маленького количества цифр,
      // так как к таким цифрам при выводе необходимо дописать лидирующие нули.
      // Обратите внимание, что к самой первой цифре приписывать лидирующие нули не нужно.
      stringstream ss;
      // Чтобы не было 0123 0004, а было 123 0000 (нет лидирующих нулей)
      // Вывод разделен на две части
      // Выводим старший разряд
      if (lnum.empty()) ss << "0";
      else ss << lnum.back();


      //    (здесь небольшой тонкий момент: нужно не забыть записать приведение типа (int),
      //    поскольку в противном случае число a.size() будут беззнаковым,
      //    и если a.size() <= 1, то при вычитании произойдёт переполнение)
      for (int j = static_cast<int>(lnum.size()) - 2; j >= 0 && lnum.size() > 1; --j)
        // выводим остальные, последний (младший разряд будет дополнен нулями)
        // иначе если бы у нас было число 0123 0004 - то без дополнения нулями вывелось бы 123 4,
        // а нужно 123 0004
        ss << setw(BaseLen) << setfill('0') << lnum[j];
      return ss.str();
    }
  };


  // Сначала мы просто выводим самый последний элемент вектора (или 0, если вектор пустой),
  // а затем выводим все оставшиеся элементы вектора, дополняя их нулями до 9 символов:
  template<int Base, int BaseLen>
  ostream &operator<<(ostream &out, const BigInt<Base, BaseLen> &bi) {
    out << static_cast<string>(bi);
    return out;
  }
}