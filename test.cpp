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
//    cout << "��������Ҫ�����Ķ���ʽ����(���롰cancel������)" << endl;
//    string name = getName();
//
//    if (name == "cancel") {
//        return;
//    }
//
//    cout << "***************************************" << endl;
//    cout << "��ѡ�����Ĳ��� ��" << endl;
//    cout << "1���ӷ�" << endl;
//    cout << "2������" << endl;
//    cout << "3���˷�" << endl;
//    cout << "4����" << endl;
//    cout << "5����ֵ" << endl;
//    cout << "�������������" << endl;
//
//    string command;
//
//    while (command == "") {
//        getline(cin, command);
//        if (command == "1") {
//            cout << "���ĸ�����ʽ��ӣ�������cancelȡ����";
//            string otherName = getName();
//            if (otherName == "cancel") {
//                return;
//            }
//
//            cout << name << " + " << otherName << " = "
//                << polyMap[name] + polyMap[otherName] << endl << endl;
//            cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name] + polyMap[otherName]);
//            }
//        } else if (command == "2") {
//            cout << "��ȥ�ĸ�����ʽ��������cancelȡ����";
//            string otherName = getName();
//            if (otherName == "cancel") {
//                return;
//            }
//
//            cout << name << " - " << otherName << " = "
//                << polyMap[name] - polyMap[otherName] << endl << endl;
//            cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name] - polyMap[otherName]);
//            }
//        } else if (command == "3") {
//            cout << "Ҫ�����ĸ�����ʽ��������cancelȡ����";
//            string otherName = getName();
//            if (otherName == "cancel") {
//                return;
//            }
//
//            cout << name << " * " << otherName << " = "
//                << polyMap[name] * polyMap[otherName] << endl << endl;
//            cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name] * polyMap[otherName]);
//            }
//        } else if (command == "4") {
//            cout << name << "\' = " << polyMap[name].derivative() << endl;
//            cout << "�Ƿ�Ҫ�������� Y���棬N������" << endl;
//            if (getYesNo()) {
//                this->insertPoly(polyMap[name].derivative());
//            }
//        } else if (command == "5") {
//            cout << "������x��ֵ��";
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
//            cout << endl << "û����������" << endl;
//            cout << "�������������� ��";
//        } else {
//            cout << endl << "��ʾ��������1-5֮�������" << endl;
//            cout << "�������������� ��";
//            command = "";
//        }
//    }
//}
