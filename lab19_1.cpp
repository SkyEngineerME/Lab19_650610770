#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string fileN, vector<string> &n, vector<int> &score , vector<char> &grades){
    ifstream file(fileN);
    string s;
    char format[] = "%[^:]: %d %d %d";
    while(getline(file,s)){
     int x,y,z;
     char names[100];
     sscanf(s.c_str(),format,names,&x,&y,&z);
     n.push_back(names);
     score.push_back(x+y+z);
     grades.push_back(score2grade(x+y+z));
    }
    
}

void getCommand(string &command, string &key){  
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> name,vector<int> score, vector<char> grades, string key){
    int x = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i< name.size(); i++){
        if(key == toUpperStr(name[i])){
            cout << name[i] << "'s score = " << score[i] << endl;
            cout << name[i] << "'s grade = " << grades[i] << endl;
            x++;
        }else if(i == name.size()-1 && x == 0){
            cout << "Cannot found." << endl;
        }
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> name,vector<int> score, vector<char> grades, string key){
    int x = 0;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i< name.size(); i++){
        if(*key.c_str() == grades[i]){
            cout << name[i] << " (" << score[i] << ")" << endl;
            x++;
        }else if(i == name.size()-1 && x== 0){
            cout << "Cannot found." << endl;
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
