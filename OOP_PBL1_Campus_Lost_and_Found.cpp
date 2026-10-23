#include <iostream>
#include <vector>
#include <string>
using namespace std;

class LostItem
{
protected:
    int id;
    string itemName;
    string location;
    string date;
    string status;

public:
    LostItem(int i,string n,string l,string d)
    {
        id=i;
        itemName=n;
        location=l;
        date=d;
        status="Reported";
    }

    int getId()
    {
        return id;
    }

    string getStatus()
    {
        return status;
    }

    void markResolved()
    {
        status="Resolved";
    }

    virtual void display()=0;
    virtual ~LostItem() {}
};

class LostReport:public LostItem
{
public:
    LostReport(int i,string n,string l,string d):LostItem(i,n,l,d) {}

    void display()
    {
        cout<<"ID: "<<id<<endl;
        cout<<"Type: Lost item"<<endl;
        cout<<"Item: "<<itemName<<endl;
        cout<<"Last seen at: "<<location<<endl;
        cout<<"Date: "<<date<<endl;
        cout<<"Status: "<<status<<endl;
    }
};

class FoundReport:public LostItem
{
public:
    FoundReport(int i,string n,string l,string d):LostItem(i,n,l,d) {}

    void display()
    {
        cout<<"ID: "<<id<<endl;
        cout<<"Type: Found item"<<endl;
        cout<<"Item: "<<itemName<<endl;
        cout<<"Found at: "<<location<<endl;
        cout<<"Date: "<<date<<endl;
        cout<<"Status: "<<status<<endl;
    }
};

class CampusHelpDesk
{
    vector<LostItem*> reports;
    int nextId;

public:
    CampusHelpDesk()
    {
        nextId=1;
    }

    void addLostReport()
    {
        string name,location,date;
        cout<<"Enter item name (one word): ";
        cin>>name;
        cout<<"Enter last-seen location (one word): ";
        cin>>location;
        cout<<"Enter date (DD/MM/YYYY): ";
        cin>>date;
        reports.push_back(new LostReport(nextId,name,location,date));
        cout<<"Lost report added. Report ID: "<<nextId<<endl;
        nextId++;
    }

    void addFoundReport()
    {
        string name,location,date;
        cout<<"Enter item name (one word): ";
        cin>>name;
        cout<<"Enter found location (one word): ";
        cin>>location;
        cout<<"Enter date (DD/MM/YYYY): ";
        cin>>date;
        reports.push_back(new FoundReport(nextId,name,location,date));
        cout<<"Found report added. Report ID: "<<nextId<<endl;
        nextId++;
    }

    void showReports()
    {
        if(reports.empty())
        {
            cout<<"No reports available"<<endl;
            return;
        }

        for(int i=0;i<reports.size();i++)
        {
            cout<<"\n--------------------"<<endl;
            reports[i]->display();
        }
    }

    void searchReport()
    {
        int searchId;
        cout<<"Enter report ID: ";
        cin>>searchId;

        for(int i=0;i<reports.size();i++)
        {
            if(reports[i]->getId()==searchId)
            {
                reports[i]->display();
                return;
            }
        }
        cout<<"Report not found"<<endl;
    }

    void resolveReport()
    {
        int searchId;
        cout<<"Enter report ID to mark as resolved: ";
        cin>>searchId;

        for(int i=0;i<reports.size();i++)
        {
            if(reports[i]->getId()==searchId)
            {
                reports[i]->markResolved();
                cout<<"Report marked as resolved"<<endl;
                return;
            }
        }
        cout<<"Report not found"<<endl;
    }

    ~CampusHelpDesk()
    {
        for(int i=0;i<reports.size();i++)
            delete reports[i];
    }
};

int main()
{
    CampusHelpDesk helpDesk;
    int choice;

    do
    {
        cout<<"\nCampus Lost-and-Found System\n";
        cout<<"1. Report lost item\n";
        cout<<"2. Report found item\n";
        cout<<"3. View all reports\n";
        cout<<"4. Search report by ID\n";
        cout<<"5. Mark report as resolved\n";
        cout<<"6. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
                helpDesk.addLostReport();
                break;
            case 2:
                helpDesk.addFoundReport();
                break;
            case 3:
                helpDesk.showReports();
                break;
            case 4:
                helpDesk.searchReport();
                break;
            case 5:
                helpDesk.resolveReport();
                break;
            case 6:
                cout<<"Exiting system"<<endl;
                break;
            default:
                cout<<"Invalid choice"<<endl;
        }
    }while(choice!=6);

    return 0;
}
