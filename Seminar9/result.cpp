#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <iomanip>

using namespace std;

/* Expected output:

Highscore      | Fastest       
Team D  : 37   | Team C
Team C  : 12   | Team B
Team B  : 5    | Team A

*/

string team_to_string(pair<string, int> const& team)
{
    ostringstream oss{};
    oss << left << setw(8) << team.first
        << ": " << setw(4) << team.second;
    return oss.str();
}



int main()
{
    vector<pair<string, int>> const results {
        {"Team C", 12},
        {"Team B", 5},
        {"Team A", 0},
        {"Team D", 37},
    };
    vector<pair<string, int>> highscore(3);

    // Create unnecessary mutable new vector based on result.
    auto res{results};

    // Sort it based on the second value in pair.
    sort(res.begin(), res.end(), [&](const pair<string, int> &a, const pair<string, int> &b){
        return a.second > b.second;
    });

    // Add in this case the three topmost results in res to highscore.
    transform(res.begin(), res.begin() + highscore.size(), begin(highscore), [&](pair<string, int> const& team) {
        return team;
    });

    // Create unnecessary mutable new vector to store the fastest teams
    // vector<string> fastest_teams(3);
    // transform(results.begin(), results.begin() + fastest_teams.size(), begin(fastest_teams), [&](pair<string, int> const& team) {
    //     return team.first;
    // });

    for (unsigned i{}; i < highscore.size(); i++) {
         cout << team_to_string(highscore[i]) << " | " << results[i].first << endl;
    }


    
}