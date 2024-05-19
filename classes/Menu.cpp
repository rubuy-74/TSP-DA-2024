#include "Menu.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "Parser.h"
#include "TSP.h"
#include "Triangular.h"
#include "Heuristic.h"

bool done = false;

void Menu::MainMenu(){
    while (!done) {
        std::cout << "\n\n ----------------------------------------------\n"
                     "|                 Main Menu                    |\n"
                     " ----------------------------------------------\n";
        std::cout << "Hello, travelling salesman!\n";
        std::cout << "Select the number of the topic...\n"
                     "[1]> Backtracking algorithm (4.1)\n"
                     "[2]> Triangular Approximation (4.2)\n"
                     "[3]> Other Heuristics (4.3)\n"
                     "[4]> TSP in Real World (4.4)\n"

                     "\n[0]> Quit\n";

        int topic_in_main_menu;
        std::string striTemp;

        topic_in_main_menu = 0;
        striTemp = "";
        std::cin >> striTemp;
        try {
            topic_in_main_menu = stoi(striTemp);
        }
        catch (...) {
            topic_in_main_menu = 100;
        }


        if (topic_in_main_menu == 1) {
            auto start = std::chrono::high_resolution_clock::now();
            TSPBacktracking(dataset, path, file);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "TSP Backtracking took " << duration.count() / 1000000.0 << " seconds.\n";
        } else if (topic_in_main_menu == 2 && this->file != "shipping.csv") {
            auto start = std::chrono::high_resolution_clock::now();
            TSPTriangular(this->dataset, this->path, this->file);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "TSP Triangular Approximation took " << duration.count() / 1000000.0 << " seconds.\n";
        } else if (topic_in_main_menu == 3 && this->file != "shipping.csv") {
            auto start = std::chrono::high_resolution_clock::now();
            TSPHeuristic(this->dataset, this->path, this->file, 0);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << "TSP Heuristic " << duration.count() / 1000000.0 << " seconds.\n";
        } else if (topic_in_main_menu == 4) {
            std::cout << "Select the index of the starting node:\n";
            int index;
            std::cin >> index;
            auto start = std::chrono::high_resolution_clock::now();
            if(!TSPHeuristic(this->dataset, this->path, this->file, index)) {
                backToMainMenu();
            }
            else {
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                std::cout << "TSP Heuristic took " << duration.count() / 1000000.0 << " seconds.\n";
            }
        }
        else if (topic_in_main_menu == 0) break;
        else if (topic_in_main_menu < 4) std::cout << "Error: Not valid choice\n";
        else std::cout << "Error: Choose one number of the Main Menu.\n";

        backToMainMenu();
    }

}

void Menu::DatasetMenu() {

    std::cout << "\n\n ----------------------------------------------\n"
                     "|                 Dataset Menu                 |\n"
                     " ----------------------------------------------\n";
    std::cout << "Hello, travelling salesman!\n";
    std::cout << "Select the number of the topic...\n"
                 "[1]> Shipping Toy-Graph\n"
                 "[2]> Stadiums Toy-Graph\n"
                 "[3]> Tourism Toy-Graph\n"
                 "[4]> Graph 1 Real-world Graph\n"
                 "[5]> Graph 2 Real-world Graph\n"
                 "[6]> Graph 3 Real-world Graph\n"
                 "[7]> Extra Fully Connected Graph\n"

                 "\n[0]> Quit\n";

    int topic_in_dataset_menu;
    std::string striTemp;

    while (true) {
        topic_in_dataset_menu = 0;
        striTemp = "";
        std::cin >> striTemp;
        try {
            topic_in_dataset_menu = stoi(striTemp);
        }
        catch (...) {
            topic_in_dataset_menu = 100;
        }


        if (topic_in_dataset_menu == 1) {
            this->file = "shipping.csv";
            this->path = "../toy-graphs/";
            break;
        } else if (topic_in_dataset_menu == 2) {
            this->file = "stadiums.csv";
            this->path = "../toy-graphs/";
            break;
        } else if (topic_in_dataset_menu == 3) {
            this->file = "tourism.csv";
            this->path = "../toy-graphs/";
            break;
        } else if (topic_in_dataset_menu == 4) {
            this->file = "edges.csv";
            this->path = "../real-world/graph1/";
            break;
        } else if (topic_in_dataset_menu == 5) {
            this->file = "edges.csv";
            this->path = "../real-world/graph2/";
            break;
        } else if (topic_in_dataset_menu == 6) {
            this->file = "edges.csv";
            this->path = "../real-world/graph3/";
            break;
        } else if (topic_in_dataset_menu == 7) {
            std::cout << "Select the fully connected graph you want to use (ex: edges_25.csv) ... " <<std::endl;
            std::string edgesFile;
            std::cin >> edgesFile;

            this->file = edgesFile;
            this->path = "../other_graphs/";
            break;
        }

        else if (topic_in_dataset_menu == 0) break;
        else std::cout << "Error: Choose one number of the Main Menu.\n";
    }
}


