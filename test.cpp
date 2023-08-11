class A {
public:
  int test() const { // Declare the member function as const
      return 1;
  }
};

int main() {
  const A a;
  a.test();
  return 0;
}