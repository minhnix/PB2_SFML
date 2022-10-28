#include "../header/Computer.h"

using namespace std;

Computer::Computer(/* args */)
{
  id = "";
  name = "";
  timeUsed = 0;
  idStudent = "";
  status = "not_using";
}
Computer::Computer(string id, string name, string status, string idStudent, long long timeUsed)
{

  this->id = id;
  this->name = name;
  this->status = status;
  this->idStudent = idStudent;
  this->timeUsed = timeUsed;
}

Computer::~Computer()
{
}
pair<string, string> *Computer::getAll()
{
  static pair<string, string> data[10];
  data[0] = make_pair("length", "5");
  data[1] = make_pair("id", id);
  data[2] = make_pair("name", name);
  data[3] = make_pair("status", status);
  data[4] = make_pair("idStudent", idStudent);
  data[5] = make_pair("timeUsed", to_string(timeUsed));
  return data;
}
string Computer::getId()
{
  return id;
}
string Computer::getName()
{
  return name;
}
string Computer::getStatus()
{
  return status;
}
string Computer::getIdStudent()
{
  return idStudent;
}
long long Computer::getTimeUsed()
{
  return timeUsed;
}
void Computer::setId(string id)
{
  this->id = id;
};
void Computer::setName(string name)
{
  this->name = name;
}
void Computer::setStatus(string status)
{
  this->status = status;
}
void Computer::setIdStudent(string idStudent)
{
  this->idStudent = idStudent;
}
void Computer::setTimeUsed(long long timeUsed)
{
  this->timeUsed = timeUsed;
}
bool Computer::operator==(const Computer &computer)
{
  return (id == computer.id);
}
ostream &operator<<(ostream &cout, const Computer &computer)
{
  return cout << "Id = " << computer.id << "\nName = " << computer.name << endl;
}