void TSPBacktracking(Dataset dataset,std::string filePath, std::string file) {
    Parser parser;

    auto e = parser.readFile(filePath + file,true);
    dataset.loadEdges(e);
    dataset.loadMatrix(e);

    std::vector<int> path(dataset.getGraph().getNodeSize(),0);
    double sumDist = TSP::tspBT(dataset.getAdjMatrix(),dataset.getGraph().getNodeSize(),path);
    path.push_back(0);
    printPath(path,sumDist);
}

void TSPTriangular(Dataset dataset, std::string filePath, std::string file) {
    Parser parser;
    std::vector<int> result;
    auto e = parser.readFile(filePath + file,true);
    dataset.loadEdges(e);
    Graph g = dataset.getGraph();

    if(filePath == "../real-world/graph1/" || filePath == "../real-world/graph2/" || filePath == "../real-world/graph3/"){
        g.makeGraphFullyConnected();
    }

    double sumDist = Triangular::tspTriangular(g,result);
    printPath(result,sumDist);
}

bool TSPHeuristic(Dataset dataset,std::string path, std::string file, int startingIndex) {
    Parser parser;

    auto e = parser.readFile(path + file,true);
    dataset.loadEdges(e);
    Graph g = dataset.getGraph();

    if(startingIndex > g.getNodeSize()) {
        std::cout << "Index too big.\n";
        return false;
    }
    auto start = std::chrono::high_resolution_clock::now();

    if(path == "../toy-graphs/" && file == "shipping.csv"){
        g.connectGraphThroughDjikstra();
    }

    if(path == "../real-world/graph1/" || path == "../real-world/graph2/" || path == "../real-world/graph3/"){
        g.connectGraphThroughDjikstra();
    }

    std::pair<double, std::vector<int>> tsp = Heuristic::heuristic(&g, startingIndex);
    printPath(tsp.second,tsp.first);
    return true;
}


void printPath(std::vector<int> path,double sumDist) {
    std::cout << "Distance: " << sumDist << '\n';
    std::cout << "Path:" << '\n';
    for(int i = 0; i < path.size(); i++) {
        std::cout << path[i] << ", ";
    }
    std::cout << '\n';
}


Menu::Menu() {
}


void Menu::backToMainMenu( ){
    std::cout << "\n[1]> Back to Main Menu.\n"
                 "[0]> Quit.\n";
    int back;
    std::string striBack;
    while (true) {
        back = 0;
        striBack = "";
        std::cin >> striBack;
        try {
            back = stoi(striBack);
        }
        catch (...) {
            back = 10;
        }
        if (back == 1) { return;}
        else if (back == 0) {done = true; break;};
        std::cout << "> Invalid choice.\n"
                     "[1]> Back to Main Menu.\n"
                     "[0]> Quit.\n";
    }

}


