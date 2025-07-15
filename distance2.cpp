#include <bits/stdc++.h>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
using namespace std;

class City
{
public:
    class adjPlaces
    {
    public:
        unordered_map<string, int> neighb;
    };

    unordered_map<string, adjPlaces> trstSpot;

    City()
    {
        trstSpot.clear();
    }

    void addVertex(string name)
    {
        adjPlaces plc;
        trstSpot[name] = plc;
    }

    bool contains_vertex(string name)
    {
        if (trstSpot.count(name) == 0)
        {
            return false;
        }
        return true;
    }

    void addEdge(string name1, string name2, int dist)
    {
        // if any of these two touristSpot is not there in our record OR if there's already an existing edge then simply return
        if (trstSpot.count(name1) == 0 || trstSpot.count(name2) == 0 || trstSpot[name1].neighb.count(name2) > 0)
            return;

        trstSpot[name1].neighb[name2] = dist;
        trstSpot[name2].neighb[name1] = dist;
    }

    bool contains_edge(string name1, string name2)
    {
        if (trstSpot.count(name1) == 0 || trstSpot.count(name2) == 0 || trstSpot[name1].neighb.count(name2) == 0)
        {
            return false;
        }
        return true;
    }

    void display_trstSpot()
    {
        cout << endl;
        cout << YELLOW << "Here's the list of all the places you can visit and enjoy in Shimla" << endl
             << endl
             << RESET;
        int i = 1;
        for (auto it : trstSpot)
        {
            cout << i << ". " << it.first << endl;
            i++;
        }
        cout << endl;
    }

    void nav_map()
    {
        cout << endl;
        int i = 1;
        for (auto it : trstSpot)
        {
            cout << i << ". " << it.first;
            cout << endl;
            for (auto ite : it.second.neighb)
            {
                cout << "\t * " << ite.first << " - " << ite.second << "km" << endl;
            }
            i++;
            cout << endl;
        }
        cout << endl;
    }

    void DFS(unordered_map<string, int> &numbering, vector<int> &vis, string src, string dest, vector<string> &path, set<vector<string>> &paths)
    {

        path.push_back(src);
        vis[numbering[src]] = 1; // Mark the current node as visited

        if (src == dest)
        { // If we reached the destination
            paths.insert(path);
        }
        else
        {
            for (auto it : trstSpot[src].neighb)
            {
                if (vis[numbering[it.first]] == 0)
                { // Only go to unvisited nodes
                    DFS(numbering, vis, it.first, dest, path, paths);
                }
            }
        }

        vis[numbering[src]] = 0; // Backtrack: unmark the node as visited
        path.pop_back();         // Remove the last node from the current path
    }

    void show_all_paths(string src, string dest)
    {

        if (trstSpot.find(src) == trstSpot.end() || trstSpot.find(dest) == trstSpot.end())
        {
            cout << RED << "Source or destination not found!" << RESET << endl;
            return;
        }

        // assigning index to trstSpot
        unordered_map<string, int> numbering;
        int i = 0;
        for (auto it : trstSpot)
        {
            numbering[it.first] = i;
            i++;
        }

        vector<int> vis(numbering.size(), 0);

        set<vector<string>> paths;
        vector<string> path;
        DFS(numbering, vis, src, dest, path, paths);

        if (paths.empty())
        {
            cout << RED << "No path exists from " << src << " to " << dest << RED << endl;
        }
        else
        {
            cout << "All paths from " << GREEN << src << RESET << " to " << RED << dest << RESET << ":" << endl
                 << endl;
            for (auto it : paths)
            {
                for (auto ite : it)
                {
                    cout << YELLOW<< " -> " <<RESET<< ite;
                }
                cout << endl
                     << endl;
            }
        }
    }

