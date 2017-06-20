#include "polynomial.h"

//int main()
//{
//    polynomial poly;
//    term term1(1, 2), term2(2, 1), term3(1, 0);
//    poly.addTermToPoly(term1);
//    poly.addTermToPoly(term2);
//    poly.addTermToPoly(term3);
//    cout << poly.storeFormat() << endl;
//    polynomial poly2("");
//    cout << poly2 << endl;
//}


//int main()
//{
//    polynomial poly, poly2;
//    term term1(1, 2), term2(2, 1), term3(1, 0);
//    poly.addTermToPoly(term1);
//    poly2.addTermToPoly(term2);
//    cout << poly << endl << poly2 << endl;
//    cout << poly + poly2 << endl;
//    cout << poly - poly2 << endl;
//    cout << (poly+poly2) * (poly - poly2) << endl;
//}


//int main()
//{
//    string arr[] = { "(3,2)","(2,1)","(3,0)","(1,-1)","(3,-2)" },
//        err[] = { "(3,0.1)", "(z,1)", "(1,z)", "1,0)", "(1 0)", "(1,0" };
//
//    for (int i = 0; i != 5; ++i) {
//        cout << isStrValid(arr[i]) << endl;
//    }
//
//    for (int i = 0; i != 6; ++i) {
//        cout << isStrValid(err[i]) << endl;
//    }
//
//    cout << isStrValid("(3,2)(2,1)(3,0)(1,-1)(3,-2)") << endl;
//}


//void UI::opera()
//{
//    cout << "请输入您要操作的多项式名：(输入“cancel”操作)" << endl;
//    string name = getName();
//
//    if (name == "cancel") {
//        return;
//    }
//
//    cout << "***************************************" << endl;
//    cout << "请选择您的操作 ：" << endl;
//    cout << "1：加法" << endl;
//    cout << "2：减法" << endl;
//    cout << "3：乘法" << endl;
//    cout << "4：求导" << endl;
//    cout << "5：赋值" << endl;
//    cout << "请输入您的命令：" << endl;
//
//    string command;
//
//    while (command == "") {
//        getline(cin, command);
//        if (command == "1") {
//            cout << "和哪个多项式相加？（输入cancel取消）";
//            string otherName = getName();
//            if (otherName == "cancel") {
//                return;
//            }
//
//            cout << name << " + " << otherName << " = "
//                << polyMap[name] + polyMap[otherName] << endl << endl;
//            cout << "是否要储存结果？ Y储存，N不储存" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name] + polyMap[otherName]);
//            }
//        } else if (command == "2") {
//            cout << "减去哪个多项式？（输入cancel取消）";
//            string otherName = getName();
//            if (otherName == "cancel") {
//                return;
//            }
//
//            cout << name << " - " << otherName << " = "
//                << polyMap[name] - polyMap[otherName] << endl << endl;
//            cout << "是否要储存结果？ Y储存，N不储存" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name] - polyMap[otherName]);
//            }
//        } else if (command == "3") {
//            cout << "要乘上哪个多项式？（输入cancel取消）";
//            string otherName = getName();
//            if (otherName == "cancel") {
//                return;
//            }
//
//            cout << name << " * " << otherName << " = "
//                << polyMap[name] * polyMap[otherName] << endl << endl;
//            cout << "是否要储存结果？ Y储存，N不储存" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name] * polyMap[otherName]);
//            }
//        } else if (command == "4") {
//            cout << name << "\' = " << polyMap[name].derivative() << endl;
//            cout << "是否要储存结果？ Y储存，N不储存" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name].derivative());
//            }
//        } else if (command == "5") {
//            cout << "请输入x的值：";
//
//            double x = DBL_MAX;
//
//            while (x == DBL_MAX) {
//                string value;
//                getline(cin, value);
//                stringstream stream;
//                stream << value;
//                stream >> x;
//            }
//
//            cout << name << "(" << x << ") = " << polyMap[name].evalue(x) << endl;
//
//        } else if (command == "") {
//            cout << endl << "没有输入命令" << endl;
//            cout << "请输入您的命令 ：";
//        } else {
//            cout << endl << "提示：请输入1-5之间的数字" << endl;
//            cout << "请输入您的命令 ：";
//            command = "";
//        }
//    }
//}
