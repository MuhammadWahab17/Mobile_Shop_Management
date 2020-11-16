//
//  main.cpp
//  04071913024_Muhammad_Wahab_A1
//
//  Created by Ch Muhammad Wahab on 06/10/2020.
//  Copyright © 2020 Ch Muhammad Wahab. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

int menu(){
   cout<<
    "1:Add(mobile)\n"
    "2:Display(mobiles)\n"
    "3:Modify(mobile_info)\n"
    "4:Search(mobile(s))\n"
    "5:Delete(mobile)\n"
    "6.Read record into an array\n"
    "7:Exit()\n"
    "Enter Choice:";
    int choice;cin>>choice;
    return choice;
}

int main(int argc, const char * argv[]) {
    cout<<"Welcome to Mobile Sale Management System\n";
    mobile model;
    model.display();
    while(1){
    switch (menu()) {
        case 1:
            model.add();
            break;
        case 2:
            model.display();
            break;
        case 3:
            model.modify();
            break;
        case 4:
            model.search();
            break;
        case 5:
            model.Delete();
            break;
        case 6:
            model.readarray();
            break;
        case 7:
            exit(1);
        default:
            cout<<"Press any digit within 1-6\n";
            break;
    }
    }
}