    // FINDING SHORTEST DISTANCE FROM SRC to DEST using Dijkstra Algorithm and greedy approach
    int shortest_distance(string src, string dest)
    {

        unordered_map<string, int> numbering;
        int i = 0;
        for (auto it : trstSpot)
        {
            numbering[it.first] = i;
            i++;
        }

        priority_queue<pair<int, pair<string, int>>, vector<pair<int, pair<string, int>>>, greater<pair<int, pair<string, int>>>> pq;
        pq.push({0, {src, numbering[src]}});

        vector<int> dist(numbering.size(), 1e9);
        dist[numbering[src]] = 0;

        while (!pq.empty())
        {
            auto it = pq.top();

            string plc_name = it.second.first;
            int plc_index = it.second.second;
            int dis = it.first;

            pq.pop();

            for (auto ite : trstSpot[plc_name].neighb)
            {

                string adj_placename = ite.first;
                int adj_placeindex = numbering[adj_placename];
                int edgewt = ite.second;

                if (dis + edgewt < dist[adj_placeindex])
                {
                    dist[adj_placeindex] = dis + edgewt;
                    pq.push({dist[adj_placeindex], {adj_placename, adj_placeindex}});
                }
            }
        }
        return dist[numbering[dest]];
    }

    // FINDING SHORTEST PATH FROM SRC to DEST using Dijkstra Algorithm and greedy approach
    void shortest_path(string src, string dest)
    {

        unordered_map<string, int> numbering;
        unordered_map<int, string> numbering_2;
        int i = 0;
        // bi-directional mapping
        for (auto it : trstSpot)
        {
            numbering[it.first] = i;
            numbering_2[i] = it.first;
            i++;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, numbering[src]});

        vector<int> dist(numbering.size(), 1e9);
        dist[numbering[src]] = 0;

        vector<int> parent(numbering.size());
        for (int i = 0; i < numbering.size(); i++)
        {
            parent[i] = i;
        }

        while (!pq.empty())
        {
            auto it = pq.top();

            int plc_index = it.second;
            int dis = it.first;

            pq.pop();

            for (auto ite : trstSpot[numbering_2[plc_index]].neighb)
            {

                string adj_placename = ite.first;
                int adj_placeindex = numbering[adj_placename];
                int edgewt = ite.second;

                if (dis + edgewt < dist[adj_placeindex])
                {
                    dist[adj_placeindex] = dis + edgewt;
                    parent[adj_placeindex] = plc_index;
                    pq.push({dist[adj_placeindex], adj_placeindex});
                }
            }
        }

        vector<int> path_index;
        int node = numbering[dest];

        if (dist[node] == 1e9)
        {
            cout << RED << "No path found from " << src << " to " << dest << "." << RESET << endl;
            return;
        }

        int parent_node = parent[node];

        while (node != parent_node)
        {
            path_index.push_back(node);
            node = parent_node;
            parent_node = parent[node];
        }
        path_index.push_back(numbering[src]);
        reverse(path_index.begin(), path_index.end());

