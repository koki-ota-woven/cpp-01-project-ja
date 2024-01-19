#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <string>
#include "Player.h"

// 地図の大きさの設定
const int row = 50;
const int column = 100;
const int reload_time = 1000; // 地図を読み込む時間の設定
// 地図のアイコンの設定
const char fuel_station_icon = 'F';
const char passenger_icon = 'P';
const char goal_icon = 'G';
const char player_icon = 'O';

// 罰金等の設定
const int gas_price = 20;
const int direction_fine = 50;
const int speed_limit_fine = 10;
const int speed_limit = 4;

const int sunrise_time = 7;
const int sunset_time = 19;

std::atomic_bool inputReady(false);
std::string input;

// ユーザーからのコマンドの受付
void getInput() {
    while (true) {
        std::string command;
        std::cin >> command;
        if (command != "") {
            input = command;
            inputReady = true;
        }
    }
}

// 最新の状態の道路状況を描画する関数
void printRace(char array1[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            std::cout << array1[i][j];
        }
        std::cout << std::endl;
    }
}

// ベースとなる道路の描画の準備
void initRace(char track[row][column], char padding_char) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (i == 0) {
                track[i][j] = '-';
            } else if (i == row-1) {
                track[i][j] = '-';
            } else if (j == 0) {
                track[i][j] = '|';
            } else if (i == 18 && j > 20 && j < 60) {
                track[i][j] = '-';
            } else if (i == 22 && j > 20 && j < 60) {
                track[i][j] = '-';
            } else if (i == 20 && j > 25 && j < 40) {
                track[i][j] = '=';
            } else if (i == 20 && j == 40) {
                track[i][j] = '>';
            } else if (j == column-1) {
                track[i][j] = '|';
            } else {
                track[i][j] = padding_char;
            }
        }
    }
}

// ガードレールへの衝突判定
bool detectPosition(int player_position_x, int player_position_y, char track[row][column]){
    if (player_position_x > column || player_position_x < 0){
        return false;
    } else if (player_position_y > row || player_position_y < 0){
        return false;
    } if (track[player_position_y][player_position_x] == '-') {
        return false;
    } else if (track[player_position_y][player_position_x] == '|'){
        return false;
    }
    return true;
}

// ユーアーの入力に応じた次のプレイヤーの座標の設定
bool movePlayer(int& player_position_x, int& player_position_y, const std::string& direction, char track[row][column], Player player) {
    int new_player_position_x = player_position_x;
    int new_player_position_y = player_position_y;

    if (direction == "+y") {
        new_player_position_y += player.getSpeed();
    } else if (direction == "-y") {
        new_player_position_y -= player.getSpeed();
    } else if (direction == "+x") {
        new_player_position_x += player.getSpeed();
    } else if (direction == "-x") {
        new_player_position_x -= player.getSpeed();
    }

    if (!detectPosition(new_player_position_x, new_player_position_y, track)) {
        std::cout << "GAME OVER: Bump into a guard rail" << std::endl;
        player.stop();
        return false;
    } else {
        player_position_x = new_player_position_x;
        player_position_y = new_player_position_y;
        return true;
    }
}


