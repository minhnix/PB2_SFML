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
void Manage::Create()
{
    string id, name;
    cout << "Nhap thong tin may tinh moi\n";
    cout << "ID may tinh: ";
    getline(cin, id);
    if (listComputer.indexOf(id) != -1)
    {
        cout << "ID may da ton tai\n";
        return;
    }
    cout << "Ten may: ";
    getline(cin, name);
    Computer computer(id, name, "not_using", "", 0);
    listComputer.add(computer);
    dbComputer.Create(computer);
    cout << "Da tao thanh cong\n";
}
void Manage::Update()
{
    string id, name;
    cout << "Nhap thong tin can sua\n";
    cout << "ID may tinh can sua: ";
    getline(cin, id);
    int index = listComputer.indexOf(id);
    if (index == -1)
    {
        cout << "May nay khong ton tai\n";
        return;
    }
    cout << "Nhap ten moi: ";
    getline(cin, name);
    listComputer.at(index).setName(name);
    dbComputer.Update(index, "name", name.c_str());
    cout << "Da sua thanh cong\n";
}
void Manage::Delete()
{
    string id;
    cout << "Nhap id may muon xoa: ";
    getline(cin, id);
    int index = listComputer.indexOf(id);
    if (index == -1)
    {
        cout << "May nay khong ton tai\n";
        return;
    }
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
void Manage::Register()
{
    cout << "Danh sach cac may tinh chua dang ky\n";
    for (int i = 0; i < listComputer.length(); i++)
    {
        if (listComputer.at(i).getStatus() == "not_using")
            cout << listComputer.at(i) << endl;
    }
    string idComputer, idStudent;
    cout << "Nhap mssv: ";
    getline(cin, idStudent);
    int indexStudent = listStudent.indexOf(idStudent);
    if (indexStudent == -1)
    {
        cout << "Ban chua dang ky. Vui long nhap ten de dang ky: ";
        string name;
        getline(cin, name);
        listStudent.add(Student(idStudent, name));
        dbStudent.Create(listStudent.at(listStudent.length() - 1));
        cout << "Ban da dang ky mssv thanh cong\n";
    }
    else
    {
        for (int i = 0; i < listComputer.length(); i++)
        {
            if (idStudent == listComputer.at(i).getIdStudent())
            {
                cout << "Ban da dang ky may so " << listComputer.at(i).getId() << endl;
                return;
            }
        }
    }
    int indexComputer = 0;
    while (1)
    {
        cout << "Nhap id may tinh can dang ky: ";
        getline(cin, idComputer);
        indexComputer = listComputer.indexOf(idComputer);
        if (indexComputer != -1 && listComputer.at(indexComputer).getStatus() != "using")
            break; // register successfully
        if (indexComputer == -1)
            cout << "May tinh nay khong ton tai\n";
        else
            cout << "May nay da dang ky\n"; // exist and using
    }
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string id = idStudent + idComputer + to_string(now);
    listRegister.add(Record(idComputer, idStudent, now, 0));
    dbRegister.Create(listRegister.at(listRegister.length() - 1));
    listComputer.at(indexComputer).setStatus("using");
    dbComputer.Update(indexComputer, "status", "using");
    listComputer.at(indexComputer).setIdStudent(idStudent);
    dbComputer.Update(indexComputer, "idStudent", idStudent.c_str());
    cout << "Ban da dang ky thanh cong vao luc " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;
}
void Manage::Unregister()
{
    cout << "Nhap mssv cua ban: ";
    string idStudent, idComputer;
    int indexRegister;
    getline(cin, idStudent);
    bool oke = true;
    for (int i = 0; i < listRegister.length(); i++)
    {
        if (idStudent == listRegister.at(i).getIdStudent() && listRegister.at(i).getUnRegisteredAt() == 0)
        {
            oke = false;
            indexRegister = i;
            idComputer = listRegister.at(i).getIdComputer();
            break;
        }
    }
    if (oke)
    {
        cout << "Ban chua dang ky may nao\n";
        return;
    }
    time_t now = time(0);
    int indexComputer = listComputer.indexOf(idComputer);
    long long timeUsed = listComputer.at(indexComputer).getTimeUsed() + (now - listRegister.at(indexRegister).getRegisteredAt());
    listRegister.at(indexRegister).setUnRegisterAt(now);     // update unRegistered time
    dbRegister.Update(indexRegister, "unRegisteredAt", now); // save database
    listComputer.at(indexComputer).setTimeUsed(timeUsed);    // update timeUsed Computer
    dbComputer.Update(indexComputer, "timeUsed", timeUsed);  // save database
    listComputer.at(indexComputer).setIdStudent("");
    dbComputer.Update(indexComputer, "idStudent", "");
    listComputer.at(indexComputer).setStatus("not_using");
    dbComputer.Update(indexComputer, "status", "not_using");
    cout << "Ban da huy dang ky thanh cong\n";
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