        cout << "\nShortest path from " << GREEN << src << RESET << " to " << RED << dest << RESET << ":" << endl;
        for (auto it : path_index)
        {
            cout <<YELLOW<< "-> " <<RESET<< numbering_2[it] << " ";
        }
        cout << "\nTotal Distance: " << dist[numbering[dest]] << endl;
    }

    // available modes of transport:
    // 1.On foot: Rs0/km   2.bus: Rs2.19/km  3.car: Rs13/km
    void getFarePrice(string src, string dest, string mode)
    {
        double BUS_FARE_PER_KM = 2.19;
        double CAR_FARE_PER_KM = 13.0;
        double ON_FOOT_PER_KM = 13.0;

        int total_dist = shortest_distance(src, dest);

        if (total_dist == 1e9)
        {
            cout << RED << "path does not exist" << RESET;
            return;
        }

        double total_fare = 0.0;

        if (mode == "bus")
        {
            total_fare = total_dist * BUS_FARE_PER_KM;
            cout << "Total Distance: " << total_dist << " km" << endl;
            cout << "Fare per km (" << mode << "): Rs" << BUS_FARE_PER_KM << endl;
            cout << "Total Fare (" << mode << "): Rs" << total_fare << endl;
        }
        else if (mode == "car")
        {
            total_fare = total_dist * CAR_FARE_PER_KM;
            cout << "Total Distance: " << total_dist << " km" << endl;
            cout << "Fare per km (" << mode << "): Rs" << CAR_FARE_PER_KM << endl;
            cout << "Total Fare (" << mode << "): Rs" << total_fare << endl;
        }
        else if (mode == "foot")
        {
            total_fare = total_dist * 0.0;
            cout << "Total Distance: " << total_dist << " km" << endl;
            cout << "Fare per km (" << mode << "): Rs" << ON_FOOT_PER_KM << endl;
            cout << "Total Fare (" << mode << "): Rs" << total_fare << endl;
        }
        else
        {
            cout << RED << "Invalid mode of transport selected." << RESET << endl;
            return;
        }
    }

    void min_time(string src, string dest, string mode)
    {

        int total_dist = shortest_distance(src, dest);
        if (total_dist == 1e9)
        {
            cout << RED << "path does not exist" << RESET;
            return;
        }

        double speed;

        if (mode == "foot")
        {
            speed = 5; // km/h
        }
        else if (mode == "bus")
        {
            speed = 40; // km/h
        }
        else if (mode == "car")
        {
            speed = 60; // km/h
        }
        else
        {
            cout << RED << "Invalid mode of transport selected." << RESET << endl;
            return;
        }

        double time = total_dist / speed; // Time in hours
        int hours = (int)time;
        int minutes = (int)((time - hours) * 60);

        cout << "Minimum Time from " << GREEN << src << RESET << " to " << RED << dest << RESET << " by " << mode << ": ";
        cout << hours << " hours and " << minutes << " minutes." << endl;
    }

    // FILE HANDLING: User Reviews for Tourist Spots Allow users to rate and leave reviews for each tourist spot.
    void saveReviewToFile(string name, string review, int rating)
    {
        string filename = name + "_reviews.txt"; // Reviews saved in a separate file per spot
        ofstream file(filename, ios::app);       // opening file in append mode

        if (file.is_open())
        {
            file << review << " | " << rating << endl;
            file.close();
        }
        else
        {
            cout << RED << "Unable to open the file" << RESET << endl;
        }
    }

    void loadReviewsFromFile(string name)
    {
        vector<string> reviews;

        string filename = name + "_reviews.txt";
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << RED << "Unable to open the file" << RESET << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            reviews.push_back(line);
        }
        file.close();

        cout << "\nReviews for " << name << ":\n";
        for (auto it : reviews)
        {
            cout << it << endl;
        }
    }
    // Multi-Stop Route Planning:users can input multiple destinations (e.g., for a day tour) and find the best route covering all spots.
    vector<vector<int>> floydWarshall(unordered_map<string, int> &numbering)
    {
        vector<vector<int>> distMatrix;
        int n = numbering.size();
        distMatrix.assign(n, vector<int>(n, 1e9));

        // Initialize distances from edges
        for (auto &place : trstSpot)
        {
            int u = numbering[place.first];
            distMatrix[u][u] = 0; // Distance to itself is 0
            for (auto &neighbor : place.second.neighb)
            {
                int v = numbering[neighbor.first];
                distMatrix[u][v] = neighbor.second;
            }
        }

        // Floyd-Warshall algorithm
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (distMatrix[i][k] != 1e9 && distMatrix[k][j] != 1e9)
                    {
                        distMatrix[i][j] = min(distMatrix[i][j], distMatrix[i][k] + distMatrix[k][j]);
                    }
                }
            }
        }

        return distMatrix;
    }

    void multiStopRoute(vector<string> &destinations)
    {
        unordered_map<string, int> numbering;
        int idx = 0;
        for (auto &place : trstSpot)
        {
            numbering[place.first] = idx++;
        }

        // Get precomputed distance matrix
        vector<vector<int>> distMatrix = floydWarshall(numbering);

        vector<string> currentRoute, bestRoute;
        int minDistance = 1e9;

        // Backtracking to find the shortest multi-stop route
        function<void(string, unordered_set<string> &, int)> backtrack = [&](string current, unordered_set<string> &visited, int totalDistance)
        {
            if (visited.size() == destinations.size())
            {
                if (totalDistance < minDistance)
                {
                    minDistance = totalDistance;
                    bestRoute = currentRoute;
                }
                return;
            }

            for (auto &next : destinations)
            {
                if (visited.count(next) == 0)
                {
                    int currentIdx = numbering[current];
                    int nextIdx = numbering[next];

                    // Skip if no path exists
                    if (distMatrix[currentIdx][nextIdx] == 1e9)
                        continue;

                    visited.insert(next);
                    currentRoute.push_back(next);
                    backtrack(next, visited, totalDistance + distMatrix[currentIdx][nextIdx]);
                    visited.erase(next);
                    currentRoute.pop_back();
                }
            }
        };

        // Start backtracking from the first destination
        unordered_set<string> visited;
        currentRoute.push_back(destinations[0]);
        visited.insert(destinations[0]);
        backtrack(destinations[0], visited, 0);

        // Display the result
        if (bestRoute.empty())
        {
            cout <<RED<< "\nNo valid route exists to cover all destinations." <<RESET<< endl;
        }
        else
        {
            cout << YELLOW<<"\nBest Route covering all destinations:" << RESET<<endl;
            for (auto &place : bestRoute)
            {
                cout << "-> " << place << " ";
            }
            cout <<YELLOW<< "\nTotal Distance: " <<RESET<< minDistance << " km" << endl;
        }
    }

    void initializeDestinations()
    {
        addVertex("The Ridge");
        addVertex("Mall Road");
        addVertex("Jakhoo Temple");
        addVertex("Christ Church");
        addVertex("Lakkar Bazaar");
        addVertex("Kali Bari Temple");
        addVertex("Scandal Point");
        addVertex("Viceregal Lodge");
        addVertex("Annandale");
        addVertex("Indian Institute of Advanced Study");
        addVertex("Himachal State Museum");
        addVertex("Army Heritage Museum");
        addVertex("Summer Hill");
        addVertex("Chadwick Falls");
        addVertex("Kufri");
        addVertex("Naldehra");
        addVertex("Mashobra");

        // Adjusted connections for destinations
        addEdge("The Ridge", "Mall Road", 3);
        addEdge("The Ridge", "Christ Church", 2);
        addEdge("The Ridge", "Jakhoo Temple", 4);
        addEdge("Mall Road", "Lakkar Bazaar", 5);
        addEdge("Mall Road", "Scandal Point", 2);
        addEdge("Jakhoo Temple", "Christ Church", 1);
        addEdge("Christ Church", "Scandal Point", 2);
        addEdge("Christ Church", "Lakkar Bazaar", 5);
        addEdge("Kali Bari Temple", "Mall Road", 6);
        addEdge("Kali Bari Temple", "Lakkar Bazaar", 3);
        addEdge("Viceregal Lodge", "Annandale", 3);
        addEdge("Viceregal Lodge", "Indian Institute of Advanced Study", 5);
        addEdge("Viceregal Lodge", "Himachal State Museum", 4);
        addEdge("Annandale", "Army Heritage Museum", 2);
        addEdge("Army Heritage Museum", "Summer Hill", 5);
        addEdge("Summer Hill", "Indian Institute of Advanced Study", 3);
        addEdge("Summer Hill", "Chadwick Falls", 2);
        addEdge("Chadwick Falls", "Himachal State Museum", 1);
        addEdge("Kufri", "Mashobra", 5);
        addEdge("Kufri", "Naldehra", 6);
        addEdge("Mashobra", "Naldehra", 4);
        addEdge("Mall Road", "Viceregal Lodge", 6);
        addEdge("Summer Hill", "Mashobra", 7);
    }
};

