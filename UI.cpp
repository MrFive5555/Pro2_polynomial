#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "UI.h"

using namespace std;

UI::UI()
{
    fstream file("poly.data", fstream::in);
    if (!file) {
        return;
    }

    string name, polyStr;
    file >> name;

    while (file) {
        getline(file, polyStr);
        stringstream strstream(polyStr);
        polyMap.insert(pair<string, polynomial>(name, polynomial(polyStr)));

        file >> name;
    }

    file.clear();
    file.close();
}

void UI::printMenu()
{
    cout << endl;
    cout << "================================" << endl;
    cout << "=  ��ѡ�����Ĳ��� ��           =" << endl;
    cout << "=  ���� 1 ���������ʽ         =" << endl;
    cout << "=  ���� 2 ��ɾ������ʽ         =" << endl;
    cout << "=  ���� 3 �����ж���ʽ�ӷ�     =" << endl;
    cout << "=  ���� 4 �����ж���ʽ����     =" << endl;
    cout << "=  ���� 5 �����ж���ʽ�˷�     =" << endl;
    cout << "=  ���� 6 �����ж���ʽ��     =" << endl;
    cout << "=  ���� 7 �����ж���ʽ��ֵ     =" << endl;
    cout << "=  ���� 8 ���ж϶���ʽ���     =" << endl;
    cout << "=  ���� 9 ���鿴�Ѵ���Ķ���ʽ =" << endl;
    cout << "=  ���� 0 ���˳�               =" << endl;
    cout << "================================" << endl << endl;

    cout << "�������������� ��";
}

bool UI::getCommand()
{
    printMenu();
    string command;

    while (command == "") {
        getline(cin, command);
        if (command == "1") {
            input();
        } else if (command == "2") {
            del();
        } else if (command == "3") {
            add();
        } else if (command == "4") {
            subtraction();
        } else if (command == "5") {
            multiply();
        } else if (command == "6") {
            derivative();
        } else if (command == "7") {
            evalueAtAPoint();
        } else if (command == "8") {
            isEqual();
        } else if (command == "9") {
            seek();
        } else if (command == "0") {
            cout << "��ӭ�ٴ�ʹ�ö���ʽ������" << endl;
            return false;
        } else if (command == "") {
            cout << endl << "û����������" << endl;
            cout << "�������������� ��";
        } else {
            cout << endl << "��ʾ��������0-9֮�������" << endl;
            cout << "�������������� ��";
            command = "";
        }
    }

    cout << "���س�����" << endl;
    getline(cin, command);
    return true;
}

void UI::input()
{
    cout << endl
        << "���������ʽ����\"��ϵ��1�� ָ��1����ϵ��2�� ָ��2����ϵ��3�� ָ��3��...\"�ĸ�ʽ��" << endl
        << "�磨3,2����2,1����3,0����ʾ3x^2 + 2x + 3" << endl
        << "����ʾ��ֻ����Ӣ�����뷨�����룬����һ����������룩" << endl
        << "====================================================================" << endl;
    

    string str;
    getline(cin, str);
    while (!isStrValid(str)) {
        cout << "��ʽ�����ʹ�����������룬�밴��ȷ�ĸ�ʽ���룺" << endl
             << "====================================================================" << endl;
        getline(cin, str);
    }

    this->insertPoly(polynomial(str));
}

void UI::del()
{
    cout << "��������Ҫɾ���Ķ���ʽ�� ��(���롰cancel��ȡ��ɾ��)" << endl;
    string name;
    getline(cin, name);

    while (polyMap.find(name) == polyMap.end()) {
        if (name == "cancel") {
            return;
        }
        cout << "û����Ϊ" << name << "�Ķ���ʽ������������ ��" << endl;
        getline(cin, name);
    }

    polyMap.erase(name);
    refreshFile();
    cout << "ɾ���ɹ�" << endl;
}

void UI::add()
{
    string str;
    int count = 0;
    cout << "�ж��ٸ�����ʽ��ӣ�" << endl;

    getline(cin, str);
    stringstream stream(str);
    stream >> count;
    while (count <= 0) {
        cout << "�Ƿ����룡��������ȷ����Ӹ�����" << endl;

        getline(cin, str);
        stringstream stream(str);
        stream >> count;
    }

    //input polynomial
    vector<string> operaVec;
    cout << "����������" << count << "������ʽ������ʹ�ö���ʽ��������(3,2����2,1������ʽ��" << endl;

    for (int i = 0; i != count; ++i) {
        cout << "# " << i+1 << "��";

        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "��ʽ����ʹ�����������롢��û���������ʽ�����������룺" << endl;
            cout << "# " << i+1 << "��";
            getline(cin, str);
        }
        operaVec.push_back(str);
    }

    //output result
    polynomial newPoly(getPoly(operaVec.front()));
    if (isStrValid(operaVec.front())) {
        cout << " ( " << getPoly(operaVec.front()) << " ) ";
    } else {
        cout << operaVec.front();
    }
    
    for (vector<string>::iterator iter = operaVec.begin() + 1; iter != operaVec.end(); ++iter) {
        cout << " + ";

        if (isStrValid(*iter)) {
            cout << " ( " << getPoly(*iter) << " ) ";
        } else {
            cout << *iter;
        }

        newPoly = newPoly + getPoly(*iter);
    }
    cout << " = " << newPoly << endl;

    //if store the result
    cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "��¼�ɹ�" << endl;
    }
}

