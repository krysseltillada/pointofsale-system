#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;

const int ROWMAXLIST = 50;
const int COLMAXLIST = 4;
int rowcounter = 0;
int colcounter = 4;

class Pos_system
{
    protected:
    string username;
    string password;
    string inputpassword;
    string inputusername;

    public:
    Pos_system(string usr = "NULL", string pwd = "NULL");
    bool load_usr_pwd();
    bool chck_str(string);
    bool chck_symbols(string);
    bool ifnumber(string);
    bool ifletter(string);
    bool chck_email(string);
    bool chck_website(string);
    void System_time();
    void System_date();
};

Pos_system::Pos_system(string user, string pass)
{
    username = user;
    password = pass;
}

bool Pos_system::chck_website(string chck)
{
    string getdomain;
    int countstring1 = 0;

    for(int c = 0; c < chck.length(); c++)
    {
        if(chck.at(c) == '.'){
            countstring1++;
            getdomain = chck.substr(countstring1, int(chck.length()));
             if(getdomain == "com" || getdomain == "org" || getdomain == "net" || getdomain == "int" || getdomain == "edu" || getdomain == "gov" || getdomain == "mil"){
                        return true;
                }
             else{
                return false;
                }
        }
        else{
         countstring1++;
         continue;
        }
    }

    return false;
}

bool Pos_system::chck_email(string chck)
{
    string getdomain;
    int countstring1 = 0, countstring2 = 0, countstring3 = 0;
    for(int c = 0; c < chck.length(); c++)
    {
        if(chck.at(c) == '@'){
            countstring1++;
            countstring3++;
        for(; countstring1 < chck.length(); countstring1++){
            if(chck.at(countstring1) == '.'){
                    countstring2++;
                    countstring2 = countstring2 + countstring3;
                    getdomain = chck.substr(countstring2, int(chck.length()));
                    if(getdomain == "com" || getdomain == "org" || getdomain == "net" || getdomain == "int" || getdomain == "edu" || getdomain == "gov" || getdomain == "mil"){
                        return true;
                    }
                    else{
                        return false;
                    }
            }
            else{
                countstring2++;
                continue;
            }

        }
        }
        else{
            countstring1++;
            countstring3++;
            continue;
        }
    }
    return false;
}

bool Pos_system::ifletter(string chck)
{
    for(int c = 0; c < chck.length(); c++)
    {
        if(isalpha(chck.at(c)))
            return false;
        else
            continue;
    }
    return true;
}

void Pos_system::System_time()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

     cout << "time: "<< (( ltm->tm_hour == 00 ||  ltm->tm_hour == 12) ? 12 : ltm->tm_hour % 12) << ":"
          << setw(2) <<  ltm->tm_min << ":" << setw(2) <<  ltm->tm_sec << ( ltm->tm_hour < 12 ? " AM" : " PM");

    return;
}

void Pos_system::System_date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    cout << "Date: " <<  1 + ltm->tm_mon << "/" <<  ltm->tm_mday << "/" << 1900 + ltm->tm_year << endl;

}


class Admin_system : virtual public Pos_system
{
protected:
    string name;
    string companyname;
    string companydescrip;
    string branch;
    string email;
    string website;
    string telno;
    string faxno;

public:
    Admin_system(string n = "none", string c_name = "none", string b = "none", string e = "none", string w = "none", string tel_no = "none", string fax_no = "none");
    void user_pwd_enter();
    void user_pwd_setup();
    void user_pwd_change();
    void user_pwd_reset();
    bool user_pwd_reset_confirm();
    void user_pwd_reset_setup();
    void user_info_setup();
    bool user_verify(string);
    bool pwd_verify(string);
    void save_Admin_data();
    bool load_Admin_data();
    void save_usr_pwd();
    void user_info_modify();
};

Admin_system::Admin_system(string n, string c_name, string b, string e, string w, string tel_no, string fax_no)
{
    name = n;
    companyname = c_name;
    branch = b;
    email = e;
    website = w;
    telno = tel_no;
    faxno = fax_no;
}

void Admin_system::user_info_modify()
{
     cout << "               modify: please enter the following info: " << endl
         << "               --------------------------------------- " << endl;
    bool loop = true;

    cout << setw(27) << "owner name: "; getline(cin, name);
    cout << setw(27) << "company name: "; getline(cin, companyname);
    cout << setw(27) << "company description: "; getline(cin, companydescrip);
    cout << setw(27) << "branch: "; getline(cin, branch);

    while(loop)
    {
        try
        {
            cout << setw(27) << "email: "; getline(cin, email);
            if(chck_email(email)){
                break;
            }
            else{
                throw email;
            }
        }
        catch(string email)
        {
            cout << "invalid " << email << " email address " << endl;
            continue;
        }
    }

    while(loop)
    {
        try
        {
              cout << setw(27) << "website: "; getline(cin, website);
              if(chck_website(website)){
                break;
              }
              else{
                throw website;
              }

        }
        catch(string website)
        {
            cout << "invalid website the domain is invalid or it is subdomain" << endl;
            continue;
        }
    }

    while(loop)
    {
        try
        {
            cout << setw(27) << "telephone no.: "; getline(cin, telno);
            if(ifnumber(telno))
                break;
            else
                throw telno;
        }
        catch(string telno)
        {
            cout << setw(27) << telno << " does have a letter" << endl;
            continue;
        }
    }

    while(loop)
    {
        try
        {
            cout << setw(27) << "fax no.: "; getline(cin, faxno);
            if(ifnumber(faxno))
                break;
            else
                throw faxno;
        }
        catch(string faxno)
        {
            cout << setw(27) << faxno << " does have a letter" << endl;
            continue;
        }
    }

    return;
}

