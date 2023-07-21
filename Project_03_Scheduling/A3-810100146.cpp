#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

const int ASCII_CODE_ZERO = 48;
const string OUTPUT_HANDLE_STRING = ": ";
const string NO_TRANSLATOR_FOUND = "Not Found";


struct Time{
    int hour=0;
    int minute=0;
};

struct Timespan{
    Time start;
    Time end;
};

struct Language{
    bool is_translator_chosen=false;
    string name;
    int translators_number=0;
};

struct Translator{
    string name;
    vector<Language> languages;
    Timespan available_time;
    vector<Timespan> time_reserved;
    int known_language=0;
};


struct Event{
    string name;
    Timespan time;
    vector<Language> languages;
    vector<Translator> chosen_translators;
};

int find_number(string line){
    int result=0;
    result = stoi(line);
    return result;
}

string find_word(string line, int current_index){
    string word;
    for(int index = current_index ; index < line.size() ; index++){
        if(line[index]==' '){
            break;
        }
        word.push_back(line[index]);
    }
    return word;
}

int skip_word(string line, int current_index){
    int index;
    for(index=current_index ; index<line.size() ; index++){
        if(line[index] == ' '){
            break;
        }
    }
    index++;
    return index;
}

string find_name(string line){
    string name;
    name = find_word(line , 0);
    return name;
}

Time string_int_conv(string line, int string_index){
    Time time;
    time.hour += (line[string_index] - ASCII_CODE_ZERO) * 10;
    time.hour += (line[string_index + 1] - ASCII_CODE_ZERO);
    time.minute += (line[string_index + 3] - ASCII_CODE_ZERO) * 10;
    time.minute += (line[string_index + 4] - ASCII_CODE_ZERO);
    return time;
}

Time find_start_time(string line){
    Time start_time;
    int string_index = 0;
    string_index = skip_word(line, string_index);
    start_time = string_int_conv(line , string_index);
    return start_time;
}

Time find_end_time(string line){
    Time end_time;
    int string_index = 0;
    string_index = skip_word(line, string_index);
    string_index = skip_word(line, string_index);
    end_time = string_int_conv(line , string_index);
    return end_time;
}

vector<Language> find_languages(string line){
    vector<Language> languages;
    int string_index = 0;
    string_index = skip_word(line, string_index);
    string_index = skip_word(line, string_index);
    string_index = skip_word(line, string_index);
    while(string_index < line.size()){
        Language language;
        language.name = find_word(line, string_index);
        languages.push_back(language);
        string_index = skip_word(line, string_index);
    }
    return languages;
}

Translator seperate_trns_info(string line){
    Translator translator;
    translator.name = find_name(line);
    translator.available_time.start = find_start_time(line);
    translator.available_time.end = find_end_time(line);
    translator.languages = find_languages(line);
    return translator;
}

vector<Translator> read_translators(fstream &file){
    string read_line;

    int translators_number;
    getline(file, read_line);
    translators_number = find_number(read_line);

    vector<Translator> translators_result;
    for(int i=0 ; i<translators_number ; i++) {
        getline(file, read_line);
        Translator translator;
        translator = seperate_trns_info(read_line);
        translators_result.push_back(translator);
    }
    return translators_result;
}

Event seperate_event_info(string line){
    Event event;
    event.name = find_name(line);
    event.time.start = find_start_time(line);
    event.time.end = find_end_time(line);
    event.languages = find_languages(line);
    return event;
}

vector<Event> read_events(fstream& file){
    string read_line;

    int events_number;
    getline(file, read_line);
    events_number = find_number(read_line);

    vector<Event> events_result;
    for(int i=0 ; i<events_number ; i++) {
        getline(file, read_line);
        Event event;
        event = seperate_event_info(read_line);
        events_result.push_back(event);
    }
    return events_result;
}

void read_from_file(string file_path, vector<Translator>& translators, vector<Event>& events){
    fstream FILE;
    FILE.open(file_path);
    translators = read_translators(FILE);
    events = read_events(FILE);
}

vector<Event> make_space_for_chosen_translators(vector<Event> events){
    for(int i=0 ; i<events.size() ; i++){
        for(int j=0 ; j<events[i].languages.size() ; j++){
            Translator empty;
            events[i].chosen_translators.push_back(empty);
        }  
    }
    return events;
}

int calculate_number(vector<Translator> translators, Language language){
    int count=0;
    for(int i=0 ; i<translators.size() ; i++){
        for(int j=0 ; j<translators[i].languages.size() ; j++){
            if(language.name == translators[i].languages[j].name){
                count++;
            }
        }
    }
    return count;
}

vector<Event> find_language_trns_number(vector<Translator> translators, vector<Event> events){
    for(int i=0 ; i<events.size() ; i++){
        for (int j=0 ; j<events[i].languages.size() ; j++){
            events[i].languages[j].translators_number = calculate_number(translators, events[i].languages[j]);
        }
    }
    return events;
}

int figure_lng_priority(vector<Translator> translators, Event event){
    int min;
    int index;
    for(int i =0 ; i<event.languages.size() ; i++){
        if(event.languages[i].is_translator_chosen == false){
            min = event.languages[i].translators_number;
            index = i;
            break;
        }
    }
    for(int i=0 ;i<event.languages.size() ; i++){
        if(event.languages[i].translators_number < min && event.languages[i].is_translator_chosen == false){
            min=event.languages[i].translators_number;
            index = i;
        }
    }
    return index;
}