// Personalized Recommendations: Based on users' preferences, provide personalized recommendations for tourist spots(e.g.,nature,adventure,history).
class Personalized
{
public:
    class catSpot
    {
    public:
        unordered_set<string> spots;
    };

    unordered_map<string, catSpot> categories;

    void addCategory(string cat)
    {
        catSpot plcs;
        categories[cat] = plcs;
    }

    void addLink(string cat, string name)
    {
        if (categories.count(cat) == 0 || categories[cat].spots.count(name) > 0)
            return;

        categories[cat].spots.insert(name);
    }

    void getRecommendations(vector<string> cats)
    {
        for (auto ite : cats)
        {

            if (categories.find(ite) != categories.end())
            {
                cout << "Places that best suits your preferred category (" << ite << "):" << endl;
                for (auto it : categories[ite].spots)
                {
                    cout << "-" << it << endl;
                }
                cout << endl;
            }

            else
            {
                cout << RED << "No recommendations available for category: " << ite << RESET << endl;
            }
        }
    }

    void addShimlaPlaces()
    {
        addCategory("Nature");
        addCategory("Adventure");
        addCategory("History");

        // Add places to each category
        addLink("Nature", "Kufri");
        addLink("Nature", "Naldehra");
        addLink("Nature", "Mashobra");
        addLink("Nature", "Summer Hill");
        addLink("Nature", "Chadwick Falls");
        addLink("Nature", "The Ridge");

        addLink("Adventure", "Kufri");
        addLink("Adventure", "Mall Road");
        addLink("Adventure", "Jakhoo Temple");
        addLink("Adventure", "Annandale");

        addLink("History", "Christ Church");
        addLink("History", "Kali Bari Temple");
        addLink("History", "Viceregal Lodge");
        addLink("History", "Army Heritage Museum");
    }
};