void Admin_system::save_Admin_data()
{
    string filename = "Admin.txt";
    ofstream outFile;
    outFile.open(filename.c_str());

    while(outFile.fail())
    {
        cout << "file either corrupt or erased" << endl;
        return;
    }

    outFile << name << endl
            << companyname << endl
            << branch << endl
            << email << endl
            << website << endl
            << telno << endl
            << faxno << endl;

    return;
}

void Admin_system::user_pwd_reset_setup()
{
    cout << "               reset: please enter your username and password             " << endl
         << "               ----------------------------------------------             " << endl;
    bool loop = true;

    while(loop){
    try{
    cout << "\n               new username: "; getline(cin, username);
    if(chck_symbols(username)){
    if(chck_str(username)){
        break;
    }
    else{
        throw username;
    }
    }
    else
    {
        cout << "               the username you type cannot include symbols:";
        continue;
    }
    }
    catch(string username)
    {
        cout << "               username " << inputusername << " not too strong " << endl;
        continue;
    }
    }

    while(loop){
    try{
    cout << "\n               new password: "; getline(cin, password);
    if(chck_symbols(password)){
    if(chck_str(password)){
        break;
    }
    else{
        throw password;
    }
    }
    else
    {
        cout << "\n               the password you type cannot include symbols:";
        continue;
    }
    }
    catch(string password)
    {
        cout << "\n               password: " << inputpassword << " not too strong "<< endl;
        continue;
    }
    }

    return;
}

bool Admin_system::user_pwd_reset_confirm()
{
    bool loop = true;
    string filename = "resetcode.txt";
    string resetcode;
    string inputstrng;
    ifstream inFile;
    inFile.open(filename.c_str());

    while(inFile.fail())
    {
        cout << "failed to load the resetcode: " << endl;
        return false;
    }

    inFile >> resetcode;

    while(loop){
    try
    {
        cout << "                       enter the reset code: "; getline(cin, inputstrng);
        if(inputstrng == resetcode)
            break;
        else
            throw inputstrng;
    }
    catch(string inputstrng)
    {
        cout << "                       invalid code: " << endl
             << "                       note:look for the text generated code and enter the code" << endl;
        continue;
    }
    }

    return true;
}

void Admin_system::user_pwd_reset()
{
    string filename = "resetcode.txt";
    ofstream outFile;
    outFile.open(filename.c_str());
    long int randomcode;

    while(outFile.fail())
    {
        cout << filename << " not found " << endl;
    }

    srand(time(NULL));
    randomcode = 1 + rand() % 100000;

    outFile << randomcode << endl;

    if(user_pwd_reset_confirm())
        user_pwd_reset_setup();

    return;
}

bool Pos_system::ifnumber(string check)
{
    for(int i = 0; i < int(check.length()); i++)
    {
        if(isalpha(check.at(i)))
            return false;
        else
            continue;
    }

    return true;
}

void Admin_system::user_info_setup()
{
    cout << "               setup: please enter the following info: " << endl
         << "               --------------------------------------- " << endl;
    bool loop = true;

    cout << setw(27) << "owner name: "; getline(cin, name);
    cout << setw(27) << "company name: "; getline(cin, companyname);
    cout << setw(27) << "company description: "; getline(cin, companydescrip);
    cout << setw(27) << "branch: "; getline(cin, branch);

    while(loop)
    {
        try
        {
         cout << setw(27) << "email: "; getline(cin, email);
         if(chck_email(email)){
            break;
         }
         else{
            throw email;
         }
        }
        catch(string email)
        {
            cout << "invalid email address " << email << endl;
            continue;
        }

    }

    while(loop)
    {
        try
        {
             cout << setw(27) << "website: "; getline(cin, website);
             if(chck_website(website)){
                break;
             }
             else{
                throw website;
             }
        }
        catch(string website)
        {
            cout << "invalid website or it is a subdomain" << endl;
            continue;
        }
    }

    while(loop)
    {
        try
        {
            cout << setw(27) << "telephone no.: "; getline(cin, telno);
            if(chck_symbols(telno))
                break;
            else
                throw telno;
        }
        catch(string telno)
        {
            cout << setw(27) << telno << " does have a letter or symbols" << endl;
            continue;
        }
    }

    while(loop)
    {
        try
        {
            cout << setw(27) << "fax no.: "; getline(cin, faxno);
            if(chck_symbols(faxno))
                break;
            else
                throw faxno;
        }
        catch(string faxno)
        {
            cout << setw(27) << faxno << " does have a letter or symbols" << endl;
            continue;
        }
    }

    return;
}

bool Admin_system::load_Admin_data()
{
    string filename = "Admin.txt";
    ifstream inFile;
    inFile.open(filename.c_str());

    while(inFile.fail())
        return false;

    inFile >> name >> companyname >> companydescrip >> branch >> email >> website;
    return true;
}

void Admin_system::save_usr_pwd()
{
    string filename = "Data.txt";
    ofstream outFile;
    outFile.open(filename.c_str());

    while(outFile.fail()){
        cout << "failed to load the filename " << filename << endl;
    }

    outFile << username << endl
            << password << endl;


    return;
}

bool Pos_system::load_usr_pwd()
{
    string filename = "Data.txt";
    ifstream inFile;

    inFile.open(filename.c_str());


    while(inFile.fail())
    {
        return true;
    }

    inFile >> username >> password;

    return false;
}

bool Admin_system::user_verify(string usr)
{
    if(usr == username)
        return true;
    else
        return false;
}

bool Admin_system::pwd_verify(string pwd)
{
    if(pwd == password)
        return true;
    else
        return false;
}

