#include "Computer.h"
#include "Student.h"
#include "Record.h"
#include "List.h"
#include "Database.h"

using namespace std;
using namespace rapidjson;

struct notification
{
  string msg;
  int posX, posY;
  int code = 0;
};

class Manage
{
public:
  List<Student> listStudent;
  List<Computer> listComputer;
  List<Record> listRegister;
  Database<Student> dbStudent;
  Database<Computer> dbComputer;
  Database<Record> dbRegister;

public:
  Manage();
  ~Manage();
  notification Create(string id, string name);
  notification Update(string id, string name);
  notification Delete(string id);
  notification Register(int i, string id, string name);
  notification Unregister(string id);
  void ShowComputer(int index);
  void ShowAllComputer();
  void ShowTime();
  void ShowC(int index); // in thoi gian su dung 1 may chỉ định
  void ShowTotalTime();  // in thoi gian su dung tat ca cac may
  void showInfoAtTime();
};
