#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

#define N 100000

using namespace std;

struct Coordinate{
    double x, y;
};

bool compare_coor_x(Coordinate p1, Coordinate p2){
    return (p1.x < p2.x);
}

bool compare_coor_y(Coordinate p1, Coordinate p2){
    return (p1.y < p2.y);
}

double compute_dist(Coordinate p1, Coordinate p2){
    double value = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    return value;
}

double point_across_mid(Coordinate points[], int closest_size, double d){
    double min_dist = d;
    double cur_dist;
    
    for(int i = 0; i < closest_size; i++){
        for(int j = i+1; j < closest_size && j - i < 7; j++){
            cur_dist = compute_dist(points[i], points[j]);
            if(cur_dist < min_dist){
                min_dist = cur_dist;
            }
        }
    }

    return min_dist;
}

double divide_conquer(Coordinate points[], int n){
    if (n <= 3) {
        double min = 99999;
        double cur_dist;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                cur_dist = compute_dist(points[i], points[j]);
                if(cur_dist < min){
                    min = cur_dist;
                }
            }
        }
        return min;
    }
    else {
        double d = 99999;
        int mid_index = n/2;
        double left_d = divide_conquer(points, mid_index);
        double right_d = divide_conquer(points+mid_index, n-mid_index);

        if(left_d < right_d){
            d = left_d;
        }
        else{
            d = right_d;
        }

        Coordinate middle_point = points[mid_index];
        Coordinate points_in_d[n];
        int count = 0;
        for(int i = 0; i < n; i++){
            if(abs(points[i].x - middle_point.x) < d){
                //Collect the points that are close to middle point.
                points_in_d[count] = points[i];
                count++;
            }
        }

        sort(points_in_d, points_in_d+count, compare_coor_y);
        double shortest_dist = point_across_mid(points_in_d, count, d);
        
        return shortest_dist;
    }
}

int main(){
    int T, n;
    double coor;
    cin>>T;
    Coordinate points[N];
    for (int i = 0; i < T; i++){
        cin>>n;
        for(int j = 0; j < n; j++){
            cin>>coor;
            points[j].x = coor;
            cin>>coor;
            points[j].y = coor;
        }

        sort(points, points+n, compare_coor_x);

        cout << fixed << setprecision(6) << divide_conquer(points, n) << endl;
    }

    return 0;
}