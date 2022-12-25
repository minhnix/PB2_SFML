#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/filewritestream.h"
#include "../rapidjson/pointer.h"
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <ctime>
#include <unordered_map>

using namespace rapidjson;
using namespace std;

template <class T>
class Database
{
private:
  const char *path;
  Document db;

public:
  Database(const char *);
  ~Database();
  int getTotalCol();
  void writer();
  void Create(T);
  string GetStringDB(int index, const char *field);
  long long GetLLDB(int index, const char *field);
  void Update(int index, const char *field, const char *value);
  void Update(int index, const char *field, long long value);
  void Delete(int index);
};
template <class T>
Database<T>::Database(const char *path)
    : path(path)
{
  FILE *fi = fopen(path, "rb");
  char DB[1000000];
  FileReadStream input(fi, DB, sizeof(DB));
  db.ParseStream(input);
  fclose(fi);
}
template <class T>
Database<T>::~Database()
{
}
template <class T>
int Database<T>::getTotalCol()
{
  return db.GetArray().Size();
}
template <class T>
void Database<T>::writer()
{
  FILE *fo = fopen(path, "wb");
  char writeBuffer[1000000];
  FileWriteStream os(fo, writeBuffer, size(writeBuffer));
  Writer<FileWriteStream> writer(os);
  db.Accept(writer);
  fclose(fo);
}
template <class T>
void Database<T>::Create(T t)
{
  string col = "/" + to_string(getTotalCol());
  pair<string, string> *data = t.getAll();
  int count = atoi((data[0].second).c_str());
  int length = count;
  for (int i = 1; i <= length; i++)
  {
    string key = data[i].first;
    string value = data[i].second;
    long long valueLL = atoll(value.c_str());
    if ((length > 2) && ((count == 1) || ((count == 2) && valueLL != 0)))
    {
      // set long long
      Pointer((col + "/" + key).c_str()).Set(db, valueLL);
    }
    else
    {
      // set string
      Pointer((col + "/" + key).c_str()).Set(db, value.c_str());
    }
    count--;
  }
  writer();
}
template <class T>
string Database<T>::GetStringDB(int index, const char *field)
{
  return db.GetArray()[index][field].GetString();
}
template <class T>
long long Database<T>::GetLLDB(int index, const char *field)
{
  return db.GetArray()[index][field].GetInt64();
}
template <class T>
void Database<T>::Update(int index, const char *field, const char *value)
{
  if (index >= getTotalCol())
  {
    cout << "index too large";
    return;
  }
  Pointer(("/" + to_string(index) + "/" + string(field)).c_str()).Set(db, value);
  writer();
}
template <class T>
void Database<T>::Update(int index, const char *field, long long value)
{
  if (index >= getTotalCol())
  {
    cout << "index too large";
    return;
  }
  Pointer(("/" + to_string(index) + "/" + string(field)).c_str()).Set(db, value);
  writer();
}
template <class T>
void Database<T>::Delete(int index)
{
  if (index >= getTotalCol())
  {
    cout << "index too large\n";
    return;
  }
  Pointer(("/" + to_string(index)).c_str()).Erase(db);
  writer();
}