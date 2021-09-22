#include<iostream>
#include<random>
#include<vector>

const int DataSize = 20000;

int RandomInteger(int min = 1, int max = 1000)
{
    //Source: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(min, max);

    return distrib(gen);
}
double EulcideanDistance(std::vector<int> A, std::vector<int> B)
{
    int var = 0;
    for (int i = 0; i < A.size(); i++)
    {
        var += ((A[i] - B[i]) * (A[i] - B[i]));
    }
    return sqrt(var);
}
double SinglePrecision(double num)
{
    double decimal = (num * 10) - (int(num) * 10);
    double ddecimal = int(decimal);
    //std::cout << num << " --- " << int(num) << " --- " << ddecimal << "\n";
    num = int(num) + (ddecimal / 10);
    return num;
}

template<int dimensions>
class Point
{
public:
    std::vector<int> point;
    Point()
    {
        for (int i = 0; i < dimensions; i++)
            point.push_back(RandomInteger());
    }
};

template<int dimensions, int samples>
class Coordinates
{
public:
    std::vector<std::vector<int>> CPoints;
    std::vector<double> distances;
    std::vector<double> NormalizedDistances;
    double min, max;

    Coordinates()
    {
        min = max = 0;
        for (int i = 0; i < samples; i++)
        {
            Point<dimensions> P;
            CPoints.push_back(P.point);
        }
    }
    void CheckDistances()
    {
        //Checking with the first added point
        double distance = EulcideanDistance(CPoints[0], CPoints[1]);
        min = distance, max = distance;
        distances.push_back(distance);
        for (int i = 2; i < samples; i++)
        {
            distance = EulcideanDistance(CPoints[0], CPoints[i]);
            distances.push_back(distance);
            if (distance > max)
                max = distance;
            if (distance < min)
                min = distance;
        }
    }
    void ScaleMetric()
    {
        double div = max - min;
        //Sort min-max and other distances in proportion 0 to 1
        for (int i = 0; i < distances.size(); i++)
        {
            NormalizedDistances.push_back((distances[i] - min) / (div));
            NormalizedDistances[i] = SinglePrecision(NormalizedDistances[i]);
        }
    }
    void GroupSimilar()
    {
        std::pair<double, int> range_coincidence;
        std::vector<std::pair<double, int>> pairs;
        for (double i = 0; i < 1; i += 0.1)
        {
            range_coincidence.first = i;
            range_coincidence.second = 0;
            pairs.push_back(range_coincidence);
        }
        for (int i = 0; i < NormalizedDistances.size(); i++)
        {
            if (NormalizedDistances[i]==0)
               pairs[0].second = pairs[0].second + 1;
            else if (NormalizedDistances[i] == 0.1)
                pairs[1].second = pairs[1].second + 1;
            else if (NormalizedDistances[i] == 0.2)
                pairs[2].second = pairs[2].second + 1;
            else if (NormalizedDistances[i] == 0.3)
                pairs[3].second = pairs[3].second + 1;
            else if (NormalizedDistances[i] == 0.4)
                pairs[4].second = pairs[4].second + 1;
            else if (NormalizedDistances[i] == 0.5)
                pairs[5].second = pairs[5].second + 1;
            else if (NormalizedDistances[i] == 0.6)
                pairs[6].second = pairs[6].second + 1;
            else if (NormalizedDistances[i] == 0.7)
                pairs[7].second = pairs[7].second + 1;
            else if (NormalizedDistances[i] == 0.8)
                pairs[8].second = pairs[8].second + 1;
            else if (NormalizedDistances[i] == 0.9)
                pairs[9].second = pairs[9].second + 1;
            else if (NormalizedDistances[i] == 1)
                pairs[10].second = pairs[10].second + 1;
        }
        /*
        std::cout << "Groups:\n";
        for (int i = 0; i < pairs.size(); i++)
        {
            std::cout << pairs[i].first << "--" << pairs[i].second << "\n";
        }
        */
    }
};

int main()
{
    Coordinates<3, 20> Test;
    Test.CheckDistances();
    Test.ScaleMetric();
    Test.GroupSimilar();
}
