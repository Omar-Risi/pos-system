#include "utils/data.h"
#include "utils/service.h"
#include "menus/welcome-menu.h"

using namespace std;
int main() {

  Database db;
  Service::registerDatabase(&db);

  db.add("products", new Table());

  WelcomeMenu welcomeMenu;
  welcomeMenu.open();

  return 0;
}
