/* Memory leak checker */
#ifdef _DEBUG
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#endif /* _DEBUG */

#include <conio.h>
#include <cmath>

#include <iomanip>
#include <iostream>
#include <vector>
#include <deque>

#include <windows.h>
#include <gtest/gtest.h>

extern "C" {
#include "../C data structrures/trees/red_black_leaning_left.h"
#include "../C data structrures/hash/hash_table_double.h"
}

int main( int argc, char **argv ) {
  SetDbgMemHooks();

  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();

  _getch();
  return 0;
}

TEST( samples, sample1 ) {
  hash_table_double Table;
  initTableDouble(&Table, 16, 17, 29);

  addTableDouble(&Table, "Boo-Yah");
  addTableDouble(&Table, "Look at it go!");
  addTableDouble(&Table, "Roll out the barrel");
  addTableDouble(&Table, "Feel it in your bones!");

  clearTableDouble(&Table);
}

TEST( collision, test1 ) {
  hash_table_double Table;
  initTableDouble(&Table, 16, 17, 29);

  addTableDouble(&Table, "One");
  addTableDouble(&Table, "Two");
  addTableDouble(&Table, "Three");
  addTableDouble(&Table, "Forever");
  addTableDouble(&Table, "I");
  addTableDouble(&Table, "Will");
  addTableDouble(&Table, "Not");
  addTableDouble(&Table, "Sleep");
  addTableDouble(&Table, "Never");
  addTableDouble(&Table, "Five");
  addTableDouble(&Table, "Six");
  addTableDouble(&Table, "Seven");
  addTableDouble(&Table, "Hate");
  addTableDouble(&Table, "Lover");
  addTableDouble(&Table, "I");
  addTableDouble(&Table, "Will");
  addTableDouble(&Table, "Wait");
  addTableDouble(&Table, "Forever");

  clearTableDouble(&Table);
}

TEST( deletions, test1 ) {
  hash_table_double Table;
  initTableDouble(&Table, 16, 17, 29);

  addTableDouble(&Table, "One");
  addTableDouble(&Table, "Two");
  addTableDouble(&Table, "Three");
  addTableDouble(&Table, "Forever");
  addTableDouble(&Table, "I");
  addTableDouble(&Table, "Will");
  addTableDouble(&Table, "Not");
  addTableDouble(&Table, "Sleep");
  addTableDouble(&Table, "Never");
  addTableDouble(&Table, "Five");
  addTableDouble(&Table, "Six");
  addTableDouble(&Table, "Seven");
  addTableDouble(&Table, "Hate");
  addTableDouble(&Table, "Lover");
  addTableDouble(&Table, "I");
  addTableDouble(&Table, "Will");
  addTableDouble(&Table, "Wait");
  addTableDouble(&Table, "Forever");

  deleteTableDouble(&Table, "Forever");
  deleteTableDouble(&Table, "One");
  deleteTableDouble(&Table, "Six");
  deleteTableDouble(&Table, "Seven");
  deleteTableDouble(&Table, "Hate");
  deleteTableDouble(&Table, "Lover");
  deleteTableDouble(&Table, "I");
  deleteTableDouble(&Table, "Will");
  deleteTableDouble(&Table, "Two");
  deleteTableDouble(&Table, "Wait");
  deleteTableDouble(&Table, "Forever");
  deleteTableDouble(&Table, "I");
  deleteTableDouble(&Table, "Will");
  deleteTableDouble(&Table, "Not");
  deleteTableDouble(&Table, "Sleep");
  deleteTableDouble(&Table, "Three");
  deleteTableDouble(&Table, "Never");
  deleteTableDouble(&Table, "Five");

  clearTableDouble(&Table);
}
