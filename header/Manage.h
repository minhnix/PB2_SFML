#include "Computer.h"
#include "Student.h"
#include "Record.h"
#include "List.h"
#include "Database.h"

using namespace std;
using namespace rapidjson;

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
  void Create();
  void Update();
  void Delete();
  void Register();
  void Unregister();
  void ShowComputer(int index);
  void ShowAllComputer();
  void ShowTime();
  void ShowC(int index); // in thoi gian su dung 1 may chỉ định
  void ShowTotalTime();  // in thoi gian su dung tat ca cac may
  void showInfoAtTime();
};
