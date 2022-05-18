/*
            Name: Abdelrahman Osama Ahmed Mohamed
            ID: 1808518
            Section: 5
            Task 3 : Guarini's Puzzle
*/


#include <bits/stdc++.h>
using namespace std;
class Guarini_Puzzle{
    private:
        int steps;
        vector<char>board;
        vector<bool>empty;
        vector<vector<int>> possible_moves_from_this_position;
        map<int,int>tile_to_knight;
    public:
        Guarini_Puzzle(){
            steps=0;
            board=vector<char>{
                'B','B','B',
                'e','e','e',
                'e','e','e',
                'W','W','W',
            };
            empty=vector<bool>{
                false,false,false,
                true,true,true,
                true,true,true,
                false,false,false
            };
            possible_moves_from_this_position=vector<vector<int>>{
                {6,8},
                {7,9},
                {4,8},
                {3,9,11},
                {10,12},
                {1,7,11},
                {2,6,12},
                {1,3},
                {2,4,10},
                {5,9},
                {4,6},
                {5,7}
            };
            tile_to_knight.insert(pair<int,int>(3,11));
            tile_to_knight.insert(pair<int,int>(11,1));
            tile_to_knight.insert(pair<int,int>(1,12));
            tile_to_knight.insert(pair<int,int>(12,2));
            tile_to_knight.insert(pair<int,int>(2,10));
        }
        bool check_tile_empty(int i){
            return empty[i-1];
        }
        vector<int> get_possible_moves(int i){
            return possible_moves_from_this_position[i-1];
        }
        bool reached_special_case(){
            vector <char>special{
                'W','e','W',
                'e','e','e',
                'e','e','B',
                'W','B','B',
            };
            for (int i = 0 ; i < 12 ; i++){
                if (board[i]!=special[i]){
                    return false;
                }
            }
            return true;
        }
        void move(int start_position, int end_position){
            swap(board[start_position-1],board[end_position-1]);
            swap(empty[start_position-1],empty[end_position-1]);
            print_board();
        }
        void print_board(){
            cout << "Step " << steps++ << endl << endl;
            for (int i = 0 ; i < 12; i++){
                cout << board[i] << " | ";
                if((i+1)%3 == 0){
                    cout << "\n----------\n";
                } 
            }
            cout << endl <<  endl  << endl;
        }
        int empty_tile_to_fill(){
            for (int i = 0 ; i < 3; i++){
                if (board[i]=='e') return i+1;
            }
            for (int i = 9 ; i < 12; i++){
                if (board[i]=='e') return i+1;
            }
            return 0;
        }
        bool path_detector(int source, int destination, vector<int>&path,vector<bool>&visited){
            visited[source-1]=true;
            if (source==destination){
                path.push_back(source);
                return true;
            }
            vector<int> init = possible_moves_from_this_position[source-1];
            for (int i = 0 ; i < init.size(); i++){
                if (empty[init[i]-1] && !visited[init[i]-1]){
                    visited[init[i]-1]=true;
                    if (path_detector(init[i],destination,path,visited)){
                        path.push_back(source);
                    }
                }
            }
            return path.size();
        }
        void get_path_for_knight(int source,int destination){
            vector<bool>visited{
                false,false,false,
                false,false,false,
                false,false,false,
                false,false,false,
            };
            vector<int>path;
            path_detector(source,destination,path,visited);
            reverse(path.begin(),path.end());
            vector<int>path_1_corrupted={11,6,11,4,3};
            vector<int>path_2_corrupted={1,1,6,11};
            if(path==path_1_corrupted) path={11,4,3};
            if(path==path_2_corrupted) path={1,6,11};
            for (int i = 1 ; i<path.size(); i++){
                move(path[i-1],path[i]);
            }
        }
        void guarini(){
            int next_tile_to_fill = empty_tile_to_fill();
            int knight = tile_to_knight[next_tile_to_fill];
            get_path_for_knight(knight,next_tile_to_fill);

        }
        void solve(){
            print_board();
            
            //first move is special 
            move (3,4);
            move (4,9);

            // divide the board so that putting every knight in its place
            while(!reached_special_case()){
                guarini();
            }

            // this is a special case that we need to move back the knight at position 9
            move(9,4);
            guarini();

            // find the path for last knight
            get_path_for_knight(4,10);

            // that's it!! puzzle is solved
            
        }

};



int main(){
    Guarini_Puzzle g;
    g.solve();
}