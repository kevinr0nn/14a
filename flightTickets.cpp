/**
 * @file flightTickets.cpp
 * @author your name (tobias.hoglin@gmail.com)
 * @brief Ticket program, prints tickets from bookings and flight csv files
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// doxygen i terminalen
#include<iostream>
#include<cstdlib>
#include<iterator>
#include<list>
#include<fstream>
#include<fstream>
#include<sstream>
#include<cstring>
using namespace std;

/***/
class Flights
{
private:
int flightno;
string dep;
string des;
string datestr;
string timestr;
int nfs;
int fs;
int nbs;
int bs;
int nes;
int es;

    public:
    
    Flights(){this->fs = 0; this->bs = 0; this->es = 0;}
    
    // setters
    void set_flightno(int flightno){
        this->flightno = flightno;
    }
    void set_dep(string dep){
        this->dep = dep;
    }
    void set_des(string des){
        this->des = des;
    }
    void set_datestr(string datestr){
        this->datestr = datestr;
    }
    void set_timestr(string timestr){
        this->timestr = timestr;
    }
    void set_nfs(int nfs){
        this->nfs = nfs*7;
    }
    void set_nbs(int nbs){
        this->nbs = nbs*7;
    }
    void set_nes(int nes){
        this->nes = nes*7;
    }
    void increaseFs()
    {
        this->fs = fs+1;
    }
    void increaseBs()
    {
        this->bs = bs+1;
    }
    void increaseEs()
    {
        this->es = es+1;
    }
    /**
     * @brief Getters the flightno object data
     *  
     */
    int get_flightno(){
        return flightno;
    }
    string get_dep(){
        return dep;
    }
    string get_des(){
        return des;
    }
    string get_datestr(){
        return datestr;
    }
    string get_timestr(){
        return timestr;
    }
    int get_nfs(){
        return nfs; 
    }
    int get_fs(){
        return fs;
    }
    int get_nbs(){
        return nbs;
    }
    int get_bs(){
        return bs;
    } 
    int get_nes(){
        return nes;
    }
    int get_es(){
        return es;
    }
    
};
/**
 * @brief Bookings class. Containing booking information.
 * 
 */

class Bookings
{
private:
    int bookingno;
    string datestr;
    string timestr;
    string dep;
    string des;
    string sclass;
    string fname;
    string lname;

public:
    Bookings(){}
    /**
     * @brief Setters to the bookings objects attributes.
     */
    void set_bookingno(int bookingno){
        this->bookingno = bookingno;
    }
    void set_datestr(string datestr){
        this->datestr = datestr;
    }
    void set_timestr(string timestr){
        this->timestr = timestr;
    }
    void set_dep(string dep){
        this->dep = dep;
    }
    void set_des(string des){
        this->des = des;
    }
    void set_sclasss(string sclass){
        this->sclass = sclass;
    }
    void set_fname(string fname){
        this->fname = fname;
    }
    void set_lname(string lname){
        this->lname = lname;
    }
    // getters
    int get_bookingsno(){
        return bookingno;
    }
    string get_datestr(){
        return datestr;
    }
    string get_timestr(){
        return timestr;
    }
    string get_dep(){
        return dep;
    }
    string get_des(){
        return des;
    }
    string get_sclass(){
        return sclass;
    }
    string get_fname(){
        return fname;
    }
    string get_lname(){
        return lname;
    }
};

class flightManager
{
    list<Flights *> myFlights; // create a sample list of pointers to myClass objects
    
    public:
    void readFlights(string filename)
    {
       ifstream infile(filename);
       string line;
       if(infile.is_open())
       {
            while(getline(infile,line))
            {
                stringstream sstr(line);
                Flights *f = new Flights;
                string temp;

                getline(sstr,temp,',');
                f->set_flightno(atoi(temp.c_str()));

                getline(sstr,temp,',');
                f->set_dep(temp);
                getline(sstr,temp,',');
                f->set_des(temp);
                getline(sstr,temp,',');
                f->set_datestr(temp);
                getline(sstr,temp,',');
                f->set_timestr(temp);
                getline(sstr,temp,',');
                f->set_nfs(atoi(temp.c_str()));
                getline(sstr,temp,',');
                f->set_nbs(atoi(temp.c_str()));
                getline(sstr,temp,',');
                f->set_nes(atoi(temp.c_str()));
                
                myFlights.push_back(f);
            } 
        infile.close();              
       } 
    }

    list<Flights *> get_flighList()
    {
        return myFlights;
    }
};

class bookingManager
{
    list<Bookings *> myBookings; // create a sample list of pointers to myBookings objects
    
    public:
    bookingManager(){}
    void readBookings(string filename)
    {
       ifstream infile(filename);
       string line;
       if(infile.is_open())
       {
            while(getline(infile,line))
            {
                stringstream sstr(line);
                Bookings *b = new Bookings;
                string temp;
                getline(sstr,temp,',');
                b->set_bookingno(atoi(temp.c_str()));
                getline(sstr,temp,',');
                b->set_datestr(temp);
                getline(sstr,temp,',');
                b->set_timestr(temp);
                getline(sstr,temp,',');
                b->set_dep(temp);
                getline(sstr,temp,',');
                b->set_des(temp);
                getline(sstr,temp,',');
                b->set_sclasss(temp);
                getline(sstr,temp,',');
                b->set_fname(temp);
                getline(sstr,temp,',');
                b->set_lname(temp);
                
                myBookings.push_back(b);
            } 
            infile.close();              
       }
    } 
    list<Bookings *> get_bookingsList(){
        return myBookings;
    }
};