void Admin_system::user_pwd_enter()
{
    bool loop = true;

    while(loop)
    {
        try
        {
            cout << setw(33) << "username: "; getline(cin, inputusername);
            if(user_verify(inputusername)){
                break;
            }
            else{
                throw username;
            }
        }
        catch(string username)
        {
            cout << setw(33) << "invalid username: " << endl;
            continue;
        }
    }

    while(loop)
    {
        try
        {
            cout << setw(33) << "password: "; getline(cin, inputpassword);
            if(pwd_verify(inputpassword)){
                break;
            }
            else{
                throw password;
            }
        }
        catch(string inputpassword)
        {
            cout << setw(33) << "invalid password: " <<  endl;
            continue;
        }
    }

    return;
}

void Admin_system::user_pwd_change()
{
    bool loop1 = true;

    while(loop1){
    try
    {
    cout << "old username: "; getline(cin, inputusername);
    if(user_verify(inputusername)){
        while(loop1){
            cout << "enter new username: "; getline(cin, inputusername);
            if(chck_symbols(inputusername)){
                if(chck_str(inputusername)){
                        if(user_verify(inputusername)){
                            cout << "same username enter a new one: " << endl;
                            continue;
                        }
                        else{
                            username = inputusername;
                            break;
                        }
                }
                else{
                    cout << "username not too strong" << endl;
                    continue;
                }
            }
            else{
                cout << "username cannot include symbols " << endl;
                continue;
            }
                break;
        }
        break;
    }
    else{
        throw inputusername;
    }
    }
    catch(string inputusername)
    {
        cout << "wrong username: " << endl;
        continue;
    }
    }

    while(loop1){
    try
    {
    cout << "old password: "; getline(cin, inputpassword);
    if(pwd_verify(inputpassword)){
        while(loop1){
            cout << "enter new password: "; getline(cin, inputpassword);
            if(chck_symbols(inputpassword)){
                if(chck_str(inputpassword)){
                        if(pwd_verify(inputpassword)){
                            cout << "same password entered enter a new one " << endl;
                            continue;
                        }
                        else{
                            password = inputpassword;
                            break;
                        }
                }
                else{
                    cout << "password not too strong" << endl;
                    continue;
                }
            }
            else{
                cout << "password cannot include symbols" << endl;
                continue;
            }
                break;
        }
        break;
    }
    else{
        throw inputusername;
    }
    }
    catch(string inputusername)
    {
        cout << "wrong username: " << endl;
        continue;
    }
    }

    save_usr_pwd();

    return;
}

void Admin_system::user_pwd_setup()
{
    cout << "               setup: please enter your username and password             " << endl
         << "               ----------------------------------------------             " << endl;
    bool loop = true;

    while(loop){
    try{
    cout << "\n               new username: "; getline(cin, inputusername);
    if(chck_symbols(inputusername)){
    if(chck_str(inputusername)){
            username = inputusername;
        break;
    }
    else{
        throw inputusername;
    }
    }
    else
    {
        cout << "               the username you type cannot include symbols:";
        continue;
    }
    }
    catch(string inputusername)
    {
        cout << "               username " << inputusername << " not too strong " << endl;
        continue;
    }
    }

    while(loop){
    try{
    cout << "\n               new password: "; getline(cin, inputpassword);
    if(chck_symbols(inputpassword)){
    if(chck_str(inputpassword)){
        password = inputpassword;
        break;
    }
    else{
        throw inputpassword;
    }
    }
    else
    {
        cout << "\n               the password you type cannot include symbols:";
        continue;
    }
    }
    catch(string inputpassword)
    {
        cout << "\n               password: " << inputpassword << " not too strong "<< endl;
        continue;
    }
    }

    return;
}

bool Pos_system::chck_str(string checkstrng)
{
    int countstr1 = 0, countstr2 = 0;

    for(int i = 0; i < int(checkstrng.length()); i++){
        if(isdigit(checkstrng.at(i)))
            countstr1++;
        else if(isupper(checkstrng.at(i)))
            countstr1++;
        else
            countstr2++;
    }

    if(countstr1 > countstr2)
        if(checkstrng.length() < 5)
        return false;
        else
        return true;
    else
        return false;
}

bool Pos_system::chck_symbols(string checkstrng)
{
    for(int i = 0; i < int(checkstrng.length()); i++)
    {
        if(ispunct(checkstrng.at(i)))
            return false;
        else
            continue;
    }

    return true;

}

class Inventory_system: public virtual Admin_system, public virtual Pos_system
{
protected:
    int counter = 1;
    string productname[ROWMAXLIST][COLMAXLIST];
    string productstocks[ROWMAXLIST][COLMAXLIST];
    string price[ROWMAXLIST][COLMAXLIST];
    string expiredate[ROWMAXLIST][COLMAXLIST];

public:
    Inventory_system(string pn = "NONE", string ps = "NONE", string ed = "NONE", string d = "NONE");
    void inventory_display();
    void inventory_add();
    void inventory_delete();
    void inventory_modify();
    void inventory_save();
    void inventory_load();
    void inventory_search_manage(string);
    void inventory_search();
    void inventory_add_check();
    bool inventory_load_chck();
};

bool Inventory_system::inventory_load_chck()
{
    string filename1 = "Inventory.txt";
    string filename2 = "Dataloop.txt";
    ifstream check1, check2;
    check1.open(filename1.c_str());
    check2.open(filename2.c_str());

    if(check1.fail()){
        return false;
    }

    if(check2.fail()){
        return false;
    }

    return true;
}

Inventory_system::Inventory_system(string pn, string ps, string ed, string p)
{
    productname[ROWMAXLIST][COLMAXLIST] = pn;
    productstocks[ROWMAXLIST][COLMAXLIST] = ps;
    price[ROWMAXLIST][COLMAXLIST] = ed;
    expiredate[ROWMAXLIST][COLMAXLIST] = p;
}

void Inventory_system::inventory_delete()
{
    string mark = "delete";
    cout << "delete: " << endl;
    inventory_search_manage(mark);
    inventory_save();
    return;

}

