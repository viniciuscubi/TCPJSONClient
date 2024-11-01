#include <string>
#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <chrono>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "../include/parser.hpp"
#include "../include/pinsys.hpp"
#include "../include/client.hpp"

#define test_pin 14

int main()
{

    std::vector<int> mea_time{1,5,10,60};
    std::string wifi_freq = "ETHERNET_CABLE_";
    std::vector<std::string> jsons;
    std::vector<std::string> n_bytes{"109","500"};

    std::string json_109 = "{\
        \"Transaction ID\":0,\
        \"Protocol ID\":0,\
        \"Length\":0,\
        \"Unit ID\":0,\
        \"Function Code\":0,\
        \"AHi\": 0,\
        \"ALo\":0,\
        \"NHi\":0,\
        \"NLo\":0\
        }";



    std::string json_500 = "{\
        \"Transaction ID\":0,\
        \"Protocol ID\":0,\
        \"Length\":0,\
        \"Unit ID\":0,\
        \"Function Code\":0,\
        \"AHi\": 0,\
        \"ALo\":0,\
        \"NHi\":0,\
        \"NLo\":0,\
        \"Lorem\":0,\
        \"ipsum\":0,\
        \"dolor\":0,\
        \"sit\":0,\
        \"amet\":0,\
        \"consectetur\":0,\
        \"adipiscing\":0,\
        \"elit\":0,\
        \"Nunc\":0,\
        \"nec\":0,\
        \"arcu\":0,\
        \"odio\":0,\
        \"Duis\":0,\
        \"gravida\":0,\
        \"ex\":0,\
        \"id\":0,\
        \"tempor\":0,\
        \"eleifend\":0,\
        \"Vivamus\":0,\
        \"a\":0,\
        \"vulputate\":0,\
        \"dapibus\":0,\
        \"lacus\":0,\
        \"quis\":0,\
        \"mattis\":0,\
        \"Donec\":0,\
        \"sed\":0,\
        \"libero\":0,\
        \"Lorem\":0,\
        \"ipsum\":0,\
        \"dolor\":0,\
        \"sit\":0,\
        \"amet\":0,\
        \"consectetur\":0,\
        \"adipiscin\":0,\
        \"eli\":0,\
        \"Nun\":0,\
        \"pindorama\":0\
        }";    

    jsons.push_back(json_109);
    jsons.push_back(json_500);

    
    for(int i = 0; i < 2; i++){

        for(int j = 0; j < (int)mea_time.size(); j++){

            std::cout << wifi_freq << "Testing..." << std::endl;
            std::cout << "Packet size: "  << std::setw(3) << std::setfill('0') <<  n_bytes[i] << "Bytes" << std::endl;
            std::cout << "Testing time: " << std::setw(2) << std::setfill('0') << mea_time[j] << "s" << std::endl;

            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') <<  n_bytes[i] << "B_" << wifi_freq << std::setw(2) << std::setfill('0') << mea_time[j] << "s.txt";
            
            std::ofstream file(ss.str());

            bool var = true;

            PinSys ps(test_pin);

            Client cv("tcp://192.168.1.102:5555");

            std::string data = jsons[i];
            //std::cout << std::fixed << std::setprecision(4);
            file << std::fixed << std::setprecision(4);

            auto start_test = std::chrono::steady_clock::now();
            int exp_elapsed_time = 0;

            while(exp_elapsed_time < mea_time[j]) {

                auto start = std::chrono::steady_clock::now();

                cv.send(data);

                std::string reply = cv.receive();

                auto end = std::chrono::steady_clock::now();
                
/*
                std::cout << reply.size() << " bytes " 
                << "time="  
                << ((double)(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()))/2000000 
                << " ms" << std::endl;
*/

                file <<reply.size() << " bytes " 
                << "time="  
                << ((double)(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()))/2000000 
                << " ms" << std::endl;

                Parser parser(reply);

                if(parser.parse()){
                    rapidjson::Value &dat = parser.getData();
                    rapidjson::Value& ahi = dat["AHi"];

                    if(ahi.GetInt()){
                        var = true;
                    }else{
                        var = false;
                    }
                    ps.updatePin(var);
                    data = reply;

                }else{
                    std::cerr << "error" << std::endl;

                }        

                exp_elapsed_time = (int)(std::chrono::duration_cast<std::chrono::seconds>
                                    (std::chrono::steady_clock::now() - start_test).count());
            }

            file.close();

        }

    }

    return 0;
}