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
    cout << "=  请选择您的操作 ：           =" << endl;
    cout << "=  输入 1 ：输入多项式         =" << endl;
    cout << "=  输入 2 ：删除多项式         =" << endl;
    cout << "=  输入 3 ：进行多项式加法     =" << endl;
    cout << "=  输入 4 ：进行多项式减法     =" << endl;
    cout << "=  输入 5 ：进行多项式乘法     =" << endl;
    cout << "=  输入 6 ：进行多项式求导     =" << endl;
    cout << "=  输入 7 ：进行多项式赋值     =" << endl;
    cout << "=  输入 8 ：判断多项式相等     =" << endl;
    cout << "=  输入 9 ：查看已储存的多项式 =" << endl;
    cout << "=  输入 0 ：退出               =" << endl;
    cout << "================================" << endl << endl;

    cout << "请输入您的命令 ：";
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
            cout << "欢迎再次使用多项式计算器" << endl;
            return false;
        } else if (command == "") {
            cout << endl << "没有输入命令" << endl;
            cout << "请输入您的命令 ：";
        } else {
            cout << endl << "提示：请输入0-9之间的数字" << endl;
            cout << "请输入您的命令 ：";
            command = "";
        }
    }

    cout << "按回车继续" << endl;
    getline(cin, command);
    return true;
}

void UI::input()
{
    cout << endl
        << "请输入多项式，按\"（系数1， 指数1）（系数2， 指数2）（系数3， 指数3）...\"的格式，" << endl
        << "如（3,2）（2,1）（3,0）表示3x^2 + 2x + 3" << endl
        << "（提示：只能在英文输入法下输入，并在一行内完成输入）" << endl
        << "====================================================================" << endl;
    

    string str;
    getline(cin, str);
    while (!isStrValid(str)) {
        cout << "格式错误或使用了中文输入，请按正确的格式输入：" << endl
             << "====================================================================" << endl;
        getline(cin, str);
    }

    this->insertPoly(polynomial(str));
}

void UI::del()
{
    cout << "请输入你要删除的多项式名 ：(输入“cancel”取消删除)" << endl;
    string name;
    getline(cin, name);

    while (polyMap.find(name) == polyMap.end()) {
        if (name == "cancel") {
            return;
        }
        cout << "没有名为" << name << "的多项式，请重新输入 ：" << endl;
        getline(cin, name);
    }

    polyMap.erase(name);
    refreshFile();
    cout << "删除成功" << endl;
}

void UI::add()
{
    string str;
    int count = 0;
    cout << "有多少个多项式相加？" << endl;

    getline(cin, str);
    stringstream stream(str);
    stream >> count;
    while (count <= 0) {
        cout << "非法输入！请输入正确的相加个数：" << endl;

        getline(cin, str);
        stringstream stream(str);
        stream >> count;
    }

    //input polynomial
    vector<string> operaVec;
    cout << "请依次输入" << count << "个多项式，可以使用多项式名或形如(3,2）（2,1）的形式：" << endl;

    for (int i = 0; i != count; ++i) {
        cout << "# " << i+1 << "：";

        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "格式错误、使用了中文输入、或没有这个多项式，请重新输入：" << endl;
            cout << "# " << i+1 << "：";
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
    cout << "是否要储存结果？ Y储存，N不储存" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "记录成功" << endl;
    }
}

void UI::subtraction()
{

    //input polynomial
    vector<string> operaVec;
    cout << "请依次输入相减的两个多项式，可以使用多项式名或形如(3,2）（2,1）的形式：" << endl;

    for (int i = 0; i != 2; ++i) {
        string str;
        cout << "# " << i + 1 << "：";

        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "格式错误、使用了中文输入、或没有这个多项式，请重新输入：" << endl;
            cout << "# " << i + 1 << "：";
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
    cout << "是否要储存结果？ Y储存，N不储存" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "记录成功" << endl;
    }
}

