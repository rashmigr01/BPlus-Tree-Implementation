#include "function.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string fname;
    cout << "Enter n: ";
    cin >> num;
    Bptree tre;
    cout << "Enter the file name: ";
    cin >> fname;
    vector<vector<string> > data;
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            data.push_back(row);
        }
    }
    file.close();
    int l = data.size();
    for (int i = 0; i < data.size(); i++)
    {
        tre.insert(i);
    }

    while (true)
    {
        int cmd = 0;
        cout << "The commands:\n 1: search in B+ Tree\n 2: insert into B+ Tree\n 3: delete from B+ Tree\n 4: display B+ Tree\nEnter the number to choose the command:";
        cin >> cmd;
        if (cmd == 1)
        {
            int k;
            cout << "Enter the keys to be searched:";
            cin >> k;
            tre.search(k, data);
            int cm;
            cout << "Enter 0 to continue and 1 to exit:";
            cin >> cm;
            if (cm == 1)
            {
                break;
            }
            else if (cm == 0)
            {
                continue;
            }
            else
            {
                cout << "Invalid command";
            }
        }
        else if (cmd == 2)
        {
            cout << "Enter the values of the tuple that you need to insert:\n";
            vector<string> a;
            for (int i = 0; i < data[0].size(); i++)
            {
                string k;
                cin >> k;
                a.push_back(k);
            }
            data.push_back(a);
            tre.insert(data.size() - 1);
            fstream fi;
            fi.open(fname, ios::app);
            for(auto x : a){
                fi<<x<<',';
            }fi<<'\n';
            fi.close();
            int cm;
            cout << "Enter 0 to continue and 1 to exit:";
            cin >> cm;
            if (cm == 1)
            {
                break;
            }
            else if (cm == 0)
            {
                continue;
            }
            else
            {
                cout << "Invalid command";
            }
        }
        else if (cmd == 3)
        {
            int delkey;
            cout << "Enter the key that you need to delete:";
            cin >> delkey;
            tre.deletekey(delkey);
            int cm;
            cout << "Enter 0 to continue and 1 to exit:";
            cin >> cm;
            if (cm == 1)
            {
                break;
            }
            else if (cm == 0)
            {
                continue;
            }
            else
            {
                cout << "Invalid command";
            }
        }
        else if (cmd == 4)
        {
            dotf << "strict graph{\n";
            tre.display(tre.root, data);
            dotf << "}";
            dotf.close();
            cout << "The output is generated in output.dot file and image is generated in output.png file\n";
            system("dot -Tpng output.dot > output.png");
            int cm;
            cout << "Enter 0 to continue and 1 to exit:";
            cin >> cm;
            if (cm == 1)
            {
                break;
            }
            else if (cm == 0)
            {
                continue;
            }
            else
            {
                cout << "Invalid command";
            }
        }
        else
        {
            cout << "Invalid command";
        }
    }

    return 0;
}
