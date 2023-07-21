#include"Location.hh"

using namespace std;

Location::Location(string n, Coordination c, int t)
:coordination(c)
{
    name = n;
    traffic = t;
}

Location::Location(string line)
:coordination(DEFAULT_COR)
{
    vector<string> words;
    string word;
    for(int i=0 ; i<line.size() ; i++){
        if(line[i] != LOCATION_SEPERATOR){
            word.push_back(line[i]);
        }
        else{
            words.push_back(word);
            word.clear();
        }
    }
    words.push_back(word);
    name = words[0];
    coordination = Coordination(stod(words[1]), stod(words[2]));
    traffic = stoi(words[3]);
}

bool Location::is_equal(string n){
    if(name == n)
        return true;
    else
        return false;
}

double Location::calculate_price_to(Location* loc){
    double distance = coordination.calculate_distance_to(loc->coordination);
    double price;
    price = distance * (traffic + loc->traffic) * PRIMAL_PRICE;
    return price;
}