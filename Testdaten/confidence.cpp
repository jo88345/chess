#include <iostream>
#include <cmath>

double Elo(double score){
    return 400 * log10(score/(1-score));
}

int main(){


    int wins = 298;
    int losses =291;
    int draws = 411;

    int games = wins + draws + losses;

    double score = (wins + 0.5*draws)/games;

    std::cout << games << '\n';

    std::cout << score << '\n';

    double elo = 400 * log10(score/(1-score));

    double sigma = sqrt((wins*(1-score)*(1-score) + draws*(0.5-score)*(0.5-score) + losses*(score)*(score))/games);

    std::cout << sigma*sigma << '\n';

    double std_deviation = sigma/sqrt(games);

    std::cout << std_deviation << '\n';

    double lower = Elo(score-1.645*std_deviation);

    double upper = Elo(score + 1.645 * std_deviation);


    std::cout << elo << '\n';



    std::cout << elo - upper << '\n';
    std::cout << elo - lower << '\n';
    
    std::cout << ((elo - upper)-(elo - lower))/2 << '\n';
    return 0;
}