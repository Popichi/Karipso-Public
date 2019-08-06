/* Input example: L = [("abc", 10), ("def", 15), ("ghi", 10), ("abc", 12), ("xyz", 100)]
   The function should return ["xyz", "abc", ..., "def", "ghi"] */

/* TO DO: 1) Modify it to return only the top 10 movies!
          2) Learn the optimal way of solving this challenge! */

// Question was taken from: https://www.careercup.com/question?id=5713593060818944

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <unordered_map>

std::vector<std::string> ttwrates(const std::vector<std::pair<std::string, int> >& movies) {
    std::unordered_map<std::string, int> unsor_movies;
    std::map<int, std::string> sor_movies;
    std::vector<std::string> ttw_movies;
    for (std::vector<std::pair<std::string, int> >::const_iterator it = movies.begin(); it != movies.end(); ++it) {
        unsor_movies[it->first] += it->second;
    }

    for (std::unordered_map<std::string, int>::iterator it = unsor_movies.begin(); it != unsor_movies.end(); ++it) {
        std::cout << "Movie: " << it->first << ", Watch rate: " << it->second << std::endl;
        sor_movies[it->second] = it->first;
    }

    std::cout << std::endl;

    // If there are more than 10 movies and we only want to return the top 10 elements, then we should only save the first 10 movies
    // in the map!
    for (std::map<int, std::string>::reverse_iterator it = sor_movies.rbegin(); it != sor_movies.rend(); ++it) {
        std::cout << "Movie: " << it->second << ", Watch rate: " << it->first << std::endl;
        ttw_movies.push_back(it->second);
    }

    return ttw_movies;
}

int main () {
    std::vector<std::pair<std::string, int> > movies = {{"abc", 10}, {"def", 15}, {"ghi", 10}, {"abc", 12}, {"xyz", 100}};
    std::vector<std::string> ttw_movies = ttwrates(movies);

    std::cout << std::endl << "Videos with the top 10 watch rates are:" << std::endl;
    for (std::vector<std::string>::iterator it = ttw_movies.begin(); it != ttw_movies.end(); ++it) {
        std::cout << "Movie: " << *it << std::endl;
    }

    return 0;
}