void Inventory_system::inventory_load()
{
    string filename1 = "Inventory.txt";
    string filename2 = "Dataloop.txt";

    ifstream inFile1, inFile2;

    inFile1.open(filename1.c_str());
    inFile2.open(filename2.c_str());

    while(inFile1.fail()){
        cout << "you dont create the list create a list now" << filename1 << endl;
        return;
    }

    while(inFile2.fail()){
        cout << "create a list first" << filename2 << endl;
        return;
    }

    inFile2 >> rowcounter >> colcounter;

    for(int p = 0; p < rowcounter; p++)
    {
        for(int l = 0; l < colcounter; l++)
        {
            if(l == 0){
            inFile1 >> productname[p][l];
            }
            else if(l == 1){
                inFile1 >> productstocks[p][l];
            }
            else if(l == 2){
                inFile1 >> expiredate[p][l];
            }
            else if(l == 3){
                inFile1 >> price[p][l];
            }
            else{

            }
        }
    }


    return;
}

void Inventory_system::inventory_save()
{
    int counter = 1;
    string filename1 = "Inventory.txt";
    string filename2 = "Dataloop.txt";

    ofstream writeFile1, writeFile2;
    writeFile1.open(filename1.c_str());
    writeFile2.open(filename2.c_str());

    while(writeFile1.fail()){
        cout << "the file is either corrupt or delete: " << endl;
        return;
    }

    while(writeFile2.fail()){
        cout << "the file is either corrupt or delete: " << endl;
        return;
    }

    writeFile1 << setiosflags(ios::left);
    for(int j = 0; j < rowcounter; j++)
    {
        for(int i = 0; i < colcounter; i++)
        {
            if(i == 0){
                writeFile1 << setw(18)<< productname[j][i];
            }
            else if(i == 1){
                writeFile1 << setw(11)<< productstocks[j][i];
            }
            else if(i == 2){
                writeFile1 << setw(15)<< expiredate[j][i];
            }
            else if(i == 3){
                writeFile1 <<  setw(1)<< price[j][i];
            }
            else{

            }
        }
        counter++;
        writeFile1 << endl;
    }



    writeFile2 << rowcounter << endl
               << colcounter << endl;

    return;

}

void Inventory_system::inventory_search_manage(string mark)
{
    bool loop = true;
    string inputnum1, inputnum2, inputnum3, delinput1, delinput2;
    string counter1;
    ostringstream conv_string1 ,conv_string2;
    int a, i, d, conv_delinput1_int, conv_delinput2_int;
    int tempstring1_int, deleted_stocks, tempstring2_int, deleted_price;


    cout << "test: " << endl
         << "search list no.: "; getline(cin, inputnum1);


    counter1 = inputnum1;
    a = atoi(inputnum1.c_str());
    a--;
        cout << "for list no. " << counter1 << endl
             << "1.product name. " << endl
             << "2.stock " << endl
             << "3.expiration date" << endl
             << "4.price" << endl;

        getline(cin, inputnum2);
        i = atoi(inputnum2.c_str());
        i--;

        if(mark == "modify"){
            while(loop){
            try{
            if(i == 0){
                cout << "for list no. " << counter1 << endl
                     << "productname: "; getline(cin, productname[a][i]);
                     return;
            }
            else if(i == 1){
                 while(loop){
                 cout << "for list no. " << counter1 << endl
                      << "no of stocks: "; getline(cin,productstocks[a][i]);
                      if(ifletter(productstocks[a][i])){
                        return;
                      }
                      else{
                        cout << "you type a letter " << endl;
                        continue;
                      }
                      }
            }
            else if(i == 2){
                 cout << "for list no " << counter1 << endl
                      << "expiredate:";  getline(cin, expiredate[a][i]);
                      return;
            }
            else if(i == 3){
                cout << "for list no " << counter << endl
                     << "price: "; getline(cin, price[a][i]);
                     return;
            }
            }
            catch(int i ){
                cout << "invalid number" << endl;
                continue;
            }
        }
        }
        else if(mark == "delete")
        {
            if(i == 0){
                productname[a][i] = "none";
                cout << "for list no. " << counter1 << endl
                     << "productname: " << productname[a][i] << " has been deleted" << endl;
                     return;
            }
            else if(i == 1){
                 cout << "for list no. " << counter1 << endl
                      << "no of stocks: " <<  productstocks[a][i] << endl;
                 cout << "1.delete all" << endl
                      << "2.input a number" << endl;
                      while(loop){
                      try{
                      getline(cin, inputnum3);
                      d = atoi(inputnum3.c_str());
                      if(d == 1){
                         productstocks[a][i] = "0";
                         cout << "number of stocks has been deleted" << endl;
                         return;
                      }
                      else if(d == 2){
                        cout << "enter the number of stocks to be deleted: ";
                        getline(cin, delinput1);
                        conv_delinput1_int = atoi(delinput1.c_str());
                        tempstring1_int = atoi(productstocks[a][i].c_str());
                        deleted_stocks = tempstring1_int - conv_delinput1_int;
                        if(deleted_stocks < 0){
                            deleted_stocks = 0;
                            return;
                        }
                        else{
                            conv_string1 << deleted_stocks;
                            productstocks[a][i] = conv_string1.str();
                            return;
                        }
                      }
                      else{
                            throw d;
                      }
                      }
                      catch(int d){
                          cout << "invalid number: " << d << endl;
                          continue;
                      }
                      }
            }

            else if(i == 2){
                 expiredate[a][i] = "none";
                 cout << "for list no " << counter1 << endl
                      << "expiredate: stored has been deleted " << endl;
            }
            else if(i == 3){
                cout << "for list no. " << counter1 << endl
                      << "price: " <<  price[a][i] << endl;
                 cout << "1.delete all" << endl
                      << "2.reduce the price: " << endl;
                      while(loop){
                      try{
                      getline(cin, inputnum3);
                      d = atoi(inputnum3.c_str());
                      if(d == 1){
                         price[a][i] = "0";
                         cout << "price in the list" << counter << "has been deleted" << endl;
                         return;
                      }
                      else if(d == 2){
                        cout << "enter a number to reduce: ";
                        getline(cin, delinput2);
                        conv_delinput2_int = atoi(delinput2.c_str());
                        tempstring2_int = atoi(price[a][i].c_str());
                        deleted_price = tempstring2_int - conv_delinput2_int;
                        if(deleted_price < 0){
                            deleted_price = 0;
                            return;
                        }
                        else{
                            conv_string2 << deleted_price;
                            price[a][i] = conv_string2.str();
                            return;
                        }
                      }
                      else{
                            throw d;
                      }
                      }
                      catch(int d){
                          cout << "invalid number: " << d << endl;
                          continue;
                      }
                      }

            }
        }
        else {cout << "mark values has not found";}
    return;
}