vector<Translator> add_who_knows_event_lng(vector<Translator> translators, Event event, int lng_index){
    vector<Translator> result;
    for(int i=0 ; i<translators.size() ; i++){
        for(int j=0 ; j<translators[i].languages.size() ; j++){
            if(translators[i].languages[j].name == event.languages[lng_index].name){
                result.push_back(translators[i]);
            }
        }
    }
    return result;
}

char compare_time(Time time_1, Time time_2){//time_1 'char' time_2
    if(time_1.hour > time_2.hour){
        return '>';
    }
    else if(time_1.hour == time_2.hour){
        if(time_1.minute > time_2.minute){
            return '>';
        }
        else if(time_1.minute < time_2.minute){
            return '<';
        }
        else{
            return '=';
        }
    }
    else{
        return '<';
    }
}

vector<Translator> remove_busy_translators(vector<Translator> translators, Event event, int lng_index){
    vector<Translator> result;
    for(int i=0 ; i<translators.size() ; i++){
        bool check_loop_j_status = true;
        if(compare_time(translators[i].available_time.start, event.time.start)=='>' || compare_time(event.time.end, translators[i].available_time.end)=='>'){
            continue;
        }
        for(int j=0 ; j<translators[i].time_reserved.size() ; j++){
            if(compare_time(translators[i].time_reserved[j].start, event.time.start)=='>' && compare_time(translators[i].time_reserved[j].start, event.time.end)=='<'){
                check_loop_j_status = false;
            }
            if(compare_time(translators[i].time_reserved[j].start, event.time.start)=='=' ||
            (compare_time(translators[i].time_reserved[j].start, event.time.start)=='<' && compare_time(translators[i].time_reserved[j].end, event.time.start)=='>')){
                check_loop_j_status = false;
            }
        }
        if(check_loop_j_status == true){
            result.push_back(translators[i]);
        }
    }
    return result;
}

vector<Translator> count_translators_lng(vector<Translator> translators){
    for(int i=0 ; i<translators.size() ; i++){
        translators[i].known_language = translators[i].languages.size();
    }
    return translators;
}

int find_min_trns_known_lng(vector<Translator> translators){
    int min;
    min = translators[0].known_language;
    for(int i=0 ; i<translators.size() ; i++){
        if(translators[i].known_language<min){
            min=translators[i].known_language;
        }
    }
    return min;
}

vector<Translator> list_min_trns_known_lng(vector<Translator> translators, int min_trns_known_lng){
    vector<Translator> result;
    for(int i=0 ; i<translators.size() ; i++){
        if(translators[i].known_language == min_trns_known_lng){
            result.push_back(translators[i]);
        }
    }
    return result;
}

Translator choose_least_ascii_code(vector<Translator> translators){
    Translator answer;
    vector<string> names;
    for(int i=0 ; i<translators.size() ; i++){
        names.push_back(translators[i].name);
    }
    sort(names.begin(), names.end());
    for(int i=0 ; i<translators.size() ; i++){
        if(translators[i].name == names[0]){
            answer=translators[i];
        }
    }
    return answer;
}

Translator figure_trns_priority(vector<Translator> translators){
    Translator result;
    if(translators.size() == 0){
        result.name = NO_TRANSLATOR_FOUND;
        return result;
    }
    int min_trns_known_lng;
    min_trns_known_lng = find_min_trns_known_lng(translators);
    vector<Translator> new_list;
    new_list = list_min_trns_known_lng(translators, min_trns_known_lng);
    result = choose_least_ascii_code(new_list);
    return result;
}

Event add_to_event(Event event ,Translator chosen, int lng_index){
    event.chosen_translators[lng_index] = chosen;
    return event;
}

vector<Translator> add_time_reserved(vector<Translator> translators, Event event, Translator chosen){
    for(int i=0 ; i<translators.size() ; i++){
        if(translators[i].name == chosen.name){
            translators[i].time_reserved.push_back(event.time);
        }
    }
    return translators;
}

vector<Translator> find_translators_for(vector<Translator> translators, Event& event, int lng_index){
    vector<Translator> available_translators;
    available_translators = add_who_knows_event_lng(translators, event, lng_index);
    
    available_translators = remove_busy_translators(available_translators, event, lng_index);
    
    available_translators = count_translators_lng(available_translators);

    Translator chosen;
    chosen = figure_trns_priority(available_translators);
    event = add_to_event(event, chosen, lng_index);

    vector<Translator> update_list;
    update_list = add_time_reserved(translators, event, chosen);
    return update_list;
}

vector<Event> put_translators_on_work(vector<Translator> translators, vector<Event> events){
    events = find_language_trns_number(translators, events);
    for(int i=0 ; i<events.size() ; i++){
        int event_language_numbers = events[i].languages.size();
        for(int j=0 ; j<event_language_numbers ; j++){
            int lng_index;
            lng_index = figure_lng_priority(translators, events[i]);
            translators = find_translators_for(translators, events[i], lng_index);
            events[i].languages[lng_index].is_translator_chosen = true;
        }
    }
    return events;
}

void output_handling(vector<Event> events){
    for(int i=0 ; i<events.size() ; i++){
        cout<<events[i].name<<endl;
        for(int j=0 ; j<events[i].languages.size() ; j++){
            cout<<events[i].languages[j].name<<OUTPUT_HANDLE_STRING<<events[i].chosen_translators[j].name<<endl;
        }
    }
}

int main(int argc, char* argv[]){
    vector<Translator> translators;
    vector<Event> events;
    read_from_file(argv[1] ,translators, events);
    events = make_space_for_chosen_translators(events);
    events = put_translators_on_work(translators, events);
    output_handling(events);
}