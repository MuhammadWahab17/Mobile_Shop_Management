//
//  Header.h
//  04071913024_Muhammad_Wahab_A1
//
//  Created by Ch Muhammad Wahab on 06/10/2020.
//  Copyright © 2020 Ch Muhammad Wahab. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <iostream>
#include <fstream>
using namespace std;

int i=0;
class mobile{
    //arrays are not allowed so string is used
    string name;
    string model;
    int ram,rom,battery;
    long sr_no;
    double price;
public:
    mobile(string n=" ", string n2=" ",int ram=0,int rom=0,int battery=0,double price=0,long sr=0)
    :ram(ram),rom(rom),battery(battery),price(price),sr_no(sr){
        name.assign(n);
        model.assign(n2);
    }
    void setprice(){
        cout<<"Enter New price:";
        cin>>price;
    }
    
    void input(){
         if (i++>=0) {
             cin.ignore();
         }
        cout<<"Enter Mobile Brand:";getline(cin,name);
        cout<<"Enter Mobile Model:";getline(cin,model);
        cout<<"Enter Mobile Serial No:";cin>>sr_no;
        cout<<"How much GB ram "<<name<<" has:";cin>>ram;
        cout<<"How much GB rom "<<name<<" has:";cin>>rom;
        cout<<"How much mAH battery "<<name<<" has:";cin>>battery;
        cout<<"Specify "<<name<<"'s price(RS):";cin>>price;
        
    }
    void add(){
        //file is opened in append mode in order to save new data safely at the end
        mobile obj;
        obj.input();
        ofstream file("mobilerecord.bin",ios::binary|ios::app);
        if(file.is_open()){
            if(!file.bad())
            file.write((const char*)&obj,sizeof(obj));
            else
                cout<<"Space full! or permission denied";
        }
        else{
            cout<<"error in opening file";
        }
        file.close();
    }
    
    void display(){
        mobile obj;
        ifstream file("mobilerecord.bin",ios::binary);
            if(file.is_open()){
                file.seekg(0,ios::end);
                    if(file.tellg() < sizeof(obj)){
                        cout<<"File is empty\n";
                    }
                file.seekg(0);
                while(file.read((char*)&obj,sizeof(obj))) //while read()returns true(1) record
                                                          //are  displayed
                    {
                        obj.output();
                    }
            }
            else{
                cout<<"File failed to load \nBad name or path\n";
                ofstream file("mobilerecord.bin",ios::binary);  //file created in case if no file exists
                cout<<"New file created 'mobilerecord.bin' \n";
                file.close();
            }
        file.close();
    }
    void output(){
        cout<<"Mobile Brand: "<<name<<endl;
        cout<<"Mobile Model: "<<model<<endl;
        cout<<"Mobile Serial No: "<<sr_no<<endl;
        cout<<"Ram: "<<ram<<"GB"<<endl;
        cout<<"Rom: "<<rom<<"GB"<<endl;
        cout<<"Battery: "<<battery<<"mAH"<<endl;
        cout<<"Price: "<<price<<"RS\n\n";
    }
   
    void modify(){
        int found =0;
        cout<<"In modify function\n";
        mobile obj;
        cout<<"Enter mobile Serial No:";
        long sr;
        cin>>sr;
        fstream file("mobilerecord.bin",ios::binary| ios::ate |ios::in |ios::out);//opened in at the end
                                                            //mode so file pointer can move with in file
        file.seekg(0);                  //position of file pointer set to 0(start) by default was at the end
        if(file.is_open()){
            while(!file.eof()){
                file.read((char*)&obj, sizeof(obj));   //record read
                if(obj.sr_no==sr){                     // if sr_no matches
                file.seekp(-1*(sizeof(obj)),ios::cur); //file pointer is set one record backward
                                                       //as record to be modified is read
                    found=1;
                    cout<<"Do you want to \n1.update it's price \n2.want to enter new brand :";
                    int choice;cin>>choice;
                    if(choice==1){
                        obj.setprice();
                    }
                    else{
                        obj.input();
                    }
                file.write((const char*)&obj, sizeof(obj));
                break;
                }
            }
        }
        else{
            cout<<"File not opened \nBad path or format\n";
        }
        if(found==0){
            cout<<"There's no mobile with serial number "<<sr<<" in the file\n";
        }
        file.close();
    }
    