void Inventory_system::inventory_modify()
{
    string mark = "modify";
    cout << ":modify " << endl;
    inventory_search_manage(mark);
    inventory_save();
    cout << "the info was modified " << endl;
    return;
}

void Inventory_system::inventory_display()
{
    int counter = 1;
    inventory_load();
    if(load_Admin_data()){
            cout << "               " << companyname << "   inventory list " << endl
                 << "           -------------------------------" << endl;
            cout << "-----------------------------------------------------------" << endl
                 << "list no  Product name  no of stocks  expiration date  price" << endl
                 << "-------  ------------  ------------  ---------------  -----" << endl;

    cout << setiosflags(ios::left);
    for(int j = 0; j < rowcounter; j++)
    {
        cout <<  setw(10) << counter;
        for(int i = 0; i < colcounter; i++)
        {
            if(i == 0){
                cout << setw(18)<< productname[j][i];
            }
            else if(i == 1){
                cout << setw(11)<< productstocks[j][i];
            }
            else if(i == 2){
                cout  << setw(15)<< expiredate[j][i];
            }
            else if(i == 3){
                cout <<  setw(1)<< price[j][i];
            }
            else{

            }
        }
        counter++;
        cout << endl;
    }
    }
    else{
        cout << "cannot draw info" << endl;
        return;
    }
    return;
}

void Inventory_system::inventory_add()
{
    string filename1 = "Inventory.txt";
    string filename2 = "Dataloop.txt";
    ifstream chckfile1, chckfile2;
    chckfile1.open(filename1.c_str());
    chckfile2.open(filename2.c_str());

    const int COL = 4;
    int ROW = 0;
    int counter;
    bool loop = true;
    string key;

    if(chckfile1.fail() && chckfile2.fail()){
    ROW++;
    for(int j = 0; j < ROW; j++)
    {
        rowcounter++;
        counter = rowcounter;
        cout << "for list no. " << counter << endl;
        for(int i = 0; i < COL; i++)
        {
            colcounter++;
            if(i == 0){
            cout << "product name: "; getline(cin,productname[j][i]);
            }
            if(i == 1){
                cout << "number of stocks: "; getline(cin, productstocks[j][i]);
            }
            else if(i == 2){
                cout << "expiration date: "; getline(cin, expiredate[j][i]);
            }
            else if(i == 3){
                cout << "price: "; getline(cin, price[j][i]);
            }
            else{

            }

        }

        inventory_save();

         while(loop)
              {
              cout << "add another one? (y or n):";
              getline(cin ,key);
              transform(key.begin(), key.end(), key.begin(), ::tolower);
            try
            {
                if(key == "y"){
                    ROW++;
                    break;
                }
                else if(key == "n"){
                    return;
                }
                else{
                    throw key;
                }
            }
            catch(string key)
            {
                cout << "invalid leter: " << endl;
                continue;
            }

        }
        counter++;
        }
    }
    else{
        chckfile2 >> rowcounter >> colcounter;
        rowcounter++;
        cout <<"at rowcounter chck file" << rowcounter << endl;
        for(; rowcounter < ROWMAXLIST; rowcounter++)
        {
        counter = rowcounter;
        rowcounter--;
        cout << "(fuck)for list no. " << counter << endl;
        for(int i = 0; i < COL; i++)
        {
            if(i == 0){
            cout << "product name: "; getline(cin,productname[rowcounter][i]);
            }
            if(i == 1){
                cout << "number of stocks: "; getline(cin, productstocks[rowcounter][i]);
            }
            else if(i == 2){
                cout << "expiration date: "; getline(cin, expiredate[rowcounter][i]);
            }
            else if(i == 3){
                cout << "price: "; getline(cin, price[rowcounter][i]);
            }
            else{

            }
        }

        ///***********************************///
        while(loop)
              {
              rowcounter++;
              cout << "add another one? (y or n):";
              getline(cin ,key);
              transform(key.begin(), key.end(), key.begin(), ::tolower);
            try
            {
                if(key == "y"){
                        rowcounter++;
                    break;
                }
                else if(key == "n"){
                    inventory_save();
                    cout << "test" << endl;
                    return;
                }
                else{
                    throw key;
                }
            }
            catch(string key)
            {
                cout << "invalid leter: " << endl;
                continue;
            }

        }
        ///***********************************///

        }
        inventory_save();
    }

    return;
}

///has some bugs///
class Billing_system : public virtual Admin_system, public virtual Inventory_system, public virtual Pos_system
{
protected:
    int rowcounter2 = 0;
    int colcounter2 = 4;
    double total2 = 0;
    double amt_to_pay = 0;
    double amt_stocks_to_get = 0;
    double change = 0;
    string bill_productname[ROWMAXLIST][COLMAXLIST];
    string bill_productstocks[ROWMAXLIST][COLMAXLIST];
    string bill_expiredate[ROWMAXLIST][COLMAXLIST];
    string bill_price[ROWMAXLIST][COLMAXLIST];
public:
    void bill_display();
    int bill_inventory_update(string);
    void bill_search_manage(string, string);
    void bill_save();
    void bill_add();
    void bill_clear();
    void bill_load();
    void bill_print_receipt();
    void bill_totalize(double);
    void bill_transaction();
    void bill_transaction_finalize(double);
    bool bill_load_chck();
};

