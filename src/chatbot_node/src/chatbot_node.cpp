#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <string>

using namespace std;


//Add your code here

//callback for the subsriber 

void sent_msg_callback(const message_ui::sent_msg mess)
{
	//message=sent_msg.message;
  std::cout << "I heard" << std::endl;
  std::cout << mess.message<< std::endl;
	//cout<< message.message;

}

int main(int argc, char **argv) {

  ros::init(argc, argv, "chatbot_node");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("sent_msg", 1000, sent_msg_callback);
  

  //ros::Publisher reply_msg_pub = n.advertise<reply_msg.msg>("reply_msg",1000);

  //Add your code here



  ros::Rate loop_rate(20);

  while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
