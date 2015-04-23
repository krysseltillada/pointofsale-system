#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

const int ROWMAXLIST = 1000;
const int COLMAXLIST = 4;

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
    void System_time();
    void System_date();
};

Pos_system::Pos_system(string user, string pass)
{
    username = user;
    password = pass;
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


class Admin_system : public Pos_system
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
    cout << setw(27) << "email: "; getline(cin, email);
    cout << setw(27) << "website: "; getline(cin, website);

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
    bool loop = true;

    while(loop){
    try
    {
    cout << "old username: "; getline(cin, inputusername);
    if(user_verify(inputusername)){
        while(loop){
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

    while(loop){
    try
    {
    cout << "old password: "; getline(cin, inputpassword);
    if(pwd_verify(inputpassword)){
        while(loop){
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

class Inventory_system: public Admin_system
{
protected:
    int counter = 1;
    string productname[ROWMAXLIST][COLMAXLIST];
    string productstocks[ROWMAXLIST][COLMAXLIST];
    string price[ROWMAXLIST][COLMAXLIST];
    string expiredate[ROWMAXLIST][COLMAXLIST];
    int rowcounter = 0;
    int colcounter = 0;

public:
    Inventory_system(string pn = "NONE", string ps = "NONE", string ed = "NONE", string d = "NONE");
    void inventory_display();
    void inventory_add();
    void inventory_delete();
    void inventory_modify();
    void inventory_save();
    void inventory_load();
    void inventory_update();
    void inventory_search_manage(string);
    void inventory_search();
};

Inventory_system::Inventory_system(string pn, string ps, string ed, string p)
{
    productname[ROWMAXLIST][COLMAXLIST] = pn;
    productstocks[ROWMAXLIST][COLMAXLIST] = ps;
    price[ROWMAXLIST][COLMAXLIST] = ed;
    expiredate[ROWMAXLIST][COLMAXLIST] = p;
}

void Inventory_system::inventory_load()
{
    string filename1 = "Inventory.txt";
    string filename2 = "Dataloop.txt";

    ifstream inFile1, inFile2;

    inFile1.open(filename1.c_str());
    inFile2.open(filename2.c_str());

    while(inFile1.fail()){
        cout << "failed to load the file " << filename1 << endl;
        return;
    }

    while(inFile2.fail()){
        cout << "failed to load the file " << filename2 << endl;
        return;
    }

    colcounter++;
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

    inFile2 >> rowcounter >> colcounter;

    return;
}

void Inventory_system::inventory_save()
{
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

    if(load_Admin_data()){
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
    }
    else{
        cout << "cannot draw info" << endl;
        return;
    }

    writeFile2 << rowcounter << endl
               << colcounter << endl;

    return;

}

void Inventory_system::inventory_search_manage(string mark)
{

    string inputnum1, inputnum2;
    string counter1;
    int a, i;


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
            if(i == 0){
                cout << "for list no. " << counter1 << endl
                     << "productname: "; getline(cin, productname[a][i]);
            }
            else if(i == 1){
                 cout << "for list no. " << counter1 << endl
                      << "no of stocks: "; getline(cin,productstocks[a][i]);
            }
            else if(i == 2){
                 cout << "for list no " << counter1 << endl
                      << "expiredate:";  getline(cin, expiredate[a][i]);
            }
            else if(i == 3){
                cout << "for list no " << counter << endl
                     << "price: "; getline(cin, price[a][i]);
            }
            else{

            }
        }
        else {}
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
    counter = 1;
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
    const int COL = 4;
    int ROW = 0;
    bool loop = true;
    string key;

    ROW++;
    for(int j = 0; j < ROW; j++)
    {
        rowcounter++;
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
                    inventory_display();
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


    return;
}

///not finished//
class Billing_system : public Admin_system, public Inventory_system
{
protected:
    string productname;
    string price;


public:
    void bill_display();
    void bill_display_options();
    void bill_inventory_update();
    void bill_transaction();
};

int main()
{

    Admin_system admin;
    Pos_system main;
    Inventory_system inventory;

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
    inventory.inventory_load();
    inventory.inventory_display();
    inventory.inventory_modify();
    inventory.inventory_display();
    }
    else{
        cout << "file not found either corrupted or erased" << endl;
    }

    return 0;
}