class EventCalendar
{
public:
    class Event
    {
    public:
        string name;
        string description;
        string location;
        string date; // date format: YYYY-MM-DD
    };

    // Store events in a map, where key is the date and value is a list of events
    unordered_map<string, vector<Event>> events; // use of vector to store multiple events for the same date

    // Function to add a new event
    void addEvent(string name, string description, string location, string date)
    {
        Event newEvent = {name, description, location, date};
        events[date].push_back(newEvent);
    }

    // Function to display events for a given date
    void displayEvents(string date)
    {
        if (events.count(date) > 0)
        {
            cout << "Events on " << date << ":\n";
            for (auto it : events[date])
            {
                cout << "Event: " << it.name << endl;
                cout << "Location: " << it.location << endl;
                cout << "Description: " << it.description << endl;
                cout << "----------------------\n";
            }
        }
        else
        {
            cout << RED << "No events on " << date << ".\n"
                 << RESET;
        }
    }

    void additionEvents()
    {
        addEvent("Shimla Summer Festival", "A festival showcasing local culture and crafts.", "Mall Road", "2024-05-15");
        addEvent("Kullu Dussehra", "A traditional festival celebrating the victory of good over evil.", "Kullu", "2024-10-01");
        addEvent("Shimla Arts Festival", "A celebration of arts with music, dance, and performances.", "The Ridge", "2024-06-20");
        addEvent("Himachal Pradesh Day", "Celebrating the foundation of Himachal Pradesh.", "Shimla", "2024-04-15");
    }
};

string normalizeName(const string &name)
{
    string result;
    for (char ch : name)
    {
        if (ch != ' ')
            result += tolower(ch);
    }
    return result;
}

