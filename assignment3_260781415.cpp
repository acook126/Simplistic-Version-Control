//Andrew Cook
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Implementing the linked list as a class
class LinkedList
{
public:
    LinkedList(string a, int b, int c)
    {
        contents = a;
        version_number = b;
        hash = c;
        next = NULL;
    }

    LinkedList *add(LinkedList *temp, int hsh, string content)
    {
        // Loop through current list and add verison to list dynamically only if it is unique
        LinkedList *head = temp;
        while (true)
        {
            if (hsh == temp->hash)
            {
                cout << "git322 did not detect any change to your file and will not create a new version." << endl;
                break;
            }
            if (temp->next == NULL)
            {
                LinkedList *add = new LinkedList(content, temp->version_number + 1, hsh);
                temp->next = add;
                cout << "Your content has been added successfully." << endl;
                return head;
            }
            temp = temp->next;
        }
        LinkedList *nothing;
        return nothing;
    }
    int verisons(LinkedList *temp)
    {
        int num_versions = 0;
        while (temp != NULL)
        {
            num_versions++;
            temp = temp->next;
        }
        return num_versions;
    }
    void print(LinkedList *temp)
    {
        // Go through the whole list and print info of all verisons
        while (temp != NULL)
        {
            cout << "Version Number: " << temp->version_number << endl;
            cout << "Hash Value: " << temp->hash << endl;
            cout << "Content: " << temp->contents << endl;
            temp = temp->next;
        }
    }
    void load(LinkedList *temp, int version_num)
    {
        while (temp != NULL)
        {
            if (temp->version_number == version_num)
            {
                ofstream file;
                file.open("file.txt");
                file << temp->contents;
                file.close();
                cout << "Version " << version_num << " loaded successfully. Please refresh your text editor to seethe changes." << endl;
                break;
            }
            if (temp->next == NULL)
            {
                cout << "Please enter a valid version number. If you are not sure please press 'p' to list all valid version numbers." << endl;
                return;
            }
            temp = temp->next;
        }
    }
    void compare(LinkedList *temp, int version1, int version2)
    {
        string one, two;
        while (temp != NULL)
        {
            if (temp->version_number == version1)
                one = temp->contents;
            if (temp->version_number == version2)
                two = temp->contents;
            temp = temp->next;
        }
        // As long as there is lines in the file compare them
        if (!one.empty() && !two.empty())
        {
            // Extract one line each from both verisons
            istringstream l1(one);
            string line1;
            istringstream l2(two);
            string line2;
            int count = 1;
            // Compare the versions line by line
            while (true)
            {
                int c1 = 0;
                int c2 = 0;
                if (!getline(l1, line1))
                    c1++;
                if (!getline(l2, line2))
                    c2++;
                if (c1 == 1 && c2 == 1)
                    break;
                else if (c1 == 1)
                    line1 = "<Empty Line>";
                else if (c2 == 1)
                    line2 = "<Empty Line>";

                int h1 = std::hash<string>{}(line1);
                int h2 = std::hash<string>{}(line2);
                if (h1 != h2)
                {
                    cout << "Line " << count << ":" << line1 << " <<>> " << line2 << endl;
                }
                else
                {
                    cout << "Line " << count << ": <Identical>" << endl;
                }
                count++;
            }
        }
    }

    int search(LinkedList *temp, string keyword)
    {
        int count = 0;
        while (temp != NULL)
        {
            size_t finder = temp->contents.find(keyword);
            if (finder != string::npos)
            {
                if (count == 0)
                    cout << "The keyword '" << keyword << "' has been found in the following versions:" << endl;
                count++;
                cout << "Version Number: " << temp->version_number << endl;
                cout << "Hash Value: " << temp->hash << endl;
                cout << "Content: " << temp->contents << endl;
            }
            temp = temp->next;
        }
        return count;
    }

    void remove(LinkedList *temp, int version)
    {
        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                cout << "Please enter a valid version number." << endl;
                return;
            }
            if (temp->next->version_number == version)
            {
                LinkedList *a = temp->next->next;
                delete temp->next;
                temp->next = a;
                cout << "Version " << version << " deleted successfully." << endl;
                break;
            }
            temp = temp->next;
        }
    }

    string contents;
    int version_number;
    int hash;
    LinkedList *next;
};

class Git322
{
public:
    void addVersion()
    {
        ifstream ifs("file.txt");
        string content((istreambuf_iterator<char>(ifs)),
                       (istreambuf_iterator<char>()));
        int hsh = hash<string>{}(content);
        // Loop through current list and add verison to list dynamically only if it is unique
        mylist->next->add(mylist, hsh, content);
    }
    void printVersions()
    {
        LinkedList *temp = mylist->next;
        // Count the number of verions in the list
        int num_versions = temp->verisons(temp);
        cout << "Number of versions: " << num_versions << endl;
        temp = mylist->next;
        temp->print(temp);
    }

    void loadVersion(int version_num)
    {
        LinkedList *temp = mylist->next;
        temp->load(temp, version_num);
    }

    void compareVersions(int version1, int version2)
    {
        LinkedList *temp = mylist->next;
        temp->compare(temp, version1, version2);
    }

