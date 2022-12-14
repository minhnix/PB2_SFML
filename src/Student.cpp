#include "../header/Student.h"

using namespace std;

Student::Student()
{
  this->id = "";
  this->name = "";
}

Student::Student(string id, string name)
{
  this->id = id;
  this->name = name;
}

Student::~Student()
{
}
pair<string, string> *Student::getAll()
{
  static pair<string, string> data[10];
  data[0] = make_pair("length", "2");
  data[1] = make_pair("id", id);
  data[2] = make_pair("name", name);
  return data;
}
string Student::getId()
{
  return id;
}
string Student::getName()
{
  return name;
}
void Student::setId(string id)
{
  this->id = id;
};
void Student::setName(string name)
{
  this->name = name;
}
bool Student::operator==(const Student &s)
{
  return (id == s.id);
}
ostream &operator<<(ostream &cout, const Student &student)
{
  return cout << "id = " << student.id << "\nname = " << student.name << endl;
}