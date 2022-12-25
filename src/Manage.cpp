#include "../header/Manage.h"

using namespace std;
using namespace rapidjson;

const char *PATH_DB_STUDENT = "../database/db_student.json";
const char *PATH_DB_COMPUTER = "../database/db_computer.json";
const char *PATH_DB_REGISTER = "../database/db_register.json";

Manage::Manage()
    : dbStudent(Database<Student>(PATH_DB_STUDENT)), dbComputer(Database<Computer>(PATH_DB_COMPUTER)), dbRegister(Database<Record>(PATH_DB_REGISTER))
{
    for (int i = 0; i < dbRegister.getTotalCol(); i++)
        listRegister.add(Record(dbRegister.GetStringDB(i, "idComputer"), dbRegister.GetStringDB(i, "idStudent"), dbRegister.GetLLDB(i, "registeredAt"), dbRegister.GetLLDB(i, "unRegisteredAt")));
    for (int i = 0; i < dbComputer.getTotalCol(); i++)
    {
        listComputer.add(Computer(dbComputer.GetStringDB(i, "id"), dbComputer.GetStringDB(i, "name"), dbComputer.GetStringDB(i, "status"), dbComputer.GetStringDB(i, "idStudent"), dbComputer.GetLLDB(i, "timeUsed")));
    }
    for (int i = 0; i < dbStudent.getTotalCol(); i++)
        listStudent.add(Student(dbStudent.GetStringDB(i, "id"), dbStudent.GetStringDB(i, "name")));
}

