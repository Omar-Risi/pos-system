#include "utils/data.h"
#include "utils/menu.h"
#include "utils/service.h"
#include <iostream>

using namespace std;
int main() {

  Database db;
  Service::registerDatabase(&db);

  return 0;
}
