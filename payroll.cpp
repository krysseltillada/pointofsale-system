#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ctime>

using namespace std;

class Admin
{
    private:
    string username;
    string password;
    string inputpassword;
    string inputusername;
    string name;
    string companyname;
    string companydescrip;
    string branch;
    string email;
    string website;
    string telno;
    string faxno;

    public:
    Admin(string user_name = "NULL", string pass_word = "NULL", string n = "none", string c_name = "none", string b = "none", string e = "none", string w = "none", string tel_no = "none", string fax_no = "none");
    void user_pwd_enter();
    void user_pwd_setup();
    void user_pwd_change();
    void user_pwd_reset();
    bool user_pwd_reset_confirm();
    bool chck_str(string);
    bool chck_symbols(string);
    bool user_verify(string);
    bool pwd_verify(string);
    bool load_usr_pwd();
    bool load_main_data();
    void save_usr_pwd();
    void user_info_setup();
    bool ifnumber(string);
};

Admin::Admin(string usr, string pwd, string n, string c_name, string b, string e, string w, string tel_no, string fax_no)
{
    username = usr;
    password = pwd;
    name = n;
    companyname = c_name;
    branch = b;
    email = e;
    website = w;
    telno = tel_no;
    faxno = fax_no;
}

bool Admin::user_pwd_reset_confirm()
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

void Admin::user_pwd_reset()
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
        user_pwd_setup();

    return;
}

bool Admin::ifnumber(string check)
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

void Admin::user_info_setup()
{
    cout << "               setup: please enter the following info: " << endl
         << "               --------------------------------------- " << endl;
    bool loop = true;

    cout << setw(27) << "owner name: "; getline(cin, name);
    cout << setw(27) << "company name: "; getline(cin, companyname);
    cout << setw(27) << "company description: "; getline(cin, companydescrip);
    cout << setw(27) << "branch: "; getline(cin, branch);
    cout << setw(27) << "email: "; getline(cin, email);
    cout << setw(27) << "website: "; getline(cin, email);

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

bool Admin::load_main_data()
{
    string filename = "Data.txt";
    ifstream inFile;
    inFile.open(filename.c_str());

    while(inFile.fail())
        return false;

    inFile >> username >> password;
    return true;
}

void Admin::save_usr_pwd()
{
    string filename = "Data.txt";
    ofstream outFile;
    outFile.open(filename.c_str());

    while(outFile.fail()){
        cout << "failed to load the filename " << filename << endl;
    }

    outFile << username << endl
            << password << endl;

    outFile << endl;

    outFile << name << endl;
    outFile << companyname << endl;
    outFile << companydescrip << endl;
    outFile << branch << endl;
    outFile << email << endl;
    outFile << website << endl;
    outFile << telno << endl;
    outFile << faxno << endl;

    return;
}

bool Admin::load_usr_pwd()
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

bool Admin::user_verify(string usr)
{
    if(usr == username)
        return true;
    else
        return false;
}

bool Admin::pwd_verify(string pwd)
{
    if(pwd == password)
        return true;
    else
        return false;
}

void Admin::user_pwd_enter()
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

void Admin::user_pwd_change()
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

void Admin::user_pwd_setup()
{
    cout << "               setup: please enter your username and password             " << endl
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

bool Admin::chck_str(string checkstrng)
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

bool Admin::chck_symbols(string checkstrng)
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

int main()
{

    Admin admin1;

    if(admin1.load_usr_pwd())
    {
     cout << "file not found (test)" << endl;
     admin1.user_pwd_setup();
     cout << endl;
     admin1.user_info_setup();
     admin1.save_usr_pwd();
    }

    if(admin1.load_main_data()){
       cout << setw(45) << "-----------" << endl
            << setw(45) << "   login   " << endl
            << setw(45) << "-----------" << endl;
    admin1.user_pwd_enter();
    admin1.user_pwd_change();

    }
    else{
        cout << "file not found either corrupted or erased" << endl;
    }

    return 0;
}
