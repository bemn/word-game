#include "console/Console.h"

int main() {
    std::wstring test;
    wcon >> test;
    wcon << test[0] << " test" << '\n';
}
