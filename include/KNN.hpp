#ifndef FDE20_BONUSPROJECT_3_KNN_HPP
#define FDE20_BONUSPROJECT_3_KNN_HPP

#include "Matrix.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include<unordered_map>
#include <algorithm>
using namespace std;

using Entry = Matrix::Entry;



bool comp(pair<unsigned,double> a, pair<unsigned,double> b) {
    return a.second < b.second;
}

// vector<Matrix::Entry> getKNN(const Matrix &m, unsigned start, unsigned k) {
//   using Entry = Matrix::Entry;
//   vector<Entry> result;
//   result.reserve(k);
//   unordered_map<unsigned, double> distances;
//   vector<bool> visited;
//   queue<Entry> q;
//   double max = INTMAX_MAX;
//   visited.reserve(max);


//   for (auto e : m.entries)
//   {
//     distances[e.column] = max;
//   }
//   distances[start] = 0;
  
//   q.push({start, 0});
//   while (!q.empty())
//   {
//     auto curr = q.front();
//     q.pop();
//     visited[curr.column] = true;
//     for (auto n : m.getNeighbors(curr.column))
//     {
//       if(visited[n.column]) continue;
//       visited[n.column] = true;
//       if(distances[n.column] > distances[curr.column] + n.weight){
//         distances[n.column] = distances[curr.column] + n.weight;
//         q.push({n.column, distances[n.column]});
//       }
//     }
//   }

  

//   vector<pair<unsigned, double>> elems(distances.begin(), distances.end());
//   sort(elems.begin(), elems.end(), comp);

//   for (auto it = elems.begin() + 1; it <= elems.begin() + k; it++)
//   {
//     if(it->second != max){
//       result.push_back({it->first, it->second});
//     }
//   }
//   return result;
// }


vector<Matrix::Entry> getKNN(const Matrix &m, unsigned start, unsigned k) {
    using Entry = Matrix::Entry;
    vector<Entry> result;
    result.reserve(k);
    vector<double> distances(m.entries.size(), numeric_limits<double>::max());
    priority_queue<pair<double, unsigned>, vector<pair<double, unsigned>>, greater<>> q;
    vector<bool> visited(m.entries.size(),false);
    distances[start] = 0;
    q.push({0, start});
    while (!q.empty())
    {
        unsigned curr = q.top().second;
        q.pop();
        if (visited[curr]) continue;
        visited[curr] = true;
        for (auto n : m.getNeighbors(curr))
        {
            if (distances[n.column] > distances[curr] + n.weight)
            {
                distances[n.column] = distances[curr] + n.weight;
                q.push({distances[n.column], n.column});
            }
        }
    }
    for (unsigned i = 0; i < distances.size(); i++)
    {
        if(distances[i] != numeric_limits<double>::max() && distances[i] != 0){
          result.push_back({i, distances[i]});
        }
    }
    sort(result.begin(), result.end(), [](Entry a, Entry b){return a.weight < b.weight;});
    if(result.size()>k)
    {
        int extra = result.size() - k;
        for (int i = 0; i < extra; i++) {
          result.pop_back();
        }
    }
    return result;
}
#endif

