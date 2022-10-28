#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

class Record
{
private:
  string id;
  string idComputer;
  string idStudent;
  long long registeredAt;
  long long unRegisteredAt;

public:
  Record(/* args */);
  Record(string idComputer, string idStudent, long long registeredAt, long long unRegisteredAt);
  ~Record();
  pair<string, string> *getAll();
  string getId();
  string getIdComputer();
  string getIdStudent();
  long long getRegisteredAt();
  long long getUnRegisteredAt();
  void setIdComputer(string idComputer);
  void setIdStudent(string idStudent);
  void setRegisterAt(long long registeredAt);
  void setUnRegisterAt(long long unRegisteredAt);
  bool operator==(const Record &);
  friend ostream &operator<<(ostream &, const Record &);
};