void UI::subtraction()
{

    //input polynomial
    vector<string> operaVec;
    cout << "�����������������������ʽ������ʹ�ö���ʽ��������(3,2����2,1������ʽ��" << endl;

    for (int i = 0; i != 2; ++i) {
        string str;
        cout << "# " << i + 1 << "��";

        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "��ʽ����ʹ�����������롢��û���������ʽ�����������룺" << endl;
            cout << "# " << i + 1 << "��";
            getline(cin, str);
        }
        operaVec.push_back(str);
    }

    polynomial newPoly(getPoly(operaVec.front()) - getPoly(operaVec.back()));

    //output result
    cout << "**********************************************************************" << endl << "* ";

    if (isStrValid(operaVec.front())) {
        cout << getPoly(operaVec.front());
    } else {
        cout << operaVec.front();
    }

    cout << " - ";

    if (isStrValid(operaVec.back())) {
        cout << getPoly(operaVec.back());
    } else {
        cout << operaVec.back();
    }

    cout << " = " << newPoly << endl;
    cout << "**********************************************************************" << endl;

    //if store the result
    cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "��¼�ɹ�" << endl;
    }
}

void UI::multiply()
{
    string str;
    int count = 0;
    cout << "�ж��ٸ�����ʽ��ˣ�" << endl;

    getline(cin, str);
    stringstream stream(str);
    stream >> count;
    while (count <= 0) {
        cout << "�Ƿ����룡��������ȷ����˸�����" << endl;

        getline(cin, str);
        stringstream stream(str);
        stream >> count;
    }

    //input polynomial
    vector<string> operaVec;
    cout << "����������" << count << "������ʽ������ʹ�ö���ʽ��������(3,2����2,1������ʽ��" << endl;

    for (int i = 0; i != count; ++i) {
        cout << "# " << i + 1 << "��";

        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "��ʽ����ʹ�����������롢��û���������ʽ�����������룺" << endl;
            cout << "# " << i + 1 << "��";
            getline(cin, str);
        }
        operaVec.push_back(str);
    }

    //output result
    polynomial newPoly(getPoly(operaVec.front()));
    cout << "**********************************************************************" << endl << "* ";
    if (isStrValid(operaVec.front())) {
        cout << " ( " << getPoly(operaVec.front()) << " ) ";
    } else {
        cout << operaVec.front();
    }

    for (vector<string>::iterator iter = operaVec.begin() + 1; iter != operaVec.end(); ++iter) {
        cout << " * ";

        if (isStrValid(*iter)) {
            cout << " ( " << getPoly(*iter) << " ) ";
        } else {
            cout << *iter;
        }

        newPoly = newPoly * getPoly(*iter);
    }
    cout << " = " << newPoly << endl;
    cout << "**********************************************************************" << endl;

    //if store the result
    cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "��¼�ɹ�" << endl;
    }
}

void UI::derivative()
{
    //input polynomial
    cout << "������Ҫ�󵼵Ķ���ʽ������ʹ�ö���ʽ��������(3,2����2,1������ʽ��" << endl;

    string str;
    cout << "# 1 ��";

    getline(cin, str);
    while (!canGetPoly(str)) {
        cout << "��ʽ����ʹ�����������롢��û���������ʽ�����������룺" << endl;
        cout << "# 1 ��";
        getline(cin, str);
    }

    polynomial newPoly(getPoly(str).derivative());

    //output result
    cout << "**********************************************************************" << endl << "* ";

    if (isStrValid(str)) {
        cout << "( " << getPoly(str) << " )";
    } else {
        cout << str;
    }

    cout << "' = " << newPoly << endl;
    cout << "**********************************************************************" << endl;

    //if store the result
    cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "��¼�ɹ�" << endl;
    }
}

