#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char **argv) {
  doctest::Context context;

  context.setOption("abort-after", 5);
  context.setOption("order-by", "name");

  context.applyCommandLine(argc, argv);

  context.setOption("no-breaks", true);

  int res = context.run();

  if (context.shouldExit()) {
    return res;
  }

  return res;
}