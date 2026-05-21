#include "menus/login-menu.h"
#include "menus/welcome-menu.h"
#include "utils/data.h"
#include "utils/service.h"

using namespace std;
int main() {

  Database db;
  Service::registerDatabase(&db);

  db.add("products", new Table());

  LoginMenu loginMenu;

  bool isLoggedIn = loginMenu.open("admin", "admin123");

  if (isLoggedIn) {
    WelcomeMenu *welcomeMenu;
    welcomeMenu->open();
  }
  return 0;
}
