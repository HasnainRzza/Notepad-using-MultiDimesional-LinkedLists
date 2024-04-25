#include"text.cpp"
#include<iomanip>
#include<string>
#include<vector>

using namespace std;
vector<string> dict;
void load_datainvector()
{
    string fname="dictionary.txt";
    ifstream file(fname);
    string line;
    while(getline(file,line)){
        dict.push_back(line);
    }
    file.close();
   
}
class Node {
public:
    Node* above;
    Node* below;
    Node* after;
    Node* before;
    char data;

    Node(char d) {
        above = below = after = before = nullptr;
        data = d;
    }
};

class notepad {
public:
    Node* head;
    Node* curr;
    Node *cursor;

    notepad() {
        head = curr =cursor= nullptr;
    }
void makecursor(int move) {
    // Node* cursor = head;
    if (move == 72) {
        // Up arrow key
        if (cursor->above != nullptr) {
            cursor = cursor->above;
        }
    } else if (move == 80) {
        // Down arrow key
        if (cursor->below != nullptr) {
            cursor = cursor->below;
        }
    } else if (move == 75) {
        // Left arrow key
        if (cursor->before != nullptr) {
            cursor = cursor->before;
        }
    } else if (move == 77) {
        // Right arrow key
        if (cursor->after != nullptr) {
            cursor = cursor->after;
        }
    }
    else if(move==8)
    {
        if (cursor->before != nullptr) {
            Node* current = cursor;
            while (current != nullptr) {
                current->data = (current->after != nullptr) ? current->after->data : '\0';
                current = current->after;
            }
        }        
    }
    else if(move==19)
    {
        savetofile();
    }
}
void suggest() {
    string sub = "";
    vector<string> suggestions;
    Node* rowPtr = head;
    Node* colPtr = head;
    int clen = 0;
    int suggestionCount = 0;

    while (rowPtr != nullptr) {
        while (colPtr != nullptr) {
            if (colPtr->data != ' ' && colPtr->data != '\0') {
                sub += colPtr->data;
                colPtr->after;
            } else {
                colPtr = colPtr->after;
                int len = sub.length();
                for (string x : dict) {
                    if (x.find(sub) != string::npos && x.length() > sub.length()) {
                        suggestions.push_back(x);
                        sub = "";
                        suggestionCount++;
                        if (suggestionCount >= 3) {
                            // Return when we have 3 suggestions
                            for (const string& suggestion : suggestions) {
                                cout << "\nI suggest you making test as: " << suggestion;
                            }
                            return;
                        }
                        break;
                    }
                }
            }
        }
        colPtr = rowPtr->below;
        rowPtr = rowPtr->below;
    }

    // Print the last word if there is one
    if (!sub.empty()) {
        suggestions.push_back(sub);
    }

    for (const string& suggestion : suggestions) {
        cout << "\nI suggest you making test as: " << suggestion;
    }
    cout << "\n";
}

Node *addnewline()
{

    Node *tempcurr;
    for(int i=0;i<maxCharCount;i++)
    {
        Node *newnode=new Node('b');
        
        tempcurr->after=newnode;
        newnode->before=tempcurr;
        tempcurr=newnode;
    }
    while(tempcurr->before!=nullptr)
    {
        tempcurr=tempcurr->before;
    }
    return tempcurr;

}
void addtext()
{
   
    cout<<"Do you want to enter character:";
    char text='d';
    cin>>text;
    if(text=='y')
    {
        cout<<"Enter character: ";
        text=_getch();
        if (cursor->data == '\0') {
            cursor->data = text;
            cursor = cursor->after;
        } else {
            // Move all nodes' data after the cursor forward
            Node* current = cursor;
            Node* prev = nullptr;

            while (current != nullptr) {
                char temp = current->data;
                current->data = text;
                text = temp;  // Store the character to be moved to the next node
                prev = current;
                current = current->after;
            }
            cursor=cursor->after;
        
            }
        }
 

}

   void makegrid(int row, int col) {
        Node *t=nullptr;
        int v=0;
        if (!head) {
            Node* newnode = new Node('\0');
            head = curr = t=newnode;
        }
    
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col-1; j++) {
                Node* newnode = new Node('\0');
                while (curr->after != nullptr) {
                    curr = curr->after;

                    
                }
                curr->after = newnode;
                newnode->before = curr;
                curr = newnode;
            }