void UI::multiply()
{
    string str;
    int count = 0;
    cout << "有多少个多项式相乘？" << endl;

    getline(cin, str);
    stringstream stream(str);
    stream >> count;
    while (count <= 0) {
        cout << "非法输入！请输入正确的相乘个数：" << endl;

        getline(cin, str);
        stringstream stream(str);
        stream >> count;
    }

    //input polynomial
    vector<string> operaVec;
    cout << "请依次输入" << count << "个多项式，可以使用多项式名或形如(3,2）（2,1）的形式：" << endl;

    for (int i = 0; i != count; ++i) {
        cout << "# " << i + 1 << "：";

        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "格式错误、使用了中文输入、或没有这个多项式，请重新输入：" << endl;
            cout << "# " << i + 1 << "：";
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
    cout << "是否要储存结果？ Y储存，N不储存" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "记录成功" << endl;
    }
}

void UI::derivative()
{
    //input polynomial
    cout << "请输入要求导的多项式，可以使用多项式名或形如(3,2）（2,1）的形式：" << endl;

    string str;
    cout << "# 1 ：";

    getline(cin, str);
    while (!canGetPoly(str)) {
        cout << "格式错误、使用了中文输入、或没有这个多项式，请重新输入：" << endl;
        cout << "# 1 ：";
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
    cout << "是否要储存结果？ Y储存，N不储存" << endl;
    if (getYesNo() && insertPoly(newPoly)) {
        cout << "记录成功" << endl;
    }
}

void UI::evalueAtAPoint()
{
    //input polynomial
    cout << "请输入要求值的多项式，可以使用多项式名或形如(3,2）（2,1）的形式：" << endl;

    string str;
    cout << "# 1 ：";

    getline(cin, str);
    while (!canGetPoly(str)) {
        cout << "格式错误、使用了中文输入、或没有这个多项式，请重新输入：" << endl;
        cout << "# 1 ：";
        getline(cin, str);
    }

    polynomial newPoly(getPoly(str));

    //get the value of x
    string doubleStr;
    cout << "请输入x的值：" << endl;
    cout << "x = ";

    getline(cin, doubleStr);
    while (!canGetDouble(doubleStr)) {
        cout << "非法输入，请重新输入x的值：" << endl;
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
    cout << "请依次输入需要判断是否相等的2个多项式，可以使用多项式名或形如(3,2）（2,1）的形式：" << endl;

    for (int i = 0; i != 2; ++i) {
        cout << "# " << i + 1 << "：";

        string str;
        getline(cin, str);
        while (!canGetPoly(str)) {
            cout << "格式错误、使用了中文输入、或没有这个多项式，请重新输入：" << endl;
            cout << "# " << i + 1 << "：";
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
        cout << "* 已记录的多项式有：" << endl;


        for (map<string, polynomial>::const_iterator iter = polyMap.begin();
            iter != polyMap.end(); ++iter) {
            cout << "*  "
                << setw(8) << setiosflags(ios::left)
                << iter->first << iter->second << endl;
        }
        cout << "***************************************" << endl;
    } else {
        cout << "没有记录多项式，可以按输入1开始输入" << endl;
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
    cout << " 输入Y或N ：";
    while (1) {
        getline(cin, YesNo);
        if (YesNo == "Y") {
            return true;
        } else if(YesNo == "N") {
            return false;
        } else {
            cout << "请输入Y或N" << endl;
        }
    }
    return true;
}

bool UI::insertPoly(const polynomial poly)
{
    cout << "请为输入的多项式命名 ：(输入cancel取消)" << endl;
    string name;

    while (1) {
        getline(cin, name);
        if (name == "cancel") {
            return false;
        }
        if (polyMap.find(name) != polyMap.end()) {
            cout << "已有相同名字的多项式，请重新输入 ：" << endl;
            continue;
        }
        if (name.length() > 5) {
            cout << "多项式名过长，请输入小于6个字符的多项式名 ： ";
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