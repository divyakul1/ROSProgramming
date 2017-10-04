#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <arithmetic_node/arithmetic_reply.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>

//std::string replymessage ("I didn't get that");



using namespace std;


//ros::NodeHandle n;

ros::Publisher pub;
ros::Subscriber sub;
arithmetic_node::arithmetic_reply response;



//ros::Publisher pub = n.advertise<chatbot_node::reply_msg>("reply_msg", 1000);

//Add your code here
int go_on =0;
//callback for the subsriber


void sent_msg_callback(const message_ui::sent_msg mess)
{
	//message=sent_msg.message;
  //std::cout << "I heard" << std::endl;
  //std::cout << mess.message<< std::endl;
	//cout<< message.message;

    float numbers[(mess.message).length()-1];
    string operand;
    string operandfinal;
    long finalfirstnumber;
    int finalfn;
    float addfinal=0;

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



/*

for(int m=1; m<mess.message.length(); m++){

    if (isalpha(mess.message[m])){
        go_on=1;
    }
    else{
        go_on=0;
    }
}

*/
    if (operand.compare("+") == 0){

        //then this is an add operator
        operandfinal="Add";
        float numbernew1=0;
        float numbernew2=0;

        for (int i=0; i < finalfn; i++) {

            numbernew1 = (pow(10, finalfn - i - 1) * numbers[i]) + numbernew1;
        }


            for (int k=finalfn+1; k< (mess.message).length(); k++){

                int length1=(mess.message).length()-(finalfn+1);

                numbernew2 = (pow(10,length1-(k-(finalfn+1))-1)) * numbers[k]+ numbernew2;

                //addfinal=numbernew2;

            }

        addfinal=numbernew1+numbernew2;
        response.oper_type=operandfinal;
        response.answer = addfinal; //actual answer to mathematical question

        response.time_answered=ros::Time::now().toSec();//time at which the calculation is complete
        response.process_time=response.time_answered-response.time_received; //the time difference between time received and time answered.

        pub.publish(response);


    }

    else if (operand.compare("-") == 0){

        //then this is an add operator
        operandfinal="Subract";
        float numbernew1=0;
        float numbernew2=0;

        for (int i=0; i < finalfn; i++) {
            //addfinal = addfinal*10 + numbers[i];

            //int number = 100 * int1 + 10 * int2 + int3;



            numbernew1 = (pow(10, finalfn - i - 1) * numbers[i]) + numbernew1;
        }


        for (int k=finalfn+1; k< (mess.message).length(); k++){

            int length1=(mess.message).length()-(finalfn+1);

            numbernew2 = (pow(10,length1-(k-(finalfn+1))-1)) * numbers[k]+ numbernew2;

            //addfinal=numbernew2;

        }

        addfinal=numbernew1-numbernew2;
        response.oper_type=operandfinal;
        response.answer = addfinal; //actual answer to mathematical question

        response.time_answered=ros::Time::now().toSec();//time at which the calculation is complete
        response.process_time=response.time_answered-response.time_received; //the time difference between time received and time answered.

        pub.publish(response);


    }

    else if (operand.compare("*") == 0){

        //then this is an add operator
        operandfinal="Multiply";
        float numbernew1=0;
        float numbernew2=0;

        for (int i=0; i < finalfn; i++) {
            //addfinal = addfinal*10 + numbers[i];

            //int number = 100 * int1 + 10 * int2 + int3;



            numbernew1 = (pow(10, finalfn - i - 1) * numbers[i]) + numbernew1;
        }


        for (int k=finalfn+1; k< (mess.message).length(); k++){

            int length1=(mess.message).length()-(finalfn+1);

            numbernew2 = (pow(10,length1-(k-(finalfn+1))-1)) * numbers[k]+ numbernew2;

            //addfinal=numbernew2;

        }

        addfinal=numbernew1*numbernew2;
        response.oper_type=operandfinal;
        response.answer = addfinal; //actual answer to mathematical question

        response.time_answered=ros::Time::now().toSec();//time at which the calculation is complete
        response.process_time=response.time_answered-response.time_received; //the time difference between time received and time answered.

        pub.publish(response);


    }

    else if (operand.compare("/") == 0){

        //then this is an add operator
        operandfinal="Divide";
        float numbernew1=0;
        float numbernew2=0;

        for (int i=0; i < finalfn; i++) {
            //addfinal = addfinal*10 + numbers[i];

            //int number = 100 * int1 + 10 * int2 + int3;



            numbernew1 = (pow(10, finalfn - i - 1) * numbers[i]) + numbernew1;
        }


        for (int k=finalfn+1; k< (mess.message).length(); k++){

            int length1=(mess.message).length()-(finalfn+1);

            numbernew2 = (pow(10,length1-(k-(finalfn+1))-1)) * numbers[k]+ numbernew2;

            //addfinal=numbernew2;

        }

        addfinal=numbernew1/numbernew2;
        response.oper_type=operandfinal;
        response.answer = addfinal; //actual answer to mathematical question

        response.time_answered=ros::Time::now().toSec();//time at which the calculation is complete
        response.process_time=response.time_answered-response.time_received; //the time difference between time received and time answered.

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
    response.time_received= ros::Time::now().toSec();



    ros::Rate loop_rate(20);

  while(ros::ok()) {

    ros::spinOnce();
    loop_rate.sleep();

  }

  return 0;
}