    void search(){
        //main menu for different criteria of search
    Start:
        cout<<"In search function\n";
        cout<<"1.SearchByMobileName()\n"
              "2.SearchByPriceRange()\n"
              "3.SearchByRam()\n"
        "Choose:";
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                SearchByMobileName();
                break;
            case 2:
                SearchByPriceRange();
                break;
            case 3:
                SearchByRam();
                break;
                
            default:
                cout<<"Wrong Number Entered\n";
                goto Start;
                break;
        }
    }
    void SearchByMobileName(){
        //serach by mobile name requires user to enter mobile brand.
        //all movies of that brand will be displayed
        //file is opened record are read one by one if brand matches it is displayed on screen
        int found=0;
        cout<<"In SearchByMobileName Function\n";
        mobile obj;
        cout<<"Enter mobile brand:";
        cin.ignore();
        string mobilename;
        getline(cin,mobilename);
        ifstream file("mobilerecord.bin",ios::binary);
        if(!file.fail()){
            while(file.read((char*)&obj, sizeof(obj))){
                if(obj.name.compare(mobilename)==0){
                    obj.output();
                    found++;
                }
            }
        }
        else{
            cout<<"Bad path or format\n";
        }
        if(found==0){
            cout<<"There's no "<<mobilename<<" in the file\n";
        }
        file.close();
    }
    void SearchByPriceRange(){
        //serach by price requires user to enter his demanding range and is served according..
        //all mobiles within given range will be displayed
        //file is opened record are read one by one if it's in range it is displayed on screen
        int found=0;
        cout<<"In SearchByPriceRange Function\n";
        mobile obj;
        int lower_range,upper_range;
        cout<<"Enter lower Range:";
        cin>>lower_range;
        cout<<"Enter upper Range:";
        cin>>upper_range;
        
        ifstream file("mobilerecord.bin",ios::binary);
        if(!file.fail()){
            while(file.read((char*)&obj, sizeof(obj))){
                if(obj.price>=lower_range && obj.price<=upper_range){
                    obj.output();
                    found++;
                }
            }
        }
        else{
            cout<<"Bad path or format\n";
        }
        if(found==0){
            cout<<"There's no mobile in range "<<lower_range<<"-"<<upper_range<<" in the file\n";
        }
        file.close();
    }
    void SearchByRam(){
        //serach by ram requires user to enter his demanding ram and is served according..
        //all mobiles having the requested ram will be displayed
        //file is opened record are read one by one if ram matches it is displayed on screen
        int found=0;
        cout<<"In SearchByRam Function\n";
        mobile obj;
        int ram;
        cout<<"Enter Ram (2GB,3GB,4GB,6GB,8GB,?):";
        cin>>ram;
        
        ifstream file("mobilerecord.bin",ios::binary);
        if(!file.fail()){
            while(file.read((char*)&obj, sizeof(obj))){
                if(obj.ram==ram){
                    obj.output();
                    found++;
                }
            }
        }
        else{
            cout<<"Bad path or format\n";
        }
        if(found==0){
            cout<<"There's no mobile in with ram "<<ram<<" in the file\n";
        }
        file.close();
    }
    
    void Delete(){
        //delete executes on bases of serial no
        //in delete i'll read file till record to be deleted and write those records in a new file
        //when record to be deleted is reached i'll skip step to write it in new file and then found variable
        // becomes 1 so after then we know that one record that was to be deleted is done so write
        //upcoming records even they have same sr no accidently
        int found=0;
        cout<<"In Delete Function\n";
        mobile obj;
        cout<<"Enter mobile Serial No:";
        long sr;cin>>sr;
        ifstream file("mobilerecord.bin",ios::binary);
        ofstream fwrite("newfile.bin",ios::binary|ios::trunc);

        if(!file.fail()){
            while(file.read((char*)&obj,sizeof(obj))){
                if(obj.sr_no==sr && found ==0 ){
                    found=1;
                    obj.output();
                    cout<<"Are you sure to delete this? (y/n) :";
                    char ch;
                    cin>>ch;
                    if(ch=='n'||ch=='N')
                    {
                        goto writeit;
                    }
//                    ofstream file1("restore.dat",ios::binary|ios::app);
//                    file1.write((const char*)&obj,sizeof(obj));
//                    file1.close();
                    found=2;
                }
                else{
                writeit:
                    mobile obj2=obj;
                    if(fwrite.is_open()){
                        fwrite.write((const char*)&obj2,sizeof(obj2));
                    }
                    else{
                        cout<<"Error in opening new file";
                    }
                
                }
            }
            if(found==2 && remove("mobilerecord.bin")==0){   //if found!=2 then remove() will not execute
               rename("newfile.bin","mobilerecord.bin");     //no file will remove and else will execute
               cout<<"Record Deleted Successfully!\n";       //means old file will remove when record
                                                             //is surely deleted
            }
            else{
                if(found==0){cout<<"Record not found\n";}
                cout<<"No Record deleted!\n";
            }
        }
        else{
            cout<<"Bad path or format\n";
        }
        fwrite.close();
        file.close();
    }
    void readarray(){
        mobile model;
        unsigned long int count=0;
        fstream file("mobilerecord.bin",ios::binary | ios::ate |ios::in |ios::out);
        count = file.tellg()/sizeof(model);
        
        file.seekg(0);
        mobile array[count];
        file.read((char*)array,sizeof(array));
        for (int i=0; i<count; i++) {
            array[i].output();
        }
        
    }
//    void restore(){
//        mobile obj;
//        ifstream file("restore.dat",ios::binary);
//        file.read((char*)&obj,sizeof(obj));
//        ofstream writefile("mobilerecord.bin",ios::binary|ios::ate);
//
//    }
};


#endif /* Header_h */