Manage::~Manage()
{
}
notification Manage::Create(string id, string name)
{
    notification notice;
    if (id == "")
    {
        notice.msg = "Please enter computer id";
        notice.posX = 220;
        notice.posY = 240;
    }
    else if (listComputer.indexOf(id) == -1 && name == "")
    {
        notice.msg = "Please enter computer name";
        notice.posX = 200;
        notice.posY = 240;
    }
    else if (listComputer.indexOf(id) != -1)
    {
        notice.msg = "Computer id exists";
        notice.posX = 270;
        notice.posY = 240;
    }
    else
    {
        notice.code = 1;
        notice.msg = "Create successfully";
        notice.posX = 250;
        notice.posY = 240;
    }
    if (notice.code)
    {
        Computer computer(id, name, "not_using", "", 0);
        listComputer.add(computer);
        dbComputer.Create(computer);
    }
    return notice;
}
notification Manage::Update(string id, string name)
{
    notification notice;
    if (id == "")
    {
        notice.msg = "Please enter computer id";
        notice.posX = 220;
        notice.posY = 240;
    }
    else if (listComputer.indexOf(id) == -1)
    {
        notice.msg = "Computer id do not exist";
        notice.posX = 220;
        notice.posY = 240;
    }
    else if (listComputer.indexOf(id) != -1 && name == "")
    {
        notice.msg = "Please enter computer name";
        notice.posX = 200;
        notice.posY = 240;
    }
    else
    {
        notice.code = 1;
        notice.msg = "Update successfully";
        notice.posX = 245;
        notice.posY = 240;
    }
    if (notice.code)
    {
        int index = listComputer.indexOf(id);
        listComputer.at(index).setName(name);
        dbComputer.Update(index, "name", name.c_str());
    }
    return notice;
}
notification Manage::Delete(string id)
{
    notification notice;
    if (id == "")
    {
        notice.msg = "Please enter computer id";
        notice.posX = 220;
        notice.posY = 240;
    }
    else if (listComputer.indexOf(id) == -1)
    {
        notice.msg = "Computer id do not exist";
        notice.posX = 220;
        notice.posY = 240;
    }
    else
    {
        bool used = false;
        for (int i = 0; i < listRegister.length(); i++)
        {
            if (id == listRegister.at(i).getIdComputer() && listRegister.at(i).getUnRegisteredAt() == 0)
            {
                used = true;
                break;
            }
        }
        if (!used)
        {
            notice.msg = "Delete successfully";
            notice.posX = 255;
            notice.posY = 240;
            notice.code = 1;
        }
        else
        {
            notice.msg = "Computer is being used. Can not delete";
            notice.posX = 120;
            notice.posY = 240;
        }
    }
    if (notice.code)
    {
        int index = listComputer.indexOf(id);
        listComputer.removeAt(index);
        dbComputer.Delete(index);
        int i = 0;
        while (i < listRegister.length())
        {
            if (listRegister.at(i).getIdComputer() == id)
            {
                listRegister.removeAt(i);
                dbRegister.Delete(i);
            }
            else
                i++;
        }
    }
    return notice;
}
notification Manage::Register(int i, string id, string name)
{
    notification notice;
    if (id == "")
    {
        notice.msg = "Please enter student id";
        notice.posX = 230;
        notice.posY = 240;
    }
    else if (listStudent.indexOf(id) == -1 && name == "")
    {
        notice.msg = "Please enter student name";
        notice.posX = 210;
        notice.posY = 240;
    }
    else if (listStudent.indexOf(id) != -1 && name != listStudent.at(listStudent.indexOf(id)).getName() && name != "")
    {
        notice.msg = "Please check student name";
        notice.posX = 210;
        notice.posY = 240;
    }
    else
    {
        bool used = false;
        for (int index = 0; index < listComputer.length(); index++)
            if (id == listComputer.at(index).getIdStudent())
            {
                used = true;
                break;
            }
        if (!used)
        {
            notice.code = 1;
            notice.msg = "Register successfully";
            notice.posX = 240;
            notice.posY = 240;
        }
        else
        {
            notice.msg = "Student is using computer";
            notice.posX = 220;
            notice.posY = 240;
        }
    }
    if (notice.code == 1)
    {
        time_t now = time(0);
        if (listStudent.indexOf(id) == -1)
        {
            listStudent.add(Student(id, name));
            dbStudent.Create(Student(id, name));
        }
        listComputer.at(i).setStatus("using");
        dbComputer.Update(i, "status", "using");
        listComputer.at(i).setIdStudent(id);
        dbComputer.Update(i, "idStudent", id.c_str());
        listRegister.add(Record(listComputer.at(i).getId(), id, now, 0));
        dbRegister.Create(Record(listComputer.at(i).getId(), id, now, 0));
    }
    return notice;
}
notification Manage::Unregister(string id)
{
    notification notice;
    int indexRegister;
    string idComputer;
    if (id == "")
    {
        notice.msg = "Please enter student id";
        notice.posX = 230;
        notice.posY = 240;
    }
    else if (listStudent.indexOf(id) == -1)
    {
        notice.msg = "Student id do not exist";
        notice.posX = 230;
        notice.posY = 240;
    }
    else
    {
        bool used = false;
        for (int i = 0; i < listRegister.length(); i++)
        {
            if (id == listRegister.at(i).getIdStudent() && listRegister.at(i).getUnRegisteredAt() == 0)
            {
                used = true;
                indexRegister = i;
                idComputer = listRegister.at(i).getIdComputer();
                break;
            }
        }
        if (used)
        {
            notice.code = 1;
            notice.msg = "Unregister successfully";
            notice.posX = 240;
            notice.posY = 240;
        }
        else
        {
            notice.msg = "Student is not using computer";
            notice.posX = 190;
            notice.posY = 240;
        }
    }
    if (notice.code)
    {
        time_t now = time(0);
        int indexComputer = listComputer.indexOf(idComputer);
        long long timeUsed = listComputer.at(indexComputer).getTimeUsed() + (now - listRegister.at(indexRegister).getRegisteredAt());
        listRegister.at(indexRegister).setUnRegisterAt(now);
        dbRegister.Update(indexRegister, "unRegisteredAt", now);
        listComputer.at(indexComputer).setTimeUsed(timeUsed);
        dbComputer.Update(indexComputer, "timeUsed", timeUsed);
        listComputer.at(indexComputer).setIdStudent("");
        dbComputer.Update(indexComputer, "idStudent", "");
        listComputer.at(indexComputer).setStatus("not_using");
        dbComputer.Update(indexComputer, "status", "not_using");
    }
    return notice;
}

