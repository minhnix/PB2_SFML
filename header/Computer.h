#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

class Computer
{
private:
  string id;
  string name;
  string status;
  long long timeUsed;
  string idStudent;

public:
  Computer(/* args */);
  Computer(string id, string name, string status, string idStudent, long long timeUsed);
  ~Computer();
  pair<string, string> *getAll();
  string getId();
  string getName();
  string getStatus();
  string getIdStudent();
  long long getTimeUsed();
  void setId(string id);
  void setName(string name);
  void setTimeUsed(long long timeUsed);
  void setStatus(string status);
  void setIdStudent(string idStudent);
  bool operator==(const Computer &);
  friend ostream &operator<<(ostream &, const Computer &);
};