bool Billing_system::bill_load_chck()
{
    string filename1 = "Inventory.txt";
    string filename2 = "Dataloop.txt";
    ifstream check1, check2;
    check1.open(filename1.c_str());
    check2.open(filename2.c_str());

    if(check1.fail()){
        return false;
    }

    if(check2.fail()){
        return false;
    }

    return true;
}

void Billing_system::bill_print_receipt()
{
    string filename = "receipt.txt";
    ofstream WriteReceipt;
    int bill_receipt_counter = 1;
    WriteReceipt.open(filename.c_str());

    if(WriteReceipt.fail()){
        cout << "failed to write the file " << filename << endl;
        return;
    }

    WriteReceipt << "           company name: " << companyname << "  tel no.: " << telno << "  website: " << website << endl
                 << "           email: " << email << "          fax no.: " << faxno << "  branch: " << branch << endl
                 << "           owner: " << name << endl
                 << "                       Billing list " << endl
                 << "               -------------------------------" << endl;
    WriteReceipt << "------------------------------------------------------------------" << endl
                 << "list no  Product name    quantity    expiration date  price  total" << endl
                 << "-------  ------------  ------------  ---------------  -----  -----" << endl;

    WriteReceipt << setiosflags(ios::left);
    for(int j = 0; j < rowcounter2; j++)
    {
        WriteReceipt <<  setw(10) << bill_receipt_counter;
        for(int i = 0; i < colcounter2; i++)
        {
            if(i == 0){
                WriteReceipt << setw(18)<< bill_productname[j][i];
            }
            else if(i == 1){
                WriteReceipt << setw(11)<< bill_productstocks[j][i];
            }
            else if(i == 2){
                WriteReceipt  << setw(15)<< bill_expiredate[j][i];
            }
            else if(i == 3){
                WriteReceipt <<  setw(7)<< bill_price[j][i] << setw(2) << bill_price[j][i];
            }
            else{

            }
        }
        bill_receipt_counter++;
        WriteReceipt << endl;
    }
    WriteReceipt << "-------------------------------------------------------------------" << endl
                 << "                                                      total: " << total2 << endl
                 << "                                                      change: " << change << endl;

    return;
}

void Billing_system::bill_clear()
{
    bool loop = true;
    string input1;
    while(loop){
    cout << "clear: y or n : ";
    getline(cin,input1);
    if(ifnumber(input1)){
        cout << "you type a number" << endl;
        continue;
    }
    else if(input1 == "y" || input1 == "Y"){
        total2 = 0;
        rowcounter2 = 0;
        cout << "has been cleared" << endl;
        rowcounter++;
        break;
    }
    else if(input1 == "n" || input1 == "N"){
        break;
    }
    else{
        cout << "invalid choice: " << endl;
        continue;
    }
    }


    return;
}

int Billing_system::bill_inventory_update(string input1)
{
    ostringstream conv_str_int;
    int curr_inventory, updated_inventory;
    int conv_input1_int;

    conv_input1_int = atoi(input1.c_str());
    conv_input1_int--;

    curr_inventory = atoi(productstocks[conv_input1_int][1].c_str());
    curr_inventory--;
    updated_inventory = curr_inventory;
    if(updated_inventory < 0){
        cout << "the number you've entered exceended your stocks:";
    }
    else{
        conv_str_int << updated_inventory;
        productstocks[conv_input1_int][1] = conv_str_int.str();
        inventory_save();
    }

    return 1;
}

void Billing_system::bill_transaction_finalize(double amt_to_pay)
{
    change = amt_to_pay - total2;
}

void Billing_system::bill_transaction()
{
    bool loop = true;
    string str_amt_to_pay;
    while(loop){
    cout << "amount to pay: "; getline(cin, str_amt_to_pay);
    if(ifletter(str_amt_to_pay)){
        amt_to_pay = atof(str_amt_to_pay.c_str());
        bill_transaction_finalize(amt_to_pay);
        break;
    }
    else{
     cout << "you type a letter" << endl;
     continue;

    }
    }
    return;
}

void Billing_system::bill_totalize(double total1)
{
    total2 = total2 + total1;
    return;
}

void Billing_system::bill_load()
{
    string filename1 = "Bill.txt";
    string filename2 = "Billloop.txt";

    ifstream loadFile1, loadFile2;

    loadFile1.open(filename1.c_str());
    loadFile2.open(filename2.c_str());

    while(loadFile1.fail()){
        cout << "failed to load the file " << filename1 << endl;
        return;
    }

    while(loadFile2.fail()){
        cout << "failed to load the file " << filename2 << endl;
        return;
    }

    loadFile2 >> rowcounter2 >> colcounter2;

    for(int p = 0; p < rowcounter2; p++)
    {
        for(int l = 0; l < colcounter2; l++)
        {
            if(l == 0){
            loadFile1 >> bill_productname[p][l];
            }
            else if(l == 1){
                loadFile1 >> bill_productstocks[p][l];
            }
            else if(l == 2){
                loadFile1 >> bill_expiredate[p][l];
            }
            else if(l == 3){
                loadFile1 >> bill_price[p][l];
            }
            else{

            }
        }
    }

    return;
}