void Manage::ShowComputer(int index)
{
    time_t now = time(0);
    string idStudent = listComputer.at(index).getIdStudent();
    long long time = 0;
    for (int j = 0; j < listRegister.length(); j++)
        if (idStudent == listRegister.at(j).getIdStudent() && listRegister.at(j).getUnRegisteredAt() == 0)
            time = now - listRegister.at(j).getRegisteredAt();
    cout << listComputer.at(index);
    cout << "Total Time Used = " << listComputer.at(index).getTimeUsed() + time << endl;
    string status;
    if (listComputer.at(index).getStatus() == "not_using")
        cout << "The Computer Is Not Used\n";
    else
    {
        string name = listStudent.at(listStudent.indexOf(idStudent)).getName();
        status = "The Computer Is Being Used By " + name;
        status += " For " + to_string(time) + " Seconds";
        cout << status << endl;
    }
}
void Manage::ShowAllComputer()
{
    for (int i = 0; i < listComputer.length(); i++)
        ShowComputer(i);
}
void Manage::ShowC(int index)
{
    time_t now = time(0);
    long long time;
    if (listComputer.at(index).getStatus() == "not_using")
        time = listComputer.at(index).getTimeUsed();
    else
        for (int i = 0; i < listRegister.length(); i++)
            if (listComputer.at(index).getId() == listRegister.at(i).getIdComputer() && listRegister.at(i).getUnRegisteredAt() == 0)
            {
                time = listComputer.at(index).getTimeUsed() + now - listRegister.at(i).getRegisteredAt();
                break;
            }
    cout << "The Total Usage Time Of Machine " << listComputer.at(index).getId() << " Is " << time << endl;
}
void Manage::ShowTime()
{
    string id;
    cout << "Enter The Computer's ID To Check ";
    getline(cin, id);
    int index = listComputer.indexOf(id);
    if (index == -1)
    {
        cout << "Id Computer Does Not Exist\n";
        return;
    }
    ShowC(index);
}
void Manage::ShowTotalTime()
{
    for (int i = 0; i < listComputer.length(); i++)
        ShowC(i);
}
// option ngay, gio, between ngay gio...

void Manage::showInfoAtTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "Time: " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
    cout << "\nDay: " << ltm->tm_mday << "/" << ltm->tm_mon + 1 << "/" << 1900 + ltm->tm_year;
    cout << "\nBan muon xem thong tin may tinh vao ngay nao: ";
    int day;
    cin >> day;
    ltm->tm_mday = day;
    // begin
    ltm->tm_hour = 0;
    ltm->tm_min = 0;
    ltm->tm_sec = 0;
    time_t begin = mktime(ltm);
    // end
    ltm->tm_hour = 23;
    ltm->tm_min = 59;
    ltm->tm_sec = 59;
    time_t end = mktime(ltm);
    for (int i = 0; i < listRegister.length(); i++)
    {
        Record record = listRegister.at(i);
        if (
            (record.getRegisteredAt() >= begin && record.getRegisteredAt() <= end) || // ở giữa
            (record.getRegisteredAt() < begin && record.getUnRegisteredAt() == 0) ||  // ở trước, chưa kết thúc
            (record.getRegisteredAt() < begin && record.getUnRegisteredAt() >= begin) // ở trước, kết thúc
        )
        {
            long long timeStart = listRegister.at(i).getRegisteredAt();
            long long timeFinish = listRegister.at(i).getUnRegisteredAt();
            tm *ltmBegin = localtime(&timeStart);
            cout << "May " << listRegister.at(i).getIdComputer() << " duoc su dung boi sinh vien " << listRegister.at(i).getIdStudent()
                 << " tu " << ltmBegin->tm_hour << ":" << ltmBegin->tm_min << ":" << ltmBegin->tm_sec << " " << ltmBegin->tm_mday << "/" << ltmBegin->tm_mon;
            if (timeFinish != 0)
            {
                tm *ltmEnd = localtime(&timeFinish);
                cout << " den " << ltmEnd->tm_hour << ":" << ltmEnd->tm_min << ":" << ltmEnd->tm_sec << " " << ltmEnd->tm_mday << "/" << ltmEnd->tm_mon;
            }
            cout << endl;
        }
    }
}
// 1 năm = 31 556 926