void UI::evalueAtAPoint()
{
    //input polynomial
    cout << "������Ҫ��ֵ�Ķ���ʽ������ʹ�ö���ʽ��������(3,2����2,1������ʽ��" << endl;

    string str;
    cout << "# 1 ��";

    getline(cin, str);
    while (!canGetPoly(str)) {
        cout << "��ʽ����ʹ�����������롢��û���������ʽ�����������룺" << endl;
        cout << "# 1 ��";
        getline(cin, str);
    }

    polynomial newPoly(getPoly(str));

    //get the value of x
    string doubleStr;
    cout << "������x��ֵ��" << endl;
    cout << "x = ";

    getline(cin, doubleStr);
    while (!canGetDouble(doubleStr)) {
        cout << "�Ƿ����룬����������x��ֵ��" << endl;
        cout << "x = ";
        getline(cin, doubleStr);
    }

    //output result
    cout << "**********************************************************************" << endl << "* ";

    if (isStrValid(str)) {
        cout << getPoly(str);
    } else {
        cout << str << "(" << atof(doubleStr.c_str()) << ")";
    }

    cout << " = " << newPoly.evalue(atof(doubleStr.c_str())) << endl;
    cout << "**********************************************************************" << endl;
}

void UI::isEqual()
{
    vector<string> operaVec;
    cout << "������������Ҫ�ж��Ƿ���ȵ�2������ʽ������ʹ�ö���ʽ��������(3,2����2,1������ʽ��" << endl;

    for (int i = 0; i != 2; ++i) {
        cout << "# " << i + 1 << "��";

        string str;
        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "��ʽ����ʹ�����������롢��û���������ʽ�����������룺" << endl;
            cout << "# " << i + 1 << "��";
            getline(cin, str);
        }
        operaVec.push_back(str);
    }

    //output result
    cout << "**********************************************************************" << endl << "* ";

    if (isStrValid(operaVec.front())) {
        cout << getPoly(operaVec.front());
    } else {
        cout << operaVec.front();
    }

    cout << (getPoly(operaVec.front()) == getPoly(operaVec.back()) ? " == " : " != ");

    if (isStrValid(operaVec.back())) {
        cout << getPoly(operaVec.back());
    } else {
        cout << operaVec.back();
    }

    cout << endl;
    cout << "**********************************************************************" << endl;
}

void UI::seek()
{

    if (polyMap.size() != 0) {
        cout << "***************************************" << endl;
        cout << "* �Ѽ�¼�Ķ���ʽ�У�" << endl;


        for (map<string, polynomial>::const_iterator iter = polyMap.begin();
            iter != polyMap.end(); ++iter) {
            cout << "*  "
                << setw(8) << setiosflags(ios::left)
                << iter->first << iter->second << endl;
        }
        cout << "***************************************" << endl;
    } else {
        cout << "û�м�¼����ʽ�����԰�����1��ʼ����" << endl;
        return;
    }
    
}

bool UI::canGetPoly(string str)
{
    if (isStrValid(str)) {
        return true;
    }

    if (polyMap.find(str) != polyMap.end()) {
        return true;
    }

    return false;
}

polynomial UI::getPoly(string str)
{
    if (isStrValid(str)) {
        return polynomial(str);
    }

    if (polyMap.find(str) != polyMap.end()) {
        return polyMap[str];
    }

    throw runtime_error("UNKNOWN ERROR");
    return polynomial("");
}

bool UI::canGetDouble(string str)
{
    stringstream stream(str);
    double dou = DBL_MAX;
    stream >> dou;
    if (dou == DBL_MAX) {
        return false;
    }

    str = "";
    getline(stream, str);
    if (!str.empty()) {
        return false;
    }

    return true;
}

bool UI::getYesNo()
{
    string YesNo;
    cout << " ����Y��N ��";
    while (1) {
        getline(cin, YesNo);
        if (YesNo == "Y") {
            return true;
        } else if(YesNo == "N") {
            return false;
        } else {
            cout << "������Y��N" << endl;
        }
    }
    return true;
}

bool UI::insertPoly(const polynomial poly)
{
    cout << "��Ϊ����Ķ���ʽ���� ��(����cancelȡ��)" << endl;
    string name;

    while (1) {
        getline(cin, name);
        if (name == "cancel") {
            return false;
        }
        if (polyMap.find(name) != polyMap.end()) {
            cout << "������ͬ���ֵĶ���ʽ������������ ��" << endl;
            continue;
        }
        if (name.length() > 5) {
            cout << "����ʽ��������������С��6���ַ��Ķ���ʽ�� �� ";
            continue;
        }
        break;
    }
    
    polyMap.insert(pair<string, polynomial>(name, poly));
    refreshFile();
    return true;
}

void UI::refreshFile()
{
    fstream file("poly.data", fstream::out | fstream::trunc);
    if (!file) {
        return;
    }

    for (map<string, polynomial>::iterator iter = polyMap.begin();
        iter != polyMap.end(); ++iter) {
        file << iter->first << " " << iter->second.storeFormat() << endl;
    }

    file.clear();
    file.close();
}