int main()
{
    City Shimla;
    Shimla.initializeDestinations();

    cout << BOLD << CYAN << "\n\t\t\t\t\t\t\t\tWelcome to Shimla City Navigation System!" << RESET << endl;
    cout << BOLD << CYAN << "\t\t\t\t\t\tExplore beautiful Shimla and find your way around its scenic destinations" << RESET << endl;
    cout << BOLD << "\t\t\t\t\t\t--------------------------------------------------------------------------" << RESET << endl
         << endl;

    char choice = 'y';
    do
    {
        cout << "1. List Of All The Tourist Spots In Shimla" << endl;
        cout << "2. To Display The Navigation Map" << endl;
        cout << "3. Get All The Available Paths From Source To Destination" << endl;
        cout << "4. Get All The Required Details From Source Station To Destination Station" << endl;
        cout << "5. Add Review And Rating For A Tourist Spot" << endl;
        cout << "6. Display The Reviews And Ratings For Tourist Spots Given By Travellers" << endl;
        cout << "7. Multi-Stop Route Planning:Input multiple destinations for a day tour and find the best route covering all spots." << endl;
        cout << "8. Get Personalized Recommendations for tourist spots(Categories: Nature,Adventure,History)" << endl;
        cout << "9. Event Calendar: To Display a calendar of events happening in Shimla" << endl;
        cout << RED << "10. EXIT" << RESET << endl;

        cout << BLUE << "\nENTER YOUR CHOICE FROM THE ABOVE LIST: " << RESET;
        int ch = -1;
        cin >> ch;
        cout << endl;

        if (ch == 10)
        {
            break;
        }

        else if (ch == 1)
        {
            Shimla.display_trstSpot();
        }

        else if (ch == 2)
        {
            Shimla.nav_map();
        }

        else if (ch == 3)
        {
            Shimla.display_trstSpot();

            // Clear the newline character left in the buffer by previous input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string src, dest;
            cout << GREEN << "Enter Source: ";
            getline(cin, src);
            cout << RED << "Enter Destination: ";
            getline(cin, dest);
            cout << RESET << endl;

            string normalizedSrc = normalizeName(src);
            string normalizedDest = normalizeName(dest);

            bool srcExists = false, destExists = false;
            string actualSrc, actualDest;

            for (auto spot : Shimla.trstSpot)
            {
                if (normalizeName(spot.first) == normalizedSrc)
                {
                    srcExists = true;
                    actualSrc = spot.first;
                }
                if (normalizeName(spot.first) == normalizedDest)
                {
                    destExists = true;
                    actualDest = spot.first;
                }
            }

            if (!srcExists || !destExists)
            {
                cout << RED << "Invalid Source or Destination entered." << RESET << endl;
                return 0;
            }

            Shimla.show_all_paths(actualSrc, actualDest);
        }

        else if (ch == 4)
        {
            Shimla.display_trstSpot();

            // Clear the newline character left in the buffer by previous input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string src, dest;
            cout << GREEN << "Enter Source: ";
            getline(cin, src);
            cout << RED << "Enter Destination: ";
            getline(cin, dest);
            cout << RESET << endl;
            string normalizedSrc = normalizeName(src);
            string normalizedDest = normalizeName(dest);

            bool srcExists = false, destExists = false;
            string actualSrc, actualDest;

            for (auto spot : Shimla.trstSpot)
            {
                if (normalizeName(spot.first) == normalizedSrc)
                {
                    srcExists = true;
                    actualSrc = spot.first;
                }
                if (normalizeName(spot.first) == normalizedDest)
                {
                    destExists = true;
                    actualDest = spot.first;
                }
            }

            if (!srcExists || !destExists)
            {
                cout << RED << "Invalid Source or Destination entered." << RESET << endl;
                return 0;
            }

            int shrtstDist = Shimla.shortest_distance(actualSrc, actualDest);
            cout << "\n\nThe shortest distance from " << GREEN << src << RESET << " to " << RED << dest << ": " << RESET << shrtstDist << "km" << endl;

            Shimla.shortest_path(actualSrc, actualDest);

            string mode;
            cout << YELLOW << "\nEnter mode of transport (foot, bus, car): ";
            cin >> mode;
            cout << RESET << endl;
            Shimla.min_time(actualSrc, actualDest, mode);
            cout << endl;
            Shimla.getFarePrice(actualSrc, actualDest, mode);
        }

        else if (ch == 5)
        {
            Shimla.display_trstSpot();

            // Clear the newline character left in the buffer by previous input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string src;
            cout << YELLOW << "Enter name of the place: ";
            getline(cin, src);
            cout << RESET;
            string normalizedSrc = normalizeName(src);

            bool srcExists = false;
            string actualSrc;

            for (auto spot : Shimla.trstSpot)
            {
                if (normalizeName(spot.first) == normalizedSrc)
                {
                    srcExists = true;
                    actualSrc = spot.first;
                    break;
                }
            }

            if (!srcExists)
            {
                cout << RED << "Invalid Source or Destination entered." << RESET << endl;
                return 0;
            }

            cout << "Enter your review for " << actualSrc << ": ";
            string review;
            getline(cin, review);

            cout << "Enter your rating (1 to 5): ";
            int rating;
            cin >> rating;
            cin.ignore(); // Clear any newline character left in the input buffer

            Shimla.saveReviewToFile(actualSrc, review, rating);
        }

        else if (ch == 6)
        {
            Shimla.display_trstSpot();

            // Clear the newline character left in the buffer by previous input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string src;
            cout << YELLOW << "Enter name of the place: ";
            getline(cin, src);
            cout << RESET;
            string normalizedSrc = normalizeName(src);

            bool srcExists = false;
            string actualSrc;

            for (auto spot : Shimla.trstSpot)
            {
                if (normalizeName(spot.first) == normalizedSrc)
                {
                    srcExists = true;
                    actualSrc = spot.first;
                }
            }

            if (!srcExists)
            {
                cout << RED << "Invalid Source or Destination entered." << RESET << endl;
                return 0;
            }
            cout << endl;
            Shimla.loadReviewsFromFile(actualSrc);
        }
        else if (ch == 7)
        {
            Shimla.display_trstSpot();

            // Clear the newline character left in the buffer by previous input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string src, dest;
            cout <<GREEN<< "Enter Source: ";
            getline(cin, src);
            cout <<RED<< "Enter Destination: ";
            getline(cin, dest);
            cout<<RESET;
            string normalizedSrc = normalizeName(src);
            string normalizedDest = normalizeName(dest);

            bool srcExists = false, destExists = false;
            string actualSrc, actualDest;

            for (auto spot : Shimla.trstSpot)
            {
                if (normalizeName(spot.first) == normalizedSrc)
                {
                    srcExists = true;
                    actualSrc = spot.first;
                }
                if (normalizeName(spot.first) == normalizedDest)
                {
                    destExists = true;
                    actualDest = spot.first;
                }
            }

            if (!srcExists || !destExists)
            {
                cout <<RED<< "Invalid Source or Destination entered." << RESET<<endl;
            }

            cout <<YELLOW<< "Enter the number of places you want to visit in between: "<<RESET;
            int numStops;
            cin >> numStops;
            cin.ignore(); // Clear the input buffer

            vector<string> stops(numStops);
            for (int i = 0; i < numStops; i++)
            {
                cout << "Enter place " << i + 1 << ": ";
                getline(cin, stops[i]);
            }

            // Validate the stops
            vector<string> validStops;
            for (auto &stop : stops)
            {
                string normalizedStop = normalizeName(stop);
                bool stopExists = false;

                for (auto spot : Shimla.trstSpot)
                {
                    if (normalizeName(spot.first) == normalizedStop)
                    {
                        validStops.push_back(spot.first);
                        stopExists = true;
                        break;
                    }
                }

                if (!stopExists)
                {
                    cout << RED<<"Invalid stop entered: " << stop <<RESET<< endl;
                }
            }

            // Add source and destination to the list of stops
            validStops.insert(validStops.begin(), actualSrc); // Add source at the beginning
            validStops.push_back(actualDest);                 // Add destination at the end

            // Call multi-stop route planner
            Shimla.multiStopRoute(validStops);
        }

        else if (ch == 8)
        {
            Personalized for_you;
            for_you.addShimlaPlaces();

            int num;
            cout << YELLOW << "Enter number of preferences(Nature, History, Adventure) that you have: ";
            cin >> num;
            cout << RESET;
            cin.ignore();

            vector<string> cats(num);
            for (int i = 0; i < num; i++)
            {
                cout << "Enter your preference(Nature, History, Adventure) " << i + 1 << ": ";
                string cat;
                getline(cin, cat);
                cats[i] = cat;
            }

            cout << endl;
            for_you.getRecommendations(cats);
        }

        else if (ch == 9)
        {
            EventCalendar eve;
            eve.additionEvents();

            string date;
            cout << "Enter date(YYYY-MM-DD)";
            cin >> date;

            eve.displayEvents(date);
        }

        cout << BLUE << "\n\n\nDo you want to go to the main page or not?(y/n)\n"
             << RESET;
        cin >> choice;
        system("cls");

    } while (choice == 'y' || choice == 'Y');

    return 0;
}