    void search(string keyword)
    {
        LinkedList *temp = mylist->next;
        int count = temp->search(temp, keyword);
        if (count == 0)
            cout << "Your keyword '" << keyword << "' was not found in any version." << endl;
    }

    void removeVersion(int version)
    {
        LinkedList *temp = mylist->next;
        temp->remove(temp, version);
    }

private:
    LinkedList *mylist = new LinkedList("", 0, 0);
};

class EnhancedGit322 : public Git322
{
public:
    void saveToFile()
    {
        int num_versions = 0;
        LinkedList *temp = mylist->next;
        while (temp != NULL)
        {
            num_versions++;
            temp = temp->next;
        }
        temp = mylist->next;
        ofstream file;
        file.open("versions.txt");
        file << num_versions << endl;
        while (temp != NULL)
        {

            file << temp->contents << endl;
            file << "__END OF CONTENT__" << endl;
            file << temp->hash << endl;
            file << temp->version_number << endl;
            temp = temp->next;
        }
        file.close();
    }

    void loadFromFile()
    {
        LinkedList *temp;
        ifstream file;
        file.open("versions.txt");

        int numberOfVersions = 0;
        string numvers;
        std::getline(file, numvers);
        if (!numvers.empty())
        {
            numberOfVersions = stoi(numvers);
            temp = new LinkedList("", 0, 0);
            mylist->next = temp;
        }

        for (int i = 0; i < numberOfVersions; i++)
        {
            string full_content;
            string content;
            string hsh;
            string vnum;

            while (true)
            {
                std::getline(file, content);
                if (content != "__END OF CONTENT__")
                {
                    full_content.append(content);
                    if (full_content.back()!='\n')
                    {
                        full_content.append("\n");
                    }
                }
                else
                    break;
            }
            std::getline(file, hsh);
            std::getline(file, vnum);

            temp->contents = full_content;
            temp->hash = stoi(hsh);
            temp->version_number = stoi(vnum);

            if(i<numberOfVersions-1){
                LinkedList *temp2=new LinkedList("",0,0);
                temp->next=temp2;
                temp=temp->next;

            }
        }
    }

    void addVersion()

    {
        loadFromFile();
        ifstream ifs("file.txt");
        string content((istreambuf_iterator<char>(ifs)),
                       (istreambuf_iterator<char>()));
        int hsh = hash<string>{}(content);
        // Loop through current list and add verison to list dynamically only if it is unique
        mylist->next->add(mylist, hsh, content);

        saveToFile();
    }

    void printVersions()
    {
        loadFromFile();
        LinkedList *temp = mylist->next;
        // Count the number of verions in the list
        int num_versions = temp->verisons(temp);
        cout << "Number of versions: " << num_versions << endl;
        temp = mylist->next;
        temp->print(temp);
    }

    void loadVersion(int version_num)
    {
        loadFromFile();
        LinkedList *temp = mylist->next;
        temp->load(temp, version_num);
    }

    void compareVersions(int version1, int version2)
    {
        loadFromFile();
        LinkedList *temp = mylist->next;
        temp->compare(temp, version1, version2);
    }

    void search(string keyword)
    {
        loadFromFile();
        LinkedList *temp = mylist->next;
        int count = temp->search(temp, keyword);
        if (count == 0)
            cout << "Your keyword '" << keyword << "' was not found in any version." << endl;
    }

     void removeVersion(int version)
    {
        loadFromFile();
        LinkedList *temp = mylist;
        temp->remove(temp, version);
        saveToFile();
    }

private:
    LinkedList *mylist = new LinkedList("", 0, 0);
};

int main()
{
    // Loop for users menu interation
    EnhancedGit322 myfile;
    while (true)
    {
        char in;
        cout << "Welcome to the Comp322 file versioning system!" << endl;
        cout << "To add the content of your file to version control press 'a'" << endl;
        cout << "To remove a version press 'r" << endl;
        cout << "To load a version press 'l'" << endl;
        cout << "To print to the screen the detailed list of all versions press 'p'" << endl;
        cout << "To compare any 2 versions press 'c'" << endl;
        cout << "To search versions for a keyword press 's'" << endl;
        cout << "To exit press 'e'" << endl;
        cin >> in;
        if (in == 'a')
        {
            myfile.addVersion();
        }
        else if (in == 'p')
        {
            myfile.printVersions();
        }
        else if (in == 'l')
        {
            int vers = 0;
            cout << "Which version would you like to load?" << endl;
            cin >> vers;
            myfile.loadVersion(vers);
        }
        else if (in == 'c')
        {
            int vers1;
            cout << "Please enter the number of the first version to compare:" << endl;
            cin >> vers1;
            int vers2;
            cout << "Please enter the number of the second version to compare:" << endl;
            cin >> vers2;
            myfile.compareVersions(vers1, vers2);
        }
        else if (in == 's')
        {
            string word;
            cout << "Please enter the keyword that you are looking for:" << endl;
            cin >> word;
            myfile.search(word);
        }
        else if (in == 'r')
        {
            int vers;
            cout << "Enter the number of the version that you want to delete:" << endl;
            cin >> vers;
            myfile.removeVersion(vers);
        }
        else if (in == 'e')
        {
            break;
        }
    }
}