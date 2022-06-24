#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace lec9::practice {

  template<int Base = 1000 * 1000 * 1000, int BaseLen = 9>
  struct BigInt {
    vector<int> lnum;

    BigInt() {
    }

    // ############################## ЧТЕНИЕ ЧИСЛА ################################################

    BigInt(std::string_view sw) {
      for(int endpos = (int)sw.size(); endpos > 0; endpos -= BaseLen) {
        const int startpos = std::max(0, endpos - BaseLen);
        const int nOfChars = endpos - startpos;
        int num{0};
        from_chars(&sw[startpos], &sw[startpos]+nOfChars, num);
        lnum.push_back(num);
      }
    }


    // ################################# СЛОЖЕНИЕ И ВЫЧИТАНИЕ ################################################
    BigInt<Base, BaseLen> operator+(const BigInt<Base, BaseLen> &other) {
      BigInt<Base, BaseLen> result;
      int carry = 0;
      for(int i = 0; i < std::max(lnum.size(), other.lnum.size()) || carry; ++i) {
        if(i < lnum.size())
          carry += lnum[i];
        if(i < other.lnum.size())
          carry += other.lnum[i];
        result.lnum.push_back(carry % Base);
        carry /= Base;
      }
      return result;
    }

    BigInt<Base, BaseLen> operator-(const BigInt<Base, BaseLen> &other) {
      BigInt<Base, BaseLen> result;
      int borrow = 0;
      for(int i = 0; i < std::max(lnum.size(), other.lnum.size()); ++i) {
        if(i < lnum.size())
          borrow += lnum[i];
        if(i < other.lnum.size())
          borrow -= other.lnum[i];
        result.lnum.push_back((borrow+ Base) % Base);
        borrow = (borrow + Base) / Base - 1;
      }
      while(!result.lnum.empty() && result.lnum.back() == 0) result.lnum.pop_back();
      return result;
    }

    // ################################### Сравнение чисел ############################################
    bool operator<(const BigInt<Base, BaseLen> &other) const {
      if(lnum.size() != other.lnum.size()) return lnum.size() < other.lnum.size();
      for(int i = lnum.size()-1; i >= 0; --i) {
        if(lnum[i] != other.lnum[i]) return lnum[i] < other.lnum[i];
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
      int carry = 0;
      for(int i = 0; i < lnum.size() || carry; ++i) {
        if(i < lnum.size())
          carry += lnum[i] * num;
        result.lnum.push_back(carry % Base);
        carry /= Base;
      }
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
      result.lnum.resize(lnum.size() + other.lnum.size(),0);
      for(int i = 0; i < lnum.size(); ++i) {
        long long carry = 0;
        for(int j = 0; j < other.lnum.size() || carry; ++j) {
          long long current = result.lnum[i+j] + carry;
          if(j < other.lnum.size())
            current += lnum[i] * 1ll * other.lnum[j];
          result.lnum[i+j] = current % Base;
          carry = current / Base;
        }
      }
      while(!result.lnum.empty() && result.lnum.back() ==0) result.lnum.pop_back();
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
      int remainder{0};
      for(int i = lnum.size()-1; i >=0; --i) {
        remainder = remainder * Base + lnum[i];
        result.lnum.push_back(remainder / num);
        remainder %= num;
      }
      std::reverse(begin(result.lnum), end(result.lnum));
      while(!result.lnum.empty() && result.lnum.back() == 0) result.lnum.pop_back();
      return result;
    }

    /*функция делит число a на короткое число num и возвращает остаток от деления*/
    std::pair<BigInt<Base, BaseLen>, long long> operator%(int num) {
      BigInt<Base, BaseLen> result;
      long long remainder = 0;
      for(int i = lnum.size()-1; i >= 0; --i) {
        remainder = remainder * 1ll * Base + lnum[i];
        result.lnum.push_back(remainder / num);
        remainder %= num;
      }
      std::reverse(begin(result.lnum), end(result.lnum));
      while(!result.lnum.empty() && result.lnum.back() ==0) result.lnum.pop_back();
      return {result, remainder};
    }

    operator string() const {
      stringstream ss;
      if(lnum.empty()) ss << "0";
      else {
        ss << lnum.back();
        for(auto rit = lnum.rbegin()+1; rit != lnum.rend(); ++rit) {
          ss << setw(BaseLen) << setfill('0') << *rit;
        }
      }
     return ss.str();
    }
  };


  // Сначала мы просто выводим самый последний элемент вектора (или 0, если вектор пустой),
  // а затем выводим все оставшиеся элементы вектора, дополняя их нулями до 9 символов:
  template<int Base, int BaseLen>
  ostream &operator<<(ostream &out, const BigInt<Base, BaseLen> &bi) {
    out << string(bi);
    return out;
  }
}