            while (curr->before != nullptr) {
                curr = curr->before;
           
            }
            v++;
            if(i!=row-1)
            {
                    Node* newnode = new Node('-');
                    curr->below = newnode;
                    newnode->above = curr;
                    curr = newnode;
                    
            }    
        }
        cursor=head;
        ogrid(row,col);
    }
    void ogrid(int row,int col)
    {
        Node *temp1=head;
        curr=head;
        Node *temp2=head->below;
        // int x=0;
        // cout<<curr->below;
        // while(curr->below!=nullptr)
        // {
        //     cout<<curr->data;
        //     curr=curr->below;
        //     // x++;
        // }
        // cout<<x;
        // cout<<temp2->data;
        for(int i=0;i<row;i++)
        {
                while(temp1->after!=nullptr &&temp2->after!=nullptr )
                {
                    temp2->above=temp1;
                    temp1->below=temp2;
                    temp1=temp1->after;
                    temp2=temp2->after;
                }
            
               while(temp1->before!=nullptr &&temp2->before!=nullptr)
               {
                temp1=temp1->before;
                temp2=temp2->before;
               }
               temp2=temp2->below;
               if(temp2==nullptr)
               return;
               temp1=temp1->below;
        }


    }

void savetofile() {
    string fname = "save.txt";
    ofstream file(fname);
    if (!file) {
        cout<<"\ncant open file."<<endl;
        return;
    }
    Node* rptr = head;
    Node* cptr = head;
    while (rptr != nullptr) {
        while (cptr != nullptr) {
            if (cptr->data != '\0') {
                file << cptr->data;
            }
            cptr = cptr->after;
        }
        file << "\n";
        cptr = rptr->below;
        rptr = rptr->below;
    }
    file.close();
}


void loadfile() {
    ifstream file("save.txt");
    if (!file) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    char c;
    Node* rowHead = head;
    Node* currentNode = head;

    while (file.get(c)) {
        if (c == '\n') {
            if (rowHead->below != nullptr) 
                {
                rowHead = rowHead->below;
                currentNode = rowHead; 
                } 
            }
        else 
        {
            if (currentNode != nullptr) {
                currentNode->data = c;
                currentNode = currentNode->after;
            } else {
                cerr << "Too much data for the grid. Data will be truncated." << endl;
                break;
            }
        }
    }

    file.close();
}


    void display() {
        cout<<cursor->data;
        cout << "\n\n\n";
        Node* rowPtr = head;
        Node* colPtr = head;

        while (rowPtr != nullptr) {
            while (colPtr != nullptr) {
                cout << colPtr->data << " ";
                colPtr = colPtr->after;
            }

            cout << "\n";
            colPtr = rowPtr->below;
            rowPtr = rowPtr->below;
        }
    }
    ~notepad() {
        deleteGrid(head);
    }

    void deleteGrid(Node* node) {
        if (node) {
            // Recursively delete the nodes below and to the right
            deleteGrid(node->below);
            deleteGrid(node->after);
            // Delete the current node
            delete node;
        }
    }    
};

int main() {
    load_datainvector();
    char user='\0';
    char text;
    string filename = "save.txt";
    FileAnalyzer analyzer(filename);
    analyzer.analyze();
    notepad obj;
    obj.makegrid(rowCounter, maxCharCount);
    obj.display();
    cout<<"Press C+l to load from file";
    int load=_getche();
    if(load==12)
    obj.loadfile();
    obj.display();
    int move=0;
    // int i=0;
 while (true) {
    // i++;
        move= _getch();

            move = _getch(); 
            obj.makecursor(move);
            obj.display();
            
        
         if (move == 27) {
            cout << "Escape key pressed. Exiting..." ;
            obj.deleteGrid(obj.head);
            obj.~notepad();
            break;
        }
        cin.clear();
        cout<<"\n Do you want to enter text y/n:";
        user=_getch();
        if(user=='y')
        {
            obj.addtext();
        }
        
 }  
        // obj.suggest();
    
 
    
    return 0;
}