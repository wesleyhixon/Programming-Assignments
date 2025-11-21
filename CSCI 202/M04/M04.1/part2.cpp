#include <iostream>
#include <map>
#include <string>
#include <algorithm>

std::map<std::string, std::string> stateCapitals = {
    {"alabama", "Montgomery"},
    {"alaska", "Juneau"},
    {"arizona", "Phoenix"},
    {"arkansas", "Little Rock"},
    {"california", "Sacramento"},
    {"colorado", "Denver"},
    {"connecticut", "Hartford"},
    {"delaware", "Dover"},
    {"florida", "Tallahassee"},
    {"georgia", "Atlanta"},
    {"hawaii", "Honolulu"},
    {"idaho", "Boise"},
    {"illinois", "Springfield"},
    {"indiana", "Indianapolis"},
    {"iowa", "Des Moines"},
    {"kansas", "Topeka"},
    {"kentucky", "Frankfort"},
    {"louisiana", "Baton Rouge"},
    {"maine", "Augusta"},
    {"maryland", "Annapolis"},
    {"massachusetts", "Boston"},
    {"michigan", "Lansing"},
    {"minnesota", "Saint Paul"},
    {"mississippi", "Jackson"},
    {"missouri", "Jefferson City"},
    {"montana", "Helena"},
    {"nebraska", "Lincoln"},
    {"nevada", "Carson City"},
    {"new hampshire", "Concord"},
    {"new jersey", "Trenton"},
    {"new mexico", "Santa Fe"},
    {"new york", "Albany"},
    {"north carolina", "Raleigh"},
    {"north dakota", "Bismarck"},
    {"ohio", "Columbus"},
    {"oklahoma", "Oklahoma City"},
    {"oregon", "Salem"},
    {"pennsylvania", "Harrisburg"},
    {"rhode island", "Providence"},
    {"south carolina", "Columbia"},
    {"south dakota", "Pierre"},
    {"tennessee", "Nashville"},
    {"texas", "Austin"},
    {"utah", "Salt Lake City"},
    {"vermont", "Montpelier"},
    {"virginia", "Richmond"},
    {"washington", "Olympia"},
    {"west virginia", "Charleston"},
    {"wisconsin", "Madison"},
    {"wyoming", "Cheyenne"},
    {"district of columbia", "Washington"}
};

std::map<std::string, std::string> properNames = {
    {"alabama", "Alabama"},
    {"alaska", "Alaska"},
    {"arizona", "Arizona"},
    {"arkansas", "Arkansas"},
    {"california", "California"},
    {"colorado", "Colorado"},
    {"connecticut", "Connecticut"},
    {"delaware", "Delaware"},
    {"florida", "Florida"},
    {"georgia", "Georgia"},
    {"hawaii", "Hawaii"},
    {"idaho", "Idaho"},
    {"illinois", "Illinois"},
    {"indiana", "Indiana"},
    {"iowa", "Iowa"},
    {"kansas", "Kansas"},
    {"kentucky", "Kentucky"},
    {"louisiana", "Louisiana"},
    {"maine", "Maine"},
    {"maryland", "Maryland"},
    {"massachusetts", "Massachusetts"},
    {"michigan", "Michigan"},
    {"minnesota", "Minnesota"},
    {"mississippi", "Mississippi"},
    {"missouri", "Missouri"},
    {"montana", "Montana"},
    {"nebraska", "Nebraska"},
    {"nevada", "Nevada"},
    {"new hampshire", "New Hampshire"},
    {"new jersey", "New Jersey"},
    {"new mexico", "New Mexico"},
    {"new york", "New York"},
    {"north carolina", "North Carolina"},
    {"north dakota", "North Dakota"},
    {"ohio", "Ohio"},
    {"oklahoma", "Oklahoma"},
    {"oregon", "Oregon"},
    {"pennsylvania", "Pennsylvania"},
    {"rhode island", "Rhode Island"},
    {"south carolina", "South Carolina"},
    {"south dakota", "South Dakota"},
    {"tennessee", "Tennessee"},
    {"texas", "Texas"},
    {"utah", "Utah"},
    {"vermont", "Vermont"},
    {"virginia", "Virginia"},
    {"washington", "Washington"},
    {"west virginia", "West Virginia"},
    {"wisconsin", "Wisconsin"},
    {"wyoming", "Wyoming"},
    {"district of columbia", "District of Columbia"}
};


int main(){
    bool running = true;

    while(running){
        std::cout << "Please enter a US State to see the name of its capital. Enter 0 to exit. " << std::endl;

        std::string input;
        std::getline(std::cin, input);

        if(input == "0"){
            running = false;
            break;
        }

        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if(stateCapitals.find(input) == stateCapitals.end()){
            std::cout << "State not found!" << std::endl;
            continue;
        }
        else{
            std::string capital = stateCapitals[input];
            std::cout << "This is the capital of " << properNames[input] << ": " << capital << std::endl;
        }
    }

    return 0;
}