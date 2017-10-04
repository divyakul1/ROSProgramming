#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <arithmetic_node/arithmetic_reply.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>


//std::string replymessage ("I didn't get that");



using namespace std;


//ros::NodeHandle n;

ros::Publisher pub;
ros::Subscriber sub;
arithmetic_node::arithmetic_reply response;



//ros::Publisher pub = n.advertise<chatbot_node::reply_msg>("reply_msg", 1000);

//Add your code here

//callback for the subsriber


void sent_msg_callback(const message_ui::sent_msg mess)
{
	//message=sent_msg.message;
  //std::cout << "I heard" << std::endl;
  //std::cout << mess.message<< std::endl;
	//cout<< message.message;
    response.time_received = ros::Time::now().toSec();

    float numbers[(mess.message).length()-1];
    string operand;
    string operandfinal;
    long finalfirstnumber;
    int finalfn;
    float addfinal=0;
    int go_on =0;
    float numbernew1 = 0;
    float numbernew2 = 0;

    int length3=mess.message.length();

    for (string::const_iterator it = mess.message.begin();
         it != mess.message.end(); it++) {


        // index = int()it;

        if (isdigit(*it)) {
            numbers[it - mess.message.begin()] = (int) *it - '0';
        }
        else {
            operand = *it;
            finalfirstnumber = it - mess.message.begin();
            finalfn = (int) finalfirstnumber;
        }
    }


    string str1 = mess.message.substr (0,finalfirstnumber);
    string str2 = mess.message.substr (finalfirstnumber+1,mess.message.length());
/*

    for (int i = 0; i < finalfn; i++) {

        numbernew1 = (pow(10, finalfn - i - 1) * numbers[i]) + numbernew1;
    }


    for (int k = finalfn + 1; k < (mess.message).length(); k++) {

        int length1 = (mess.message).length() - (finalfn + 1);

        numbernew2 = (pow(10, length1 - (k - (finalfn + 1)) - 1)) * numbers[k] + numbernew2;

        //addfinal=numbernew2;

    }

*/

    for(int m=0; m<mess.message.length(); m++){


        if (isalpha(mess.message[m])){
            go_on=1;
        }
        else if (isnan(numbernew1)){
            go_on=1;
        }

        else if (isnan(numbernew2)){
            go_on=1;
        }

        else if(mess.message[0]=='-'){
            go_on=1;
        }

        else if(mess.message[finalfn+1]=='-'){
            go_on=1;
        }


    }

    if (go_on==0) {

        numbernew1=stof(str1);
        numbernew2=stof(str2);


        if (operand.compare("+") == 0) {

            //then this is an add operator
            operandfinal = "Add";

            addfinal = numbernew1 + numbernew2;
            //addfinal=length3;


        } else if (operand.compare("-") == 0) {

            //then this is an add operator
            operandfinal = "Subract";

            addfinal = numbernew1 - numbernew2;


        } else if (operand.compare("*") == 0) {

            //then this is an add operator
            operandfinal = "Multiply";

            addfinal = numbernew1 * numbernew2;


        } else if (operand.compare("/") == 0) {

            //then this is an add operator
            operandfinal = "Divide";


            addfinal = numbernew1 / numbernew2;


        }

        response.oper_type = operandfinal;
        response.answer = addfinal; //actual answer to mathematical question

        response.time_answered = ros::Time::now().toSec();//time at which the calculation is complete
        response.process_time = response.time_answered -
                                response.time_received; //the time difference between time received and time answered.

        pub.publish(response);

    }



   // arithmetic_node::arithmetic_reply response;

    //response.header.stamp=ros::Time::now(); //time at which message is sent
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "arithmetic node");

  ros::NodeHandle n;

    //publish

  pub =n.advertise<arithmetic_node::arithmetic_reply>("arithmetic_reply", 1000);

    //subscribe



    sub = n.subscribe("sent_msg", 1000, sent_msg_callback);




    ros::Rate loop_rate(20);

  while(ros::ok()) {

    ros::spinOnce();
    loop_rate.sleep();

  }

  return 0;
}