void Billing_system::bill_save()
{
    string filename3 = "Bill.txt";
    string filename4 = "Billloop.txt";
    ofstream saveFile1, saveFile2;
    saveFile1.open(filename3.c_str());
    saveFile2.open(filename4.c_str());

    while(saveFile1.fail()){
        cout << "failed to SAVE the file " << filename3 << endl;
        return;
    }

    while(saveFile2.fail()){
        cout << "failed to SAVE the file " << filename4 << endl;
        return;
    }

    saveFile2 << rowcounter2 << endl
              << colcounter2 << endl;

    saveFile1 << setiosflags(ios::left);
    for(int l = 0; l < rowcounter2; l++)
    {
        for(int b = 0; b < colcounter2; b++)
        {
            if(b == 0){
                saveFile1 << setw(18)<< bill_productname[l][b];
            }
            else if(b == 1){
                saveFile1 << setw(11)<< bill_productstocks[l][b];
            }
            else if(b == 2){
                saveFile1  << setw(15)<< bill_expiredate[l][b];
            }
            else if(b == 3){
                saveFile1 <<  setw(1)<< bill_price[l][b];
            }
            else{

            }
        }
        saveFile1 << endl;
    }

    return;

}

void Billing_system::bill_search_manage(string input1, string mark)
{
    ostringstream conv_str;
    inventory_load();
    int conv_input1_int = atoi(input1.c_str());
    double total1 = 0;
    conv_input1_int--;

    if(mark == "add"){
        bill_productname[rowcounter2][0] = productname[conv_input1_int][0];
        conv_str <<  bill_inventory_update(input1);
        bill_productstocks[rowcounter2][1] = conv_str.str();
        bill_expiredate[rowcounter2][2] = expiredate[conv_input1_int][2];
        bill_price[rowcounter2][3] = price[conv_input1_int][3];
        total1 = atof(bill_price[rowcounter2][3].c_str());
        bill_totalize(total1);
        rowcounter2++;
    }
    else{}

    return;

}

void Billing_system::bill_add()
{
    bool loop = true;
    string input1;
    string mark = "add";
    while(loop){
    cout << "add: " << endl
         << "enter a list no. to add: " << endl;
    getline(cin,input1);
    if(ifletter(input1)){
    bill_search_manage(input1, mark);
    bill_save();
    break;
    }
    else{
    cout << "you type a letter " << endl;
    continue;
    break;
    }
    }
    return;
}

void Billing_system::bill_display()
{
    int bill_display_counter = 1;
    if(load_Admin_data()){
            cout << "           company name: " << companyname << "  tel no.: " << telno << "  website: " << website << endl
                 << "           email: " << email << "          fax no.: " << faxno << "  branch: " << branch << endl
                 << "           owner: " << name << endl
                 << "                       Billing list " << endl
                 << "               -------------------------------" << endl;
            cout << "------------------------------------------------------------------" << endl
                 << "list no  Product name    quantity    expiration date  price  total" << endl
                 << "-------  ------------  ------------  ---------------  -----  -----" << endl;

    cout << setiosflags(ios::left);
    for(int j = 0; j < rowcounter2; j++)
    {
        cout <<  setw(10) << bill_display_counter;
        for(int i = 0; i < colcounter2; i++)
        {
            if(i == 0){
                cout << setw(18)<< bill_productname[j][i];
            }
            else if(i == 1){
                cout << setw(11)<< bill_productstocks[j][i];
            }
            else if(i == 2){
                cout  << setw(15)<< bill_expiredate[j][i];
            }
            else if(i == 3){
                cout <<  setw(7)<< bill_price[j][i] << setw(2) << bill_price[j][i];
            }
            else{

            }
        }
        bill_display_counter++;
        cout << endl;
    }
        cout << "-------------------------------------------------------------------" << endl
             << "                                                      total: " << total2 << endl
             << "                                                      change: " << change << endl;
    }
    else{cout << "cannot draw" << endl;}

}