class ticketManager
{
    public:
    void seatMap(list<Flights *> myFlights)
    {

        list<Flights *>::iterator fit;
        char filename[100];
        for(fit = myFlights.begin(); fit != myFlights.end(); ++fit)
        {
		    sprintf(filename, "Flightmap-%d, %s", (*fit)->get_flightno(), (*fit)->get_timestr().c_str());
		    ofstream outfile(filename);
            if(outfile.is_open())
            {
                int nfs = (*fit)->get_nfs();
                int fs = (*fit)->get_fs();
                nfs /= 7;
                outfile << "First class" << endl;
			    for(int i = 0; i < nfs; i++)
			    {
                        if((i+1)%7==3 || (i+1)%7==6){outfile << " ";}
                        if(i<=fs) outfile << "[1]";
                        else outfile << "[0]"; 
                        if((i+1)%7==0){outfile << "\n";}
                }  
                
                int nbs = (*fit)->get_nbs();
                int bs = (*fit)->get_bs();
                nbs /= 7;
                outfile << "\nBusiness class" << endl;
                for(int i = 0; i < nbs; i++)
			    {
                        if((i+1)%7==3 || (i+1)%7==6){outfile << " ";}
                        if(i<=bs) outfile << "[1]";
                        else outfile << "[0]"; 
                        if((i+1)%7==0){outfile << "\n";}
                }
                int nes = (*fit)->get_nes();
                int es = (*fit)->get_es();
                nes /= 7;
                outfile << "\nEconomy class" << endl;
                for(int i = 0; i < nes; i++)
			    {
                        if((i+1)%7==3 || (i+1)%7==6){outfile << " ";}
                        if(i<=es) outfile << "[1]";
                        else outfile << "[0]"; 
                        if((i+1)%7==0){outfile << "\n";}
                }    
            }
        }
    }


    ticketManager(){}
    void canceledflights(list<Flights *> myFlights)
    {
        list<Flights *>::iterator fit;
        for(fit = myFlights.begin() ; fit != myFlights.end() ; ++fit)
        if((*fit)->get_fs() == 0 && (*fit)->get_bs() == 0 && (*fit)->get_es() == 0)
        {
            ofstream outfile("canceled-flights.txt", std::ios_base::app);
            if(outfile.is_open())
            {
                outfile << "Flight nr " << (*fit)->get_flightno() << " " << (*fit)->get_timestr() << " is canceled" << endl;
            }
        }
    }


    void matchseat(list<Flights *> myFlights, list<Bookings *> myBookings)
    {
        
        list<Bookings *>::iterator bit;
        list<Flights *>::iterator fit;
        
        for(bit = myBookings.begin() ; bit != myBookings.end(); ++bit)
        { 
            for(fit = myFlights.begin() ; fit != myFlights.end() ; ++fit)
            {
                if((*bit)->get_dep() == (*fit)->get_dep() && (*bit)->get_des() == (*fit)->get_des() && (*bit)->get_datestr() == (*fit)->get_datestr() && (*bit)->get_timestr() == (*fit)->get_timestr() )
                {   
                    int seat;
                    int row;
                    if((*bit)->get_sclass() == "first")
                    {
                        (*fit)->increaseFs();
                        row = (*fit)->get_fs()/7+1;
                        seat = (*fit)->get_fs();
                    }


                    if((*bit)->get_sclass() == "business")
                    {
                        (*fit)->increaseBs();
                        seat = (*fit)->get_bs()+(*fit)->get_nfs();
                        row = seat/7+1;
                    }
                    if((*bit)->get_sclass() == "economy")
                    {
                        (*fit)->increaseEs();
                        seat = (*fit)->get_es()+(*fit)->get_nfs()+(*fit)->get_nbs();
                        row = seat/7+1;
                    }
                    char filename[20]; 
                    sprintf(filename, "ticket-%d.txt", (*bit)->get_bookingsno());
                    ofstream outfile(filename);
                    if(outfile.is_open())
                    {
                        outfile << "BOOKING:" << (*bit)->get_bookingsno() << endl;
                        outfile << "FLIGHT:" << (*fit)->get_flightno();
                        outfile << " DEPARTURE:" << (*fit)->get_dep();
                        outfile << " DESTINATION:" <<(*fit)->get_des();
                        outfile << " " << (*fit)->get_datestr() << " ";
                        outfile << (*fit)->get_timestr() << endl;
                        outfile << "PASSENGER " << (*bit)->get_fname() << " " << (*bit)->get_lname();
                        outfile << " CLASS: " << (*bit)->get_sclass() << endl;
                        outfile << "ROW: " << row << " SEAT " << seat << endl;

                    }
                }
            }
        }
    }
};





int main()
{   
    flightManager fm;
    fm.readFlights("flights.csv");
    bookingManager bm;
    bm.readBookings("bookings.csv");
    ticketManager tm;
    tm.matchseat(fm.get_flighList(), bm.get_bookingsList());
    tm.canceledflights(fm.get_flighList());
    tm.seatMap(fm.get_flighList());
    cout << "Tickets and seatmaps printed"<< endl;
    
    return 0;
}

