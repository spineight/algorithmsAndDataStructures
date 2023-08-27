// refs
// http://e-maxx.ru/algo/stacks_for_minima
// https://informatics.mccme.ru/mod/statements/view.php?id=33285#1

// tasks:
// https://informatics.mccme.ru/mod/statements/view3.php?id=8755&chapterid=1007#1
// https://informatics.mccme.ru/mod/statements/view3.php?id=33285&chapterid=412#1


namespace lec1 {
/**
*  Стэк основанный на массиве фиксированной длины.
*/
  template<size_t MAX_SIZE /**< вместимость стэка */>
  struct StackArrayBased {
    StackArrayBased() : sp(-1) {}

    int sp; /**< указывает на последний элемент в стеке. Если стэк пуст == -1*/
    int s[MAX_SIZE];

    bool empty() const { return sp == -1; }

    void push(int x) {
      ++sp;
      s[sp] = x;
    }

    int back() const {
      return s[sp];
    }

    void clear() { sp = -1; }

    void pop() {
      sp--;
    }

    size_t size() { return sp + 1; }
  };
}