int main() {
    char car_type;

    std::cout << "G (Gasoline) or H (Hybrid): ";
    std::cin >> car_type;
    if (car_type != 'G' && car_type != 'H'){
        std::cout << "Please select T(Toyota) or H(Honda)" << std::endl;
        return 1;
    }

    std::thread inputThread(getInput);
    Player player(car_type);

    // 各ポイントの初期位置の設定
    int player_position_x = 5;
    int player_position_y = 1;
    int fuel_station_1_x = 50;
    int fuel_station_1_y = 30;
    int fuel_station_2_x = 10;
    int fuel_station_2_y = 10;
    int passenger_position_x = 50;
    int passenger_position_y = 20;
    int goal_position_x = 95;
    int goal_position_y = 46;
    int time = 7;
    char padding_char;
    std::string direction = "+y";
    std::string weather;
    std::string day_state;

    while (true) {
        // 時間によって昼、夜の状態を変更
        if (time >= sunrise_time && time <= sunset_time ){
            padding_char = ' ';
            day_state = "Daytime";
        } else {
            padding_char = 'X';
            day_state = "Night";
        }

        // 10%の確率で天候を雨に設定
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        int weather_number = std::rand() % 10;
        if (weather_number == 9){
            weather = "Rain";
        } else {
            weather = "Sunny";
        }

        // 現在のゲーム状況の出力
        std::cout << "Mission: Take a passenger to goal" << std::endl;
        std::cout << "<ICON>  O: player,  F: gas station,  P: passenger,  G: Goal,  ====>: One Direction Area" << std::endl;
        std::cout << "Time: " << time << ":00      State: " << day_state << "       Weather: " << weather<< std::endl;

        // 最新の状態での地図の描画の実行
        char track[row][column];
        initRace(track, padding_char);
        if (player.getPassenger() == 0) {
            track[passenger_position_y][passenger_position_x] = passenger_icon;
        }
        track[fuel_station_1_y][fuel_station_1_x] = fuel_station_icon;
        track[fuel_station_2_y][fuel_station_2_x] = fuel_station_icon;
        track[player_position_y][player_position_x] = player_icon;
        track[goal_position_y][goal_position_x] = goal_icon;
        printRace(track);
        player.showInfo();

        // 一方通行の道路で逆走した場合の処理
        if ((player_position_x > 20) && (player_position_x < 60) && (player_position_y > 18) && (player_position_y < 22)) {
            if (direction == "-x") {
                std::cout << "You break the one-direction path rule, You have to pay $" << direction_fine << std::endl;
                player.pay(direction_fine);
            }
        }

        // 速度超過した場合の処理
        if (player.getSpeed() > speed_limit) {
            std::cout << "You exceeded the speed limit 4, You have to pay $" << speed_limit_fine << std::endl;
            player.pay(speed_limit_fine);
        }

        // 燃料の消費
        player.consumeFuel();

        // リロードの時間の調整
        std::this_thread::sleep_for(std::chrono::milliseconds(reload_time));

        //　時刻の設定
        if (time >= 23) {
            time = 0;
        } else{
            time += 1;
        }

        // ガスステーション1での給油処理
        if ((player_position_x == fuel_station_1_x) && (player_position_y == fuel_station_1_y)) {
            player.refuel();
            player.pay(gas_price);
        }

        // ガスステーション2での給油処理
        if ((player_position_x == fuel_station_2_x) && (player_position_y == fuel_station_2_y)) {
            player.refuel();
            player.pay(gas_price);
        }

        // 乗客を乗せる処理
        if ((player_position_x == passenger_position_x) && (player_position_y == passenger_position_y)) {
            player.passengerRide();
        }

        // ゲームクリアの処理
        if ((player.getPassenger() == 1) &&
            (player_position_x == goal_position_x) && (player_position_y == goal_position_y)) {
            std::cout << "Clear: Well Done!!" << std::endl;
            break;
        }

        // エンジン切れでのゲームオーバーの条件
        if (player.getFuel() < 0) {
            std::cout << "GAME OVER: There is no fuel" << std::endl;
            break;
        }

        // 破産でのゲームオーバーの条件
        if (player.getBalance() < 0) {
            std::cout << "GAME OVER: Bankrupt" << std::endl;
            break;
        }

        // ユーザーの入力のゲームへの反映
        if (inputReady) {
            if (input == "h") {
                direction = player.goLeft();
            } else if (input == "l") {
                direction = player.goRight();
            } else if (input == "k") {
                direction = player.goUp();
            } else if (input == "j") {
                direction = player.goDown();
            } else if (input == "a") {
                player.accelerate();
            } else if (input == "d") {
                player.decelerate();
            } else if (input == "s") {
                if (weather == "Rain") continue;
                player.stop();
            } else if (input == "r") {
                player.refuel();
            } else if (input == "q") {
                break;
            } else {
                std::cout << "!!!!Invalid command!!!!" << std::endl;
            }
            inputReady = false;
        }
        std::cout << std::endl << std::endl;

        // ガードレールにぶつかった場合、ループを抜ける
        if (not movePlayer(player_position_x, player_position_y, direction, track, player)){
            break;
        }
    }

    inputThread.join();
    return 0;
}