int main()
{
    string input1, input2, input_bill_add, input_admin_menu, input_inventory_menu;
    int conv_input1_int, conv_input2_int ,  conv_input_bill_add_int, conv_input_admin_menu_int, conv_input_inventory_menu_int;
    bool loop = true;

    Admin_system admin;
    Pos_system main;
    Inventory_system inventory;
    Billing_system billing;

    if(admin.load_usr_pwd())
    {
     cout << "file not found (test)" << endl;
     admin.user_pwd_setup();
     admin.save_usr_pwd();
     cout << endl;
     admin.user_info_setup();
     admin.save_Admin_data();
    }

    if(admin.load_Admin_data()){
    main.System_date();
    main.System_time();
       cout << endl;
       cout << endl;
       cout << endl;
       cout << setw(45) << "-----------" << endl
            << setw(45) << "   login   " << endl
            << setw(45) << "-----------" << endl;
    admin.user_pwd_enter();
           ///sg fault//
            while(loop){
                try
                {
                 cout << endl;
                 cout << setw(45) << "Main menu:" << endl
                      << setw(45) << "---------" << endl
                      << setw(45) << "1.Billing menu" << endl
                      << setw(45) << "2.Admin menu" << endl
                      << setw(45) << "3.Inventory menu" << endl
                      << setw(45) << "4.exit" << endl;
                 cout << setw(45) << "enter: "; getline(cin, input1);
                 ///for billing menu
                 conv_input1_int = atoi(input1.c_str());
                 if(conv_input1_int == 1){
                        if(billing.bill_load_chck()){
                        while(loop){
                        try{
                        cout << setw(45) << "Billing menu" << endl
                             << setw(45) << "------------" << endl
                             << setw(45) << "1.add an item" << endl
                             << setw(45) << "2.back " << endl;
                        cout << setw(45) << "enter: "; getline(cin, input2);
                        conv_input2_int = atoi(input2.c_str());
                        ///*********************///
                        if(conv_input2_int == 1){
                            inventory.inventory_load();
                            inventory.inventory_display();
                            billing.bill_add();
                            billing.bill_save();
                            billing.bill_load();
                            billing.bill_display();
                            while(loop){
                            try{
                            cout << setw(45) << "options: " << endl
                                 << setw(45) << "-------" << endl
                                 << setw(45) << "1.add another item" << endl
                                 << setw(45) << "2.clear the list" << endl
                                 << setw(45) << "3.finalize" << endl
                                 << setw(45) << "4.print the receipt" << endl
                                 << setw(45) << "5.back" << endl;
                            cout << setw(45) << "enter: "; getline(cin, input_bill_add);
                            conv_input_bill_add_int = atoi(input_bill_add.c_str());
                            if(conv_input_bill_add_int == 1){
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    billing.bill_add();
                                    billing.bill_save();
                                    billing.bill_load();
                                    billing.bill_display();
                                    continue;
                            }
                            else if(conv_input_bill_add_int == 2){
                                    billing.bill_load();
                                    billing.bill_clear();
                                    billing.bill_save();
                                    continue;
                            }
                            else if(conv_input_bill_add_int == 3){
                                    billing.bill_load();
                                    billing.bill_display();
                                    billing.bill_transaction();
                                    billing.bill_display();
                                    billing.bill_save();
                                    continue;
                            }
                            else if(conv_input_bill_add_int == 4){
                                    billing.bill_load();
                                    billing.bill_print_receipt();
                                    cout << "the receipt has been printed " << endl;
                                    continue;

                            }
                            else if(conv_input_bill_add_int == 5){
                                    break;
                            }
                            else{
                                throw input_bill_add;
                            }
                            }
                            catch(string input_bill_add){
                                cout << "invalid input " << input_bill_add << endl;
                                continue;
                            }
                            }
                        }
                        ///*********************************/////
                        else if(conv_input2_int == 2){
                                break;

                        }
                        else{
                            throw input2;
                        }
                        }
                        catch(string input2){
                            cout << "invalid choice " << input2 << endl;
                            continue;
                        }
                        }
                        }
                        else{
                            cout << "create a list first " << endl;
                            continue;
                        }
                 }
                 ///billing menu///
                 ///admin menu///
                 else if(conv_input1_int == 2){
                        while(loop){
                        try{
                        cout << setw(45) << "Admin menu: " << endl
                             << setw(45) << "----------- " << endl
                             << setw(45) << "1.change the password and the user" << endl
                             << setw(45) << "2.modify the admin info" << endl
                             << setw(45) << "3.reset" << endl
                             << setw(45) << "4.back" << endl;
                        cout << setw(45) << "enter: "; getline(cin, input_admin_menu);
                        conv_input_admin_menu_int = atoi(input_admin_menu.c_str());
                        if(conv_input_admin_menu_int == 1){
                            admin.user_pwd_change();
                            admin.load_usr_pwd();
                            continue;
                        }
                        else if(conv_input_admin_menu_int == 2){
                            admin.user_info_modify();
                            admin.save_Admin_data();
                            if(admin.load_Admin_data()){}
                            continue;
                        }
                        else if(conv_input_admin_menu_int == 3){
                            admin.load_usr_pwd();
                            admin.user_pwd_reset();
                            admin.save_usr_pwd();
                            admin.load_usr_pwd();
                            continue;
                        }
                        else if(conv_input_admin_menu_int == 4){
                            break;
                        }
                        }
                        catch(string input_admin_menu){
                            cout << "invalid choice " << input_admin_menu << endl;
                            continue;
                        }
                        }
                 }
                 ///admin menu///
                 ///inventory menu// *** continue this tommorroww found sg fault
                 else if(conv_input1_int == 3){
                        while(loop){
                        try{
                            cout << setw(45) << "Inventory menu " << endl
                                 << setw(45) << "-------------- " << endl
                                 << setw(45) << "1.add a item " << endl
                                 << setw(45) << "2.delete " << endl
                                 << setw(45) << "3.modify an item " << endl
                                 << setw(45) << "4.display" << endl
                                 << setw(45) << "5.back " << endl;
                            cout << setw(45) << "enter: "; getline(cin, input_inventory_menu);
                            conv_input_inventory_menu_int = atoi(input_inventory_menu.c_str());
                            if(conv_input_inventory_menu_int == 1){
                                    inventory.inventory_load();
                                    inventory.inventory_add();
                                    inventory.inventory_save();
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    continue;
                            }
                            else if(conv_input_inventory_menu_int == 2){
                                    if(inventory.inventory_load_chck()){
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    inventory.inventory_delete();
                                    inventory.inventory_save();
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    continue;
                                    }
                                    else{
                                        cout << "create a list first " << endl;
                                        continue;
                                    }
                            }
                            else if(conv_input_inventory_menu_int == 3){
                                    if(inventory.inventory_load_chck()){
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    inventory.inventory_modify();
                                    inventory.inventory_save();
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    continue;
                                    }
                                    else{
                                        cout << "create a list first " << endl;
                                        continue;
                                    }
                            }
                            else if(conv_input_inventory_menu_int == 4){
                                    if(inventory.inventory_load_chck()){
                                    inventory.inventory_load();
                                    inventory.inventory_display();
                                    continue;
                                    }
                                    else{
                                        cout << "create a list first " << endl;
                                        continue;
                                    }
                            }
                            else if(conv_input_inventory_menu_int == 5)
                            {
                                break;
                            }
                            else{
                                throw input_inventory_menu;
                            }
                        }
                        catch(string input_inventory_menu){
                            cout << "invalid input " << input_inventory_menu << endl;
                            continue;
                        }
                        }
                 }
                 ///inventory menu///
                 else if(conv_input1_int == 4){
                        return 0;
                 }
                 else{
                    throw input1;
                 }
                }
                catch(string input1){
                    cout << setw(45) << "invalid choice " << input1 << endl;
                    continue;
                }
            }
    }
    else{
        cout << "file not found either corrupted or erased" << endl;
    }

    return 0;
}
