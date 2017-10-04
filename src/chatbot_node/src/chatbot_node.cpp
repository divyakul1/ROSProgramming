#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <string>

std::string replymessage ("I didn't get that");



using namespace std;


//ros::NodeHandle n;

ros::Publisher pub;

//ros::Publisher pub = n.advertise<chatbot_node::reply_msg>("reply_msg", 1000);

//Add your code here

//callback for the subsriber 

void sent_msg_callback(const message_ui::sent_msg mess) {
    //message=sent_msg.message;
    //std::cout << "I heard" << std::endl;
    //std::cout << mess.message<< std::endl;
    //cout<< message.message;


    if (isalpha(mess.message[1])) {

        if (mess.message.compare("Hello") == 0) {

            //std:string name=ros::param::get("Name");

            replymessage = "Hello Divya";
            //std::cout << replymessage << '\n';
        } else if (mess.message.compare("What is your name?") == 0) {

            replymessage = "My name is MRSD Siri";
            //std::cout << replymessage << '\n';
        } else if (mess.message.compare("How are you?") == 0) {
            replymessage = "I am fine, thank you";
            //std::cout << replymessage << '\n';
        } else {


            replymessage = "I didn't get that";
            //std::cout << replymessage << '\n';

        }


        chatbot_node::reply_msg response;
        response.message = replymessage;

        pub.publish(response);


    }
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "chatbot node");

  ros::NodeHandle n;

  pub =n.advertise<chatbot_node::reply_msg>("reply_msg", 1000);
  ros::Subscriber sub = n.subscribe("sent_msg", 1000, sent_msg_callback);


  ros::Rate loop_rate(20);

  while(ros::ok()) {

    ros::spinOnce();
    loop_rate.sleep();

  }

  return 0;
}
