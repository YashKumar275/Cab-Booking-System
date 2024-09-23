#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

const char *HOST = "127.0.0.1";
const char *USER = "root";
const char *PW = "pes2ug21cs930";
const char *DB = "Project";

class Cab
{
private:
    string cab_num, pickup, destination;
    int passenger_num;

public:
    Cab(string cnum, string pick, string des, int pass)
    {
        cab_num = cnum;
        pickup = pick;
        destination = des;
        passenger_num = pass;
    }

    string getCnum()
    {
        return cab_num;
    }

    string getPick()
    {
        return pickup;
    }

    string getDes()
    {
        return destination;
    }

    int getPassNum()
    {
        return passenger_num;
    }
};

void display(MYSQL *conn)
{
    string dis = "SELECT * FROM Cab";
    if (mysql_query(conn, dis.c_str()))
    {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else
    {
        MYSQL_RES *res;
        res = mysql_store_result(conn);
        if (res)
        {
            int num = mysql_num_fields(res);
            MYSQL_ROW row;
            while (row = mysql_fetch_row(res))
            {
                for (int i = 0; i < num; i++)
                {
                    cout << " " << row[i];
                }
                cout << endl;
            }
        }
    }
}

int main()
{
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0))
    {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Logged in Database!" << endl;
    }

    Sleep(3000);

    Cab c1("Cab001", "Electronic City", "JP Nagar", 2);
    Cab c2("Cab002", "Banashankari", "RR Nagar", 1);
    Cab c3("Cab003", "Jayanagar", "Sarjapur", 3);

    int intP1 = c1.getPassNum();
    int intP2 = c2.getPassNum();
    int intP3 = c3.getPassNum();

    stringstream ss1, ss2, ss3;
    ss1 << intP1;
    string strP1 = ss1.str();
    ss2 << intP2;
    string strP2 = ss2.str();
    ss3 << intP3;
    string strP3 = ss3.str();

    string insert1 = "INSERT INTO Cab (CNumber, Departure, Destination, PassengerNum) VALUES('" + c1.getCnum() + "', '" + c1.getPick() + "', '" + c1.getDes() + "', '" + strP1 + "')";
    string insert2 = "INSERT INTO Cab (CNumber, Departure, Destination, PassengerNum) VALUES('" + c2.getCnum() + "', '" + c2.getPick() + "', '" + c2.getDes() + "', '" + strP2 + "')";
    string insert3 = "INSERT INTO Cab (CNumber, Departure, Destination, PassengerNum) VALUES('" + c3.getCnum() + "', '" + c3.getPick() + "', '" + c3.getDes() + "', '" + strP3 + "')";

    if (mysql_query(conn, insert1.c_str()) || mysql_query(conn, insert2.c_str()) || mysql_query(conn, insert3.c_str()))
    {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else
    {
        cout << "Inserted Successfully!!" << endl;
    }
    Sleep(3000);

    bool exit = false;
    while (!exit)
    {
        system("cls");
        cout << endl;
        cout << "Welcome to Cab Booking System" << endl;
        cout << "1. Book a Cab " << endl;
        cout << "2. Exit " << endl;
        cout << "Enter Your Choice: ";
        int val;
        cin >> val;

        if (val == 1)
        {
            system("cls");
            display(conn);
            string cab;
            cout << endl;
            cout << "Enter Cab Number: ";
            cin >> cab;

            int total;

            string check = "SELECT PassengerNum FROM Cab WHERE CNumber= '" + cab + "'";
            if (mysql_query(conn, check.c_str()))
            {
                cout << "Error: " << mysql_error(conn) << endl;
            }
            else
            {
                MYSQL_RES *res;
                res = mysql_store_result(conn);
                if (res)
                {
                    MYSQL_ROW row = mysql_fetch_row(res);
                    if (row)
                    {

                        total = atoi(row[0]);
                    }
                }
            }

            if (total > 0)
            {
                total--;
                stringstream sst;
                sst << total;
                string strT = sst.str();

                string update = "UPDATE Cab SET PassengerNum = '" + strT + "' WHERE = '" + cab + "'";
                if (mysql_query(conn, update.c_str()))
                {
                    cout << "Error: " << mysql_error(conn) << endl;
                }
                else
                {
                    cout << "Cab is Booked in: " << cab << endl;
                }

                if (total == 0)
                {
                    cout << "Sorry! No seat in cab Available!" << endl;
                }
            }
            Sleep(8000);
        }
        else if (val == 2)
        {
            exit = true;
            cout << "Good Bye!!" << endl;
            Sleep(3000);
        }
        else
        {
            cout << "Invalid Input" << endl;
            Sleep(3000);
        }
    }
    return 0;
}